#!/usr/bin/env node

import { fileURLToPath } from 'url';
import { dirname, join, normalize } from 'path';
import { existsSync, rmSync, mkdirSync, copyFileSync, readdirSync, readFileSync, writeFileSync } from 'fs';
import { execSync } from 'child_process';

// Get current directory (equivalent to cd "$(dirname "$0")")
const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
process.chdir(__dirname);

const OUT_DIRECTORY = 'lib';

// Main build function
async function build(): Promise<void> {
	try {
		// Find WASM bin directory
		const debugBin = join(__dirname, '../../build/Debug/bin');
		const releaseBin = join(__dirname, '../../build/Release/bin');
		const binDir = existsSync(debugBin) ? debugBin : releaseBin;
		console.log(`\n************ Using WASM bin directory: ${binDir} ************`);

		// Copy `MRJavaScript.*` files from `binDir` to `src/`
		const binFiles = readdirSync(binDir).filter(f => f.startsWith('MRJavaScript.'));
		if (binFiles.length === 0) {
			console.warn(`No \`MRJavaScript.*\` files found in ${binDir}!`);
		} else {
			console.log('\n');
			for (const file of binFiles) {
				const srcPath = join(binDir, file);
				const destPath = join(__dirname, 'src', file);
				copyFileSync(srcPath, destPath);
				console.log('----------------------------------------------------------------------');
				console.log(`Copied WASM bin ${file} to \`src/\` directory！！！`);
			}
			console.log('----------------------------------------------------------------------');
		}


		/// NOTE: Patching for issue #24579: `https://github.com/emscripten-core/emscripten/issues/24579`
		const wasmDTSPath = join(__dirname, 'src', 'MRJavaScript.d.ts');
		if (existsSync(wasmDTSPath)) {
			let wasmDTSContent = readFileSync(wasmDTSPath, 'utf-8');
			wasmDTSContent = wasmDTSContent.replace(/Arguments/g, 'IArguments');
			writeFileSync(wasmDTSPath, wasmDTSContent);
			console.log('\n');
			console.log('----------------------------------------------------------------------');
			console.log('Replaced type `Arguments` with `IArguments` in `MRJavaScript.d.ts`！！！');
			console.log('----------------------------------------------------------------------\n');
		} else {
			console.warn('`MRJavaScript.d.ts` not found, cannot replace type `Arguments`!');
		}
		///


		console.log('\n************ Starting build process ************');

		// Clean or create lib directory
		if (existsSync(OUT_DIRECTORY)) {
			console.log(`Cleaning existing ${OUT_DIRECTORY} directory...`);
			rmSync(OUT_DIRECTORY, { recursive: true, force: true });
		}
		mkdirSync(OUT_DIRECTORY, { recursive: true });

		// Compile TypeScript
		console.log('\n************ Compiling TypeScript ************');
		execSync('npx tsc --project tsconfig.production.json', {
			stdio: 'inherit',
			cwd: process.cwd()
		});

		// Copy required files to lib directory
		console.log('\n************ Copying required files ************');
		const filesToCopy = [
			'src/MRJavaScript.wasm',
			// 'src/MRJavaScript.data',
			'src/MRJavaScript.d.ts',
			'src/MRJavaScript.js'
		];

		for (const file of filesToCopy) {
			if (existsSync(file)) {
				const fileName = file.split('/').pop()!;
				copyFileSync(file, join(OUT_DIRECTORY, fileName));
				console.log(`Copied ${file} to ${OUT_DIRECTORY}/`);
			} else {
				console.warn(`Warning: ${file} not found, skipping...`);
			}
		}

		///
		// Bundle for different environments
		// const environments = ['node', 'web'];
		// for (const env of environments) {
		// 	await bundle(env);
		// }
		///

		console.log('\n************ Build completed successfully! ************');
	} catch (error) {
		console.error('Build failed:', error);
		process.exit(1);
	}
}

// Bundle function for specific environment
async function bundle(environment: string): Promise<void> {
	console.log(`Bundling for ${environment} environment...`);

	const envDir = join(OUT_DIRECTORY, environment);
	mkdirSync(envDir, { recursive: true });

	// Files to copy for each environment
	const filesToBundle = [
		'index.js',
		'index.d.ts',
		'MRJavaScript.js',
		'MRJavaScript.wasm',
		// 'MRJavaScript.data',
		'MRJavaScript.d.ts'
	];

	for (const file of filesToBundle) {
		const srcPath = join(OUT_DIRECTORY, file);
		const destPath = join(envDir, file);

		if (existsSync(srcPath)) {
			copyFileSync(srcPath, destPath);
			console.log(`  Copied ${file} to ${environment}/`);
		} else {
			console.warn(`  Warning: ${srcPath} not found for ${environment} bundle`);
		}
	}
}

// Run the build if this script is executed directly
if (normalize(import.meta.url) === normalize(`file://${process.argv[1]}`)) {
	build().catch((error) => {
		console.error('Unhandled error:', error);
		process.exit(1);
	});
}

export { build, bundle };
