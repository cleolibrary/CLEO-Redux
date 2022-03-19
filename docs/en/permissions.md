# Permissions


CLEO Redux acknowledges some [custom commands](./custom-commands.md) (opcodes) as unsafe and requires the user to decide whether to run them or not. Raw access to the process memory, loading external libraries or making network requests can be harmful and produce undesired side-effects. Hence CLEO introduces permission levels for running the unsafe code.

There are four available levels:

## All

Any unsafe operation is allowed. Use this only when you trust the scripts you run.

## Lax

This is the default permission level.

No unsafe operation is allowed unless the script explicitly requests it. Currently to request a permission, the name of the script file must include the permissions tokens wrapped in square brackets.

For example, if the script wants to access the memory via `0A8D READ_MEMORY` the file name must contain `[mem]`, e.g. `cool-spawner[mem].cs`. If the file is named differently CLEO rejects `0A8D` and the script crashes.

## Strict

No unsafe operation is allowed unless the script explicitly requests it (see `"Lax"`) and the CLEO config file permits this type of operation under the `Permissions` section.

Permissions section in `cleo.ini` allows to enable or disable groups of unsafe operations by using the permission tokens. For example,

```ini
mem=0
```

disables all memory-related opcodes even if the script has the `[mem]` token in the file name.

> `Permissions` section in the `cleo.ini` only takes effect when `PermissionLevel` is `Strict`.

## None

No unsafe operation is allowed.
