#include <string>
#include <vector>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRExpected.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRSurroundingContour.h>
#include <MRMesh/MRFillContourByGraphCut.h>
#include <MRMesh/MREdgeMetric.h>
#include <MRMesh/MREdgePoint.h>
#include <MRMesh/MRPolyline.h>
#include <MRMesh/MRLine3.h>
#include <MRMesh/MRMeshProject.h>
#include <MRMesh/MRContoursCut.h>
#include <MRMesh/MRPolylineProject.h>
#include <MRMesh/MRMeshBoolean.h>
#include <MRMesh/MROneMeshContours.h>
#include <MRMesh/MRMeshIntersect.h>
#include <MRMesh/MRParallelFor.h>
#include <MRMesh/MRFillContour.h>
#include <MRMesh/MREdgePaths.h>
#include <MRMesh/MREnums.h>
#include <MRMesh/MRSignDetectionMode.h>
#include <MRMesh/MRMeshBuilder.h>
#include <MRMesh/MRMeshBuilderTypes.h>
#include <MRMesh/MRProgressCallback.h>
#include <MRMesh/MRTriMesh.h>
#include <MRMesh/MRMeshFillHole.h>
#include <MRMesh/MRMeshSubdivide.h>
#include <MRMesh/MRPositionVertsSmoothly.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRPolyline.h>
#include <MRMesh/MRTimer.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRAABBTreePoints.h>
#include <MRMesh/MRBuffer.h>
#include <MRMesh/MRPartMapping.h>
#include <MRMesh/MRLineSegm.h>
#include <MRMesh/MRLineSegm3.h>
#include <MRMesh/MRMeshMath.h>
#include <MRMesh/MRPointOnFace.h>
#include <MRMesh/MRMesh.h>

#include <MRVoxels/MRFixUndercuts.h>
#include <MRVoxels/MROffset.h>

#include "MRMesh.h"
#include "MRUtils.h"
#include "MREdgeMetric.h"

using namespace emscripten;
using namespace MR;
using namespace MeshBuilder;

