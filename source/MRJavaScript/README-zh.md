# JS/TS 绑定

应该遵守的代码规范。

## TODOs

- 按原接口导出的js接口与封装了特殊功能导出的js接口区分开
- V2: In version 2, use functions (MACROs) to generate emscripten bindings to reduce redundancy
- V3: In version 3, use clang's ast related api to parse C++ source code then generate emscripten bindings

## 指针 & 引用参数

在 Embind 里，不需要在 JS 端区分 “这是一个指针” 和 “这是一个引用”——对 C++ 侧暴露给 JS 的类而言，Embind 会封装好一个 JS “wrapper object”，这个对象本身就 **携带** 了它到底是一个 `Mesh*` 还是 `Mesh&`（底层都是指针） 的信息。

### 绑定层面

假设有以下代码：

```cpp
// 允许裸指针
EMSCRIPTEN_BINDINGS(my_module) {
  class_<Mesh>("Mesh")
    .constructor<>()       // JS 侧可以 new Module.Mesh()
    // … 更多绑定 …
    ;

  class_<IPointsToMeshProjector>("IPointsToMeshProjector")
    .allow_subclass<IPointsToMeshProjector>("IPointsToMeshProjector")
    .function(
      "updateMeshData",
      &IPointsToMeshProjector::updateMeshData,
      pure_virtual(),
      allow_raw_pointers()   // 允许在 JS 侧传入 Mesh* 或 Mesh 的实例
    )
    // …
    ;
}
```

* 当在 `.function(...)` 里写上了 `allow_raw_pointers()`，Embind 就允许这个方法接收任何 JS 侧的 `Module.Mesh` 实例（或者 `null`/`undefined`），并自动把它“解”成底层的 C++ `Mesh*`。
* 如果是 `const Mesh& mesh`（引用参数），Embind 内部同样会把 JS 传入的那个 `Module.Mesh` wrapper 当成它的地址来用——因为引用背后本质就是指针，只不过语义不同。

### JS 端如何调用

```js
// 假设已经从 C++ 那边获得了一个 mesh：
let mesh = new Module.Mesh(); // 也可以是从 C++ 侧传过来的现成 Mesh 对象

// 假设 proj 是 JS 侧继承 IPointsToMeshProjector 得到的实例：
let proj = new MyProjector();

// 调用时直接把 mesh 当作参数传入即可——Embind 会
// - 如果是 C++ 侧签名是 (const Mesh& mesh), 就把这个 wrapper 解成 &mesh
// - 如果是 C++ 侧签名是 (const Mesh* mesh), 就把这个 wrapper 解成 mesh*
// 这两个情况在 JS 端完全“透明”，不需要写额外的转换
proj.updateMeshData(mesh);

// 如果想传 nullptr 给 C++ 的指针参数（Mesh*），也可以传 JS 端的 null/undefined：
proj.updateMeshData(null);  // C++ 这边就收到 mesh == nullptr
```
## 设计指南

使用 `val(typed_memory_view(...))` 和 `HEAPU8.set(uint8Array, ptr)` 来避免拷贝操作、提升性能。

### 导出到 JS/TS

```cpp
class MeshWrapper {
// …

public:
    std::vector<Vector3f> points;
    std::vector<Vector3i> faces;

    const float* vertexDataPtr() const { return reinterpret_cast<const float*>(points.data()); }
    size_t vertexCount() const { return points.size(); }

    const int* faceDataPtr() const { return reinterpret_cast<const int*>(faces.data()); }
    size_t faceIndexCount() const { return faces.size() * 3; }

// …
};

val getVertexPositions( MeshWrapper& mw ) const {
    return val( typed_memory_view( mw.vertexCount() * 3, mw.vertexDataPtr() ) ); // Float32Array
}

EMSCRIPTEN_BINDINGS( SomeModule ) {
   function( "getVertexPositions", &getVertexPositions );
}
```

```js
// 从 WebAssembly 获取 Mesh 实例
const mesh = Module.returnParts(...).first;

// 获取零拷贝的内存视图
const positions = mesh.getVertexPositions(); // Float32Array

// 创建 three.js 的 BufferGeometry
const geometry = new THREE.BufferGeometry();

// 直接用 Float32Array 作为 three.js 的 attribute
geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));

const material = new THREE.MeshStandardMaterial({
  color: 0x00ff00,
  side: THREE.DoubleSide
});
const meshObject = new THREE.Mesh(geometry, material);

scene.add(meshObject);
```

### 加载 STL

```js
// …

const uint8Array = new Uint8Array(contents);
const ptr = Module._malloc(uint8Array.byteLength);
Module.HEAPU8.set(uint8Array, ptr);
const result = await Module.MeshLoadWrapper.fromBinaryData(
  ptr,
  uint8Array.byteLength,
  'stl'
);

// …
```

## `static_cast` 和 `reinterpret_cast`

### **static_cast**

**用途：安全的类型转换**
- 编译时检查转换的合法性
- 进行必要的值转换
- 保持数据的语义意义

