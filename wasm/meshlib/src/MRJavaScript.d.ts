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
export interface AABBTreeObjects extends ClassHandle {
}

export interface VectorAABBTreePointsPoint extends ClassHandle {
  size(): number;
  get(_0: number): AABBTreePointsPoint | undefined;
  push_back(_0: AABBTreePointsPoint): void;
  resize(_0: number, _1: AABBTreePointsPoint): void;
  set(_0: number, _1: AABBTreePointsPoint): boolean;
}

export interface VectorAABBTreePointsNode extends ClassHandle {
  size(): number;
  get(_0: number): AABBTreePointsNode | undefined;
  push_back(_0: AABBTreePointsNode): void;
  resize(_0: number, _1: AABBTreePointsNode): void;
  set(_0: number, _1: AABBTreePointsNode): boolean;
}

export interface AABBTreePointsNode extends ClassHandle {
  box: Box3f;
  l: NodeId;
  r: NodeId;
}

export interface AABBTreePoints extends ClassHandle {
  orderedPoints(): VectorAABBTreePointsPoint;
  getBoundingBox(): Box3f;
  refit(_0: VertCoords, _1: VertBitSet): void;
}

export interface AffineXf2f extends ClassHandle {
  A: Matrix2f;
  b: Vector2f;
  equals(_0: AffineXf2f): boolean;
  notEquals(_0: AffineXf2f): boolean;
  inverse(): AffineXf2f;
  operatorCall(_0: Vector2f): Vector2f;
  linearOnly(_0: Vector2f): Vector2f;
}

export interface AffineXf2d extends ClassHandle {
  A: Matrix2d;
  b: Vector2d;
  equals(_0: AffineXf2d): boolean;
  notEquals(_0: AffineXf2d): boolean;
  inverse(): AffineXf2d;
  operatorCall(_0: Vector2d): Vector2d;
  linearOnly(_0: Vector2d): Vector2d;
}

export interface AffineXf3f extends ClassHandle {
  A: Matrix3f;
  b: Vector3f;
  equals(_0: AffineXf3f): boolean;
  notEquals(_0: AffineXf3f): boolean;
  inverse(): AffineXf3f;
  operatorCall(_0: Vector3f): Vector3f;
  linearOnly(_0: Vector3f): Vector3f;
}

export interface AffineXf3d extends ClassHandle {
  A: Matrix3d;
  b: Vector3d;
  equals(_0: AffineXf3d): boolean;
  notEquals(_0: AffineXf3d): boolean;
  inverse(): AffineXf3d;
  operatorCall(_0: Vector3d): Vector3d;
  linearOnly(_0: Vector3d): Vector3d;
}

export interface AxisValue<T extends number> {
  value: T;
}
export type Axis = AxisValue<0>|AxisValue<1>|AxisValue<2>|AxisValue<3>;

export interface CubicBezierCurve2f extends ClassHandle {
  getPoint(_0: number): Vector2f;
  setPoint(_0: number, _1: Vector2f): void;
}

export interface CubicBezierCurve2d extends ClassHandle {
  getPoint(_0: number): Vector2d;
  setPoint(_0: number, _1: Vector2d): void;
}

export interface CubicBezierCurve3f extends ClassHandle {
  getPoint(_0: number): Vector3f;
  setPoint(_0: number, _1: Vector3f): void;
}

export interface CubicBezierCurve3d extends ClassHandle {
  getPoint(_0: number): Vector3d;
  setPoint(_0: number, _1: Vector3d): void;
}

export interface CubicBezierCurve4f extends ClassHandle {
  getPoint(_0: number): Vector4f;
  setPoint(_0: number, _1: Vector4f): void;
}

export interface CubicBezierCurve4d extends ClassHandle {
  getPoint(_0: number): Vector4d;
  setPoint(_0: number, _1: Vector4d): void;
}

export interface __InternalDynamicBitset extends ClassHandle {
  size(): number;
  count(): number;
  empty(): boolean;
  clear(): void;
  find_first(): number;
  find_next(_0: number): number;
  resize(_0: number, _1: boolean): void;
  push_back(_0: boolean): void;
  pop_back(): void;
}

export interface BitSet extends ClassHandle {
  test(_0: number): boolean;
  set(_0: number, _1: boolean): BitSet;
  setAll(): BitSet;
  setRange(_0: number, _1: number, _2: boolean): BitSet;
  reset(_0: number): BitSet;
  resetAll(): BitSet;
  resetRange(_0: number, _1: number): BitSet;
  flip(_0: number): BitSet;
  flipAll(): BitSet;
  find_last(): number;
  nthSetBit(_0: number): number;
  bitwiseAndAssign(_0: BitSet): BitSet;
  bitwiseOrAssign(_0: BitSet): BitSet;
  bitwiseXorAssign(_0: BitSet): BitSet;
  subtractAssign(_0: BitSet): BitSet;
  subtract(_0: BitSet, _1: number): BitSet;
  autoResizeSet(_0: number, _1: boolean): void;
  autoResizeSetRange(_0: number, _1: number, _2: boolean): void;
  autoResizeTestSet(_0: number, _1: boolean): boolean;
  heapBytes(): number;
  resizeWithReserve(_0: number): void;
  backId(): number;
  endId(): number;
}

export interface FaceBitSet extends ClassHandle {
  copyFrom(_0: BitSet): FaceBitSet;
  moveFrom(_0: BitSet): FaceBitSet;
  testFromInt(_0: number): boolean;
  setAll(): FaceBitSet;
  resetAll(): FaceBitSet;
  flipAll(): FaceBitSet;
  bitwiseAndAssign(_0: FaceBitSet): FaceBitSet;
  bitwiseOrAssign(_0: FaceBitSet): FaceBitSet;
  bitwiseXorAssign(_0: FaceBitSet): FaceBitSet;
  subtractAssign(_0: FaceBitSet): FaceBitSet;
  isSubsetOf(_0: FaceBitSet): boolean;
  isProperSubsetOf(_0: FaceBitSet): boolean;
  intersects(_0: FaceBitSet): boolean;
  test(_0: FaceId): boolean;
  testSet(_0: FaceId, _1: boolean): boolean;
  set(_0: FaceId, _1: boolean): FaceBitSet;
  setRange(_0: FaceId, _1: number, _2: boolean): FaceBitSet;
  reset(_0: FaceId): FaceBitSet;
  resetRange(_0: FaceId, _1: number): FaceBitSet;
  flip(_0: FaceId): FaceBitSet;
  findFirst(): FaceId;
  findNext(_0: FaceId): FaceId;
  findLast(): FaceId;
  nthSetBit(_0: number): FaceId;
  autoResizeSet(_0: FaceId, _1: boolean): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: boolean): void;
  autoResizeTestSet(_0: FaceId, _1: boolean): boolean;
  backId(): FaceId;
  endId(): FaceId;
}

export interface VertBitSet extends ClassHandle {
}

export interface EdgeBitSet extends ClassHandle {
}

export interface UndirectedEdgeBitSet extends ClassHandle {
}

export interface PixelBitSet extends ClassHandle {
}

export interface VoxelBitSet extends ClassHandle {
}

export interface RegionBitSet extends ClassHandle {
}

export interface NodeBitSet extends ClassHandle {
}

export interface ObjBitSet extends ClassHandle {
}

export interface TextureBitSet extends ClassHandle {
}

export interface GraphVertBitSet extends ClassHandle {
}

export interface GraphEdgeBitSet extends ClassHandle {
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
  corner(_0: Vector2b): Vector2f;
  size(): Vector2f;
  include(_0: Vector2f): void;
  contains(_0: Vector2f): boolean;
  getBoxClosestPointTo(_0: Vector2f): Vector2f;
  getDistanceSqToPoint(_0: Vector2f): number;
  expanded(_0: Vector2f): Box2f;
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
  corner(_0: Vector3b): Vector3f;
  size(): Vector3f;
  include(_0: Vector3f): void;
  contains(_0: Vector3f): boolean;
  getBoxClosestPointTo(_0: Vector3f): Vector3f;
  getDistanceSqToPoint(_0: Vector3f): number;
  expanded(_0: Vector3f): Box3f;
}

export interface FaceBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  heapBytes(): number;
  get(_0: FaceId): FaceId;
  set(_0: FaceId, _1: FaceId): void;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  dataPtr(): NoDefInitFaceId | null;
}

export interface VertBMapBuffer extends ClassHandle {
}

export interface EdgeBMapBuffer extends ClassHandle {
}

export interface UndirectedEdgeBMapBuffer extends ClassHandle {
}

export interface WholeEdgeBMapBuffer extends ClassHandle {
}

