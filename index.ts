import { readFile } from 'node:fs/promises';

import hljs from 'highlight.js';

import { html } from 'onlybuild';

import renderMarkdown from './_utilities/render-markdown.js';
import getModifiedDate from './_utilities/get-modified-date.js';

const renderDemo = async (name: string) => {
  return html`<div class="wrapper">
      ${await renderMarkdown(await readFile(`demos/${name}/header.md`, 'utf8'))}
    </div>

    <div class="demo">
      <canvas id="${name}" tabindex="-1" width="1000" height="600"></canvas>
    </div>

    <script src="demos/${name}/${name}.js"></script>
    <script>
      ${name}Module({
        canvas: document.querySelector('#${name}')
      });
    </script>`;
};

const renderDemoWithCode = async (name: string) => {
  const code = await readFile(`demos/${name}/${name}.cpp`, 'utf8');

  const highlightedCode = hljs.highlight(code, { language: 'cpp' }).value;

  return html`<div class="wrapper">
      ${await renderMarkdown(await readFile(`demos/${name}/header.md`, 'utf8'))}
    </div>

    <div class="demo">
      <div class="demo-canvas">
        <canvas id="${name}" tabindex="-1" width="1000" height="600"></canvas>
        <p class="demo-canvas-footer">This is live demo of the code snippet.</p>
      </div>

      <copy-to-clipboard class="demo-code">
        <pre><code class="hljs language-cpp">${highlightedCode}</code></pre>
      </copy-to-clipboard>

      <script src="demos/${name}/${name}.js"></script>
      <script>
        ${name}Module({
          canvas: document.querySelector('#${name}')
        });
      </script>
    </div>`;
};

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
      <main>
        <header>
          <div class="wrapper">
            <img
              src="./images/logo-rounded.svg"
              alt="Handcrank Engine"
              class="logo"
            />
            ${await renderMarkdown(
              await readFile('./_includes/header.md', 'utf8')
            )}
          </div>
        </header>

        ${await renderDemo('demo')}
        ${await renderDemoWithCode('drawRectRenderer')}
        ${await renderDemoWithCode('simpleEventLoop')}
        ${await renderDemoWithCode('spriteRenderer')}
        ${await renderDemoWithCode('animation')}
        ${await renderDemoWithCode('tiledMapSupport')}
      </main>
      <footer>
        <div class="wrapper">
          <p>
            Last Updated
            ${(await getModifiedDate('./index.ts')).toLocaleDateString(
              'en-us',
              {
                year: 'numeric',
                month: 'long',
                day: 'numeric'
              }
            )}
          </p>
        </div>
      </footer>
    </body>
  </html>`;
