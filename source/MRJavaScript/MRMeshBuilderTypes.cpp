#include <array>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRMeshBuilderTypes.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( MRMeshBuilderTypesModule )
{
	class_<MeshBuilder::Triangle>( "Triangle" )
		.constructor<>()
		.constructor<VertId, VertId, VertId, FaceId>()
	
		.property( "f", &MeshBuilder::Triangle::f )
		.property( "v", &MeshBuilder::Triangle::v )
		
		.function( "equals", optional_override( [] ( const MeshBuilder::Triangle& self, const MeshBuilder::Triangle& other )
		{
			return self.f == other.f && self.v[0] == other.v[0] && self.v[1] == other.v[1] && self.v[2] == other.v[2];
		} ) );


	class_<MeshBuilder::BuildSettings>( "BuildSettings" )
		.constructor<>()
	
		.property( "shiftFaceId", &MeshBuilder::BuildSettings::shiftFaceId )
		.property( "allowNonManifoldEdge", &MeshBuilder::BuildSettings::allowNonManifoldEdge )
	
        .function( "getRegion", optional_override( [] ( MeshBuilder::BuildSettings& self ) -> FaceBitSet*
        {
            return self.region;
        } ), allow_raw_pointers() )

		.function( "setRegion", optional_override( []( MeshBuilder::BuildSettings& self, const FaceBitSet& newV ) -> void {
            delete self.region;  // Clearance of old `self.region`
            self.region = new FaceBitSet(newV);
        } ) )
		.function( "setRegionCopy", optional_override( []( MeshBuilder::BuildSettings& self, const FaceBitSet& newV ) -> void {
            if (self.region) {
                *self.region = newV;  // Copy to an existing `self.region`
            } else {
                self.region = new FaceBitSet(newV);
            }
        } ) )
        .function( "setRegionWithPtr", optional_override( []( MeshBuilder::BuildSettings& self, FaceBitSet* newV ) -> void {
            if ( newV ) self.region = newV;
        } ), allow_raw_pointers() )

		.function( "getSkippedFaceCount", optional_override( [] ( MeshBuilder::BuildSettings& self ) -> int
		{
			if ( !self.skippedFaceCount ) throw std::runtime_error( "skippedFaceCount is null" );
			return *self.skippedFaceCount;
		}))
		.function( "setSkippedFaceCount", optional_override( [] ( MeshBuilder::BuildSettings& self, int v ) -> void
		{
			if ( !self.skippedFaceCount ) self.skippedFaceCount = new int;
			*self.skippedFaceCount = v;
		}));;


	value_object<MeshBuilder::VertSpan>( "VertSpan" )
		.field( "firstVertex", &MeshBuilder::VertSpan::firstVertex )
		.field( "lastVertex", &MeshBuilder::VertSpan::lastVertex );
}
