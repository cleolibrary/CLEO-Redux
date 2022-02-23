# Rust SDK

Rust SDK uses similar to C++ interface with some extra wrapping methods to allow easily convert between C and Rust types. The header file is available as a [crate](https://crates.io/crates/cleo_redux_sdk) on crates.io. See the documentation [here](https://docs.rs/cleo_redux_sdk/latest/).

## Example

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