namespace MRJS
{

// ------------------------------------------------------------------------
// Bindings for `Mesh`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( MeshModule )
{
	class_<Mesh>( "Mesh" )
		.smart_ptr<std::shared_ptr<Mesh>>( "MeshSharedPtr" )
		.constructor<>()

		.property( "topology", &Mesh::topology )
		.property( "points", &Mesh::points )

		///
		// NOTE: Let `emscripten` to handle exceptions, it will throw them on the JS side
		// 
		// Example usage:
		// 
		//  ```js
		//  /// Vertices
		//  // 1) allocate `nVerts*3` floats in WASM
		//  const verticesCount = vertices.length; 
		//  // NOTE: In `_malloc`, the specified value is in bytes, not in the number of elements
		//  // Each element in `Float32Array` occupies **4 bytes** (32 bits = 4 bytes)
		//  const verticesPtr = editor.mrmesh._malloc( verticesCount * 4 );
		//  // 2) construct a JS Float32Array that _views_ the WASM heap:
		//  const jsVertices = new Float32Array( editor.mrmesh.HEAPF32.buffer, verticesPtr, verticesCount );
		//  // 3) copy into it (once), or let your own code fill it:
		//  jsVertices.set( vertices );
		//  ///
		// 
		// 
		// 	/// Indices
		// 	const indicesCount = indices.length;
		// 	const indicesPtr = editor.mrmesh._malloc( indicesCount * 4 );
		// 	const jsIndices = new Uint32Array( editor.mrmesh.HEAPU32.buffer, indicesPtr, indicesCount );
		// 	jsIndices.set( indices );
		// 	///
		// 
		//  try {
		//  	const mesh = Module.fromTrianglesMemoryView( jsVertices, jsIndices );
		// 
		//      // ...
		// 
		//      // NOTE: This is IMPORTANT!!!
		//      mesh.delete();
		//  } catch ( error ) {
		//  	console.error( 'Error creating mesh:', error.message );
		//  }
		//  ```
		// 
		.class_function( "fromTrianglesMemoryView", 
			optional_override( [] ( const val& verticesArray, const val& indicesArray ) -> Mesh
			{
				try
				{
					if ( !verticesArray.instanceof( val::global( "Float32Array" ) ) )
					{
						throw std::runtime_error( "vertices must be Float32Array" );
					}
					if ( !indicesArray.instanceof( val::global( "Uint32Array" ) ) )
					{
						throw std::runtime_error( "indices must be Uint32Array" );
					}

					int verticesLength = verticesArray["length"].as<int>();
					int indicesLength = indicesArray["length"].as<int>();

					if ( verticesLength % 3 != 0 )
					{
						throw std::runtime_error( "vertices array length must be divisible by 3" );
					}
					if ( indicesLength % 3 != 0 )
					{
						throw std::runtime_error( "indices array length must be divisible by 3" );
					}

					int numVerts = verticesLength / 3;
					int numTris = indicesLength / 3;


					///
					// NOTE: Directly access the memory of `TypedArray` without copying
					size_t verticesByteOffset = verticesArray["byteOffset"].as<size_t>();
					const float* verticesPtr = reinterpret_cast<const float*>( verticesByteOffset );

					size_t indicesByteOffset = indicesArray["byteOffset"].as<size_t>();
					const uint32_t* indicesPtr = reinterpret_cast<const uint32_t*>( indicesByteOffset );
					///


					///
					VertCoords vCoords;
					vCoords.resize( numVerts );

					for ( int i = 0; i < numVerts; ++i )
					{
						int baseIdx = i * 3;
						vCoords[VertId( i )] = Vector3f(
							verticesPtr[baseIdx],
							verticesPtr[baseIdx + 1],
							verticesPtr[baseIdx + 2]
						);
					}
					///

					///
					Triangulation triangulation;
					triangulation.resize( numTris );

					for ( int i = 0; i < numTris; ++i )
					{
						int baseIdx = i * 3;
						triangulation[FaceId( i )] = ThreeVertIds{
							VertId( indicesPtr[baseIdx] ),
							VertId( indicesPtr[baseIdx + 1] ),
							VertId( indicesPtr[baseIdx + 2] )
						};
					}
					///

					const auto res = Mesh::fromTrianglesDuplicatingNonManifoldVertices( std::move( vCoords ), triangulation );
					return res;
				}
				catch ( const std::exception& e )
				{
					// Or return an empty `Mesh`
					// return Mesh();
					throw std::runtime_error( std::string( e.what() ) );
				}
			} )
		)
		// 
		// Example usage
		// 
		//  ```js
		//  // Three.js geometry
		//  const geometry = new THREE.BufferGeometry();
		//  const vertices = geometry.getAttribute('position').array; // `Float32Array`
		//  const indices = geometry.getIndex().array; // `Uint32Array`
		//  
		//  const mesh = MeshWrapper.fromTrianglesImpl( vertices, indices );
		// 
		//  // ...
		// 
		//  // NOTE: This is IMPORTANT!!!
		//  mesh.delete();
		//  ```
		// 
		.class_function( "fromTrianglesArray",
			optional_override( [] ( const val& verticesArray, const val& indicesArray ) -> Mesh*
			{
				try
				{
					if ( !verticesArray.instanceof( val::global( "Float32Array" ) ) )
					{
						throw std::runtime_error( "vertices must be Float32Array" );
					}
					if ( !indicesArray.instanceof( val::global( "Uint32Array" ) ) )
					{
						throw std::runtime_error( "indices must be Uint32Array" );
					}

					int verticesLength = verticesArray["length"].as<int>();
					int indicesLength = indicesArray["length"].as<int>();

					if ( verticesLength % 3 != 0 )
					{
						throw std::runtime_error( "vertices array length must be divisible by 3" );
					}
					if ( indicesLength % 3 != 0 )
					{
						throw std::runtime_error( "indices array length must be divisible by 3" );
					}

					int numVerts = verticesLength / 3;
					int numTris = indicesLength / 3;


					///
					std::vector<float> verticesVec = emscripten::convertJSArrayToNumberVector<float>( verticesArray );
					std::vector<uint32_t> indicesVec = emscripten::convertJSArrayToNumberVector<uint32_t>( indicesArray );
					const float* verticesPtr = verticesVec.data();
					const uint32_t* indicesPtr = indicesVec.data();
					///


					///
					VertCoords vCoords;
					vCoords.resize( numVerts );

					// Read vertex data from vector (memory contiguous, high performance)
					for ( int i = 0; i < numVerts; ++i )
					{
						int baseIdx = i * 3;
						vCoords[VertId( i )] = Vector3f(
							verticesPtr[baseIdx],
							verticesPtr[baseIdx + 1],
							verticesPtr[baseIdx + 2]
						);
					}
					///

					///
					Triangulation triangulation;
					triangulation.resize( numTris );

					for ( int i = 0; i < numTris; ++i )
					{
						int baseIdx = i * 3;
						triangulation[FaceId( i )] = ThreeVertIds{
							VertId( indicesPtr[baseIdx] ),
							VertId( indicesPtr[baseIdx + 1] ),
							VertId( indicesPtr[baseIdx + 2] )
						};
					}
					///

					return new Mesh( Mesh::fromTriangles( std::move(vCoords ), triangulation ) );
				}
				catch ( const std::exception& e )
				{
					throw std::runtime_error( std::string( e.what() ) );
				}
			} ),
			// IMPORTANT: JS is responsible for `.delete()` when it gets it!!!
			return_value_policy::take_ownership()
		)

		.class_function( "getGeometry",
			optional_override( []( Mesh& mesh ) -> val
			{
				val meshData = MRJS::exportMeshMemoryView( mesh );

				val geoObj = val::object();
				geoObj.set( "success", true );
				geoObj.set( "mesh", meshData );

				return geoObj;
			})
		)
		///

		///
		.function( "fromTriangles", &Mesh::fromTriangles )

		.function( "fromTriMesh",
			optional_override( [] ( TriMesh& triMesh, const MeshBuilder::BuildSettings& settings, ProgressCallback cb ) -> Mesh
			{
				return Mesh::fromTriMesh( std::move( triMesh ), settings, cb );
			} )
		)
		.function( "fromTriMeshWithUniquePtr",
			optional_override( [] ( std::unique_ptr<TriMesh> triMesh, const MeshBuilder::BuildSettings& settings, ProgressCallback cb ) -> Mesh
			{
				return Mesh::fromTriMesh( std::move( *triMesh ), settings, cb );
			} ),
			allow_raw_pointers()
		)
		.function( "fromTriMeshWithoutProgressCallback",
			optional_override( [] ( TriMesh& triMesh, const MeshBuilder::BuildSettings& settings ) -> Mesh
			{
				return Mesh::fromTriMesh( std::move( triMesh ), settings );
			} )
		)
		.function( "fromTriMeshWithDefaultSettings",
			optional_override( [] ( TriMesh& triMesh ) -> Mesh
			{
				MeshBuilder::BuildSettings defaultSettings;
				return Mesh::fromTriMesh( std::move( triMesh ), defaultSettings );
			} )
		)

		.function( "fromTrianglesDuplicatingNonManifoldVertices", &Mesh::fromTrianglesDuplicatingNonManifoldVertices, allow_raw_pointers() )
		.function( "fromFaceSoup", &Mesh::fromFaceSoup )
		.function( "fromPointTriples", &Mesh::fromPointTriples )
		///

		.function( "equals", optional_override( [] ( const Mesh& self, const Mesh& other )
		{
			return self == other;
		} ) )

		.function( "orgPnt", &Mesh::orgPnt )
		.function( "destPnt", &Mesh::destPnt )
		.function( "edgeVector", &Mesh::edgeVector )
		.function( "edgeSegment", &Mesh::edgeSegment )

		.function( "edgePoint", select_overload<Vector3f ( EdgeId, float ) const>( &Mesh::edgePoint ))
		.function( "edgePointWithMeshEdgePoint", select_overload<Vector3f ( const MeshEdgePoint& ) const>( &Mesh::edgePoint ))

		.function( "edgeCenter", &Mesh::edgeCenter )

		.function( "getLeftTriPoints", select_overload<void( EdgeId, Vector3f&, Vector3f&, Vector3f& ) const>( &Mesh::getLeftTriPoints ) )
		// FIXME
		// .function( "getLeftTriPointsWithArray3Vector3f", select_overload<void ( EdgeId, std::array<Vector3f, 3>& ) const>( &Mesh::getLeftTriPoints ))
		.function( "getLeftTriPointsWithTriangle3f", select_overload<Triangle3f ( EdgeId ) const>( &Mesh::getLeftTriPoints ))

		.function( "getTriPoints", select_overload<void( FaceId, Vector3f &, Vector3f &, Vector3f & ) const>( &Mesh::getTriPoints ) )
		// FIXME
		// .function( "getTriPointsWithArray3Vector3f", select_overload<void( FaceId, std::array<Vector3f, 3>& ) const>( &Mesh::getTriPoints ) )
		.function( "getTriPointsWithTriangle3f", select_overload<Triangle3f( FaceId ) const>( &Mesh::getTriPoints ) )
	
		.function( "triPoint", &Mesh::triPoint )
		.function( "triCenter", &Mesh::triCenter )
		.function( "triangleAspectRatio", &Mesh::triangleAspectRatio )
		.function( "circumcircleDiameterSq", &Mesh::circumcircleDiameterSq )
		.function( "circumcircleDiameter", &Mesh::circumcircleDiameter )

		.function( "toTriPoint", select_overload<MeshTriPoint( VertId ) const>( &Mesh::toTriPoint ) )
		.function( "toTriPointWithFaceId", select_overload<MeshTriPoint( FaceId, const Vector3f & ) const>( &Mesh::toTriPoint ) )
		.function( "toTriPointWithPointOnFace", select_overload<MeshTriPoint( const PointOnFace& ) const>( &Mesh::toTriPoint ) )
	
		.function( "toEdgePoint", select_overload<MeshEdgePoint( VertId ) const>( &Mesh::toEdgePoint ) )
		.function( "toEdgePointWithEdgeId", select_overload<MeshEdgePoint( EdgeId, const Vector3f & ) const>( &Mesh::toEdgePoint ) )

		.function( "getClosestVertex", select_overload<VertId( const PointOnFace & ) const>( &Mesh::getClosestVertex ) )
		.function( "getClosestVertexWithMeshTriPoint", select_overload<VertId( const MeshTriPoint & p ) const>( &Mesh::getClosestVertex ) )
	
		.function( "getClosestEdge", select_overload<UndirectedEdgeId( const PointOnFace& ) const>( &Mesh::getClosestEdge ) )
		.function( "getClosestEdgeWithMeshTriPoint", select_overload<UndirectedEdgeId( const MeshTriPoint& ) const>( &Mesh::getClosestEdge ) )

		.function( "volume", &Mesh::volume, allow_raw_pointers() )
		.function( "normalWithFaceId", select_overload<Vector3f ( const FaceId ) const>( &Mesh::normal ))
		.function( "normalWithMeshTriPoint", select_overload<Vector3f ( VertId ) const>( &Mesh::normal ))
		.function( "normal", select_overload<Vector3f ( const MeshTriPoint & ) const>( &Mesh::normal ))

		.function( "getBoundingBox", &Mesh::getBoundingBox )
		.function( "computeBoundingBoxWithFaceBitSet", select_overload<Box3f ( const AffineXf3f * ) const>( &Mesh::computeBoundingBox ), allow_raw_pointers() )
		.function( "computeBoundingBox", select_overload<Box3f ( const FaceBitSet*, const AffineXf3f* ) const>( &Mesh::computeBoundingBox ), allow_raw_pointers() )
		.function( "transform", &Mesh::transform, allow_raw_pointers() )
		.function( "addPoint", &Mesh::addPoint )
		.function( "addSeparateEdgeLoop", &Mesh::addSeparateEdgeLoop )
		.function( "addSeparateContours", &Mesh::addSeparateContours, allow_raw_pointers() )
		.function( "attachEdgeLoopPart", &Mesh::attachEdgeLoopPart )
	
		.function( "addMeshWithPartMapping", select_overload<void( const Mesh&, PartMapping, bool )>( &Mesh::addMesh ) )
		.function( "addMesh", select_overload<void (const Mesh &, FaceMap *, VertMap *, WholeEdgeMap *, bool)>( &Mesh::addMesh ), allow_raw_pointers())
		.function( "addMeshPartWithPartMapping", select_overload<void ( const MeshPart &, const PartMapping& )>( &Mesh::addMeshPart ))
		.function( "addMeshPart", select_overload<void ( const MeshPart &, bool,
        const std::vector<EdgePath> &, const std::vector<EdgePath> &, PartMapping )>( &Mesh::addMeshPart ))
		.function( "cloneRegion", &Mesh::cloneRegion )
		
		.function( "packWithPartMapping", select_overload<void( const PartMapping&, bool )>( &Mesh::pack ) )
		.function( "packWithMap", select_overload<void( FaceMap*, VertMap*, WholeEdgeMap*, bool )>( &Mesh::pack ), allow_raw_pointers() )
		.function( "pack", select_overload<Expected<void>( const PackMapping&, ProgressCallback )>( &Mesh::pack ) )

		///
		// NOTE: `copy constructor of 'PackMapping' is implicitly deleted because field 'e' has a deleted copy constructor`
		.function( "packOptimally", 
			optional_override( []( Mesh& self, bool param ) -> std::unique_ptr<PackMapping> {
				// `packOptimally` returns the value by using `std::move()`
				return std::make_unique<PackMapping>( self.packOptimally( param ) );
			}),
			allow_raw_pointers()
		)
		// 
		// NOTE
		// 
		// 1️⃣ `static`: Ensures that `result` is the same object across multiple calls to the function (independent for each thread).
		// 2️⃣ `thread_local`: In a multithreaded context, each thread has its own copy of `result`, avoiding interference and preventing data races.
		// 3️⃣ `return &result;`: Returns a pointer to this static variable to Emscripten, allowing JS to obtain a raw pointer.
		// 
		// 📌 Why do this?
		// - Because `PackMapping` cannot be copied, it can only be moved.
		// - Emscripten defaults to copying return values (it does not support directly returning move-only values).
		// - Using a `thread_local` static variable effectively places `PackMapping` outside the stack, and returning a pointer bypasses the copy restriction.
		// 
		// ⚡ This is an older technique used to expose a non-copyable large object to JS.
		// 
		// ✅ When is it reasonable to use?
		// - Multiple threads will not share the same `result` instance, as `thread_local` ensures each thread has its own copy.
		// - The pointer returned from C++ to JS must be used quickly and not stored for too long or used asynchronously, as the next C++ call will overwrite `result`.
		// - Be cautious: if there is concurrent access in multithreading, or if JS holds the pointer for too long, there is a risk. If JS saves this pointer to a global variable or passes it to asynchronous logic, the next C++ call may have overwritten or released `result`, leading to reading invalid memory.
		// 
		// 🔑 Modern solution:
		// - Use `std::unique_ptr<PackMapping>`, directly returning a smart pointer, allowing Embind to manage the lifecycle, which is safer and free from race conditions.
		// 
		.function( "packOptimallyWithThreadLocalPtr",
			optional_override( [] ( Mesh& self, bool param ) -> PackMapping*
			{
				static thread_local PackMapping result;
				result = self.packOptimally( param );
				return &result;
			} ),
			allow_raw_pointers()
		)
		// The JS side must call `.delete()` to release it manually, otherwise it will leak memory!
		.function( "packOptimallyByNew",
			optional_override( [] ( Mesh& self, bool param ) -> PackMapping*
				{
					return new PackMapping( self.packOptimally( param ) );
				} 
			),
			allow_raw_pointers()
		)

		.function( "packOptimallyWithProgressCallback",
			optional_override( []( Mesh& self, bool param, ProgressCallback callback ) -> std::unique_ptr<PackMapping> {
				auto result = self.packOptimally( param, callback );
				
				if ( result.has_value() ) {
					return std::make_unique<PackMapping>( std::move( result.value() ) );
				} else {
					throw std::runtime_error( result.error() );
				}
			}),
			allow_raw_pointers()
		)
		///

		.function( "deleteFaces", &Mesh::deleteFaces, allow_raw_pointers() )

		.function( "projectPointWithPointOnFace", select_overload<bool( const Vector3f&, PointOnFace&, float, const FaceBitSet*, const AffineXf3f* ) const>( &Mesh::projectPoint ), allow_raw_pointers() )
		.function( "projectPointWithProjectionResult", select_overload<bool ( const Vector3f&, MeshProjectionResult&, float, const FaceBitSet*, const AffineXf3f * ) const>( &Mesh::projectPoint ), allow_raw_pointers() )
		.function( "projectPoint", select_overload<MeshProjectionResult ( const Vector3f&, float, const FaceBitSet *, const AffineXf3f * ) const>( &Mesh::projectPoint ), allow_raw_pointers() )
		.function( "findClosestPointWithProjectionResult", select_overload<bool ( const Vector3f&, MeshProjectionResult&, float, const FaceBitSet*, const AffineXf3f * ) const>( &Mesh::findClosestPoint ), allow_raw_pointers() )
		.function( "findClosestPoint", select_overload<MeshProjectionResult ( const Vector3f&, float, const FaceBitSet *, const AffineXf3f * ) const>( &Mesh::findClosestPoint ), allow_raw_pointers() )

		// HACK
		// 
		// The copy constructor of the `AABBTree` class is private, 
		// while Emscripten needs to create a copy of the object when generating the binding
		// 
		.function( "getAABBTree", optional_override( [] ( const Mesh& mesh ) -> const AABBTree*
		{
			return &mesh.getAABBTree();
		} ), allow_raw_pointers() )
		.function( "getAABBTreeNotCreate", &Mesh::getAABBTreeNotCreate, allow_raw_pointers() )
		// HACK
		.function( "getAABBTreePoints", optional_override( [] ( const Mesh& mesh ) -> const AABBTreePoints*
		{
			return &mesh.getAABBTreePoints();
		} ), allow_raw_pointers() )
		.function( "getAABBTreePointsNotCreate", &Mesh::getAABBTreePointsNotCreate, allow_raw_pointers() )
		.function( "getDipolesNotCreate", &Mesh::getDipolesNotCreate, allow_raw_pointers() )
		.function( "invalidateCaches", &Mesh::invalidateCaches )
		.function( "updateCaches", &Mesh::updateCaches )
		.function( "heapBytes", &Mesh::heapBytes )
		.function( "shrinkToFit", &Mesh::shrinkToFit )
		.function( "mirror", &Mesh::mirror )
		.function( "signedDistance", select_overload<float( const Vector3f& ) const>( &Mesh::signedDistance ) );


	function( "computeVertexNormalsImpl", +[] ( const Mesh& mesh )
	{
		std::vector<Vector3f> normals;
		for ( VertId v{ 0 }; v < mesh.topology.vertSize(); ++v )
		{
			if ( mesh.topology.hasVert( v ) )
			{
				normals.push_back( mesh.normal( v ) );
			}
		}
		
		return MRJS::vector3fToFloat32Array( normals );
	} );
}


// ------------------------------------------------------------------------
// Wrapper for `Mesh`
// ------------------------------------------------------------------------
MeshWrapper::MeshWrapper( const Mesh& m ) : mesh( m ) {}

Mesh MeshWrapper::getMesh() { return mesh; }
Mesh* MeshWrapper::getMeshPtr() { return &mesh; }

val MeshWrapper::fromTrianglesImpl( const val& verticesArray, const val& indicesArray )
{
	val result = val::object();

	try
	{
		if ( !verticesArray.instanceof( val::global( "Float32Array" ) ) )
		{
			throw std::runtime_error( "vertices must be Float32Array" );
		}
		if ( !indicesArray.instanceof( val::global( "Uint32Array" ) ) )
		{
			throw std::runtime_error( "indices must be Uint32Array" );
		}

		int verticesLength = verticesArray["length"].as<int>();
		int indicesLength = indicesArray["length"].as<int>();

		if ( verticesLength % 3 != 0 )
		{
			throw std::runtime_error( "vertices array length must be divisible by 3" );
		}
		if ( indicesLength % 3 != 0 )
		{
			throw std::runtime_error( "indices array length must be divisible by 3" );
		}

		int numVerts = verticesLength / 3;
		int numTris = indicesLength / 3;


		///
		size_t verticesByteOffset = verticesArray["byteOffset"].as<size_t>();
		const float* verticesPtr = reinterpret_cast<const float*>( verticesByteOffset );

		size_t indicesByteOffset = indicesArray["byteOffset"].as<size_t>();
		const uint32_t* indicesPtr = reinterpret_cast<const uint32_t*>( indicesByteOffset );
		///


		///
		VertCoords vCoords;
		vCoords.resize( numVerts );

		for ( int i = 0; i < numVerts; ++i )
		{
			int baseIdx = i * 3;
			vCoords[VertId( i )] = Vector3f(
				verticesPtr[baseIdx],
				verticesPtr[baseIdx + 1],
				verticesPtr[baseIdx + 2]
			);
		}
		///

		///
		Triangulation triangulation;
		triangulation.resize( numTris );

		for ( int i = 0; i < numTris; ++i )
		{
			int baseIdx = i * 3;
			triangulation[FaceId( i )] = ThreeVertIds{
				VertId( indicesPtr[baseIdx] ),
				VertId( indicesPtr[baseIdx + 1] ),
				VertId( indicesPtr[baseIdx + 2] )
			};
		}
		///

		auto mesh = Mesh::fromTriangles( std::move( vCoords ), triangulation );

		result.set( "success", true );
		result.set( "mesh", MeshWrapper( mesh ) );
	}
	catch ( const std::exception& e )
	{
		result.set( "success", false );
		result.set( "error", std::string( e.what() ) );
	}

	return result;
}

val MeshWrapper::fromTrianglesImplWithArray( const val& verticesArray, const val& indicesArray )
{
	val result = val::object();

	try
	{
		if ( !verticesArray.instanceof( val::global( "Float32Array" ) ) )
		{
			throw std::runtime_error( "vertices must be Float32Array" );
		}
		if ( !indicesArray.instanceof( val::global( "Uint32Array" ) ) )
		{
			throw std::runtime_error( "indices must be Uint32Array" );
		}

		int verticesLength = verticesArray["length"].as<int>();
		int indicesLength = indicesArray["length"].as<int>();

		if ( verticesLength % 3 != 0 )
		{
			throw std::runtime_error( "vertices array length must be divisible by 3" );
		}
		if ( indicesLength % 3 != 0 )
		{
			throw std::runtime_error( "indices array length must be divisible by 3" );
		}

		int numVerts = verticesLength / 3;
		int numTris = indicesLength / 3;

        // NOTE: Using `emscripten::convertJSArrayToNumberVector`, a safer way to obtain data from a `TypedArray`
		std::vector<float> verticesVec = emscripten::convertJSArrayToNumberVector<float>( verticesArray );
		std::vector<uint32_t> indicesVec = emscripten::convertJSArrayToNumberVector<uint32_t>( indicesArray );
		const float* verticesPtr = verticesVec.data();
		const uint32_t* indicesPtr = indicesVec.data();

		///
		VertCoords vCoords;
		vCoords.resize( numVerts );

		// Read vertex data from vector (memory contiguous, high performance)
		for ( int i = 0; i < numVerts; ++i )
		{
			int baseIdx = i * 3;
			vCoords[VertId( i )] = Vector3f(
				verticesPtr[baseIdx],
				verticesPtr[baseIdx + 1],
				verticesPtr[baseIdx + 2]
			);
		}
		///

		///
		Triangulation triangulation;
		triangulation.resize( numTris );

		for ( int i = 0; i < numTris; ++i )
		{
			int baseIdx = i * 3;
			triangulation[FaceId( i )] = ThreeVertIds{
				VertId( indicesPtr[baseIdx] ),
				VertId( indicesPtr[baseIdx + 1] ),
				VertId( indicesPtr[baseIdx + 2] )
			};
		}
		///

		auto mesh = Mesh::fromTriangles( std::move( vCoords ), triangulation );

		result.set( "success", true );
		result.set( "mesh", MeshWrapper( mesh ) );
	}
	catch ( const std::exception& e )
	{
		result.set( "success", false );
		result.set( "error", std::string( e.what() ) );
	}

	return result;
}

val MeshWrapper::getBoundingBoxImpl() const
{
	return MRJS::box3fToObject( mesh.getBoundingBox() );
}

val MeshWrapper::getVertexPositionImpl( int vertId ) const
{
	if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
	{
		return MRJS::vector3fToArray( mesh.points[VertId( vertId )] );
	}
	return val::null();
}

void MeshWrapper::setVertexPositionImpl( int vertId, const val& position )
{
	if ( vertId >= 0 && vertId < ( int )mesh.points.size() )
	{
		mesh.points[VertId( vertId )] = MRJS::arrayToVector3f( position );
		mesh.invalidateCaches(); // IMPORTANT: invalidate caches after modification
	}
}

int MeshWrapper::getVertexCountImpl() const
{
	return ( int )mesh.topology.lastValidVert() + 1;
}

int MeshWrapper::getFaceCountImpl() const
{
	return ( int )mesh.topology.lastValidFace() + 1;
}

double MeshWrapper::getVolumeImpl() const
{
	return mesh.volume();
}

double MeshWrapper::getAreaImpl() const
{
	return mesh.area();
}

val MeshWrapper::findCenterImpl() const
{
	return MRJS::vector3fToArray( mesh.findCenterFromBBox() );
}

val MeshWrapper::getFaceVerticesImpl( int faceId ) const
{
	if ( faceId >= 0 && faceId < ( int )mesh.topology.lastValidFace() + 1 )
	{
		FaceId f( faceId );
		if ( mesh.topology.hasFace( f ) )
		{
			val result = val::array();
			EdgeId e = mesh.topology.edgeWithLeft( f );

			for ( int i = 0; i < 3; ++i )
			{
				// Assuming triangular faces
				result.set( i, ( int )mesh.topology.org( e ) );
				e = mesh.topology.next( e );
			}
			return result;
		}
	}
	return val::null();
}

val MeshWrapper::getFaceNormalImpl( int faceId ) const
{
	if ( faceId >= 0 && faceId < ( int )mesh.topology.lastValidFace() + 1 )
	{
		FaceId f( faceId );
		if ( mesh.topology.hasFace( f ) )
		{
			return MRJS::vector3fToArray( mesh.normal( f ) );
		}
	}
	return val::null();
}

val MeshWrapper::segmentByPointsImpl(
	const std::vector<float>& coordinates, const std::vector<float>& dir,
	const EdgeMetricWrapper& edgeMetricWrapper )
{
	val result = val::object();

	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	if ( meshCopy.points.empty() )
	{
		result.set( "success", false );
		result.set( "error", std::string( "Mesh not initialized!" ) );

		return result;
	}

	try
	{
		auto edgeMetric_ = edgeMetricWrapper.getMetric();
		std::vector<Vector3f> inputPoints = MRJS::parseJSCoordinates( coordinates );

		if ( inputPoints.size() < 2 )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Segmenting mesh needs exactly 2 or 3 input points!" ) );

			return result;
		}

		// Step 1: Find closest vertices on the mesh for each input point using `findProjection()`
		std::vector<VertId> keyVertices;
		keyVertices.reserve( inputPoints.size() );

		MeshPart m = MeshPart( meshCopy );

		meshCopy.getAABBTree();
		for ( const Vector3f& point : inputPoints )
		{
			MeshProjectionResult closestVert = findProjection( point, m );
			if ( !closestVert.valid() )
			{
				result.set( "success", false );
				result.set( "error", std::string( "Could not find valid vertex for input point" ) );

				return result;
			}
			keyVertices.push_back( meshCopy.getClosestVertex( closestVert.proj ) );
		}

		// Step 2: Use the direction provided by JavaScript
		Vector3f contourDirection( dir[0], dir[1], dir[2] );

		// Normalize the direction vector to ensure it's a unit vector
		float dirLength = contourDirection.length();
		if ( dirLength < 1e-6f )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Direction vector is too small or zero" ) );

			return result;
		}
		contourDirection /= dirLength;

