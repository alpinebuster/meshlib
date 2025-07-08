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

To use the meshlib, do the following:

```js
import { createMeshSDK } from 'meshlib';

const mrmesh = await createMeshSDK();
```

Ensure cross-origin isolation (COOP + COEP) is supported:

1.Vite

```js
export default defineConfig({
  ...,

  server: {
    headers: {
      // Enforcing cross-origin isolation of pages
      'Cross-Origin-Opener-Policy': 'same-origin',
      'Cross-Origin-Embedder-Policy': 'require-corp'
    }
  },

  ...
});
```

2.Nginx

```nginx
server {
  listen 80;
  server_name your.domain.com;
  
  add_header Cross-Origin-Opener-Policy same-origin;
  add_header Cross-Origin-Embedder-Policy require-corp;
  
  root /var/www/your-app;
  index index.html;
}
```

## Local Development

```sh
npm install
npm run build
```

## Release

```sh
npm login
npm publish --tag beta --access public
npm publish --tag latest --access public
```