export interface CloudPartMapping extends ClassHandle {
  src2tgtVerts: VertMap | null;
  tgt2srcVerts: VertMap | null;
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

export interface Dipole extends ClassHandle {
  area: number;
  rr: number;
  pos: Vector3f;
  dirArea: Vector3f;
  addIfGoodApprox(_0: Vector3f, _1: number, _2: number): any;
}

export interface EdgePoint extends ClassHandle {
}

export interface MeshSegmentation extends ClassHandle {
  segmentByPoints(_0: StdVectorf, _1: StdVectorf): any;
}

export interface FixParams extends ClassHandle {
  voxelSize: number;
  bottomExtension: number;
  smooth: boolean;
  findParameters: FindParams;
}

export interface ICP extends ClassHandle {
  setCosineLimit(_0: number): void;
  setDistanceLimit(_0: number): void;
  setBadIterCount(_0: number): void;
  setFarDistFactor(_0: number): void;
  setFltSamples(_0: VertBitSet): void;
  sampleFltPoints(_0: number): void;
  setRefSamples(_0: VertBitSet): void;
  sampleRefPoints(_0: number): void;
  samplePoints(_0: number): void;
  setXfs(_0: AffineXf3f, _1: AffineXf3f): void;
  setFloatXf(_0: AffineXf3f): void;
  autoSelectFloatXf(): AffineXf3f;
  updatePointPairs(): void;
  getStatusInfo(): string;
  getNumSamples(): number;
  getNumActivePairs(): number;
  getMeanSqDistToPoint(): number;
  getMeanSqDistToPlane(): number;
  calculateTransformation(): AffineXf3f;
  setParams(_0: ICPProperties): void;
  getParams(): ICPProperties;
}

export interface ICPMethodValue<T extends number> {
  value: T;
}
export type ICPMethod = ICPMethodValue<0>|ICPMethodValue<1>|ICPMethodValue<2>;

export interface ICPModeValue<T extends number> {
  value: T;
}
export type ICPMode = ICPModeValue<0>|ICPModeValue<1>|ICPModeValue<2>|ICPModeValue<3>|ICPModeValue<4>;

export interface ICPExitTypeValue<T extends number> {
  value: T;
}
export type ICPExitType = ICPExitTypeValue<0>|ICPExitTypeValue<1>|ICPExitTypeValue<2>|ICPExitTypeValue<3>|ICPExitTypeValue<4>;

export interface EdgeHashMapEntries extends ClassHandle {
  size(): number;
  get(_0: number): EdgeIdPair | undefined;
  push_back(_0: EdgeIdPair): void;
  resize(_0: number, _1: EdgeIdPair): void;
  set(_0: number, _1: EdgeIdPair): boolean;
}

export interface UndirectedEdgeHashMapEntries extends ClassHandle {
  size(): number;
  get(_0: number): UndirectedEdgeIdPair | undefined;
  push_back(_0: UndirectedEdgeIdPair): void;
  resize(_0: number, _1: UndirectedEdgeIdPair): void;
  set(_0: number, _1: UndirectedEdgeIdPair): boolean;
}

export interface WholeEdgeHashMapEntries extends ClassHandle {
  size(): number;
  get(_0: number): UndirectedE2EIdPair | undefined;
  push_back(_0: UndirectedE2EIdPair): void;
  resize(_0: number, _1: UndirectedE2EIdPair): void;
  set(_0: number, _1: UndirectedE2EIdPair): boolean;
}

export interface FaceHashMapEntries extends ClassHandle {
  size(): number;
  get(_0: number): FaceIdPair | undefined;
  push_back(_0: FaceIdPair): void;
  resize(_0: number, _1: FaceIdPair): void;
  set(_0: number, _1: FaceIdPair): boolean;
}

export interface VertHashMapEntries extends ClassHandle {
  size(): number;
  get(_0: number): VertIdPair | undefined;
  push_back(_0: VertIdPair): void;
  resize(_0: number, _1: VertIdPair): void;
  set(_0: number, _1: VertIdPair): boolean;
}

export interface VectorEdgeId extends ClassHandle {
  size(): number;
  get(_0: number): EdgeId | undefined;
  push_back(_0: EdgeId): void;
  resize(_0: number, _1: EdgeId): void;
  set(_0: number, _1: EdgeId): boolean;
}

export interface VectorUndirectedEdgeId extends ClassHandle {
  size(): number;
  get(_0: number): UndirectedEdgeId | undefined;
  push_back(_0: UndirectedEdgeId): void;
  resize(_0: number, _1: UndirectedEdgeId): void;
  set(_0: number, _1: UndirectedEdgeId): boolean;
}

export interface VectorFaceId extends ClassHandle {
  size(): number;
  get(_0: number): FaceId | undefined;
  push_back(_0: FaceId): void;
  resize(_0: number, _1: FaceId): void;
  set(_0: number, _1: FaceId): boolean;
}

export interface VectorVertId extends ClassHandle {
  size(): number;
  get(_0: number): VertId | undefined;
  push_back(_0: VertId): void;
  resize(_0: number, _1: VertId): void;
  set(_0: number, _1: VertId): boolean;
}

export interface VectorPixelId extends ClassHandle {
  size(): number;
  get(_0: number): PixelId | undefined;
  push_back(_0: PixelId): void;
  resize(_0: number, _1: PixelId): void;
  set(_0: number, _1: PixelId): boolean;
}

export interface VectorVoxelId extends ClassHandle {
  size(): number;
  get(_0: number): VoxelId | undefined;
  push_back(_0: VoxelId): void;
  resize(_0: number, _1: VoxelId): void;
  set(_0: number, _1: VoxelId): boolean;
}

export interface VectorRegionId extends ClassHandle {
  size(): number;
  get(_0: number): RegionId | undefined;
  push_back(_0: RegionId): void;
  resize(_0: number, _1: RegionId): void;
  set(_0: number, _1: RegionId): boolean;
}

export interface VectorNodeId extends ClassHandle {
  size(): number;
  get(_0: number): NodeId | undefined;
  push_back(_0: NodeId): void;
  resize(_0: number, _1: NodeId): void;
  set(_0: number, _1: NodeId): boolean;
}

export interface VectorObjId extends ClassHandle {
  size(): number;
  get(_0: number): ObjId | undefined;
  push_back(_0: ObjId): void;
  resize(_0: number, _1: ObjId): void;
  set(_0: number, _1: ObjId): boolean;
}

export interface VectorTextureId extends ClassHandle {
  size(): number;
  get(_0: number): TextureId | undefined;
  push_back(_0: TextureId): void;
  resize(_0: number, _1: TextureId): void;
  set(_0: number, _1: TextureId): boolean;
}

export interface VectorGraphVertId extends ClassHandle {
  size(): number;
  get(_0: number): GraphVertId | undefined;
  push_back(_0: GraphVertId): void;
  resize(_0: number, _1: GraphVertId): void;
  set(_0: number, _1: GraphVertId): boolean;
}

export interface VectorGraphEdgeId extends ClassHandle {
  size(): number;
  get(_0: number): GraphEdgeId | undefined;
  push_back(_0: GraphEdgeId): void;
  resize(_0: number, _1: GraphEdgeId): void;
  set(_0: number, _1: GraphEdgeId): boolean;
}

export interface VectorEdgePath extends ClassHandle {
  push_back(_0: VectorEdgeId): void;
  resize(_0: number, _1: VectorEdgeId): void;
  size(): number;
  get(_0: number): VectorEdgeId | undefined;
  set(_0: number, _1: VectorEdgeId): boolean;
}

export interface VectorVectorEdgePath extends ClassHandle {
  push_back(_0: VectorEdgePath): void;
  resize(_0: number, _1: VectorEdgePath): void;
  size(): number;
  get(_0: number): VectorEdgePath | undefined;
  set(_0: number, _1: VectorEdgePath): boolean;
}

export interface MyClass extends ClassHandle {
  x: number;
  readonly x_readonly: number;
  incrementX(): void;
}

export interface Matrix2b extends ClassHandle {
}

export interface Matrix2i extends ClassHandle {
}

export interface Matrix2ll extends ClassHandle {
}

export interface Matrix2f extends ClassHandle {
}

export interface Matrix2d extends ClassHandle {
}

export interface Matrix3b extends ClassHandle {
}

export interface Matrix3i extends ClassHandle {
}

export interface Matrix3ll extends ClassHandle {
}

export interface Matrix3f extends ClassHandle {
}

export interface Matrix3d extends ClassHandle {
}

export interface Matrix4b extends ClassHandle {
}

export interface Matrix4i extends ClassHandle {
}

export interface Matrix4ll extends ClassHandle {
}

export interface Matrix4f extends ClassHandle {
}

export interface Matrix4d extends ClassHandle {
}

export interface Mesh extends ClassHandle {
  signedDistance(_0: Vector3f): number;
}

export interface MeshWrapper extends ClassHandle {
  mesh: Mesh;
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

export interface BooleanOperationValue<T extends number> {
  value: T;
}
export type BooleanOperation = BooleanOperationValue<0>|BooleanOperationValue<1>|BooleanOperationValue<2>|BooleanOperationValue<3>|BooleanOperationValue<4>|BooleanOperationValue<5>|BooleanOperationValue<6>|BooleanOperationValue<7>|BooleanOperationValue<8>;

export interface BooleanResult extends ClassHandle {
  mesh: Mesh;
  meshABadContourFaces: FaceBitSet;
  meshBBadContourFaces: FaceBitSet;
  get errorString(): string;
  set errorString(value: EmbindString);
  valid(): boolean;
  getMesh(): Mesh;
}

export interface __phmap_internal_FlatHashMapPolicy_VertId extends ClassHandle {
}

export interface __phmap_internal_raw_hash_set_VertId extends ClassHandle {
  size(): number;
  clear(): void;
}

export interface __phmap_internal_raw_hash_map_VertId extends ClassHandle {
}

export interface FaceHashMapWrapper extends ClassHandle {
  set(_0: FaceId, _1: FaceId): void;
  get(_0: FaceId): FaceId;
  has(_0: FaceId): boolean;
}

export interface VertHashMap extends ClassHandle {
  keys(): VectorVertId;
  values(): VectorVertId;
  insert(_0: VertId, _1: VertId): void;
  get(_0: VertId): any;
  has(_0: VertId): boolean;
  erase(_0: VertId): void;
}

export interface FaceHashMap extends ClassHandle {
}

export interface EdgeHashMap extends ClassHandle {
}

export interface UndirectedEdgeHashMap extends ClassHandle {
}

export interface WholeEdgeHashMap extends ClassHandle {
}

export interface MakeDegenerateBandAroundRegionParamsWrapper extends ClassHandle {
  setMaxEdgeLength(_0: number): void;
  clearMaxEdgeLength(): void;
  setOutNewFaces(_0: FaceBitSet | null): void;
  getOutNewFaces(): FaceBitSet | null;
  setOutExtrudedEdges(_0: UndirectedEdgeBitSet | null): void;
  getOutExtrudedEdges(): UndirectedEdgeBitSet | null;
  setNew2OldMap(_0: VertHashMap | null): void;
  getNew2OldMap(): VertHashMap | null;
  getMaxEdgeLength(): number | undefined;
}

export interface MakeDegenerateBandAroundRegionParams extends ClassHandle {
  outNewFaces: FaceBitSet | null;
  outExtrudedEdges: UndirectedEdgeBitSet | null;
  new2OldMap: VertHashMap | null;
  getMaxEdgeLength(): number;
  setMaxEdgeLength(_0: number): void;
}

export interface FillHoleParams extends ClassHandle {
  makeDegenerateBand: boolean;
  maxPolygonSubdivisions: number;
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

export type UndirectedEdgeIdPair = [ UndirectedEdgeId, UndirectedEdgeId ];

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

export type EdgeIdPair = [ EdgeId, EdgeId ];

export type UndirectedE2EIdPair = [ UndirectedEdgeId, EdgeId ];

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

export type FaceIdPair = [ FaceId, FaceId ];

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

export type VertIdPair = [ VertId, VertId ];

export interface PixelId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: PixelId): boolean;
  notEquals(_0: PixelId): boolean;
  lessThan(_0: PixelId): boolean;
  increment(): PixelId;
  decrement(): PixelId;
  incrementByInt(_0: number): PixelId;
  decrementByInt(_0: number): PixelId;
}

export interface VoxelId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: VoxelId): boolean;
  notEquals(_0: VoxelId): boolean;
  lessThan(_0: VoxelId): boolean;
  increment(): VoxelId;
  decrement(): VoxelId;
  incrementByInt(_0: number): VoxelId;
  decrementByInt(_0: number): VoxelId;
}

export interface RegionId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: RegionId): boolean;
  notEquals(_0: RegionId): boolean;
  lessThan(_0: RegionId): boolean;
  increment(): RegionId;
  decrement(): RegionId;
  incrementByInt(_0: number): RegionId;
  decrementByInt(_0: number): RegionId;
}

export interface NodeId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: NodeId): boolean;
  notEquals(_0: NodeId): boolean;
  lessThan(_0: NodeId): boolean;
  increment(): NodeId;
  decrement(): NodeId;
  incrementByInt(_0: number): NodeId;
  decrementByInt(_0: number): NodeId;
}

export interface ObjId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: ObjId): boolean;
  notEquals(_0: ObjId): boolean;
  lessThan(_0: ObjId): boolean;
  increment(): ObjId;
  decrement(): ObjId;
  incrementByInt(_0: number): ObjId;
  decrementByInt(_0: number): ObjId;
}

export interface TextureId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: TextureId): boolean;
  notEquals(_0: TextureId): boolean;
  lessThan(_0: TextureId): boolean;
  increment(): TextureId;
  decrement(): TextureId;
  incrementByInt(_0: number): TextureId;
  decrementByInt(_0: number): TextureId;
}

export interface GraphVertId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: GraphVertId): boolean;
  notEquals(_0: GraphVertId): boolean;
  lessThan(_0: GraphVertId): boolean;
  increment(): GraphVertId;
  decrement(): GraphVertId;
  incrementByInt(_0: number): GraphVertId;
  decrementByInt(_0: number): GraphVertId;
}

export interface GraphEdgeId extends ClassHandle {
  valid(): boolean;
  toInt(): number;
  toBool(): boolean;
  get(): number;
  equals(_0: GraphEdgeId): boolean;
  notEquals(_0: GraphEdgeId): boolean;
  lessThan(_0: GraphEdgeId): boolean;
  increment(): GraphEdgeId;
  decrement(): GraphEdgeId;
  incrementByInt(_0: number): GraphEdgeId;
  decrementByInt(_0: number): GraphEdgeId;
}

export interface VertBMap extends ClassHandle {
  tsize: number;
}

export interface FaceBMap extends ClassHandle {
  tsize: number;
}

export interface EdgeBMap extends ClassHandle {
  tsize: number;
}

export interface UndirectedEdgeBMap extends ClassHandle {
  tsize: number;
}

export interface WholeEdgeBMap extends ClassHandle {
  tsize: number;
}

export interface Triangulation extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithReserve(_0: number): void;
  popBack(): void;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  swap(_0: Triangulation): void;
  heapBytes(): number;
  equals(_0: Triangulation): boolean;
  notEquals(_0: Triangulation): boolean;
  resizeWithValue(_0: number, _1: Array3VertId): void;
  resizeWithReserveAndValue(_0: number, _1: Array3VertId): void;
  get(_0: FaceId): Array3VertId;
  set(_0: FaceId, _1: Array3VertId): void;
  getByIndex(_0: FaceId): Array3VertId;
  getByIndexMutable(_0: FaceId): Array3VertId;
  getAt(_0: FaceId): Array3VertId;
  setAt(_0: FaceId, _1: Array3VertId): boolean;
  front(): Array3VertId;
  frontMutable(): Array3VertId;
  back(): Array3VertId;
  backMutable(): Array3VertId;
  pushBack(_0: Array3VertId): void;
  emplaceBack(_0: Array3VertId): Array3VertId;
  autoResizeAt(_0: FaceId): Array3VertId;
  autoResizeSet(_0: FaceId, _1: Array3VertId): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: Array3VertId): void;
}

export interface Dipoles extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: Dipole): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: Dipole): void;
  get(_0: NodeId): Dipole;
  set(_0: NodeId, _1: Dipole): void;
  getByIndex(_0: NodeId): Dipole;
  getByIndexMutable(_0: NodeId): Dipole;
  getAt(_0: NodeId): Dipole;
  setAt(_0: NodeId, _1: Dipole): boolean;
  front(): Dipole;
  frontMutable(): Dipole;
  back(): Dipole;
  backMutable(): Dipole;
  pushBack(_0: Dipole): void;
  popBack(): void;
  emplaceBack(_0: Dipole): Dipole;
  beginId(): NodeId;
  backId(): NodeId;
  endId(): NodeId;
  autoResizeAt(_0: NodeId): Dipole;
  autoResizeSet(_0: NodeId, _1: Dipole): void;
  autoResizeSetRange(_0: NodeId, _1: number, _2: Dipole): void;
  swap(_0: Dipoles): void;
  heapBytes(): number;
}

