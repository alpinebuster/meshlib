#pragma once

#include <vector>
#include <limits>
#include <exception>
#include <string>

#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRMeshProject.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>


#include "MRMesh.h"

using namespace MR;
using emscripten::val;

/**
 * @brief MRJS namespace
 *
 * This namespace contains all the `meshlib` wrapper classes and helper functions used for JavaScript bindings.
 * Using a separate namespace helps to:
 *
 *  1. Avoid name conflicts with other libraries
 *  2. Clearly identify which code is specifically designed for JavaScript bindings
 *  3. Facilitate code organization and maintenance
 */
namespace MRJS
{

/**
 * @brief Helper function to convert a JavaScript array to a Vector3f
 * @param arr JavaScript array containing 3 floating-point elements
 * @return Vector3f object
 *
 * This function extracts three floating-point values from the array passed in from JavaScript,
 * creates, and returns a 3D vector object for passing coordinate data between C++ and JavaScript.
 */
Vector3f arrayToVector3f( const val& arr );

/**
 * @brief Helper function to convert a Vector3f to a JavaScript array
 * @param v Vector3f object
 * @return JavaScript array containing the x, y, and z components
 *
 * This function converts a C++ 3D vector object into an array format that can be understood by JavaScript,
 * facilitating the display or processing of coordinate data in a web interface.
 */
val vector3fToArray( const Vector3f& v );

/**
 * @brief Helper function to convert a Box3F to a JavaScript object
 * @param box 3D bounding box object
 * @return JavaScript object containing min and max properties
 *
 * A bounding box is an important data structure that describes the spatial extent of a 3D object.
 * This function converts it into a JavaScript object for easier visualization or collision detection on the frontend.
 */
val box3fToObject( const Box<Vector3<float>>& box );

/**
 * @brief JavaScript-friendly wrapper for the Mesh class
 *
 * This class provides a bridge for JavaScript code to easily manipulate C++ Mesh objects.
 * It encapsulates common mesh operations, including geometric queries, transformations, projections, and more.
 *
 * Design considerations:
 * - Simplify complex C++ mesh operations into interfaces callable from JavaScript
 * - Provide error handling mechanisms to ensure stability of JavaScript calls
 * - Support for creating, modifying, and querying mesh operations
 */
class MeshWrapper {
public:
    /// The internally stored grid object
    Mesh mesh;

    /**
     * @brief Default constructor
     * Creates an empty mesh wrapper
     */
    MeshWrapper() = default;

    /**
     * @brief Constructs a wrapper from an existing Mesh object
     * @param m The Mesh object to be wrapped
     */
    MeshWrapper( const Mesh& m );

    // Static factory method
    /**
     * @brief Creates a mesh from triangle data
     * @param vertexCoords JavaScript array containing all vertex coordinates
     * @param triangles JavaScript array containing triangle index information
     * @return JavaScript object containing success field and mesh or error field
     *
     * This is the main method for creating a mesh. It accepts an array of vertex coordinates and an array of triangle indices,
     * constructing a complete mesh topology. The returned object contains the operation result and any potential error information.
     *
     * Vertex coordinate format: [[x1,y1,z1], [x2,y2,z2], ...]
     * Triangle format: [[v1,v2,v3], [v4,v5,v6], ...]
     */
    static val fromTriangles( const val& vertexCoords, const val& triangles );
    static val fromTrianglesMemoryView( const float* vertexPtr,
                                        size_t        numVerts,
                                        const uint32_t* triPtr,
                                        size_t         numTris );

    // Geometric query method
    /**
     * @brief Retrieves the bounding box of the mesh
     * @return JavaScript object containing min and max arrays
     *
     * The bounding box is the smallest axis-aligned rectangular prism that encloses the entire mesh,
     * which is important for mesh rendering, collision detection, and spatial queries.
     */
    val getBoundingBox() const;

    /**
     * @brief Retrieves the position of the specified vertex
     * @param vertId Vertex ID
     * @return Array of vertex coordinates, or null if the ID is invalid
     *
     * This method allows querying the 3D coordinates of any vertex in the mesh,
     * commonly used for mesh editing and vertex operations.
     */
    val getVertexPosition( int vertId ) const;

    /**
     * @brief Sets the position of the specified vertex
     * @param vertId Vertex ID
     * @param position New vertex coordinate array [x, y, z]
     *
     * After modifying the vertex position, invalidateCaches() is automatically called,
     * ensuring that the internal caches of the mesh (such as normals, areas, etc.) are updated correctly.
     */
    void setVertexPosition( int vertId, const val& position );

    int getVertexCount() const;
    int getFaceCount() const;

    /**
     * @brief Calculates the volume of the mesh
     * @return Volume value
     *
     * Note: Only closed meshes can yield an accurate volume calculation.
     */
    double getVolume() const;

    /**
     * @brief Calculates the surface area of the mesh
     * @return Surface area value
     */
    double getArea() const;

    /**
     * @brief Calculates the geometric center of the mesh from the bounding box
     * @return Array of center point coordinates
     *
     * This method computes the center based on the bounding box, which is fast but may not represent the centroid.
     */
    val findCenter() const;

    // Face operation method
    /**
     * @brief Retrieves the vertex indices of the specified face
     * @param faceId Face ID
     * @return Array containing three vertex indices, or null if the ID is invalid
     *
     * The returned array contains the indices of the three vertices that form the triangular face,
     * with the vertex order following the right-hand rule to determine the face's orientation.
     */
    val getFaceVertices( int faceId ) const;

    /**
     * @brief Retrieves the normal vector of the specified face
     * @param faceId Face ID
     * @return Normal vector array [x, y, z], or null if the ID is invalid
     *
     * The normal vector is perpendicular to the surface of the face and is used for lighting calculations, collision detection, and more.
     */
    val getFaceNormal( int faceId ) const;

    // Point projection method
    /**
     * @brief Projects a point onto the surface of the mesh
     * @param point Array of coordinates of the point to be projected [x, y, z]
     * @param maxDistance Maximum search distance, defaults to infinity
     * @return JavaScript object containing the projection result or error information
     *
     * This method finds the closest point on the mesh surface to the given point,
     * commonly used for surface sampling, collision detection, and mesh alignment.
     */
    val projectPoint( const val& point, float maxDistance = std::numeric_limits<float>::max() ) const;

    val fixUndercuts(const Vector3f& upDirection) const;
    val fillHoles() const;

    // Transformation method
    /**
     * @brief Applies an affine transformation to the mesh
     * @param matrix 4x4 transformation matrix passed as a flat array of 16 elements
     *
     * Transformation matrix format: [m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33]
     * Supports various affine transformations such as rotation, translation, and scaling.
     */
    void transform( const val& matrix );

    // Optimization method
    /**
     * @brief Optimizes the memory layout of the mesh
     *
     * This method reorganizes the mesh data, removing unused vertices and faces,
     * improving memory efficiency and access performance. It is recommended to call this after completing mesh editing.
     */
    void pack();
};

} // namespace MRJS
