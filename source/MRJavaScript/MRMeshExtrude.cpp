#include <optional>
#include <memory>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

struct MakeDegenerateBandAroundRegionParamsWrapper {
    std::shared_ptr<FaceBitSet> outNewFaces;
    std::shared_ptr<UndirectedEdgeBitSet> outExtrudedEdges;
    std::shared_ptr<VertHashMap> new2OldMap;
    std::optional<float> maxEdgeLength; // Modern and safe!

    void setMaxEdgeLength(float val) { maxEdgeLength = val; }
    std::optional<float> getMaxEdgeLength() const { return maxEdgeLength; }
    void clearMaxEdgeLength() { maxEdgeLength.reset(); }

    void setOutNewFaces(std::shared_ptr<FaceBitSet> ptr) { outNewFaces = std::move(ptr); }
    std::shared_ptr<FaceBitSet> getOutNewFaces() const { return outNewFaces; }

    void setOutExtrudedEdges(std::shared_ptr<UndirectedEdgeBitSet> ptr) { outExtrudedEdges = std::move(ptr); }
    std::shared_ptr<UndirectedEdgeBitSet> getOutExtrudedEdges() const { return outExtrudedEdges; }

    void setNew2OldMap(std::shared_ptr<VertHashMap> ptr) { new2OldMap = std::move(ptr); }
    std::shared_ptr<VertHashMap> getNew2OldMap() const { return new2OldMap; }
};


class FaceHashMapWrapper {
public:
	void set( FaceId key, FaceId value )
	{
		map_[key] = value;
	}
	FaceId get( FaceId key ) const
	{
		return map_.at( key );
	}
	bool has( FaceId key ) const
	{
		return map_.find( key ) != map_.end();
	}

private:
	FaceHashMap map_;
};


/// TODO: V2
/// Used to prevent BindingError (to make Emscripten happy :))
/// 
EMSCRIPTEN_BINDINGS( __phmapInternalModule ) {
    using K = VertId;
    using V = VertId;

    using Hash = phmap::priv::hash_default_hash<K>;
    using Eq = phmap::priv::hash_default_eq<K>;

    using Policy = phmap::priv::FlatHashMapPolicy<K, V>;
    using RawHashSet = phmap::priv::raw_hash_set<
        Policy, Hash, Eq, std::allocator<std::pair<const K, V>>
    >;
    using RawHashMap = phmap::priv::raw_hash_map<
        Policy, Hash, Eq, std::allocator<std::pair<const K, V>>
    >;

    class_<Policy>("__phmap_internal_FlatHashMapPolicy_VertId");
    class_<RawHashSet>("__phmap_internal_raw_hash_set_VertId");
    class_<RawHashMap>("__phmap_internal_raw_hash_map_VertId");
}

