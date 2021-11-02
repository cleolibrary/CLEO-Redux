### 0.7.1 - Nov 02, 2021

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

### 0.6.1 - Oct 08, 2021
- fix crash in `Memory` class methods

### 0.6.0 - Oct 08, 2021

- add [INT_ADD](https://library.sannybuilder.com/#/gta3/CLEO/0A8E), [INT_SUB](https://library.sannybuilder.com/#/gta3/CLEO/0A8F), [INT_MUL](https://library.sannybuilder.com/#/gta3/CLEO/0A90), [INT_DIV](https://library.sannybuilder.com/#/gta3/CLEO/0A91) commands
- math operations are now available through the native JavaScript `Math` object where possible ([see documentation](using-math.md)).
- new static methods in `Memory` class. See [documentation](using-memory.md) for more info

#### BREAKING CHANGES
- `asFloat` has been removed in favor of `Memory.ToFloat`
- class `Object` has been renamed to `ScriptObject` to avoid conflicts with native JavaScript Object.
- deprecated command `isKeyPressed` has been deleted. Use `Pad.isKeyPressed` instead

### 0.5.3 - Oct 02, 2021

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

### 0.4.0 - Sep 02, 2021

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
