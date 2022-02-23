# Other Features

CLEO Redux puts focus on improving dev experience and make scripting process easier. 

## Integration with Visual Studio Code

See demo: https://youtu.be/jqz8_lGnG4g

VS Code has excellent JavaScript support out of the box and is highly customizable. CLEO Redux generates typings for all supported commands that you can use when writing JavaScript in VS Code. Add the following line in your `*.js` script to get the full autocomplete support:

For `GTA III` or `re3`:

```
/// <reference path=".config/gta3.d.ts" />
```

For `Vice City` or `reVC`

```
/// <reference path=".config/vc.d.ts" />
```

For `San Andreas`

```
/// <reference path=".config/sa.d.ts" />
```

This line instructs VS Code where to look for the commands definitions for the autocomplete feature. The `path` can be relative to the script file or be absolute. [Find out more information](https://www.typescriptlang.org/docs/handbook/triple-slash-directives.html#-reference-path-) on the official TypeScript portal.

## SCM Log

CLEO Redux has built-in support for tracking SCM instructions. To enable trace for executed commands open up `cleo.ini` and change `LogOpcodes` to 1. Note that it can greatly impact game performance due to frequent microdelays during writes to the log file. Use this option only for debugging purposes.

## Hot Reload

CLEO monitors active scripts and reloads them in game as they change

Demo: https://www.youtube.com/watch?v=WanLojClqFw

Adding a new script file in CLEO directory or deleting one while the game is running starts or stops the script automatically

Demo: https://www.youtube.com/watch?v=LAi2syrsxJg

Hot reload for CS scripts does not work when CLEO Redux runs alongside CLEO Library (e.g. in classic San Andreas).