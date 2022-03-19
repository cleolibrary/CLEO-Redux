# Configuration

CLEO Redux exposes some of the configurable settings in the file `CLEO\.config\cleo.ini`.

- `AllowCs` - when set to `1` CLEO loads and executes `*.cs` files located in the [CLEO directory](./cleo-directory.md). Enabled by default.
- `AllowJs` - when set to `1` CLEO loads and executes `*.js` files located in the [CLEO directory](./cleo-directory.md). Enabled by default.
- `AllowFxt` - when set to `1` CLEO loads and [uses](./using-fxt.md) `*.fxt` files located in the CLEO\CLEO_TEXT directory. Enabled by default.
- `CheckUpdates` - when set to `1` CLEO check if there is a new update available for download during the game startup. Enabled by default.
- `LogOpcodes` - when set to `1` CLEO logs all executed opcodes in custom scripts. This log is part of the `cleo_redux.log` file (see [Log](./log.md))
- `PermissionLevel` - sets the [permission level](./permissions.md) for unsafe operations (see below). Default is `Lax`.
