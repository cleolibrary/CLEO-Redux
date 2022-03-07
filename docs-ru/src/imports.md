# Imports

You can import other script files in your code to make the code modular and share the common logic. The runtime supports the `import` statement as described in [this article](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/import).

To avoid running the included `.js` files as standalone scripts, either put them into a separate folder (e.g. `CLEO/includes/`) or use the extension `.mjs`.

```js
// imports default export from other.js or other.mjs located in the same directory
import func from "./other"; 

// imports named export PedType from types.js or types.mjs located in the CLEO/includes directory
import { PedType } from "./includes/types"; 

// imports vehicles.json as a JavaScript value (an array, object).
import data from "./vehicles.json";
```

Currently only import of `.js` (`.mjs`) and `.json` files is supported.