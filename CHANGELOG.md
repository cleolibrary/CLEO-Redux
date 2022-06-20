### 0.9.4 - May 12, 2022

- add support for custom file loaders allowing [import of various file formats](https://re.cleo.li/docs/en/imports.html)
- add [new bindings](https://re.cleo.li/docs/en/api.html) available in JS code: a static object `CLEO` and a constant `__filename`
- add new config option `DisplayMenuInfo` to control whether CLEO Redux should display the version information in the main menu (supported in GTA III/VC/SA)
- fix a conversion error in some commands when an integer number is given instead of a boolean

**SDK AND PLUGINS**

- when `RuntimeNextTick` is called with both arguments set to zero (`RuntimeNextTick(0, 0)`) CLEO calculates correct values for current_time and time_step as the time elapsed from the last call of `RuntimeInit` and the delta time between two ticks respectively
- add an option in the installer to download SilentPatch as a dependency of the ImGuiRedux plugin
- new methods `RegisterLoader`, `AllocMem`, `FreeMem` (see the guide)
- new file loaders for Text files (any host) and IDE files (GTA3, VC, SA)

**BREAKING CHANGES**

- configuration option `LogOpcodes` is no longer applied to JS scripts. To start tracing executed commands in a script use `CLEO.debug.trace(true)`. To disable tracing use `CLEO.debug.trace(false)`.
- `__dirname` is now `const` and can not be changed
- static methods have been excluded from [fluent interface](https://re.cleo.li/docs/en/fluent-interface.html) (can't be chained with other methods)

### 0.9.3 - Apr 22, 2022

- CLEO can be [embedded](https://re.cleo.li/docs/en/embedding.html) and run on unknown hosts via the self-hosted mode [See demo](https://www.youtube.com/watch?v=rk2LvDt7UkI)
- new installer that automatically downloads extra dependencies such as Ultimate ASI Loader and plugins (dylib, IniFiles, or ImGuiRedux)
- support for organizing scripts and its dependencies in sub-directories inside the CLEO folder. See https://re.cleo.li/docs/en/script-lifecycle.html#organizing-scripts
- automatically download the latest `enums.js` file from Sanny Builder Library along with the command definitions. You can import enums in JS with `import * as enums from './.config/enums';`
- memory access operations can run on an unknown host (previously they had a dependency on the `op` command which itself can only run in GTA games)
- `Memory.CallFunctionReturnFloat` and `Memory.CallMethodReturnFloat` are now available for 32-bit hosts. `CallFunctionReturnFloat` has been previously added for 64-bit hosts.

**SDK AND PLUGINS**

- SDK's method `ResolvePath` now resolves paths starting with `./` or `.\` relative to the script directory. You can use them in commands like `READ_INT_FROM_INI_FILE` or `LOAD_DYNAMIC_LIBRARY`
- new SDK methods `GetHostName`, `SetHostName`, `RuntimeInit`, `RuntimeNextTick`. SDK version is now 2.
- IniFiles plugin updated to 1.2: increased max length of the INI file path
- Dylib plugin updated to 1.1: increased max length of the DLL file path

**BREAKING CHANGES**

- delete previously deprecated command `op`. Use `native` instead.
- rename `GAME` variable to `HOST` (`GAME` is still available for use but it's recommended to update older scripts)

| Game                                | File                                                                                                 | Minimum Required Version |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| GTA III, re3                        | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json)                      | `0.218`                  |
| GTA VC, reVC                        | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json)                            | `0.220`                  |
| GTA San Andreas (Classic) 1.0       | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json)                            | `0.236`                  |
| GTA III: The Definitive Edition     | [gta3_unreal.json](https://github.com/sannybuilder/library/blob/master/gta3_unreal/gta3_unreal.json) | `0.213`                  |
| Vice City: The Definitive Edition   | [vc_unreal.json](https://github.com/sannybuilder/library/blob/master/vc_unreal/vc_unreal.json)       | `0.215`                  |
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json)       | `0.220`                  |

### 0.9.2 - Mar 04, 2022

- add support for The Definitive Edition Title Update 1.04 (GTA III DE 1.0.0.15284, VC DE 1.0.0.15399, SA DE 1.0.0.15483)
- fix an issue with string arguments in Memory call commands in GTA San Andreas (https://github.com/cleolibrary/CLEO-Redux/issues/36)
- fix an issue with scripts not working if the path to the game directory has square brackets `[`, `]`

### 0.9.1 - Feb 22, 2022

- add [SDK for developing custom commands](using-sdk.md) in C++ and Rust
- add support for fallible commands in JS (also known as `IF and SET` commands in SCM scripts), they return `undefined` when failing, e.g. `DynamicLibrary.Load` or `Char.IsInAnySearchlight`)
- two new plugins adding commands to work with DLL (`dylib.cleo`) and INI files (`IniFiles.cleo`) in all supported games
- add `__dirname` variable in JS scripts that resolves to the current file's directory
- add a new function [native](README.md#custom-bindings) that calls a scripting command by name (similar to `op`):

```ts
/** Executes a named command with the given arguments */
declare function native<T>(name: string, ...args: any[]): T;
```

```js
const lib = native("LOAD_DYNAMIC_LIBRARY", "test.dll");
```

- fix a rounding issue with floating-point numbers in GTA 3
- fix an issue with imports not working in JS when the CLEO folder is located in the AppData directory
- fix an issue with the `showTextBox` command in San Andreas displaying some garbage text
- fix a conversion error when the `showTextBox` command is given an integer argument
- fix an issue with scripts permissions not being validated for JS scripts
- fix an issue when the object returned as a result of some commands (`Object.GrabEntityOnRope()`, `Heli.GrabEntityOnWinch()` and like) did not have relevant fields wrapped in a class instance

**INSTALLATION STEPS**

https://github.com/cleolibrary/CLEO-Redux/blob/master/README.md#installation

**BREAKING CHANGES**

| Game                                | File                                                                                                 | Minimum Required Version |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| GTA III, re3                        | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json)                      | `0.208`                  |
| GTA VC, reVC                        | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json)                            | `0.210`                  |
| GTA San Andreas (Classic) 1.0       | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json)                            | `0.210`                  |
| GTA III: The Definitive Edition     | [gta3_unreal.json](https://github.com/sannybuilder/library/blob/master/gta3_unreal/gta3_unreal.json) | `0.210`                  |
| Vice City: The Definitive Edition   | [vc_unreal.json](https://github.com/sannybuilder/library/blob/master/vc_unreal/vc_unreal.json)       | `0.212`                  |
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json)       | `0.216`                  |

### 0.9.0 - Jan 23, 2022

- add support for JS scripts in **GTA III: The Definitive Edition (v1.0.0.14718)** and **Vice City: The Definitive Edition (v1.0.0.14718)** (some limitations apply, see [Feature support](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix) for the details)
- add support for modern ES6+ syntax (arrow functions, const/let, classes, more methods in the standard library, etc), see [Mines Drop script](examples/mines-drop.js) as an example
- add support for [importing other scripts and JSON files](README.md#Imports)

For 64-bit games (The Trilogy):

- you can now call game functions with floating-point arguments - thanks to @ThirteenAG.
- new command `Memory.CallFunctionReturnFloat` that is similar to `Memory.CallFunctionReturn` but is used for functions that return a floating-point number

```js
let x = Memory.FromFloat(123.456);
let y = Memory.FromFloat(456.555);
let groundZ = Memory.CallFunctionReturnFloat(0x100cc50, true, 2, x, y);
```

- new convenience method `Memory.Fn.X64Float` that can be used for functions that return a floating-point number:

```js
let CWorldFindGroundZForCoord = Memory.Fn.X64Float(0x100cc50, true);
let x = Memory.FromFloat(123.456);
let y = Memory.FromFloat(456.555);
let groundZ = CWorldFindGroundZForCoord(x, y);
```

### 0.8.6 - Jan 12, 2022

- add [CALL_FUNCTION](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C08) and [CALL_FUNCTION_RETURN](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C09) commands in San Andreas: The Definitive Edition
- add `Memory.Fn.X64` convenience methods for [calling functions from JavaScript on the x64 platform](using-memory-64.md#calling-foreign-functions)
- `showTextBox` now works in San Andreas: The Definitive Edition
- fix an issue with FxtStore object not showing in VS Code autocomplete
- fix an issue with text draw not working in GTA San Andreas
- fix an issue in CLEO dev builds causing the game crash on startup while checking for an update

#### BREAKING CHANGE

- minimum required version of `sa_unreal.json` is `0.209`

### 0.8.5 - Jan 1, 2022

- add support for [static FXT files](using-fxt.md#static-fxt-files) in `CLEO_TEXT` folder
- add support for [private FXT storage](using-fxt.md#fxtstore) in each JS script
- fix an issue when [scripts permissions](README.md#permissions) were not validated for CLEO scripts
- fix an issue when the game may crash on the script reload
- [custom CLEO opcodes](README.md#compatibility-with-the-trilogy-the-definitive-edition) (`0C00`-`0C07`) can now be used in the main.scm in San Andreas: DE

### 0.8.4 - Dec 17, 2021

- for San Andreas: The Definitive Edition:

  - new opcodes `0C06 WRITE_MEMORY` and `0C07 READ_MEMORY`, as well as corresponding JavaScript commands: `Memory.Write` and `Memory.Read`. [Read the guide](using-memory-64.md) for more information
  - fix an issue with opcodes `0C01`, `0C02`, `0C03`, `0C04` crashing the game

- for all games:
  - improve stability of JS scripts (https://github.com/cleolibrary/CLEO-Redux/issues/22)
  - fix an issue when scripts permissions were not validated for CLEO scripts

#### BREAKING CHANGES

CLEO Redux for San Andreas: The Definitive Edition now uses `sa_unreal.json` from https://github.com/sannybuilder/library.

| Game                                | Minimum Required Version |
| ----------------------------------- | ------------------------ |
| GTA III, re3                        | `0.200`                  |
| GTA VC, reVC                        | `0.201`                  |
| GTA San Andreas (Classic) 1.0       | `0.202`                  |
| San Andreas: The Definitive Edition | `0.204`                  |

### 0.8.3 - Dec 8, 2021

- fix a critical bug in CS scripts scheduler causing abnormal behavior (mostly resulting in slow execution) (https://github.com/cleolibrary/CLEO-Redux/issues/21)
- fix an issue making coronas created in CLEO scripts not render (https://github.com/cleolibrary/CLEO-Redux/issues/23)

### 0.8.2 - Dec 4, 2021

- CLEO now uses AppData directory if there is no write permissions in the current game directory (see [First Time Setup](README.md#first-time-setup) note)
- add fluent interface for methods on constructible entities. See demo: https://www.youtube.com/watch?v=LLgJ0fWbklg
- fix an issue when a script could run during game pause (when the game menu is active)

### 0.8.1 - Dec 1, 2021

- add support for San Andreas: The Definitive Edition v1.0.0.14718 (Title Update 1.03)

### 0.8.0 - Nov 25, 2021

- new 64-bit version of CLEO Redux (cleo_redux64.asi). It's intended to work only with remastered games.
- [initial support](README.md#compatibility-with-the-trilogy-the-definitive-edition) for San Andreas: The Definitive Edition v1.0.0.14296 and v1.0.0.14388
- fix an issue when scripts might not reload after loading a save file

#### KNOWN ISSUES:

- `showTextBox` function does not work in JavaScript in San Andreas: The Definitive Edition
- CLEO does not display its version in the main menu in San Andreas: The Definitive Edition

#### BREAKING CHANGES

- minimum required version of `gta3.json` is `0.100`
- minimum required version of `vc.json` is `0.145`
- minimum required version of `sa.json` is `0.175`

### 0.7.6 - Nov 18, 2021

- CLEO Redux now works on Windows 7

### 0.7.5 - Nov 13, 2021

- fix: some custom command could have unconventional arguments order (e.g. [0AA4 GET_DYNAMIC_LIBRARY_PROCEDURE](https://library.sannybuilder.com/#/sa/CLEO/0AA4))
- fix: "if and set" commands had incorrect definitions in \*.d.ts file

### 0.7.4 - Nov 11, 2021

- ignore mobile and console command definitions (fixes https://github.com/cleolibrary/CLEO-Redux/issues/6)

#### BREAKING CHANGE

- minimum required version of `vc.json` is `0.144`
- minimum required version of `sa.json` is `0.168`

### 0.7.3 - Nov 8, 2021

- ensure custom scripts have unique [in-game names](https://library.sannybuilder.com/#/vc/default/03A4) when the first 7 characters of their file names are the same (e.g. scripts in files `spawner_a.cs`, `spawner_b.cs`, `spawner_c.cs` would now have names `spawner`, `spawn01`, `spawn02` respectively)
- fix: internal address error could make a JS script execute a wrong instruction

#### BREAKING CHANGE

- minimum required version of `sa.json` is `0.167`

### 0.7.2 - Nov 4, 2021

- add `ONMISSION` variable that can be used to manipulate the global player's on a mission status

```js
if (!ONMISSION) {
  showTextBox("Not on a mission. Setting ONMISSION to true");
  ONMISSION = true;
}
```

#### BREAKING CHANGES

- using `new` operator on a static object (for which Sanny Builder Library does not define a constructor, e.g. `Audio` or `Hud`) now throws an error:

```js
var hud = new Hud(); // error: Hud is not constructable
```

- minimum required version of `sa.json` is `0.166`

### 0.7.1 - Nov 2, 2021

- new static function `Memory.Translate` to get memory address of a function or variable by its name (see [documentation](using-memory.md#finding-memory-addresses-in-re3-and-revc))
- new function `exit` to terminate the script early

### 0.7.0 - Oct 30, 2021

- CLEO Redux can now work as an extension to CLEO Library (see [Relation to CLEO Library](README.md#relation-to-cleo-library))
- CLEO Redux is now able to execute JavaScript in GTA San Andreas with CLEO 4.4 installed
- new config parameter `AllowCs` to control `*.cs` scripts
- fix: ini config was ignored if there were missing parameters in the `cleo.ini`

#### BREAKING CHANGE

CLEO Redux' primary distribution file has been renamed to `cleo_redux.asi`. To avoid conflicts with previously installed versions of CLEO Redux manually delete old `cleo.asi` file from the game directory.

### 0.6.2 - Oct 11, 2021

- add [CALL_FUNCTION](https://library.sannybuilder.com/#/gta3/CLEO/0AA5), [CALL_FUNCTION_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA7), [CALL_METHOD](https://library.sannybuilder.com/#/gta3/CLEO/0AA6), [CALL_METHOD_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA8). See [Using Memory](using-memory.md#calling-foreign-functions) for more information.
- update typings to include links to relevant documentation

### 0.6.1 - Oct 8, 2021

- fix crash in `Memory` class methods

### 0.6.0 - Oct 8, 2021

- add [INT_ADD](https://library.sannybuilder.com/#/gta3/CLEO/0A8E), [INT_SUB](https://library.sannybuilder.com/#/gta3/CLEO/0A8F), [INT_MUL](https://library.sannybuilder.com/#/gta3/CLEO/0A90), [INT_DIV](https://library.sannybuilder.com/#/gta3/CLEO/0A91) commands
- math operations are now available through the native JavaScript `Math` object where possible ([see documentation](using-math.md)).
- new static methods in `Memory` class. See [documentation](using-memory.md) for more info

#### BREAKING CHANGES

- `asFloat` has been removed in favor of `Memory.ToFloat`
- class `Object` has been renamed to `ScriptObject` to avoid conflicts with native JavaScript Object.
- deprecated command `isKeyPressed` has been deleted. Use `Pad.isKeyPressed` instead

### 0.5.3 - Oct 2, 2021

- add a new built-in JavaScript function `asFloat` to cast an integer value returned by the `Memory.Read` command to a floating point number ([IEEE 754](https://en.wikipedia.org/wiki/IEEE_754))

```js
var gravity = asFloat(Memory.Read(gravityAddress, 4, false)); // the gravity var now holds a floating-point value
```

- auto-generated `*.d.ts` files now make a distinction between integer and floating-point parameters, VS Code autocomplete now displays them with `int` and `float` types respectively
- auto-generated `*.d.ts` files now have `<reference no-default-lib="true"/>` so it is no longer needed to add this line in a script file to exclude unsupported JS commands from autocomplete
- fix: `op` incorrectly returned any single value as integer regardless of the type information
- fix: `showTextBox` command was missing in the `cleo.log` with `logOpcodes=1`

### 0.5.2 - Sep 30, 2021

- CLEO now checks for updates and notifies in the main menu (can be disabled with `CheckUpdates=0`)
- command `isKeyPressed` has been deprecated, use `Pad.IsKeyPressed` instead
- fix: deadlock causing timeouts in JS scripts

### 0.5.1 - Sep 28, 2021

- add support for `Boolean`, `null` and `undefined` as arguments of the `op` command
- allow arbitrary size in `0A8C WRITE_MEMORY` to fill a continiuos block of memory with a single byte value
- fix: after reloading the game JS scripts could have been duplicated

### 0.5.0 - Sep 25, 2021

- add support for GTA III 1.0 and GTA VC 1.0
- add support for auto-incrementing variables `TIMERA` and `TIMERB`
- add permission levels for unsafe opcodes
- add two unsafe opcodes: `0A8C WRITE_MEMORY` and `0A8D READ_MEMORY`
- fix: custom opcodes did not work in main.scm
- fix: gosub did not work in CS scripts
- fix: race condition caused false-positive timeouts for JS scripts

### 0.4.0 - Sep 2, 2021

- add bindings for all opcodes in JS scripts
- CLEO can now generate a `*.d.ts` file for autocomplete in VS Code
- add hot reload for `*.js` files
- fix: opcodes log did not work even with `LogOpcodes=1`

### 0.3.1 - Aug 21, 2021

- add `op` function to execute any opcode from JavaScript code
- add `GAME` constant to check the current host game
- CLEO now keeps its settings in `CLEO/.config/cleo.ini` created on the first run
- JavaScript support can be disabled using `AllowJs=0` setting

### 0.3.0 - Aug 17, 2021

- add experimental VM executing ECMAScript 5 (JavaScript)

### 0.2.1 - Aug 14, 2021

- watch the CLEO directory and start/stop scripts if a CS file has been added or deleted

### 0.2.0 - Aug 13, 2021

- add hot reload

### 0.1.2 - Aug 13, 2021

- add support for reVC

### 0.1.1 - Aug 12, 2021

- initial release
