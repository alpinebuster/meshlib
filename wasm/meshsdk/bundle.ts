#!/usr/bin/env node

import { fileURLToPath } from 'url';
import { dirname, join, normalize } from 'path';
import { existsSync, rmSync, mkdirSync, copyFileSync } from 'fs';
import { execSync } from 'child_process';

// Get current directory (equivalent to cd "$(dirname "$0")")
const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
process.chdir(__dirname);

const OUT_DIRECTORY = 'lib';

// Main build function
async function build(): Promise<void> {
	try {
		console.log('Starting build process...');

		// Clean or create lib directory
		if (existsSync(OUT_DIRECTORY)) {
			console.log(`Cleaning existing ${OUT_DIRECTORY} directory...`);
			rmSync(OUT_DIRECTORY, { recursive: true, force: true });
		}
		mkdirSync(OUT_DIRECTORY, { recursive: true });

		// Compile TypeScript
		console.log('Compiling TypeScript...');
		execSync('npx tsc --project tsconfig.production.json', {
			stdio: 'inherit',
			cwd: process.cwd()
		});

		// Copy required files to lib directory
		console.log('Copying required files...');
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

		console.log('Build completed successfully!');
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
