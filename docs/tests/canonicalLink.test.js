const fs = require('fs');
const path = require('path');
const cheerio = require('cheerio');
require('dotenv').config();

function getHtmlFiles(dir) {
  const htmlFiles = [];

  function readDirRecursively(currentDir) {
    const items = fs.readdirSync(currentDir, { withFileTypes: true });
    items.forEach(item => {
      const fullPath = path.join(currentDir, item.name);
      if (item.isDirectory()) {
        readDirRecursively(fullPath);
      } else if (item.isFile() && item.name.endsWith('.html')) {
        htmlFiles.push(fullPath);
      }
    });
  }
  readDirRecursively(dir);

  return htmlFiles;
}

function testCanonicalLink(filePath, rootDir, urlPrefix) {
  const html = fs.readFileSync(filePath, 'utf8');
  const $ = cheerio.load(html);
  const canonicalTag = $('link[rel="canonical"]');
  expect(canonicalTag.length).toBeGreaterThan(0);

  const href = canonicalTag.attr('href');
  expect(href).toBeDefined();

  const relativePath = path.relative(rootDir, filePath);
  const expectedUrl = `${urlPrefix}/${relativePath}`;
  expect(href).toBe(expectedUrl);
}

describe('HTML file canonical link tests', () => {
  const htmlDir = process.env.HTML_DIR;
  const urlPrefix = process.env.URL_PREFIX;

  if (!htmlDir || !urlPrefix) {
    throw new Error('Please specify HTML_DIR and URL_PREFIX in .env');
  }

  const filesToTest = getHtmlFiles(htmlDir);

  filesToTest.forEach(filePath => {
    it(`should contain <link rel="canonical"> tag with correct URL in ${filePath}`, () => {
      testCanonicalLink(filePath, htmlDir, urlPrefix);
    });
  });
});