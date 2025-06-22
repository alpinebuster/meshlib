import { defineConfig } from 'vite'
import { resolve } from 'path'
import type { ServerOptions, BuildOptions } from 'vite'

// Utilizing TypeScript's type inference, defineConfig will automatically infer the correct type
export default defineConfig(({ command, mode, isSsrBuild, isPreview }) => {
	return {
		root: 'editor',

		build: {
			rollupOptions: {
				input: {
					main: resolve(__dirname, 'editor/index.html'),
					// Add more pages as needed
					// about: resolve(__dirname, 'editor/about.html'),
				},
				// NOTE: Mainly affects **production** construction, suitable for controlling which dependencies are not packaged
				// Tell Vite that these modules are external and not to try to package them
				// external: [
				// 	'three',
				// 	/^three\/addons\//,     // Match all imports starting with `three/addons/`
				// 	/^three\/examples\//,   // The same as above
				// 	'three-gpu-pathtracer',
				// 	'three-mesh-bvh',
				// ],
				output: {
					// Code partitioning strategy: separating large libraries into separate chunks
					manualChunks: {
						'three': ['three'],
						'three-addons': ['three/examples/jsm/'],
						'three-examples': ['three/examples/'],
						'three-gpu-pathtracer': ['three-gpu-pathtracer'],
						'three-mesh-bvh': ['three-mesh-bvh']
					}
				}
			},
			outDir: '../dist',
			// Whether or not to generate source mapping files for production debugging
			sourcemap: true,
			// Whether to empty the output directory when building
			emptyOutDir: true
		} as BuildOptions,

		optimizeDeps: {
			// Explicitly include large dependencies that need to be pre-built
			include: [
				'three',
				'three-gpu-pathtracer',
				'three-mesh-bvh',
			],
			// NOTE: Primarily affects dependency pre-builds in **development** environments and applies to performance optimization during development
			// Explicitly excluding these dependencies prevents Vite from trying to pre-build them
			exclude: [
				// 'three',
				// 'three-gpu-pathtracer',
				// 'three-mesh-bvh',
				// FIXME: Why windows needs this but unix systems not?
				'@alpinebuster/meshlib',
				"@ffmpeg/ffmpeg", "@ffmpeg/util",
			],

			esbuildOptions: {
				target: 'esnext',
				// Explicit support for the top-level `await` feature
				supported: {
					'top-level-await': true
				},
				define: {
					global: 'globalThis',  // Ensuring that Three.js works in all environments
				},
				// Set the output format to ESM
				format: 'esm',
			}
		},

		server: {
			port: 3320,
			host: 'localhost',
			// open: true,
			fs: {
				// REF: `https://vite.dev/config/server-options.html#server-fs-allow`
				strict: command === 'build',
			},
			/**
			 * To use `SharedArrayBuffer` (i.e., enable multithreading with Emscripten-Pthreads) in the browser 
			 * and pass it between Workers via `postMessage`, 
			 * the page must run in a **cross-origin isolated** state.
			 * Otherwise, you will encounter the error:
			 *
			 *  ```txt
			 *  SharedArrayBuffer transfer requires self.crossOriginIsolated
			 *  ```
			 */
			headers: {
				// Ensure that your page and any context it opens in (e.g., subwindows, iframes) 
				// belong to the same source so that they are not interfered with by other sources.
				'Cross-Origin-Opener-Policy': 'same-origin',
				// Require that all embedded resources (scripts, WebAssembly, workers, etc.) 
				// are either homologous or come with explicit licenses
				'Cross-Origin-Embedder-Policy': 'require-corp',
			},

			hmr: {
				port: 3321,
				overlay: true,  // Displaying error overlays in the browser
			},

			watch: {
				include: ['editor/**/*.html', 'editor/**/*.js', 'editor/**/*.ts', 'editor/**/*.css'],
				ignored: ['**/node_modules/**', '**/dist/**']
			}
		} as ServerOptions,

		css: {
			devSourcemap: true,
			preprocessorOptions: {
				scss: {
					// SCSS Global Variable Import Example
					additionalData: `@import "@/styles/variables.scss";`
				}
			}
		},

		// Path Alias Configuration - Make Import Paths Simpler
		resolve: {
			alias: {
				'three/addons/': resolve(__dirname, 'node_modules/three/examples/jsm/'),
				'three/examples/': resolve(__dirname, 'node_modules/three/examples/')
			}
		},

		// Environment Variable Configuration
		define: {
			// Global constants can be defined here
			__DEV__: JSON.stringify(process.env.NODE_ENV !== 'production')
		}
	}
});
