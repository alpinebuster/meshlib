#pragma once

#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshTopology.h>

using namespace emscripten;
using namespace MR;

namespace MRJS {

// Helper function to export mesh data using typed_memory_view
inline auto exportMeshData = []( const Mesh& meshToExport ) -> val {
    // === Export point data ===
    auto _points = meshToExport.points;
    size_t pointCount = _points.size();
    size_t totalPointElements = pointCount * 3;
    const float* pointData = reinterpret_cast<const float*>( _points.data() );

    // Use typed_memory_view for vertices
    val pointsArray = val( typed_memory_view(
        totalPointElements, 
        pointData
    ) );

    // === Export triangle data ===
    Triangulation _tri = meshToExport.topology.getTriangulation();
    size_t triangleCount = _tri.size();
    size_t totalTriElements = triangleCount * 3; // Each triangle has three indexes
    const int* triData = reinterpret_cast<const int*>( _tri.data() );

    // Use typed_memory_view for triangles
    val triangleArray = val( typed_memory_view(
        totalTriElements, 
        triData
    ) );
    
    val meshData = val::object();
    meshData.set( "vertices", pointsArray );
    meshData.set( "vertexCount", pointCount );
    meshData.set( "indices", triangleArray );
    meshData.set( "triangleCount", triangleCount );

    return meshData;
};


// Impl：Automatically registering elements `0, 1, …, N − 1` at compile time
template<typename T, std::size_t... Is>
void bindStdArrayImpl( const char* jsName, std::index_sequence<Is...> ) {
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
void bindStdArray( const char* jsName ) {
    bindStdArrayImpl<T>( jsName, std::make_index_sequence<N>{} );
}


template<typename OptionalType>
struct OptionalAccess {
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
        .function( "hasValue", &OptionalAccess<OptionalV>::has_value );
}

} // namespace MRUtil