export interface FaceMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: FaceId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: FaceId): void;
  get(_0: FaceId): FaceId;
  set(_0: FaceId, _1: FaceId): void;
  getByIndex(_0: FaceId): FaceId;
  getByIndexMutable(_0: FaceId): FaceId;
  getAt(_0: FaceId): FaceId;
  setAt(_0: FaceId, _1: FaceId): boolean;
  front(): FaceId;
  frontMutable(): FaceId;
  back(): FaceId;
  backMutable(): FaceId;
  pushBack(_0: FaceId): void;
  popBack(): void;
  emplaceBack(_0: FaceId): FaceId;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): FaceId;
  autoResizeSet(_0: FaceId, _1: FaceId): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: FaceId): void;
  swap(_0: FaceMap): void;
  heapBytes(): number;
  equals(_0: FaceMap): boolean;
  notEquals(_0: FaceMap): boolean;
}

export interface VertMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: VertId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: VertId): void;
  get(_0: VertId): VertId;
  set(_0: VertId, _1: VertId): void;
  getByIndex(_0: VertId): VertId;
  getByIndexMutable(_0: VertId): VertId;
  getAt(_0: VertId): VertId;
  setAt(_0: VertId, _1: VertId): boolean;
  front(): VertId;
  frontMutable(): VertId;
  back(): VertId;
  backMutable(): VertId;
  pushBack(_0: VertId): void;
  popBack(): void;
  emplaceBack(_0: VertId): VertId;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  autoResizeAt(_0: VertId): VertId;
  autoResizeSet(_0: VertId, _1: VertId): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: VertId): void;
  swap(_0: VertMap): void;
  heapBytes(): number;
  equals(_0: VertMap): boolean;
  notEquals(_0: VertMap): boolean;
}

export interface EdgeMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: EdgeId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: EdgeId): void;
  get(_0: EdgeId): EdgeId;
  set(_0: EdgeId, _1: EdgeId): void;
  getByIndex(_0: EdgeId): EdgeId;
  getByIndexMutable(_0: EdgeId): EdgeId;
  getAt(_0: EdgeId): EdgeId;
  setAt(_0: EdgeId, _1: EdgeId): boolean;
  front(): EdgeId;
  frontMutable(): EdgeId;
  back(): EdgeId;
  backMutable(): EdgeId;
  pushBack(_0: EdgeId): void;
  popBack(): void;
  emplaceBack(_0: EdgeId): EdgeId;
  beginId(): EdgeId;
  backId(): EdgeId;
  endId(): EdgeId;
  autoResizeAt(_0: EdgeId): EdgeId;
  autoResizeSet(_0: EdgeId, _1: EdgeId): void;
  autoResizeSetRange(_0: EdgeId, _1: number, _2: EdgeId): void;
  swap(_0: EdgeMap): void;
  heapBytes(): number;
  equals(_0: EdgeMap): boolean;
  notEquals(_0: EdgeMap): boolean;
}

export interface UndirectedEdgeMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: UndirectedEdgeId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: UndirectedEdgeId): void;
  get(_0: UndirectedEdgeId): UndirectedEdgeId;
  set(_0: UndirectedEdgeId, _1: UndirectedEdgeId): void;
  getByIndex(_0: UndirectedEdgeId): UndirectedEdgeId;
  getByIndexMutable(_0: UndirectedEdgeId): UndirectedEdgeId;
  getAt(_0: UndirectedEdgeId): UndirectedEdgeId;
  setAt(_0: UndirectedEdgeId, _1: UndirectedEdgeId): boolean;
  front(): UndirectedEdgeId;
  frontMutable(): UndirectedEdgeId;
  back(): UndirectedEdgeId;
  backMutable(): UndirectedEdgeId;
  pushBack(_0: UndirectedEdgeId): void;
  popBack(): void;
  emplaceBack(_0: UndirectedEdgeId): UndirectedEdgeId;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  autoResizeAt(_0: UndirectedEdgeId): UndirectedEdgeId;
  autoResizeSet(_0: UndirectedEdgeId, _1: UndirectedEdgeId): void;
  autoResizeSetRange(_0: UndirectedEdgeId, _1: number, _2: UndirectedEdgeId): void;
  swap(_0: UndirectedEdgeMap): void;
  heapBytes(): number;
  equals(_0: UndirectedEdgeMap): boolean;
  notEquals(_0: UndirectedEdgeMap): boolean;
}

export interface ObjMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: ObjId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: ObjId): void;
  get(_0: ObjId): ObjId;
  set(_0: ObjId, _1: ObjId): void;
  getByIndex(_0: ObjId): ObjId;
  getByIndexMutable(_0: ObjId): ObjId;
  getAt(_0: ObjId): ObjId;
  setAt(_0: ObjId, _1: ObjId): boolean;
  front(): ObjId;
  frontMutable(): ObjId;
  back(): ObjId;
  backMutable(): ObjId;
  pushBack(_0: ObjId): void;
  popBack(): void;
  emplaceBack(_0: ObjId): ObjId;
  beginId(): ObjId;
  backId(): ObjId;
  endId(): ObjId;
  autoResizeAt(_0: ObjId): ObjId;
  autoResizeSet(_0: ObjId, _1: ObjId): void;
  autoResizeSetRange(_0: ObjId, _1: number, _2: ObjId): void;
  swap(_0: ObjMap): void;
  heapBytes(): number;
  equals(_0: ObjMap): boolean;
  notEquals(_0: ObjMap): boolean;
}

export interface WholeEdgeMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: EdgeId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: EdgeId): void;
  get(_0: UndirectedEdgeId): EdgeId;
  set(_0: UndirectedEdgeId, _1: EdgeId): void;
  getByIndex(_0: UndirectedEdgeId): EdgeId;
  getByIndexMutable(_0: UndirectedEdgeId): EdgeId;
  getAt(_0: UndirectedEdgeId): EdgeId;
  setAt(_0: UndirectedEdgeId, _1: EdgeId): boolean;
  front(): EdgeId;
  frontMutable(): EdgeId;
  back(): EdgeId;
  backMutable(): EdgeId;
  pushBack(_0: EdgeId): void;
  popBack(): void;
  emplaceBack(_0: EdgeId): EdgeId;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  autoResizeAt(_0: UndirectedEdgeId): EdgeId;
  autoResizeSet(_0: UndirectedEdgeId, _1: EdgeId): void;
  autoResizeSetRange(_0: UndirectedEdgeId, _1: number, _2: EdgeId): void;
  swap(_0: WholeEdgeMap): void;
  heapBytes(): number;
  equals(_0: WholeEdgeMap): boolean;
  notEquals(_0: WholeEdgeMap): boolean;
}

export interface UndirectedEdge2RegionMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: RegionId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: RegionId): void;
  get(_0: UndirectedEdgeId): RegionId;
  set(_0: UndirectedEdgeId, _1: RegionId): void;
  getByIndex(_0: UndirectedEdgeId): RegionId;
  getByIndexMutable(_0: UndirectedEdgeId): RegionId;
  getAt(_0: UndirectedEdgeId): RegionId;
  setAt(_0: UndirectedEdgeId, _1: RegionId): boolean;
  front(): RegionId;
  frontMutable(): RegionId;
  back(): RegionId;
  backMutable(): RegionId;
  pushBack(_0: RegionId): void;
  popBack(): void;
  emplaceBack(_0: RegionId): RegionId;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  autoResizeAt(_0: UndirectedEdgeId): RegionId;
  autoResizeSet(_0: UndirectedEdgeId, _1: RegionId): void;
  autoResizeSetRange(_0: UndirectedEdgeId, _1: number, _2: RegionId): void;
  swap(_0: UndirectedEdge2RegionMap): void;
  heapBytes(): number;
  equals(_0: UndirectedEdge2RegionMap): boolean;
  notEquals(_0: UndirectedEdge2RegionMap): boolean;
}

export interface Face2RegionMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: RegionId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: RegionId): void;
  get(_0: FaceId): RegionId;
  set(_0: FaceId, _1: RegionId): void;
  getByIndex(_0: FaceId): RegionId;
  getByIndexMutable(_0: FaceId): RegionId;
  getAt(_0: FaceId): RegionId;
  setAt(_0: FaceId, _1: RegionId): boolean;
  front(): RegionId;
  frontMutable(): RegionId;
  back(): RegionId;
  backMutable(): RegionId;
  pushBack(_0: RegionId): void;
  popBack(): void;
  emplaceBack(_0: RegionId): RegionId;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): RegionId;
  autoResizeSet(_0: FaceId, _1: RegionId): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: RegionId): void;
  swap(_0: Face2RegionMap): void;
  heapBytes(): number;
  equals(_0: Face2RegionMap): boolean;
  notEquals(_0: Face2RegionMap): boolean;
}

export interface Vert2RegionMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: RegionId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: RegionId): void;
  get(_0: VertId): RegionId;
  set(_0: VertId, _1: RegionId): void;
  getByIndex(_0: VertId): RegionId;
  getByIndexMutable(_0: VertId): RegionId;
  getAt(_0: VertId): RegionId;
  setAt(_0: VertId, _1: RegionId): boolean;
  front(): RegionId;
  frontMutable(): RegionId;
  back(): RegionId;
  backMutable(): RegionId;
  pushBack(_0: RegionId): void;
  popBack(): void;
  emplaceBack(_0: RegionId): RegionId;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  autoResizeAt(_0: VertId): RegionId;
  autoResizeSet(_0: VertId, _1: RegionId): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: RegionId): void;
  swap(_0: Vert2RegionMap): void;
  heapBytes(): number;
  equals(_0: Vert2RegionMap): boolean;
  notEquals(_0: Vert2RegionMap): boolean;
}

export interface VertCoords extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithReserve(_0: number): void;
  popBack(): void;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  swap(_0: VertCoords): void;
  heapBytes(): number;
  equals(_0: VertCoords): boolean;
  notEquals(_0: VertCoords): boolean;
  resizeWithValue(_0: number, _1: Vector3f): void;
  resizeWithReserveAndValue(_0: number, _1: Vector3f): void;
  get(_0: VertId): Vector3f;
  set(_0: VertId, _1: Vector3f): void;
  getByIndex(_0: VertId): Vector3f;
  getByIndexMutable(_0: VertId): Vector3f;
  getAt(_0: VertId): Vector3f;
  setAt(_0: VertId, _1: Vector3f): boolean;
  front(): Vector3f;
  frontMutable(): Vector3f;
  back(): Vector3f;
  backMutable(): Vector3f;
  pushBack(_0: Vector3f): void;
  emplaceBack(_0: Vector3f): Vector3f;
  autoResizeAt(_0: VertId): Vector3f;
  autoResizeSet(_0: VertId, _1: Vector3f): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: Vector3f): void;
}

export interface VertCoords2 extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithReserve(_0: number): void;
  popBack(): void;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  swap(_0: VertCoords2): void;
  heapBytes(): number;
  equals(_0: VertCoords2): boolean;
  notEquals(_0: VertCoords2): boolean;
  resizeWithValue(_0: number, _1: Vector2f): void;
  resizeWithReserveAndValue(_0: number, _1: Vector2f): void;
  get(_0: VertId): Vector2f;
  set(_0: VertId, _1: Vector2f): void;
  getByIndex(_0: VertId): Vector2f;
  getByIndexMutable(_0: VertId): Vector2f;
  getAt(_0: VertId): Vector2f;
  setAt(_0: VertId, _1: Vector2f): boolean;
  front(): Vector2f;
  frontMutable(): Vector2f;
  back(): Vector2f;
  backMutable(): Vector2f;
  pushBack(_0: Vector2f): void;
  emplaceBack(_0: Vector2f): Vector2f;
  autoResizeAt(_0: VertId): Vector2f;
  autoResizeSet(_0: VertId, _1: Vector2f): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: Vector2f): void;
}

