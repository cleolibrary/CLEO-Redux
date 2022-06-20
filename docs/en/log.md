# Log

CLEO logs important events and errors immediately as they occur in the `cleo_redux.log` file located in the game directory.

{{#include ./cleo-directory-note.md}}

The log file gets overwritten on each game run. If you experience any issue when using CLEO Redux, start investigating the root cause from this file.

To stream events in your terminal while testing a script, run:

```
tail -f cleo_redux.log
```

`tail` is a unix command so a compatible environment is needed (for example Git Bash).

The log file also lists all executed opcodes with [`LogOpcodes=1`](./config.md#general) and JavaScript commands with [`CLEO.debug.trace(true)`](./api.md#cleo). 