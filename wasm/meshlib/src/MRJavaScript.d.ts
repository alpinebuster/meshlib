// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
declare namespace RuntimeExports {
    /**
     * @param {string|null=} returnType
     * @param {Array=} argTypes
     * @param {Array=} args
     * @param {Object=} opts
     */
    function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: any[] | undefined, opts?: any | undefined): any;
    let HEAPU8: any;
    namespace FS {
        export let root: any;
        export let mounts: any[];
        export let devices: {};
        export let streams: any[];
        export let nextInode: number;
        export let nameTable: any;
        export let currentPath: string;
        export let initialized: boolean;
        export let ignorePermissions: boolean;
        export let filesystems: any;
        export let syncFSRequests: number;
        export let readFiles: {};
        export { ErrnoError };
        export { FSStream };
        export { FSNode };
        export function lookupPath(path: any, opts?: {}): {
            path: string;
            node?: undefined;
        } | {
            path: string;
            node: any;
        };
        export function getPath(node: any): any;
        export function hashName(parentid: any, name: any): number;
        export function hashAddNode(node: any): void;
        export function hashRemoveNode(node: any): void;
        export function lookupNode(parent: any, name: any): any;
        export function createNode(parent: any, name: any, mode: any, rdev: any): any;
        export function destroyNode(node: any): void;
        export function isRoot(node: any): boolean;
        export function isMountpoint(node: any): boolean;
        export function isFile(mode: any): boolean;
        export function isDir(mode: any): boolean;
        export function isLink(mode: any): boolean;
        export function isChrdev(mode: any): boolean;
        export function isBlkdev(mode: any): boolean;
        export function isFIFO(mode: any): boolean;
        export function isSocket(mode: any): boolean;
        export function flagsToPermissionString(flag: any): string;
        export function nodePermissions(node: any, perms: any): 0 | 2;
        export function mayLookup(dir: any): any;
        export function mayCreate(dir: any, name: any): any;
        export function mayDelete(dir: any, name: any, isdir: any): any;
        export function mayOpen(node: any, flags: any): any;
        export function checkOpExists(op: any, err: any): any;
        export let MAX_OPEN_FDS: number;
        export function nextfd(): number;
        export function getStreamChecked(fd: any): any;
        export function getStream(fd: any): any;
        export function createStream(stream: any, fd?: number): any;
        export function closeStream(fd: any): void;
        export function dupStream(origStream: any, fd?: number): any;
        export function doSetAttr(stream: any, node: any, attr: any): void;
        export namespace chrdev_stream_ops {
            function open(stream: any): void;
            function llseek(): never;
        }
        export function major(dev: any): number;
        export function minor(dev: any): number;
        export function makedev(ma: any, mi: any): number;
        export function registerDevice(dev: any, ops: any): void;
        export function getDevice(dev: any): any;
        export function getMounts(mount: any): any[];
        export function syncfs(populate: any, callback: any): void;
        export function mount(type: any, opts: any, mountpoint: any): any;
        export function unmount(mountpoint: any): void;
        export function lookup(parent: any, name: any): any;
        export function mknod(path: any, mode: any, dev: any): any;
        export function statfs(path: any): any;
        export function statfsStream(stream: any): any;
        export function statfsNode(node: any): {
            bsize: number;
            frsize: number;
            blocks: number;
            bfree: number;
            bavail: number;
            files: any;
            ffree: number;
            fsid: number;
            flags: number;
            namelen: number;
        };
        export function create(path: any, mode?: number): any;
        export function mkdir(path: any, mode?: number): any;
        export function mkdirTree(path: any, mode: any): void;
        export function mkdev(path: any, mode: any, dev: any): any;
        export function symlink(oldpath: any, newpath: any): any;
        export function rename(old_path: any, new_path: any): void;
        export function rmdir(path: any): void;
        export function readdir(path: any): any;
        export function unlink(path: any): void;
        export function readlink(path: any): any;
        export function stat(path: any, dontFollow: any): any;
        export function fstat(fd: any): any;
        export function lstat(path: any): any;
        export function doChmod(stream: any, node: any, mode: any, dontFollow: any): void;
        export function chmod(path: any, mode: any, dontFollow: any): void;
        export function lchmod(path: any, mode: any): void;
        export function fchmod(fd: any, mode: any): void;
        export function doChown(stream: any, node: any, dontFollow: any): void;
        export function chown(path: any, uid: any, gid: any, dontFollow: any): void;
        export function lchown(path: any, uid: any, gid: any): void;
        export function fchown(fd: any, uid: any, gid: any): void;
        export function doTruncate(stream: any, node: any, len: any): void;
        export function truncate(path: any, len: any): void;
        export function ftruncate(fd: any, len: any): void;
        export function utime(path: any, atime: any, mtime: any): void;
        export function open(path: any, flags: any, mode?: number): any;
        export function close(stream: any): void;
        export function isClosed(stream: any): boolean;
        export function llseek(stream: any, offset: any, whence: any): any;
        export function read(stream: any, buffer: any, offset: any, length: any, position: any): any;
        export function write(stream: any, buffer: any, offset: any, length: any, position: any, canOwn: any): any;
        export function mmap(stream: any, length: any, position: any, prot: any, flags: any): any;
        export function msync(stream: any, buffer: any, offset: any, length: any, mmapFlags: any): any;
        export function ioctl(stream: any, cmd: any, arg: any): any;
        export function readFile(path: any, opts?: {}): Uint8Array<any>;
        export function writeFile(path: any, data: any, opts?: {}): void;
        export function cwd(): any;
        export function chdir(path: any): void;
        export function createDefaultDirectories(): void;
        export function createDefaultDevices(): void;
        export function createSpecialDirectories(): void;
        export function createStandardStreams(input: any, output: any, error: any): void;
        export function staticInit(): void;
        export function init(input: any, output: any, error: any): void;
        export function quit(): void;
        export function findObject(path: any, dontResolveLastLink: any): any;
        export function analyzePath(path: any, dontResolveLastLink: any): {
            isRoot: boolean;
            exists: boolean;
            error: number;
            name: any;
            path: any;
            object: any;
            parentExists: boolean;
            parentPath: any;
            parentObject: any;
        };
        export function createPath(parent: any, path: any, canRead: any, canWrite: any): any;
        export function createFile(parent: any, name: any, properties: any, canRead: any, canWrite: any): any;
        export function createDataFile(parent: any, name: any, data: any, canRead: any, canWrite: any, canOwn: any): void;
        export function createDevice(parent: any, name: any, input: any, output: any): any;
        export function forceLoadFile(obj: any): boolean;
        export function createLazyFile(parent: any, name: any, url: any, canRead: any, canWrite: any): any;
    }
}
declare class ErrnoError {
    constructor(errno: any);
    name: string;
    errno: any;
}
declare class FSStream {
    shared: {};
    set object(val: any);
    get object(): any;
    node: any;
    get isRead(): boolean;
    get isWrite(): boolean;
    get isAppend(): number;
    set flags(val: any);
    get flags(): any;
    set position(val: any);
    get position(): any;
}
declare class FSNode {
    constructor(parent: any, name: any, mode: any, rdev: any);
    node_ops: {};
    stream_ops: {};
    readMode: number;
    writeMode: number;
    mounted: any;
    parent: any;
    mount: any;
    id: number;
    name: any;
    mode: any;
    rdev: any;
    atime: number;
    mtime: number;
    ctime: number;
    set read(val: boolean);
    get read(): boolean;
    set write(val: boolean);
    get write(): boolean;
    get isFolder(): any;
    get isDevice(): any;
}
interface WasmModule {
  _malloc(_0: number): number;
  _printtt(): void;
  _free(_0: number): void;
}

