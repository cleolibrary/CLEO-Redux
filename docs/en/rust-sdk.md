# Rust SDK

Rust SDK uses similar to C++ interface with some extra wrapping methods to allow easily convert between C and Rust types. The header file is available as a [crate](https://crates.io/crates/cleo_redux_sdk) on crates.io. See the documentation [here](https://docs.rs/cleo_redux_sdk/latest/).

The crate already declares the native dependency on `cleo_redux.lib` (32-bit) or `cleo_redux64.lib` (64-bit), so a plugin only has to add `cleo_redux_sdk` to its dependencies.

## Linking

Download [`cleo_redux.lib`](https://github.com/cleolibrary/CLEO-Redux/blob/master/SDK/cleo_redux.lib?raw=true) and [`cleo_redux64.lib`](https://github.com/cleolibrary/CLEO-Redux/blob/master/SDK/cleo_redux64.lib?raw=true) (both live in the [`SDK`](https://github.com/cleolibrary/CLEO-Redux/tree/master/SDK) folder) and put that folder on the linker's search path with `-L`:

```toml
# .cargo/config.toml
[build]
target = "i686-pc-windows-msvc" # or "x86_64-pc-windows-msvc"

[target.i686-pc-windows-msvc]
rustflags = [
    "-C", "target-feature=+crt-static",
    "-C", "link-arg=/OUT:build/MyPlugin.cleo",
    "-L", "../../SDK"
]
```

Relative `-L` paths are resolved from the package directory.

## Example

See the [Input](https://github.com/cleolibrary/CLEO-Redux/tree/master/plugins/Input) plugin. It adds a bunch of new commands to check or emulate keyboard and mouse input. 

