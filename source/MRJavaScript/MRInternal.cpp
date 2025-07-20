#include <optional>
#include <memory>

#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRMeshExtrude.h>
#include <MRMesh/MRRegionBoundary.h>
#include <MRMesh/MRBitSet.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

#define BIND_PHMAP_INTERNAL_TYPES(KEY, VAL, NAME)                               \
    EMSCRIPTEN_BINDINGS(__phmapInternal##NAME) {                                \
        using K = KEY; using V = VAL;                                           \
                                                                                \
        using Hash = phmap::priv::hash_default_hash<K>;                         \
        using Eq = phmap::priv::hash_default_eq<K>;                             \
                                                                                \
        using Policy = phmap::priv::FlatHashMapPolicy<K, V>;                    \
        using RawHashSet = phmap::priv::raw_hash_set<Policy, phmap::priv::Hash<K>, phmap::priv::EqualTo<K>, std::allocator<std::pair<const K, V>>>; \
        using RawHashMap = phmap::priv::raw_hash_map<Policy, phmap::priv::Hash<K>, phmap::priv::EqualTo<K>, std::allocator<std::pair<const K, V>>>; \
                                                                                \
        class_<Policy>("__phmap_internal_FlatHashMapPolicy_" #NAME);            \
        class_<RawHashSet>("__phmap_internal_raw_hash_set_" #NAME);             \
        class_<RawHashMap>("__phmap_internal_raw_hash_map_" #NAME);             \
    }

// TODO: V2
