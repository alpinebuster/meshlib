import { promises as fs } from 'fs'
import { join } from 'path'

import { createMeshSDK } from '..'
import { parseHeader } from './utils'

const testdatadir = join(__dirname, '../../../cpp/test/raw-sets')

test('file reader', async () => {
  const file = await fs.readFile(join(testdatadir, 'autzen_trim.laz'))

  const {
    pointDataRecordFormat,
    pointDataRecordLength,
    pointCount,
    scale,
    offset,
    min,
    max,
  } = parseHeader(file)

  // Check some header values for sanity, for example we want to make sure we
  // don't get a pointCount of 0 and then not perform any data checks.
  expect(pointDataRecordFormat).toEqual(3)
  expect(pointDataRecordLength).toEqual(34)
  expect(pointCount).toEqual(110_000)
  expect(scale).toEqual([0.01, 0.01, 0.01])
  expect(min.every((v, i) => v < max[i])).toBe(true)

  // Create our Emscripten module.
  const MRMesh = await createMeshSDK()
  const laszip = new MRMesh.LASZip()

  // Allocate our memory in the Emscripten heap: a filePtr buffer for our
  // compressed content and a single point's worth of bytes for our output.
  const dataPtr = MRMesh._malloc(pointDataRecordLength)
  const filePtr = MRMesh._malloc(file.byteLength)

  // Copy our data into the Emscripten heap so we can point at it in getPoint().
  MRMesh.HEAPU8.set(
    new Uint8Array(file.buffer, file.byteOffset, file.byteLength),
    filePtr
  )

  try {
    laszip.open(filePtr, file.byteLength)

    for (let i = 0; i < pointCount; ++i) {
      laszip.getPoint(dataPtr)

      // Now our dataPtr (in the Emscripten heap) contains our point data, copy
      // it out into our own Buffer.
      const pointbuffer = Buffer.from(
        MRMesh.HEAPU8.buffer,
        dataPtr,
        pointDataRecordLength
      )

      // Grab the scaled/offset XYZ values and reverse the scale/offset to get
      // their absolute positions.  It would be possible to add checks for
      // attributes other than XYZ here - our pointbuffer contains an entire
      // point whose format corresponds to the pointDataRecordFormat above.
      const point = [
        pointbuffer.readInt32LE(0),
        pointbuffer.readInt32LE(4),
        pointbuffer.readInt32LE(8),
      ].map((v, i) => v * scale[i] + offset[i])

      // Doing 6 expect(point[n]).toBeGreaterThanOrEqual(min[n]) style checks in
      // this tight loop slows down the test by 50x, so do a quicker check.
      if (point.some((v, i) => v < min[i] || v > max[i])) {
        console.error(i, point, min, max)
        throw new Error(`Point ${i} out of expected range`)
      }
    }
  } finally {
    MRMesh._free(filePtr)
    MRMesh._free(dataPtr)
    laszip.delete()
  }
})
