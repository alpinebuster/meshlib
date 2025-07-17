#pragma once

#include <optional>
#include <type_traits>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MREdgePaths.h>

using namespace emscripten;
using namespace MR;


namespace MRJS
{


// Helper function to create Vector3f from JavaScript array
Vector3f arrayToVector3f( const val& arr );

// Helper function to convert Vector3f to JavaScript array
val vector3fToArray( const Vector3f& v );

// Helper function to convert Box3F to JavaScript object
val box3fToObject( const Box<Vector3<float>>& box );

// Helper function to convert Expected<T> to JavaScript-friendly result
template<typename T>
val expectedToJs( const Expected<T>& expected );

// Convert C++ vector to JavaScript `Float32Array`
// REF: [Memory Views](`https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#memory-views`)
[[nodiscard]] val vector3fToFloat32Array( const std::vector<Vector3f>& vec );

/**
 * @brief Helper function to convert flat coordinate array to Vector3f points
 * This design is more JavaScript-friendly than individual Point3D objects
 * coordinates should contain [x1,y1,z1, x2,y2,z2, x3,y3,z3, ...] for each point
 */
[[nodiscard]] std::vector<Vector3f> parseJSCoordinates( const std::vector<float>& coordinates );

std::pair<Mesh, Mesh> returnParts( const Mesh& mesh, const std::vector<EdgePath>& cut );

// NOTE: Export mesh data using `typed_memory_view()`
// 
//  unsigned char*  -> Uint8Array
//  char*	        -> Int8Array
//  unsigned short*	-> Uint16Array
//  short*	        -> Int16Array
//  unsigned int*	-> Uint32Array
//  int*	        -> Int32Array
//  float*	        -> Float32Array
//  double*	        -> Float64Array
// 
inline auto exportMeshMemoryView = [] ( const Mesh& meshToExport ) -> val
{
    // === Export point data ===
    const auto& points_ = meshToExport.points;
    size_t pointCount = points_.size();
    size_t vertexElementCount = pointCount * 3;
    const float* pointDataPtr = reinterpret_cast<const float*>( points_.data() );

    // Use `typed_memory_view()` for vertices
    val pointsArray = val( typed_memory_view(
        vertexElementCount, 
        pointDataPtr
    ) );

    // === Export triangle data ===
    const auto& tris_ = meshToExport.topology.getTriangulation();
    size_t triangleCount = tris_.size();
    size_t triElementCount = triangleCount * 3;
    // NOTE:
    // 
    //  uint32_t*   	-> Uint32Array, we need `Uint32Array` for threejs
    //  int*	        -> Int32Array
    // 
    const uint32_t* triDataPtr = reinterpret_cast<const uint32_t*>( tris_.data() );

    /// NOTE: V3 - Working & Faster than V1
    val triangleArray = val::global( "Uint32Array" ).new_( triElementCount );
    val triangleView_ = val( typed_memory_view( triElementCount, triDataPtr ) ); // Use `typed_memory_view()` for triangles
    triangleArray.call<void>( "set", triangleView_ );
    ///

    /// NOTE: V2 - NOT WORKING:
    // This will return corrupted indices because the `tris_` returned by `getTriangulation()` must be copied
    // While the vertices returned by `meshToExport.points` will live long enough to be called by JS side.
    // 
    // val triangleArray = val( typed_memory_view(
    //     triElementCount,
    //     triDataPtr
    // ) );
    ///

    /// NOTE: V1 - Working
    // TODO: Use `ParallelFor` to optimize this?
    // 
    // val triangleArray = val::array();
    // triangleArray.set("length", triElementCount);
	// for (size_t i = 0; i < triElementCount; ++i) {
	// 	triangleArray.set(i, val(triDataPtr[i]));
	// }
    ///

    val meshData = val::object();
    meshData.set( "vertices", pointsArray );
    meshData.set( "vertexElementCount", vertexElementCount );
    meshData.set( "vertexCount", pointCount );
    meshData.set( "indices", triangleArray );
    meshData.set( "indexElementCount", triElementCount );
    meshData.set( "indexCount", triangleCount );
    // meshData.set( "sizeofThreeVertIds", sizeof( ThreeVertIds ) );
    // meshData.set( "sizeofUInt32", sizeof( uint32_t ) * 3 );

    return meshData;
};
inline auto exportMeshData = []( const Mesh& meshToExport ) -> val {
    // === Export point data ===
    const auto& points_ = meshToExport.points;
    size_t pointCount = points_.size();
    size_t vertexElementCount = pointCount * 3;
    const float* pointDataPtr = reinterpret_cast<const float*>( points_.data() );

    val pointsArray = val::array();
    // Pre-allocate the array length to improve performance
    pointsArray.set("length", vertexElementCount);
    // Batch setting values - faster than pushing them one by one
    for (size_t i = 0; i < vertexElementCount; ++i) {
        pointsArray.set(i, val(pointDataPtr[i]));
    }

    // === Export triangle data ===
    const auto& tris_ = meshToExport.topology.getTriangulation();
    size_t triangleCount = tris_.size();
    size_t indexElementCount = triangleCount * 3; // Each triangle has 3 indexes
    const int* triDataPtr = reinterpret_cast<const int*>( tris_.data() );

	val triangleArray = val::array();
    triangleArray.set("length", indexElementCount);
	for (size_t i = 0; i < indexElementCount; ++i) {
		triangleArray.set(i, val(triDataPtr[i]));
	}

    val meshData = val::object();
    meshData.set( "vertices", pointsArray );
    meshData.set( "vertexElementCount", val(vertexElementCount) );
    meshData.set( "vertexCount", val( pointCount ) );
    meshData.set( "indices", triangleArray );
    meshData.set( "indexElementCount", val(indexElementCount) );
    meshData.set( "indexCount", triangleCount );

    return meshData;
};


// Impl：Automatically registering elements `0, 1, …, N − 1` at compile time
template<typename T, std::size_t... Is>
void bindStdArrayImpl( const char* jsName, std::index_sequence<Is...> )
{
    // 1) `sizeof...(Is)` is the number of integers in the pack—that is, `N`.
    // 
    // Therefore:
    //   `value_array<std::array<T, sizeof...(Is)>>( jsName )`
    // is equivalent to
    //   `value_array<std::array<T, N>>( jsName )`
    // 
    auto arr = value_array<std::array<T, sizeof...( Is )>>( jsName );
    // 2) This is a common trick combining pack-expansion, the comma operator, and an initializer list. The effect is to invoke:
    // 
    //   arr.element( emscripten::index<0>() );
    //   arr.element( emscripten::index<1>() );
    //   …
    //   arr.element( emscripten::index<N-1>() );
    // 
    // all at compile time
    // 
    ( void )std::initializer_list<int>{ ( arr.element( emscripten::index<Is>() ), 0 )... };
}
/**
 *@brief Just specify `T`, `N`, and the `jsName`.
 * The compiler generates the index sequence `0…N-1` and calls `bindStdArrayImpl`, which in turn registers every element.
 *
 * @tparam T 
 * @tparam N 
 * @param jsName 
 */
template<typename T, std::size_t N>
void bindStdArray( const char* jsName )
{
    bindStdArrayImpl<T>( jsName, std::make_index_sequence<N>{} );
}

} // namespace MRUtil
