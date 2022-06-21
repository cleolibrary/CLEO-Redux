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

## Organizing Scripts

A single self-contained script file can be placed directly in the [CLEO directory](./cleo-directory.md). 

Complex JS scripts having a lot of dependencies (imported files, [FXT](./using-fxt.md) dictionaries) can be organized in folders. CLEO Redux scans the subdirectories of the [CLEO directory](./cleo-directory.md) and checks if there is a file named `index.js`. If `index.js` is found, CLEO Redux runs it. It also loads all FXT files from the same directory. 

Let's have a look at the example structure: 

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
 
 After scanning subdirectories, CLEO loads `index.js` and `text.fxt` located in the `folderA` and skips `folderB` as there is no `index.js` file.

 > CLEO_TEXT, CLEO_PLUGINS, and .config are not considered as script directories.