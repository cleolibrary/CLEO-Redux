# C++ SDK

Custom plugins may call methods exposed by CLEO Redux using a provided `.lib` file. Include `cleo_redux_sdk.h` in your DLL project and link the binary with `cleo_redux.lib` (or `cleo_redux64.lib` if the target platform is x86_64) and you can start writing new commands.

## Example

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

[See more information](https://library.sannybuilder.com/#/sa_unreal/classes/IniFile) in Sanny Builder Library. The usage of the `IniFile` class requires an `fs` [permission](./permissions.md).
