// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
declare namespace RuntimeExports {
    /**
     * @param {string|null=} returnType
     * @param {Array=} argTypes
     * @param {Arguments|Array=} args
     * @param {Object=} opts
     */
    function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: (IArguments|any[]) | undefined, opts?: any | undefined): any;
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
        export function readFile(path: any, opts?: {}): any;
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
  _printtt(): void;
  _malloc(_0: number): number;
  _free(_0: number): void;
  _emsGetPointerSize(): number;
}

type EmbindString = ArrayBuffer|Uint8Array|Uint8ClampedArray|Int8Array|string;
export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  clone(): this;
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

export interface MyClass extends ClassHandle {
  x: number;
  readonly x_readonly: number;
  incrementX(): void;
}

export interface Mesh extends ClassHandle {
  signedDistance(_0: Vector3F): number;
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

export interface Vector3F extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3F;
  furthestBasisVector(): Vector3F;
  unsignZeroValues(): void;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
  perpendicular(): Vector3FPair;
}

export type Vector3FPair = [ Vector3F, Vector3F ];

export interface Vector3I extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3F;
  furthestBasisVector(): Vector3I;
  perpendicular(): Vector3FPair;
  unsignZeroValues(): Vector3F;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
}

export type Vector3IPair = [ Vector3I, Vector3I ];

export interface Vector3D extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3D;
  furthestBasisVector(): Vector3D;
  unsignZeroValues(): void;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
  perpendicular(): Vector3DPair;
}

export type Vector3DPair = [ Vector3D, Vector3D ];

export interface Vector3LL extends ClassHandle {
  x: bigint;
  y: bigint;
  z: bigint;
  lengthSq(): bigint;
  length(): number;
  normalized(): Vector3F;
  furthestBasisVector(): Vector3LL;
  perpendicular(): Vector3FPair;
  unsignZeroValues(): Vector3F;
  isFinite(): boolean;
  get(_0: number): bigint;
  set(_0: number): bigint;
}

export type Vector3LLPair = [ Vector3LL, Vector3LL ];

export interface Vector4F extends ClassHandle {
  x: number;
  y: number;
  z: number;
  w: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector4F;
  proj3d(): Vector3F;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
}

export interface Vector4I extends ClassHandle {
  x: number;
  y: number;
  z: number;
  w: number;
  lengthSq(): number;
  get(_0: number): number;
  set(_0: number): number;
}

