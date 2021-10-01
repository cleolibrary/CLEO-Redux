# CLEO Redux

## Getting Started

### What is CLEO Redux?

CLEO Redux is a scripting runtime for GTA III and GTA Vice City in a form of an ASI library that the game can natively load. It's a member of the CLEO family and provides familiar experience to anyone who used CLEO Library for GTA San Andreas or its re-implementations for other games. The main goal of CLEO is to provide a way to easily customize the game with countless user-made scripts.

If you're new to CLEO visit the [official website](https://cleo.li/) to find more information on it.

### Supported Releases

- GTA III v1.0
- GTA Vice City v1.0
- re3
- reVC

## Installation

- Copy `cleo.asi` to the game directory.
- Run the game

Note: CLEO Redux does not alter any game files.

### First time setup

There could be a noticeable lag during the first game run as CLEO Redux downloads the files necessary for JavaScript support. It won't happen on subsequent runs.

Also a new folder named `CLEO` should appear in the game directory. This is the primary location for all CLEO scripts, plugins and configs.

### Compatibility with re3 and reVC

CLEO Redux only supports "Windows D3D9 MSS 32bit" version of re3 or reVC.

When running on `re3` and `reVC` make sure the game directory contains the file `re3.pdb` (for **re3**) or `reVC.pdb` (for **reVC**). Due to the dynamic nature of memory addresses in those implementations CLEO Redux relies on debug information stored in the PDB file to correctly locate itself.

### Uninstallation

- Delete `cleo.asi`.
- Delete the `CLEO` folder (optional).
- Delete the `cleo.log` (optional)

## Configuration

CLEO Redux exposes some of the configurable settings in the file `CLEO\.config\cleo.ini`.

### General Configuration

- `AllowJS` - when set to `1` CLEO loads and executes `*.js` files located in the CLEO directory. Enabled by default.
- `CheckUpdates` - when set to `1` CLEO check if there is a new update available for download during the game startup. Enabled by default.
- `LogOpcodes` - when set to `1` CLEO logs all executed opcodes in custom scripts. This log is part of the `cleo.log` file that can be found in the game directory.
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

CLEO logs important events and errors in the `cleo.log` file located in the game directory. This file gets overwritten on each game run. If you experience any issue when using CLEO Redux, start investigating the root cause from the file.

## Custom Scripts

### Adding a new script

Generally a script file should just be copied to the `CLEO` directory. Some scripts may require extra steps for installation. In case of any issues check the script documentation or ask its author.

### Removing the script

Delete the script file from `CLEO` directory. Some scripts may require extra steps for undoing the installation. In case of any issues check the script documentation or ask its author.

### Supported Languages

CLEO Redux supports compiled binary scripts (`*.cs`) in the native SCM format and plain text scripts (`*.js`) written in JavaScript.

CLEO Redux targets JavaScript as the primary language for custom scripts. JavaScript is a popular programming language with rich ecosystem and plenty of available information. It's free from SCM language limits and pitfalls such as lack of support for functions, arrays, or the low number of variables.

JavaScript is enabled by default. To disable it open up `CLEO\.config\cleo.ini` and change `AllowJS` to `0`.

### Custom Commands

- 0A93
  [TERMINATE_THIS_CUSTOM_SCRIPT](https://library.sannybuilder.com/#/sa/CLEO/0A93)
- 0AB0 [IS_KEY_PRESSED](https://library.sannybuilder.com/#/sa/CLEO/0AB0)
- 0A8D [READ_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8D) (**UNSAFE** - requires `mem` permission)
- 0A8C [WRITE_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8C) (**UNSAFE** - requires `mem` permission)

### Writing CS scripts

Use [Sanny Builder 3.8.0](https://sannybuilder.com) in GTA III or GTA VC edit modes respectively. Check out [this page](https://cleo.li/scripts.html) for more information.

### Writing JS scripts

Use VS Code (recommended) or any editor of your choice. Create a new file with `.js` extension and put it in the CLEO folder.

Note: The runtime supports scripts in [ECMAScript 5.1 standard](https://262.ecma-international.org/5.1). It means you won't be able to use the most recent JavaScript features out of the box, however you can use any traspiler, such as [Babel](https://babeljs.io/) or [TypeScript](https://www.typescriptlang.org/), to downlevel unsupported ES6+ code to ES5.

### Integration with Visual Studio Code

See demo: https://youtu.be/jqz8_lGnG4g

CLEO Redux generates typings for all supported commands that you can use when writing JavaScript in VS Code. Add the two following lines in your `*.js` script to get the full autocomplete support:

```
/// <reference no-default-lib="true"/>
/// <reference path=".config/gta3.d.ts" /> // or vc.d.ts
```

The first line excludes standard JavaScript API from autocomplete as it's not supported in the CLEO runtime.

The second line instructs VS Code where to look for the commands definitions for the autocomplete feature. The `path` can be relative to the script file or be absolute. [Find out more information](https://www.typescriptlang.org/docs/handbook/triple-slash-directives.html#-reference-path-) on the official TypeScript portal.

## JavaScript Support

### Prerequisites

When JavaScript is enabled CLEO Redux needs commands definitions from https://library.sannybuilder.com/. On the first run CLEO would try to download the necessary files and put them into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download `gta3.json` or `vc.json` from the [library's repo](https://github.com/sannybuilder/library) and put them to the `CLEO/.config` directory.

### Script Lifecycle

A file with the JavaScript code should have the \*.js extension and contain known instructions as described below. The script may have no instructions (the empty script). It runs as soon as the the new game starts or a save file is loaded.

The script terminates automatically when the last instruction has been executed. The runtime also terminates stuck scripts to prevent the game from freezing. The stuck script is the one that took more than 2 seconds to run since the last wait command. If that happened, check out your loops, some of the are missing the wait command.

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

CLEO Redux supports all in-game commands (opcodes) in the class form as defined in Sanny Builder Library. Keywords and custom extensions are not supported.

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

### Custom Bindings

- `GAME` - current game id. Possible values: `gta3`, `vc`, `re3`, `reVC`

```js
if (GAME === "gta3") {
  showTextBox("This is GTA III");
}
if (GAME === "vc") {
  showTextBox("This is Vice City");
}
```

- `log(...values)` - prints `{values}` to the cleo.log

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

- `isKeyPressed(vk_id)` - returns `true` if the key with the [code](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) `{vk_id}` is pressed. Deprecated since 0.5.2, use [Pad.isKeyPressed](https://library.sannybuilder.com/#/gta3/CLEO/0AB0) instead.

```js
if (isKeyPressed(0x74)) {
  log("F5 is pressed");
}
```

## Dev Features

### SCM Log

CLEO Redux has built-in support for tracking SCM instructions. To enable trace for executed commands open up cleo.ini and change `LogOpcodes` to 1.

### Hot Reload

CLEO monitors active scripts and reloads them in game as they change

Demo: https://www.youtube.com/watch?v=WanLojClqFw.

Adding a new script file in CLEO directory or deleting one while the game is running starts or stops the script automatically

Demo: https://www.youtube.com/watch?v=LAi2syrsxJg