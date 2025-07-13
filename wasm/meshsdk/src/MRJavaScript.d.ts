// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
declare namespace RuntimeExports {
    /**
     * @param {string|null=} returnType
     * @param {Array=} argTypes
     * @param {IArguments|Array=} args
     * @param {Object=} opts
     */
    function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: (IArguments | any[]) | undefined, opts?: any | undefined): any;
    let HEAPU8: any;
    let HEAP32: any;
    let HEAPF32: any;
    let HEAPU32: any;
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
  _free(_0: number): void;
  _printtt(): void;
  _main(_0: number, _1: number): number;
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
export interface AABBTree extends ClassHandle {
}

export interface AABBTreeObjects extends ClassHandle {
}

export interface AABBTreePointsNode extends ClassHandle {
  box: Box3f;
  l: NodeId;
  r: NodeId;
}

export interface AABBTreePoints extends ClassHandle {
  heapBytes(): number;
  getBoundingBox(): Box3f;
  getLeafOrder(_0: VertBMap): void;
  getLeafOrderAndReset(_0: VertBMap): void;
  refit(_0: VertCoords, _1: VertBitSet): void;
  nodes(): NodeVec;
  orderedPoints(): VectorAABBTreePointsPoint;
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

export interface BooleanOperationValue<T extends number> {
  value: T;
}
export type BooleanOperation = BooleanOperationValue<0>|BooleanOperationValue<1>|BooleanOperationValue<2>|BooleanOperationValue<3>|BooleanOperationValue<4>|BooleanOperationValue<5>|BooleanOperationValue<6>|BooleanOperationValue<7>|BooleanOperationValue<8>;

export interface BooleanResultMapObjectValue<T extends number> {
  value: T;
}
export type BooleanResultMapObject = BooleanResultMapObjectValue<0>|BooleanResultMapObjectValue<1>|BooleanResultMapObjectValue<2>;

export interface BooleanResultMaps extends ClassHandle {
  identity: boolean;
  cut2origin: FaceMap;
  cut2newFaces: FaceMap;
  old2newVerts: VertMap;
  old2newEdges: WholeEdgeMap;
}

export interface BooleanInternalParameters extends ClassHandle {
  originalMeshA: Mesh | null;
  originalMeshB: Mesh | null;
  optionalOutCut: VectorEdgePath | null;
}

export interface BooleanResultMapper extends ClassHandle {
  map(_0: FaceBitSet, _1: BooleanResultMapObject): FaceBitSet;
  mapFaces(_0: FaceBitSet, _1: BooleanResultMapObject): FaceBitSet;
  mapVerts(_0: VertBitSet, _1: BooleanResultMapObject): VertBitSet;
  mapEdges(_0: EdgeBitSet, _1: BooleanResultMapObject): EdgeBitSet;
  newFaces(): FaceBitSet;
  filteredOldFaceBitSet(_0: FaceBitSet, _1: BooleanResultMapObject): FaceBitSet;
  getMaps(_0: BooleanResultMapObject): BooleanResultMaps;
}

export interface Box1f extends ClassHandle {
}

export interface Box1i extends ClassHandle {
}

export interface Box1ll extends ClassHandle {
}

export interface Box1d extends ClassHandle {
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

export interface Box2i extends ClassHandle {
}

export interface Box2ll extends ClassHandle {
}

export interface Box2d extends ClassHandle {
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

export interface Box3i extends ClassHandle {
}

export interface Box3ll extends ClassHandle {
}

export interface Box3d extends ClassHandle {
}

export interface FaceBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  heapBytes(): number;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  get(_0: FaceId): FaceId;
  set(_0: FaceId, _1: FaceId): void;
  dataConst(): FaceId | null;
  data(): NoDefInitFaceId | null;
}

export interface VertBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  heapBytes(): number;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  get(_0: VertId): VertId;
  set(_0: VertId, _1: VertId): void;
  dataConst(): VertId | null;
  data(): NoDefInitVertId | null;
}

export interface EdgeBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  heapBytes(): number;
  beginId(): EdgeId;
  backId(): EdgeId;
  endId(): EdgeId;
  get(_0: EdgeId): EdgeId;
  set(_0: EdgeId, _1: EdgeId): void;
  dataConst(): EdgeId | null;
  data(): NoDefInitEdgeId | null;
}

export interface UndirectedEdgeBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  heapBytes(): number;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  get(_0: UndirectedEdgeId): UndirectedEdgeId;
  set(_0: UndirectedEdgeId, _1: UndirectedEdgeId): void;
  dataConst(): UndirectedEdgeId | null;
  data(): NoDefInitUndirectedEdgeId | null;
}

export interface WholeEdgeBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  heapBytes(): number;
  beginId(): UndirectedEdgeId;
  backId(): UndirectedEdgeId;
  endId(): UndirectedEdgeId;
  get(_0: UndirectedEdgeId): EdgeId;
  set(_0: UndirectedEdgeId, _1: EdgeId): void;
  dataConst(): EdgeId | null;
  data(): NoDefInitEdgeId | null;
}

export interface FaceIdEdgeIdSizeTBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  beginId(): number;
  backId(): number;
  endId(): number;
  heapBytes(): number;
  get(_0: number): FaceId;
  set(_0: number, _1: FaceId): void;
  dataConst(): FaceId | null;
  data(): NoDefInitFaceId | null;
}

export interface VertIdSizeTBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  beginId(): number;
  backId(): number;
  endId(): number;
  heapBytes(): number;
  get(_0: number): VertId;
  set(_0: number, _1: VertId): void;
  dataConst(): VertId | null;
  data(): NoDefInitVertId | null;
}

export interface EdgeIdSizeTBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  beginId(): number;
  backId(): number;
  endId(): number;
  heapBytes(): number;
  get(_0: number): EdgeId;
  set(_0: number, _1: EdgeId): void;
  dataConst(): EdgeId | null;
  data(): NoDefInitEdgeId | null;
}

export interface UndirectedEdgeIdSizeTBMapBuffer extends ClassHandle {
  capacity(): number;
  size(): number;
  empty(): boolean;
  clear(): void;
  resize(_0: number): void;
  beginId(): number;
  backId(): number;
  endId(): number;
  heapBytes(): number;
  get(_0: number): UndirectedEdgeId;
  set(_0: number, _1: UndirectedEdgeId): void;
  dataConst(): UndirectedEdgeId | null;
  data(): NoDefInitUndirectedEdgeId | null;
}

export interface PackMapping extends ClassHandle {
  setV(_0: VertBMap): void;
  getV(): VertBMap | null;
  setVWithPtr(_0: VertBMap | null): void;
  setF(_0: FaceBMap): void;
  getF(): FaceBMap | null;
  setFWithPtr(_0: FaceBMap | null): void;
  setE(_0: UndirectedEdgeBMap): void;
  getE(): UndirectedEdgeBMap | null;
  setEWithPtr(_0: UndirectedEdgeBMap | null): void;
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

export interface NewEdgesMap extends ClassHandle {
  splitEdges: UndirectedEdgeBitSet;
  map: UndirectedEdgeIdIntHashMap;
}

export interface ForceFillValue<T extends number> {
  value: T;
}
export type ForceFill = ForceFillValue<0>|ForceFillValue<1>|ForceFillValue<2>;

export interface CutMeshParameters extends ClassHandle {
  forceFillMode: ForceFill;
  new2oldEdgesMap: NewEdgesMap | null;
  new2OldMap: FaceMap | null;
  sortData: SortIntersectionsData | null;
}

export interface Dipole extends ClassHandle {
  area: number;
  rr: number;
  pos: Vector3f;
  dirArea: Vector3f;
  addIfGoodApprox(_0: Vector3f, _1: number, _2: number): any;
}

export interface EdgeLengthMesh extends ClassHandle {
  edgeLengths: UndirectedEdgeScalars;
  topology: MeshTopology;
  cotan(_0: UndirectedEdgeId): number;
  isDelone(_0: UndirectedEdgeId, _1: number): boolean;
  leftCotan(_0: EdgeId): number;
  flipEdge(_0: EdgeId): boolean;
  edgeLengthAfterFlip(_0: EdgeId): number | undefined;
}

export interface EdgeMetricWrapper extends ClassHandle {
  evaluate(_0: EdgeId): number;
}

export interface EdgePoint extends ClassHandle {
  e: EdgeId;
  a: SegmPointf;
  inVertex(): boolean;
  moveToClosestVertex(): void;
  valid(): boolean;
  opbool(): boolean;
  sym(): EdgePoint;
  equals(_0: EdgePoint): boolean;
  inVertexFromMeshTopology(_0: MeshTopology): VertId;
  getClosestVertex(_0: MeshTopology): VertId;
  isBd(_0: MeshTopology, _1: FaceBitSet | null): boolean;
  inVertexFromPolylineTopology(_0: PolylineTopology): VertId;
  getClosestVertexFromPolylineTopology(_0: PolylineTopology): VertId;
}

export interface EdgePointPair extends ClassHandle {
  a: EdgePoint;
  b: EdgePoint;
  equals(_0: EdgePointPair): boolean;
}

export interface EdgeSegment extends ClassHandle {
  e: EdgeId;
  a: SegmPointf;
  b: SegmPointf;
  edgePointA(): EdgePoint;
  edgePointB(): EdgePoint;
  valid(): boolean;
  equals(_0: EdgeSegment): boolean;
  sym(): EdgeSegment;
}

export interface VertexMassValue<T extends number> {
  value: T;
}
export type VertexMass = VertexMassValue<0>|VertexMassValue<1>;

export interface EdgeWeightsValue<T extends number> {
  value: T;
}
export type EdgeWeights = EdgeWeightsValue<0>|EdgeWeightsValue<1>;

export interface ProcessingValue<T extends number> {
  value: T;
}
export type Processing = ProcessingValue<0>|ProcessingValue<1>;

export interface OrientNormalsValue<T extends number> {
  value: T;
}
export type OrientNormals = OrientNormalsValue<0>|OrientNormalsValue<1>|OrientNormalsValue<2>;

export interface OffsetModeValue<T extends number> {
  value: T;
}
export type OffsetMode = OffsetModeValue<0>|OffsetModeValue<1>|OffsetModeValue<2>;

export interface ColoringTypeValue<T extends number> {
  value: T;
}
export type ColoringType = ColoringTypeValue<0>|ColoringTypeValue<1>|ColoringTypeValue<1>|ColoringTypeValue<1>|ColoringTypeValue<2>;

export interface UseAABBTreeValue<T extends number> {
  value: T;
}
export type UseAABBTree = UseAABBTreeValue<0>|UseAABBTreeValue<1>|UseAABBTreeValue<2>;

export interface GeodesicPathApproxValue<T extends number> {
  value: T;
}
export type GeodesicPathApprox = GeodesicPathApproxValue<0>|GeodesicPathApproxValue<1>|GeodesicPathApproxValue<2>;

export interface ExpectedVoid extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  hasError(): boolean;
  error(): string;
}

export interface ExpectedMeshTopology extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): MeshTopology;
  get(): MeshTopology;
  valueOr(_0: MeshTopology): MeshTopology;
  getValuePtr(): MeshTopology | null;
}

export interface ExpectedMesh extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): Mesh;
  get(): Mesh;
  valueOr(_0: Mesh): Mesh;
  getValuePtr(): Mesh | null;
}

export interface ExpectedEdgeLengthMesh extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  value(): EdgeLengthMesh;
  error(): string;
  hasError(): boolean;
  getValuePtr(): EdgeLengthMesh | null;
  get(): EdgeLengthMesh;
  valueOr(_0: EdgeLengthMesh): EdgeLengthMesh;
}

export interface ExpectedMeshOrPoints extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): MeshOrPoints;
  get(): MeshOrPoints;
  valueOr(_0: MeshOrPoints): MeshOrPoints;
  getValuePtr(): MeshOrPoints | null;
}

export interface ExpectedPointCloud extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): PointCloud;
  get(): PointCloud;
  valueOr(_0: PointCloud): PointCloud;
  getValuePtr(): PointCloud | null;
}

export interface ExpectedAABBTree extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  value(): AABBTree;
  error(): string;
  hasError(): boolean;
  getValuePtr(): AABBTree | null;
  get(): AABBTree;
}

export interface ExpectedAABBTreePoints extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  value(): AABBTreePoints;
  error(): string;
  hasError(): boolean;
  getValuePtr(): AABBTreePoints | null;
  get(): AABBTreePoints;
}

export interface ExpectedAABBTreeObjects extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  value(): AABBTreeObjects;
  error(): string;
  hasError(): boolean;
  getValuePtr(): AABBTreeObjects | null;
  get(): AABBTreeObjects;
  valueOr(_0: AABBTreeObjects): AABBTreeObjects;
}

export interface ExpectedCloudPartMapping extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  value(): CloudPartMapping;
  error(): string;
  hasError(): boolean;
  getValuePtr(): CloudPartMapping | null;
  get(): CloudPartMapping;
  valueOr(_0: CloudPartMapping): CloudPartMapping;
}

export interface ExpectedPartMapping extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): PartMapping;
  get(): PartMapping;
  valueOr(_0: PartMapping): PartMapping;
  getValuePtr(): PartMapping | null;
}

export interface ExpectedMeshOrPointsXf extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): MeshOrPointsXf;
  get(): MeshOrPointsXf;
  valueOr(_0: MeshOrPointsXf): MeshOrPointsXf;
  getValuePtr(): MeshOrPointsXf | null;
}

export interface ExpectedMeshTexture extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): MeshTexture;
  get(): MeshTexture;
  valueOr(_0: MeshTexture): MeshTexture;
  getValuePtr(): MeshTexture | null;
}

export interface ExpectedGridSettings extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): GridSettings;
  get(): GridSettings;
  getValuePtr(): GridSettings | null;
}

export interface ExpectedTriMesh extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): TriMesh;
  get(): TriMesh;
  valueOr(_0: TriMesh): TriMesh;
  getValuePtr(): TriMesh | null;
}

export interface ExpectedPackMapping extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  value(): PackMapping;
  error(): string;
  hasError(): boolean;
  getValuePtr(): PackMapping | null;
  get(): PackMapping;
}

export interface ExpectedEdgePath extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): VectorEdgeId;
  get(): VectorEdgeId;
  valueOr(_0: VectorEdgeId): VectorEdgeId;
  getValuePtr(): VectorEdgeId | null;
}

export interface ExpectedEdgeLoops extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): VectorEdgePath;
  get(): VectorEdgePath;
  valueOr(_0: VectorEdgePath): VectorEdgePath;
  getValuePtr(): VectorEdgePath | null;
}

export interface ExpectedOneMeshContour extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): OneMeshContour;
  get(): OneMeshContour;
  valueOr(_0: OneMeshContour): OneMeshContour;
  getValuePtr(): OneMeshContour | null;
}

export interface ExpectedSurfacePath extends ClassHandle {
  hasValue(): boolean;
  opbool(): boolean;
  error(): string;
  hasError(): boolean;
  value(): SurfacePath;
  get(): SurfacePath;
  valueOr(_0: SurfacePath): SurfacePath;
  getValuePtr(): SurfacePath | null;
}

export interface MeshSegmentation extends ClassHandle {
  segmentByPoints(_0: StdVectorf, _1: StdVectorf): any;
}

export interface FillHoleNicelySettings extends ClassHandle {
  triangulateOnly: boolean;
  maxEdgeLen: number;
  maxEdgeSplits: number;
  maxAngleChangeAfterFlip: number;
  smoothCurvature: boolean;
  naturalSmooth: boolean;
  edgeWeights: EdgeWeights;
  vmass: VertexMass;
  triangulateParams: FillHoleParams;
  uvCoords: VertCoords2 | null;
  colorMap: VertColors | null;
  faceColors: FaceColors | null;
  onEdgeSplit: VoidFunctorEdgeIdEdgeId;
  beforeEdgeSplit: EdgePredicate;
}

export interface FixParams extends ClassHandle {
  voxelSize: number;
  bottomExtension: number;
  smooth: boolean;
  findParameters: FindParams;
}

export interface FreeFormDeformer extends ClassHandle {
  apply(): void;
  getAllRefGridPositions(): VectorVector3f;
  setAllRefGridPositions(_0: VectorVector3f): void;
  applySinglePoint(_0: Vector3f): Vector3f;
  init(_0: Vector3i, _1: Box3f): void;
  setRefGridPointPosition(_0: Vector3i, _1: Vector3f): void;
  getRefGridPointPosition(_0: Vector3i): Vector3f;
  getIndex(_0: Vector3i): number;
  getCoord(_0: number): Vector3i;
  getResolution(): Vector3i;
}

export interface FreeFormBestFit extends ClassHandle {
  addOther(_0: FreeFormBestFit): void;
  setStabilizer(_0: number): void;
  getStabilizer(): number;
  findBestDeformationReferenceGrid(): VectorVector3f;
  addPairf(_0: Vector3f, _1: Vector3f, _2: number): void;
  addPaird(_0: Vector3d, _1: Vector3d, _2: number): void;
}

export interface ModelPointsData extends ClassHandle {
  validPoints: VertBitSet | null;
  xf: AffineXf3f | null;
  fakeObjId: ObjId;
  points: VertCoords | null;
}

export interface ObjVertId extends ClassHandle {
  vId: VertId;
  objId: ObjId;
  equals(_0: ObjVertId): boolean;
}

export interface EdgeTypeValue<T extends number> {
  value: T;
}
export type EdgeType = EdgeTypeValue<0>|EdgeTypeValue<1>|EdgeTypeValue<2>|EdgeTypeValue<3>;

export interface TriTypeValue<T extends number> {
  value: T;
}
export type TriType = TriTypeValue<0>|TriTypeValue<1>;

