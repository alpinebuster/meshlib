#!/usr/bin/env ts‑node

import express, { Request, Response, NextFunction } from 'express';
import path from 'path';
import { fileURLToPath } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const app = express();

// Add COEP/COOP to all responses
app.use((req: Request, res: Response, next: NextFunction) => {
	res.setHeader('Cross-Origin-Embedder-Policy', 'require-corp');
	res.setHeader('Cross-Origin-Opener-Policy', 'same-origin');
	next();
});

// Static directory (files under `dist`)
const DIST = path.join(__dirname, 'dist');
app.use(express.static(DIST));

app.get('./', (req: Request, res: Response) => {
	res.sendFile(path.join(DIST, 'index.html'));
});

const port = process.env.PORT ? Number(process.env.PORT) : 9311;
app.listen(port, () => {
	console.log(`Serving on http://localhost:${port}`);
});