type EmbindString = ArrayBuffer|Uint8Array|Uint8ClampedArray|Int8Array|string;
export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  // @ts-ignore - If targeting lower than ESNext, this symbol might not exist.
  [Symbol.dispose](): void;
  clone(): this;
}
export interface Box2f extends ClassHandle {
  min: Vector2f;
  max: Vector2f;
  valid(): boolean;
  diagonal(): number;
  volume(): number;
  includeBox(_0: Box2f): void;
  containsBox(_0: Box2f): boolean;
  intersects(_0: Box2f): boolean;
  intersection(_0: Box2f): Box2f;
  intersect(_0: Box2f): Box2f;
  getDistanceSqToBox(_0: Box2f): number;
  insignificantlyExpanded(): Box2f;
  center(): Vector2f;
  size(): Vector2f;
  include(_0: Vector2f): void;
  contains(_0: Vector2f): boolean;
  getBoxClosestPointTo(_0: Vector2f): Vector2f;
  getDistanceSqToPoint(_0: Vector2f): number;
  expanded(_0: Vector2f): Box2f;
  corner(_0: Vector2b): Vector2f;
}

export interface Box3f extends ClassHandle {
  min: Vector3f;
  max: Vector3f;
  valid(): boolean;
  diagonal(): number;
  volume(): number;
  includeBox(_0: Box3f): void;
  containsBox(_0: Box3f): boolean;
  intersects(_0: Box3f): boolean;
  intersection(_0: Box3f): Box3f;
  intersect(_0: Box3f): Box3f;
  getDistanceSqToBox(_0: Box3f): number;
  insignificantlyExpanded(): Box3f;
  center(): Vector3f;
  size(): Vector3f;
  include(_0: Vector3f): void;
  contains(_0: Vector3f): boolean;
  getBoxClosestPointTo(_0: Vector3f): Vector3f;
  getDistanceSqToPoint(_0: Vector3f): number;
  expanded(_0: Vector3f): Box3f;
  corner(_0: Vector3b): Vector3f;
}

