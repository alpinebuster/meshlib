// #include <string>
// #include <vector>
// #include <memory>

// #include <emscripten/bind.h>
// #include <emscripten/val.h>

// #include <MRMesh/MRMesh.h>
// #include <MRMesh/MRMeshLoad.h>
// #include <MRMesh/MRVector3.h>
// #include <MRMesh/MRExpected.h>

// using namespace emscripten;
// using namespace MR;

// // 辅助函数：将 C++ vector 转换为 JavaScript Float32Array
// val vectorToFloat32Array(const std::vector<Vector3f>& vec) {
//     return val(typed_memory_view(vec.size() * 3, reinterpret_cast<const float*>(vec.data())));
// }

// // 辅助函数：将三角剖分数据转换为 JavaScript 数组
// val triangulationToJS(const Triangulation& t) {
//     std::vector<uint32_t> flatTris;
//     for (const auto& tri : t) {
//         flatTris.push_back(tri[0].get());
//         flatTris.push_back(tri[1].get());
//         flatTris.push_back(tri[2].get());
//     }
//     return val::array(flatTris);
// }

// // Mesh 类的 JavaScript 绑定
// EMSCRIPTEN_BINDINGS(Mesh) {
//     class_<Mesh>("Mesh")
//         .constructor<>()
//         .function("getBoundingBox", &Mesh::getBoundingBox)
//         .function("computeBoundingBox", select_overload<Box3f() const>(&Mesh::computeBoundingBox))
//         .function("averageEdgeLength", &Mesh::averageEdgeLength)
//         .function("area", select_overload<double() const>(&Mesh::area))
//         .function("volume", select_overload<double() const>(&Mesh::volume))
//         .function("signedDistance", select_overload<float(const Vector3f&) const>(&Mesh::signedDistance))
//         .function("projectPoint", select_overload<MeshProjectionResult(const Vector3f&, float, const FaceBitSet*, const AffineXf3f*) const>(&Mesh::projectPoint))
//         .function("transform", select_overload<void(const AffineXf3f&, const VertBitSet*)>(&Mesh::transform))
//         .function("pack", select_overload<void(const PartMapping&, bool)>(&Mesh::pack))
//         .function("getPoints", &Mesh::points)
//         .function("getTopology", &Mesh::topology);
        
//     // 暴露 Vector3f
//     value_array<Vector3f>("Vector3f")
//         .element(&Vector3f::x)
//         .element(&Vector3f::y)
//         .element(&Vector3f::z);
        
//     // 暴露 Box3f
//     class_<Box3f>("Box3f")
//         .property("min", &Box3f::min)
//         .property("max", &Box3f::max);
        
//     // 暴露 MeshProjectionResult
//     class_<MeshProjectionResult>("MeshProjectionResult")
//         .property("distSq", &MeshProjectionResult::distSq)
//         .property("mtp", &MeshProjectionResult::mtp)
//         .property("point", &MeshProjectionResult::point);
        
//     // 暴露 MeshTriPoint
//     class_<MeshTriPoint>("MeshTriPoint")
//         .property("face", &MeshTriPoint::face)
//         .property("coords", &MeshTriPoint::coords);
// }

// // MeshLoad 命名空间的 JavaScript 绑定
// EMSCRIPTEN_BINDINGS(MeshLoad) {
//     function("fromObj", select_overload<Expected<Mesh>(const std::filesystem::path&, const MeshLoadSettings&)>(&MeshLoad::fromObj));
//     function("fromOff", select_overload<Expected<Mesh>(const std::filesystem::path&, const MeshLoadSettings&)>(&MeshLoad::fromOff));
//     function("fromPly", select_overload<Expected<Mesh>(const std::filesystem::path&, const MeshLoadSettings&)>(&MeshLoad::fromPly));
//     function("fromAnyStl", select_overload<Expected<Mesh>(const std::filesystem::path&, const MeshLoadSettings&)>(&MeshLoad::fromAnyStl));
//     function("fromAnySupportedFormat", select_overload<Expected<Mesh>(const std::filesystem::path&, const MeshLoadSettings&)>(&MeshLoad::fromAnySupportedFormat));
    
//     // 内存加载版本
//     function("fromObjData", +[](const std::string& data) -> Mesh {
//         std::istringstream stream(data);
//         auto mesh = MeshLoad::fromObj(stream).value();
//         return mesh;
//     });
    
//     function("fromOffData", +[](const std::string& data) -> Mesh {
//         std::istringstream stream(data);
//         auto mesh = MeshLoad::fromOff(stream).value();
//         return mesh;
//     });
    
//     function("fromPlyData", +[](const std::string& data) -> Mesh {
//         std::istringstream stream(data);
//         auto mesh = MeshLoad::fromPly(stream).value();
//         return mesh;
//     });
    
//     function("fromStlData", +[](const std::string& data) -> Mesh {
//         std::istringstream stream(data);
//         auto mesh = MeshLoad::fromAnyStl(stream).value();
//         return mesh;
//     });
// }

// // 静态构造函数的绑定
// EMSCRIPTEN_BINDINGS(MeshStatic) {
//     function("fromTriangles", +[](const std::vector<Vector3f>& vertices, const std::vector<uint32_t>& indices) -> Mesh {
//         VertCoords vertCoords;
//         vertCoords.resize(vertices.size());
//         for (size_t i = 0; i < vertices.size(); ++i) {
//             vertCoords[VertId(i)] = vertices[i];
//         }
        
//         Triangulation tris;
//         for (size_t i = 0; i < indices.size(); i += 3) {
//             tris.push_back({ 
//                 VertId(indices[i]), 
//                 VertId(indices[i+1]), 
//                 VertId(indices[i+2]) 
//             });
//         }
        
//         return Mesh::fromTriangles(std::move(vertCoords), tris).value();
//     });
// }

// // 工具函数绑定
// EMSCRIPTEN_BINDINGS(MeshUtils) {
//     function("computeVertexNormals", +[](const Mesh& mesh) {
//         std::vector<Vector3f> normals;
//         for (VertId v{0}; v < mesh.topology.vertSize(); ++v) {
//             if (mesh.topology.hasVert(v)) {
//                 normals.push_back(mesh.normal(v));
//             }
//         }
//         return vectorToFloat32Array(normals);
//     });
// }
