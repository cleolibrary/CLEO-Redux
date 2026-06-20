# Permissions


CLEO Redux acknowledges some [custom commands](./custom-commands.md) (opcodes) as unsafe and requires the user to decide whether to run them or not. Raw access to the process memory, loading external libraries or making network requests can be harmful and produce undesired side-effects. Hence CLEO introduces permission levels for running the unsafe code.

There are four available levels:

### All

Any unsafe operation is allowed. Use this only when you trust the scripts you run.

### Lax

This is the default permission level.

No unsafe operation is allowed unless the script explicitly requests it. Permissions can be requested in three ways:

#### File Names (All Script Types)

Include permission tokens wrapped in square brackets directly in the script file name. This works for all script types (CS, JS, TS):

- `cool-spawner[mem].cs`
- `main[mem][dll].ts`
- `script[fs].js`

If the file is named differently without the required permission tokens, CLEO rejects unsafe operations.

#### Directory Names (JS/TS Only)

For [script directories](./script-lifecycle.md#organizing-scripts) (subdirectories with `index.js`/`index.ts`), include permission tokens in the directory name:

```
CLEO/
├─ my_mod[mem][dll]/
│  ├─ index.ts
│  ├─ utils.ts
```

#### mod.json Manifest (JS/TS Only)

Alternatively, declare permissions in a `mod.json` file within your script directory:

```
CLEO/
├─ my_mod/
│  ├─ mod.json
│  ├─ index.ts
```

With `mod.json` content:

```json
{
  "permissions": ["mem", "dll"]
}
```

This allows you to keep your script directory name clean while still requesting necessary permissions. When both directory name suffixes and `mod.json` permissions are present, the directory name suffix takes precedence.

### Strict

No unsafe operation is allowed unless the script explicitly requests it (see `"Lax"`) and the CLEO config file permits this type of operation under the `Permissions` section.

Permissions section in `cleo.ini` allows to enable or disable groups of unsafe operations by using the [permission tokens](#known-permission-tokens). For example,

```ini
mem=0
```

disables all memory-related opcodes even if the script has the `[mem]` token in the file name.

> `Permissions` section in the `cleo.ini` only takes effect when `PermissionLevel` is `Strict`.

### None

No unsafe operation is allowed.

## Known Permission Tokens

- `mem` - reading from and writing to the process memory, calling foreign functions 
- `dll` - loading dynamic libraries and finding exported functions
- `fs` - creating, reading and deleting files from the local file system