export interface FaceNormals extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithReserve(_0: number): void;
  popBack(): void;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  swap(_0: FaceNormals): void;
  heapBytes(): number;
  equals(_0: FaceNormals): boolean;
  notEquals(_0: FaceNormals): boolean;
  resizeWithValue(_0: number, _1: Vector3f): void;
  resizeWithReserveAndValue(_0: number, _1: Vector3f): void;
  get(_0: FaceId): Vector3f;
  set(_0: FaceId, _1: Vector3f): void;
  getByIndex(_0: FaceId): Vector3f;
  getByIndexMutable(_0: FaceId): Vector3f;
  getAt(_0: FaceId): Vector3f;
  setAt(_0: FaceId, _1: Vector3f): boolean;
  front(): Vector3f;
  frontMutable(): Vector3f;
  back(): Vector3f;
  backMutable(): Vector3f;
  pushBack(_0: Vector3f): void;
  emplaceBack(_0: Vector3f): Vector3f;
  autoResizeAt(_0: FaceId): Vector3f;
  autoResizeSet(_0: FaceId, _1: Vector3f): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: Vector3f): void;
}

export interface TexturePerFace extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: TextureId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: TextureId): void;
  get(_0: FaceId): TextureId;
  set(_0: FaceId, _1: TextureId): void;
  getByIndex(_0: FaceId): TextureId;
  getByIndexMutable(_0: FaceId): TextureId;
  getAt(_0: FaceId): TextureId;
  setAt(_0: FaceId, _1: TextureId): boolean;
  front(): TextureId;
  frontMutable(): TextureId;
  back(): TextureId;
  backMutable(): TextureId;
  pushBack(_0: TextureId): void;
  popBack(): void;
  emplaceBack(_0: TextureId): TextureId;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): TextureId;
  autoResizeSet(_0: FaceId, _1: TextureId): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: TextureId): void;
  swap(_0: TexturePerFace): void;
  heapBytes(): number;
  equals(_0: TexturePerFace): boolean;
  notEquals(_0: TexturePerFace): boolean;
}

export interface VertColors extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: Color): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: Color): void;
  get(_0: VertId): Color;
  set(_0: VertId, _1: Color): void;
  getByIndex(_0: VertId): Color;
  getByIndexMutable(_0: VertId): Color;
  getAt(_0: VertId): Color;
  setAt(_0: VertId, _1: Color): boolean;
  front(): Color;
  frontMutable(): Color;
  back(): Color;
  backMutable(): Color;
  pushBack(_0: Color): void;
  popBack(): void;
  emplaceBack(_0: Color): Color;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  autoResizeAt(_0: VertId): Color;
  autoResizeSet(_0: VertId, _1: Color): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: Color): void;
  swap(_0: VertColors): void;
  heapBytes(): number;
  equals(_0: VertColors): boolean;
  notEquals(_0: VertColors): boolean;
}

export interface FaceColors extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: Color): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: Color): void;
  get(_0: FaceId): Color;
  set(_0: FaceId, _1: Color): void;
  getByIndex(_0: FaceId): Color;
  getByIndexMutable(_0: FaceId): Color;
  getAt(_0: FaceId): Color;
  setAt(_0: FaceId, _1: Color): boolean;
  front(): Color;
  frontMutable(): Color;
  back(): Color;
  backMutable(): Color;
  pushBack(_0: Color): void;
  popBack(): void;
  emplaceBack(_0: Color): Color;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): Color;
  autoResizeSet(_0: FaceId, _1: Color): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: Color): void;
  swap(_0: FaceColors): void;
  heapBytes(): number;
  equals(_0: FaceColors): boolean;
  notEquals(_0: FaceColors): boolean;
}

export interface EdgeColors extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: Color): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: Color): void;
  get(_0: EdgeId): Color;
  set(_0: EdgeId, _1: Color): void;
  getByIndex(_0: EdgeId): Color;
  getByIndexMutable(_0: EdgeId): Color;
  getAt(_0: EdgeId): Color;
  setAt(_0: EdgeId, _1: Color): boolean;
  front(): Color;
  frontMutable(): Color;
  back(): Color;
  backMutable(): Color;
  pushBack(_0: Color): void;
  popBack(): void;
  emplaceBack(_0: Color): Color;
  beginId(): EdgeId;
  backId(): EdgeId;
  endId(): EdgeId;
  autoResizeAt(_0: EdgeId): Color;
  autoResizeSet(_0: EdgeId, _1: Color): void;
  autoResizeSetRange(_0: EdgeId, _1: number, _2: Color): void;
  swap(_0: EdgeColors): void;
  heapBytes(): number;
  equals(_0: EdgeColors): boolean;
  notEquals(_0: EdgeColors): boolean;
}

export interface UndirectedEdgeColors extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: Color): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: Color): void;
  get(_0: UndirectedEdgeId): Color;
  set(_0: UndirectedEdgeId, _1: Color): void;
  getByIndex(_0: UndirectedEdgeId): Color;
  getByIndexMutable(_0: UndirectedEdgeId): Color;
  getAt(_0: UndirectedEdgeId): Color;
  setAt(_0: UndirectedEdgeId, _1: Color): boolean;
  front(): Color;
  frontMutable(): Color;
  back(): Color;
  backMutable(): Color;
  pushBack(_0: Color): void;
  popBack(): void;
  emplaceBack(_0: Color): Color;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  autoResizeAt(_0: UndirectedEdgeId): Color;
  autoResizeSet(_0: UndirectedEdgeId, _1: Color): void;
  autoResizeSetRange(_0: UndirectedEdgeId, _1: number, _2: Color): void;
  swap(_0: UndirectedEdgeColors): void;
  heapBytes(): number;
  equals(_0: UndirectedEdgeColors): boolean;
  notEquals(_0: UndirectedEdgeColors): boolean;
}

export interface VertScalars extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: number): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: number): void;
  get(_0: VertId): number;
  set(_0: VertId, _1: number): void;
  getByIndex(_0: VertId): number;
  getByIndexMutable(_0: VertId): number;
  getAt(_0: VertId): number;
  setAt(_0: VertId, _1: number): boolean;
  front(): number;
  frontMutable(): number;
  back(): number;
  backMutable(): number;
  pushBack(_0: number): void;
  popBack(): void;
  emplaceBack(_0: number): number;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  autoResizeAt(_0: VertId): number;
  autoResizeSet(_0: VertId, _1: number): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: number): void;
  swap(_0: VertScalars): void;
  heapBytes(): number;
  equals(_0: VertScalars): boolean;
  notEquals(_0: VertScalars): boolean;
}

export interface FaceScalars extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: number): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: number): void;
  get(_0: FaceId): number;
  set(_0: FaceId, _1: number): void;
  getByIndex(_0: FaceId): number;
  getByIndexMutable(_0: FaceId): number;
  getAt(_0: FaceId): number;
  setAt(_0: FaceId, _1: number): boolean;
  front(): number;
  frontMutable(): number;
  back(): number;
  backMutable(): number;
  pushBack(_0: number): void;
  popBack(): void;
  emplaceBack(_0: number): number;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): number;
  autoResizeSet(_0: FaceId, _1: number): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: number): void;
  swap(_0: FaceScalars): void;
  heapBytes(): number;
  equals(_0: FaceScalars): boolean;
  notEquals(_0: FaceScalars): boolean;
}

export interface EdgeScalars extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: number): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: number): void;
  get(_0: EdgeId): number;
  set(_0: EdgeId, _1: number): void;
  getByIndex(_0: EdgeId): number;
  getByIndexMutable(_0: EdgeId): number;
  getAt(_0: EdgeId): number;
  setAt(_0: EdgeId, _1: number): boolean;
  front(): number;
  frontMutable(): number;
  back(): number;
  backMutable(): number;
  pushBack(_0: number): void;
  popBack(): void;
  emplaceBack(_0: number): number;
  beginId(): EdgeId;
  backId(): EdgeId;
  endId(): EdgeId;
  autoResizeAt(_0: EdgeId): number;
  autoResizeSet(_0: EdgeId, _1: number): void;
  autoResizeSetRange(_0: EdgeId, _1: number, _2: number): void;
  swap(_0: EdgeScalars): void;
  heapBytes(): number;
  equals(_0: EdgeScalars): boolean;
  notEquals(_0: EdgeScalars): boolean;
}

export interface UndirectedEdgeScalars extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: number): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: number): void;
  get(_0: UndirectedEdgeId): number;
  set(_0: UndirectedEdgeId, _1: number): void;
  getByIndex(_0: UndirectedEdgeId): number;
  getByIndexMutable(_0: UndirectedEdgeId): number;
  getAt(_0: UndirectedEdgeId): number;
  setAt(_0: UndirectedEdgeId, _1: number): boolean;
  front(): number;
  frontMutable(): number;
  back(): number;
  backMutable(): number;
  pushBack(_0: number): void;
  popBack(): void;
  emplaceBack(_0: number): number;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  autoResizeAt(_0: UndirectedEdgeId): number;
  autoResizeSet(_0: UndirectedEdgeId, _1: number): void;
  autoResizeSetRange(_0: UndirectedEdgeId, _1: number, _2: number): void;
  swap(_0: UndirectedEdgeScalars): void;
  heapBytes(): number;
  equals(_0: UndirectedEdgeScalars): boolean;
  notEquals(_0: UndirectedEdgeScalars): boolean;
}

export interface NodeVec extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: AABBTreePointsNode): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: AABBTreePointsNode): void;
  get(_0: NodeId): AABBTreePointsNode;
  set(_0: NodeId, _1: AABBTreePointsNode): void;
  getByIndex(_0: NodeId): AABBTreePointsNode;
  getByIndexMutable(_0: NodeId): AABBTreePointsNode;
  getAt(_0: NodeId): AABBTreePointsNode;
  setAt(_0: NodeId, _1: AABBTreePointsNode): boolean;
  front(): AABBTreePointsNode;
  frontMutable(): AABBTreePointsNode;
  back(): AABBTreePointsNode;
  backMutable(): AABBTreePointsNode;
  pushBack(_0: AABBTreePointsNode): void;
  popBack(): void;
  emplaceBack(_0: AABBTreePointsNode): AABBTreePointsNode;
  beginId(): NodeId;
  backId(): NodeId;
  endId(): NodeId;
  autoResizeAt(_0: NodeId): AABBTreePointsNode;
  autoResizeSet(_0: NodeId, _1: AABBTreePointsNode): void;
  autoResizeSetRange(_0: NodeId, _1: number, _2: AABBTreePointsNode): void;
  swap(_0: NodeVec): void;
  heapBytes(): number;
}

export interface MeshLoadWrapper extends ClassHandle {
}

export interface MeshOrPoints extends ClassHandle {
  getObjBoundingBox(): Box3f;
  cacheAABBTree(): void;
  computeBoundingBox(_0: AffineXf3f | null): Box3f;
  points(): VertCoords;
  validPoints(): VertBitSet;
  asMeshPart(): MeshPart | null;
  asPointCloud(): PointCloud | null;
}

export interface MeshOrPointsXf extends ClassHandle {
  obj: MeshOrPoints;
  xf: AffineXf3f;
}

export interface MeshPart extends ClassHandle {
  region: FaceBitSet | null;
  getMesh(): Mesh;
}

export interface MeshVertPart extends ClassHandle {
  region: VertBitSet | null;
  getMesh(): Mesh;
}

export interface MeshProjectionResult extends ClassHandle {
  distSq: number;
  mtp: MeshTriPoint;
  proj: PointOnFace;
  valid(): boolean;
  asBool(): boolean;
}

export interface VectorMeshProjectionResult extends ClassHandle {
  push_back(_0: MeshProjectionResult): void;
  resize(_0: number, _1: MeshProjectionResult): void;
  size(): number;
  get(_0: number): MeshProjectionResult | undefined;
  set(_0: number, _1: MeshProjectionResult): boolean;
}

export interface MeshTopology extends ClassHandle {
}

export type WeightedVertex = {
  v: VertId,
  weight: number
};

export type WeightedVertexArray3 = [ WeightedVertex, WeightedVertex, WeightedVertex ];

export interface MeshTriPoint extends ClassHandle {
  e: EdgeId;
  bary: TriPointf;
  valid(): boolean;
  asBool(): boolean;
  inVertex(): boolean;
  onEdge(_0: MeshTopology): EdgePoint;
  isBd(_0: MeshTopology, _1: FaceBitSet | null): boolean;
  fromTriangle(_0: MeshTopology, _1: FaceId): boolean;
  lnext(_0: MeshTopology): MeshTriPoint;
  canonical(_0: MeshTopology): MeshTriPoint;
  getWeightedVerts(_0: MeshTopology): WeightedVertexArray3;
}

export interface NoDefInitFaceId extends ClassHandle {
}

export interface NoDefInitVertId extends ClassHandle {
}

export interface NoDefInitEdgeId extends ClassHandle {
}

export interface NoDefInitUndirectedEdgeId extends ClassHandle {
}

export interface OffsetParameters extends ClassHandle {
  closeHolesInHoleWindingNumber: boolean;
  windingNumberThreshold: number;
  windingNumberBeta: number;
  memoryEfficient: boolean;
  signDetectionMode: SignDetectionMode;
}

