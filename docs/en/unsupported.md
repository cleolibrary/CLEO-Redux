# Unsupported or limited support scenarios

Despite our best effort some scenarios while available in game are not supported or supported with limitations by CLEO Redux. Some of them are imposed by the nature of SCM format or JavaScript language or the difficulties in bridging JavaScript and the native code.

Check the [Features support page](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix) to find out high-level features and the status of their support in different games.

The following items are known to be not working and there is no specific timeline on getting them fixed.

## Unsupported features in CS

- in x64 games (SA: DE) you can't read and write 64-bit values as the script engine only supports 32-bit values. You may need to use other means to access the game memory (e.g. from JavaScript)

## Unsupported features in JS

- for commands requiring a global SCM variable (e.g. countdown timers) use [scm.ts library](https://github.com/x87/scm.ts).

- commands implicitly loading models or textures (such as widgets) [Tracking issue](https://github.com/cleolibrary/CLEO-Redux/issues/12). You can circumvent the issue by preloading needed resources, e.g. by calling them in a .CS script first.

- you can't call the game functions that need references to variables to store the result. There is no "take an address of the variable" syntax. As a workaround, if the platform permits (e.g. in San Andreas with CLEO 4.4) you can allocate a memory block and pass its address to the function, then read the result from the memory using [Memory.Read](./using-memory.md).

- only integer numbers can be used as arguments for commands with variable arguments, such as `Text.PrintFormattedNow`. In the Sanny Builder Library these arguments are referred to as `arg: arguments`. If you need to pass a floating-point value, you can use `Memory.FromFloat`:

```
Text.PrintFormattedNow('%d %d %d %.2f', 100, 1, 2, 3, Memory.FromFloat(1.5))
```
