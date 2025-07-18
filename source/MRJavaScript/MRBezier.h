#include <array>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector.h>
#include <MRMesh/MRVector2.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRVector4.h>
#include <MRMesh/MRVectorTraits.h>
#include <MRMesh/MRBezier.h>

using namespace emscripten;
using namespace MR;


namespace MRJS
{

template <typename CurveType, typename VectorType>
auto bindTypedCubicBezierCurve( const std::string& className ) {
    auto cls = class_<CurveType>( className.c_str() )
        .constructor<>()
    
        .function( "getPoint", &CurveType::getPoint )
        .function( "setPoint",
            optional_override( [] ( CurveType& self, int idx, VectorType& p ) -> void
            {
                if ( idx >= 0 && idx < 4 )
                {
                    self.p[idx] = p;
                }
            } ) 
        )
        .class_function( "getWeights", &CurveType::getWeights );

    return cls;
}

} // MRJS

