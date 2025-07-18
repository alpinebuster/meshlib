#pragma once

#include <vector>
#include <limits>
#include <exception>
#include <string>

#include <emscripten/val.h>

#include <MRMesh/MRMesh.h>
#include <MRMesh/MRMeshFwd.h>
#include <MRMesh/MRVector3.h>
#include <MRMesh/MRAffineXf3.h>
#include <MRMesh/MRMeshProject.h>
#include <MRMesh/MRBox.h>
#include <MRMesh/MRVectorTraits.h>

#include <MRVoxels/MROffset.h>

#include "MRMesh.h"
#include "MREdgeMetric.h"

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

    Mesh getMesh();
    Mesh* getMeshPtr();

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
    static val fromTrianglesImplWithArray( const val& vertexCoords, const val& triangles );
    static val fromTrianglesImpl( const val& vertexCoords, const val& triangles );

    // Geometric query method
    /**
     * @brief Retrieves the bounding box of the mesh
     * @return JavaScript object containing min and max arrays
     *
     * The bounding box is the smallest axis-aligned rectangular prism that encloses the entire mesh,
     * which is important for mesh rendering, collision detection, and spatial queries.
     */
    val getBoundingBoxImpl() const;
    /**
     * @brief Retrieves the position of the specified vertex
     * @param vertId Vertex ID
     * @return Array of vertex coordinates, or null if the ID is invalid
     *
     * This method allows querying the 3D coordinates of any vertex in the mesh,
     * commonly used for mesh editing and vertex operations.
     */
    val getVertexPositionImpl( int vertId ) const;
    /**
     * @brief Sets the position of the specified vertex
     * @param vertId Vertex ID
     * @param position New vertex coordinate array [x, y, z]
     *
     * After modifying the vertex position, invalidateCaches() is automatically called,
     * ensuring that the internal caches of the mesh (such as normals, areas, etc.) are updated correctly.
     */
    void setVertexPositionImpl( int vertId, const val& position );
    int getVertexCountImpl() const;
    int getFaceCountImpl() const;
    /**
     * @brief Calculates the volume of the mesh
     * @return Volume value
     *
     * Note: Only closed meshes can yield an accurate volume calculation.
     */
    double getVolumeImpl() const;
    /**
     * @brief Calculates the surface area of the mesh
     * @return Surface area value
     */
    double getAreaImpl() const;
    /**
     * @brief Calculates the geometric center of the mesh from the bounding box
     * @return Array of center point coordinates
     *
     * This method computes the center based on the bounding box, which is fast but may not represent the centroid.
     */
    val findCenterImpl() const;
    // Face operation method
    /**
     * @brief Retrieves the vertex indices of the specified face
     * @param faceId Face ID
     * @return Array containing three vertex indices, or null if the ID is invalid
     *
     * The returned array contains the indices of the three vertices that form the triangular face,
     * with the vertex order following the right-hand rule to determine the face's orientation.
     */
    val getFaceVerticesImpl( int faceId ) const;
    /**
     * @brief Retrieves the normal vector of the specified face
     * @param faceId Face ID
     * @return Normal vector array [x, y, z], or null if the ID is invalid
     *
     * The normal vector is perpendicular to the surface of the face and is used for lighting calculations, collision detection, and more.
     */
    val getFaceNormalImpl( int faceId ) const;
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
    val projectPointImpl( const val& point, float maxDistance = std::numeric_limits<float>::max() ) const;

    val thickenMeshImpl( float offset, GeneralOffsetParameters &params ) const;
    val cutMeshWithPolylineImpl( const std::vector<float>& coordinates ) const;
    val segmentByPointsImpl( const std::vector<float>& coordinates, const std::vector<float>& dir,
	const EdgeMetricWrapper& edgeMetricWrapper ) const;
    val fixUndercutsImpl( const Vector3f& upDirection ) const;
    val fillHolesImpl() const;
};

} // MRJS
