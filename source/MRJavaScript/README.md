# JS/TS Bindings

Rules that should obey.

- Standard library `tl::expected<T, E>`: ``
- Standard library `std::function`: `class_<std::function<std::string( std::string )>>( "StringFunctorString" ).constructor<>().function( "opcall", &std::function<std::string( std::string )>::operator() );`
- Standard library `std::optional`: `register_optional<SmallClass>();`
- Standard library `std::array`: `value_array<std::array<float, 3>>( "Array3f" ).element( emscripten::index<0>() ).element( emscripten::index<1>() ).element( emscripten::index<2>() );`, `value_array<std::array<EdgeId, 2>>( "Array2EdgeId" ).element( emscripten::index<0>() ).element( emscripten::index<1>() );`
- Standard library `std::vector`: `register_vector<Vector3f>( "VectorVector3f" );`
- Standard library `std::pair`: `value_array<std::pair<Vector3f, Vector3f>>( "Vector3fPair" ).element( &std::pair<Vector3f, Vector3f>::first ).element( &std::pair<Vector3f, Vector3f>::second )`
- Wrapper functions for structs consistently use `create#ORIGINAL_NAME` (e.g., for `SortIntersectionsData`, the name is `createSortIntersectionsData`)
- Encapsulate common functional processes that are composed of different modules by adding the `Impl` suffix to the corresponding key function name (e.g., `fixUndercuts` corresponds to `fixUndercutsImpl`).

- Prioritize using `val(typed_memory_view(...))` and `HEAPU8.set(uint8Array, ptr)`

- Automatically delete short-lived C++ objects at the end of the scope when they’re declared with a using keyword: `using x = new Module.MyClass; x.method();`. Using `smart_ptr_constructor()` ensures that when creating an object in JavaScript, a **smart pointer** is returned, making it easier to manage the object's lifecycle. Using `smart_ptr()` allows for more flexible parameter and return types, but still returns a **raw pointer** when creating an object.
- Provide **wrapper** functions or classes to handle complex pointer logic


## TODOs

- Distinguish between "JavaScript interfaces exported according to the original API" and "JavaScript interfaces exported with encapsulated specialized functionalities".
- V2: In version 2, use functions (MACROs) to generate emscripten bindings to reduce redundancy
- V3: In version 3, use clang's ast related api to parse C++ source code then generate emscripten bindings

### FIXME: WASM DEBUGGING

Data from JS/TS will be corrupted in DEBUG mode.

### FIXME: Cannot convert a BigInt value to a number

There were some change to the `memory64` spec relatively recently. You'll need set `NODE_JS` in your emscripten config use `node 24`, see [issue #24620](https://github.com/emscripten-core/emscripten/issues/24620).

Run `vi "${EMSDK}/.emscripten"`, then change the `NODE_JS` to `node 24`:

```txt
import os
emsdk_path = os.path.dirname(os.getenv('EM_CONFIG')).replace('\\', '/')
#NODE_JS = emsdk_path + '/node/22.16.0_64bit/bin/node'
NODE_JS = '/home/zzz/.nvm/versions/node/v24.3.0/bin/node'
LLVM_ROOT = emsdk_path + '/upstream/bin'
BINARYEN_ROOT = emsdk_path + '/upstream'
EMSCRIPTEN_ROOT = emsdk_path + '/upstream/emscripten'
```

### FIXME: The `--emit-tsd` option generated TypeScript type for the args parameter of the `ccall` function should use `IArguments` instead of `Arguments`

[REF](https://github.com/emscripten-core/emscripten/issues/24579)


## Reference & Pointer

When binding a class with Embind, every C++ instance of that class gets a JS “wrapper object” (an `Module.Mesh`). Whether the C++ signature is


```cpp
void foo(const Mesh* mesh);
```

or

```cpp
void foo(const Mesh& mesh);
```

in JS, we should always just pass the same wrapper:

```js
// create or receive a Mesh instance
let mesh = new Module.Mesh();        // or obtained from a C++ call

// call a bound method that takes `Mesh*` or `Mesh&`:
someBinder.foo(mesh);
```

Embind will automatically unwrap that `Module.Mesh` into either a `Mesh*` or a `Mesh&` as needed.

If the binding uses raw pointers, be sure `allow_raw_pointers` is added:

```cpp
.function("foo", &MyClass::foo, allow_raw_pointers())
```

so that JS can also do:

```js
someBinder.foo(null);    // passes a nullptr for `Mesh*`
```

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

## Differences between `static_cast` and `reinterpret_cast`

### **static_cast**

**Purpose: Safe type conversion**  
- Performs compile-time checks for conversion validity  
- Executes any necessary value conversions  
- Preserves the semantic meaning of the data  

**Example:**
```cpp
EdgeId edgeId(42);
int value = static_cast<int>(edgeId);  // Calls EdgeId’s operator int()
// Actually invokes EdgeId::operator ValueType() const { return id_; }
```

**Characteristics:**  
- May invoke user-defined conversion operators or constructors  
- Can change the representation of the data  
- Compiler ensures the conversion is legal  
- Relatively safe  

### **reinterpret_cast**

**Purpose: Reinterpret the bit pattern in memory**  
- Does no actual conversion, only changes how the compiler interprets the bits  
- Performs no safety checks  
- Operates directly on raw memory  

**Example:**
```cpp
std::vector<EdgeId> edges = {EdgeId(1), EdgeId(2), EdgeId(3)};
const int* intPtr = reinterpret_cast<const int*>(edges.data());
// Reinterprets EdgeId* as int* with no actual conversion
```

**Characteristics:**  
- Zero overhead; calls no functions  
- Only changes the pointer/reference type  
- Not guaranteed to be safe  
- Requires that source and target types share the same memory layout  

### **Usage**

**EdgeId conversions:**
```cpp
// static_cast – invokes user-defined conversion
int value = static_cast<int>(edgeId);  // Calls operator ValueType()

// reinterpret_cast – directly reinterprets memory (for arrays)
const int* data = reinterpret_cast<const int*>(edges.data());
```

## Performance Compare

TODO

## Differences between pointers

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