EMSCRIPTEN_BINDINGS( HashMapBindings )
{
	class_<FaceHashMapWrapper>( "FaceHashMapWrapper" )
		.constructor<>()
		.function( "set", &FaceHashMapWrapper::set )
		.function( "get", &FaceHashMapWrapper::get )
		.function( "has", &FaceHashMapWrapper::has );
	
	class_<VertHashMap>( "VertHashMap" )
		.constructor<>()
        .smart_ptr<std::shared_ptr<VertHashMap>>( "shared_ptr<VertHashMap>" ) 

		.function( "size", &VertHashMap::size )
		.function( "insert", optional_override( [] ( VertHashMap& self, const VertId& key, const VertId& value )
		{
			self.insert( { key, value } );
		} ) )
		.function( "get", optional_override( [] ( const VertHashMap& self, const VertId& key ) -> val
		{
			auto it = self.find( key );
			if ( it != self.end() )
			{
				return val( it->second );
			}
			else
			{
				return val::undefined();
			}
		} ) )
		.function( "has", optional_override( [] ( const VertHashMap& self, const VertId& key ) -> bool
		{
			return self.find( key ) != self.end();
		} ) )
		.function( "erase", optional_override( [] ( VertHashMap& self, const VertId& key )
		{
			self.erase( key );
		} ) )
		.function( "clear", &VertHashMap::clear )
		.function( "keys", optional_override( [] ( const VertHashMap& self ) -> std::vector<VertId>
		{
			std::vector<VertId> keys;
			for ( const auto& pair : self )
			{
				keys.push_back( pair.first );
			}

			return keys;
		} ) )
		.function( "values", optional_override( [] ( const VertHashMap& self ) -> std::vector<VertId>
		{
			std::vector<VertId> values;
			for ( const auto& pair : self )
			{
				values.push_back( pair.second );
			}
			
			return values;
		} ) );

	class_<FaceHashMap>( "FaceHashMap" )
		.constructor<>()
        .smart_ptr<std::shared_ptr<FaceHashMap>>( "shared_ptr<FaceHashMap>" ) ;

	class_<EdgeHashMap>( "EdgeHashMap" )
		.constructor<>()
        .smart_ptr<std::shared_ptr<EdgeHashMap>>( "shared_ptr<EdgeHashMap>" ) ;

	class_<UndirectedEdgeHashMap>( "UndirectedEdgeHashMap" )
		.constructor<>()
        .smart_ptr<std::shared_ptr<UndirectedEdgeHashMap>>( "shared_ptr<UndirectedEdgeHashMap>" ) ;

	class_<WholeEdgeHashMap>( "WholeEdgeHashMap" )
		.constructor<>()
        .smart_ptr<std::shared_ptr<WholeEdgeHashMap>>( "shared_ptr<WholeEdgeHashMap>" ) ;
}

EMSCRIPTEN_BINDINGS( MeshFillHoleModule )
{
    class_<MakeDegenerateBandAroundRegionParamsWrapper>( "MakeDegenerateBandAroundRegionParamsWrapper" )
        .constructor<>()

        .function("setMaxEdgeLength", &MakeDegenerateBandAroundRegionParamsWrapper::setMaxEdgeLength)
        .function("getMaxEdgeLength", &MakeDegenerateBandAroundRegionParamsWrapper::getMaxEdgeLength)
        .function("clearMaxEdgeLength", &MakeDegenerateBandAroundRegionParamsWrapper::clearMaxEdgeLength)

        .function("setOutNewFaces", &MakeDegenerateBandAroundRegionParamsWrapper::setOutNewFaces)
        .function("getOutNewFaces", &MakeDegenerateBandAroundRegionParamsWrapper::getOutNewFaces)

        .function("setOutExtrudedEdges", &MakeDegenerateBandAroundRegionParamsWrapper::setOutExtrudedEdges)
        .function("getOutExtrudedEdges", &MakeDegenerateBandAroundRegionParamsWrapper::getOutExtrudedEdges)

        .function("setNew2OldMap", &MakeDegenerateBandAroundRegionParamsWrapper::setNew2OldMap)
        .function("getNew2OldMap", &MakeDegenerateBandAroundRegionParamsWrapper::getNew2OldMap);


	class_<MakeDegenerateBandAroundRegionParams>( "MakeDegenerateBandAroundRegionParams" )
		.constructor<>()
		.property( "outNewFaces", &MakeDegenerateBandAroundRegionParams::outNewFaces, return_value_policy::reference() )
		.property( "outExtrudedEdges", &MakeDegenerateBandAroundRegionParams::outExtrudedEdges, return_value_policy::reference() )
		.property( "new2OldMap", &MakeDegenerateBandAroundRegionParams::new2OldMap, return_value_policy::reference() )
				
		.function( "getMaxEdgeLength", optional_override( [] ( MakeDegenerateBandAroundRegionParams& self )
		{
			if ( !self.maxEdgeLength ) throw std::runtime_error( "maxEdgeLength is null" );
			return *self.maxEdgeLength;
		}))
		.function( "setMaxEdgeLength", optional_override( [] ( MakeDegenerateBandAroundRegionParams& self, float v )
		{
			if ( !self.maxEdgeLength ) self.maxEdgeLength = new float;
			*self.maxEdgeLength = v;
		}));

	function( "makeDegenerateBandAroundRegion", &makeDegenerateBandAroundRegion );
}
