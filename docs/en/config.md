# Configuration

CLEO Redux exposes some of the configurable settings in the file `cleo\.config\cleo.ini`.

## General

- `AllowCs` - when set to `1` CLEO loads and executes `*.cs` files located in the [CLEO directory](./cleo-directory.md). Enabled by default.
- `DelegateCs` - when set to `1` CLEO Redux hands compiled scripts (`*.cs`) over to [another instance of CLEO](./relation-to-cleo-library.md#running-cleo-redux-as-an-addon-to-cleo-library) and disables its own CS support. Useful when the other instance can not be detected automatically, e.g. when it is served from modloader. Takes precedence over `AllowCs`. Disabled by default.
- `AllowJs` - when set to `1` CLEO loads and executes `*.js` and `*.ts` files located in the [CLEO directory](./cleo-directory.md). Enabled by default.
- `AllowFxt` - when set to `1` CLEO loads and [uses](./using-fxt.md) `*.fxt` files located in the cleo\cleo_text directory. Enabled by default.
- `LogOpcodes` - when set to `1` CLEO [logs](./log.md) all executed opcodes in custom scripts.
- `PermissionLevel` - sets the [permission level](./permissions.md) for unsafe operations (see below). Default is `Lax`.
- `LogDirectory` - specifies a custom directory for the [log file](./log.md).

## Host

- `EnableSelfHost` - when set to `1` CLEO runs in the self-host mode. Only applicable on an Unknown host. See the [Emdedding](./embedding.md) guide for more information.
- `SelfHostFps` - the amount of iterations per second the CLEO's main loop will do. Only applicable when `EnableSelfHost` is `1`. Default is `30`.

## Permissions

This section lists permission tokens and sets whether they are allowed or not in the [Strict mode](./permissions.md#strict).
