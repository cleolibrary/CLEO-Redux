# Configuration

CLEO Redux exposes some of the configurable settings in the file `CLEO\.config\cleo.ini`.

## General

- `AllowCs` - when set to `1` CLEO loads and executes `*.cs` files located in the [CLEO directory](./cleo-directory.md). Enabled by default.
- `AllowJs` - when set to `1` CLEO loads and executes `*.js` files located in the [CLEO directory](./cleo-directory.md). Enabled by default.
- `AllowFxt` - when set to `1` CLEO loads and [uses](./using-fxt.md) `*.fxt` files located in the CLEO\CLEO_TEXT directory. Enabled by default.
- `CheckUpdates` - (deprecated in favor of [Frontend](./installation-plugins.md) plugin)
- `LogOpcodes` - when set to `1` CLEO [logs](./log.md) all executed opcodes in custom scripts.
- `DisplayMenuInfo` - when set to `1` CLEO displays some information in the main menu. Enabled by default.
- `PermissionLevel` - sets the [permission level](./permissions.md) for unsafe operations (see below). Default is `Lax`.

## Host

- `EnableSelfHost` - when set to `1` CLEO runs in the self-host mode. Only applicable on an Unknown host. See the [Emdedding](./embedding.md) guide for more information.
- `SelfHostFps` - the amount of iterations per second the CLEO's main loop will do. Only applicable when `EnableSelfHost` is `1`. Default is `30`.

## Permissions

This section lists permission tokens and sets whether they are allowed or not in the [Strict mode](./permissions.md#strict).
