# JavaScript API

- [Native functions](#native-functions)
- [CLEO Redux Bindings](#cleo-redux-bindings)
  - [Variables](#variables)
    - [HOST](#host)
    - [ONMISSION](#onmission)
    - [TIMERA, TIMERB](#timera-timerb)
    - [\_\_dirname](#__dirname)
    - [\_\_filename](#__filename)
  - [Functions](#functions)
    - [addEventListener](#addeventlistener)
    - [asyncWait](#asyncwait)
    - [clearTimeout](#cleartimeout)
    - [clearInterval](#clearinterval)
    - [dispatchEvent](#dispatchevent)
    - [exit](#exit)
    - [log](#log)
    - [native](#native)
    - [setInterval](#setinterval)
    - [setTimeout](#settimeout)
    - [showTextBox](#showtextbox)
    - [wait](#wait)
  - [Static Objects](#static-objects)
    - [Memory](#memory)
    - [Math](#math)
    - [FxtStore](#fxtstore)
    - [CLEO](#cleo)
      - [CLEO.debug](#cleodebug)
      - [CLEO.version](#cleoversion)
      - [CLEO.apiVersion](#cleoapiversion)
      - [CLEO.hostVersion](#cleohostversion)
      - [CLEO.runScript](#cleorunscript)

## Native functions

CLEO Redux supports all commands native to the current game. In the classic GTA 3D series they are also known as _opcodes_. In GTA IV they are known as _native functions_. You can find them in [Sanny Builder Library](https://library.sannybuilder.com/).

Each available command has a predefined name that the game associates with a particular set of instructions running as you execute that command with arguments. To call a command by name use a built-in function [`native`](./api#native). For example, to change the player's health run `native("SET_PLAYER_HEALTH", 0, 100)`, where `0` is the player's id and `100` is the desired health.

For convenience, CLEO Redux also defines a wide set of abstractions on top of the native functions called _classes_. Each class represents a group of commands around some domain, e.g. commands related to the player, vehicles, or text display can be found in classes `Player`, `Car`, or `Text` respectively. You can browse available classes and their methods in Sanny Builder Library.

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

#### addEventListener

`addEventListener(name, callback)` calls the `{callback}` function every time an [event](./events.md) with the specified `{name}` is triggered. The `{callback}` function accepts a single argument that contains event-specific data. `addEventListener` returns a function that can be used to remove the listener.

```js
const cancel = addEventListener("OnVehicleCreate", (event) => {
  log("A vehicle is created!");
});

// ...

cancel(); // the event callback won't be called anymore
```

#### asyncWait

`await asyncWait(timeInMs)` pauses the script execution for at least `{timeInMs}` milliseconds. `asyncWait` can be used in async functions.

```js
async function loop() {
  while (true) {
    await asyncWait(1000);
    log("1 second passed");
  }
}
```

#### clearTimeout

See [setTimeout](#settimeout).

#### clearInterval

See [setInterval](#setinterval).

#### dispatchEvent

`dispatchEvent(name, data?)` triggers a custom event with the specified `{name}` and `{data}`. The `{data}` argument is optional. The event can be caught by [`addEventListener`](#addeventlistener) function from any active script.

```js
addEventListener("greeting", (event) => {
  log(event.data); // prints "hello"
});

dispatchEvent("greeting", "hello");
```

#### exit

`exit(reason?)` terminates the script immediately. `exit` function accepts an optional string argument that will be added to the `cleo_redux.log`.

```js
exit("Script ended");
```

#### log

`log(...values)` prints comma-separated `{values}` to the `cleo_redux.log`

```js
var x = 1;
log("value of x is ", x);
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

#### setInterval

`setInterval(callback, timeInMs?)` calls the `{callback}` function every `{timeInMs}` milliseconds (or `0` if the argument is not present).

`setInterval` returns an unique id that can be used to cancel the interval early using [clearInterval](#clearinterval).

```js
let intervalId = setInterval(() => {
  showTextBox("1 second passed");
}, 1000);

clearInterval(intervalId); // the callback won't be called anymore
```

#### setTimeout

`setTimeout(callback, timeInMs?)` calls the `{callback}` function after `{timeInMs}` milliseconds (or `0` if the argument is not present).

`setTimeout` returns an unique id that can be used to cancel the timeout early using [clearTimeout](#cleartimeout).

```js
let timeoutId = setTimeout(() => {
  exit("Terminate script);
}, 1000);

clearTimeout(timeoutId); // the callback won't be called
```

#### showTextBox

`showTextBox(text)` displays `{text}` in the black rectangular box. Not available on an `unknown` host.

```js
showTextBox("Hello, world!");
```

#### wait

`wait(timeInMs)` pauses the script execution for at least `{timeInMs}` milliseconds

```js
while (true) {
  wait(1000);
  log("1 second passed");
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

  ##### CLEO.hostVersion

  - `CLEO.hostVersion` - a complex property providing information about the host version. Currently only available if the current exe file has version info (e.g. GTA IV or GTA Trilogy)

  ```js
  log(CLEO.hostVersion); // "1.2.0.43"
  log(CLEO.hostVersion.major); // "1"
  log(CLEO.hostVersion.minor); // "2"
  log(CLEO.hostVersion.patch); // "0"
  log(CLEO.hostVersion.pre); // undefined
  log(CLEO.hostVersion.build); // "43"
  ```

  ##### CLEO.runScript

  - `CLEO.runScript(fileName, args?)` - method that spawns a new instance of the script. `fileName` is the path to the script to launch. `args` is an optional parameter to pass arguments to the script.

    > Don't overuse this feature as spawning a new script is a costly operation. Avoid spawning too many scripts in a loop.

    `runScript` has the following limitations:

    - script files must have one of the following extensions: `.mjs`, `.js` (JS scripts), `.ts` (TS scripts), `.s` or `.cs` (CS scripts).
    - spawning CS scripts is not supported in the [delegate mode](./relation-to-cleo-library.md#running-cleo-redux-as-an-addon-to-cleo-library) (i.e. won't work in GTA San Andreas with CLEO 4 installed.)

    When running a new script you can also provide arguments to it. `args` is a JavaScript object which keys correspond to variable names in the script. Key names for a CS script are numeric and correspond to local variables (0@, 1@, 2@, etc). JS scripts can receive both numbers and strings as arguments, whereas CS scripts can only receive numbers.

    You can spawn multiple instances of the same script with different arguments.

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
    0109: player $PLAYER_CHAR money += 1@ // gives the player $500
    0A93: terminate_this_custom_script
    ```

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
    00A1: set_char_coordinates $PLAYER_ACTOR x 0@ y 1@ z 2@ // teleports the player at -921.25 662.125 -100.0
    0A93: terminate_this_custom_script
    ```
