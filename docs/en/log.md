# Log

CLEO logs important events and errors immediately as they occur in the `cleo_redux.log` file. This file is located in the same directory where you put `cleo_redux.asi`.
   
> If CLEO fails to create new files in the game directory due to the lack of write permissions, it fallbacks to using alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`.

You can also configure a custom log directory in the `cleo.ini` file using the `LogDirectory` option (e.g. `LogDirectory=CLEO`), in which case the log file will be created in that directory instead of the default folder.

The log file gets overwritten on each game run. If you experience any issue when using CLEO Redux, start investigating the root cause from this file.

To stream events in your terminal while testing a script, run:

```
tail -f cleo_redux.log
```

`tail` is a unix command so a compatible environment is needed (for example [Git Bash](https://git-scm.com/downloads)).

For windows users using powershell, run:

```
Get-Content cleo_redux.log -Wait -Tail 0
```

The log file also lists all executed opcodes with [`LogOpcodes=1`](./config.md#general) and JavaScript commands with [`CLEO.debug.trace(true)`](./api.md#cleo). 
