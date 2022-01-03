# CLEO Redux

[![Discord](https://img.shields.io/discord/911487285990674473?style=for-the-badge)](https://discord.gg/d5dZSfgBZr) 
[![YouTube Channel](https://img.shields.io/badge/YouTube-Channel-FF0000?style=for-the-badge)](https://www.youtube.com/playlist?list=PLNxQuEFtVkeizoLEQiok7qzr1f0mcwfFb)


## Getting Started

### What is CLEO Redux?

CLEO Redux is a scripting runtime for the GTA 3D era games. It is a proud member of the CLEO family and provides familiar experience to anyone who used CLEO Library for the classic GTA San Andreas or its re-implementations for other games. The main goal of CLEO is to provide a way to easily customize the game with countless user-made scripts.

If you're new to CLEO visit the [official website](https://cleo.li/) to find more information about it.

### Supported Languages

CLEO Redux supports compiled binary scripts (`*.cs`) in the native SCM format and plain text scripts (`*.js`) written in JavaScript.

CLEO Redux targets JavaScript as the primary language for custom scripts. JavaScript is a popular programming language with rich ecosystem and plenty of available information. It's free from SCM language limits and pitfalls such as lack of support for functions, arrays, or the low number of variables.

JavaScript is enabled by default. To disable it open up `CLEO\.config\cleo.ini` and change `AllowJs` to `0`.

### Supported Releases

Classic:

- GTA III 1.0
- GTA Vice City 1.0
- GTA San Andreas 1.0 (only with [CLEO 4.4](https://github.com/cleolibrary/CLEO4))

Remasters:

- San Andreas: The Definitive Edition 1.0.0.14296, 1.0.0.14388, v1.0.0.14718 (Title Update 1.03) (see [Compatibility details](#compatibility-with-the-trilogy-the-definitive-edition))

Other:

- re3 (see [Compatibility details](#compatibility-with-re3-and-revc))
- reVC (see [Compatibility details](#compatibility-with-re3-and-revc))

CLEO Redux only supports the PC version of each game.

For the complete reference on supported features refer to this page: https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix

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

If you run San Andreas: The Definitive Edition:

- Download and install [Ultimate ASI Loader x64](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest/version.zip) by ThirteenAG (place `version.dll` to the `GTA San Andreas - Definitive Edition\Gameface\Binaries\Win64` directory)
- Copy `cleo_redux64.asi` to the same directory.

For all other games:

- Copy `cleo_redux.asi` to the game directory.

- Run the game

Note: CLEO Redux does not alter any game files. It exploits the fact that the game natively loads `.asi` files as addons to the Miles Sound System library. No extra software is required.

You should see the words "CLEO Redux" and the current version in the bottom-right corner of the game menu (except in San Andreas: The Definitive Edition).

### First time setup

There could be a noticeable lag during the first game run as CLEO Redux downloads the files necessary for [JavaScript support](#javascript-support). It won't happen on subsequent runs.

Also a new folder named `CLEO` should appear in the game directory\*. This is the primary location for all CLEO scripts, plugins and configs.

\*If CLEO fails to create new files in the game directory due to the lack of write permissions, it fallbacks to using alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`. `cleo_redux.log` and the `CLEO` directory can be found there.

### Compatibility with re3 and reVC

CLEO Redux only supports "Windows D3D9 MSS 32bit" version of `re3` or `reVC`.

When running on `re3` and `reVC` make sure the game directory contains the file `re3.pdb` (for **re3**) or `reVC.pdb` (for **reVC**). Due to the dynamic nature of memory addresses in those implementations CLEO Redux relies on debug information stored in the PDB file to correctly locate itself.

### Compatibility with The Trilogy: The Definitive Edition

At the moment CLEO Redux only supports San Andreas: The Definitive Edition `1.0.0.14296`, `1.0.0.14388`, `v1.0.0.14718` (Title Update 1.03). There are some key differences from other games:

- Ultimate ASI Loader by ThirteenAG is required, see [Installation](#installation) notes
- there is no CLEO version displaying in the main menu
- function `showTextBox` does not work in JS scripts
- opcodes for custom commands are different, only a few are supported:

  - 0C00 [IS_KEY_PRESSED](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C00)
  - 0C01 [INT_ADD](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C01)
  - 0C02 [INT_SUB](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C02)
  - 0C03 [INT_MUL](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C03)
  - 0C04 [INT_DIV](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C04)
  - 0C05 [TERMINATE_THIS_CUSTOM_SCRIPT](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C05)
  - 0C06 [WRITE_MEMORY](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C06)
  - 0C07 [READ_MEMORY](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C07)

- Sanny Builder does not support these new opcodes out-of-the-box yet. To enable new opcodes in your CS scripts add the following lines on top of your script:

```
{$O 0C00=1,  is_key_pressed %1d% }
{$O 0C01=3,%3d% = %1d% + %2d% }
{$O 0C02=3,%3d% = %1d% - %2d% }
{$O 0C03=3,%3d% = %1d% * %2d% }
{$O 0C04=3,%3d% = %1d% / %2d% }
{$O 0C05=0,terminate_this_custom_script }
{$O 0C06=5,write_memory %1d% size %2d% value %3d% virtual_protect %4d% ib %5d% }
{$O 0C07=5,%5d% = read_memory %1d% size %2d% virtual_protect %3d% ib %4d% }
```

Use SA Mobile mode to compile CLEO scripts for San Andreas: The Definitive Edition.

For many people running their game with CLEO Redux installed results in the immediate crash. It happens if there is no write permissions in the current directory (`Win64`). To remediate this issue CLEO will fallback to using alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`. `cleo_redux.log` and the `CLEO` directory can be found there. See also the [troubleshooting guide](TROUBLESHOOTING.md).

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

## Custom Scripts

### Adding a new script

Generally a script file should just be copied to the `CLEO` directory. Some scripts may require extra steps for installation. In case of any issues check the script documentation or ask its author.

### Removing the script

Delete the script file from `CLEO` directory. Some scripts may require extra steps for undoing the installation. In case of any issues check the script documentation or ask its author.

### Custom Commands

Note: the following commands are for classic games only. For San Andreas: The Definitive Edition [check this information](#compatibility-with-the-trilogy-the-definitive-edition).

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

### Writing CS scripts

Use [Sanny Builder 3](https://sannybuilder.com) in GTA III, GTA VC or GTA SA edit modes respectively. Use SA Mobile mode to compile CLEO scripts for San Andreas: The Definitive Edition. Check out [this page](https://cleo.li/scripts.html) for more information.

### Writing JS scripts

Use VS Code (recommended) or any editor of your choice. Create a new file with `.js` extension and put it in the CLEO folder. See [JavaScript support](#javascript-support) for extra information.

Note: The runtime supports scripts in [ECMAScript 5.1 standard](https://262.ecma-international.org/5.1). It means you won't be able to use the most recent JavaScript features out of the box, however you can use any transpiler, such as [Babel](https://babeljs.io/) or [TypeScript](https://www.typescriptlang.org/), to downlevel unsupported ES6+ code to ES5.

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

## JavaScript Support

### Prerequisites

When JavaScript is enabled CLEO Redux needs commands definitions from https://library.sannybuilder.com/. On the first run CLEO tries to download them and put into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download a required file (see the table below) and place it in the `CLEO/.config` directory.

| Game | File | Minumum Required Version |
| --- | --- | --- | 
| GTA III, re3 | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json) | `0.200`
| GTA VC, reVC | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json) | `0.201`
| GTA San Andreas (Classic) 1.0 | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json) | `0.202`
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json) | `0.204`

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

### Custom Bindings

- `GAME` - current game id. Possible values: `gta3`, `vc`, `re3`, `reVC`, `sa`, `sa_unreal`

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

### SCM Log

CLEO Redux has built-in support for tracking SCM instructions. To enable trace for executed commands open up `cleo.ini` and change `LogOpcodes` to 1. Note that it can greatly impact game performance due to frequent microdelays during writes to the log file. Use this option only for debugging purposes.

### Hot Reload

CLEO monitors active scripts and reloads them in game as they change

Demo: https://www.youtube.com/watch?v=WanLojClqFw

Adding a new script file in CLEO directory or deleting one while the game is running starts or stops the script automatically

Demo: https://www.youtube.com/watch?v=LAi2syrsxJg

Hot reload for CS scripts does not work when CLEO Redux runs alongside CLEO Library (e.g. in classic San Andreas).

## License

CLEO Redux is available under the [end-user license agreement](./LICENSE.txt)
