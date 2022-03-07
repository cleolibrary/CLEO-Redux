# Script Lifecycle

A file with the JavaScript code should have a `.js` extension and contain valid instructions. The script may have no instructions (the empty script). It runs as soon as the the new game starts or a save file is loaded.

Valid instructions include a code conforming to the ECMAScript 2020 standard and custom bindings available in the CLEO Redux runtime. If the runtime encounters an unknown or [illegal](./permissions.md) instruction the execution halts and a new error is [logged](./log.md) in `cleo_redux.log`

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