		// Step 3: Create surrounding contour
		auto contourResult = surroundingContour( meshCopy, keyVertices, edgeMetric_, contourDirection );

		if ( !contourResult )
		{
			result.set( "success", false );
			result.set( "error", std::string( "Failed to create surrounding contour: " ) + contourResult.error() );

			return result;
		}

		// Step 4: Convert EdgeLoop to EdgePath for `fillContourLeftByGraphCut()`
		EdgeLoop contour = contourResult.value();
		EdgePath contourPath( contour.begin(), contour.end() );

		// Step 5: Fill the contour to get the segmented region
		Mesh segMesh;
		FaceBitSet segmentedFaces = fillContourLeftByGraphCut( meshCopy.topology, contourPath, edgeMetric_ );
		segMesh.addMeshPart( {meshCopy, &segmentedFaces} );

		// Step 6: Convert results to JavaScript-friendly format using emscripten val
		val meshData = MRJS::exportMeshMemoryView( segMesh );

		// Since `EdgeId` has an implicit conversion operator to int, and it is internally represented as an int
		// We can directly reinterpret `EdgeId*` as `int*`
		const int* contourData = reinterpret_cast<const int*>( contour.data() );
		size_t contourSize = contour.size();
		val contourEdgesArray = val( typed_memory_view( contourSize, contourData ) );