export interface Color extends ClassHandle {
  r: number;
  g: number;
  b: number;
  a: number;
  getUInt32(): number;
  scaledAlpha(_0: number): Color;
  get(_0: number): number;
  set(_0: number): number;
}

export interface StdVectorf extends ClassHandle {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export interface MyClass extends ClassHandle {
  x: number;
  readonly x_readonly: number;
  incrementX(): void;
}

export interface Mesh extends ClassHandle {
  signedDistance(_0: Vector3f): number;
}

export interface MeshWrapper extends ClassHandle {
  getBoundingBox(): any;
  getVertexCount(): number;
  getFaceCount(): number;
  getVolume(): number;
  getArea(): number;
  findCenter(): any;
  getVertexPosition(_0: number): any;
  setVertexPosition(_0: number, _1: any): void;
  getFaceVertices(_0: number): any;
  getFaceNormal(_0: number): any;
  fillHoles(): any;
  projectPoint(_0: any, _1: number): any;
  transform(_0: any): void;
  pack(): void;
}

export type NoInit = {

};

export interface UndirectedEdgeId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: UndirectedEdgeId): boolean;
  notEquals(_0: UndirectedEdgeId): boolean;
  lessThan(_0: UndirectedEdgeId): boolean;
  increment(): UndirectedEdgeId;
  decrement(): UndirectedEdgeId;
  incrementByInt(_0: number): UndirectedEdgeId;
  decrementByInt(_0: number): UndirectedEdgeId;
}

export interface EdgeId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  sym(): EdgeId;
  even(): boolean;
  odd(): boolean;
  undirected(): UndirectedEdgeId;
  toUndirected(): UndirectedEdgeId;
  equals(_0: EdgeId): boolean;
  notEquals(_0: EdgeId): boolean;
  lessThan(_0: EdgeId): boolean;
  increment(): EdgeId;
  decrement(): EdgeId;
  incrementByInt(_0: number): EdgeId;
  decrementByInt(_0: number): EdgeId;
}

export interface FaceId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: FaceId): boolean;
  notEquals(_0: FaceId): boolean;
  lessThan(_0: FaceId): boolean;
  increment(): FaceId;
  decrement(): FaceId;
  incrementByInt(_0: number): FaceId;
  decrementByInt(_0: number): FaceId;
}

export interface VertId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: VertId): boolean;
  notEquals(_0: VertId): boolean;
  lessThan(_0: VertId): boolean;
  increment(): VertId;
  decrement(): VertId;
  incrementByInt(_0: number): VertId;
  decrementByInt(_0: number): VertId;
}

export interface MeshLoadWrapper extends ClassHandle {
}

export interface Vectori extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  get(_0: number): number;
  set(_0: number): number;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: number): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: number): void;
  autoResizeAt(_0: number): number;
  autoResizeSet(_0: number, _1: number): void;
  pushBack(_0: number): void;
  popBack(): void;
  front(): number;
  back(): number;
  beginId(): number;
  backId(): number;
  endId(): number;
  capacity(): number;
  reserve(_0: number): void;
  heapBytes(): number;
  equals(_0: Vectori): boolean;
  notEquals(_0: Vectori): boolean;
  getData(): any;
  getDataConst(): any;
}

