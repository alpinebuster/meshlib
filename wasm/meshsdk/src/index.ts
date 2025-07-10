import createMeshSDK from './MRJavaScript.js';

export { createMeshSDK };
export const create = createMeshSDK;

export type MRMesh = Awaited<ReturnType<typeof createMeshSDK>>;
export const MRMesh = { create: createMeshSDK };
