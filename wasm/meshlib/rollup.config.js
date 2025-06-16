import commonjs from "@rollup/plugin-commonjs";
import copy from "rollup-plugin-copy";
import includePaths from "rollup-plugin-includepaths";
import typescript from "@rollup/plugin-typescript";

export default {
  input: "src/index.ts",
  output: {
    file: "lib/index.js",
    format: "umd",
    name: "MRMesh",
    globals: { fs: "fs", path: "path" },
  },
  external: ["fs", "path"],
  plugins: [
    commonjs({ include: "src/MRJavaScript.js" }),
    typescript({
      tsconfig: "./tsconfig.production.json",
      // Put declarations at the top level of the output dir.
      // declarationDir: ".",
    }),
    includePaths({ paths: "src", extensions: [".ts", ".js"] }),
    copy({
      targets: [
        { src: "src/MRJavaScript.wasm", dest: "lib" },
        // { src: "src/MRJavaScript.data", dest: "lib" },
        { src: "src/MRJavaScript.d.ts", dest: "lib" },
      ],
    }),
  ],
};
