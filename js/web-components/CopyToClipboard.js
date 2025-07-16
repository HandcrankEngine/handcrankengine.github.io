{
  const css = content => content;

  const delayBeforeHidingCopyCheckmark = 1000;

  const styles = css`
    @import url('https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.11.1/styles/base16/github.min.css')
    (prefers-color-scheme: light);

    @import url('https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.11.1/styles/base16/dracula.min.css')
    (prefers-color-scheme: dark);

    div {
      position: relative;
    }

    pre {
      margin: 2rem 0;
      font-family: inherit;
      font-size: 1rem;
      background-color: var(--pre-background-color);
    }

    button {
      position: absolute;
      top: 0.9rem;
      right: 0.9rem;
      padding: 0;
      font-size: 1rem;
      line-height: 1;
      border: none;
      background: none;
      cursor: pointer;
    }

    button svg:hover {
      opacity: 0.75;
    }

    button span {
      display: block;
      position: absolute;
      padding: 0.25rem 0.5rem;
      border-radius: 0.25rem;
      opacity: 0;
      right: calc(100% + 1rem);
    }

    button.copied span {
      animation: slide-in 200ms;
      animation-fill-mode: forwards;
    }

    button.slide-out span {
      animation: slide-out 200ms;
      animation-fill-mode: forwards;
    }

    @media (prefers-color-scheme: dark) {
      svg {
        fill: #fff;
      }

      button.copied svg {
        stroke: #fff;
      }

      button span {
        color: #000;
        background-color: #fff;
      }
    }

    @media (prefers-color-scheme: light) {
      svg {
        fill: #000;
      }

      button.copied svg {
        stroke: #000;
      }

      button span {
        color: #fff;
        background-color: #000;
      }
    }

    @keyframes slide-in {
      from {
        opacity: 0;
        right: calc(100% + 0.75rem);
      }

      to {
        opacity: 1;
        right: calc(100% + 0.5rem);
      }
    }

    @keyframes slide-out {
      from {
        opacity: 1;
        right: calc(100% + 0.5rem);
      }

      to {
        opacity: 0;
        right: calc(100% + 0.75rem);
      }
    }
  `;

  class CopyToClipboard extends HTMLElement {
    /** @type {any} */
    timeout = null;

    constructor() {
      super();

      this.attachShadow({ mode: 'open' });

      this.shadowRoot?.appendChild(this.stylesheet());
      this.shadowRoot?.appendChild(this.preTags());
    }

    /**
     * Returns a document fragment containing copies of the Web Component's child pre tags.
     *
     * @returns {DocumentFragment}
     */
    preTags() {
      const fragment = document.createDocumentFragment();

      /** @type {HTMLPreElement[]} */
      const tags = Array.from(this.querySelectorAll('pre'));

      for (let i = 0; i < tags.length; i += 1) {
        const div = document.createElement('div');

        div.appendChild(this.clipboardButton());

        div.appendChild(tags[i]);

        fragment.appendChild(div);
      }

      return fragment;
    }

    /**
     * Returns a style tag for use within the Web Component shadow DOM.
     *
     * @returns {HTMLStyleElement}
     */
    stylesheet() {
      const style = document.createElement('style');

      style.appendChild(document.createTextNode(styles));

      return style;
    }

    handleClipboardButtonClick = e => {
      /** @type {HTMLButtonElement} */
      const button = e.target.closest('button');
      /** @type {HTMLPreElement} */
      const pre = e.target.closest('div').querySelector('pre');

      if (!pre || !pre.textContent) {
        return;
      }

      let content = pre.textContent.trim();

      if (pre.querySelector('.language-bash') && !content.match(/\n/)) {
        content = content.replace(/^\$\s+/, '');
      }

      navigator.clipboard.writeText(content);

      button.classList.add('copied');
      button.classList.remove('slide-out');

      if (this.timeout) {
        clearTimeout(this.timeout);
      }

      this.timeout = setTimeout(() => {
        button.classList.remove('copied');
        button.classList.add('slide-out');
      }, delayBeforeHidingCopyCheckmark);
    };

    /**
     * Returns a button with the clipboard SVG icon.
     *
     * @returns {HTMLButtonElement}
     */
    clipboardButton = () => {
      const button = document.createElement('button');

      button.appendChild(this.createElementWithTextNode('span', 'Copied!'));

      button.appendChild(this.clipboardIcon());

      button.addEventListener('click', this.handleClipboardButtonClick);

      return button;
    };

    /**
     * Returns an SVG icon of a clipboard.
     *
     * @returns {SVGSVGElement}
     */
    clipboardIcon = () => {
      const xmlNamespace = 'http://www.w3.org/2000/svg';

      const svg = document.createElementNS(xmlNamespace, 'svg');

      svg.setAttribute('height', '1.5em');
      svg.setAttribute('viewBox', '0 0 384 512');

      svg.appendChild(
        document.createComment(
          'Awesome Free 6.5.2 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license/free Copyright 2024 Fonticons, Inc.'
        )
      );

      const svgClipboardPath = document.createElementNS(xmlNamespace, 'path');

      svgClipboardPath.setAttribute(
        'd',
        'M280 64h40c35.3 0 64 28.7 64 64V448c0 35.3-28.7 64-64 64H64c-35.3 0-64-28.7-64-64V128C0 92.7 28.7 64 64 64h40 9.6C121 27.5 153.3 0 192 0s71 27.5 78.4 64H280zM64 112c-8.8 0-16 7.2-16 16V448c0 8.8 7.2 16 16 16H320c8.8 0 16-7.2 16-16V128c0-8.8-7.2-16-16-16H304v24c0 13.3-10.7 24-24 24H192 104c-13.3 0-24-10.7-24-24V112H64zm128-8a24 24 0 1 0 0-48 24 24 0 1 0 0 48z'
      );

      svg.appendChild(svgClipboardPath);

      const svgCheckMarkPath = document.createElementNS(xmlNamespace, 'path');

      svgCheckMarkPath.setAttribute('d', 'M121 328.892L161.343 369L274 257');
      svgCheckMarkPath.setAttribute('fill', 'none');
      svgCheckMarkPath.setAttribute('stroke-width', '40');
      svgCheckMarkPath.setAttribute('stroke-linecap', 'round');
      svgCheckMarkPath.setAttribute('stroke-linejoin', 'round');

      svg.appendChild(svgCheckMarkPath);

      return svg;
    };

    /**
     * Create an HTMLElement with text.
     *
     * @param {string} tagName
     * @param {string | null} content
     * @returns {HTMLElement}
     */
    createElementWithTextNode(tagName, content = null) {
      const element = document.createElement(tagName);

      if (content) {
        element.appendChild(document.createTextNode(content));
      }

      return element;
    }
  }

  customElements.define('copy-to-clipboard', CopyToClipboard);
}
