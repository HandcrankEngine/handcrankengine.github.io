import { Marked } from 'marked';

import markedFootnote from 'marked-footnote';
import { markedHighlight } from 'marked-highlight';

import hljs from 'highlight.js';

const marked = new Marked(
  markedFootnote(),
  markedHighlight({
    langPrefix: 'hljs language-',
    highlight(code, lang) {
      const language = hljs.getLanguage(lang) ? lang : 'plaintext';
      return hljs.highlight(code, { language }).value;
    }
  })
);

const renderMarkdown = async (contents: string) => {
  let output = await marked.parse(contents);

  output = output
    .replace(/<pre>/g, '<copy-to-clipboard><pre>')
    .replace(/<\/pre>/g, '</pre></copy-to-clipboard>')
    .replace(/<!\-\-.*\-\->/gs, '');

  output = output.replace(
    /<img src="(.+\.mp4)" alt="(.*)">/,
    `<video autoplay="autoplay" loop="loop" muted="muted">
    <source type="video/mp4" src="$1">
</video>`
  );

  return output;
};

export default renderMarkdown;
