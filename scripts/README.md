# Building

## Cannot convert a BigInt value to a number

There were some change to the memory64 spec relatively recently. You'll need set `NODE_JS` in your emscripten config use `node 24`, see [issue #24620](https://github.com/emscripten-core/emscripten/issues/24620).

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