**示例：**
```cpp
EdgeId edgeId(42);
int value = static_cast<int>(edgeId);  // 调用 EdgeId 的 operator int()
// 这里实际调用了 EdgeId::operator ValueType() const { return id_; }
```

**特点：**
- 会调用类型转换操作符或构造函数
- 可能改变数据的表示形式
- 编译器会检查转换是否合法
- 相对安全

### **reinterpret_cast**

**用途：重新解释内存中的位模式**
- 不进行任何转换，只是改变编译器对内存的解释
- 不检查转换的安全性
- 直接操作内存

**示例：**
```cpp
std::vector<EdgeId> edges = {EdgeId(1), EdgeId(2), EdgeId(3)};
const int* intPtr = reinterpret_cast<const int*>(edges.data());
// 直接将 EdgeId* 重新解释为 int*，没有任何转换
```

**特点：**
- 零开销，不调用任何函数
- 只改变指针/引用的类型
- 不保证安全性
- 要求源类型和目标类型有相同的内存布局

### **应用**

**EdgeId 转换：**
```cpp
// static_cast - 调用转换操作符
int value = static_cast<int>(edgeId);  // 调用 operator ValueType()

// reinterpret_cast - 直接重新解释内存（用于数组）
const int* data = reinterpret_cast<const int*>(edges.data());
```

## 性能对比

TODO

## 指针之间的区别

C++ 标准库里，跟 “指针” 相关的主要有以下几种类型：

| 指针类型                         | 所属头文件  | 所有权模型              | 拷贝／移动         | 引用计数                 | 线程安全          | 典型用途                             |
| ------------------------------ | ---------- | --------------------- | ---------------- | ----------------------  | ---------------- | ----------------------------------- |
| **裸指针**<br>`T*`              |     —      | 无所有权（非拥有）       | 可拷贝·可移动      | 无                      | 无                | 与 C 接口交互、内部临时访问             |
| **`std::unique_ptr`**          | `<memory>` | 独占所有权              | 不可拷贝；可移动   | 无                       | —                | 明确单一所有者；工厂函数返回；容器元素     |
| **`std::shared_ptr`**          | `<memory>` | 共享所有权              | 可拷贝·可移动     | 有（线程安全）             | 引用计数操作线程安全 | 需要跨多个组件／线程共享对象             |
| **`std::weak_ptr`**            | `<memory>` | 弱引用（不拥有）         | 可拷贝·可移动     | 链接到 `shared_ptr` 的计数 | 同 `shared_ptr`   | 观察者模式、打破 `shared_ptr` 循环引用  |
| **`std::auto_ptr`**<br>(已废弃) | `<memory>` | 独占所有权（移动语义怪异） | 拷贝时会转移所有权 | 无                       | —                 | C++11 前的独占智能指针，已在 C++17 移除 |

---

## 细节对比

1. **裸指针 (`T*`)**

   * **无所有权**：它只是一个地址，指向的对象销毁和它无关。
   * **使用场景**：

     * 访问外部（C API、第三方库）分配的内存；
     * 快速遍历、非拥有语义。
   * **风险**：悬空指针、内存泄漏、重复释放。

2. **`std::unique_ptr<T>`**

   * **独占式拥有**：任意时刻只有一个 `unique_ptr` 拥有对象。
   * **移动语义**：支持 `std::move` 转移所有权，但禁止拷贝。
   * **零开销**：大小等同于裸指针，没有引用计数。
   * **典型用法**：工厂函数返回、`std::vector<std::unique_ptr<T>>`、RAII 管理。

3. **`std::shared_ptr<T>`**

   * **引用计数**：内部维护一个控制块，跟踪多少 `shared_ptr` 在持有同一对象。
   * **拷贝即共享**：拷贝构造和拷贝赋值会增加计数；析构或重置会减少计数，计数为 0 时销毁对象。
   * **线程安全**：对同一控制块的计数增减是原子操作。
   * **使用场景**：多个所有者间共享生命周期；难以确定谁先销毁时。

4. **`std::weak_ptr<T>`**

   * **不拥有对象**：它不会增加引用计数，只持有一个弱引用。
   * **打破循环引用**：常与 `shared_ptr` 配合，用来观察对象而不延长其生命周期。
   * **升级检查**：通过 `lock()` 可以尝试得到一个 `shared_ptr<T>`（如果对象还存在）。

5. **`std::auto_ptr<T>`（已废弃）**

   * **早期独占管理**：支持拷贝，但拷贝会转移所有权（语义容易令人困惑）。
   * **已移除**：C++11 引入更合理的 `unique_ptr`，C++17 中 `auto_ptr` 被正式废弃并移除。

### 建议

* **优先**使用 `std::unique_ptr` 来管理“单一所有权”资源。
* **需要共享**时，再考虑 `std::shared_ptr` + `std::weak_ptr`。
* **绝大多数场合**都不应使用裸指针来管理生命期，除非有特殊性能或兼容性需求。