export interface SharpOffsetParameters extends OffsetParameters {
  minNewVertDev: number;
  maxNewRank2VertDev: number;
  maxNewRank3VertDev: number;
  maxOldVertPosCorrection: number;
}

export interface GeneralOffsetParameters extends SharpOffsetParameters {
  mode: OffsetMode;
}

export interface OffsetModeValue<T extends number> {
  value: T;
}
export type OffsetMode = OffsetModeValue<0>|OffsetModeValue<1>|OffsetModeValue<2>;

export interface SignDetectionModeValue<T extends number> {
  value: T;
}
export type SignDetectionMode = SignDetectionModeValue<0>|SignDetectionModeValue<1>|SignDetectionModeValue<2>|SignDetectionModeValue<3>|SignDetectionModeValue<4>;

export interface Plane3f extends ClassHandle {
  d: number;
  n: Vector3f;
  negate(): Plane3f;
  positive(): Plane3f;
  normalized(): Plane3f;
  distance(_0: Vector3f): number;
  project(_0: Vector3f): Vector3f;
}

export interface Plane3d extends ClassHandle {
  d: number;
  n: Vector3d;
  negate(): Plane3d;
  positive(): Plane3d;
  normalized(): Plane3d;
  distance(_0: Vector3d): number;
  project(_0: Vector3d): Vector3d;
}

export interface ReorderValue<T extends number> {
  value: T;
}
export type Reorder = ReorderValue<0>|ReorderValue<1>|ReorderValue<2>;

export interface PointCloud extends ClassHandle {
  points: VertCoords;
  normals: VertCoords;
  validPoints: VertBitSet;
  calcNumValidPoints(): number;
  hasNormals(): boolean;
  getVertIds(_0: VertBitSet | null): VertBitSet;
  getAABBTreeNotCreate(): AABBTreePoints | null;
  getBoundingBox(): Box3f;
  computeBoundingBox(_0: AffineXf3f | null): Box3f;
  getLexicographicalOrder(): VectorVertId;
  addPartByMask(_0: PointCloud, _1: VertBitSet, _2: CloudPartMapping, _3: VertCoords | null): void;
  mirror(_0: Plane3f): void;
  flipOrientation(_0: VertBitSet | null): void;
  pack(_0: VertMap | null): boolean;
  packReorder(_0: Reorder): VertBMap;
  invalidateCaches(): void;
  heapBytes(): number;
  findCenterFromPoints(): Vector3f;
  findCenterFromBBox(): Vector3f;
  addPoint(_0: Vector3f): VertId;
  addPointNormal(_0: Vector3f, _1: Vector3f): VertId;
}

export interface PointOnFace extends ClassHandle {
  face: FaceId;
  point: Vector3f;
  valid(): boolean;
  asBool(): boolean;
}

export type MeshMeshDistanceResult = {
  a: PointOnFace,
  b: PointOnFace,
  distSq: number
};

export type MeshMeshSignedDistanceResult = {
  a: PointOnFace,
  b: PointOnFace,
  signedDist: number
};

export interface IPointsToMeshProjector extends ClassHandle {
  updateMeshData(_0: Mesh | null): void;
  projectionsHeapBytes(_0: number): number;
  findProjections(_0: VectorMeshProjectionResult, _1: VectorVector3f, _2: AffineXf3f | null, _3: AffineXf3f | null, _4: number, _5: number): void;
}

export interface PointsToMeshProjector extends IPointsToMeshProjector {
  updateMeshData(_0: Mesh | null): void;
  projectionsHeapBytes(_0: number): number;
  findProjections(_0: VectorMeshProjectionResult, _1: VectorVector3f, _2: AffineXf3f | null, _3: AffineXf3f | null, _4: number, _5: number): void;
}

export interface MeshProjectionParameters extends ClassHandle {
  loDistLimitSq: number;
  upDistLimitSq: number;
  refXf: AffineXf3f | null;
  xf: AffineXf3f | null;
}

export interface SegmPointf extends ClassHandle {
}

export interface SegmPointd extends ClassHandle {
}

export interface SymMatrix2b extends ClassHandle {
}

export interface SymMatrix2i extends ClassHandle {
}

export interface SymMatrix2ll extends ClassHandle {
}

export interface SymMatrix2f extends ClassHandle {
}

export interface SymMatrix2d extends ClassHandle {
}

export interface SymMatrix3b extends ClassHandle {
}

export interface SymMatrix3i extends ClassHandle {
}

export interface SymMatrix3ll extends ClassHandle {
}

export interface SymMatrix3f extends ClassHandle {
}

export interface SymMatrix3d extends ClassHandle {
}

export interface SymMatrix4b extends ClassHandle {
}

export interface SymMatrix4i extends ClassHandle {
}

export interface SymMatrix4ll extends ClassHandle {
}

export interface SymMatrix4f extends ClassHandle {
}

export interface SymMatrix4d extends ClassHandle {
}

export interface TriPointf extends ClassHandle {
}

export interface TriPointd extends ClassHandle {
}