		// Build the result object
		result.set( "success", true );
		result.set( "contourEdges", contourEdgesArray );
		result.set( "mesh", meshData );
	}
	catch ( const std::exception& e )
	{
		result.set( "success", false );
		result.set( "error", std::string( "Exception during segmentation: " ) + e.what() );
	}

	return result;
}

val MeshWrapper::thickenMeshImpl( float offset, GeneralOffsetParameters &params )
{
	// Return the mesh wrapped in an object that indicates success
	val returnObj = val::object();

	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	MeshBuilder::uniteCloseVertices( meshCopy, meshCopy.computeBoundingBox().diagonal() * 1e-6 );
	auto result = thickenMesh( mesh, offset, params );
	if ( result )
	{
		Mesh& shell = result.value();

		///

		// // Stitch boundaries 
		// auto holes = shell.topology.findHoleRepresentiveEdges();
		// if ( holes.size() != 2 )
		// {
		// 	returnObj.set( "success", false );

		// 	std::string errorMessage = "Expected 2 holes, found " + std::to_string( holes.size() ) + "\n";
		// 	returnObj.set( "error: ", errorMessage );
		// 	return returnObj;
		// }

		///

		// Find boundary holes
		auto holes = findRightBoundary( shell.topology );
		std::vector<float> holesLength( holes.size() );
		std::vector<Vector3f> holeCenters( holes.size() );

		for ( size_t i = 0; i < holes.size(); ++i )
		{
			float length = 0.0f;
			Vector3f center;
			for ( EdgeId e : holes[i] )
			{
				auto org = shell.topology.org( e );
				auto dest = shell.topology.dest( e );
				length += ( shell.points[dest] - shell.points[org] ).length();
				center += shell.points[org];
			}
			holesLength[i] = length;
			holeCenters[i] = center / float( holes[i].size() );
		}

		// Find largest two holes
		int maxLengthI = 0, maxLengthI2 = -1;
		float maxLength = -1.0f;
		for ( int i = 0; i < holesLength.size(); ++i )
		{
			if ( holesLength[i] > maxLength )
			{
				maxLength = holesLength[i];
				maxLengthI = i;
			}
		}

		maxLength = -1.0f;
		for ( int i = 0; i < holesLength.size(); ++i )
		{
			if ( i != maxLengthI && holesLength[i] > maxLength )
			{
				maxLength = holesLength[i];
				maxLengthI2 = i;
			}
		}

		// Build hole pairs
		std::vector<std::array<int, 2>> holePairs;
		if ( maxLengthI2 != -1 )
			holePairs.push_back( { maxLengthI, maxLengthI2 } );

		// Find nearest pairs for remaining holes
		std::vector<int> minDistancesI( holes.size(), -1 );
		for ( int i = 0; i < holes.size(); ++i )
		{
			if ( i == maxLengthI || i == maxLengthI2 )
				continue;

			float minDist = std::numeric_limits<float>::max();
			int minJ = -1;

			for ( int j = 0; j < holes.size(); ++j )
			{
				if ( j == i || j == maxLengthI || j == maxLengthI2 )
					continue;

				float dist = ( holeCenters[i] - holeCenters[j] ).length();
				if ( dist < minDist )
				{
					minDist = dist;
					minJ = j;
				}
			}
			minDistancesI[i] = minJ;
		}

		for ( int i = 0; i < holes.size() / 2; ++i )
		{
			if ( minDistancesI[i] != -1 )
				holePairs.push_back( { i, minDistancesI[i] } );
		}

		// Stitch holes with cylinders
		FaceBitSet newFaces;
		StitchHolesParams stitchParams;
		stitchParams.metric = getMinAreaMetric( shell );
		stitchParams.outNewFaces = &newFaces;

		for ( const auto& pair : holePairs )
		{
			if ( pair[0] < holes.size() && pair[1] < holes.size() )
			{
				if ( !holes[pair[0]].empty() && !holes[pair[1]].empty() )
					buildCylinderBetweenTwoHoles( shell, holes[pair[0]][0], holes[pair[1]][0], stitchParams );
			}
		}

		// Subdivide new faces
		SubdivideSettings subdivSettings;
		subdivSettings.region = &newFaces;
		subdivSettings.maxEdgeSplits = INT_MAX;
		subdivSettings.maxEdgeLen = 1.0f;

		subdivideMesh( shell, subdivSettings );

		// Smooth vertices
		auto smoothVerts = getInnerVerts( shell.topology, newFaces );
		positionVertsSmoothly( shell, smoothVerts );


		val meshData = MRJS::exportMeshMemoryView( shell );

		returnObj.set( "success", true );
		returnObj.set( "mesh", meshData );

		return returnObj;
	}
	else
	{
		// Return an error object with the error message
		val returnObj = val::object();
		returnObj.set( "success", false );
		returnObj.set( "error", result.error() );

		return returnObj;
	}
}

