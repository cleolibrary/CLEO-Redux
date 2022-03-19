# Deprecated

Usage of the following commands is not recommended.

# op

`op(opcode_id, ...input_args)` - a low-level function to execute any in-game command with opcode `{opcode_id}`.

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