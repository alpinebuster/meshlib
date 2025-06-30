import createMeshLib from './MRJavaScript.js';

export { createMeshLib };
export const create = createMeshLib;

export type MRMesh = Awaited<ReturnType<typeof createMeshLib>>;
export const MRMesh = { create: createMeshLib };
