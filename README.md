# CLEO Redux

[![Discord](https://img.shields.io/discord/911487285990674473?style=for-the-badge)](https://discord.gg/d5dZSfgBZr)
[![YouTube Channel](https://img.shields.io/badge/YouTube-Channel-FF0000?style=for-the-badge)](https://www.youtube.com/playlist?list=PLNxQuEFtVkeizoLEQiok7qzr1f0mcwfFb)

- [Getting Started](#getting-started)
  - [What is CLEO Redux?](#what-is-cleo-redux)
  - [Supported Languages](#supported-languages)
  - [Supported Releases](#supported-releases)
  - [Relation to CLEO Library](#relation-to-cleo-library)
    - [Running CLEO Redux as a standalone software](#running-cleo-redux-as-a-standalone-software)
    - [Running CLEO Redux as an addon to CLEO library](#running-cleo-redux-as-an-addon-to-cleo-library)
- [Installation](#installation)
  - [First time setup](#first-time-setup)
  - [Compatibility with re3 and reVC](#compatibility-with-re3-and-revc)
  - [Compatibility with The Trilogy: The Definitive Edition](#compatibility-with-the-trilogy-the-definitive-edition)
  - [Uninstallation](#uninstallation)
- [Configuration](#configuration)
  - [General Configuration](#general-configuration)
  - [Permissions](#permissions)
    - [All](#all)
    - [Lax](#lax)
    - [Strict](#strict)
    - [None](#none)
- [Log](#log)
- [Custom Scripts](#custom-scripts)
  - [Adding a new script](#adding-a-new-script)
  - [Removing the script](#removing-the-script)
  - [Custom Commands](#custom-commands)
  - [Writing CS scripts](#writing-cs-scripts)
  - [Writing JS scripts](#writing-js-scripts)
- [JavaScript Support](#javascript-support)
  - [Prerequisites](#prerequisites)
  - [Script Lifecycle](#script-lifecycle)
  - [Native Commands](#native-commands)
    - [Class ScriptObject vs Object](#class-scriptobject-vs-object)
    - [Class Math](#class-math)
    - [Fluent Interface](#fluent-interface)
    - [Examples](#examples)
  - [Imports](#imports)
  - [Custom Bindings](#custom-bindings)
  - [Deprecated](#deprecated)
- [Custom Text](#custom-text)
- [Dev Features](#dev-features)
  - [Integration with Visual Studio Code](#integration-with-visual-studio-code)
  - [SCM Log](#scm-log)
  - [Hot Reload](#hot-reload)
  - [SDK](#sdk)
- [License](#license)

## Getting Started

### What is CLEO Redux?

CLEO Redux is a scripting runtime for the GTA 3D era games. It is a proud member of the CLEO family and provides familiar experience to anyone who used CLEO Library for the classic GTA San Andreas or its re-implementations for other games. The main goal of CLEO is to provide a way to easily customize the game with countless user-made scripts.

If you're new to CLEO visit the [official website](https://cleo.li/) to find more information about it.

### Supported Languages

CLEO Redux supports compiled binary scripts (`*.cs`) in the native SCM format and plain text scripts (`*.js`) written in JavaScript.

CLEO Redux targets JavaScript as the primary language for custom scripts. JavaScript is a popular programming language with rich ecosystem and plenty of available information. It's free from SCM language limits and pitfalls such as lack of support for functions, arrays, or the low number of variables.

### Supported Releases

Classic:

- GTA III 1.0
- GTA Vice City 1.0
- GTA San Andreas 1.0 (only with [CLEO 4.4](https://github.com/cleolibrary/CLEO4))

Remasters (The Trilogy):

- GTA III 1.0.0.14718
- GTA Vice City 1.0.0.14718
- San Andreas 1.0.0.14296, 1.0.0.14388, 1.0.0.14718 (Title Update 1.03)

See [The Definitive Edition FAQ](the-definitive-edition-faq.md) for the details.

Other:

- re3 (see [Compatibility details](#compatibility-with-re3-and-revc))
- reVC (see [Compatibility details](#compatibility-with-re3-and-revc))

CLEO Redux only supports the PC version of each game.

For the complete reference on supported features [refer to this page](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix). Also there are known limitations [listed here](unsupported.md).

### Relation to CLEO Library

CLEO is a common name for the custom libraries designed and created for GTA III, Vice City or San Andreas. Each version can be found and downloaded [here](https://cleo.li/download.html). CLEO Redux is _another_ CLEO implementation made from scratch with a few distinctive features, such as single code base for all games, or support for JavaScript code.

At the moment CLEO Redux can not be considered as a complete replacement for CLEO Library due to the lack of support for many widely used CLEO commands. To solve this issue and get the best out of the two libraries, CLEO Redux supports two different usage strategies.

CLEO Redux can run as a standalone software, or as an addon to CLEO Library. In the first case your game directory would only contain `cleo_redux.asi` (or `cleo_redux64.asi`) file. In the second case, your game directory would have both `cleo.asi` (or `III.CLEO.asi` or `VC.CLEO.asi`) and `cleo_redux.asi` (or `cleo_redux64.asi`).

#### Running CLEO Redux as a standalone software

As a standalone software CLEO Redux runs compiled scripts and JavaScript and provides access to all native script commands. It also provides a limited set of [custom commands](#custom-commands) backward-compatible to CLEO Library. Existing CLEO scripts may not work if they use custom commands (for example from a third-party plugin) not supported by CLEO Redux.

This mode does not work in the classic GTA San Andreas.

#### Running CLEO Redux as an addon to CLEO library

As an addon CLEO Redux runs alongside CLEO Library delegating it all the care for custom scripts. It means all custom scripts and plugins made for CLEO Library will continue working exactly the same. CLEO Redux only manages JS scripts. All custom commands become available to JavaScript runtime, which means you can use commands currently not implemented natively in CLEO Redux, for example for [files](https://library.sannybuilder.com/#/gta3/classes/File) or [dynamic libraries](https://library.sannybuilder.com/#/gta3/classes/DynamicLibrary).

This mode works in classic GTA III, GTA Vice City and GTA San Andreas where CLEO Library exists.

## Installation

If you run The Definitive Edition (GTA III, VC, or SA):

- [Follow this guide](the-definitive-edition-faq.md#how-to-install-cleo-redux-in-the-definitive-edition).

For all other games:

- Copy `cleo_redux.asi` to the game directory.

- Run the game

Plugins for CLEO Redux (`*.cleo`) should be copied to the `CLEO\CLEO_PLUGINS` directory.

Note: CLEO Redux does not alter any game files. It exploits the fact that the game natively loads `.asi` files as addons to the Miles Sound System library. No extra software is required.

### First time setup

There could be a noticeable lag during the first game run as CLEO Redux downloads the files necessary for [JavaScript support](#javascript-support). It won't happen on subsequent runs.

Also a new folder named `CLEO` should appear in the game directory\*. This is the primary location for all CLEO scripts, plugins and configs.

\*If CLEO fails to create new files in the game directory due to the lack of write permissions, it fallbacks to using alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`. `cleo_redux.log` and the `CLEO` directory can be found there.

### Compatibility with re3 and reVC

CLEO Redux only supports "Windows D3D9 MSS 32bit" version of `re3` or `reVC`.

When running on `re3` and `reVC` make sure the game directory contains the file `re3.pdb` (for **re3**) or `reVC.pdb` (for **reVC**). Due to the dynamic nature of memory addresses in those implementations CLEO Redux relies on debug information stored in the PDB file to correctly locate itself.

### Compatibility with The Trilogy: The Definitive Edition

Check [The Definitive Edition FAQ](the-definitive-edition-faq.md)

### Uninstallation

- Delete `cleo_redux.asi` (or `cleo_redux64.asi`).
- Delete the `CLEO` folder (optional).
- Delete the `cleo_redux.log` (optional)

## Configuration

CLEO Redux exposes some of the configurable settings in the file `CLEO\.config\cleo.ini`.

### General Configuration

- `AllowCs` - when set to `1` CLEO loads and executes `*.cs` files located in the CLEO directory. Enabled by default.
- `AllowJs` - when set to `1` CLEO loads and executes `*.js` files located in the CLEO directory. Enabled by default.
- `AllowFxt` - when set to `1` CLEO loads and [uses](#custom-text) `*.fxt` files located in the CLEO\CLEO_TEXT directory. Enabled by default.
- `CheckUpdates` - when set to `1` CLEO check if there is a new update available for download during the game startup. Enabled by default.
- `LogOpcodes` - when set to `1` CLEO logs all executed opcodes in custom scripts. This log is part of the `cleo_redux.log` file (see [Log](#log))
- `PermissionLevel` - sets the permission level for unsafe operations (see below). Default is `Lax`.

### Permissions

CLEO Redux acknowledges some [custom commands](#custom-commands) (opcodes) as unsafe and requires the user to decide whether to run them or not. Raw access to the process memory, loading external libraries or making network requests can be harmful and produce undesired side-effects. Hence CLEO introduces permission levels for running the unsafe code.

There are four available levels:

#### All

Any unsafe operation is allowed. Use this only when you trust the scripts you run.

#### Lax

This is the default permission level.

No unsafe operation is allowed unless the script explicitly requests it. Currently to request a permission, the name of the script file must include the permissions tokens wrapped in square brackets.

For example, if the script wants to access the memory via `0A8D READ_MEMORY` the file name must contain `[mem]`, e.g. `cool-spawner[mem].cs`. If the file is named differently CLEO rejects `0A8D` and the script crashes.

#### Strict

No unsafe operation is allowed unless the script explicitly requests it (see `"Lax"`) and the CLEO config file permits this type of operation under the `Permissions` section.

Permissions section in `cleo.ini` allows to enable or disable groups of unsafe operations by using the permission tokens. For example,

```ini
mem=0
```

disables all memory-related opcodes even if the script has the `[mem]` token in the file name.

Note: `Permissions` section in the `cleo.ini` only takes effect when `PermissionLevel` is `Strict`.

#### None

No unsafe operation is allowed.

## Log

CLEO logs important events and errors in the `cleo_redux.log` file located in the game directory (or `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`, see [First Time Setup](#first-time-setup) note). This file gets overwritten on each game run. If you experience any issue when using CLEO Redux, start investigating the root cause from this file.

To stream events in your terminal while testing a script, run:

```
tail -f cleo_redux.log
```

`tail` is a unix command so a compatible environment is needed (for example Git Bash).

## Custom Scripts

### Adding a new script

Generally a script file should just be copied to the `CLEO` directory. Some scripts may require extra steps for installation. In case of any issues check the script documentation or ask its author.

### Removing the script

Delete the script file from `CLEO` directory. Some scripts may require extra steps for undoing the installation. In case of any issues check the script documentation or ask its author.

### Custom Commands

Note: the following commands are for classic games only. For The Definitive Edition [check this information](the-definitive-edition-faq.md#can-i-use-cleo-opcodes).

- 0A8C [WRITE_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8C) (**UNSAFE** - requires `mem` permission)
- 0A8D [READ_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8D) (**UNSAFE** - requires `mem` permission)
- 0A8E [INT_ADD](https://library.sannybuilder.com/#/gta3/CLEO/0A8E)
- 0A8F [INT_SUB](https://library.sannybuilder.com/#/gta3/CLEO/0A8F)
- 0A90 [INT_MUL](https://library.sannybuilder.com/#/gta3/CLEO/0A90)
- 0A91 [INT_DIV](https://library.sannybuilder.com/#/gta3/CLEO/0A91)
- 0A93 [TERMINATE_THIS_CUSTOM_SCRIPT](https://library.sannybuilder.com/#/gta3/CLEO/0A93)
- 0AA5 [CALL_FUNCTION](https://library.sannybuilder.com/#/gta3/CLEO/0AA5) (**UNSAFE** - requires `mem` permission)
- 0AA6 [CALL_FUNCTION_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA6) (**UNSAFE** - requires `mem` permission)
- 0AA7 [CALL_METHOD](https://library.sannybuilder.com/#/gta3/CLEO/0AA7) (**UNSAFE** - requires `mem` permission)
- 0AA8 [CALL_METHOD_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA8) (**UNSAFE** - requires `mem` permission)
- 0AB0 [IS_KEY_PRESSED](https://library.sannybuilder.com/#/gta3/CLEO/0AB0)

This list might not be complete as there are custom plugins with extra commands (see [Using SDK](./using-sdk.md)). Refer to [Sanny Builder Library](https://library.sannybuilder.com) for the complete list of available commands for each game.

### Writing CS scripts

Use [Sanny Builder 3](https://sannybuilder.com) in GTA III, GTA VC or GTA SA edit modes respectively. Check out [this page](https://cleo.li/scripts.html) for more information.

[Check the FAQ](the-definitive-edition-faq.md#how-do-i-compile-cleo-scripts-with-sanny-builder) for the information on CS support in the remastered games.

### Writing JS scripts

Use VS Code (recommended) or any editor of your choice. Create a new file with `.js` extension and put it in the CLEO folder. See [JavaScript support](#javascript-support) for extra information.

The runtime supports scripts in [ECMAScript 2020 standard](https://262.ecma-international.org/11.0/). It means you are able to use the most recent JavaScript features out of the box, such as imports, classes, arrow functions, etc.

CLEO Redux is not Node.js. Don't expect sockets, file system operations or other Node.js features to be available here.

## JavaScript Support

### Prerequisites

When JavaScript is enabled CLEO Redux needs commands definitions from https://library.sannybuilder.com/. On the first run CLEO tries to download them and put into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download a required file (see the table below) and place it in the `CLEO/.config` directory.

| Game                                | File                                                                                                 | Minumum Required Version |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| GTA III, re3                        | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json)                      | `0.208`                  |
| GTA VC, reVC                        | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json)                            | `0.210`                  |
| GTA San Andreas (Classic) 1.0       | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json)                            | `0.210`                  |
| GTA III: The Definitive Edition     | [gta3_unreal.json](https://github.com/sannybuilder/library/blob/master/gta3_unreal/gta3_unreal.json) | `0.210`                  |
| Vice City: The Definitive Edition   | [vc_unreal.json](https://github.com/sannybuilder/library/blob/master/vc_unreal/vc_unreal.json)       | `0.212`                  |
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json)       | `0.216`                  |

### Script Lifecycle

A file with the JavaScript code should have the `*.js` extension and contain known instructions as described below. The script may have no instructions (the empty script). It runs as soon as the the new game starts or a save file is loaded.

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

### Native Commands

CLEO Redux supports all in-game commands (opcodes) in the class form as defined in Sanny Builder Library.

#### Class ScriptObject vs Object

Sanny Builder Library defines a static class `Object` to group commands allowing to create and manipulate 3D objects in-game. At the same time JavaScript has the [native Object class](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object) with its own methods.

To avoid mixing the two, CLEO Redux uses `ScriptObject` class instead of the Library's `Object` with [the same interface](https://library.sannybuilder.com/#/gta3/classes/Object).

```js
var x = ScriptObject.Create(modelId, x, y, z); // opcode 0107, creates a new object in the game

var x = Object.create(null); // native JavaScript code, creates a new object in JS memory
```

#### Class Math

Similarly to the `Object` class (see above), both the Library and native JavaScript runtime use the same name for mathematical utilities: class `Math`. In this case however, the decision was made to keep both native and script methods under the same class name.

The priority was given to the native code in those cases where it provides the same functionality as script opcodes. For example, to calculate the absolute value of a number, use native [Math.abs](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/abs), not [Math.Abs](https://library.sannybuilder.com/#/gta3?q=%22abs%22). See [Using Math](using-math.md) for more detailed information.

#### Fluent Interface

Methods on constructible entities (such as `Player`, `Car`, `Char` -- any entities created via a constructor method) support chaining (also known as Fluent Interface). It allows to write code like this:

```js
var p = new Player(0);

p.giveWeapon(2, 100)
  .setHealth(5)
  .setCurrentWeapon(2)
  .getChar()
  .setCoordinates(1144, -600, 14)
  .setBleeding(true);
```

See demo: https://www.youtube.com/watch?v=LLgJ0fWbklg.

Destructor methods interrupt the chain. E.g. given the code:

`Char.Create(0, 0, 0, 0, 0).setCoordinates(0, 0, 0).delete()`

the chain can not continue after delete method as the character gets removed and its handle is not longer valid.

#### Examples

If you were to change the time of day to 22:00, run the following command

```js
Clock.SetTimeOfDay(22, 0);
```

This would be the equivalent of the opcode `00C0: set_time_of_day 22 0` or `SET_TIME_OF_DAY 22 0` in SCM code.

Change player's money

```js
var player = new Player(0);
player.addScore(1000);
```

`new Player(0);` is the equivalent of getting the player's index using `$PLAYER_CHAR` global variable in Sanny Builder.

Create a dynamic entity (e.g. a car)

```js
// request a model
Streaming.RequestModel(101);

// wait while the game loads the model
while (!Streaming.HasModelLoaded(101)) {
  wait(250);
}

// create a car at the coordinates and store the handle
var infernus = Car.Create(101, 1234.0, 567.0, -100.0);
```

Variable `infernus` will contain a handle of the newly created car. It can be passed directly to any command receiving the `Car` handle

```js
// create a marker on the created car and store the marker handle
var blip = Blip.AddForCar(infernus);
```

The same variable infernus can be used to call the `Car`'s methods, for example, to explode the car

```js
infernus.explode();
```

This would be the equivalent to the opcode `020B: explode_car $infernus` or `EXPLODE_CAR $infernus` in SCM scripts.

Also check out the [example scripts](examples).

### Imports

You can import other script files in your code to make the code modular and share the common logic. The runtime supports the `import` statement as described in https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/import

To avoid running the included `.js` files as standalone scripts, either put them into a separate folder (e.g. `CLEO/includes/`) or use the extension `.mjs`.

```js
import func from "./other"; // imports default export from other.js or other.mjs located in the same directory

import { PedType } from "./includes/types"; // imports named export PedType from types.js or types.mjs located in the CLEO/includes directory

import data from "./vehicles.json"; // imports vehicles.json as a JavaScript value (an array, object).
```

Currently only import of `.js` (`.mjs`) and `.json` files is supported.

### Custom Bindings

The following variables and functions are only available in JavaScript code.

- `GAME` - current game id. Possible values: `gta3`, `vc`, `re3`, `reVC`, `sa`, `gta3_unreal`, `vc_unreal`, `sa_unreal`

```js
if (GAME === "gta3") {
  showTextBox("This is GTA III");
}
if (GAME === "sa") {
  showTextBox("This is San Andreas");
}
if (GAME === "sa_unreal") {
  showTextBox("This is San Andreas: The Definitive Edition");
}
```

- `ONMISSION` - global flag controlling whether the player is on a mission now.

```js
if (!ONMISSION) {
  showTextBox("Not on a mission. Setting ONMISSION to true");
  ONMISSION = true;
}
```

- `TIMERA` and `TIMERB` - two auto-incrementing timers useful for measuring time intervals.

```js
while (true) {
  TIMERA = 0;
  // wait 1000 ms
  while (TIMERA < 1000) {
    wait(0);
  }
  showTextBox("1 second passed");
}
```

- `__dirname` - an absolute path to the directory with the current file

- `log(...values)` - prints comma-separated `{values}` to the `cleo_redux.log`

```js
var x = 1;
log("value of x is ", x);
```

- `wait(timeInMs)` - pauses the script execution for at least `{timeInMs}` milliseconds

```js
while (true) {
  wait(1000);
  log("1 second passed");
}
```

- `showTextBox(text)` - displays `{text}` in the black rectangular box

```js
showTextBox("Hello, world!");
```

- `exit(reason?)` - terminates the script immediately. `exit` function accepts an optional string argument that will be added to the `cleo_redux.log`.

```js
exit("Script ended");
```

- family of static methods in the `Memory` class for manipulating different data types. See the [Memory guide](using-memory.md) for more information.

- `native(command_name, ...input_args)` - a low-level function to execute any in-game command using its name `{command_name}`

```js
native("SET_TIME_OF_DAY", 12, 30); // sets the time of day to 12:30
```

### Deprecated

Note: usage of the following commands is not recommended.

- `op(opcode_id, ...input_args)` - a low-level function to execute any in-game command with opcode `{opcode_id}`.

  For the commands that return a single value, the result is this value.

  For the commands that return multiple values, the result is an object where each key corresponds to a returned value. The key names match the output names given in the command definition

  For the conditional commands the result is the boolean value `true` or `false`

```js
op(0x00c0, 12, 30); // sets the time of day to 12:30
```

```js
var pos = op(0x0054, 0); // returns player 0 coordinates vector {x, y, z}
showTextBox("Player pos:", " x = ", pos.x, " y = ", pos.y, " z = ", pos.z);
```

```js
if (op(0x0248, 101)) {
  // checks the condition
  showTextBox("Model with id 101 has been loaded");
}
```

## Custom Text

CLEO Redux supports custom text content without the need to edit game files. See [this guide](using-fxt.md) for more information.

## Dev Features

### Integration with Visual Studio Code

See demo: https://youtu.be/jqz8_lGnG4g

CLEO Redux generates typings for all supported commands that you can use when writing JavaScript in VS Code. Add the following line in your `*.js` script to get the full autocomplete support:

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

### SCM Log

CLEO Redux has built-in support for tracking SCM instructions. To enable trace for executed commands open up `cleo.ini` and change `LogOpcodes` to 1. Note that it can greatly impact game performance due to frequent microdelays during writes to the log file. Use this option only for debugging purposes.

### Hot Reload

CLEO monitors active scripts and reloads them in game as they change

Demo: https://www.youtube.com/watch?v=WanLojClqFw

Adding a new script file in CLEO directory or deleting one while the game is running starts or stops the script automatically

Demo: https://www.youtube.com/watch?v=LAi2syrsxJg

Hot reload for CS scripts does not work when CLEO Redux runs alongside CLEO Library (e.g. in classic San Andreas).

### SDK

CLEO Redux provides a [C++ and Rust SDK](./plugins/SDK) for developing custom commands. Find more information in the [Using SDK](./using-sdk.md) guide.

## License

CLEO Redux is available under the [end-user license agreement](./LICENSE.txt)
