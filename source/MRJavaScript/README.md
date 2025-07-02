# JS/TS Bindings

## Design Guide

Use `val(typed_memory_view(...))` & `HEAPU8.set(uint8Array, ptr)` to improve performance by avoiding copy ops.

### Export to JS/TS

```cpp
class MeshWrapper {
// ...

public:
    std::vector<Vector3f> points;
    std::vector<Vector3i> faces;

    const float* vertexDataPtr() const { return reinterpret_cast<const float*>(points.data()); }
    size_t vertexCount() const { return points.size(); }

    const int* faceDataPtr() const { return reinterpret_cast<const int*>(faces.data()); }
    size_t faceIndexCount() const { return faces.size() * 3; }

// ...
};

val getVertexPositions( MeshWrapper& mw ) const {
    return val( typed_memory_view( mw.vertexCount() * 3, mw.vertexDataPtr() ) ); // Float32Array
}

EMSCRIPTEN_BINDINGS( SomeModule ) {
   function( "getVertexPositions", &getVertexPositions )
}
```

```js
// Getting the Mesh from WebAssembly
const mesh = Module.returnParts(...).first;

// Getting the Memory View
const positions = mesh.getVertexPositions(); // Float32Array，zero-copy

// Create threejs `BufferGeometry()`
const geometry = new THREE.BufferGeometry();

// Use `Float32Array` directly in threejs attribute.
geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));

const material = new THREE.MeshStandardMaterial({ color: 0x00f00, side: THREE.DoubleSide });
const meshObject = new THREE.Mesh(geometry, material);

scene.add(meshObject);
```

### Load STL

```js
// ...

const uint8Array = new Uint8Array(contents);
const ptr = Module._malloc(uint8Array.byteLength);
Module.HEAPU8.set(uint8Array, ptr);
const result = await Module.MeshLoadWrapper.fromBinaryData(ptr, uint8Array.byteLength, 'stl');

// ...
```

### Performance Compare

TODO

## TODOs

- V2: In version 2, use functions (MACROs) to generate emscripten bindings to reduce redundancy
- V3: In version 3, use clang's ast related api to parse C++ source code then generate emscripten bindings

## NOTEs
In the C++ standard library there are several “pointer” types, each with different ownership and lifetime semantics:

| Pointer Type                        | Header     | Ownership Model                    | Copy / Move                      | Reference Counting                   | Thread Safety                       | Typical Use Cases                                        |
| ----------------------------------- | ---------- | ---------------------------------- | -------------------------------- | ------------------------------------ | ----------------------------------- | -------------------------------------------------------- |
| **Raw pointer**<br>`T*`             | —          | No ownership                       | Copyable & Movable               | None                                 | None                                | Interfacing with C APIs, non-owning access               |
| **`std::unique_ptr<T>`**            | `<memory>` | Exclusive ownership                | Move-only (no copy)              | None                                 | N/A                                 | Factory returns, container elements, strict ownership    |
| **`std::shared_ptr<T>`**            | `<memory>` | Shared ownership                   | Copyable & Movable               | Yes (atomic or non-atomic)           | Reference-count ops are thread-safe | Shared resources across modules or threads               |
| **`std::weak_ptr<T>`**              | `<memory>` | Non-owning “weak” ref              | Copyable & Movable               | Linked to `shared_ptr` control block | Same as `shared_ptr`                | Breaking `shared_ptr` reference cycles, observer pattern |
| **`std::auto_ptr<T>`**<br>(removed) | `<memory>` | Exclusive ownership (move-on-copy) | Copyable but transfers ownership | None                                 | N/A                                 | Deprecated in C++17—use `unique_ptr` instead             |

---

### Key Differences

1. **Raw pointer (`T*`)**

   * **Ownership**: None—you must manage object lifetime yourself.
   * **When to use**: Non-owning access, interfacing with legacy C or third-party APIs.
   * **Drawbacks**: Risk of dangling pointers, leaks, or double deletes.

2. **`std::unique_ptr<T>`**

   * **Ownership**: Exclusive; only one `unique_ptr` may own the object at a time.
   * **Copy/Move**: Non-copyable; move-only via `std::move`.
   * **Overhead**: Minimal—just a raw pointer under the hood.
   * **Use when**: It is needed to strict single ownership, e.g. RAII factory returns or container elements.

3. **`std::shared_ptr<T>`**

   * **Ownership**: Shared; internal reference count tracks how many owners.
   * **Copy/Move**: Copyable—copies increment the count; moveable too.
   * **Overhead**: Control block for reference counts, atomic ops if thread-safe.
   * **Use when**: Multiple parts of code must share lifetime and can’t easily determine who deletes last.

4. **`std::weak_ptr<T>`**

   * **Ownership**: Doesn’t own; merely observes a `shared_ptr`’s object without incrementing the count.
   * **Use**: Breaks cyclic `shared_ptr` references; allows check if the object still exists via `lock()`.

5. **`std::auto_ptr<T>`**

   * **Note**: Deprecated in C++11 and removed in C++17 due to confusing copy semantics (ownership transfers on copy). Use `unique_ptr` instead.

### Choosing Which to Use

* **Prefer `unique_ptr`** whenever require enforcing a single owner—minimal overhead and clear semantics.
* **Use `shared_ptr` + `weak_ptr`** only when shared ownership required; watch out for cycles.
* **Reserve raw pointers** for non-owning references or interop with C APIs; avoid them for ownership.
