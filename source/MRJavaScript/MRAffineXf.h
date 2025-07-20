#pragma once

#include <type_traits>

#include <MRPch/MRWasm.h>

using namespace emscripten;

// NOTE: 
// 1. Both `EM_NAME::operator()` and `EM_NAME::linearOnly` are const member functions:
// 
// TYPE operator()( const TYPE& x ) const noexcept;
// TYPE linearOnly( const TYPE& x ) const noexcept;
// 
// So it is required to tell `select_overload()` that the methods are const.
// 
// 2. `inverse()` requires not using integer
// 
#define BIND_AFFINE_XF(EM_NAME, TYPE) \
    class_<EM_NAME>(#EM_NAME) \
        .constructor<>() \
        .constructor<const TYPE::MatrixType&, const TYPE&>() \
        .property("A", &EM_NAME::A) \
        .property("b", &EM_NAME::b) \
        .class_function("translation", select_overload<EM_NAME(const TYPE&)>(&EM_NAME::translation)) \
        .class_function("linear", select_overload<EM_NAME(const TYPE::MatrixType&)>(&EM_NAME::linear)) \
        .class_function("xfAround", select_overload<EM_NAME(const TYPE::MatrixType&, const TYPE&)>(&EM_NAME::xfAround)) \
        .function("operatorCall", select_overload<TYPE(const TYPE&) const>(&EM_NAME::operator())) \
        .function("linearOnly", select_overload<TYPE(const TYPE&) const>(&EM_NAME::linearOnly)) \
        .function("equals", optional_override([](const EM_NAME& a, const EM_NAME& b) { return a == b; })) \
        .function("notEquals", optional_override([](const EM_NAME& a, const EM_NAME& b) { return a != b; }));

/**
 *@brief Bind `AffineXf` to `AffineXf2f`, `AffineXf2d`, `AffineXf3f` and `AffineXf3d` 
 *
 * `.template constructor<…>()` to tell the compiler “constructor is a dependent‑template.
 * Use `typename TYPE::MatrixType` so that `MatrixType` is recognized as a type.
 *
 * @tparam EM_NAME
 * @tparam TYPE 
 * @param jsName 
 */
template<typename EM_NAME, typename TYPE>
void bindAffineXf( const char* jsName )
{
    auto cls = class_<EM_NAME>( jsName )
        .template constructor<>()
        .template constructor<const typename TYPE::MatrixType&, const TYPE&>()
        .property( "A", &EM_NAME::A )
        .property( "b", &EM_NAME::b )
        .class_function( "translation", select_overload<EM_NAME( const TYPE& )>( &EM_NAME::translation ) )
        // NOTE: When do I have to use `typename` and not `class`?
        // 
        // The only scenario where it is needed to differentiate is dependent names - **inside a template**,
        // when tell the compiler that "this is a type that depends on template parameters",
        // it is needed to prepend the type with the `typename`
        // 
        .class_function( "linear", select_overload<EM_NAME( const typename TYPE::MatrixType& )>( &EM_NAME::linear ) )
        .class_function( "xfAround", select_overload<EM_NAME( const typename TYPE::MatrixType&, const TYPE& )>( &EM_NAME::xfAround ) )
        // `operator()`, `linearOnly()` needs to add `const`
        .function( "operatorCall", select_overload<TYPE( const TYPE& ) const>( &EM_NAME::operator() ) )
        .function( "linearOnly", select_overload<TYPE( const TYPE& ) const>( &EM_NAME::linearOnly ) )
        .function( "equals", optional_override( [] ( const EM_NAME& a, const EM_NAME& b )
        {
            return a == b;
        } ) )
        .function( "notEquals", optional_override( [] ( const EM_NAME& a, const EM_NAME& b )
        {
            return a != b;
        } ) );

    // 2) Conditionally bind `inverse()` to non-integer types
    if constexpr ( !std::is_integral_v<typename TYPE::ValueType> )
    {
        // Note that the `inverse()` signature is: `AffineXf inverse() const noexcept ` 
        cls.function( "inverse", select_overload<EM_NAME() const>( &EM_NAME::inverse ) );
    }
}