export interface Vectorf extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  get(_0: number): number;
  set(_0: number): number;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: number): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: number): void;
  autoResizeAt(_0: number): number;
  autoResizeSet(_0: number, _1: number): void;
  pushBack(_0: number): void;
  popBack(): void;
  front(): number;
  back(): number;
  beginId(): number;
  backId(): number;
  endId(): number;
  capacity(): number;
  reserve(_0: number): void;
  heapBytes(): number;
  equals(_0: Vectorf): boolean;
  notEquals(_0: Vectorf): boolean;
  getData(): any;
  getDataConst(): any;
}

export interface Vector2f extends ClassHandle {
  x: number;
  y: number;
  length(): number;
  lengthSq(): number;
  normalized(): Vector2f;
  perpendicular(): Vector2f;
  isFinite(): boolean;
  furthestBasisVector(): Vector2f;
  get(_0: number): number;
  set(_0: number): number;
}

export interface Vector2i extends ClassHandle {
  x: number;
  y: number;
  length(): number;
  lengthSq(): number;
  perpendicular(): Vector2i;
  furthestBasisVector(): Vector2i;
  get(_0: number): number;
  set(_0: number): number;
}

export interface Vector2b extends ClassHandle {
  x: boolean;
  y: boolean;
  length(): number;
  lengthSq(): boolean;
  get(_0: number): boolean;
  set(_0: number): boolean;
}

export interface Vector3f extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3f;
  furthestBasisVector(): Vector3f;
  unsignZeroValues(): void;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
  perpendicular(): Vector3fPair;
}

export type Vector3fPair = [ Vector3f, Vector3f ];

export interface Vector3i extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3f;
  furthestBasisVector(): Vector3i;
  perpendicular(): Vector3fPair;
  unsignZeroValues(): Vector3f;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
}

export type Vector3iPair = [ Vector3i, Vector3i ];

export interface Vector3d extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3d;
  furthestBasisVector(): Vector3d;
  unsignZeroValues(): void;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
  perpendicular(): Vector3DPair;
}

export type Vector3DPair = [ Vector3d, Vector3d ];

export interface Vector3ll extends ClassHandle {
  x: bigint;
  y: bigint;
  z: bigint;
  lengthSq(): bigint;
  length(): number;
  normalized(): Vector3f;
  furthestBasisVector(): Vector3ll;
  perpendicular(): Vector3fPair;
  unsignZeroValues(): Vector3f;
  isFinite(): boolean;
  get(_0: number): bigint;
  set(_0: number): bigint;
}

export type Vector3llPair = [ Vector3ll, Vector3ll ];

export interface Vector3b extends ClassHandle {
  x: boolean;
  y: boolean;
  z: boolean;
  lengthSq(): boolean;
  length(): number;
  get(_0: number): boolean;
  set(_0: number): boolean;
}

export type Vector3bPair = [ Vector3b, Vector3b ];

export interface Vector4f extends ClassHandle {
  x: number;
  y: number;
  z: number;
  w: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector4f;
  proj3d(): Vector3f;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
}

export interface Vector4i extends ClassHandle {
  x: number;
  y: number;
  z: number;
  w: number;
  lengthSq(): number;
  get(_0: number): number;
  set(_0: number): number;
}

