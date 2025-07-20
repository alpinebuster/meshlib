#include <iostream>

#include <emscripten.h>
#include <MRPch/MRWasm.h>

using namespace emscripten;

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void printtt() { std::cout << "Hello world from `MeshSDK` wasm binding tests!" << std::endl; }
}

float lerp( float a, float b, float t ) { return ( 1 - t ) * a + t * b; }
class MyClass {
public:
    MyClass( int x, std::string y ): x( x ), y( y ) {}

    void incrementX() { ++x; }
    int getX() const { return x; }
    void setX( int x_ ) { x = x_; }

    static std::string getStringFromInstance( const MyClass& instance ) { return instance.y; }

private:
    int x;
    std::string y;
};


EMSCRIPTEN_BINDINGS( JSTestModule ) {
    function( "lerp", &lerp );


    class_<MyClass>( "MyClass" )
        .constructor<int, std::string>()
        .function( "incrementX", &MyClass::incrementX )
        .property( "x", &MyClass::getX, &MyClass::setX )
        .property( "x_readonly", &MyClass::getX )
        .class_function( "getStringFromInstance", &MyClass::getStringFromInstance );
}