export interface StdVectori extends ClassHandle {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export interface StdVectorf extends ClassHandle {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export interface StdVectord extends ClassHandle {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export interface StdVectorll extends ClassHandle {
  push_back(_0: bigint): void;
  resize(_0: number, _1: bigint): void;
  size(): number;
  get(_0: number): bigint | undefined;
  set(_0: number, _1: bigint): boolean;
}

export interface StdVectorUi64 extends ClassHandle {
  push_back(_0: bigint): void;
  resize(_0: number, _1: bigint): void;
  size(): number;
  get(_0: number): bigint | undefined;
  set(_0: number, _1: bigint): boolean;
}

export type Array2f = [ number, number ];

export type Array2d = [ number, number ];

export type Array3f = [ number, number, number ];

export type Array3d = [ number, number, number ];

export type Array4f = [ number, number, number, number ];

export type Array4d = [ number, number, number, number ];

export type Array2EdgeId = [ EdgeId, EdgeId ];

export type Array3EdgeId = [ EdgeId, EdgeId, EdgeId ];

export type Array4EdgeId = [ EdgeId, EdgeId, EdgeId, EdgeId ];

export type Array2UndirectedEdgeId = [ UndirectedEdgeId, UndirectedEdgeId ];

export type Array3UndirectedEdgeId = [ UndirectedEdgeId, UndirectedEdgeId, UndirectedEdgeId ];

export type Array4UndirectedEdgeId = [ UndirectedEdgeId, UndirectedEdgeId, UndirectedEdgeId, UndirectedEdgeId ];

export type Array2FaceId = [ FaceId, FaceId ];

export type Array3FaceId = [ FaceId, FaceId, FaceId ];

export type Array4FaceId = [ FaceId, FaceId, FaceId, FaceId ];

export type Array2VertId = [ VertId, VertId ];

export type Array3VertId = [ VertId, VertId, VertId ];

export type Array4VertId = [ VertId, VertId, VertId, VertId ];

export type Array2PixelId = [ PixelId, PixelId ];

export type Array3PixelId = [ PixelId, PixelId, PixelId ];

export type Array4PixelId = [ PixelId, PixelId, PixelId, PixelId ];

export type Array2VoxelId = [ VoxelId, VoxelId ];

export type Array3VoxelId = [ VoxelId, VoxelId, VoxelId ];

export type Array4VoxelId = [ VoxelId, VoxelId, VoxelId, VoxelId ];

export type Array2RegionId = [ RegionId, RegionId ];

export type Array3RegionId = [ RegionId, RegionId, RegionId ];

export type Array4RegionId = [ RegionId, RegionId, RegionId, RegionId ];

export type Array2NodeId = [ NodeId, NodeId ];

export type Array3NodeId = [ NodeId, NodeId, NodeId ];

export type Array4NodeId = [ NodeId, NodeId, NodeId, NodeId ];

export type Array2ObjId = [ ObjId, ObjId ];

export type Array3ObjId = [ ObjId, ObjId, ObjId ];

export type Array4ObjId = [ ObjId, ObjId, ObjId, ObjId ];

export type Array2TextureId = [ TextureId, TextureId ];

export type Array3TextureId = [ TextureId, TextureId, TextureId ];

export type Array4TextureId = [ TextureId, TextureId, TextureId, TextureId ];

export type Array2GraphVertId = [ GraphVertId, GraphVertId ];

export type Array3GraphVertId = [ GraphVertId, GraphVertId, GraphVertId ];

export type Array4GraphVertId = [ GraphVertId, GraphVertId, GraphVertId, GraphVertId ];

export type Array2GraphEdgeId = [ GraphEdgeId, GraphEdgeId ];

export type Array3GraphEdgeId = [ GraphEdgeId, GraphEdgeId, GraphEdgeId ];

export type Array4GraphEdgeId = [ GraphEdgeId, GraphEdgeId, GraphEdgeId, GraphEdgeId ];

export interface VectorVectori extends ClassHandle {
  size(): number;
  get(_0: number): Vectori | undefined;
  push_back(_0: Vectori): void;
  resize(_0: number, _1: Vectori): void;
  set(_0: number, _1: Vectori): boolean;
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

export interface VectorVectorf extends ClassHandle {
  size(): number;
  get(_0: number): Vectorf | undefined;
  push_back(_0: Vectorf): void;
  resize(_0: number, _1: Vectorf): void;
  set(_0: number, _1: Vectorf): boolean;
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

export interface VectorVectord extends ClassHandle {
  size(): number;
  get(_0: number): Vectord | undefined;
  push_back(_0: Vectord): void;
  resize(_0: number, _1: Vectord): void;
  set(_0: number, _1: Vectord): boolean;
}

export interface Vectord extends ClassHandle {
}

export interface VectorVector2b extends ClassHandle {
  size(): number;
  get(_0: number): Vector2b | undefined;
  push_back(_0: Vector2b): void;
  resize(_0: number, _1: Vector2b): void;
  set(_0: number, _1: Vector2b): boolean;
}

export interface Vector2b extends ClassHandle {
  x: boolean;
  y: boolean;
  length(): number;
  lengthSq(): boolean;
  get(_0: number): boolean;
  set(_0: number): boolean;
}

export interface VectorVector2i extends ClassHandle {
  size(): number;
  get(_0: number): Vector2i | undefined;
  push_back(_0: Vector2i): void;
  resize(_0: number, _1: Vector2i): void;
  set(_0: number, _1: Vector2i): boolean;
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

export interface VectorVector2ll extends ClassHandle {
  size(): number;
  get(_0: number): Vector2ll | undefined;
  push_back(_0: Vector2ll): void;
  resize(_0: number, _1: Vector2ll): void;
  set(_0: number, _1: Vector2ll): boolean;
}

export interface Vector2ll extends ClassHandle {
}

export interface VectorVector2f extends ClassHandle {
  size(): number;
  get(_0: number): Vector2f | undefined;
  push_back(_0: Vector2f): void;
  resize(_0: number, _1: Vector2f): void;
  set(_0: number, _1: Vector2f): boolean;
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

export interface VectorVector2d extends ClassHandle {
  size(): number;
  get(_0: number): Vector2d | undefined;
  push_back(_0: Vector2d): void;
  resize(_0: number, _1: Vector2d): void;
  set(_0: number, _1: Vector2d): boolean;
}

export interface Vector2d extends ClassHandle {
}

export interface VectorVector3b extends ClassHandle {
  size(): number;
  get(_0: number): Vector3b | undefined;
  push_back(_0: Vector3b): void;
  resize(_0: number, _1: Vector3b): void;
  set(_0: number, _1: Vector3b): boolean;
}

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

export interface VectorVector3i extends ClassHandle {
  size(): number;
  get(_0: number): Vector3i | undefined;
  push_back(_0: Vector3i): void;
  resize(_0: number, _1: Vector3i): void;
  set(_0: number, _1: Vector3i): boolean;
}

export interface Vector3i extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  furthestBasisVector(): Vector3i;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
  normalized(): Vector3f;
  unsignZeroValues(): Vector3f;
  perpendicular(): Vector3fPair;
}

export type Vector3iPair = [ Vector3i, Vector3i ];

export interface VectorVector3ll extends ClassHandle {
  size(): number;
  get(_0: number): Vector3ll | undefined;
  push_back(_0: Vector3ll): void;
  resize(_0: number, _1: Vector3ll): void;
  set(_0: number, _1: Vector3ll): boolean;
}

export interface Vector3ll extends ClassHandle {
  x: bigint;
  y: bigint;
  z: bigint;
  lengthSq(): bigint;
  length(): number;
  furthestBasisVector(): Vector3ll;
  isFinite(): boolean;
  get(_0: number): bigint;
  set(_0: number): bigint;
  normalized(): Vector3f;
  unsignZeroValues(): Vector3f;
  perpendicular(): Vector3fPair;
}

export type Vector3llPair = [ Vector3ll, Vector3ll ];

export interface VectorVector3f extends ClassHandle {
  size(): number;
  get(_0: number): Vector3f | undefined;
  push_back(_0: Vector3f): void;
  resize(_0: number, _1: Vector3f): void;
  set(_0: number, _1: Vector3f): boolean;
}

export interface Vector3f extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3f;
  furthestBasisVector(): Vector3f;
  perpendicular(): Vector3fPair;
  unsignZeroValues(): void;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
}

export type AABBTreePointsPoint = {
  coord: Vector3f,
  id: VertId
};

export type FindParams = {
  upDirection: Vector3f,
  wallAngle: number
};

export type ICPProperties = {
  method: ICPMethod,
  p2plAngleLimit: number,
  p2plScaleLimit: number,
  cosThreshold: number,
  distThresholdSq: number,
  farDistFactor: number,
  icpMode: ICPMode,
  fixedRotationAxis: Vector3f,
  iterLimit: number,
  badIterStopCount: number,
  exitVal: number,
  mutualClosest: boolean
};

export type ProjectionResult = {
  point: Vector3f,
  isBd: boolean,
  distSq: number,
  closestVert: VertId
};

export type Vector3fPair = [ Vector3f, Vector3f ];

export interface VectorVector3d extends ClassHandle {
  size(): number;
  get(_0: number): Vector3d | undefined;
  push_back(_0: Vector3d): void;
  resize(_0: number, _1: Vector3d): void;
  set(_0: number, _1: Vector3d): boolean;
}

export interface Vector3d extends ClassHandle {
  x: number;
  y: number;
  z: number;
  lengthSq(): number;
  length(): number;
  normalized(): Vector3d;
  furthestBasisVector(): Vector3d;
  perpendicular(): Vector3DPair;
  unsignZeroValues(): void;
  isFinite(): boolean;
  get(_0: number): number;
  set(_0: number): number;
}

export type Vector3DPair = [ Vector3d, Vector3d ];

export interface VectorVector4b extends ClassHandle {
  size(): number;
  get(_0: number): Vector4b | undefined;
  push_back(_0: Vector4b): void;
  resize(_0: number, _1: Vector4b): void;
  set(_0: number, _1: Vector4b): boolean;
}

export interface Vector4b extends ClassHandle {
}

export interface VectorVector4i extends ClassHandle {
  size(): number;
  get(_0: number): Vector4i | undefined;
  push_back(_0: Vector4i): void;
  resize(_0: number, _1: Vector4i): void;
  set(_0: number, _1: Vector4i): boolean;
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

export interface VectorVector4ll extends ClassHandle {
  size(): number;
  get(_0: number): Vector4ll | undefined;
  push_back(_0: Vector4ll): void;
  resize(_0: number, _1: Vector4ll): void;
  set(_0: number, _1: Vector4ll): boolean;
}

export interface Vector4ll extends ClassHandle {
}

export interface VectorVector4f extends ClassHandle {
  size(): number;
  get(_0: number): Vector4f | undefined;
  push_back(_0: Vector4f): void;
  resize(_0: number, _1: Vector4f): void;
  set(_0: number, _1: Vector4f): boolean;
}

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

export interface VectorVector4d extends ClassHandle {
  size(): number;
  get(_0: number): Vector4d | undefined;
  push_back(_0: Vector4d): void;
  resize(_0: number, _1: Vector4d): void;
  set(_0: number, _1: Vector4d): boolean;
}

export interface Vector4d extends ClassHandle {
}

export interface VisualObject extends ClassHandle {
}

interface EmbindModule {
  AABBTreeObjects: {
    new(): AABBTreeObjects;
  };
  VectorAABBTreePointsPoint: {
    new(): VectorAABBTreePointsPoint;
  };
  VectorAABBTreePointsNode: {
    new(): VectorAABBTreePointsNode;
  };
  AABBTreePointsNode: {
    new(): AABBTreePointsNode;
  };
  AABBTreePoints: {
    new(_0: Mesh): AABBTreePoints;
    new(_0: VertCoords, _1: VertBitSet | null): AABBTreePoints;
    MaxNumPointsInLeaf: number;
  };
  AffineXf2f: {
    new(): AffineXf2f;
    new(_0: Matrix2f, _1: Vector2f): AffineXf2f;
    linear(_0: Matrix2f): AffineXf2f;
    translation(_0: Vector2f): AffineXf2f;
    xfAround(_0: Matrix2f, _1: Vector2f): AffineXf2f;
  };
  AffineXf2d: {
    new(): AffineXf2d;
    new(_0: Matrix2d, _1: Vector2d): AffineXf2d;
    linear(_0: Matrix2d): AffineXf2d;
    translation(_0: Vector2d): AffineXf2d;
    xfAround(_0: Matrix2d, _1: Vector2d): AffineXf2d;
  };
  AffineXf3f: {
    new(): AffineXf3f;
    new(_0: Matrix3f, _1: Vector3f): AffineXf3f;
    linear(_0: Matrix3f): AffineXf3f;
    translation(_0: Vector3f): AffineXf3f;
    xfAround(_0: Matrix3f, _1: Vector3f): AffineXf3f;
  };
  to3dimXff(_0: AffineXf2f): AffineXf3f;
  to2dimXff(_0: AffineXf3f): AffineXf2f;
  AffineXf3d: {
    new(): AffineXf3d;
    new(_0: Matrix3d, _1: Vector3d): AffineXf3d;
    linear(_0: Matrix3d): AffineXf3d;
    translation(_0: Vector3d): AffineXf3d;
    xfAround(_0: Matrix3d, _1: Vector3d): AffineXf3d;
  };
  to3dimXfd(_0: AffineXf2d): AffineXf3d;
  to2dimXfd(_0: AffineXf3d): AffineXf2d;
  Axis: {X: AxisValue<0>, Y: AxisValue<1>, Z: AxisValue<2>, Count: AxisValue<3>};
  CubicBezierCurve2f: {
    new(): CubicBezierCurve2f;
    getWeights(_0: number): Array4f;
  };
  CubicBezierCurve2d: {
    new(): CubicBezierCurve2d;
    getWeights(_0: number): Array4d;
  };
  CubicBezierCurve3f: {
    new(): CubicBezierCurve3f;
    getWeights(_0: number): Array4f;
  };
  CubicBezierCurve3d: {
    new(): CubicBezierCurve3d;
    getWeights(_0: number): Array4d;
  };
  CubicBezierCurve4f: {
    new(): CubicBezierCurve4f;
    getWeights(_0: number): Array4f;
  };
  CubicBezierCurve4d: {
    new(): CubicBezierCurve4d;
    getWeights(_0: number): Array4d;
  };
  __InternalDynamicBitset: {
    new(): __InternalDynamicBitset;
    new(_0: number): __InternalDynamicBitset;
    new(_0: number, _1: boolean): __InternalDynamicBitset;
  };
  BitSet: {
    new(): BitSet;
    new(_0: number): BitSet;
    new(_0: number, _1: boolean): BitSet;
    createWithBool(_0: number, _1: boolean): BitSet;
    beginId(): number;
  };
  FaceBitSet: {
    new(): FaceBitSet;
    new(_0: BitSet): FaceBitSet;
    createWithSize(_0: number): FaceBitSet;
    createWithValue(_0: number, _1: boolean): FaceBitSet;
    createFromBitSet(_0: BitSet): FaceBitSet;
    createFromBitSetMove(_0: BitSet): FaceBitSet;
    beginId(): FaceId;
  };
  VertBitSet: {
    new(): VertBitSet;
  };
  EdgeBitSet: {
    new(): EdgeBitSet;
  };
  UndirectedEdgeBitSet: {
    new(): UndirectedEdgeBitSet;
  };
  PixelBitSet: {
    new(): PixelBitSet;
  };
  VoxelBitSet: {
    new(): VoxelBitSet;
  };
  RegionBitSet: {
    new(): RegionBitSet;
  };
  NodeBitSet: {
    new(): NodeBitSet;
  };
  ObjBitSet: {
    new(): ObjBitSet;
  };
  TextureBitSet: {
    new(): TextureBitSet;
  };
  GraphVertBitSet: {
    new(): GraphVertBitSet;
  };
  GraphEdgeBitSet: {
    new(): GraphEdgeBitSet;
  };
  faceBitSetAnd(_0: FaceBitSet, _1: FaceBitSet): FaceBitSet;
  faceBitSetOr(_0: FaceBitSet, _1: FaceBitSet): FaceBitSet;
  faceBitSetXor(_0: FaceBitSet, _1: FaceBitSet): FaceBitSet;
  faceBitSetSub(_0: FaceBitSet, _1: FaceBitSet): FaceBitSet;
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
  FaceBMapBuffer: {
    new(): FaceBMapBuffer;
    new(_0: number): FaceBMapBuffer;
  };
  VertBMapBuffer: {
    new(): VertBMapBuffer;
    new(_0: number): VertBMapBuffer;
  };
  EdgeBMapBuffer: {
    new(): EdgeBMapBuffer;
    new(_0: number): EdgeBMapBuffer;
  };
  UndirectedEdgeBMapBuffer: {
    new(): UndirectedEdgeBMapBuffer;
    new(_0: number): UndirectedEdgeBMapBuffer;
  };
  WholeEdgeBMapBuffer: {
    new(): WholeEdgeBMapBuffer;
    new(_0: number): WholeEdgeBMapBuffer;
  };
  CloudPartMapping: {
    new(): CloudPartMapping;
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
  PI: number;
  PI2: number;
  PI_F: number;
  PI2_F: number;
  Dipole: {
    new(): Dipole;
  };
  EdgePoint: {
    new(): EdgePoint;
  };
  MeshSegmentation: {
    new(_0: Mesh): MeshSegmentation;
  };
  FixParams: {
    new(): FixParams;
  };
  ICP: {
    new(_0: MeshOrPoints, _1: MeshOrPoints, _2: AffineXf3f, _3: AffineXf3f, _4: VertBitSet, _5: VertBitSet): ICP;
    new(_0: MeshOrPoints, _1: MeshOrPoints, _2: AffineXf3f, _3: AffineXf3f, _4: number): ICP;
    new(_0: MeshOrPointsXf, _1: MeshOrPointsXf, _2: VertBitSet, _3: VertBitSet): ICP;
    new(_0: MeshOrPointsXf, _1: MeshOrPointsXf, _2: number): ICP;
  };
  ICPMethod: {Combined: ICPMethodValue<0>, PointToPoint: ICPMethodValue<1>, PointToPlane: ICPMethodValue<2>};
  ICPMode: {RigidScale: ICPModeValue<0>, AnyRigidXf: ICPModeValue<1>, OrthogonalAxis: ICPModeValue<2>, FixedAxis: ICPModeValue<3>, TranslationOnly: ICPModeValue<4>};
  ICPExitType: {NotStarted: ICPExitTypeValue<0>, NotFoundSolution: ICPExitTypeValue<1>, MaxIterations: ICPExitTypeValue<2>, MaxBadIterations: ICPExitTypeValue<3>, StopMsdReached: ICPExitTypeValue<4>};
  EdgeHashMapEntries: {
    new(): EdgeHashMapEntries;
  };
  UndirectedEdgeHashMapEntries: {
    new(): UndirectedEdgeHashMapEntries;
  };
  WholeEdgeHashMapEntries: {
    new(): WholeEdgeHashMapEntries;
  };
  FaceHashMapEntries: {
    new(): FaceHashMapEntries;
  };
  VertHashMapEntries: {
    new(): VertHashMapEntries;
  };
  VectorEdgeId: {
    new(): VectorEdgeId;
  };
  VectorUndirectedEdgeId: {
    new(): VectorUndirectedEdgeId;
  };
  VectorFaceId: {
    new(): VectorFaceId;
  };
  VectorVertId: {
    new(): VectorVertId;
  };
  VectorPixelId: {
    new(): VectorPixelId;
  };
  VectorVoxelId: {
    new(): VectorVoxelId;
  };
  VectorRegionId: {
    new(): VectorRegionId;
  };
  VectorNodeId: {
    new(): VectorNodeId;
  };
  VectorObjId: {
    new(): VectorObjId;
  };
  VectorTextureId: {
    new(): VectorTextureId;
  };
  VectorGraphVertId: {
    new(): VectorGraphVertId;
  };
  VectorGraphEdgeId: {
    new(): VectorGraphEdgeId;
  };
  VectorEdgePath: {
    new(): VectorEdgePath;
  };
  VectorVectorEdgePath: {
    new(): VectorVectorEdgePath;
  };
  lerp(_0: number, _1: number, _2: number): number;
  MyClass: {
    new(_0: number, _1: EmbindString): MyClass;
    getStringFromInstance(_0: MyClass): string;
  };
  Matrix2b: {
    new(): Matrix2b;
  };
  Matrix2i: {
    new(): Matrix2i;
  };
  Matrix2ll: {
    new(): Matrix2ll;
  };
  Matrix2f: {
    new(): Matrix2f;
  };
  Matrix2d: {
    new(): Matrix2d;
  };
  Matrix3b: {
    new(): Matrix3b;
  };
  Matrix3i: {
    new(): Matrix3i;
  };
  Matrix3ll: {
    new(): Matrix3ll;
  };
  Matrix3f: {
    new(): Matrix3f;
  };
  to3dimMatf(_0: Matrix2f): Matrix3f;
  to2dimMatf(_0: Matrix3f): Matrix2f;
  Matrix3d: {
    new(): Matrix3d;
  };
  to3dimMatd(_0: Matrix2d): Matrix3d;
  to2dimMatd(_0: Matrix3d): Matrix2d;
  Matrix4b: {
    new(): Matrix4b;
  };
  Matrix4i: {
    new(): Matrix4i;
  };
  Matrix4ll: {
    new(): Matrix4ll;
  };
  Matrix4f: {
    new(): Matrix4f;
  };
  Matrix4d: {
    new(): Matrix4d;
  };
  Mesh: {
    new(): Mesh;
  };
  makeBasisAxes(_0: number, _1: number, _2: number, _3: number, _4: number): Mesh;
  smoothExtractedRegionBoundary(_0: Mesh, _1: number): any;
  calculateRecommendedVoxelSize(_0: Mesh, _1: number): number;
  computeVertexNormals(_0: Mesh): any;
  MeshWrapper: {
    new(): MeshWrapper;
    new(_0: Mesh): MeshWrapper;
    fromTriangles(_0: any, _1: any): any;
  };
  BooleanOperation: {InsideA: BooleanOperationValue<0>, InsideB: BooleanOperationValue<1>, OutsideA: BooleanOperationValue<2>, OutsideB: BooleanOperationValue<3>, Union: BooleanOperationValue<4>, Intersection: BooleanOperationValue<5>, DifferenceBA: BooleanOperationValue<6>, DifferenceAB: BooleanOperationValue<7>, Count: BooleanOperationValue<8>};
  BooleanResult: {
    new(): BooleanResult;
  };
  performBoolean(_0: Mesh, _1: Mesh, _2: BooleanOperation): BooleanResult;
  __phmap_internal_FlatHashMapPolicy_VertId: {};
  __phmap_internal_raw_hash_set_VertId: {};
  __phmap_internal_raw_hash_map_VertId: {};
  FaceHashMapWrapper: {
    new(): FaceHashMapWrapper;
  };
  VertHashMap: {
    new(): VertHashMap;
  };
  FaceHashMap: {
    new(): FaceHashMap;
  };
  EdgeHashMap: {
    new(): EdgeHashMap;
  };
  UndirectedEdgeHashMap: {
    new(): UndirectedEdgeHashMap;
  };
  WholeEdgeHashMap: {
    new(): WholeEdgeHashMap;
  };
  MakeDegenerateBandAroundRegionParamsWrapper: {
    new(): MakeDegenerateBandAroundRegionParamsWrapper;
  };
  MakeDegenerateBandAroundRegionParams: {
    new(): MakeDegenerateBandAroundRegionParams;
  };
  makeDegenerateBandAroundRegion(_0: Mesh, _1: FaceBitSet, _2: MakeDegenerateBandAroundRegionParams): void;
  FillHoleParams: {
    new(): FillHoleParams;
  };
  fillHoles(_0: Mesh, _1: VectorEdgeId, _2: FillHoleParams): void;
  noInit: NoInit;
  UndirectedEdgeId: {
    new(): UndirectedEdgeId;
    new(_0: number): UndirectedEdgeId;
  };
  makeUndirectedEdgeId(_0: number): UndirectedEdgeId;
  addUndirectedEdgeId(_0: UndirectedEdgeId, _1: number): UndirectedEdgeId;
  addUndirectedEdgeIdUInt(_0: UndirectedEdgeId, _1: number): UndirectedEdgeId;
  addUndirectedEdgeIdSize(_0: UndirectedEdgeId, _1: number): UndirectedEdgeId;
  subUndirectedEdgeId(_0: UndirectedEdgeId, _1: number): UndirectedEdgeId;
  subUndirectedEdgeIdUInt(_0: UndirectedEdgeId, _1: number): UndirectedEdgeId;
  subUndirectedEdgeIdSize(_0: UndirectedEdgeId, _1: number): UndirectedEdgeId;
  EdgeId: {
    new(): EdgeId;
    new(_0: number): EdgeId;
    fromUndirected(_0: UndirectedEdgeId): EdgeId;
  };
  makeEdgeId(_0: number): EdgeId;
  addEdgeId(_0: EdgeId, _1: number): EdgeId;
  addEdgeIdUInt(_0: EdgeId, _1: number): EdgeId;
  addEdgeIdSize(_0: EdgeId, _1: number): EdgeId;
  subEdgeId(_0: EdgeId, _1: number): EdgeId;
  subEdgeIdUInt(_0: EdgeId, _1: number): EdgeId;
  subEdgeIdSize(_0: EdgeId, _1: number): EdgeId;
  fillHole(_0: Mesh, _1: EdgeId, _2: FillHoleParams): void;
  extendHoleWithFunc(_0: Mesh, _1: EdgeId, _2: any): EdgeId;
  makeDegenerateBandAroundHole(_0: Mesh, _1: EdgeId): EdgeId;
  extendHoleWithFuncAndOutput(_0: Mesh, _1: EdgeId, _2: any): any;
  makeDegenerateBandAroundHoleWithOutput(_0: Mesh, _1: EdgeId): any;
  FaceId: {
    new(): FaceId;
    new(_0: number): FaceId;
  };
  makeFaceId(_0: number): FaceId;
  addFaceId(_0: FaceId, _1: number): FaceId;
  addFaceIdUInt(_0: FaceId, _1: number): FaceId;
  addFaceIdSize(_0: FaceId, _1: number): FaceId;
  subFaceId(_0: FaceId, _1: number): FaceId;
  subFaceIdUInt(_0: FaceId, _1: number): FaceId;
  subFaceIdSize(_0: FaceId, _1: number): FaceId;
  VertId: {
    new(): VertId;
    new(_0: number): VertId;
  };
  makeVertId(_0: number): VertId;
  addVertId(_0: VertId, _1: number): VertId;
  addVertIdUInt(_0: VertId, _1: number): VertId;
  addVertIdSize(_0: VertId, _1: number): VertId;
  subVertId(_0: VertId, _1: number): VertId;
  subVertIdUInt(_0: VertId, _1: number): VertId;
  subVertIdSize(_0: VertId, _1: number): VertId;
  PixelId: {
    new(): PixelId;
    new(_0: number): PixelId;
  };
  addPixelId(_0: PixelId, _1: number): PixelId;
  addPixelIdUInt(_0: PixelId, _1: number): PixelId;
  addPixelIdSize(_0: PixelId, _1: number): PixelId;
  subPixelId(_0: PixelId, _1: number): PixelId;
  subPixelIdUInt(_0: PixelId, _1: number): PixelId;
  subPixelIdSize(_0: PixelId, _1: number): PixelId;
  VoxelId: {
    new(): VoxelId;
    new(_0: number): VoxelId;
  };
  makeVoxelId(_0: number): VoxelId;
  addVoxelId(_0: VoxelId, _1: number): VoxelId;
  addVoxelIdUInt(_0: VoxelId, _1: number): VoxelId;
  addVoxelIdSize(_0: VoxelId, _1: number): VoxelId;
  subVoxelId(_0: VoxelId, _1: number): VoxelId;
  subVoxelIdUInt(_0: VoxelId, _1: number): VoxelId;
  subVoxelIdSize(_0: VoxelId, _1: number): VoxelId;
  RegionId: {
    new(): RegionId;
    new(_0: number): RegionId;
  };
  addRegionId(_0: RegionId, _1: number): RegionId;
  addRegionIdUInt(_0: RegionId, _1: number): RegionId;
  addRegionIdSize(_0: RegionId, _1: number): RegionId;
  subRegionId(_0: RegionId, _1: number): RegionId;
  subRegionIdUInt(_0: RegionId, _1: number): RegionId;
  subRegionIdSize(_0: RegionId, _1: number): RegionId;
  NodeId: {
    new(): NodeId;
    new(_0: number): NodeId;
  };
  addNodeId(_0: NodeId, _1: number): NodeId;
  addNodeIdUInt(_0: NodeId, _1: number): NodeId;
  addNodeIdSize(_0: NodeId, _1: number): NodeId;
  subNodeId(_0: NodeId, _1: number): NodeId;
  subNodeIdUInt(_0: NodeId, _1: number): NodeId;
  subNodeIdSize(_0: NodeId, _1: number): NodeId;
  ObjId: {
    new(): ObjId;
    new(_0: number): ObjId;
  };
  addObjId(_0: ObjId, _1: number): ObjId;
  addObjIdUInt(_0: ObjId, _1: number): ObjId;
  addObjIdSize(_0: ObjId, _1: number): ObjId;
  subObjId(_0: ObjId, _1: number): ObjId;
  subObjIdUInt(_0: ObjId, _1: number): ObjId;
  subObjIdSize(_0: ObjId, _1: number): ObjId;
  TextureId: {
    new(): TextureId;
    new(_0: number): TextureId;
  };
  addTextureId(_0: TextureId, _1: number): TextureId;
  addTextureIdUInt(_0: TextureId, _1: number): TextureId;
  addTextureIdSize(_0: TextureId, _1: number): TextureId;
  subTextureId(_0: TextureId, _1: number): TextureId;
  subTextureIdUInt(_0: TextureId, _1: number): TextureId;
  subTextureIdSize(_0: TextureId, _1: number): TextureId;
  GraphVertId: {
    new(): GraphVertId;
    new(_0: number): GraphVertId;
  };
  addGraphVertId(_0: GraphVertId, _1: number): GraphVertId;
  addGraphVertIdUInt(_0: GraphVertId, _1: number): GraphVertId;
  addGraphVertIdSize(_0: GraphVertId, _1: number): GraphVertId;
  subGraphVertId(_0: GraphVertId, _1: number): GraphVertId;
  subGraphVertIdUInt(_0: GraphVertId, _1: number): GraphVertId;
  subGraphVertIdSize(_0: GraphVertId, _1: number): GraphVertId;
  GraphEdgeId: {
    new(): GraphEdgeId;
    new(_0: number): GraphEdgeId;
  };
  addGraphEdgeId(_0: GraphEdgeId, _1: number): GraphEdgeId;
  addGraphEdgeIdUInt(_0: GraphEdgeId, _1: number): GraphEdgeId;
  addGraphEdgeIdSize(_0: GraphEdgeId, _1: number): GraphEdgeId;
  subGraphEdgeId(_0: GraphEdgeId, _1: number): GraphEdgeId;
  subGraphEdgeIdUInt(_0: GraphEdgeId, _1: number): GraphEdgeId;
  subGraphEdgeIdSize(_0: GraphEdgeId, _1: number): GraphEdgeId;
  VertBMap: {
    new(): VertBMap;
  };
  FaceBMap: {
    new(): FaceBMap;
  };
  EdgeBMap: {
    new(): EdgeBMap;
  };
  UndirectedEdgeBMap: {
    new(): UndirectedEdgeBMap;
  };
  WholeEdgeBMap: {
    new(): WholeEdgeBMap;
  };
  Triangulation: {
    new(): Triangulation;
    new(_0: number): Triangulation;
    new(_0: number, _1: Array3VertId): Triangulation;
  };
  Dipoles: {
    new(): Dipoles;
    new(_0: number): Dipoles;
    new(_0: number, _1: Dipole): Dipoles;
  };
  FaceMap: {
    new(): FaceMap;
    new(_0: number): FaceMap;
    new(_0: number, _1: FaceId): FaceMap;
  };
  VertMap: {
    new(): VertMap;
    new(_0: number): VertMap;
    new(_0: number, _1: VertId): VertMap;
  };
  EdgeMap: {
    new(): EdgeMap;
    new(_0: number): EdgeMap;
    new(_0: number, _1: EdgeId): EdgeMap;
  };
  UndirectedEdgeMap: {
    new(): UndirectedEdgeMap;
    new(_0: number): UndirectedEdgeMap;
    new(_0: number, _1: UndirectedEdgeId): UndirectedEdgeMap;
  };
  ObjMap: {
    new(): ObjMap;
    new(_0: number): ObjMap;
    new(_0: number, _1: ObjId): ObjMap;
  };
  WholeEdgeMap: {
    new(): WholeEdgeMap;
    new(_0: number): WholeEdgeMap;
    new(_0: number, _1: EdgeId): WholeEdgeMap;
  };
  UndirectedEdge2RegionMap: {
    new(): UndirectedEdge2RegionMap;
    new(_0: number): UndirectedEdge2RegionMap;
    new(_0: number, _1: RegionId): UndirectedEdge2RegionMap;
  };
  Face2RegionMap: {
    new(): Face2RegionMap;
    new(_0: number): Face2RegionMap;
    new(_0: number, _1: RegionId): Face2RegionMap;
  };
  Vert2RegionMap: {
    new(): Vert2RegionMap;
    new(_0: number): Vert2RegionMap;
    new(_0: number, _1: RegionId): Vert2RegionMap;
  };
  VertCoords: {
    new(): VertCoords;
    new(_0: number): VertCoords;
    new(_0: number, _1: Vector3f): VertCoords;
  };
  VertCoords2: {
    new(): VertCoords2;
    new(_0: number): VertCoords2;
    new(_0: number, _1: Vector2f): VertCoords2;
  };
  FaceNormals: {
    new(): FaceNormals;
    new(_0: number): FaceNormals;
    new(_0: number, _1: Vector3f): FaceNormals;
  };
  TexturePerFace: {
    new(): TexturePerFace;
    new(_0: number): TexturePerFace;
    new(_0: number, _1: TextureId): TexturePerFace;
  };
  VertColors: {
    new(): VertColors;
    new(_0: number): VertColors;
    new(_0: number, _1: Color): VertColors;
  };
  FaceColors: {
    new(): FaceColors;
    new(_0: number): FaceColors;
    new(_0: number, _1: Color): FaceColors;
  };
  EdgeColors: {
    new(): EdgeColors;
    new(_0: number): EdgeColors;
    new(_0: number, _1: Color): EdgeColors;
  };
  UndirectedEdgeColors: {
    new(): UndirectedEdgeColors;
    new(_0: number): UndirectedEdgeColors;
    new(_0: number, _1: Color): UndirectedEdgeColors;
  };
  VertScalars: {
    new(): VertScalars;
    new(_0: number): VertScalars;
    new(_0: number, _1: number): VertScalars;
  };
  FaceScalars: {
    new(): FaceScalars;
    new(_0: number): FaceScalars;
    new(_0: number, _1: number): FaceScalars;
  };
  EdgeScalars: {
    new(): EdgeScalars;
    new(_0: number): EdgeScalars;
    new(_0: number, _1: number): EdgeScalars;
  };
  UndirectedEdgeScalars: {
    new(): UndirectedEdgeScalars;
    new(_0: number): UndirectedEdgeScalars;
    new(_0: number, _1: number): UndirectedEdgeScalars;
  };
  NodeVec: {
    new(): NodeVec;
    new(_0: number): NodeVec;
    new(_0: number, _1: AABBTreePointsNode): NodeVec;
  };
  MeshLoadWrapper: {
    fromFile(_0: EmbindString): any;
    fromBinaryData(_0: number, _1: number, _2: EmbindString): any;
  };
  MeshOrPoints: {
    new(_0: Mesh): MeshOrPoints;
    new(_0: MeshPart): MeshOrPoints;
    new(_0: PointCloud): MeshOrPoints;
  };
  MeshOrPointsXf: {
    new(_0: MeshOrPoints, _1: AffineXf3f): MeshOrPointsXf;
  };
  MeshPart: {
    new(_0: Mesh): MeshPart;
    new(_0: Mesh, _1: FaceBitSet | null): MeshPart;
  };
  findMaxDistanceSqOneWay(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null, _3: number): number;
  findMaxDistanceSq(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null, _3: number): number;
  MeshVertPart: {
    new(_0: Mesh): MeshVertPart;
    new(_0: Mesh, _1: VertBitSet | null): MeshVertPart;
  };
  MeshProjectionResult: {
    new(): MeshProjectionResult;
  };
  VectorMeshProjectionResult: {
    new(): VectorMeshProjectionResult;
  };
  MeshTopology: {
    new(): MeshTopology;
  };
  fillContourLeft(_0: MeshTopology, _1: VectorEdgeId): FaceBitSet;
  fillContourLeftMultiple(_0: MeshTopology, _1: VectorEdgePath): FaceBitSet;
  MeshTriPoint: {
    new(): MeshTriPoint;
    new(_0: EdgeId, _1: TriPointf): MeshTriPoint;
  };
  NoDefInitFaceId: {
    new(): NoDefInitFaceId;
  };
  NoDefInitVertId: {
    new(): NoDefInitVertId;
  };
  NoDefInitEdgeId: {
    new(): NoDefInitEdgeId;
  };
  NoDefInitUndirectedEdgeId: {
    new(): NoDefInitUndirectedEdgeId;
  };
  OffsetParameters: {
    new(): OffsetParameters;
  };
  SharpOffsetParameters: {
    new(): SharpOffsetParameters;
  };
  GeneralOffsetParameters: {
    new(): GeneralOffsetParameters;
  };
  OffsetMode: {Smooth: OffsetModeValue<0>, Standard: OffsetModeValue<1>, Sharpening: OffsetModeValue<2>};
  SignDetectionMode: {Unsigned: SignDetectionModeValue<0>, OpenVDB: SignDetectionModeValue<1>, ProjectionNormal: SignDetectionModeValue<2>, WindingRule: SignDetectionModeValue<3>, HoleWindingRule: SignDetectionModeValue<4>};
  thickenMesh(_0: Mesh, _1: number, _2: GeneralOffsetParameters): any;
  Plane3f: {
    new(): Plane3f;
    new(_0: Plane3d): Plane3f;
    new(_0: Vector3f, _1: number): Plane3f;
    fromDirAndPt(_0: Vector3f, _1: Vector3f): Plane3f;
  };
  extendHole(_0: Mesh, _1: EdgeId, _2: Plane3f): EdgeId;
  extendAllHoles(_0: Mesh, _1: Plane3f): VectorEdgeId;
  extendHoleWithOutput(_0: Mesh, _1: EdgeId, _2: Plane3f): any;
  extendAllHolesWithOutput(_0: Mesh, _1: Plane3f): any;
  Plane3d: {
    new(): Plane3d;
    new(_0: Plane3f): Plane3d;
    new(_0: Vector3d, _1: number): Plane3d;
    fromDirAndPt(_0: Vector3d, _1: Vector3d): Plane3d;
  };
  Reorder: {None: ReorderValue<0>, Lexicographically: ReorderValue<1>, AABBTree: ReorderValue<2>};
  PointCloud: {
    new(): PointCloud;
  };
  PointOnFace: {};
  findDistance(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null, _3: number): MeshMeshDistanceResult;
  findSignedDistance(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null, _3: number): MeshMeshSignedDistanceResult;
  findSignedDistanceAB(_0: MeshPart, _1: MeshPart): MeshMeshSignedDistanceResult;
  findSignedDistanceWithTransform(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null): MeshMeshSignedDistanceResult;
  findSignedDistanceWithLimit(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null, _3: number): MeshMeshSignedDistanceResult;
  IPointsToMeshProjector: {};
  PointsToMeshProjector: {
    new(): PointsToMeshProjector;
  };
  MeshProjectionParameters: {
    new(): MeshProjectionParameters;
  };
  findSignedDistancesByPoints(_0: Mesh, _1: VertCoords, _2: VertBitSet | null, _3: MeshProjectionParameters, _4: IPointsToMeshProjector | null): VertScalars;
  findSignedDistancesByMesh(_0: Mesh, _1: Mesh, _2: MeshProjectionParameters, _3: IPointsToMeshProjector | null): VertScalars;
  SegmPointf: {
    new(): SegmPointf;
  };
  SegmPointd: {
    new(): SegmPointd;
  };
  SymMatrix2b: {
    new(): SymMatrix2b;
  };
  SymMatrix2i: {
    new(): SymMatrix2i;
  };
  SymMatrix2ll: {
    new(): SymMatrix2ll;
  };
  SymMatrix2f: {
    new(): SymMatrix2f;
  };
  SymMatrix2d: {
    new(): SymMatrix2d;
  };
  SymMatrix3b: {
    new(): SymMatrix3b;
  };
  SymMatrix3i: {
    new(): SymMatrix3i;
  };
  SymMatrix3ll: {
    new(): SymMatrix3ll;
  };
  SymMatrix3f: {
    new(): SymMatrix3f;
  };
  SymMatrix3d: {
    new(): SymMatrix3d;
  };
  SymMatrix4b: {
    new(): SymMatrix4b;
  };
  SymMatrix4i: {
    new(): SymMatrix4i;
  };
  SymMatrix4ll: {
    new(): SymMatrix4ll;
  };
  SymMatrix4f: {
    new(): SymMatrix4f;
  };
  SymMatrix4d: {
    new(): SymMatrix4d;
  };
  TriPointf: {
    new(): TriPointf;
  };
  TriPointd: {
    new(): TriPointd;
  };
  StdVectori: {
    new(): StdVectori;
  };
  StdVectorf: {
    new(): StdVectorf;
  };
  cutMeshWithPolyline(_0: Mesh, _1: StdVectorf): any;
  StdVectord: {
    new(): StdVectord;
  };
  StdVectorll: {
    new(): StdVectorll;
  };
  StdVectorUi64: {
    new(): StdVectorUi64;
  };
  VectorVectori: {
    new(): VectorVectori;
  };
  Vectori: {
    new(): Vectori;
    new(_0: number): Vectori;
    new(_0: number, _1: number): Vectori;
  };
  VectorVectorf: {
    new(): VectorVectorf;
  };
  Vectorf: {
    new(): Vectorf;
    new(_0: number): Vectorf;
    new(_0: number, _1: number): Vectorf;
  };
  getAti(_0: Vectori, _1: number, _2: number): number;
  getAtf(_0: Vectorf, _1: number, _2: number): number;
  VectorVectord: {
    new(): VectorVectord;
  };
  Vectord: {
    new(): Vectord;
  };
  VectorVector2b: {
    new(): VectorVector2b;
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
  VectorVector2i: {
    new(): VectorVector2i;
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
  VectorVector2ll: {
    new(): VectorVector2ll;
  };
  Vector2ll: {
    new(): Vector2ll;
  };
  VectorVector2f: {
    new(): VectorVector2f;
  };
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
  VectorVector2d: {
    new(): VectorVector2d;
  };
  Vector2d: {
    new(): Vector2d;
  };
  VectorVector3b: {
    new(): VectorVector3b;
  };
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
  VectorVector3i: {
    new(): VectorVector3i;
  };
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
  VectorVector3ll: {
    new(): VectorVector3ll;
  };
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
  VectorVector3f: {
    new(): VectorVector3f;
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
  to3dimVecf(_0: Vector2f): Vector3f;
  to2dimVecf(_0: Vector3f): Vector2f;
  makeArrow(_0: Vector3f, _1: Vector3f, _2: number, _3: number, _4: number, _5: number): Mesh;
  createFindParams(_0: number, _1: number, _2: number, _3: number): FindParams;
  createFixParams(_0: FindParams, _1: number, _2: number, _3: boolean): FixParams;
  fixUndercuts(_0: Mesh, _1: Vector3f, _2: number, _3: number): any;
  fixUndercutsThrows(_0: Mesh, _1: Vector3f, _2: number, _3: number): void;
  buildBottom(_0: Mesh, _1: EdgeId, _2: Vector3f, _3: number): EdgeId;
  buildBottomWithOutput(_0: Mesh, _1: EdgeId, _2: Vector3f, _3: number): any;
  projectOnAllWithProgress(_0: Vector3f, _1: AABBTreeObjects, _2: number, _3: any, _4: ObjId): void;
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
  VectorVector3d: {
    new(): VectorVector3d;
  };
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
  to3dimVecd(_0: Vector2d): Vector3d;
  to2dimVecd(_0: Vector3d): Vector2d;
  unitVector3ll(_0: bigint, _1: bigint): Vector3d;
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
  VectorVector4b: {
    new(): VectorVector4b;
  };
  Vector4b: {
    new(): Vector4b;
  };
  VectorVector4i: {
    new(): VectorVector4i;
  };
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
  VectorVector4ll: {
    new(): VectorVector4ll;
  };
  Vector4ll: {
    new(): Vector4ll;
  };
  VectorVector4f: {
    new(): VectorVector4f;
  };
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
  VectorVector4d: {
    new(): VectorVector4d;
  };
  Vector4d: {
    new(): Vector4d;
  };
  VisualObject: {
    new(): VisualObject;
  };
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