val MeshWrapper::cutMeshWithPolylineImpl( const std::vector<float>& coordinates )
{
	std::vector<Vector3f> polyline;

    int coordinatesLength = coordinates.size();
    if (coordinatesLength % 3 != 0) {
		val obj = val::object();
		obj.set( "success", false );
		obj.set( "error", "Coordinates length must be a multiple of 3!" );

		return obj;
    }

	polyline.reserve( coordinatesLength / 3 );

	for ( size_t i = 0; i < coordinatesLength; i += 3 )
	{
		polyline.emplace_back( coordinates[i], coordinates[i + 1], coordinates[i + 2] );
	}
	Polyline3 initialPolyline;
	initialPolyline.addFromPoints( polyline.data(), polyline.size() );

	std::vector<MeshTriPoint> projectedPolyline;
	projectedPolyline.reserve( initialPolyline.points.size() );
	MeshPart m = MeshPart( mesh, nullptr );


	val jsTestProjectedPoint = val::array();

	mesh.getAABBTree(); // Create tree in parallel before loop
	for ( Vector3f pt : initialPolyline.points )
	{
		MeshProjectionResult mpr = findProjection( pt, m );
		projectedPolyline.push_back( mpr.mtp );


		val projPoint = val::object();
		projPoint.set("x", mpr.proj.point.x);
		projPoint.set("y", mpr.proj.point.y);
		projPoint.set("z", mpr.proj.point.z);
		jsTestProjectedPoint.call<void>("push", projPoint);
	}

	auto meshContour = convertMeshTriPointsToMeshContour( mesh, projectedPolyline );
	if ( meshContour )
	{
    	const MR::OneMeshContour& testContour = *meshContour;
		val jsTestProjectedContour = val::array();
		for (const auto& intersection : testContour.intersections)
		{
			val point = val::object();
			point.set("x", intersection.coordinate.x);
			point.set("y", intersection.coordinate.y);
			point.set("z", intersection.coordinate.z);
			jsTestProjectedContour.call<void>("push", point);
		}


		CutMeshResult cutResults = cutMesh( mesh, { *meshContour } );


		val jsTestCutPoints = val::array();
		for (const auto& loop : cutResults.resultCut) {
			for (const auto& edge : loop) {
				Vector3f p = mesh.orgPnt(edge);
				val point = val::object();
				point.set("x", p.x);
				point.set("y", p.y);
				point.set("z", p.z);
				jsTestCutPoints.call<void>("push", point);
			}
		}
		

		auto [innerMesh, outerMesh] = MRJS::returnParts( mesh, cutResults.resultCut );
		val innerMeshData = MRJS::exportMeshMemoryView( innerMesh );
		val outerMeshData = MRJS::exportMeshMemoryView( outerMesh );


		val obj = val::object();
		obj.set( "success", true );
		obj.set( "innerMesh", innerMeshData );
		obj.set( "outerMesh", outerMeshData );
		obj.set( "jsTestProjectedPoint", jsTestProjectedPoint );
		obj.set( "jsTestProjectedContour", jsTestProjectedContour );
		obj.set( "jsTestCutPoints", jsTestCutPoints );

		return obj;
	} else {
		std::string error = meshContour.error();

		val obj = val::object();
		obj.set( "success", false );
		obj.set( "error", "convertMeshTriPointsToMeshContour: " + error );
	
		return obj;
	}
}

