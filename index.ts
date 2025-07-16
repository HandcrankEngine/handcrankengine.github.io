import { readFile } from 'node:fs/promises';

import { html } from 'onlybuild';

import renderMarkdown from './_utilities/render-markdown.js';
import getModifiedDate from './_utilities/get-modified-date.js';

export default html`<!DOCTYPE html>
  <html lang="en">
    <head>
      <meta charset="utf-8" />
      <meta name="viewport" content="initial-scale=1" />

      <title>Handcrank Engine</title>

      <meta name="description" content="Handcrank Engine" />

      <link rel="stylesheet" href="/css/styles.css" />

      <script src="/js/web-components/CopyToClipboard.js" defer></script>
    </head>
    <body>
      <main>${await renderMarkdown(await readFile('./index.md', 'utf8'))}</main>
      <footer>
        <p>
          Last Updated
          ${(await getModifiedDate('./index.md')).toLocaleDateString('en-us', {
            year: 'numeric',
            month: 'long',
            day: 'numeric'
          })}
        </p>
      </footer>
    </body>
  </html>`;
