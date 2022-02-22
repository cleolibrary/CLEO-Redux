## CLEO Redux SDK

SDK provides a way to create new script commands for any game that CLEO Redux supports. It is agnostic to the game title and the underlying runtime (CS or JS). At this moment CLEO provides [SDK for the C++ and Rust languages](./plugins/SDK).

### Platforms Support

CLEO Redux provides SDK for both 32-bit and 64-bit games. There is one notable change between the two: on the 32-bit platform the SDK functions `GetIntParam` and `SetIntParam` operate on signed 32-bit numbers, whereas on the 64-bit platform they operate on signed 64-bit numbers (declared as the type `isize`).

### Plugin structure

Each plugin is a dynamic library with the `.cleo` extension that must be placed in `CLEO\CLEO_PLUGINS`. CLEO Redux scans this directory on startup and loads all `.cleo` files using WinAPI's function `LoadLibrary`. To register a handler for the new command the plugin must call `RegisterCommand` in the DllMain function. Once a user script encounters this command CLEO Redux invokes the handler with the one argument which is a pointer to the current context. This pointer must be used for calling other SDK methods.

### Naming convention

It's recommended for 64-bit plugins to have `64` in their names (e.g. `myplugin64.cleo`).

### Unsafe commands

Commands that use low-level WinAPI and can potentially damage user environment must be explicitly registered with a permission token (third argument to the `RegisterCommand`). User can disallow usage of unsafe commands in the scripts using [permission config](https://github.com/cleolibrary/CLEO-Redux#permissions). At the moment three permission tokens are used: `mem`, `fs`, and `dll`. They mark commands operating with the host process, user files and external libraries.

### Command interface

CLEO Redux uses [Sanny Builder Library](https://library.sannybuilder.com) to know an interface of any command. For a new command to become available in the scripts, the JSON file (`gta3.json`, `vc.json`, `sa.json`) must have the command definition, including the name that matches with the value that the plugin uses `RegisterCommand` with. E.g. if the plugin registers `SHOW_MESSAGE` command, the JSON file must have a command with the name property set to `SHOW_MESSAGE`. The number and order of the input and output parameters in the definition must match the order of methods used by the plugin (i.e. `GetXXXParam` for each input argument and `SetXXXParam` for each output argument).

#### Claiming Opcodes

Opcodes get assigned to new commands in Sanny Builder Library based on the availability, similarity with existing commands in other games, and other factors. To claim an opcode reach out to Sanny Builder Library maintainers on GitHub https://github.com/sannybuilder/library/issues

#### Why use command names and not an id for the command lookup?

One of the common issues with CLEO Library plugins was that commands authored by different people often had id collisions. If two plugins add commands with the same id, it is impossible to use them both. Using string names minimizes the collisions with custom plugins as well as with native opcodes. The library's definitions will ensure each command claims only available id. Also it helps to track and document plugins in one single place.

### SDK Version

The current version is `1`. Changes to SDK will advance this number by one.

### Path Resolution Convention

String arguments representing a path to the directory or file must be normalized using SDK's function `ResolvePath`. This function takes a path and returns the absolute path resolved by the following rules:

- an absolute path gets resolved as is
- path starting with "CLEO/" or "CLEO\\" gets resolved relative to the CLEO directory which is either
  - {game}\CLEO or
  - {user}\AppData\Roaming\CLEO Redux\CLEO
- all other paths get resolved relative to the current working directory (the game directory)


### String Arguments

Strings passed in and out of the SDK methods are UTF-8 encoded. 

If the script uses an integer value where a string is expected SDK treats this number as a pointer to a null-terminated UTF-8 character sequence to read, or to a large enough buffer to store the result to:

```js
IniFile.WriteString(0xDEADBEEF, "my.ini", "section", "key")
```

SDK will read a string from the address `0xDEADBEEF` and write it to the ini file.

```
0AF4: read_string_from_ini_file 'my.ini' section 'section' key 'key' store_to 0xDEADBEEF
```

SDK will read a string from the ini file and write it at the address `0xDEADBEEF`.

### C++ SDK

Custom plugins may call methods exposed by CLEO Redux using a provided `.lib` file. Include `cleo_redux_sdk.h` in your DLL project and link the binary with `cleo_redux.lib` (or `cleo_redux64.lib` if the target platform is x86_64) and you can start writing new commands.

#### Example

See the `IniFiles` plugin that includes a project for Visual Studio 2019. It adds a static class `IniFile` with the following methods:

```ts
interface IniFile {
    ReadFloat(path: string, section: string, key: string): float | undefined;
    ReadInt(path: string, section: string, key: string): int | undefined;
    ReadString(path: string, section: string, key: string): string | undefined;
    WriteFloat(value: float, path: string, section: string, key: string): boolean;
    WriteInt(value: int, path: string, section: string, key: string): boolean;
    WriteString(value: string, path: string, section: string, key: string): boolean;
}
```

See more information in Sanny Builder Library: https://library.sannybuilder.com/#/sa_unreal/classes/IniFile. The usage of the `IniFile` class requires an `fs` [permission](README.md#permissions).

### Rust SDK

Rust SDK uses similar to C++ interface with some extra wrapping methods to allow easily convert between C and Rust types. The header file is available as a [crate](https://crates.io/crates/cleo_redux_sdk) on crates.io. See the documentation [here](https://docs.rs/cleo_redux_sdk/latest/).

#### Example

See the `Dylib` plugin. It adds a class `DynamicLibrary` with the following methods:

```ts
declare class DynamicLibrary {
    constructor(handle: number);
    static Load(libraryFileName: string): DynamicLibrary | undefined;
    free(): void;
    getProcedure(procName: string): int | undefined;
}
```

See more information in Sanny Builder Library: https://library.sannybuilder.com/#/sa_unreal/classes/DynamicLibrary. The usage of the `DynamicLibrary` class requires a `dll` [permission](README.md#permissions).