interface EmbindModule {
  Color: {
    new(): Color;
    new(_0: number, _1: number, _2: number): Color;
    new(_0: number, _1: number, _2: number, _3: number): Color;
    new(_0: Vector4I): Color;
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
    fromVector3I(_0: Vector3I): Color;
    fromVector4I(_0: Vector4I): Color;
  };
  ColorAdd(_0: Color, _1: Color): Color;
  ColorSub(_0: Color, _1: Color): Color;
  ColorMul(_0: number, _1: Color): Color;
  ColorMulRev(_0: Color, _1: number): Color;
  ColorDiv(_0: Color, _1: number): Color;
  ColorBlend(_0: Color, _1: Color): Color;
  lerp(_0: number, _1: number, _2: number): number;
  MyClass: {
    new(_0: number, _1: EmbindString): MyClass;
    getStringFromInstance(_0: MyClass): string;
  };
  Mesh: {
    new(): Mesh;
  };
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
  Vector3F: {
    new(): Vector3F;
    new(_0: number, _1: number, _2: number): Vector3F;
    diagonal(_0: number): Vector3F;
    plusX(): Vector3F;
    plusY(): Vector3F;
    plusZ(): Vector3F;
    minusX(): Vector3F;
    minusY(): Vector3F;
    minusZ(): Vector3F;
  };
  distanceSqF(_0: Vector3F, _1: Vector3F): number;
  distanceF(_0: Vector3F, _1: Vector3F): number;
  crossF(_0: Vector3F, _1: Vector3F): Vector3F;
  dotF(_0: Vector3F, _1: Vector3F): number;
  sqrF(_0: Vector3F): number;
  mixedF(_0: Vector3F, _1: Vector3F, _2: Vector3F): number;
  multF(_0: Vector3F, _1: Vector3F): Vector3F;
  divF(_0: Vector3F, _1: Vector3F): Vector3F;
  angleF(_0: Vector3F, _1: Vector3F): number;
  unitVector3F(_0: number, _1: number): Vector3F;
  Vector3I: {
    new(): Vector3I;
    new(_0: number, _1: number, _2: number): Vector3I;
    diagonal(_0: number): Vector3I;
    plusX(): Vector3I;
    plusY(): Vector3I;
    plusZ(): Vector3I;
    minusX(): Vector3I;
    minusY(): Vector3I;
    minusZ(): Vector3I;
  };
  distanceSqI(_0: Vector3I, _1: Vector3I): number;
  sqrI(_0: Vector3I): number;
  crossI(_0: Vector3I, _1: Vector3I): Vector3I;
  dotI(_0: Vector3I, _1: Vector3I): number;
  mixedI(_0: Vector3I, _1: Vector3I, _2: Vector3I): number;
  multI(_0: Vector3I, _1: Vector3I): Vector3I;
  divI(_0: Vector3I, _1: Vector3I): Vector3I;
  angleI(_0: Vector3I, _1: Vector3I): number;
  unitVector3I(_0: number, _1: number): Vector3I;
  Vector3D: {
    new(): Vector3D;
    new(_0: number, _1: number, _2: number): Vector3D;
    diagonal(_0: number): Vector3D;
    plusX(): Vector3D;
    plusY(): Vector3D;
    plusZ(): Vector3D;
    minusX(): Vector3D;
    minusY(): Vector3D;
    minusZ(): Vector3D;
  };
  distanceSqD(_0: Vector3D, _1: Vector3D): number;
  distanceD(_0: Vector3D, _1: Vector3D): number;
  crossD(_0: Vector3D, _1: Vector3D): Vector3D;
  dotD(_0: Vector3D, _1: Vector3D): number;
  sqrD(_0: Vector3D): number;
  mixedD(_0: Vector3D, _1: Vector3D, _2: Vector3D): number;
  multD(_0: Vector3D, _1: Vector3D): Vector3D;
  divD(_0: Vector3D, _1: Vector3D): Vector3D;
  angleD(_0: Vector3D, _1: Vector3D): number;
  unitVector3D(_0: number, _1: number): Vector3D;
  Vector3LL: {
    new(): Vector3LL;
    new(_0: bigint, _1: bigint, _2: bigint): Vector3LL;
    diagonal(_0: bigint): Vector3LL;
    plusX(): Vector3LL;
    plusY(): Vector3LL;
    plusZ(): Vector3LL;
    minusX(): Vector3LL;
    minusY(): Vector3LL;
    minusZ(): Vector3LL;
  };
  distanceSqLL(_0: Vector3LL, _1: Vector3LL): bigint;
  distanceLL(_0: Vector3LL, _1: Vector3LL): bigint;
  crossLL(_0: Vector3LL, _1: Vector3LL): Vector3LL;
  dotLL(_0: Vector3LL, _1: Vector3LL): bigint;
  sqrLL(_0: Vector3LL): bigint;
  mixedLL(_0: Vector3LL, _1: Vector3LL, _2: Vector3LL): bigint;
  multLL(_0: Vector3LL, _1: Vector3LL): Vector3LL;
  divLL(_0: Vector3LL, _1: Vector3LL): Vector3LL;
  angleLL(_0: Vector3LL, _1: Vector3LL): bigint;
  unitVector3LL(_0: bigint, _1: bigint): Vector3D;
  Vector4F: {
    new(): Vector4F;
    new(_0: number, _1: number, _2: number, _3: number): Vector4F;
    diagonal(_0: number): Vector4F;
  };
  distanceSq4F(_0: Vector4F, _1: Vector4F): number;
  distance4F(_0: Vector4F, _1: Vector4F): number;
  dot4F(_0: Vector4F, _1: Vector4F): number;
  sqr4F(_0: Vector4F): number;
  mult4F(_0: Vector4F, _1: Vector4F): Vector4F;
  div4F(_0: Vector4F, _1: Vector4F): Vector4F;
  Vector4I: {
    new(): Vector4I;
    new(_0: number, _1: number, _2: number, _3: number): Vector4I;
    diagonal(_0: number): Vector4I;
  };
  distanceSq4I(_0: Vector4I, _1: Vector4I): number;
  distance4I(_0: Vector4I, _1: Vector4I): number;
  dot4I(_0: Vector4I, _1: Vector4I): number;
  sqr4I(_0: Vector4I): number;
  mult4I(_0: Vector4I, _1: Vector4I): Vector4I;
  div4I(_0: Vector4I, _1: Vector4I): Vector4I;
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