interface EmbindModule {
  Box2f: {
    new(): Box2f;
    new(_0: Vector2f, _1: Vector2f): Box2f;
    fromMinAndSize(_0: Vector2f, _1: Vector2f): Box2f;
    getMinBoxCorner(_0: Vector2f): Vector2b;
    getMaxBoxCorner(_0: Vector2f): Vector2b;
  };
  Box3f: {
    new(): Box3f;
    new(_0: Vector3f, _1: Vector3f): Box3f;
    fromMinAndSize(_0: Vector3f, _1: Vector3f): Box3f;
    getMinBoxCorner(_0: Vector3f): Vector3b;
    getMaxBoxCorner(_0: Vector3f): Vector3b;
  };
  Color: {
    new(): Color;
    new(_0: number, _1: number, _2: number): Color;
    new(_0: number, _1: number, _2: number, _3: number): Color;
    new(_0: Vector4i): Color;
    white(): Color;
    black(): Color;
    gray(): Color;
    red(): Color;
    green(): Color;
    blue(): Color;
    yellow(): Color;
    brown(): Color;
    purple(): Color;
    transparent(): Color;
    fromVector3I(_0: Vector3i): Color;
    fromVector4I(_0: Vector4i): Color;
  };
  ColorAdd(_0: Color, _1: Color): Color;
  ColorSub(_0: Color, _1: Color): Color;
  ColorMul(_0: number, _1: Color): Color;
  ColorMulRev(_0: Color, _1: number): Color;
  ColorDiv(_0: Color, _1: number): Color;
  ColorBlend(_0: Color, _1: Color): Color;
  StdVectorf: {
    new(): StdVectorf;
  };
  lerp(_0: number, _1: number, _2: number): number;
  MyClass: {
    new(_0: number, _1: EmbindString): MyClass;
    getStringFromInstance(_0: MyClass): string;
  };
  Mesh: {
    new(): Mesh;
  };
  cutMeshWithPolyline(_0: Mesh, _1: StdVectorf, _2: number): any;
  computeVertexNormals(_0: Mesh): any;
  MeshWrapper: {
    new(): MeshWrapper;
    new(_0: Mesh): MeshWrapper;
    fromTriangles(_0: any, _1: any): any;
  };
  noInit: NoInit;
  UndirectedEdgeId: {
    new(): UndirectedEdgeId;
    new(_0: number): UndirectedEdgeId;
  };
  EdgeId: {
    new(): EdgeId;
    new(_0: number): EdgeId;
    fromUndirected(_0: UndirectedEdgeId): EdgeId;
  };
  FaceId: {
    new(): FaceId;
    new(_0: number): FaceId;
  };
  VertId: {
    new(): VertId;
    new(_0: number): VertId;
  };
  MeshLoadWrapper: {
    fromFile(_0: EmbindString): any;
    fromBinaryData(_0: number, _1: number, _2: EmbindString): any;
  };
  Vectori: {
    new(): Vectori;
    new(_0: number): Vectori;
    new(_0: number, _1: number): Vectori;
  };
  Vectorf: {
    new(): Vectorf;
    new(_0: number): Vectorf;
    new(_0: number, _1: number): Vectorf;
  };
  getAti(_0: Vectori, _1: number, _2: number): number;
  getAtf(_0: Vectorf, _1: number, _2: number): number;
  Vector2f: {
    new(): Vector2f;
    new(_0: number, _1: number): Vector2f;
    new(_0: Vector2f): Vector2f;
    diagonal(_0: number): Vector2f;
    plusX(): Vector2f;
    plusY(): Vector2f;
    minusX(): Vector2f;
    minusY(): Vector2f;
  };
  Vector2i: {
    new(): Vector2i;
    new(_0: number, _1: number): Vector2i;
    new(_0: Vector2i): Vector2i;
    diagonal(_0: number): Vector2i;
    plusX(): Vector2i;
    plusY(): Vector2i;
    minusX(): Vector2i;
    minusY(): Vector2i;
  };
  Vector2b: {
    new(): Vector2b;
    new(_0: boolean, _1: boolean): Vector2b;
    new(_0: Vector2b): Vector2b;
    diagonal(_0: boolean): Vector2b;
    plusX(): Vector2b;
    plusY(): Vector2b;
    minusX(): Vector2b;
    minusY(): Vector2b;
  };
  Vector3f: {
    new(): Vector3f;
    new(_0: number, _1: number, _2: number): Vector3f;
    diagonal(_0: number): Vector3f;
    plusX(): Vector3f;
    plusY(): Vector3f;
    plusZ(): Vector3f;
    minusX(): Vector3f;
    minusY(): Vector3f;
    minusZ(): Vector3f;
  };
  distanceSqf(_0: Vector3f, _1: Vector3f): number;
  distancef(_0: Vector3f, _1: Vector3f): number;
  crossf(_0: Vector3f, _1: Vector3f): Vector3f;
  dotf(_0: Vector3f, _1: Vector3f): number;
  sqrf(_0: Vector3f): number;
  mixedf(_0: Vector3f, _1: Vector3f, _2: Vector3f): number;
  multf(_0: Vector3f, _1: Vector3f): Vector3f;
  divf(_0: Vector3f, _1: Vector3f): Vector3f;
  anglef(_0: Vector3f, _1: Vector3f): number;
  unitVector3f(_0: number, _1: number): Vector3f;
  Vector3i: {
    new(): Vector3i;
    new(_0: number, _1: number, _2: number): Vector3i;
    diagonal(_0: number): Vector3i;
    plusX(): Vector3i;
    plusY(): Vector3i;
    plusZ(): Vector3i;
    minusX(): Vector3i;
    minusY(): Vector3i;
    minusZ(): Vector3i;
  };
  distanceSqi(_0: Vector3i, _1: Vector3i): number;
  sqri(_0: Vector3i): number;
  crossi(_0: Vector3i, _1: Vector3i): Vector3i;
  doti(_0: Vector3i, _1: Vector3i): number;
  mixedi(_0: Vector3i, _1: Vector3i, _2: Vector3i): number;
  multi(_0: Vector3i, _1: Vector3i): Vector3i;
  divi(_0: Vector3i, _1: Vector3i): Vector3i;
  anglei(_0: Vector3i, _1: Vector3i): number;
  unitVector3i(_0: number, _1: number): Vector3i;
  Vector3d: {
    new(): Vector3d;
    new(_0: number, _1: number, _2: number): Vector3d;
    diagonal(_0: number): Vector3d;
    plusX(): Vector3d;
    plusY(): Vector3d;
    plusZ(): Vector3d;
    minusX(): Vector3d;
    minusY(): Vector3d;
    minusZ(): Vector3d;
  };
  distanceSqd(_0: Vector3d, _1: Vector3d): number;
  distanced(_0: Vector3d, _1: Vector3d): number;
  crossd(_0: Vector3d, _1: Vector3d): Vector3d;
  dotd(_0: Vector3d, _1: Vector3d): number;
  sqrd(_0: Vector3d): number;
  mixedd(_0: Vector3d, _1: Vector3d, _2: Vector3d): number;
  multd(_0: Vector3d, _1: Vector3d): Vector3d;
  divd(_0: Vector3d, _1: Vector3d): Vector3d;
  angled(_0: Vector3d, _1: Vector3d): number;
  unitVector3d(_0: number, _1: number): Vector3d;
  Vector3ll: {
    new(): Vector3ll;
    new(_0: bigint, _1: bigint, _2: bigint): Vector3ll;
    diagonal(_0: bigint): Vector3ll;
    plusX(): Vector3ll;
    plusY(): Vector3ll;
    plusZ(): Vector3ll;
    minusX(): Vector3ll;
    minusY(): Vector3ll;
    minusZ(): Vector3ll;
  };
  distanceSqll(_0: Vector3ll, _1: Vector3ll): bigint;
  distancell(_0: Vector3ll, _1: Vector3ll): bigint;
  crossll(_0: Vector3ll, _1: Vector3ll): Vector3ll;
  dotll(_0: Vector3ll, _1: Vector3ll): bigint;
  sqrll(_0: Vector3ll): bigint;
  mixedll(_0: Vector3ll, _1: Vector3ll, _2: Vector3ll): bigint;
  multll(_0: Vector3ll, _1: Vector3ll): Vector3ll;
  divll(_0: Vector3ll, _1: Vector3ll): Vector3ll;
  anglell(_0: Vector3ll, _1: Vector3ll): bigint;
  unitVector3ll(_0: bigint, _1: bigint): Vector3d;
  Vector3b: {
    new(): Vector3b;
    new(_0: boolean, _1: boolean, _2: boolean): Vector3b;
    diagonal(_0: boolean): Vector3b;
    plusX(): Vector3b;
    plusY(): Vector3b;
    plusZ(): Vector3b;
    minusX(): Vector3b;
    minusY(): Vector3b;
    minusZ(): Vector3b;
  };
  distanceSqb(_0: Vector3b, _1: Vector3b): boolean;
  sqrb(_0: Vector3b): boolean;
  Vector4f: {
    new(): Vector4f;
    new(_0: number, _1: number, _2: number, _3: number): Vector4f;
    diagonal(_0: number): Vector4f;
  };
  distanceSq4f(_0: Vector4f, _1: Vector4f): number;
  distance4f(_0: Vector4f, _1: Vector4f): number;
  dot4f(_0: Vector4f, _1: Vector4f): number;
  sqr4f(_0: Vector4f): number;
  mult4f(_0: Vector4f, _1: Vector4f): Vector4f;
  div4f(_0: Vector4f, _1: Vector4f): Vector4f;
  Vector4i: {
    new(): Vector4i;
    new(_0: number, _1: number, _2: number, _3: number): Vector4i;
    diagonal(_0: number): Vector4i;
  };
  distanceSq4i(_0: Vector4i, _1: Vector4i): number;
  distance4i(_0: Vector4i, _1: Vector4i): number;
  dot4i(_0: Vector4i, _1: Vector4i): number;
  sqr4i(_0: Vector4i): number;
  mult4i(_0: Vector4i, _1: Vector4i): Vector4i;
  div4i(_0: Vector4i, _1: Vector4i): Vector4i;
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