val MeshWrapper::fixUndercutsImpl( const Vector3f& upDirection ) const
{
	val returnObj = val::object();

	FixUndercuts::FixParams fixParams;
	fixParams.findParameters.upDirection = upDirection.normalized();

	Mesh meshCopy;
	// NOTE: Both methods will work
	// meshCopy = mesh;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;
	
	auto result = FixUndercuts::fix( meshCopy, fixParams );

	val meshData = MRJS::exportMeshMemoryView( meshCopy );
	returnObj.set( "success", true );
	returnObj.set( "mesh", meshData );
	returnObj.set( "message", "Undercuts fixed successfully!" );

    return returnObj;
}

val MeshWrapper::fillHolesImpl() const
{
	auto holeEdges = mesh.topology.findHoleRepresentiveEdges();

	Mesh meshCopy;
	meshCopy.topology = mesh.topology;
	meshCopy.points = mesh.points;

	for ( EdgeId e : holeEdges )
	{
		FillHoleParams params;
		fillHole( meshCopy, e, params );
	}

    return MRJS::exportMeshMemoryView( meshCopy );
}

// Point projection
val MeshWrapper::projectPointImpl( const val& point, float maxDistance ) const
{
	Vector3f p = MRJS::arrayToVector3f( point );
	MeshProjectionResult result = mesh.projectPoint( p, maxDistance * maxDistance ); // Note: function expects squared distance

	if ( result.valid() )
	{
		val obj = val::object();
		obj.set( "success", true );
		// obj.set( "point", MRJS::vector3fToArray( result.proj ) );
		// obj.set( "faceId", ( int )result->face );
		// obj.set( "distance", std::sqrt( result->distSq ) );
		return obj;
	}
	else
	{
		val result = val::object();
		result.set( "success", false );
		result.set( "error", "No projection found within distance" );

		return result;
	}
}


