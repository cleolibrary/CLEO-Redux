# JavaScript API

## Native functions

CLEO Redux supports all commands native to the current game. In the classic GTA 3D series they are also known as _opcodes_. In GTA IV they are known as _native functions_. You can find them in [Sanny Builder Library](https://library.sannybuilder.com/).

Each available command has a predefined name that the game associates with a particular set of instructions running as you execute that command with arguments. To call a command by name use a built-in function [`native`](./api#native). For example, to change the player's health run `native("SET_PLAYER_HEALTH", 0, 100)`, where `0` is the player's id and `100` is the desired health.

For convenience, CLEO Redux also defines a wide set of abstractions on top of the native functions called _classes_. Each class represents a group of commands around some domain, e.g. commands related to the player, vehicles, or text display can be found in classes `Player`, `Car`, or `Text` respectively. You can browse available classes and methods they provide in Sanny Builder Library.

For example, to change the player's health using classes run `p.setHealth(100)`, where `p` is an instance of the `Player` class created with `new Player()` or `Player.Create` functions.

## CLEO Redux Bindings

In addition to native commands CLEO Redux adds extra variables and functions.

### Variables

#### HOST

the host name (previously available as `GAME` variable). Possible values are `gta3`, `vc`, `re3`, `reVC`, `sa`, `gta3_unreal`, `vc_unreal`, `sa_unreal`, `gta_iv`, `bully`, `unknown`.

CLEO plugins can use SDK to customize the name for their needs.

```js
if (HOST === "gta3") {
  showTextBox("This is GTA III");
}
if (HOST === "sa") {
  showTextBox("This is San Andreas");
}
if (HOST === "unknown") {
  showTextBox("This host is not natively supported");
}
```

#### ONMISSION

the global flag controlling whether the player is on a mission now. Not available on an `unknown` host.

```js
if (!ONMISSION) {
  showTextBox("Not on a mission. Setting ONMISSION to true");
  ONMISSION = true;
}
```

Setting `ONMISSION` to `true` has a side effect of turning the current script into a mission script, e.g. you can use mission-only commands, such as `STORE_CAR_CHAR_IS_IN` or `MISSION_HAS_FINISHED`. Setting `ONMISSION` to `false` turns the current script into a normal script.

#### TIMERA, TIMERB

two auto-incrementing timers useful for measuring time intervals.

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

#### \_\_dirname

an absolute path to the directory with the current file

#### \_\_filename

an absolute path to the current file

### Functions

#### log

`log(...values)` prints comma-separated `{values}` to the `cleo_redux.log`

```js
var x = 1;
log("value of x is ", x);
```

#### wait

`wait(timeInMs)` pauses the script execution for at least `{timeInMs}` milliseconds

```js
while (true) {
  wait(1000);
  log("1 second passed");
}
```

#### showTextBox

`showTextBox(text)` displays `{text}` in the black rectangular box. Not available on an `unknown` host.

```js
showTextBox("Hello, world!");
```

#### exit

`exit(reason?)` terminates the script immediately. `exit` function accepts an optional string argument that will be added to the `cleo_redux.log`.

```js
exit("Script ended");
```

#### native

`native(command_name, ...input_args)` is a low-level function to execute a command using its name `{command_name}`. The command name matches `name` property in a JSON file provided by Sanny Builder Library.

```js
native("SET_TIME_OF_DAY", 12, 30); // sets the time of day to 12:30
```

For the commands that return a single value, the result is this value.

```js
const progress = native("GET_PROGRESS_PERCENTAGE");
showTextBox(`Progress is ${progress}`);
```

For the commands that return multiple values, the result is an object where each key corresponds to a returned value. The key names match the output names given in the command definition

```js
var pos = native("GET_CHAR_COORDINATES", char); // returns char's coordinates vector {x, y, z}
showTextBox(`Character pos: x ${pos.x} y ${pos.y} z ${pos.z}`);
```

For the conditional commands the result is the boolean value `true` or `false`

```js
if (native("HAS_MODEL_LOADED", 101)) {
  // checks the condition
  showTextBox("Model with id 101 has been loaded");
}
```

### Static Objects

#### Memory

- `Memory` object allows to manipulate the process memory. See the [Memory guide](using-memory.md) for more information.

#### Math

- `Math` object is a standard object available in the JS runtime that provides common mathematical operations. CLEO Redux extends it with some extra commands. See the [Math object](using-math.md) for more information.

#### FxtStore

- `FxtStore` allows to update the content of in-game texts. See the [Custom Text](./using-fxt.md) guide for details.

#### CLEO

- `CLEO` object provides access to the runtime information and utilities:

  ##### CLEO.debug

  - `CLEO.debug.trace(flag)` toggles on and off command tracing in the current script. When {flag} is true all executed commands get added to `cleo_redux.log`:

  ```js
  CLEO.debug.trace(true);
  wait(50);
  const p = new Player(0);
  CLEO.debug.trace(false);
  ```

  ##### CLEO.version

  - `CLEO.version` - a complex property providing information about current CLEO version

  ```js
  log(CLEO.version); // "0.9.4-dev.20220427"
  log(CLEO.version.major); // "0"
  log(CLEO.version.minor); // "9"
  log(CLEO.version.patch); // "4"
  log(CLEO.version.pre); // "dev"
  log(CLEO.version.build); // "20220427"
  ```

  ##### CLEO.apiVersion

  - `CLEO.apiVersion` - a complex property providing information about current API (using `meta.version` field in the [primary definition](./definitions.md) file). Scripts can use it to check if the user has a particular API version installed.

  ```js
  log(CLEO.apiVersion); // "0.219"
  log(CLEO.apiVersion.major); // "0"
  log(CLEO.apiVersion.minor); // "219"
  log(CLEO.apiVersion.patch); // undefined
  log(CLEO.apiVersion.pre); // undefined
  log(CLEO.apiVersion.build); // undefined
  ```

##### CLEO.runScript

- (since 1.0.4) `CLEO.runScript(fileName, args?)` - method that spawns a new instance of the script. `fileName` is the path to the script to launch. `args` is an optional parameter to pass arguments to the script.

  > Don't overuse this feature as spawning a new script is a costly operation. Avoid spawning too many scripts in a loop.

  `runScript` has the following limitations:

  - the file name must have an extension `.mjs` or `.cs`
  - spawning CS scripts is not supported in the [delegate mode](./relation-to-cleo-library.md#running-cleo-redux-as-an-addon-to-cleo-library) (i.e. won't work in GTA San Andreas with CLEO 4 installed.)

  When running a new script you can also provide arguments to it. `args` is a JavaScript object which keys correspond to variable names in the script. Key names for a CS script are numeric and correspond to local variables (0@, 1@, 2@, etc). JS scripts can receive both numbers and strings as arguments, whereas CS scripts can only receive numbers.

  ###### Launching a new JS script

  Imagine that you have two files `main.js` and `child.mjs` in the CLEO directory:

  main.js:

  ```js
  CLEO.runScript("./child.mjs", { a: 1, b: "str", c: 10.5 });
  ```

  child.mjs:

  ```js
  showTextBox("child.mjs was launched with: " + a + " " + b + " " + c);
  ```

  Now if you run the game you should see the following message: `child.mjs was launched with: 1 str 10.5`.

  ###### Launching a new CS script

  main.js:

  ```js
  CLEO.runScript("./child.cs", { 1: 500 });
  ```

  child.cs:

  ```
  0109: player $PLAYER_CHAR money += 1@
  0A93: terminate_this_custom_script
  ```

  The player will get 500 dollars.

  To pass floating-point numbers to a CS script use `Memory.FromFloat` function:

  main.js:

  ```js
  CLEO.runScript("./child.cs", {
    0: Memory.FromFloat(-921.25),
    1: Memory.FromFloat(662.125),
    2: Memory.FromFloat(-100.0),
  });
  ```

  child.cs:

  ```

  00A1: set_char_coordinates $PLAYER_ACTOR x 0@ y 1@ z 2@
  0A93: terminate_this_custom_script

  ```
