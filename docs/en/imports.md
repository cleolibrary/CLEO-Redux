# Imports

You can import other scripts and some custom file formats in your code to make the code modular and share the common logic.


## Importing scripts

- Extensions: `.js`, `.mjs`

The runtime supports the `import` statement as described in [this article](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/import). 

`./` in a path resolves to the current file's directory. If a script is located at `C:\Game\CLEO\mod1\extra\addon.js` and it contains `import { foo } from './bar.js'`, the runtime will try to load `C:\Game\CLEO\mod1\extra\bar.js`. 

`../` resolves to the parent directory. If a script is located at `C:\Game\CLEO\mod1\extra\addon.js` and it contains `import { foo } from '../bar.js'`, the runtime will try to load `C:\Game\CLEO\mod1\bar.js`.


To avoid running imported `.js` files as standalone scripts, either put them into a separate folder outside of the main [CLEO directory](./cleo-directory.md) (e.g. `CLEO/includes/`) or use the extension `.mjs`.

```js
// imports default export from other.js or other.mjs located in the same directory
import func from "./other";

// imports named export PedType from types.js or types.mjs located in the CLEO/includes directory
import { PedType } from "./includes/types";

```

> See also [Dynamic Imports](./async.md#dynamic-imports).

## Importing JSON files

- Extensions: `.json`

```js
// imports vehicles.json as a JavaScript value (an array, object).
import data from "./vehicles.json";
```

## Importing other formats

CLEO Redux supports custom file loaders. The purpose of a loader is to load a provided file, parse it and serialize into a JSON string suitable for the use in JavaScript. Those loaders are implemented as [CLEO plugins](./installation-plugins.md) and use [CLEO SDK](./using-sdk.md#developing-file-loaders) to associate itself with particular file extensions.

Default CLEO installation includes loaders for `.txt` and `.ide` files.

### TXT

- Extensions: `.txt`, `.text`
- Plugin name: `TextLoader.cleo`

The TXT loader transforms a text file into an array of strings where each element is a line in the text file. For an empty file an empty array is constructed. If the file can not be open for reading the import statement raises an exception.

```js
import lines from "./some-file.txt";

for (const line of lines) {
  log(line); // prints a line
}
```

This script prints each line from the `some-file.txt` file into the log. If you need the content of the file as a single string use `.join('')` method to concatenate all array elements:

```js
import lines from "./some-file.txt";

log(lines.join("")); // prints the entire file
```

### IDE

- Extensions: `.ide`
- Plugin name: `IdeLoader.cleo`

The IDE loader transforms an item definition file (`*.ide`) that is widely used in GTA series games. The file is imported as an object where each key corresponds to a section in the file and the value is an array of array of strings:

```ts
interface Ide {
  [key: string]: Array<Array<string>>;
}
```

A first-level array represents a list of lines within this section in the file, and a second-level array represents a list of columns within that line. E.g. the following IDE file

```
peds
0, null, generic, PLAYER1, STAT_PLAYER, player, 7f
1, cop, cop, COP, STAT_COP, man, 7f
end

objs
170, grenade, generic, 1, 100, 0
end

```

would be transformed into:

```json
{
    "peds": [
        ["0", "null", "generic", "PLAYER1", "STAT_PLAYER", "player", "7f"],
        ["1", "cop", "cop", "COP", "STAT_COP", "man", "7f"]
    ],
    "objs": [
        "170", "grenade", "generic", "1", "100", "0"
    ]
}
```

Note that each data element becomes a string, even if it was a number in the original file. The loader does not make any assumption about specific sections, nor validate them. It follows a few simple rules where each section should start with an identifier ("peds", "objs") and end with the "end" string. It considers each line to be a comma- or space-separated set of columns that could be anything.

```js
// read data/default.ide file in the game directory
import data from "data/default.ide";

// read "peds" section from the file
const peds = data.peds;

// find a line in the peds section where the second element (column) is "cop"
const cop = peds.find((line) => line[1] === "cop");

// if the line is found print the model id from the first column
if (cop) {
  log("Cop model ID is " + parseInt(cop[0]));
} else {
  log("Model with the name 'cop' not found");
}
```

This script shows how you can use `.find` and other common array methods to find a line in the imported IDE file and use it. It prints `1` when given a file with the content shown above.