export interface GridSettings extends ClassHandle {
  dim: Vector2i;
  setVertIds(_0: VertIdSizeTBMap): void;
  getVertIds(): VertIdSizeTBMap | null;
  setVertIdsWithPtr(_0: VertIdSizeTBMap | null): void;
  setUEdgeIds(_0: UndirectedEdgeIdSizeTBMap): void;
  getUEdgeIds(): UndirectedEdgeIdSizeTBMap | null;
  setUEdgeIdsWithPtr(_0: UndirectedEdgeIdSizeTBMap | null): void;
  setFaceIds(_0: FaceIdSizeTBMap): void;
  getFaceIds(): FaceIdSizeTBMap | null;
  setFaceIdsWithPtr(_0: FaceIdSizeTBMap | null): void;
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

export interface MyClass extends ClassHandle {
  x: number;
  readonly x_readonly: number;
  incrementX(): void;
}

export interface RememberShapeValue<T extends number> {
  value: T;
}
export type RememberShape = RememberShapeValue<0>|RememberShapeValue<1>;

export interface Laplacian extends ClassHandle {
  init(_0: VertBitSet, _1: EdgeWeights, _2: VertexMass, _3: RememberShape): void;
  updateSolver(): void;
  apply(): void;
  region(): VertBitSet;
  freeVerts(): VertBitSet;
  firstLayerFixedVerts(): VertBitSet;
  fixVertex(_0: VertId, _1: boolean): void;
  applyToScalar(_0: VertScalars): void;
  fixVertexWithPos(_0: VertId, _1: Vector3f, _2: boolean): void;
}

export interface Line2f extends ClassHandle {
  p: Vector2f;
  d: Vector2f;
  normalized(): Line2f;
  project(_0: Vector2f): Vector2f;
  distanceSq(_0: Vector2f): number;
  opcall(_0: number): Vector2f;
}

export interface Line2d extends ClassHandle {
  p: Vector2d;
  d: Vector2d;
  normalized(): Line2d;
  project(_0: Vector2d): Vector2d;
  distanceSq(_0: Vector2d): number;
  opcall(_0: number): Vector2d;
}

export interface Line3f extends ClassHandle {
  p: Vector3f;
  d: Vector3f;
  normalized(): Line3f;
  project(_0: Vector3f): Vector3f;
  distanceSq(_0: Vector3f): number;
  opcall(_0: number): Vector3f;
}

export interface Line3d extends ClassHandle {
  p: Vector3d;
  d: Vector3d;
  normalized(): Line3d;
  project(_0: Vector3d): Vector3d;
  distanceSq(_0: Vector3d): number;
  opcall(_0: number): Vector3d;
}

export interface LineSegm2f extends ClassHandle {
  a: Vector2f;
  b: Vector2f;
  lengthSq(): number;
  length(): number;
  equals(_0: LineSegm2f): boolean;
  dir(): Vector2f;
  opcall(_0: number): Vector2f;
}

export interface LineSegm2d extends ClassHandle {
  a: Vector2d;
  b: Vector2d;
  lengthSq(): number;
  length(): number;
  equals(_0: LineSegm2d): boolean;
  dir(): Vector2d;
  opcall(_0: number): Vector2d;
}

export interface LineSegm3f extends ClassHandle {
  a: Vector3f;
  b: Vector3f;
  lengthSq(): number;
  length(): number;
  equals(_0: LineSegm3f): boolean;
  dir(): Vector3f;
  opcall(_0: number): Vector3f;
}

export interface LineSegm3d extends ClassHandle {
  a: Vector3d;
  b: Vector3d;
  lengthSq(): number;
  length(): number;
  equals(_0: LineSegm3d): boolean;
  dir(): Vector3d;
  opcall(_0: number): Vector3d;
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
  points: VertCoords;
  topology: MeshTopology;
  equals(_0: Mesh): boolean;
  volume(_0: FaceBitSet | null): number;
  getBoundingBox(): Box3f;
  computeBoundingBoxWithFaceBitSet(_0: AffineXf3f | null): Box3f;
  computeBoundingBox(_0: FaceBitSet | null, _1: AffineXf3f | null): Box3f;
  transform(_0: AffineXf3f, _1: VertBitSet | null): void;
  deleteFaces(_0: FaceBitSet, _1: UndirectedEdgeBitSet | null): void;
  getAABBTree(): AABBTree | null;
  getAABBTreeNotCreate(): AABBTree | null;
  getAABBTreePoints(): AABBTreePoints | null;
  getAABBTreePointsNotCreate(): AABBTreePoints | null;
  invalidateCaches(_0: boolean): void;
  updateCaches(_0: VertBitSet): void;
  heapBytes(): number;
  shrinkToFit(): void;
  edgeSegment(_0: EdgeId): LineSegm3f;
  triangleAspectRatio(_0: FaceId): number;
  circumcircleDiameterSq(_0: FaceId): number;
  circumcircleDiameter(_0: FaceId): number;
  getDipolesNotCreate(): Dipoles | null;
  addMesh(_0: Mesh, _1: FaceMap | null, _2: VertMap | null, _3: WholeEdgeMap | null, _4: boolean): void;
  packWithMap(_0: FaceMap | null, _1: VertMap | null, _2: WholeEdgeMap | null, _3: boolean): void;
  toTriPoint(_0: VertId): MeshTriPoint;
  getClosestVertexWithMeshTriPoint(_0: MeshTriPoint): VertId;
  getClosestEdgeWithMeshTriPoint(_0: MeshTriPoint): UndirectedEdgeId;
  addMeshWithPartMapping(_0: Mesh, _1: PartMapping, _2: boolean): void;
  addMeshPartWithPartMapping(_0: MeshPart, _1: PartMapping): void;
  cloneRegion(_0: FaceBitSet, _1: boolean, _2: PartMapping): Mesh;
  packWithPartMapping(_0: PartMapping, _1: boolean): void;
  mirror(_0: Plane3f): void;
  toTriPointWithPointOnFace(_0: PointOnFace): MeshTriPoint;
  getClosestVertex(_0: PointOnFace): VertId;
  getClosestEdge(_0: PointOnFace): UndirectedEdgeId;
  addMeshPart(_0: MeshPart, _1: boolean, _2: VectorEdgePath, _3: VectorEdgePath, _4: PartMapping): void;
  addSeparateEdgeLoop(_0: VectorVector3f): EdgeId;
  attachEdgeLoopPart(_0: EdgeId, _1: EdgeId, _2: VectorVector3f): void;
  addSeparateContours(_0: VectorVectorVector3f, _1: AffineXf3f | null): EdgeId;
  pack(_0: PackMapping, _1: ProgressCallback): ExpectedVoid;
  orgPnt(_0: EdgeId): Vector3f;
  destPnt(_0: EdgeId): Vector3f;
  edgeVector(_0: EdgeId): Vector3f;
  edgePoint(_0: EdgeId, _1: number): Vector3f;
  edgeCenter(_0: UndirectedEdgeId): Vector3f;
  getLeftTriPoints(_0: EdgeId, _1: Vector3f, _2: Vector3f, _3: Vector3f): void;
  getTriPoints(_0: FaceId, _1: Vector3f, _2: Vector3f, _3: Vector3f): void;
  triPoint(_0: MeshTriPoint): Vector3f;
  triCenter(_0: FaceId): Vector3f;
  toTriPointWithFaceId(_0: FaceId, _1: Vector3f): MeshTriPoint;
  normalWithFaceId(_0: FaceId): Vector3f;
  normalWithMeshTriPoint(_0: VertId): Vector3f;
  normal(_0: MeshTriPoint): Vector3f;
  addPoint(_0: Vector3f): VertId;
  projectPointWithPointOnFace(_0: Vector3f, _1: PointOnFace, _2: number, _3: FaceBitSet | null, _4: AffineXf3f | null): boolean;
  projectPointWithProjectionResult(_0: Vector3f, _1: MeshProjectionResult, _2: number, _3: FaceBitSet | null, _4: AffineXf3f | null): boolean;
  projectPoint(_0: Vector3f, _1: number, _2: FaceBitSet | null, _3: AffineXf3f | null): MeshProjectionResult;
  findClosestPointWithProjectionResult(_0: Vector3f, _1: MeshProjectionResult, _2: number, _3: FaceBitSet | null, _4: AffineXf3f | null): boolean;
  findClosestPoint(_0: Vector3f, _1: number, _2: FaceBitSet | null, _3: AffineXf3f | null): MeshProjectionResult;
  signedDistance(_0: Vector3f): number;
  getLeftTriPointsWithTriangle3f(_0: EdgeId): Array3Triangle3f;
  getTriPointsWithTriangle3f(_0: FaceId): Array3Triangle3f;
}

export interface MeshWrapper extends ClassHandle {
  mesh: Mesh;
  getMesh(): Mesh | null;
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
  fillHolesImpl(): any;
  projectPoint(_0: any, _1: number): any;
  transform(_0: any): void;
  pack(): void;
  thickenMeshImpl(_0: number, _1: GeneralOffsetParameters): any;
  cutMeshWithPolylineImpl(_0: StdVectorf): any;
  segmentByPointsImpl(_0: StdVectorf, _1: StdVectorf, _2: EdgeMetricWrapper): any;
  fixUndercutsImpl(_0: Vector3f): any;
}

export interface BooleanResult extends ClassHandle {
  mesh: Mesh;
  meshABadContourFaces: FaceBitSet;
  meshBBadContourFaces: FaceBitSet;
  get errorString(): string;
  set errorString(value: EmbindString);
  valid(): boolean;
  getMesh(): Mesh;
}

export interface UniteCloseParams extends ClassHandle {
  closeDist: number;
  uniteOnlyBd: boolean;
  region: VertBitSet | null;
  duplicateNonManifold: boolean;
  optionalVertOldToNew: VertMap | null;
  optionalDuplications: VectorVertDuplication | null;
}

export interface Triangle extends ClassHandle {
  f: FaceId;
  v: Array3VertId;
  equals(_0: Triangle): boolean;
}

export interface BuildSettings extends ClassHandle {
  shiftFaceId: number;
  allowNonManifoldEdge: boolean;
  getRegion(): FaceBitSet | null;
  setRegion(_0: FaceBitSet): void;
  setRegionCopy(_0: FaceBitSet): void;
  setRegionWithPtr(_0: FaceBitSet | null): void;
  getSkippedFaceCount(): number;
  setSkippedFaceCount(_0: number): void;
}

export type VertSpan = {
  firstVertex: number,
  lastVertex: number
};

export interface EdgeTri extends ClassHandle {
  edge: EdgeId;
  tri: FaceId;
}

export interface FlaggedTri extends ClassHandle {
  getIsEdgeATriB(): boolean;
  setIsEdgeATriB(_0: boolean): void;
  getFace(): number;
  setFace(_0: number): void;
  equals(_0: FlaggedTri): boolean;
}

export interface VarEdgeTri extends ClassHandle {
  flaggedTri: FlaggedTri;
  edge: EdgeId;
  isEdgeATriB(): boolean;
  edgeTri(): EdgeTri;
  valid(): boolean;
  opbool(): boolean;
  equals(_0: VarEdgeTri): boolean;
  tri(): FaceId;
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
  insert(_0: VertId, _1: VertId): void;
  get(_0: VertId): any;
  has(_0: VertId): boolean;
  erase(_0: VertId): void;
  keys(): VectorVertId;
  values(): VectorVertId;
}

export interface FaceHashMap extends ClassHandle {
}

export interface EdgeHashMap extends ClassHandle {
}

export interface UndirectedEdgeHashMap extends ClassHandle {
}

export interface WholeEdgeHashMap extends ClassHandle {
}

export interface UndirectedEdgeIdIntHashMap extends ClassHandle {
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

export interface StitchHolesParams extends ClassHandle {
  outNewFaces: FaceBitSet | null;
  metric: FillHoleMetric;
}

export interface FillHoleParams extends ClassHandle {
  outNewFaces: FaceBitSet | null;
  makeDegenerateBand: boolean;
  maxPolygonSubdivisions: number;
  metric: FillHoleMetric;
  getStopBeforeBadTriangulation(): boolean;
  setStopBeforeBadTriangulation(_0: boolean): void;
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

export type VertDuplication = {
  srcVert: VertId,
  dupVert: VertId
};

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
  getB(): VertBMapBuffer | null;
  setB(_0: VertBMapBuffer): void;
  setBWithPtr(_0: VertBMapBuffer | null): void;
}

export interface FaceBMap extends ClassHandle {
  tsize: number;
  getB(): FaceBMapBuffer | null;
  setB(_0: FaceBMapBuffer): void;
  setBWithPtr(_0: FaceBMapBuffer | null): void;
}

export interface EdgeBMap extends ClassHandle {
  tsize: number;
  getB(): EdgeBMapBuffer | null;
  setB(_0: EdgeBMapBuffer): void;
  setBWithPtr(_0: EdgeBMapBuffer | null): void;
}

export interface UndirectedEdgeBMap extends ClassHandle {
  tsize: number;
  getB(): UndirectedEdgeBMapBuffer | null;
  setB(_0: UndirectedEdgeBMapBuffer): void;
  setBWithPtr(_0: UndirectedEdgeBMapBuffer | null): void;
}

export interface WholeEdgeBMap extends ClassHandle {
  tsize: number;
  getB(): WholeEdgeBMapBuffer | null;
  setB(_0: WholeEdgeBMapBuffer): void;
  setBWithPtr(_0: WholeEdgeBMapBuffer | null): void;
}

export interface VertIdSizeTBMap extends ClassHandle {
  tsize: number;
  getB(): VertIdSizeTBMapBuffer | null;
  setB(_0: VertIdSizeTBMapBuffer): void;
  setBWithPtr(_0: VertIdSizeTBMapBuffer | null): void;
}

export interface UndirectedEdgeIdSizeTBMap extends ClassHandle {
  tsize: number;
  getB(): UndirectedEdgeIdSizeTBMapBuffer | null;
  setB(_0: UndirectedEdgeIdSizeTBMapBuffer): void;
  setBWithPtr(_0: UndirectedEdgeIdSizeTBMapBuffer | null): void;
}

export interface FaceIdSizeTBMap extends ClassHandle {
  tsize: number;
  getB(): FaceIdEdgeIdSizeTBMapBuffer | null;
  setB(_0: FaceIdEdgeIdSizeTBMapBuffer): void;
  setBWithPtr(_0: FaceIdEdgeIdSizeTBMapBuffer | null): void;
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

export interface VertIdEdgeIdMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: VertId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: VertId): void;
  get(_0: EdgeId): VertId;
  set(_0: EdgeId, _1: VertId): void;
  getByIndex(_0: EdgeId): VertId;
  getByIndexMutable(_0: EdgeId): VertId;
  getAt(_0: EdgeId): VertId;
  setAt(_0: EdgeId, _1: VertId): boolean;
  front(): VertId;
  frontMutable(): VertId;
  back(): VertId;
  backMutable(): VertId;
  pushBack(_0: VertId): void;
  popBack(): void;
  emplaceBack(_0: VertId): VertId;
  beginId(): EdgeId;
  backId(): EdgeId;
  endId(): EdgeId;
  autoResizeAt(_0: EdgeId): VertId;
  autoResizeSet(_0: EdgeId, _1: VertId): void;
  autoResizeSetRange(_0: EdgeId, _1: number, _2: VertId): void;
  swap(_0: VertIdEdgeIdMap): void;
  heapBytes(): number;
  equals(_0: VertIdEdgeIdMap): boolean;
  notEquals(_0: VertIdEdgeIdMap): boolean;
}

export interface EdgeIdVertIdMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: EdgeId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: EdgeId): void;
  get(_0: VertId): EdgeId;
  set(_0: VertId, _1: EdgeId): void;
  getByIndex(_0: VertId): EdgeId;
  getByIndexMutable(_0: VertId): EdgeId;
  getAt(_0: VertId): EdgeId;
  setAt(_0: VertId, _1: EdgeId): boolean;
  front(): EdgeId;
  frontMutable(): EdgeId;
  back(): EdgeId;
  backMutable(): EdgeId;
  pushBack(_0: EdgeId): void;
  popBack(): void;
  emplaceBack(_0: EdgeId): EdgeId;
  beginId(): VertId;
  backId(): VertId;
  endId(): VertId;
  autoResizeAt(_0: VertId): EdgeId;
  autoResizeSet(_0: VertId, _1: EdgeId): void;
  autoResizeSetRange(_0: VertId, _1: number, _2: EdgeId): void;
  swap(_0: EdgeIdVertIdMap): void;
  heapBytes(): number;
  equals(_0: EdgeIdVertIdMap): boolean;
  notEquals(_0: EdgeIdVertIdMap): boolean;
}

export interface EdgeIdFaceIdMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: EdgeId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: EdgeId): void;
  get(_0: FaceId): EdgeId;
  set(_0: FaceId, _1: EdgeId): void;
  getByIndex(_0: FaceId): EdgeId;
  getByIndexMutable(_0: FaceId): EdgeId;
  getAt(_0: FaceId): EdgeId;
  setAt(_0: FaceId, _1: EdgeId): boolean;
  front(): EdgeId;
  frontMutable(): EdgeId;
  back(): EdgeId;
  backMutable(): EdgeId;
  pushBack(_0: EdgeId): void;
  popBack(): void;
  emplaceBack(_0: EdgeId): EdgeId;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): EdgeId;
  autoResizeSet(_0: FaceId, _1: EdgeId): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: EdgeId): void;
  swap(_0: EdgeIdFaceIdMap): void;
  heapBytes(): number;
  equals(_0: EdgeIdFaceIdMap): boolean;
  notEquals(_0: EdgeIdFaceIdMap): boolean;
}

export interface FaceIdEdgeIdMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: FaceId): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: FaceId): void;
  get(_0: EdgeId): FaceId;
  set(_0: EdgeId, _1: FaceId): void;
  getByIndex(_0: EdgeId): FaceId;
  getByIndexMutable(_0: EdgeId): FaceId;
  getAt(_0: EdgeId): FaceId;
  setAt(_0: EdgeId, _1: FaceId): boolean;
  front(): FaceId;
  frontMutable(): FaceId;
  back(): FaceId;
  backMutable(): FaceId;
  pushBack(_0: FaceId): void;
  popBack(): void;
  emplaceBack(_0: FaceId): FaceId;
  beginId(): EdgeId;
  backId(): EdgeId;
  endId(): EdgeId;
  autoResizeAt(_0: EdgeId): FaceId;
  autoResizeSet(_0: EdgeId, _1: FaceId): void;
  autoResizeSetRange(_0: EdgeId, _1: number, _2: FaceId): void;
  swap(_0: FaceIdEdgeIdMap): void;
  heapBytes(): number;
  equals(_0: FaceIdEdgeIdMap): boolean;
  notEquals(_0: FaceIdEdgeIdMap): boolean;
}

export interface ModelPointsDataObjIdMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: ModelPointsData): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: ModelPointsData): void;
  get(_0: ObjId): ModelPointsData;
  set(_0: ObjId, _1: ModelPointsData): void;
  getByIndex(_0: ObjId): ModelPointsData;
  getByIndexMutable(_0: ObjId): ModelPointsData;
  getAt(_0: ObjId): ModelPointsData;
  setAt(_0: ObjId, _1: ModelPointsData): boolean;
  front(): ModelPointsData;
  frontMutable(): ModelPointsData;
  back(): ModelPointsData;
  backMutable(): ModelPointsData;
  pushBack(_0: ModelPointsData): void;
  popBack(): void;
  emplaceBack(_0: ModelPointsData): ModelPointsData;
  beginId(): ObjId;
  backId(): ObjId;
  endId(): ObjId;
  autoResizeAt(_0: ObjId): ModelPointsData;
  autoResizeSet(_0: ObjId, _1: ModelPointsData): void;
  autoResizeSetRange(_0: ObjId, _1: number, _2: ModelPointsData): void;
  swap(_0: ModelPointsDataObjIdMap): void;
  heapBytes(): number;
}

