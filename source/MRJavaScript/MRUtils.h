#pragma once

#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshTopology.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRMeshOrPoints.h>
#include <MRMesh/MRBitSet.h>

using namespace emscripten;
using namespace MR;

namespace MRJS {

/**
 * @brief Helper function to convert flat coordinate array to Vector3f points
 * This design is more JavaScript-friendly than individual Point3D objects
 * coordinates should contain [x1,y1,z1, x2,y2,z2, x3,y3,z3, ...] for each point
 */
[[nodiscard]] std::vector<Vector3f> parseJSCoordinates( const std::vector<float>& coordinates );

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
    size_t indexElementCount = triangleCount * 3;
    //  unsigned int*	-> Uint32Array, we need `Uint32Array` for threejs
    //  int*	        -> Int32Array
    const int* triDataPtr = reinterpret_cast< const int* >( tris_.data() );

    // FIXME: Why this wont work for indices?
    // Use `typed_memory_view()` for triangles
    // val triangleArray = val( typed_memory_view(
    //     indexElementCount, 
    //     // triDataPtr
    //     flatIndices.data()
    // ) );
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


template<typename OptionalType>
struct OptionalAccess
{
    static val value( const OptionalType& v )
    {
        return val( v.value() );
    }
    static bool hasValue( const OptionalType& v )
    {
        return v.has_value();
    }
};
template<typename V>
class_<std::optional<V>> register_optional( const char* name )
{
    using OptionalV = std::optional<V>;
    return class_<OptionalV>( name )
        .constructor<>()
        .function( "value", &OptionalAccess<OptionalV>::value )
        .function( "hasValue", &OptionalAccess<OptionalV>::hasValue );
}

} // namespace MRUtil