// ------------------------------------------------------------------------
// Bindings for `MeshWrapper`
// ------------------------------------------------------------------------
EMSCRIPTEN_BINDINGS( MeshWrapperModule )
{
	class_<MeshWrapper>( "MeshWrapper" )
		.smart_ptr<std::shared_ptr<MeshWrapper>>( "MeshWrapperSharedPtr" )

		.constructor<>()
		.constructor<const Mesh&>()
		.class_function( "fromTrianglesImpl", &MeshWrapper::fromTrianglesImpl )
		.class_function( "fromTrianglesImplWithArray", &MeshWrapper::fromTrianglesImplWithArray )

		.property( "mesh", &MeshWrapper::mesh, return_value_policy::reference() )
		.function( "getMesh", &MeshWrapper::getMesh )
		.function( "getMeshPtr", &MeshWrapper::getMeshPtr, allow_raw_pointers() )

		// Geometric properties
		.function( "getBoundingBoxImpl", &MeshWrapper::getBoundingBoxImpl )
		.function( "getVertexCountImpl", &MeshWrapper::getVertexCountImpl )
		.function( "getFaceCountImpl", &MeshWrapper::getFaceCountImpl )
		.function( "getVolumeImpl", &MeshWrapper::getVolumeImpl )
		.function( "getAreaImpl", &MeshWrapper::getAreaImpl )
		.function( "findCenterImpl", &MeshWrapper::findCenterImpl )
		.function( "getVertexPositionImpl", &MeshWrapper::getVertexPositionImpl )
		.function( "setVertexPositionImpl", &MeshWrapper::setVertexPositionImpl )
		.function( "getFaceVerticesImpl", &MeshWrapper::getFaceVerticesImpl )
		.function( "getFaceNormalImpl", &MeshWrapper::getFaceNormalImpl )

		.function( "thickenMeshImpl", &MeshWrapper::thickenMeshImpl )
		.function( "cutMeshWithPolylineImpl", &MeshWrapper::cutMeshWithPolylineImpl )
		.function( "segmentByPointsImpl", &MeshWrapper::segmentByPointsImpl )
		.function( "fixUndercutsImpl", &MeshWrapper::fixUndercutsImpl )
		.function( "fillHolesImpl", &MeshWrapper::fillHolesImpl )

		// Spatial queries
		.function( "projectPointImpl", &MeshWrapper::projectPointImpl );
}

} //namespace MRJS
