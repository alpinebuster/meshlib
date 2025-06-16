# Javascript/Typescript Binding for the meshlib

`meshlib` JS/TS implementation. It supports compilation
to WASM via [Emscripten](https://emscripten.org/) so that `meshlib` features can be used in a browser.

## Using `meshlib` in JavaScript/TypeScript

### Install

`meshlib` is available as a UMD module compatible with both NodeJS and browsers,
and includes TypeScript definitions.

```sh
npm install meshlib
```

### Usage

```js
import { createMeshLib } from 'meshlib';

const LazPerf = await createMeshLib();
```

## Local Development

Change `function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: (Arguments|any[]) | undefined, opts?: any | undefined): any;`
to `function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: (IArguments|any[]) | undefined, opts?: any | undefined): any;`, more at <https://github.com/DefinitelyTyped/DefinitelyTyped/blob/master/types/emscripten/index.d.ts> and <https://github.com/emscripten-core/emscripten/issues/24579>.

```sh
npm run install
npm run build
```
