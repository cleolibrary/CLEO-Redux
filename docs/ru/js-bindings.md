# Bindings

The following variables and functions are only available in JavaScript code.


## Variables

### GAME

current game id. Possible values: `gta3`, `vc`, `re3`, `reVC`, `sa`, `gta3_unreal`, `vc_unreal`, `sa_unreal`

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

### ONMISSION 

global flag controlling whether the player is on a mission now.

```js
if (!ONMISSION) {
  showTextBox("Not on a mission. Setting ONMISSION to true");
  ONMISSION = true;
}
```

### TIMERA, TIMERB

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

### __dirname 

an absolute path to the directory with the current file

## Functions

### log

`log(...values)` prints comma-separated `{values}` to the `cleo_redux.log`

```js
var x = 1;
log("value of x is ", x);
```

### wait 

`wait(timeInMs)` pauses the script execution for at least `{timeInMs}` milliseconds

```js
while (true) {
  wait(1000);
  log("1 second passed");
}
```

### showTextBox

`showTextBox(text)` displays `{text}` in the black rectangular box

```js
showTextBox("Hello, world!");
```

### exit

`exit(reason?)` terminates the script immediately. `exit` function accepts an optional string argument that will be added to the `cleo_redux.log`.

```js
exit("Script ended");
```

### native

`native(command_name, ...input_args)` is a low-level function to execute any in-game command using its name `{command_name}`

```js
native("SET_TIME_OF_DAY", 12, 30); // sets the time of day to 12:30
```

## Static Objects 


### Memory

- `Memory` object allows to manipulate the process memory. See the [Memory guide](using-memory.md) for more information.


### Math


- `Math` object is a standard object available in the JS runtime that provides common mathematical operations. CLEO Redux extends it with some extra commands. See the [Math object](using-math.md) for more information.
