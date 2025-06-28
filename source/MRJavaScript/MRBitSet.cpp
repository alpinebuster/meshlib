#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRBitSet.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( BisSetModule )
{
    class_<FaceBitSet>( "FaceBitSet" )
        .constructor<>();
        
    class_<VertBitSet>( "VertBitSet" )
        .constructor<>();
        
    class_<EdgeBitSet>( "EdgeBitSet" )
        .constructor<>();
        
    class_<UndirectedEdgeBitSet>( "UndirectedEdgeBitSet" )
        .constructor<>();
        
    class_<PixelBitSet>( "PixelBitSet" )
        .constructor<>();
        
    class_<VoxelBitSet>( "VoxelBitSet" )
        .constructor<>();
        
    class_<RegionBitSet>( "RegionBitSet" )
        .constructor<>();
        
    class_<NodeBitSet>( "NodeBitSet" )
        .constructor<>();
        
    class_<ObjBitSet>( "ObjBitSet" )
        .constructor<>();
        
    class_<TextureBitSet>( "TextureBitSet" )
        .constructor<>();
        
    class_<GraphVertBitSet>( "GraphVertBitSet" )
        .constructor<>();
        
    class_<GraphEdgeBitSet>( "GraphEdgeBitSet" )
        .constructor<>();
}
