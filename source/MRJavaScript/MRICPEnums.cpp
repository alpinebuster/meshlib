#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <MRMesh/MRICPEnums.h>

using namespace emscripten;
using namespace MR;

EMSCRIPTEN_BINDINGS( ICPEnumsModule )
{
    enum_<ICPMethod>( "ICPMethod" )
        .value( "Combined", ICPMethod::Combined )
        .value( "PointToPoint", ICPMethod::PointToPoint )
        .value( "PointToPlane", ICPMethod::PointToPlane );
        
    enum_<ICPMode>( "ICPMode" )
        .value( "RigidScale", ICPMode::RigidScale )
        .value( "AnyRigidXf", ICPMode::AnyRigidXf )
        .value( "OrthogonalAxis", ICPMode::OrthogonalAxis )
        .value( "FixedAxis", ICPMode::FixedAxis )
        .value( "TranslationOnly", ICPMode::TranslationOnly );
        
    enum_<ICPExitType>( "ICPExitType" )
        .value( "NotStarted", ICPExitType::NotStarted )
        .value( "NotFoundSolution", ICPExitType::NotFoundSolution )
        .value( "MaxIterations", ICPExitType::MaxIterations )
        .value( "MaxBadIterations", ICPExitType::MaxBadIterations )
        .value( "StopMsdReached", ICPExitType::StopMsdReached );
}
