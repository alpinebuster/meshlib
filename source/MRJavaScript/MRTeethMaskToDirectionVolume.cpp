#include <optional>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVolumeIndexer.h>
#include <MRMesh/MRPointsToMeshProjector.h>

#include <MRVoxels/MRVDBConversions.h>
#include <MRVoxels/MRMeshToDistanceVolume.h>
#include <MRVoxels/MRTeethMaskToDirectionVolume.h>

using namespace emscripten;
using namespace MR;


EMSCRIPTEN_BINDINGS( TeethMaskToDirectionVolumeModule )
{
	class_<DentalId>( "DentalId" )
		.class_function( "creatFromFDI", select_overload<std::optional<DentalId>( int )>( &DentalId::fromFDI ) )

		.function( "fdi", &DentalId::fdi )

		.function( "equals", optional_override( [] ( const DentalId& a, const DentalId& b ) -> bool
		{
			return a == b;
		} ) )
		.function( "lessThan", optional_override( [] ( const DentalId& a, const DentalId& b ) -> bool
		{
			return a < b;
		} ) )
		.function( "greaterThan", optional_override( [] ( const DentalId& a, const DentalId& b ) -> bool
		{
			return a > b;
		} ) )
		
		.function( "hash", optional_override( [] ( const DentalId& id ) -> size_t
		{
			return std::hash<DentalId>{}( id );
		} ) )
		.function( "toString", optional_override( [] ( const DentalId& id ) -> std::string
		{
			return std::to_string( id.fdi() );
		} ) );
}
