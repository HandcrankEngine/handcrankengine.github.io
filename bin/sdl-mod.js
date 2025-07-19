Object.defineProperty(document, 'title', {
  set: value => {
    console.log(`Attempted to change the page title to "${value}".`);
  },
  configurable: true
});
