#pragma once

#include <utility>
#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRUnionFind.h>

using namespace emscripten;
using namespace MR;


template<typename IdType>
auto bindTypedUnionFind( const std::string& className ) {
    auto cls = class_<UnionFind<IdType>>( className.c_str() )
        .template constructor<>()
        .template constructor<size_t>()

        .function( "size", &UnionFind<IdType>::size )
        .function( "reset", &UnionFind<IdType>::reset )
        .function( "unite", &UnionFind<IdType>::unite )
        .function( "united", &UnionFind<IdType>::united )
        .function( "isRoot", &UnionFind<IdType>::isRoot )
        .function( "parent", &UnionFind<IdType>::parent )
        .function( "find", &UnionFind<IdType>::find )
        .function( "findUpdateRange", &UnionFind<IdType>::findUpdateRange )
        .function( "roots", &UnionFind<IdType>::roots )
        .function( "parents", &UnionFind<IdType>::parents )
        .function( "sizeOfComp", &UnionFind<IdType>::sizeOfComp );
    
    return cls;
}
