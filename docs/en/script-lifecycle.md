# Script Lifecycle

A file with the JavaScript code should have a `.js` extension and contain valid instructions.

Valid instructions include a code conforming to the ECMAScript 2020 standard and custom bindings available in the CLEO Redux runtime. If the runtime encounters an unknown or [illegal](./permissions.md) instruction the execution halts and a new error is [logged](./log.md) in `cleo_redux.log`. The script may have no instructions (the empty script).

CLEO script runs as soon as the new game starts or a save file is loaded. If you change the file while the game is running, CLEO [reloads](./other-features.md#hot-reload) the script and it restarts.

The script terminates automatically when the last instruction has been executed. The runtime also terminates stuck scripts to prevent the game from freezing. The stuck script is the one that took more than `2` seconds to run since the last wait command. If that happened, check out your loops, some of the are missing the wait command.

```js
while (true) {
  // meaningless infinite loop normally freezing the game
  // will be terminated after two seconds
}
```

The runtime will terminate this script. To avoid that, add the wait command

```js
while (true) {
  wait(250);
  // still meaningless, but does not freeze the game
}
```

## Boot Scripts

> This feature is available since CLEO Redux v1.5.0.

Boot scripts are special one-shot scripts running as soon as runtime is loaded. They can set up initial state or perform operations that don't require the game loop.

Boot scripts are identified by the `.boot.mjs` or `.boot.mts` filename suffix (case-insensitive). For example:

- `init.boot.mjs`
- `CLEO/mod/mod.boot.mjs`

Boot scripts have the following characteristics:

- **Immediate execution**: They run automatically on a known host, or when the SDK method `RuntimeInit()` is called.
- **Single frame operations**: Boot scripts do not have access to `wait()` or `asyncWait()` commands, their execution is limited to a single frame.

Example boot script:

```js
// init.boot.mjs
log("Initializing...");
```

## Organizing Scripts

A single self-contained script file can be placed directly in the [CLEO directory](./cleo-directory.md).

Consider this example structure:

```
CLEO/
├─ CLEO_TEXT/
│  ├─ main.fxt
├─ folderA/
│  ├─ text.fxt
│  ├─ index.js
├─ folderB/
│  ├─ test.fxt
│  ├─ test.js
├─ script1.js
├─ script2.cs
```

By default CLEO Redux loads all CS and JS files from the root of the CLEO directory and FXT files from the `CLEO_TEXT` folder. So it loads `script1.js`, `script2.cs`, and `main.fxt`.

### Script Directories (index.js/index.ts)

Complex JS/TS scripts having a lot of dependencies (imported files, [FXT](./using-fxt.md) dictionaries) can be organized in folders. CLEO Redux scans the subdirectories of the [CLEO directory](./cleo-directory.md) and finds directories with either an `index.js`/`index.ts` file or a `mod.json` manifest file.

When using `index.js` or `index.ts` as the entry point, CLEO Redux runs this file and also loads all FXT files from the same directory. In the example above, CLEO loads `index.js` and `text.fxt` located in the `folderA` and skips `folderB` as there is no `index.js` file.

> CLEO_TEXT, CLEO_PLUGINS, and .config directories are exempt from this rule and are reserved for other purposes.

### Using mod.json manifest

> This feature is available since CLEO Redux v1.5.0.

Alternatively, you can use a `mod.json` file to configure your script directory. This allows you to:

- Specify custom metadata (name, description, version, etc.)
- Declare [permissions](./permissions.md) without using tokens in the directory name
- Define multiple entry points (JavaScript/TypeScript only)

Here's an example using `mod.json`:

```
CLEO/
├─ my_mod/
│  ├─ mod.json
│  ├─ main.ts
│  ├─ utils.ts
│  ├─ text.fxt
├─ script1.js
```

With a `mod.json` file like:

```json
{
  "name": "My Script",
  "permissions": ["mem", "dll"],
  "entries": ["main.ts"]
}
```

Instead of naming the folder as `my_mod[mem][dll]`, you can use the `permissions` field in `mod.json`. The `entries` field specifies which files should be executed as entry points. If omitted, CLEO Redux defaults to `index.js` or `index.ts`.

#### Multiple entry points

You can specify multiple entry points or use wildcard patterns (JS/TS files only):

```json
{
  "name": "My Scripts",
  "entries": ["main.ts", "subscript.ts"]
}
```

Or with patterns:

```json
{
  "name": "My Scripts",
  "entries": ["*.ts", "plugins/**/*.ts"]
}
```

This will execute all `.ts` files in the root and all `.ts` files in the `plugins` and its subdirectories.


### Permission handling

When both directory name suffix and `mod.json` permissions are present, the directory name suffix takes precedence. For example, `my_mod[mem]` with `mod.json` specifying `["dll"]` will result in `mem` permission being granted.
