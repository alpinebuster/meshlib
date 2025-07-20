#include <array>
#include <memory>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRAABBTree.h>
#include <MRMesh/MRFaceFace.h>
#include <MRMesh/MRMeshCollidePrecise.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MeshCollidePreciseModule )
{
    class_<EdgeTri>( "EdgeTri" )
        .constructor<>()
        .constructor<EdgeId, FaceId>()
        .property( "edge", &EdgeTri::edge )
        .property( "tri", &EdgeTri::tri );


    using FlaggedTri_ = VarEdgeTri::FlaggedTri;
    class_<FlaggedTri_>( "FlaggedTri" )
        .constructor<>()

        /// NOTE:
        // 
        // struct MyFlags {
        //     // Total of 1 + 2 + 5 = 8 bits, which is 1 byte 
        //     // ( the actual size is also affected by compiler alignment rules )
        //     unsigned int flagA : 1;  // Use **1 bit** to store `flagA` (can only be 0 or 1)
        //     unsigned int flagB : 2;  // Use **2 bits** to store `flagB` (can store values from 0 to 3)
        //     unsigned int count : 5;  // Use **5 bits** to store `count` (can store values from 0 to 31)
        // };
        // 
        ///
        .function( "getIsEdgeATriB",
            optional_override( []( const FlaggedTri_& f ) {
                // Convert the value of the **bit field** to return a `bool`
                return static_cast<bool>( f.isEdgeATriB );
            })
        )
        .function( "setIsEdgeATriB",
            optional_override( []( FlaggedTri_& f, bool v ) {
                // Receive a `bool` passed from JS and store it in a **bit field**
                f.isEdgeATriB = v ? 1u : 0u;
            })
        )
    
        .function( "getFace",
            optional_override( []( const FlaggedTri_& f ) {
                return static_cast<unsigned int>(f.face);
            })
        )
        .function( "setFace",
            optional_override( []( FlaggedTri_& f, unsigned int v ) {
                f.face = v;
            })
        )

        .function( "equals", optional_override( [] ( const FlaggedTri_& self, const FlaggedTri_& other )
        {
            return self == other;
        } ) );
        

    class_<VarEdgeTri>( "VarEdgeTri" )
        .constructor<>()
        .constructor<bool, EdgeId, FaceId>()
        .constructor<bool, const EdgeTri&>()

        .property( "edge", &VarEdgeTri::edge )
        .property( "flaggedTri", &VarEdgeTri::flaggedTri )
    
        .function( "tri", &VarEdgeTri::tri )
        .function( "isEdgeATriB", &VarEdgeTri::isEdgeATriB )
        .function( "edgeTri", &VarEdgeTri::edgeTri )
        .function( "valid", &VarEdgeTri::valid )
        
        .function( "opbool", select_overload<bool() const>( &VarEdgeTri::operator bool ) )
        .function( "equals", optional_override( [] ( const VarEdgeTri& self, const VarEdgeTri& other )
        {
            return self == other;
        } ) );


    function("findCollidingEdgeTrisPrecise_PartPart",
        select_overload<PreciseCollisionResult(const MeshPart&, const MeshPart&, ConvertToIntVector, const AffineXf3f*, bool)>(
            &findCollidingEdgeTrisPrecise), allow_raw_pointers());

    function("findSelfCollidingEdgeTrisPrecise",
        select_overload<std::vector<EdgeTri>(const MeshPart&, ConvertToIntVector, bool, const AffineXf3f*, int)>(
            &findSelfCollidingEdgeTrisPrecise), allow_raw_pointers());

    function("findCollidingEdgeTrisPrecise_MeshEdges",
        select_overload<std::vector<EdgeTri>(const Mesh&, const std::vector<EdgeId>&, const Mesh&, const std::vector<FaceId>&, ConvertToIntVector, const AffineXf3f*)>(
            &findCollidingEdgeTrisPrecise), allow_raw_pointers());

    function("findCollidingEdgeTrisPrecise_MeshFaces",
        select_overload<std::vector<EdgeTri>(const Mesh&, const std::vector<FaceId>&, const Mesh&, const std::vector<EdgeId>&, ConvertToIntVector, const AffineXf3f*)>(
            &findCollidingEdgeTrisPrecise), allow_raw_pointers());

    function("getVectorConverters_Part",
        select_overload<CoordinateConverters(const MeshPart&)>(&getVectorConverters));
    function("getVectorConverters_Parts",
        select_overload<CoordinateConverters(const MeshPart&, const MeshPart&, const AffineXf3f*)>(
            &getVectorConverters), allow_raw_pointers());
}
