# Other Features

CLEO Redux puts focus on improving dev experience and make scripting process easier.

## Integration with Visual Studio Code

<iframe width="560" height="315" src="https://www.youtube.com/embed/jqz8_lGnG4g" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

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

For `Unknown` host

```
/// <reference path=".config/unknown.d.ts" />
```

This line instructs VS Code where to look for the commands definitions for the autocomplete feature. The `path` can be relative to the script file or be absolute. [Find out more information](https://www.typescriptlang.org/docs/handbook/triple-slash-directives.html#-reference-path-) on the official TypeScript portal.

## SCM Log

CLEO Redux has built-in support for basic tracing of SCM instructions. To trace opcodes in all running CS scripts open up [`cleo.ini`](./config.md) and change `LogOpcodes` to 1. Note that it can greatly impact game performance due to frequent microdelays during writes to the log file. Use this option only for debugging purposes.

In JavaScript code use `CLEO.debug.trace(true)` to trace all commands. Use `CLEO.debug.trace(false)` to turn it off.

## Hot Reload

CLEO monitors active scripts and reloads them in game as they change

<iframe width="560" height="315" src="https://www.youtube.com/embed/WanLojClqFw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Adding a new script file in the [CLEO directory](./cleo-directory.md) or deleting one while the game is running starts or stops the script automatically

<iframe width="560" height="315" src="https://www.youtube.com/embed/LAi2syrsxJg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Hot reload for CS scripts does not work when CLEO Redux runs alongside CLEO Library (e.g. in classic San Andreas).

## Main Menu Information

CLEO Redux displays the information such as the version and the amount of active scripts in the main menu of GTA III / Vice City and San Andreas. To disable this information set [`DisplayMenuInfo`](./config.md#general) to `0`.
