#include <MRPch/MRWasm.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRDipole.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( DipoleModule )
{
    class_<Dipole>( "Dipole" )
        .constructor<>()

        .property( "pos", &Dipole::pos )
        .property( "area", &Dipole::area )
        .property( "dirArea", &Dipole::dirArea )
        .property( "rr", &Dipole::rr )

        // Since Embind can't handle reference arguments like `float& addTo` directly
        // So here the input `addTo` is wrapped in a layer with `optional_override()` and the output is passed back to JS via the `val`
        .function( "addIfGoodApprox",
            optional_override( [](
                Dipole& self,
                const Vector3f& q,
                float betaSq,
                float addTo /* Here it is received by value */ )
        {
            // Copy a copy of `addTo` on the heap and pass the original method
            float temp = addTo;
            // This will change the value of `temp`
            bool ok = self.addIfGoodApprox( q, betaSq, temp );

            val result = val::array();
            result.set( "success", ok );
            result.set( "addTo", temp );

            return result;
        } ) );
}
