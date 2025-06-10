#include <emscripten/bind.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRId.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS(MR_EdgeId) {
    // Bind UndirectedEdgeId first (needed for EdgeId constructor)
    class_<UndirectedEdgeId>("UndirectedEdgeId")
        .constructor<int>()
        .function("toInt", select_overload<int() const>(static_cast<int(UndirectedEdgeId::*)() const>(&UndirectedEdgeId::operator int)));

    class_<Id<EdgeTag>>("EdgeId")
        // Constructors
        .constructor<>()
        .constructor<int>()
		.class_function("fromUndirected", optional_override([](const UndirectedEdgeId& u) { return Id<EdgeTag>(u); }))

        // Conversion to int
        .function("toInt", optional_override([](const Id<EdgeTag>& self){ return int(self); }))
        // Validity check
        .function("valid", &Id<EdgeTag>::valid)
        // Access underlying value
        .function("get", optional_override([](Id<EdgeTag>& self){ return self.get(); }))
        // Comparison
        .function("equals", optional_override([](const Id<EdgeTag>& a, const Id<EdgeTag>& b){ return a == b; }))
        .function("notEquals", optional_override([](const Id<EdgeTag>& a, const Id<EdgeTag>& b){ return a != b; }))
        .function("lessThan", optional_override([](const Id<EdgeTag>& a, const Id<EdgeTag>& b){ return a < b; }))
        // Increment / Decrement
        .function("increment", optional_override([](Id<EdgeTag>& self){ ++self; return self; }))
        .function("decrement", optional_override([](Id<EdgeTag>& self){ --self; return self; }))
        // Symmetry operations
        .function("sym", &Id<EdgeTag>::sym)
        .function("even", &Id<EdgeTag>::even)
        .function("odd", &Id<EdgeTag>::odd)
        // Undirected conversion
        .function("undirected", &Id<EdgeTag>::undirected)
        .function("toUndirected", optional_override([](const Id<EdgeTag>& self){ return UndirectedEdgeId(self); }));
}