export interface VertSpanFaceIdMap extends ClassHandle {
  size(): number;
  empty(): boolean;
  clear(): void;
  capacity(): number;
  reserve(_0: number): void;
  resize(_0: number): void;
  resizeWithValue(_0: number, _1: VertSpan): void;
  resizeWithReserve(_0: number): void;
  resizeWithReserveAndValue(_0: number, _1: VertSpan): void;
  get(_0: FaceId): VertSpan;
  set(_0: FaceId, _1: VertSpan): void;
  getByIndex(_0: FaceId): VertSpan;
  getByIndexMutable(_0: FaceId): VertSpan;
  getAt(_0: FaceId): VertSpan;
  setAt(_0: FaceId, _1: VertSpan): boolean;
  front(): VertSpan;
  frontMutable(): VertSpan;
  back(): VertSpan;
  backMutable(): VertSpan;
  pushBack(_0: VertSpan): void;
  popBack(): void;
  emplaceBack(_0: VertSpan): VertSpan;
  beginId(): FaceId;
  backId(): FaceId;
  endId(): FaceId;
  autoResizeAt(_0: FaceId): VertSpan;
  autoResizeSet(_0: FaceId, _1: VertSpan): void;
  autoResizeSetRange(_0: FaceId, _1: number, _2: VertSpan): void;
  swap(_0: VertSpanFaceIdMap): void;
  heapBytes(): number;
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
  fromTrianglesDuplicatingNonManifoldVertices(_0: Triangulation, _1: VectorVertDuplication | null, _2: BuildSettings): Mesh;
  fromTriangles(_0: Triangulation, _1: BuildSettings, _2: ProgressCallback): Mesh;
  fromFaceSoup(_0: VectorVertId, _1: VertSpanFaceIdMap, _2: BuildSettings, _3: ProgressCallback): Mesh;
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

export interface FilterTypeValue<T extends number> {
  value: T;
}
export type FilterType = FilterTypeValue<0>|FilterTypeValue<1>;

export interface WrapTypeValue<T extends number> {
  value: T;
}
export type WrapType = WrapTypeValue<0>|WrapTypeValue<1>|WrapTypeValue<2>;

export interface ReorderValue<T extends number> {
  value: T;
}
export type Reorder = ReorderValue<0>|ReorderValue<1>|ReorderValue<2>;

export interface MeshLoadWrapper extends ClassHandle {
}

export interface FillHoleMetric extends ClassHandle {
}

export interface FillTriangleMetric extends ClassHandle {
}

export interface FillEdgeMetric extends ClassHandle {
}

export interface FillCombineMetric extends ClassHandle {
}

export interface FillHoleMetricWrapper extends ClassHandle {
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
  opbool(): boolean;
}

export interface SubdivideSettings extends ClassHandle {
  maxEdgeLen: number;
  maxEdgeSplits: number;
  maxDeviationAfterFlip: number;
  maxAngleChangeAfterFlip: number;
  criticalAspectRatioFlip: number;
  region: FaceBitSet | null;
  notFlippable: UndirectedEdgeBitSet | null;
  newVerts: VertBitSet | null;
  subdivideBorder: boolean;
  maxTriAspectRatio: number;
  maxSplittableTriAspectRatio: number;
  smoothMode: boolean;
  minSharpDihedralAngle: number;
  projectOnOriginalMesh: boolean;
}

export interface MeshTexture extends ClassHandle {
  filter: FilterType;
  wrap: WrapType;
}

export interface MeshTopology extends ClassHandle {
  makeEdge(): EdgeId;
  isLoneEdge(_0: EdgeId): boolean;
  lastNotLoneEdge(): EdgeId;
  excludeLoneEdges(_0: UndirectedEdgeBitSet): void;
  edgeSize(): number;
  edgeCapacity(): number;
  undirectedEdgeSize(): number;
  undirectedEdgeCapacity(): number;
  computeNotLoneUndirectedEdges(): number;
  findNotLoneUndirectedEdges(): UndirectedEdgeBitSet;
  edgeReserve(_0: number): void;
  hasEdge(_0: EdgeId): boolean;
  heapBytes(): number;
  shrinkToFit(): void;
  splice(_0: EdgeId, _1: EdgeId): void;
  next(_0: EdgeId): EdgeId;
  prev(_0: EdgeId): EdgeId;
  org(_0: EdgeId): VertId;
  dest(_0: EdgeId): VertId;
  left(_0: EdgeId): FaceId;
  right(_0: EdgeId): FaceId;
  setOrg(_0: EdgeId, _1: VertId): void;
  setLeft(_0: EdgeId, _1: FaceId): void;
  fromSameOriginRing(_0: EdgeId, _1: EdgeId): boolean;
  fromSameLeftRing(_0: EdgeId, _1: EdgeId): boolean;
  getOrgDegree(_0: EdgeId): number;
  getVertDegree(_0: VertId): number;
  getLeftDegree(_0: EdgeId): number;
  getFaceDegree(_0: FaceId): number;
  isLeftTri(_0: EdgeId): boolean;
  getTriVerts(_0: FaceId, _1: VertId, _2: VertId, _3: VertId): void;
  isTriVert(_0: FaceId, _1: VertId): boolean;
  getTriangulation(): Triangulation;
  getLeftTriVerts(_0: EdgeId, _1: VertId, _2: VertId, _3: VertId): void;
  getLeftTriEdges(_0: EdgeId, _1: EdgeId, _2: EdgeId): void;
  getTriEdges(_0: FaceId, _1: EdgeId, _2: EdgeId, _3: EdgeId): void;
  isLeftQuad(_0: EdgeId): boolean;
  edgePerVertex(): EdgeIdVertIdMap;
  edgeWithOrg(_0: VertId): EdgeId;
  hasVert(_0: VertId): boolean;
  numValidVerts(): number;
  lastValidVert(): VertId;
  addVertId(): VertId;
  vertResize(_0: number): void;
  vertResizeWithReserve(_0: number): void;
  vertReserve(_0: number): void;
  vertSize(): number;
  vertCapacity(): number;
  getValidVerts(): VertBitSet;
  getVertIds(_0: VertBitSet | null): VertBitSet;
  flip(_0: VertBitSet): void;
  flipWithFaceBitSet(_0: FaceBitSet): void;
  edgePerFace(): EdgeIdFaceIdMap;
  edgeWithLeft(_0: FaceId): EdgeId;
  hasFace(_0: FaceId): boolean;
  sharedEdge(_0: FaceId, _1: FaceId): EdgeId;
  sharedVertInOrg(_0: EdgeId, _1: EdgeId): EdgeId;
  sharedVertInOrgWithFaces(_0: FaceId, _1: FaceId): EdgeId;
  sharedFace(_0: EdgeId, _1: EdgeId): FaceId;
  numValidFaces(): number;
  lastValidFace(): FaceId;
  addFaceId(): FaceId;
  deleteFace(_0: FaceId, _1: UndirectedEdgeBitSet | null): void;
  deleteFaces(_0: FaceBitSet, _1: UndirectedEdgeBitSet | null): void;
  faceResize(_0: number): void;
  faceResizeWithReserve(_0: number): void;
  faceReserve(_0: number): void;
  faceSize(): number;
  faceCapacity(): number;
  getValidFaces(): FaceBitSet;
  getFaceIds(_0: FaceBitSet | null): FaceBitSet;
  bdEdgeSameLeft(_0: EdgeId, _1: FaceBitSet | null): EdgeId;
  isLeftBdFace(_0: EdgeId, _1: FaceBitSet | null): boolean;
  bdEdgeWithLeft(_0: FaceId, _1: FaceBitSet | null): EdgeId;
  isBdFace(_0: FaceId, _1: FaceBitSet | null): boolean;
  findBdFaces(_0: FaceBitSet | null): FaceBitSet;
  isLeftInRegion(_0: EdgeId, _1: FaceBitSet | null): boolean;
  isInnerEdge(_0: EdgeId, _1: FaceBitSet | null): boolean;
  isBdEdge(_0: EdgeId, _1: FaceBitSet | null): boolean;
  findLeftBdEdges(_0: FaceBitSet | null, _1: EdgeBitSet | null): EdgeBitSet;
  bdEdgeSameOrigin(_0: EdgeId, _1: FaceBitSet | null): EdgeId;
  isBdVertexInOrg(_0: EdgeId, _1: FaceBitSet | null): boolean;
  bdEdgeWithOrigin(_0: VertId, _1: FaceBitSet | null): EdgeId;
  isBdVertex(_0: VertId, _1: FaceBitSet | null): boolean;
  findBdVerts(_0: FaceBitSet | null, _1: VertBitSet | null): VertBitSet;
  isInnerOrBdVertex(_0: VertId, _1: FaceBitSet | null): boolean;
  isLeftBdEdge(_0: EdgeId, _1: FaceBitSet | null): boolean;
  isInnerOrBdEdge(_0: EdgeId, _1: FaceBitSet | null): boolean;
  nextLeftBd(_0: EdgeId, _1: FaceBitSet | null): EdgeId;
  prevLeftBd(_0: EdgeId, _1: FaceBitSet | null): EdgeId;
  findEdge(_0: VertId, _1: VertId): EdgeId;
  isClosed(_0: FaceBitSet | null): boolean;
  findNumHoles(_0: EdgeBitSet | null): number;
  flipEdge(_0: EdgeId): void;
  splitEdge(_0: EdgeId, _1: FaceBitSet | null, _2: FaceHashMap | null): EdgeId;
  splitFace(_0: FaceId, _1: FaceBitSet | null, _2: FaceHashMap | null): VertId;
  flipOrientation(_0: UndirectedEdgeBitSet | null): void;
  addPart(_0: MeshTopology, _1: FaceMap | null, _2: VertMap | null, _3: WholeEdgeMap | null, _4: boolean): void;
  rotateTriangles(): void;
  pack(_0: FaceMap | null, _1: VertMap | null, _2: WholeEdgeMap | null, _3: boolean): void;
  packWithPackMapping(_0: PackMapping): void;
  packMinMem(_0: PackMapping): void;
  equals(_0: MeshTopology): boolean;
  resizeBeforeParallelAdd(_0: number, _1: number, _2: number): void;
  addPackedPart(_0: MeshTopology, _1: EdgeId, _2: FaceMap, _3: VertMap): void;
  stopUpdatingValids(): void;
  updatingValids(): boolean;
  preferEdges(_0: UndirectedEdgeBitSet): void;
  addPartWithPartMapping(_0: MeshTopology, _1: PartMapping, _2: boolean): void;
  addPartByMaskWithPtr(_0: MeshTopology, _1: FaceBitSet | null, _2: PartMapping): void;
  addPartByMask(_0: MeshTopology, _1: FaceBitSet, _2: PartMapping): void;
  getAllTriVerts(): VectorThreeVertIds;
  findHoleRepresentiveEdges(_0: FaceBitSet | null): VectorEdgeId;
  getLeftRing(_0: EdgeId): VectorEdgeId;
  getPathVertices(_0: VectorEdgeId): VertBitSet;
  getPathLeftFaces(_0: VectorEdgeId): FaceBitSet;
  getPathRightFaces(_0: VectorEdgeId): FaceBitSet;
  getLeftRings(_0: VectorEdgeId): VectorEdgePath;
  addPartByMaskWithEdgePathPtr(_0: MeshTopology, _1: FaceBitSet | null, _2: boolean, _3: VectorEdgePath, _4: VectorEdgePath, _5: PartMapping): void;
  addPartByMaskWithEdgePath(_0: MeshTopology, _1: FaceBitSet, _2: boolean, _3: VectorEdgePath, _4: VectorEdgePath, _5: PartMapping): void;
  getTriVertsWithArray3VertId(_0: FaceId, _1: Array3VertId): void;
  getTriVertsWithThreeVertIds(_0: FaceId, _1: Array3VertId): void;
  getTriVertsWithFaceId(_0: FaceId): Array3VertId;
  getLeftTriVertsWithArray3VertId(_0: EdgeId, _1: Array3VertId): void;
  getLeftTriVertsWithThreeVertIds(_0: EdgeId, _1: Array3VertId): void;
  getLeftTriVertsWithEdgeId(_0: EdgeId): Array3VertId;
  computeValidsFromEdges(_0: ProgressCallback): boolean;
  buildGridMesh(_0: GridSettings, _1: ProgressCallback): boolean;
  checkValidity(_0: ProgressCallback, _1: boolean): boolean;
  collapseEdge(_0: EdgeId, _1: VoidFunctorEdgeIdEdgeId): EdgeId;
}

export type MeshPiece = {
  fmap: FaceMap,
  vmap: VertMap,
  topology: MeshTopology,
  rem: FaceBitSet
};

export type WeightedVertex = {
  v: VertId,
  weight: number
};

export type WeightedVertexArray3 = [ WeightedVertex, WeightedVertex, WeightedVertex ];

export interface MeshTriPoint extends ClassHandle {
  e: EdgeId;
  bary: TriPointf;
  valid(): boolean;
  opbool(): boolean;
  inVertex(): boolean;
  onEdge(_0: MeshTopology): EdgePoint;
  isBd(_0: MeshTopology, _1: FaceBitSet | null): boolean;
  fromTriangle(_0: MeshTopology, _1: FaceId): boolean;
  lnext(_0: MeshTopology): MeshTriPoint;
  canonical(_0: MeshTopology): MeshTriPoint;
  getWeightedVerts(_0: MeshTopology): WeightedVertexArray3;
}

export interface MovementBuildBodyParams extends ClassHandle {
  allowRotation: boolean;
  b2tXf: AffineXf3f | null;
  center: Vector3f | undefined;
  bodyNormal: Vector3f | undefined;
}

export interface NoDefInitFaceId extends ClassHandle {
}

export interface NoDefInitVertId extends ClassHandle {
}

export interface NoDefInitEdgeId extends ClassHandle {
}

export interface NoDefInitUndirectedEdgeId extends ClassHandle {
}

export interface BaseShellParameters extends ClassHandle {
  voxelSize: number;
}

export interface OffsetParameters extends BaseShellParameters {
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

export interface SignDetectionModeValue<T extends number> {
  value: T;
}
export type SignDetectionMode = SignDetectionModeValue<0>|SignDetectionModeValue<1>|SignDetectionModeValue<2>|SignDetectionModeValue<3>|SignDetectionModeValue<4>;

export interface SortIntersectionsData extends ClassHandle {
  rigidB2A: AffineXf3f | null;
  meshAVertsNum: number;
  isOtherA: boolean;
  getOtherMesh(): Mesh;
  getConverter(): ConvertToIntVector;
  getContours(): ContinuousContours;
}

export interface OneMeshContour extends ClassHandle {
  closed: boolean;
  intersections: VectorOneMeshIntersection;
}

export interface OneMeshIntersection extends ClassHandle {
  coordinate: Vector3f;
  primitiveIndex(): number;
  getFaceId(): FaceId;
  getEdgeId(): EdgeId;
  getVertId(): VertId;
  setFaceId(_0: FaceId): void;
  setEdgeId(_0: EdgeId): void;
  setVertId(_0: VertId): void;
}

export type SearchPathSettings = {
  geodesicPathApprox: GeodesicPathApprox,
  maxReduceIters: number
};

export interface PartMapping extends ClassHandle {
  clear(): void;
}

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
  addPartByMask(_0: PointCloud, _1: VertBitSet, _2: CloudPartMapping, _3: VertCoords | null): void;
  mirror(_0: Plane3f): void;
  flipOrientation(_0: VertBitSet | null): void;
  pack(_0: VertMap | null): boolean;
  packReorder(_0: Reorder): VertBMap;
  invalidateCaches(): void;
  heapBytes(): number;
  getLexicographicalOrder(): VectorVertId;
  findCenterFromPoints(): Vector3f;
  findCenterFromBBox(): Vector3f;
  addPoint(_0: Vector3f): VertId;
  addPointNormal(_0: Vector3f, _1: Vector3f): VertId;
}

export interface PointOnFace extends ClassHandle {
  face: FaceId;
  point: Vector3f;
  valid(): boolean;
  opbool(): boolean;
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

export interface Polyline3 extends ClassHandle {
  points: VertCoords;
  topology: PolylineTopology;
  addPart(_0: Polyline3, _1: VertMap | null, _2: WholeEdgeMap | null): void;
  addPartByMask(_0: Polyline3, _1: UndirectedEdgeBitSet, _2: VertMap | null, _3: EdgeMap | null): void;
  pack(_0: VertMap | null, _1: WholeEdgeMap | null): void;
  edgeSegment(_0: EdgeId): LineSegm3f;
  toEdgePoint(_0: VertId): EdgePoint;
  edgeLength(_0: EdgeId): number;
  edgeLengthSq(_0: EdgeId): number;
  totalLength(): number;
  getBoundingBox(): Box3f;
  computeBoundingBox(_0: AffineXf3f | null): Box3f;
  transform(_0: AffineXf3f): void;
  invalidateCaches(): void;
  splitEdge(_0: EdgeId): EdgeId;
  heapBytes(): number;
  addFromEdgePath(_0: Mesh, _1: VectorEdgeId): EdgeId;
  contours(_0: VectorVectorVertId | null): VectorVectorVector3f;
  orgPnt(_0: EdgeId): Vector3f;
  destPnt(_0: EdgeId): Vector3f;
  edgePointFromEdgeId(_0: EdgeId, _1: number): Vector3f;
  edgePoint(_0: EdgePoint): Vector3f;
  edgeCenter(_0: EdgeId): Vector3f;
  edgeVector(_0: EdgeId): Vector3f;
  toEdgePointWithEdgeId(_0: EdgeId, _1: Vector3f): EdgePoint;
  loopDirArea(_0: EdgeId): Vector3f;
  findCenterFromPoints(): Vector3f;
  splitEdgeWithEdgeId(_0: EdgeId, _1: Vector3f): EdgeId;
  addFromPointsAsClosed(_0: Vector3f | null, _1: number, _2: boolean): EdgeId;
  addFromPoints(_0: Vector3f | null, _1: number): EdgeId;
}

export interface Polyline2 extends ClassHandle {
  points: VertCoords2;
  topology: PolylineTopology;
  addPart(_0: Polyline2, _1: VertMap | null, _2: WholeEdgeMap | null): void;
  addPartByMask(_0: Polyline2, _1: UndirectedEdgeBitSet, _2: VertMap | null, _3: EdgeMap | null): void;
  pack(_0: VertMap | null, _1: WholeEdgeMap | null): void;
  edgeSegment(_0: EdgeId): LineSegm2f;
  toEdgePoint(_0: VertId): EdgePoint;
  edgeLength(_0: EdgeId): number;
  edgeLengthSq(_0: EdgeId): number;
  totalLength(): number;
  getBoundingBox(): Box2f;
  computeBoundingBox(_0: AffineXf2f | null): Box2f;
  transform(_0: AffineXf2f): void;
  invalidateCaches(): void;
  splitEdge(_0: EdgeId): EdgeId;
  heapBytes(): number;
  addFromEdgePath(_0: Mesh, _1: VectorEdgeId): EdgeId;
  contours(_0: VectorVectorVertId | null): VectorVectorVector2f;
  orgPnt(_0: EdgeId): Vector2f;
  destPnt(_0: EdgeId): Vector2f;
  edgePointFromEdgeId(_0: EdgeId, _1: number): Vector2f;
  edgePoint(_0: EdgePoint): Vector2f;
  edgeCenter(_0: EdgeId): Vector2f;
  edgeVector(_0: EdgeId): Vector2f;
  toEdgePointWithEdgeId(_0: EdgeId, _1: Vector2f): EdgePoint;
  findCenterFromPoints(): Vector2f;
  splitEdgeWithEdgeId(_0: EdgeId, _1: Vector2f): EdgeId;
  addFromPointsAsClosed(_0: Vector2f | null, _1: number, _2: boolean): EdgeId;
  addFromPoints(_0: Vector2f | null, _1: number): EdgeId;
  loopDirArea(_0: EdgeId): Vector3f;
}

export interface PolylineTopology extends ClassHandle {
  makeEdge(): EdgeId;
  makeEdgeWithVertId(_0: VertId, _1: VertId): EdgeId;
  isLoneEdge(_0: EdgeId): boolean;
  lastNotLoneEdge(): EdgeId;
  edgeSize(): number;
  undirectedEdgeSize(): number;
  computeNotLoneUndirectedEdges(): number;
  edgeReserve(_0: number): void;
  hasEdge(_0: EdgeId): boolean;
  deleteEdge(_0: UndirectedEdgeId): void;
  deleteEdges(_0: UndirectedEdgeBitSet): void;
  heapBytes(): number;
  splice(_0: EdgeId, _1: EdgeId): void;
  next(_0: EdgeId): EdgeId;
  org(_0: EdgeId): VertId;
  dest(_0: EdgeId): VertId;
  setOrg(_0: EdgeId, _1: VertId): void;
  edgePerVertex(): EdgeIdVertIdMap;
  getOrgs(): VertIdEdgeIdMap;
  edgeWithOrg(_0: VertId): EdgeId;
  hasVert(_0: VertId): boolean;
  getVertDegree(_0: VertId): number;
  numValidVerts(): number;
  lastValidVert(): VertId;
  addVertId(): VertId;
  vertResize(_0: number): void;
  vertResizeWithReserve(_0: number): void;
  vertReserve(_0: number): void;
  vertSize(): number;
  vertCapacity(): number;
  getValidVerts(): VertBitSet;
  getVertIds(_0: VertBitSet | null): VertBitSet;
  findEdge(_0: VertId, _1: VertId): EdgeId;
  splitEdge(_0: EdgeId): EdgeId;
  makePolyline(_0: VertId | null, _1: number): EdgeId;
  addPart(_0: PolylineTopology, _1: VertMap | null, _2: WholeEdgeMap | null): void;
  addPartByMask(_0: PolylineTopology, _1: UndirectedEdgeBitSet, _2: VertMap | null, _3: EdgeMap | null): void;
  pack(_0: VertMap | null, _1: WholeEdgeMap | null): void;
  equals(_0: PolylineTopology): boolean;
  notEquals(_0: PolylineTopology): boolean;
  isConsistentlyOriented(): boolean;
  flip(): void;
  checkValidity(): boolean;
  computeValidsFromEdges(): void;
  isClosed(): boolean;
  getPathVertices(_0: VectorEdgeId): VertBitSet;
  buildOpenLines(_0: VectorVertId): void;
}

export interface PolylineMaker extends ClassHandle {
  start(_0: VertId): EdgeId;
  proceed(_0: VertId): EdgeId;
  close(): void;
  finishOpen(_0: VertId): void;
}

export interface SpacingSettings extends ClassHandle {
  region: VertBitSet | null;
  numIters: number;
  stabilizer: number;
  maxSumNegW: number;
  isInverted: FacePredicate;
  dist: UndirectedEdgeMetric;
}

export type InflateSettings = {
  pressure: number,
  iterations: number,
  preSmooth: boolean,
  gradualPressureGrowth: boolean
};

export interface ConvertToFloatVector extends ClassHandle {
}

export interface ConvertToIntVector extends ClassHandle {
}

export interface CoordinateConverters extends ClassHandle {
  setToInt(_0: any): void;
  setToFloat(_0: any): void;
  callToInt(_0: Vector3f): Vector3i;
  callToFloat(_0: Vector3i): Vector3f;
}

export interface RelaxApproxTypeValue<T extends number> {
  value: T;
}
export type RelaxApproxType = RelaxApproxTypeValue<0>|RelaxApproxTypeValue<1>;

export interface RelaxParams extends ClassHandle {
  iterations: number;
  region: VertBitSet | null;
  force: number;
  limitNearInitial: boolean;
  maxInitialDist: number;
}

export interface MeshRelaxParams extends RelaxParams {
  hardSmoothTetrahedrons: boolean;
  weights: VertScalars | null;
}

export interface MeshEqualizeTriAreasParams extends MeshRelaxParams {
  noShrinkage: boolean;
}

export interface MeshApproxRelaxParams extends MeshRelaxParams {
  surfaceDilateRadius: number;
  type: RelaxApproxType;
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

export interface TriMesh extends ClassHandle {
  tris: Triangulation;
  points: VertCoords;
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

export interface VectorMeshPiece extends ClassHandle {
  push_back(_0: MeshPiece): void;
  resize(_0: number, _1: MeshPiece): void;
  size(): number;
  get(_0: number): MeshPiece | undefined;
  set(_0: number, _1: MeshPiece): boolean;
}

export interface SurfacePath extends ClassHandle {
  push_back(_0: EdgePoint): void;
  resize(_0: number, _1: EdgePoint): void;
  size(): number;
  get(_0: number): EdgePoint | undefined;
  set(_0: number, _1: EdgePoint): boolean;
}

export interface VectorAABBTreePointsPoint extends ClassHandle {
  size(): number;
  get(_0: number): AABBTreePointsPoint | undefined;
  push_back(_0: AABBTreePointsPoint): void;
  resize(_0: number, _1: AABBTreePointsPoint): void;
  set(_0: number, _1: AABBTreePointsPoint): boolean;
}

export interface VectorAABBTreePointsNode extends ClassHandle {
  push_back(_0: AABBTreePointsNode): void;
  resize(_0: number, _1: AABBTreePointsNode): void;
  size(): number;
  get(_0: number): AABBTreePointsNode | undefined;
  set(_0: number, _1: AABBTreePointsNode): boolean;
}

export interface VectorModelPointsData extends ClassHandle {
  push_back(_0: ModelPointsData): void;
  resize(_0: number, _1: ModelPointsData): void;
  size(): number;
  get(_0: number): ModelPointsData | undefined;
  set(_0: number, _1: ModelPointsData): boolean;
}

export interface VectorObjVertId extends ClassHandle {
  push_back(_0: ObjVertId): void;
  resize(_0: number, _1: ObjVertId): void;
  size(): number;
  get(_0: number): ObjVertId | undefined;
  set(_0: number, _1: ObjVertId): boolean;
}

export interface VectorMeshProjectionResult extends ClassHandle {
  push_back(_0: MeshProjectionResult): void;
  resize(_0: number, _1: MeshProjectionResult): void;
  size(): number;
  get(_0: number): MeshProjectionResult | undefined;
  set(_0: number, _1: MeshProjectionResult): boolean;
}

export interface VectorVertDuplication extends ClassHandle {
  push_back(_0: VertDuplication): void;
  resize(_0: number, _1: VertDuplication): void;
  size(): number;
  get(_0: number): VertDuplication | undefined;
  set(_0: number, _1: VertDuplication): boolean;
}

export interface VectorEdgeTri extends ClassHandle {
  push_back(_0: EdgeTri): void;
  resize(_0: number, _1: EdgeTri): void;
  size(): number;
  get(_0: number): EdgeTri | undefined;
  set(_0: number, _1: EdgeTri): boolean;
}

export interface ContinuousContour extends ClassHandle {
  push_back(_0: VarEdgeTri): void;
  resize(_0: number, _1: VarEdgeTri): void;
  size(): number;
  get(_0: number): VarEdgeTri | undefined;
  set(_0: number, _1: VarEdgeTri): boolean;
}

export interface ContinuousContours extends ClassHandle {
  push_back(_0: ContinuousContour): void;
  resize(_0: number, _1: ContinuousContour): void;
  size(): number;
  get(_0: number): ContinuousContour | undefined;
  set(_0: number, _1: ContinuousContour): boolean;
}

export interface OneMeshContours extends ClassHandle {
  push_back(_0: OneMeshContour): void;
  resize(_0: number, _1: OneMeshContour): void;
  size(): number;
  get(_0: number): OneMeshContour | undefined;
  set(_0: number, _1: OneMeshContour): boolean;
}

export interface VectorOneMeshIntersection extends ClassHandle {
  push_back(_0: OneMeshIntersection): void;
  resize(_0: number, _1: OneMeshIntersection): void;
  size(): number;
  get(_0: number): OneMeshIntersection | undefined;
  set(_0: number, _1: OneMeshIntersection): boolean;
}

export interface VectorMeshTriPoint extends ClassHandle {
  push_back(_0: MeshTriPoint): void;
  resize(_0: number, _1: MeshTriPoint): void;
  size(): number;
  get(_0: number): MeshTriPoint | undefined;
  set(_0: number, _1: MeshTriPoint): boolean;
}

export interface VectorVectorMeshPiece extends ClassHandle {
  push_back(_0: VectorMeshPiece): void;
  resize(_0: number, _1: VectorMeshPiece): void;
  size(): number;
  get(_0: number): VectorMeshPiece | undefined;
  set(_0: number, _1: VectorMeshPiece): boolean;
}

export interface SurfacePaths extends ClassHandle {
  push_back(_0: SurfacePath): void;
  resize(_0: number, _1: SurfacePath): void;
  size(): number;
  get(_0: number): SurfacePath | undefined;
  set(_0: number, _1: SurfacePath): boolean;
}

export interface VectorVectorAABBTreePointsPoint extends ClassHandle {
  push_back(_0: VectorAABBTreePointsPoint): void;
  resize(_0: number, _1: VectorAABBTreePointsPoint): void;
  size(): number;
  get(_0: number): VectorAABBTreePointsPoint | undefined;
  set(_0: number, _1: VectorAABBTreePointsPoint): boolean;
}

export interface VectorVectorAABBTreePointsNode extends ClassHandle {
  push_back(_0: VectorAABBTreePointsNode): void;
  resize(_0: number, _1: VectorAABBTreePointsNode): void;
  size(): number;
  get(_0: number): VectorAABBTreePointsNode | undefined;
  set(_0: number, _1: VectorAABBTreePointsNode): boolean;
}

export interface VectorVectorModelPointsData extends ClassHandle {
  push_back(_0: VectorModelPointsData): void;
  resize(_0: number, _1: VectorModelPointsData): void;
  size(): number;
  get(_0: number): VectorModelPointsData | undefined;
  set(_0: number, _1: VectorModelPointsData): boolean;
}

export interface VectorVectorObjVertId extends ClassHandle {
  push_back(_0: VectorObjVertId): void;
  resize(_0: number, _1: VectorObjVertId): void;
  size(): number;
  get(_0: number): VectorObjVertId | undefined;
  set(_0: number, _1: VectorObjVertId): boolean;
}

export interface VectorVectorMeshProjectionResult extends ClassHandle {
  push_back(_0: VectorMeshProjectionResult): void;
  resize(_0: number, _1: VectorMeshProjectionResult): void;
  size(): number;
  get(_0: number): VectorMeshProjectionResult | undefined;
  set(_0: number, _1: VectorMeshProjectionResult): boolean;
}

export interface VectorVectorVertDuplication extends ClassHandle {
  push_back(_0: VectorVertDuplication): void;
  resize(_0: number, _1: VectorVertDuplication): void;
  size(): number;
  get(_0: number): VectorVertDuplication | undefined;
  set(_0: number, _1: VectorVertDuplication): boolean;
}

export interface VectorVectorEdgeTri extends ClassHandle {
  push_back(_0: VectorEdgeTri): void;
  resize(_0: number, _1: VectorEdgeTri): void;
  size(): number;
  get(_0: number): VectorEdgeTri | undefined;
  set(_0: number, _1: VectorEdgeTri): boolean;
}

export interface VectorContinuousContours extends ClassHandle {
  push_back(_0: ContinuousContours): void;
  resize(_0: number, _1: ContinuousContours): void;
  size(): number;
  get(_0: number): ContinuousContours | undefined;
  set(_0: number, _1: ContinuousContours): boolean;
}

export interface VectorOneMeshContours extends ClassHandle {
  push_back(_0: OneMeshContours): void;
  resize(_0: number, _1: OneMeshContours): void;
  size(): number;
  get(_0: number): OneMeshContours | undefined;
  set(_0: number, _1: OneMeshContours): boolean;
}

export interface VectorVectorOneMeshIntersection extends ClassHandle {
  push_back(_0: VectorOneMeshIntersection): void;
  resize(_0: number, _1: VectorOneMeshIntersection): void;
  size(): number;
  get(_0: number): VectorOneMeshIntersection | undefined;
  set(_0: number, _1: VectorOneMeshIntersection): boolean;
}

export interface VectorVectorMeshTriPoint extends ClassHandle {
  push_back(_0: VectorMeshTriPoint): void;
  resize(_0: number, _1: VectorMeshTriPoint): void;
  size(): number;
  get(_0: number): VectorMeshTriPoint | undefined;
  set(_0: number, _1: VectorMeshTriPoint): boolean;
}

export interface VectorSurfacePaths extends ClassHandle {
  push_back(_0: SurfacePaths): void;
  resize(_0: number, _1: SurfacePaths): void;
  size(): number;
  get(_0: number): SurfacePaths | undefined;
  set(_0: number, _1: SurfacePaths): boolean;
}

export interface VectorArray2Vector2i extends ClassHandle {
  size(): number;
  get(_0: number): Array2Vector2i | undefined;
  push_back(_0: Array2Vector2i): void;
  resize(_0: number, _1: Array2Vector2i): void;
  set(_0: number, _1: Array2Vector2i): boolean;
}

export interface VectorArray2Vector2f extends ClassHandle {
  size(): number;
  get(_0: number): Array2Vector2f | undefined;
  push_back(_0: Array2Vector2f): void;
  resize(_0: number, _1: Array2Vector2f): void;
  set(_0: number, _1: Array2Vector2f): boolean;
}

export interface VectorArray2Vector2d extends ClassHandle {
  size(): number;
  get(_0: number): Array2Vector2d | undefined;
  push_back(_0: Array2Vector2d): void;
  resize(_0: number, _1: Array2Vector2d): void;
  set(_0: number, _1: Array2Vector2d): boolean;
}

export interface VectorArray3Vector2i extends ClassHandle {
  size(): number;
  get(_0: number): Array3Vector2i | undefined;
  push_back(_0: Array3Vector2i): void;
  resize(_0: number, _1: Array3Vector2i): void;
  set(_0: number, _1: Array3Vector2i): boolean;
}

export interface VectorArray3Vector2f extends ClassHandle {
  size(): number;
  get(_0: number): Array3Vector2f | undefined;
  push_back(_0: Array3Vector2f): void;
  resize(_0: number, _1: Array3Vector2f): void;
  set(_0: number, _1: Array3Vector2f): boolean;
}

export interface VectorArray3Vector2d extends ClassHandle {
  size(): number;
  get(_0: number): Array3Vector2d | undefined;
  push_back(_0: Array3Vector2d): void;
  resize(_0: number, _1: Array3Vector2d): void;
  set(_0: number, _1: Array3Vector2d): boolean;
}

export interface VectorArray2Triangle3i extends ClassHandle {
  size(): number;
  get(_0: number): Array2Triangle3i | undefined;
  push_back(_0: Array2Triangle3i): void;
  resize(_0: number, _1: Array2Triangle3i): void;
  set(_0: number, _1: Array2Triangle3i): boolean;
}

export interface VectorArray2Triangle3f extends ClassHandle {
  size(): number;
  get(_0: number): Array2Triangle3f | undefined;
  push_back(_0: Array2Triangle3f): void;
  resize(_0: number, _1: Array2Triangle3f): void;
  set(_0: number, _1: Array2Triangle3f): boolean;
}

export interface VectorArray2Triangle3d extends ClassHandle {
  size(): number;
  get(_0: number): Array2Triangle3d | undefined;
  push_back(_0: Array2Triangle3d): void;
  resize(_0: number, _1: Array2Triangle3d): void;
  set(_0: number, _1: Array2Triangle3d): boolean;
}

export interface VectorArray3Triangle3i extends ClassHandle {
  size(): number;
  get(_0: number): Array3Triangle3i | undefined;
  push_back(_0: Array3Triangle3i): void;
  resize(_0: number, _1: Array3Triangle3i): void;
  set(_0: number, _1: Array3Triangle3i): boolean;
}

export interface VectorArray3Triangle3f extends ClassHandle {
  fromPointTriples(_0: boolean): Mesh;
  size(): number;
  get(_0: number): Array3Triangle3f | undefined;
  push_back(_0: Array3Triangle3f): void;
  resize(_0: number, _1: Array3Triangle3f): void;
  set(_0: number, _1: Array3Triangle3f): boolean;
}

export interface VectorArray3Triangle3d extends ClassHandle {
  size(): number;
  get(_0: number): Array3Triangle3d | undefined;
  push_back(_0: Array3Triangle3d): void;
  resize(_0: number, _1: Array3Triangle3d): void;
  set(_0: number, _1: Array3Triangle3d): boolean;
}

export interface VectorVectorUndirectedEdgeId extends ClassHandle {
  size(): number;
  get(_0: number): VectorUndirectedEdgeId | undefined;
  push_back(_0: VectorUndirectedEdgeId): void;
  resize(_0: number, _1: VectorUndirectedEdgeId): void;
  set(_0: number, _1: VectorUndirectedEdgeId): boolean;
}

export interface VectorVectorFaceId extends ClassHandle {
  size(): number;
  get(_0: number): VectorFaceId | undefined;
  push_back(_0: VectorFaceId): void;
  resize(_0: number, _1: VectorFaceId): void;
  set(_0: number, _1: VectorFaceId): boolean;
}

export interface VectorVectorVertId extends ClassHandle {
  size(): number;
  get(_0: number): VectorVertId | undefined;
  push_back(_0: VectorVertId): void;
  resize(_0: number, _1: VectorVertId): void;
  set(_0: number, _1: VectorVertId): boolean;
}

export interface VectorVectorPixelId extends ClassHandle {
  size(): number;
  get(_0: number): VectorPixelId | undefined;
  push_back(_0: VectorPixelId): void;
  resize(_0: number, _1: VectorPixelId): void;
  set(_0: number, _1: VectorPixelId): boolean;
}

export interface VectorVectorVoxelId extends ClassHandle {
  size(): number;
  get(_0: number): VectorVoxelId | undefined;
  push_back(_0: VectorVoxelId): void;
  resize(_0: number, _1: VectorVoxelId): void;
  set(_0: number, _1: VectorVoxelId): boolean;
}

export interface VectorVectorRegionId extends ClassHandle {
  size(): number;
  get(_0: number): VectorRegionId | undefined;
  push_back(_0: VectorRegionId): void;
  resize(_0: number, _1: VectorRegionId): void;
  set(_0: number, _1: VectorRegionId): boolean;
}

export interface VectorVectorNodeId extends ClassHandle {
  size(): number;
  get(_0: number): VectorNodeId | undefined;
  push_back(_0: VectorNodeId): void;
  resize(_0: number, _1: VectorNodeId): void;
  set(_0: number, _1: VectorNodeId): boolean;
}

export interface VectorVectorObjId extends ClassHandle {
  size(): number;
  get(_0: number): VectorObjId | undefined;
  push_back(_0: VectorObjId): void;
  resize(_0: number, _1: VectorObjId): void;
  set(_0: number, _1: VectorObjId): boolean;
}

export interface VectorVectorTextureId extends ClassHandle {
  size(): number;
  get(_0: number): VectorTextureId | undefined;
  push_back(_0: VectorTextureId): void;
  resize(_0: number, _1: VectorTextureId): void;
  set(_0: number, _1: VectorTextureId): boolean;
}

export interface VectorVectorGraphVertId extends ClassHandle {
  size(): number;
  get(_0: number): VectorGraphVertId | undefined;
  push_back(_0: VectorGraphVertId): void;
  resize(_0: number, _1: VectorGraphVertId): void;
  set(_0: number, _1: VectorGraphVertId): boolean;
}

export interface VectorVectorGraphEdgeId extends ClassHandle {
  size(): number;
  get(_0: number): VectorGraphEdgeId | undefined;
  push_back(_0: VectorGraphEdgeId): void;
  resize(_0: number, _1: VectorGraphEdgeId): void;
  set(_0: number, _1: VectorGraphEdgeId): boolean;
}

export interface VectorThreeVertIds extends ClassHandle {
  size(): number;
  get(_0: number): Array3VertId | undefined;
  push_back(_0: Array3VertId): void;
  resize(_0: number, _1: Array3VertId): void;
  set(_0: number, _1: Array3VertId): boolean;
}

export interface VectorEdgeId extends ClassHandle {
  push_back(_0: EdgeId): void;
  resize(_0: number, _1: EdgeId): void;
  size(): number;
  get(_0: number): EdgeId | undefined;
  set(_0: number, _1: EdgeId): boolean;
}

export interface VectorUndirectedEdgeId extends ClassHandle {
  push_back(_0: UndirectedEdgeId): void;
  resize(_0: number, _1: UndirectedEdgeId): void;
  size(): number;
  get(_0: number): UndirectedEdgeId | undefined;
  set(_0: number, _1: UndirectedEdgeId): boolean;
}

export interface VectorFaceId extends ClassHandle {
  push_back(_0: FaceId): void;
  resize(_0: number, _1: FaceId): void;
  size(): number;
  get(_0: number): FaceId | undefined;
  set(_0: number, _1: FaceId): boolean;
}

export interface VectorVertId extends ClassHandle {
  push_back(_0: VertId): void;
  resize(_0: number, _1: VertId): void;
  size(): number;
  get(_0: number): VertId | undefined;
  set(_0: number, _1: VertId): boolean;
}

export interface VectorPixelId extends ClassHandle {
  push_back(_0: PixelId): void;
  resize(_0: number, _1: PixelId): void;
  size(): number;
  get(_0: number): PixelId | undefined;
  set(_0: number, _1: PixelId): boolean;
}

export interface VectorVoxelId extends ClassHandle {
  push_back(_0: VoxelId): void;
  resize(_0: number, _1: VoxelId): void;
  size(): number;
  get(_0: number): VoxelId | undefined;
  set(_0: number, _1: VoxelId): boolean;
}

export interface VectorRegionId extends ClassHandle {
  push_back(_0: RegionId): void;
  resize(_0: number, _1: RegionId): void;
  size(): number;
  get(_0: number): RegionId | undefined;
  set(_0: number, _1: RegionId): boolean;
}

export interface VectorNodeId extends ClassHandle {
  push_back(_0: NodeId): void;
  resize(_0: number, _1: NodeId): void;
  size(): number;
  get(_0: number): NodeId | undefined;
  set(_0: number, _1: NodeId): boolean;
}

export interface VectorObjId extends ClassHandle {
  push_back(_0: ObjId): void;
  resize(_0: number, _1: ObjId): void;
  size(): number;
  get(_0: number): ObjId | undefined;
  set(_0: number, _1: ObjId): boolean;
}

export interface VectorTextureId extends ClassHandle {
  push_back(_0: TextureId): void;
  resize(_0: number, _1: TextureId): void;
  size(): number;
  get(_0: number): TextureId | undefined;
  set(_0: number, _1: TextureId): boolean;
}

export interface VectorGraphVertId extends ClassHandle {
  push_back(_0: GraphVertId): void;
  resize(_0: number, _1: GraphVertId): void;
  size(): number;
  get(_0: number): GraphVertId | undefined;
  set(_0: number, _1: GraphVertId): boolean;
}

export interface VectorGraphEdgeId extends ClassHandle {
  push_back(_0: GraphEdgeId): void;
  resize(_0: number, _1: GraphEdgeId): void;
  size(): number;
  get(_0: number): GraphEdgeId | undefined;
  set(_0: number, _1: GraphEdgeId): boolean;
}

export interface VectorEdgePath extends ClassHandle {
  push_back(_0: VectorEdgeId): void;
  resize(_0: number, _1: VectorEdgeId): void;
  size(): number;
  get(_0: number): VectorEdgeId | undefined;
  set(_0: number, _1: VectorEdgeId): boolean;
}

export type CutMeshResult = {
  resultCut: VectorEdgePath,
  fbsWithContourIntersections: FaceBitSet
};

export interface VectorVectorEdgePath extends ClassHandle {
  push_back(_0: VectorEdgePath): void;
  resize(_0: number, _1: VectorEdgePath): void;
  size(): number;
  get(_0: number): VectorEdgePath | undefined;
  set(_0: number, _1: VectorEdgePath): boolean;
}

export interface EdgeHashMapEntries extends ClassHandle {
  push_back(_0: EdgeIdPair): void;
  resize(_0: number, _1: EdgeIdPair): void;
  size(): number;
  get(_0: number): EdgeIdPair | undefined;
  set(_0: number, _1: EdgeIdPair): boolean;
}

export interface UndirectedEdgeHashMapEntries extends ClassHandle {
  push_back(_0: UndirectedEdgeIdPair): void;
  resize(_0: number, _1: UndirectedEdgeIdPair): void;
  size(): number;
  get(_0: number): UndirectedEdgeIdPair | undefined;
  set(_0: number, _1: UndirectedEdgeIdPair): boolean;
}

export interface WholeEdgeHashMapEntries extends ClassHandle {
  push_back(_0: UndirectedE2EIdPair): void;
  resize(_0: number, _1: UndirectedE2EIdPair): void;
  size(): number;
  get(_0: number): UndirectedE2EIdPair | undefined;
  set(_0: number, _1: UndirectedE2EIdPair): boolean;
}

export interface FaceHashMapEntries extends ClassHandle {
  push_back(_0: FaceIdPair): void;
  resize(_0: number, _1: FaceIdPair): void;
  size(): number;
  get(_0: number): FaceIdPair | undefined;
  set(_0: number, _1: FaceIdPair): boolean;
}

export interface VertHashMapEntries extends ClassHandle {
  push_back(_0: VertIdPair): void;
  resize(_0: number, _1: VertIdPair): void;
  size(): number;
  get(_0: number): VertIdPair | undefined;
  set(_0: number, _1: VertIdPair): boolean;
}

export interface VectorVertSpanFaceId extends ClassHandle {
  push_back(_0: VertSpanFaceIdMap): void;
  resize(_0: number, _1: VertSpanFaceIdMap): void;
  size(): number;
  get(_0: number): VertSpanFaceIdMap | undefined;
  set(_0: number, _1: VertSpanFaceIdMap): boolean;
}

export interface VectorVectori extends ClassHandle {
  size(): number;
  get(_0: number): Vectori | undefined;
  push_back(_0: Vectori): void;
  resize(_0: number, _1: Vectori): void;
  set(_0: number, _1: Vectori): boolean;
}

export interface VectorVectord extends ClassHandle {
  size(): number;
  get(_0: number): Vectorf | undefined;
  push_back(_0: Vectorf): void;
  resize(_0: number, _1: Vectorf): void;
  set(_0: number, _1: Vectorf): boolean;
}

export interface VectorVectorf extends ClassHandle {
  size(): number;
  get(_0: number): Vectord | undefined;
  push_back(_0: Vectord): void;
  resize(_0: number, _1: Vectord): void;
  set(_0: number, _1: Vectord): boolean;
}

export interface VectorVector2f extends ClassHandle {
  size(): number;
  get(_0: number): Vector2f | undefined;
  push_back(_0: Vector2f): void;
  resize(_0: number, _1: Vector2f): void;
  set(_0: number, _1: Vector2f): boolean;
}

export interface VectorVectorVector2f extends ClassHandle {
  push_back(_0: VectorVector2f): void;
  resize(_0: number, _1: VectorVector2f): void;
  size(): number;
  get(_0: number): VectorVector2f | undefined;
  set(_0: number, _1: VectorVector2f): boolean;
}

export interface VectorVector2ll extends ClassHandle {
  size(): number;
  get(_0: number): Vector2ll | undefined;
  push_back(_0: Vector2ll): void;
  resize(_0: number, _1: Vector2ll): void;
  set(_0: number, _1: Vector2ll): boolean;
}

export interface VectorVectorVector2ll extends ClassHandle {
  push_back(_0: VectorVector2ll): void;
  resize(_0: number, _1: VectorVector2ll): void;
  size(): number;
  get(_0: number): VectorVector2ll | undefined;
  set(_0: number, _1: VectorVector2ll): boolean;
}

export interface VectorVector2b extends ClassHandle {
  size(): number;
  get(_0: number): Vector2b | undefined;
  push_back(_0: Vector2b): void;
  resize(_0: number, _1: Vector2b): void;
  set(_0: number, _1: Vector2b): boolean;
}

export interface VectorVectorVector2b extends ClassHandle {
  push_back(_0: VectorVector2b): void;
  resize(_0: number, _1: VectorVector2b): void;
  size(): number;
  get(_0: number): VectorVector2b | undefined;
  set(_0: number, _1: VectorVector2b): boolean;
}

export interface VectorVector2i extends ClassHandle {
  size(): number;
  get(_0: number): Vector2i | undefined;
  push_back(_0: Vector2i): void;
  resize(_0: number, _1: Vector2i): void;
  set(_0: number, _1: Vector2i): boolean;
}

export interface VectorVectorVector2i extends ClassHandle {
  push_back(_0: VectorVector2i): void;
  resize(_0: number, _1: VectorVector2i): void;
  size(): number;
  get(_0: number): VectorVector2i | undefined;
  set(_0: number, _1: VectorVector2i): boolean;
}

export interface VectorVector2d extends ClassHandle {
  size(): number;
  get(_0: number): Vector2d | undefined;
  push_back(_0: Vector2d): void;
  resize(_0: number, _1: Vector2d): void;
  set(_0: number, _1: Vector2d): boolean;
}

export interface VectorVectorVector2d extends ClassHandle {
  push_back(_0: VectorVector2d): void;
  resize(_0: number, _1: VectorVector2d): void;
  size(): number;
  get(_0: number): VectorVector2d | undefined;
  set(_0: number, _1: VectorVector2d): boolean;
}

export interface VectorVector3f extends ClassHandle {
  size(): number;
  get(_0: number): Vector3f | undefined;
  push_back(_0: Vector3f): void;
  resize(_0: number, _1: Vector3f): void;
  set(_0: number, _1: Vector3f): boolean;
}

export interface VectorVectorVector3f extends ClassHandle {
  push_back(_0: VectorVector3f): void;
  resize(_0: number, _1: VectorVector3f): void;
  size(): number;
  get(_0: number): VectorVector3f | undefined;
  set(_0: number, _1: VectorVector3f): boolean;
}

export interface VectorVector3b extends ClassHandle {
  size(): number;
  get(_0: number): Vector3b | undefined;
  push_back(_0: Vector3b): void;
  resize(_0: number, _1: Vector3b): void;
  set(_0: number, _1: Vector3b): boolean;
}

export interface VectorVectorVector3b extends ClassHandle {
  push_back(_0: VectorVector3b): void;
  resize(_0: number, _1: VectorVector3b): void;
  size(): number;
  get(_0: number): VectorVector3b | undefined;
  set(_0: number, _1: VectorVector3b): boolean;
}

export interface VectorVector3i extends ClassHandle {
  size(): number;
  get(_0: number): Vector3i | undefined;
  push_back(_0: Vector3i): void;
  resize(_0: number, _1: Vector3i): void;
  set(_0: number, _1: Vector3i): boolean;
}

export interface VectorVectorVector3i extends ClassHandle {
  push_back(_0: VectorVector3i): void;
  resize(_0: number, _1: VectorVector3i): void;
  size(): number;
  get(_0: number): VectorVector3i | undefined;
  set(_0: number, _1: VectorVector3i): boolean;
}

export interface VectorVector3ll extends ClassHandle {
  size(): number;
  get(_0: number): Vector3ll | undefined;
  push_back(_0: Vector3ll): void;
  resize(_0: number, _1: Vector3ll): void;
  set(_0: number, _1: Vector3ll): boolean;
}

export interface VectorVectorVector3ll extends ClassHandle {
  push_back(_0: VectorVector3ll): void;
  resize(_0: number, _1: VectorVector3ll): void;
  size(): number;
  get(_0: number): VectorVector3ll | undefined;
  set(_0: number, _1: VectorVector3ll): boolean;
}

export interface VectorVector3d extends ClassHandle {
  size(): number;
  get(_0: number): Vector3d | undefined;
  push_back(_0: Vector3d): void;
  resize(_0: number, _1: Vector3d): void;
  set(_0: number, _1: Vector3d): boolean;
}

export interface VectorVectorVector3d extends ClassHandle {
  push_back(_0: VectorVector3d): void;
  resize(_0: number, _1: VectorVector3d): void;
  size(): number;
  get(_0: number): VectorVector3d | undefined;
  set(_0: number, _1: VectorVector3d): boolean;
}

export interface VectorVector4f extends ClassHandle {
  size(): number;
  get(_0: number): Vector4f | undefined;
  push_back(_0: Vector4f): void;
  resize(_0: number, _1: Vector4f): void;
  set(_0: number, _1: Vector4f): boolean;
}

export interface VectorVectorVector4f extends ClassHandle {
  push_back(_0: VectorVector4f): void;
  resize(_0: number, _1: VectorVector4f): void;
  size(): number;
  get(_0: number): VectorVector4f | undefined;
  set(_0: number, _1: VectorVector4f): boolean;
}

export interface VectorVector4b extends ClassHandle {
  size(): number;
  get(_0: number): Vector4b | undefined;
  push_back(_0: Vector4b): void;
  resize(_0: number, _1: Vector4b): void;
  set(_0: number, _1: Vector4b): boolean;
}

export interface VectorVectorVector4b extends ClassHandle {
  push_back(_0: VectorVector4b): void;
  resize(_0: number, _1: VectorVector4b): void;
  size(): number;
  get(_0: number): VectorVector4b | undefined;
  set(_0: number, _1: VectorVector4b): boolean;
}

export interface VectorVector4i extends ClassHandle {
  size(): number;
  get(_0: number): Vector4i | undefined;
  push_back(_0: Vector4i): void;
  resize(_0: number, _1: Vector4i): void;
  set(_0: number, _1: Vector4i): boolean;
}

export interface VectorVectorVector4i extends ClassHandle {
  push_back(_0: VectorVector4i): void;
  resize(_0: number, _1: VectorVector4i): void;
  size(): number;
  get(_0: number): VectorVector4i | undefined;
  set(_0: number, _1: VectorVector4i): boolean;
}

export interface VectorVector4ll extends ClassHandle {
  size(): number;
  get(_0: number): Vector4ll | undefined;
  push_back(_0: Vector4ll): void;
  resize(_0: number, _1: Vector4ll): void;
  set(_0: number, _1: Vector4ll): boolean;
}

export interface VectorVectorVector4ll extends ClassHandle {
  push_back(_0: VectorVector4ll): void;
  resize(_0: number, _1: VectorVector4ll): void;
  size(): number;
  get(_0: number): VectorVector4ll | undefined;
  set(_0: number, _1: VectorVector4ll): boolean;
}

export interface VectorVector4d extends ClassHandle {
  size(): number;
  get(_0: number): Vector4d | undefined;
  push_back(_0: Vector4d): void;
  resize(_0: number, _1: Vector4d): void;
  set(_0: number, _1: Vector4d): boolean;
}

export interface VectorVectorVector4d extends ClassHandle {
  push_back(_0: VectorVector4d): void;
  resize(_0: number, _1: VectorVector4d): void;
  size(): number;
  get(_0: number): VectorVector4d | undefined;
  set(_0: number, _1: VectorVector4d): boolean;
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

export type Array2ThreeVertIds = [ Array3VertId, Array3VertId ];

export type Array3ThreeVertIds = [ Array3VertId, Array3VertId, Array3VertId ];

export type Array4ThreeVertIds = [ Array3VertId, Array3VertId, Array3VertId, Array3VertId ];

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

export interface StringFunctorString extends ClassHandle {
  opcall(_0: EmbindString): string;
}

export interface ProgressCallback extends ClassHandle {
  opcall(_0: number): boolean;
}

export interface VoidFunctorEdgeIdEdgeId extends ClassHandle {
  opcall(_0: EdgeId, _1: EdgeId): void;
}

export interface VertPredicate extends ClassHandle {
  opcall(_0: VertId): boolean;
}

export interface FacePredicate extends ClassHandle {
  opcall(_0: FaceId): boolean;
}

export interface EdgePredicate extends ClassHandle {
  opcall(_0: EdgeId): boolean;
}

export interface UndirectedEdgePredicate extends ClassHandle {
  opcall(_0: UndirectedEdgeId): boolean;
}

export interface VertMetric extends ClassHandle {
  opcall(_0: VertId): number;
}

export interface FaceMetric extends ClassHandle {
  opcall(_0: FaceId): number;
}

export interface EdgeMetric extends ClassHandle {
  opcall(_0: EdgeId): number;
}

export interface UndirectedEdgeMetric extends ClassHandle {
  opcall(_0: UndirectedEdgeId): number;
}

export interface FloatFunctorTriangulation extends ClassHandle {
  opcall(_0: Triangulation): number;
}

export interface FloatFunctorDipoles extends ClassHandle {
  opcall(_0: Dipoles): number;
}

export interface FloatFunctorFaceMap extends ClassHandle {
  opcall(_0: FaceMap): number;
}

export interface FloatFunctorVertMap extends ClassHandle {
  opcall(_0: VertMap): number;
}

export interface FloatFunctorEdgeMap extends ClassHandle {
  opcall(_0: EdgeMap): number;
}

export interface FloatFunctorUndirectedEdgeMap extends ClassHandle {
  opcall(_0: UndirectedEdgeMap): number;
}

export interface FloatFunctorObjMap extends ClassHandle {
  opcall(_0: ObjMap): number;
}

export interface FloatFunctorFaceBitSet extends ClassHandle {
  opcall(_0: FaceBitSet): number;
}

export interface FloatFunctorVertBitSet extends ClassHandle {
  opcall(_0: VertBitSet): number;
}

export interface FloatFunctorEdgeBitSet extends ClassHandle {
  opcall(_0: EdgeBitSet): number;
}

export interface FloatFunctorUndirectedEdgeBitSet extends ClassHandle {
  opcall(_0: UndirectedEdgeBitSet): number;
}

export interface FloatFunctorPixelBitSet extends ClassHandle {
  opcall(_0: PixelBitSet): number;
}

export interface FloatFunctorVoxelBitSet extends ClassHandle {
  opcall(_0: VoxelBitSet): number;
}

export interface FloatFunctorRegionBitSet extends ClassHandle {
  opcall(_0: RegionBitSet): number;
}

export interface FloatFunctorNodeBitSet extends ClassHandle {
  opcall(_0: NodeBitSet): number;
}

export interface FloatFunctorObjBitSet extends ClassHandle {
  opcall(_0: ObjBitSet): number;
}

export interface FloatFunctorTextureBitSet extends ClassHandle {
  opcall(_0: TextureBitSet): number;
}

export interface FloatFunctorGraphVertBitSet extends ClassHandle {
  opcall(_0: GraphVertBitSet): number;
}

export interface FloatFunctorGraphEdgeBitSet extends ClassHandle {
  opcall(_0: GraphEdgeBitSet): number;
}

export interface ExpectedSurfacePathFunctorMeshTriPoint extends ClassHandle {
  opcall(_0: MeshTriPoint, _1: MeshTriPoint, _2: number, _3: number): ExpectedSurfacePath;
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

export interface Vectord extends ClassHandle {
}

export interface Vector2b extends ClassHandle {
  x: boolean;
  y: boolean;
  length(): number;
  lengthSq(): boolean;
  get(_0: number): boolean;
  set(_0: number): boolean;
}

export type Array2Vector2b = [ Vector2b, Vector2b ];

export type Array3Vector2b = [ Vector2b, Vector2b, Vector2b ];

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

export type Array2Vector2i = [ Vector2i, Vector2i ];

export type Array3Vector2i = [ Vector2i, Vector2i, Vector2i ];

export interface Vector2ll extends ClassHandle {
}

export type Array2Vector2ll = [ Vector2ll, Vector2ll ];

export type Array3Vector2ll = [ Vector2ll, Vector2ll, Vector2ll ];

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

export type Array2Vector2f = [ Vector2f, Vector2f ];

export type Array3Vector2f = [ Vector2f, Vector2f, Vector2f ];

export interface Vector2d extends ClassHandle {
}

export type Array2Vector2d = [ Vector2d, Vector2d ];

export type Array3Vector2d = [ Vector2d, Vector2d, Vector2d ];

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

export type Array2Triangle3f = [ Vector3f, Vector3f ];

export type Array3Triangle3f = [ Vector3f, Vector3f, Vector3f ];

export type Vector3fPair = [ Vector3f, Vector3f ];

export interface Vector3b extends ClassHandle {
  x: boolean;
  y: boolean;
  z: boolean;
  lengthSq(): boolean;
  length(): number;
  get(_0: number): boolean;
  set(_0: number): boolean;
}

export type Array2Triangle3b = [ Vector3b, Vector3b ];

export type Array3Triangle3b = [ Vector3b, Vector3b, Vector3b ];

export type Vector3bPair = [ Vector3b, Vector3b ];

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

export type Array2Triangle3i = [ Vector3i, Vector3i ];

export type Array3Triangle3i = [ Vector3i, Vector3i, Vector3i ];

export type Vector3iPair = [ Vector3i, Vector3i ];

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

export type Array2Triangle3ll = [ Vector3ll, Vector3ll ];

export type Array3Triangle3ll = [ Vector3ll, Vector3ll, Vector3ll ];

export type Vector3llPair = [ Vector3ll, Vector3ll ];

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

export type Array2Triangle3d = [ Vector3d, Vector3d ];

export type Array3Triangle3d = [ Vector3d, Vector3d, Vector3d ];

export type Vector3DPair = [ Vector3d, Vector3d ];

export interface Vector4b extends ClassHandle {
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

export interface Vector4ll extends ClassHandle {
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

export interface Vector4d extends ClassHandle {
}

export interface VisualObject extends ClassHandle {
}

interface EmbindModule {
  AABBTree: {
    new(): AABBTree;
  };
  AABBTreeObjects: {
    new(): AABBTreeObjects;
  };
  AABBTreePointsNode: {
    new(): AABBTreePointsNode;
  };
  AABBTreePoints: {
    new(_0: Mesh): AABBTreePoints;
    new(_0: VertCoords, _1: VertBitSet | null): AABBTreePoints;
    createFromPointsSharedPtr(_0: VertCoords, _1: VertBitSet): AABBTreePoints | null;
    createFromPointCloudSharedPtr(_0: PointCloud): AABBTreePoints | null;
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
    createFromBool(_0: number, _1: boolean): BitSet;
    beginId(): number;
  };
  FaceBitSet: {
    new(): FaceBitSet;
    new(_0: BitSet): FaceBitSet;
    createFromSize(_0: number): FaceBitSet;
    createFromValue(_0: number, _1: boolean): FaceBitSet;
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
  BooleanOperation: {InsideA: BooleanOperationValue<0>, InsideB: BooleanOperationValue<1>, OutsideA: BooleanOperationValue<2>, OutsideB: BooleanOperationValue<3>, Union: BooleanOperationValue<4>, Intersection: BooleanOperationValue<5>, DifferenceBA: BooleanOperationValue<6>, DifferenceAB: BooleanOperationValue<7>, Count: BooleanOperationValue<8>};
  BooleanResultMapObject: {A: BooleanResultMapObjectValue<0>, B: BooleanResultMapObjectValue<1>, Count: BooleanResultMapObjectValue<2>};
  BooleanResultMaps: {
    new(): BooleanResultMaps;
  };
  BooleanInternalParameters: {
    new(): BooleanInternalParameters;
  };
  BooleanResultMapper: {
    new(): BooleanResultMapper;
  };
  Box1f: {
    new(): Box1f;
    new(_0: number, _1: number): Box1f;
  };
  Box1i: {
    new(): Box1i;
    new(_0: number, _1: number): Box1i;
  };
  Box1ll: {
    new(): Box1ll;
    new(_0: bigint, _1: bigint): Box1ll;
  };
  Box1d: {
    new(): Box1d;
    new(_0: number, _1: number): Box1d;
  };
  Box2f: {
    new(): Box2f;
    new(_0: Vector2f, _1: Vector2f): Box2f;
    fromMinAndSize(_0: Vector2f, _1: Vector2f): Box2f;
    getMinBoxCorner(_0: Vector2f): Vector2b;
    getMaxBoxCorner(_0: Vector2f): Vector2b;
  };
  Box2i: {
    new(): Box2i;
    new(_0: Vector2i, _1: Vector2i): Box2i;
  };
  Box2ll: {
    new(): Box2ll;
    new(_0: Vector2ll, _1: Vector2ll): Box2ll;
  };
  Box2d: {
    new(): Box2d;
    new(_0: Vector2d, _1: Vector2d): Box2d;
  };
  Box3f: {
    new(): Box3f;
    new(_0: Vector3f, _1: Vector3f): Box3f;
    fromMinAndSize(_0: Vector3f, _1: Vector3f): Box3f;
    getMinBoxCorner(_0: Vector3f): Vector3b;
    getMaxBoxCorner(_0: Vector3f): Vector3b;
  };
  Box3i: {
    new(): Box3i;
    new(_0: Vector3i, _1: Vector3i): Box3i;
  };
  Box3ll: {
    new(): Box3ll;
    new(_0: Vector3ll, _1: Vector3ll): Box3ll;
  };
  Box3d: {
    new(): Box3d;
    new(_0: Vector3d, _1: Vector3d): Box3d;
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
  FaceIdEdgeIdSizeTBMapBuffer: {
    new(): FaceIdEdgeIdSizeTBMapBuffer;
    new(_0: number): FaceIdEdgeIdSizeTBMapBuffer;
  };
  VertIdSizeTBMapBuffer: {
    new(): VertIdSizeTBMapBuffer;
    new(_0: number): VertIdSizeTBMapBuffer;
  };
  EdgeIdSizeTBMapBuffer: {
    new(): EdgeIdSizeTBMapBuffer;
    new(_0: number): EdgeIdSizeTBMapBuffer;
  };
  UndirectedEdgeIdSizeTBMapBuffer: {
    new(): UndirectedEdgeIdSizeTBMapBuffer;
    new(_0: number): UndirectedEdgeIdSizeTBMapBuffer;
  };
  PackMapping: {
    new(): PackMapping;
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
  NewEdgesMap: {
    new(): NewEdgesMap;
  };
  ForceFill: {None: ForceFillValue<0>, Good: ForceFillValue<1>, All: ForceFillValue<2>};
  CutMeshParameters: {
    new(): CutMeshParameters;
  };
  Dipole: {
    new(): Dipole;
  };
  EdgeLengthMesh: {
    new(): EdgeLengthMesh;
    fromMesh(_0: Mesh): EdgeLengthMesh;
  };
  EdgeMetricWrapper: {
    new(_0: EdgeMetricWrapper): EdgeMetricWrapper;
    createEdgeMetricWrapper(_0: EdgeMetricWrapper): EdgeMetricWrapper;
  };
  identityMetric(): EdgeMetricWrapper;
  EdgePoint: {
    new(): EdgePoint;
    new(_0: EdgeId, _1: number): EdgePoint;
    createFromMeshTopology(_0: MeshTopology, _1: VertId): EdgePoint;
    createFromPolylineTopology(_0: PolylineTopology, _1: VertId): EdgePoint;
  };
  EdgePointPair: {
    new(): EdgePointPair;
    new(_0: EdgePoint, _1: EdgePoint): EdgePointPair;
  };
  EdgeSegment: {
    new(): EdgeSegment;
    new(_0: EdgeId, _1: number, _2: number): EdgeSegment;
  };
  VertexMass: {Unit: VertexMassValue<0>, NeiArea: VertexMassValue<1>};
  EdgeWeights: {Unit: EdgeWeightsValue<0>, Cotan: EdgeWeightsValue<1>};
  Processing: {Continue: ProcessingValue<0>, Stop: ProcessingValue<1>};
  OrientNormals: {TowardOrigin: OrientNormalsValue<0>, AwayFromOrigin: OrientNormalsValue<1>, Smart: OrientNormalsValue<2>};
  OffsetMode: {Smooth: OffsetModeValue<0>, Standard: OffsetModeValue<1>, Sharpening: OffsetModeValue<2>};
  ColoringType: {SolidColor: ColoringTypeValue<0>, PrimitivesColorMap: ColoringTypeValue<1>, FacesColorMap: ColoringTypeValue<1>, LinesColorMap: ColoringTypeValue<1>, VertsColorMap: ColoringTypeValue<2>};
  asString(_0: ColoringType): string;
  UseAABBTree: {No: UseAABBTreeValue<0>, Yes: UseAABBTreeValue<1>, YesIfAlreadyConstructed: UseAABBTreeValue<2>};
  GeodesicPathApprox: {DijkstraBiDir: GeodesicPathApproxValue<0>, DijkstraAStar: GeodesicPathApproxValue<1>, FastMarching: GeodesicPathApproxValue<2>};
  ExpectedVoid: {};
  ExpectedMeshTopology: {};
  ExpectedMesh: {};
  ExpectedEdgeLengthMesh: {};
  ExpectedMeshOrPoints: {};
  ExpectedPointCloud: {};
  ExpectedAABBTree: {};
  ExpectedAABBTreePoints: {};
  ExpectedAABBTreeObjects: {};
  ExpectedCloudPartMapping: {};
  ExpectedPartMapping: {};
  ExpectedMeshOrPointsXf: {};
  ExpectedMeshTexture: {};
  ExpectedGridSettings: {};
  ExpectedTriMesh: {};
  ExpectedPackMapping: {};
  ExpectedEdgePath: {};
  ExpectedEdgeLoops: {};
  ExpectedOneMeshContour: {};
  ExpectedSurfacePath: {};
  MeshSegmentation: {
    new(_0: Mesh): MeshSegmentation;
  };
  FillHoleNicelySettings: {
    new(): FillHoleNicelySettings;
  };
  FixParams: {
    new(): FixParams;
  };
  FreeFormDeformer: {
    new(_0: VertCoords, _1: VertBitSet): FreeFormDeformer;
    createFreeFormDeformerFromMesh(_0: Mesh, _1: VertBitSet | null): FreeFormDeformer | null;
    createFreeFormDeformerFromCoords(_0: VertCoords, _1: VertBitSet): FreeFormDeformer | null;
  };
  FreeFormBestFit: {
    new(_0: Box3d, _1: Vector3i): FreeFormBestFit;
  };
  ModelPointsData: {
    new(): ModelPointsData;
  };
  ObjVertId: {
    new(): ObjVertId;
  };
  EdgeType: {Horizontal: EdgeTypeValue<0>, Vertical: EdgeTypeValue<1>, DiagonalA: EdgeTypeValue<2>, DiagonalB: EdgeTypeValue<3>};
  TriType: {Lower: TriTypeValue<0>, Upper: TriTypeValue<1>};
  GridSettings: {
    new(): GridSettings;
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
  lerp(_0: number, _1: number, _2: number): number;
  MyClass: {
    new(_0: number, _1: EmbindString): MyClass;
    getStringFromInstance(_0: MyClass): string;
  };
  RememberShape: {Yes: RememberShapeValue<0>, No: RememberShapeValue<1>};
  Laplacian: {
    new(_0: Mesh): Laplacian;
    new(_0: MeshTopology, _1: VertCoords): Laplacian;
  };
  Line2f: {
    new(): Line2f;
    new(_0: Vector2f, _1: Vector2f): Line2f;
  };
  Line2d: {
    new(): Line2d;
    new(_0: Vector2d, _1: Vector2d): Line2d;
  };
  Line3f: {
    new(): Line3f;
    new(_0: Vector3f, _1: Vector3f): Line3f;
  };
  Line3d: {
    new(): Line3d;
    new(_0: Vector3d, _1: Vector3d): Line3d;
  };
  LineSegm2f: {
    new(): LineSegm2f;
    new(_0: Vector2f, _1: Vector2f): LineSegm2f;
  };
  LineSegm2d: {
    new(): LineSegm2d;
    new(_0: Vector2d, _1: Vector2d): LineSegm2d;
  };
  LineSegm3f: {
    new(): LineSegm3f;
    new(_0: Vector3f, _1: Vector3f): LineSegm3f;
  };
  LineSegm3d: {
    new(): LineSegm3d;
    new(_0: Vector3d, _1: Vector3d): LineSegm3d;
  };
  doSegmentsIntersect2f(_0: LineSegm2f, _1: LineSegm2f, _2: number, _3: number): boolean;
  doSegmentsIntersect2d(_0: LineSegm2d, _1: LineSegm2d, _2: number, _3: number): boolean;
  doSegmentLineIntersect2f(_0: LineSegm2f, _1: Line2f, _2: number, _3: number): boolean;
  doSegmentLineIntersect2d(_0: LineSegm2d, _1: Line2d, _2: number, _3: number): boolean;
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
  isRigidf(_0: Matrix3f): boolean;
  isRigidd(_0: Matrix3d): boolean;
  decomposeMatrix3f(_0: Matrix3f, _1: Matrix3f, _2: Matrix3f): void;
  decomposeMatrix3d(_0: Matrix3d, _1: Matrix3d, _2: Matrix3d): void;
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
  findTwinEdges(_0: Mesh, _1: number): EdgeBitSet;
  findTwinUndirectedEdges(_0: Mesh, _1: number): UndirectedEdgeBitSet;
  edgeLengthMetric(_0: Mesh): EdgeMetricWrapper;
  discreteAbsMeanCurvatureMetric(_0: Mesh): EdgeMetricWrapper;
  discreteMinusAbsMeanCurvatureMetric(_0: Mesh): EdgeMetricWrapper;
  edgeCurvMetric(_0: Mesh, _1: number, _2: number): EdgeMetricWrapper;
  smoothExtractedRegionBoundary(_0: Mesh, _1: number): any;
  calculateRecommendedVoxelSize(_0: Mesh, _1: number): number;
  computeVertexNormals(_0: Mesh): any;
  MeshWrapper: {
    new(): MeshWrapper;
    new(_0: Mesh): MeshWrapper;
    fromTrianglesImpl(_0: any, _1: any): any;
  };
  BooleanResult: {
    new(): BooleanResult;
  };
  performBoolean(_0: Mesh, _1: Mesh, _2: BooleanOperation): BooleanResult;
  UniteCloseParams: {
    new(): UniteCloseParams;
  };
  uniteCloseVertices(_0: Mesh, _1: UniteCloseParams): number;
  Triangle: {
    new(): Triangle;
    new(_0: VertId, _1: VertId, _2: VertId, _3: FaceId): Triangle;
  };
  BuildSettings: {
    new(): BuildSettings;
  };
  EdgeTri: {
    new(): EdgeTri;
    new(_0: EdgeId, _1: FaceId): EdgeTri;
  };
  FlaggedTri: {
    new(): FlaggedTri;
  };
  VarEdgeTri: {
    new(): VarEdgeTri;
    new(_0: boolean, _1: EdgeTri): VarEdgeTri;
    new(_0: boolean, _1: EdgeId, _2: FaceId): VarEdgeTri;
  };
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
  findTwinUndirectedEdgeHashMap(_0: Mesh, _1: number): UndirectedEdgeHashMap;
  WholeEdgeHashMap: {
    new(): WholeEdgeHashMap;
  };
  UndirectedEdgeIdIntHashMap: {
    new(): UndirectedEdgeIdIntHashMap;
  };
  MakeDegenerateBandAroundRegionParamsWrapper: {
    new(): MakeDegenerateBandAroundRegionParamsWrapper;
  };
  MakeDegenerateBandAroundRegionParams: {
    new(): MakeDegenerateBandAroundRegionParams;
  };
  makeDegenerateBandAroundRegion(_0: Mesh, _1: FaceBitSet, _2: MakeDegenerateBandAroundRegionParams): void;
  StitchHolesParams: {
    new(): StitchHolesParams;
  };
  FillHoleParams: {
    new(): FillHoleParams;
  };
  buildCylinderBetweenTwoHoles(_0: Mesh, _1: StitchHolesParams): boolean;
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
  fillHoleNicely(_0: Mesh, _1: EdgeId, _2: FillHoleNicelySettings): FaceBitSet;
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
  buildCylinderBetweenTwoHolesWithEdges(_0: Mesh, _1: EdgeId, _2: EdgeId, _3: StitchHolesParams): void;
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
  VertIdSizeTBMap: {
    new(): VertIdSizeTBMap;
  };
  UndirectedEdgeIdSizeTBMap: {
    new(): UndirectedEdgeIdSizeTBMap;
  };
  FaceIdSizeTBMap: {
    new(): FaceIdSizeTBMap;
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
  findCloseVerticesFromMap(_0: VertMap): VertBitSet;
  uniteCloseVerticesWithVertMap(_0: Mesh, _1: number, _2: boolean, _3: VertMap | null): number;
  EdgeMap: {
    new(): EdgeMap;
    new(_0: number): EdgeMap;
    new(_0: number, _1: EdgeId): EdgeMap;
  };
  VertIdEdgeIdMap: {
    new(): VertIdEdgeIdMap;
    new(_0: number): VertIdEdgeIdMap;
    new(_0: number, _1: VertId): VertIdEdgeIdMap;
  };
  EdgeIdVertIdMap: {
    new(): EdgeIdVertIdMap;
    new(_0: number): EdgeIdVertIdMap;
    new(_0: number, _1: EdgeId): EdgeIdVertIdMap;
  };
  EdgeIdFaceIdMap: {
    new(): EdgeIdFaceIdMap;
    new(_0: number): EdgeIdFaceIdMap;
    new(_0: number, _1: EdgeId): EdgeIdFaceIdMap;
  };
  FaceIdEdgeIdMap: {
    new(): FaceIdEdgeIdMap;
    new(_0: number): FaceIdEdgeIdMap;
    new(_0: number, _1: FaceId): FaceIdEdgeIdMap;
  };
  ModelPointsDataObjIdMap: {
    new(): ModelPointsDataObjIdMap;
    new(_0: number): ModelPointsDataObjIdMap;
    new(_0: number, _1: ModelPointsData): ModelPointsDataObjIdMap;
  };
  VertSpanFaceIdMap: {
    new(): VertSpanFaceIdMap;
    new(_0: number): VertSpanFaceIdMap;
    new(_0: number, _1: VertSpan): VertSpanFaceIdMap;
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
  FilterType: {Linear: FilterTypeValue<0>, Discrete: FilterTypeValue<1>};
  WrapType: {Repeat: WrapTypeValue<0>, Mirror: WrapTypeValue<1>, Clamp: WrapTypeValue<2>};
  Reorder: {None: ReorderValue<0>, Lexicographically: ReorderValue<1>, AABBTree: ReorderValue<2>};
  MeshLoadWrapper: {
    fromFile(_0: EmbindString): any;
    fromBinaryData(_0: number, _1: number, _2: EmbindString): any;
  };
  FillHoleMetric: {
    new(): FillHoleMetric;
  };
  FillTriangleMetric: {
    new(): FillTriangleMetric;
  };
  FillEdgeMetric: {
    new(): FillEdgeMetric;
  };
  FillCombineMetric: {
    new(): FillCombineMetric;
  };
  FillHoleMetricWrapper: {
    new(_0: FillHoleMetricWrapper): FillHoleMetricWrapper;
    createFillHoleMetricWrapperFromOther(_0: FillHoleMetricWrapper): FillHoleMetricWrapper;
  };
  createCircumscribedMetric(_0: Mesh): FillHoleMetricWrapper;
  createPlaneFillMetric(_0: Mesh, _1: EdgeId): FillHoleMetricWrapper;
  createPlaneNormalizedFillMetric(_0: Mesh, _1: EdgeId): FillHoleMetricWrapper;
  createComplexStitchMetric(_0: Mesh): FillHoleMetricWrapper;
  createEdgeLengthFillMetric(_0: Mesh): FillHoleMetricWrapper;
  createEdgeLengthStitchMetric(_0: Mesh): FillHoleMetricWrapper;
  createComplexFillMetricWithEdgeId(_0: Mesh, _1: EdgeId): FillHoleMetricWrapper;
  createComplexFillMetric(_0: Mesh): FillHoleMetricWrapper;
  createUniversalMetric(_0: Mesh): FillHoleMetricWrapper;
  createMinTriAngleMetric(_0: Mesh): FillHoleMetricWrapper;
  createMinAreaMetric(_0: Mesh): FillHoleMetricWrapper;
  MeshOrPoints: {
    new(_0: Mesh): MeshOrPoints;
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
  removeSpikes(_0: Mesh, _1: number, _2: number, _3: VertBitSet | null): void;
  smoothRegionBoundary(_0: Mesh, _1: FaceBitSet, _2: number): void;
  hardSmoothTetrahedrons(_0: Mesh, _1: VertBitSet | null): void;
  SubdivideSettings: {
    new(): SubdivideSettings;
  };
  MeshTexture: {
    new(): MeshTexture;
  };
  MeshTopology: {
    new(): MeshTopology;
  };
  edgeLengthMetricFromTopology(_0: MeshTopology, _1: VertCoords): EdgeMetricWrapper;
  discreteAbsMeanCurvatureMetricFromTopology(_0: MeshTopology, _1: VertCoords): EdgeMetricWrapper;
  discreteMinusAbsMeanCurvatureMetricFromTopology(_0: MeshTopology, _1: VertCoords): EdgeMetricWrapper;
  edgeCurvMetricFromTopology(_0: MeshTopology, _1: VertCoords, _2: number, _3: number): EdgeMetricWrapper;
  edgeTableSymMetric(_0: MeshTopology, _1: EdgeMetricWrapper): EdgeMetricWrapper;
  fromSameTriangle(_0: MeshTopology, _1: EdgePoint, _2: EdgePoint): boolean;
  addTriangles(_0: MeshTopology, _1: Triangulation, _2: BuildSettings): void;
  removeSpikesWithTopology(_0: MeshTopology, _1: VertCoords, _2: number, _3: number, _4: VertBitSet | null): void;
  hardSmoothTetrahedrons_topology(_0: MeshTopology, _1: VertCoords, _2: VertBitSet | null): void;
  loadMeshDll(): void;
  MeshTriPoint: {
    new(): MeshTriPoint;
    new(_0: EdgeId, _1: TriPointf): MeshTriPoint;
  };
  MovementBuildBodyParams: {
    new(): MovementBuildBodyParams;
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
  BaseShellParameters: {
    new(): BaseShellParameters;
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
  SignDetectionMode: {Unsigned: SignDetectionModeValue<0>, OpenVDB: SignDetectionModeValue<1>, ProjectionNormal: SignDetectionModeValue<2>, WindingRule: SignDetectionModeValue<3>, HoleWindingRule: SignDetectionModeValue<4>};
  thickenMesh(_0: Mesh, _1: number, _2: GeneralOffsetParameters): any;
  suggestVoxelSize(_0: MeshPart, _1: number): number;
  offsetMesh(_0: MeshPart, _1: number, _2: OffsetParameters): ExpectedMesh;
  SortIntersectionsData: {};
  OneMeshContour: {
    new(): OneMeshContour;
  };
  OneMeshIntersection: {
    new(): OneMeshIntersection;
  };
  PartMapping: {
    new(): PartMapping;
  };
  Plane3f: {
    new(): Plane3f;
    new(_0: Plane3d): Plane3f;
    new(_0: Vector3f, _1: number): Plane3f;
    fromDirAndPt(_0: Vector3f, _1: Vector3f): Plane3f;
  };
  extendHole(_0: Mesh, _1: EdgeId, _2: Plane3f): EdgeId;
  extendHoleWithOutput(_0: Mesh, _1: EdgeId, _2: Plane3f): any;
  extendAllHolesWithOutput(_0: Mesh, _1: Plane3f): any;
  createComplexFillMetricWithPlane3f(_0: Mesh, _1: EdgeId, _2: Plane3f | null): FillHoleMetricWrapper;
  Plane3d: {
    new(): Plane3d;
    new(_0: Plane3f): Plane3d;
    new(_0: Vector3d, _1: number): Plane3d;
    fromDirAndPt(_0: Vector3d, _1: Vector3d): Plane3d;
  };
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
  Polyline3: {
    new(): Polyline3;
    new(_0: VectorVector3f): Polyline3;
    fromContours(_0: VectorVectorVector3f): Polyline3;
  };
  Polyline2: {
    new(): Polyline2;
    new(_0: VectorVector2f): Polyline2;
    fromContours(_0: VectorVectorVector2f): Polyline2;
  };
  PolylineTopology: {
    new(): PolylineTopology;
  };
  PolylineMaker: {
    new(_0: PolylineTopology): PolylineMaker;
  };
  SpacingSettings: {};
  positionVertsSmoothly(_0: Mesh, _1: VertBitSet, _2: EdgeWeights, _3: VertexMass, _4: VertBitSet | null): void;
  positionVertsSmoothlyWithTopology(_0: MeshTopology, _1: VertCoords, _2: VertBitSet, _3: EdgeWeights, _4: VertexMass, _5: VertBitSet | null): void;
  positionVertsSmoothlySharpBd(_0: Mesh, _1: VertBitSet, _2: VertCoords | null, _3: VertScalars | null): void;
  positionVertsSmoothlySharpBdWithTopology(_0: MeshTopology, _1: VertCoords, _2: VertBitSet, _3: VertCoords | null, _4: VertScalars | null): void;
  positionVertsWithSpacing(_0: Mesh, _1: SpacingSettings): void;
  positionVertsWithSpacingWithTopology(_0: MeshTopology, _1: VertCoords, _2: SpacingSettings): void;
  inflate(_0: Mesh, _1: VertBitSet, _2: InflateSettings): void;
  inflateWithTopology(_0: MeshTopology, _1: VertCoords, _2: VertBitSet, _3: InflateSettings): void;
  inflate1WithTopology(_0: MeshTopology, _1: VertCoords, _2: VertBitSet, _3: number): void;
  ConvertToFloatVector: {};
  ConvertToIntVector: {};
  createConvertToIntVector(_0: any): ConvertToIntVector;
  createConvertToFloatVector(_0: any): ConvertToFloatVector;
  CoordinateConverters: {
    new(): CoordinateConverters;
  };
  getVectorConverters_Part(_0: MeshPart): CoordinateConverters;
  getVectorConverters_Parts(_0: MeshPart, _1: MeshPart, _2: AffineXf3f | null): CoordinateConverters;
  findRegionBoundaryUndirectedEdgesInsideMesh(_0: MeshTopology, _1: FaceBitSet): UndirectedEdgeBitSet;
  findRegionOuterFaces(_0: MeshTopology, _1: FaceBitSet): FaceBitSet;
  getIncidentVerts(_0: MeshTopology, _1: FaceBitSet): VertBitSet;
  getIncidentVertsWithVertBitSet(_0: MeshTopology, _1: FaceBitSet | null, _2: VertBitSet): VertBitSet;
  getIncidentVertsWithUndirectedEdgeBitSet(_0: MeshTopology, _1: UndirectedEdgeBitSet): VertBitSet;
  getIncidentVertsWithUndirectedEdgeBitSetAndVertBitSet(_0: MeshTopology, _1: UndirectedEdgeBitSet | null, _2: VertBitSet): VertBitSet;
  getInnerVerts(_0: MeshTopology, _1: FaceBitSet): VertBitSet;
  getInnerVertsWithFaceBitSetPtr(_0: MeshTopology, _1: FaceBitSet | null): VertBitSet;
  getInnerVertsWithUndirectedEdgeBitSet(_0: MeshTopology, _1: UndirectedEdgeBitSet): VertBitSet;
  getBoundaryVerts(_0: MeshTopology, _1: FaceBitSet | null): VertBitSet;
  getRegionBoundaryVerts(_0: MeshTopology, _1: FaceBitSet): VertBitSet;
  getIncidentFaces(_0: MeshTopology, _1: VertBitSet): FaceBitSet;
  getIncidentFacesFromUndirectedEdgeBitSet(_0: MeshTopology, _1: UndirectedEdgeBitSet): FaceBitSet;
  getInnerFaces(_0: MeshTopology, _1: VertBitSet): FaceBitSet;
  getRegionEdges(_0: MeshTopology, _1: FaceBitSet): EdgeBitSet;
  getIncidentEdges(_0: MeshTopology, _1: FaceBitSet): UndirectedEdgeBitSet;
  getIncidentEdgesFromUndirectedEdgeBitSet(_0: MeshTopology, _1: UndirectedEdgeBitSet): UndirectedEdgeBitSet;
  getNeighborFaces(_0: MeshTopology, _1: UndirectedEdgeBitSet): FaceBitSet;
  getInnerEdges(_0: MeshTopology, _1: VertBitSet): UndirectedEdgeBitSet;
  getInnerEdgesFromFaceBitSet(_0: MeshTopology, _1: FaceBitSet): UndirectedEdgeBitSet;
  RelaxApproxType: {Planar: RelaxApproxTypeValue<0>, Quadric: RelaxApproxTypeValue<1>};
  RelaxParams: {
    new(): RelaxParams;
  };
  MeshRelaxParams: {
    new(): MeshRelaxParams;
  };
  MeshEqualizeTriAreasParams: {
    new(): MeshEqualizeTriAreasParams;
  };
  MeshApproxRelaxParams: {
    new(): MeshApproxRelaxParams;
  };
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
  TriMesh: {
    new(): TriMesh;
    copy(_0: TriMesh): TriMesh;
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
  cutMeshWithPolylineImpl(_0: Mesh, _1: StdVectorf): any;
  cutMeshWithPolylineImplTest(_0: Mesh, _1: StdVectorf): any;
  StdVectord: {
    new(): StdVectord;
  };
  StdVectorll: {
    new(): StdVectorll;
  };
  StdVectorUi64: {
    new(): StdVectorUi64;
  };
  VectorMeshPiece: {
    new(): VectorMeshPiece;
  };
  fromDisjointMeshPieces(_0: Triangulation, _1: VertId, _2: VectorMeshPiece, _3: BuildSettings): MeshTopology;
  SurfacePath: {
    new(): SurfacePath;
  };
  convertSurfacePathWithEndsToMeshContour(_0: Mesh, _1: MeshTriPoint, _2: SurfacePath, _3: MeshTriPoint): OneMeshContour;
  VectorAABBTreePointsPoint: {
    new(): VectorAABBTreePointsPoint;
  };
  VectorAABBTreePointsNode: {
    new(): VectorAABBTreePointsNode;
  };
  VectorModelPointsData: {
    new(): VectorModelPointsData;
  };
  VectorObjVertId: {
    new(): VectorObjVertId;
  };
  VectorMeshProjectionResult: {
    new(): VectorMeshProjectionResult;
  };
  VectorVertDuplication: {
    new(): VectorVertDuplication;
  };
  duplicateNonManifoldVertices(_0: Triangulation, _1: FaceBitSet | null, _2: VectorVertDuplication | null, _3: VertId): number;
  fromTrianglesDuplicatingNonManifoldVertices(_0: Triangulation, _1: VectorVertDuplication | null, _2: BuildSettings): MeshTopology;
  VectorEdgeTri: {
    new(): VectorEdgeTri;
  };
  findSelfCollidingEdgeTrisPrecise(_0: MeshPart, _1: ConvertToIntVector, _2: boolean, _3: AffineXf3f | null, _4: number): VectorEdgeTri;
  ContinuousContour: {
    new(): ContinuousContour;
  };
  isClosed(_0: ContinuousContour): boolean;
  findCollidingEdgeTrisPrecise_PartPart(_0: MeshPart, _1: MeshPart, _2: ConvertToIntVector, _3: AffineXf3f | null, _4: boolean): ContinuousContour;
  ContinuousContours: {
    new(): ContinuousContours;
  };
  orderIntersectionContours(_0: MeshTopology, _1: MeshTopology, _2: ContinuousContour): ContinuousContours;
  orderSelfIntersectionContours(_0: MeshTopology, _1: VectorEdgeTri): ContinuousContours;
  detectLoneContours(_0: ContinuousContours, _1: boolean): StdVectori;
  removeLoneContours(_0: ContinuousContours, _1: boolean): void;
  createSortIntersectionsDataImpl(_0: Mesh, _1: ContinuousContours, _2: CoordinateConverters, _3: AffineXf3f | null, _4: number, _5: boolean): SortIntersectionsData;
  OneMeshContours: {
    new(): OneMeshContours;
  };
  removeLoneDegeneratedContours(_0: MeshTopology, _1: OneMeshContours, _2: OneMeshContours): void;
  subdivideLoneContours(_0: Mesh, _1: OneMeshContours, _2: FaceHashMap | null): void;
  getOneMeshSelfIntersectionContours(_0: Mesh, _1: ContinuousContours, _2: CoordinateConverters, _3: AffineXf3f | null): OneMeshContours;
  VectorOneMeshIntersection: {
    new(): VectorOneMeshIntersection;
  };
  VectorMeshTriPoint: {
    new(): VectorMeshTriPoint;
  };
  convertMeshTriPointsToMeshContour(_0: Mesh, _1: VectorMeshTriPoint, _2: SearchPathSettings, _3: StdVectori | null): ExpectedOneMeshContour;
  convertMeshTriPointsToClosedContour(_0: Mesh, _1: VectorMeshTriPoint, _2: SearchPathSettings, _3: StdVectori | null): ExpectedOneMeshContour;
  VectorVectorMeshPiece: {
    new(): VectorVectorMeshPiece;
  };
  SurfacePaths: {
    new(): SurfacePaths;
  };
  convertSurfacePathsToMeshContours(_0: Mesh, _1: SurfacePaths): OneMeshContours;
  VectorVectorAABBTreePointsPoint: {
    new(): VectorVectorAABBTreePointsPoint;
  };
  VectorVectorAABBTreePointsNode: {
    new(): VectorVectorAABBTreePointsNode;
  };
  VectorVectorModelPointsData: {
    new(): VectorVectorModelPointsData;
  };
  VectorVectorObjVertId: {
    new(): VectorVectorObjVertId;
  };
  VectorVectorMeshProjectionResult: {
    new(): VectorVectorMeshProjectionResult;
  };
  VectorVectorVertDuplication: {
    new(): VectorVectorVertDuplication;
  };
  VectorVectorEdgeTri: {
    new(): VectorVectorEdgeTri;
  };
  VectorContinuousContours: {
    new(): VectorContinuousContours;
  };
  VectorOneMeshContours: {
    new(): VectorOneMeshContours;
  };
  VectorVectorOneMeshIntersection: {
    new(): VectorVectorOneMeshIntersection;
  };
  VectorVectorMeshTriPoint: {
    new(): VectorVectorMeshTriPoint;
  };
  VectorSurfacePaths: {
    new(): VectorSurfacePaths;
  };
  VectorArray2Vector2i: {
    new(): VectorArray2Vector2i;
  };
  VectorArray2Vector2f: {
    new(): VectorArray2Vector2f;
  };
  VectorArray2Vector2d: {
    new(): VectorArray2Vector2d;
  };
  VectorArray3Vector2i: {
    new(): VectorArray3Vector2i;
  };
  VectorArray3Vector2f: {
    new(): VectorArray3Vector2f;
  };
  VectorArray3Vector2d: {
    new(): VectorArray3Vector2d;
  };
  VectorArray2Triangle3i: {
    new(): VectorArray2Triangle3i;
  };
  VectorArray2Triangle3f: {
    new(): VectorArray2Triangle3f;
  };
  VectorArray2Triangle3d: {
    new(): VectorArray2Triangle3d;
  };
  VectorArray3Triangle3i: {
    new(): VectorArray3Triangle3i;
  };
  VectorArray3Triangle3f: {
    new(): VectorArray3Triangle3f;
  };
  fromPointTriples(_0: VectorArray3Triangle3f): Mesh;
  VectorArray3Triangle3d: {
    new(): VectorArray3Triangle3d;
  };
  VectorVectorUndirectedEdgeId: {
    new(): VectorVectorUndirectedEdgeId;
  };
  VectorVectorFaceId: {
    new(): VectorVectorFaceId;
  };
  VectorVectorVertId: {
    new(): VectorVectorVertId;
  };
  VectorVectorPixelId: {
    new(): VectorVectorPixelId;
  };
  VectorVectorVoxelId: {
    new(): VectorVectorVoxelId;
  };
  VectorVectorRegionId: {
    new(): VectorVectorRegionId;
  };
  VectorVectorNodeId: {
    new(): VectorVectorNodeId;
  };
  VectorVectorObjId: {
    new(): VectorVectorObjId;
  };
  VectorVectorTextureId: {
    new(): VectorVectorTextureId;
  };
  VectorVectorGraphVertId: {
    new(): VectorVectorGraphVertId;
  };
  VectorVectorGraphEdgeId: {
    new(): VectorVectorGraphEdgeId;
  };
  VectorThreeVertIds: {
    new(): VectorThreeVertIds;
  };
  VectorEdgeId: {
    new(): VectorEdgeId;
  };
  fillContourLeft(_0: MeshTopology, _1: VectorEdgeId): FaceBitSet;
  fillHoles(_0: Mesh, _1: VectorEdgeId, _2: FillHoleParams): void;
  extendAllHoles(_0: Mesh, _1: Plane3f): VectorEdgeId;
  trackLeftBoundaryLoop(_0: MeshTopology, _1: EdgeId, _2: FaceBitSet | null): VectorEdgeId;
  trackRightBoundaryLoop(_0: MeshTopology, _1: EdgeId, _2: FaceBitSet | null): VectorEdgeId;
  VectorUndirectedEdgeId: {
    new(): VectorUndirectedEdgeId;
  };
  VectorFaceId: {
    new(): VectorFaceId;
  };
  findCollidingEdgeTrisPrecise_MeshEdges(_0: Mesh, _1: VectorEdgeId, _2: Mesh, _3: VectorFaceId, _4: ConvertToIntVector, _5: AffineXf3f | null): VectorEdgeTri;
  findCollidingEdgeTrisPrecise_MeshFaces(_0: Mesh, _1: VectorFaceId, _2: Mesh, _3: VectorEdgeId, _4: ConvertToIntVector, _5: AffineXf3f | null): VectorEdgeTri;
  VectorVertId: {
    new(): VectorVertId;
  };
  addTrianglesWithVertTriples(_0: MeshTopology, _1: VectorVertId, _2: FaceBitSet | null): void;
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
  doBooleanOperation(_0: Mesh, _1: Mesh, _2: VectorEdgePath, _3: VectorEdgePath, _4: BooleanOperation, _5: AffineXf3f | null, _6: BooleanResultMapper | null, _7: boolean, _8: BooleanInternalParameters): ExpectedMesh;
  fillContourLeftMultiple(_0: MeshTopology, _1: VectorEdgePath): FaceBitSet;
  findLeftBoundary(_0: MeshTopology, _1: FaceBitSet | null): VectorEdgePath;
  findRightBoundary(_0: MeshTopology, _1: FaceBitSet | null): VectorEdgePath;
  delRegionKeepBd(_0: Mesh, _1: FaceBitSet | null, _2: boolean): VectorEdgePath;
  findLeftBoundaryInsideMesh(_0: MeshTopology, _1: FaceBitSet): VectorEdgePath;
  VectorVectorEdgePath: {
    new(): VectorVectorEdgePath;
  };
  EdgeHashMapEntries: {
    new(): EdgeHashMapEntries;
  };
  findTwinEdgePairs(_0: Mesh, _1: number): EdgeHashMapEntries;
  findTwinEdgesFromEdgePairs(_0: EdgeHashMapEntries): EdgeBitSet;
  findTwinUndirectedEdgesFromEdgePairs(_0: EdgeHashMapEntries): UndirectedEdgeBitSet;
  findTwinUndirectedEdgeHashMapFromEdgePairs(_0: EdgeHashMapEntries): UndirectedEdgeHashMap;
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
  VectorVertSpanFaceId: {
    new(): VectorVertSpanFaceId;
  };
  VectorVectori: {
    new(): VectorVectori;
  };
  VectorVectord: {
    new(): VectorVectord;
  };
  VectorVectorf: {
    new(): VectorVectorf;
  };
  VectorVector2f: {
    new(): VectorVector2f;
  };
  VectorVectorVector2f: {
    new(): VectorVectorVector2f;
  };
  VectorVector2ll: {
    new(): VectorVector2ll;
  };
  VectorVectorVector2ll: {
    new(): VectorVectorVector2ll;
  };
  VectorVector2b: {
    new(): VectorVector2b;
  };
  VectorVectorVector2b: {
    new(): VectorVectorVector2b;
  };
  VectorVector2i: {
    new(): VectorVector2i;
  };
  VectorVectorVector2i: {
    new(): VectorVectorVector2i;
  };
  VectorVector2d: {
    new(): VectorVector2d;
  };
  VectorVectorVector2d: {
    new(): VectorVectorVector2d;
  };
  VectorVector3f: {
    new(): VectorVector3f;
  };
  VectorVectorVector3f: {
    new(): VectorVectorVector3f;
  };
  makeMovementBuildBody(_0: VectorVectorVector3f, _1: VectorVectorVector3f, _2: MovementBuildBodyParams): Mesh;
  extractMeshContours(_0: OneMeshContours): VectorVectorVector3f;
  getOneMeshIntersectionContours(_0: Mesh, _1: Mesh, _2: ContinuousContours, _3: OneMeshContours | null, _4: OneMeshContours | null, _5: CoordinateConverters, _6: AffineXf3f | null, _7: VectorVectorVector3f | null, _8: boolean): void;
  VectorVector3b: {
    new(): VectorVector3b;
  };
  VectorVectorVector3b: {
    new(): VectorVectorVector3b;
  };
  VectorVector3i: {
    new(): VectorVector3i;
  };
  VectorVectorVector3i: {
    new(): VectorVectorVector3i;
  };
  VectorVector3ll: {
    new(): VectorVector3ll;
  };
  VectorVectorVector3ll: {
    new(): VectorVectorVector3ll;
  };
  VectorVector3d: {
    new(): VectorVector3d;
  };
  VectorVectorVector3d: {
    new(): VectorVectorVector3d;
  };
  VectorVector4f: {
    new(): VectorVector4f;
  };
  VectorVectorVector4f: {
    new(): VectorVectorVector4f;
  };
  VectorVector4b: {
    new(): VectorVector4b;
  };
  VectorVectorVector4b: {
    new(): VectorVectorVector4b;
  };
  VectorVector4i: {
    new(): VectorVector4i;
  };
  VectorVectorVector4i: {
    new(): VectorVectorVector4i;
  };
  VectorVector4ll: {
    new(): VectorVector4ll;
  };
  VectorVectorVector4ll: {
    new(): VectorVectorVector4ll;
  };
  VectorVector4d: {
    new(): VectorVector4d;
  };
  VectorVectorVector4d: {
    new(): VectorVectorVector4d;
  };
  StringFunctorString: {
    new(): StringFunctorString;
  };
  ProgressCallback: {
    new(): ProgressCallback;
  };
  findSmallestCloseVertices(_0: Mesh, _1: number, _2: ProgressCallback): VertMap | undefined;
  findSmallestCloseVerticesFromCloud(_0: PointCloud, _1: number, _2: ProgressCallback): VertMap | undefined;
  findSmallestCloseVerticesFromCoords(_0: VertCoords, _1: number, _2: VertBitSet | null, _3: ProgressCallback): VertMap | undefined;
  findSmallestCloseVerticesUsingTree(_0: VertCoords, _1: number, _2: AABBTreePoints, _3: VertBitSet | null, _4: ProgressCallback): VertMap | undefined;
  findCloseVertices(_0: Mesh, _1: number, _2: ProgressCallback): VertBitSet | undefined;
  findCloseVerticesFromCloud(_0: PointCloud, _1: number, _2: ProgressCallback): VertBitSet | undefined;
  findCloseVerticesFromCoords(_0: VertCoords, _1: number, _2: VertBitSet | null, _3: ProgressCallback): VertBitSet | undefined;
  verticesGridSampling(_0: MeshPart, _1: number, _2: ProgressCallback): VertBitSet | undefined;
  pointGridSampling(_0: PointCloud, _1: number, _2: ProgressCallback): VertBitSet | undefined;
  multiModelGridSampling(_0: ModelPointsDataObjIdMap, _1: number, _2: ProgressCallback): VectorObjVertId | undefined;
  fromTriangles(_0: Triangulation, _1: BuildSettings, _2: ProgressCallback): MeshTopology;
  fromFaceSoup(_0: VectorVertId, _1: VertSpanFaceIdMap, _2: BuildSettings, _3: ProgressCallback): MeshTopology;
  relax(_0: Mesh, _1: MeshRelaxParams, _2: ProgressCallback): boolean;
  relaxWithTopology(_0: MeshTopology, _1: VertCoords, _2: MeshRelaxParams, _3: ProgressCallback): boolean;
  equalizeTriAreas(_0: Mesh, _1: MeshEqualizeTriAreasParams, _2: ProgressCallback): boolean;
  equalizeTriAreasWithTopology(_0: MeshTopology, _1: VertCoords, _2: MeshEqualizeTriAreasParams, _3: ProgressCallback): boolean;
  relaxKeepVolume(_0: Mesh, _1: MeshRelaxParams, _2: ProgressCallback): boolean;
  relaxKeepVolumeWithTopology(_0: MeshTopology, _1: VertCoords, _2: MeshRelaxParams, _3: ProgressCallback): boolean;
  relaxApprox(_0: Mesh, _1: MeshApproxRelaxParams, _2: ProgressCallback): boolean;
  relaxApproxWithTopology(_0: MeshTopology, _1: VertCoords, _2: MeshApproxRelaxParams, _3: ProgressCallback): boolean;
  VoidFunctorEdgeIdEdgeId: {
    new(): VoidFunctorEdgeIdEdgeId;
  };
  VertPredicate: {
    new(): VertPredicate;
  };
  FacePredicate: {
    new(): FacePredicate;
  };
  EdgePredicate: {
    new(): EdgePredicate;
  };
  UndirectedEdgePredicate: {
    new(): UndirectedEdgePredicate;
  };
  VertMetric: {
    new(): VertMetric;
  };
  FaceMetric: {
    new(): FaceMetric;
  };
  EdgeMetric: {
    new(): EdgeMetric;
  };
  UndirectedEdgeMetric: {
    new(): UndirectedEdgeMetric;
  };
  FloatFunctorTriangulation: {
    new(): FloatFunctorTriangulation;
  };
  FloatFunctorDipoles: {
    new(): FloatFunctorDipoles;
  };
  FloatFunctorFaceMap: {
    new(): FloatFunctorFaceMap;
  };
  FloatFunctorVertMap: {
    new(): FloatFunctorVertMap;
  };
  FloatFunctorEdgeMap: {
    new(): FloatFunctorEdgeMap;
  };
  FloatFunctorUndirectedEdgeMap: {
    new(): FloatFunctorUndirectedEdgeMap;
  };
  FloatFunctorObjMap: {
    new(): FloatFunctorObjMap;
  };
  FloatFunctorFaceBitSet: {
    new(): FloatFunctorFaceBitSet;
  };
  FloatFunctorVertBitSet: {
    new(): FloatFunctorVertBitSet;
  };
  FloatFunctorEdgeBitSet: {
    new(): FloatFunctorEdgeBitSet;
  };
  FloatFunctorUndirectedEdgeBitSet: {
    new(): FloatFunctorUndirectedEdgeBitSet;
  };
  FloatFunctorPixelBitSet: {
    new(): FloatFunctorPixelBitSet;
  };
  FloatFunctorVoxelBitSet: {
    new(): FloatFunctorVoxelBitSet;
  };
  FloatFunctorRegionBitSet: {
    new(): FloatFunctorRegionBitSet;
  };
  FloatFunctorNodeBitSet: {
    new(): FloatFunctorNodeBitSet;
  };
  FloatFunctorObjBitSet: {
    new(): FloatFunctorObjBitSet;
  };
  FloatFunctorTextureBitSet: {
    new(): FloatFunctorTextureBitSet;
  };
  FloatFunctorGraphVertBitSet: {
    new(): FloatFunctorGraphVertBitSet;
  };
  FloatFunctorGraphEdgeBitSet: {
    new(): FloatFunctorGraphEdgeBitSet;
  };
  ExpectedSurfacePathFunctorMeshTriPoint: {
    new(): ExpectedSurfacePathFunctorMeshTriPoint;
  };
  convertMeshTriPointsToMeshContourWithConnector(_0: Mesh, _1: VectorMeshTriPoint, _2: ExpectedSurfacePathFunctorMeshTriPoint, _3: StdVectori | null): ExpectedOneMeshContour;
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
  Vectord: {
    new(): Vectord;
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
  Vector2ll: {
    new(): Vector2ll;
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
  closestPointOnLineSegm2f(_0: Vector2f, _1: LineSegm2f): Vector2f;
  Vector2d: {
    new(): Vector2d;
  };
  closestPointOnLineSegm2d(_0: Vector2d, _1: LineSegm2d): Vector2d;
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
  createFindParamsImpl(_0: number, _1: number, _2: number, _3: number): FindParams;
  createFixParamsImpl(_0: FindParams, _1: number, _2: number, _3: boolean): FixParams;
  fixUndercutsImpl(_0: Mesh, _1: Vector3f, _2: number, _3: number): any;
  fixUndercutsImplTest(_0: Mesh, _1: Vector3f, _2: number, _3: number): any;
  fixUndercutsImplThrows(_0: Mesh, _1: Vector3f, _2: number, _3: number): void;
  closestPointOnLineSegm3f(_0: Vector3f, _1: LineSegm3f): Vector3f;
  buildBottom(_0: Mesh, _1: EdgeId, _2: Vector3f, _3: number): EdgeId;
  buildBottomWithOutput(_0: Mesh, _1: EdgeId, _2: Vector3f, _3: number): any;
  createVerticalStitchMetric(_0: Mesh, _1: Vector3f): FillHoleMetricWrapper;
  projectOnAllWithProgress(_0: Vector3f, _1: AABBTreeObjects, _2: number, _3: any, _4: ObjId): void;
  vertexPosEqualNeiAreas(_0: Mesh, _1: VertId, _2: boolean): Vector3f;
  vertexPosEqualNeiAreasWithTopology(_0: MeshTopology, _1: VertCoords, _2: VertId, _3: boolean): Vector3f;
  surroundingContourEdges(_0: Mesh, _1: VectorEdgeId, _2: EdgeMetric, _3: Vector3f): ExpectedEdgePath;
  surroundingContourVertices(_0: Mesh, _1: VectorVertId, _2: EdgeMetric, _3: Vector3f): ExpectedEdgePath;
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
  makeFreeFormOriginGrid(_0: Box3f, _1: Vector3i): VectorVector3f;
  findBestFreeformDeformation(_0: Box3f, _1: VectorVector3f, _2: VectorVector3f, _3: Vector3i, _4: AffineXf3f | null): VectorVector3f;
  distanceSqi(_0: Vector3i, _1: Vector3i): number;
  sqri(_0: Vector3i): number;
  crossi(_0: Vector3i, _1: Vector3i): Vector3i;
  doti(_0: Vector3i, _1: Vector3i): number;
  mixedi(_0: Vector3i, _1: Vector3i, _2: Vector3i): number;
  multi(_0: Vector3i, _1: Vector3i): Vector3i;
  divi(_0: Vector3i, _1: Vector3i): Vector3i;
  anglei(_0: Vector3i, _1: Vector3i): number;
  unitVector3i(_0: number, _1: number): Vector3i;
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
  closestPointOnLineSegm3d(_0: Vector3d, _1: LineSegm3d): Vector3d;
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
  Vector4b: {
    new(): Vector4b;
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
  Vector4ll: {
    new(): Vector4ll;
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
  Vector4d: {
    new(): Vector4d;
  };
  VisualObject: {
    new(): VisualObject;
  };
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
