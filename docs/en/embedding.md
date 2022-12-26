# Embedding to custom host

CLEO Redux can be embedded and run JS scripts on an unknown (i.e. not [supported officially](./introduction.md#supported-releases)) host. A _host_ is an application in which process `cleo_redux.asi` or `cleo_redux64.asi` [gets loaded or injected](#loading-into-custom-process) and where the CLEO runtime [runs](#launching-the-cleo-runtime). This feature is highly experimental and subject to change at any moment.

- [Loading into custom process](#loading-into-custom-process)
- [Launching the CLEO runtime](#launching-the-cleo-runtime)
  - [Automatic launch](#automatic-launch)
  - [Manually Controlling the Runtime](#manually-controlling-the-runtime)
- [Available Commands](#available-commands)
- [Manifest](#manifest)
  - [Example](#example)

<iframe width="560" height="315" src="https://www.youtube.com/embed/rk2LvDt7UkI" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Loading into custom process

There are multiple ways of loading ASI file into the target process. They include but not limited to [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) or any [DLL injector](https://github.com/search?q=dll+injector) available on GitHub. The host can load CLEO ASI file as a dynamic library when needed using WinAPI's `LoadLibrary` function.

## Launching the CLEO runtime

After injecting CLEO into the target process you should launch the runtime to execute scripts. There are two ways of doing it: automatic and manual.

### Automatic launch

To launch the runtime on an unknown host immediately after loading, open the [config file](./config.md) and set `EnableSelfHost` to `1`. When loaded as a self host CLEO Redux scans the [CLEO directory](./cleo-directory.md) for plugins and scripts and runs them. This option is suitable if you don't have control over the host's source code and inject the library using an injector.

### Manually Controlling the Runtime

The host can start the runtime and advance its main loop using SDK methods `RuntimeInit` and `RuntimeNextTick`. This option is suitable if you have control over the host's source code and can execute arbitrary instructions.

This is how it can be implemented in Rust:

```toml
[dependencies]
ctor = "0.1.21"
cleo_redux_sdk = "^0.0.6"
```

```rust
use ctor::*;

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]

#[ctor]
fn init() {
    use cleo_redux_sdk;
    use std::{thread, time};

    // load CLEO scripts, FXT, enable file watcher
    cleo_redux_sdk::runtime_init();

    // init time variables
    const FPS: i32 = 30;
    let time_step = 1000 / FPS;
    let started = time::Instant::now();

    thread::spawn(move || loop {
        let current_time = started.elapsed().as_millis() as u32;

        // advance main loop providing current time and time step
        // current time is used to determine whether a script should "wake up" after wait command
        // time step is used to increment TIMERA and TIMERB variables
        cleo_redux_sdk::runtime_next_tick(current_time, time_step);

        // pause for at least time step ms
        thread::sleep(time::Duration::from_millis(time_step as u64));
    });
}
```

## Available Commands

In the self-hosted mode CLEO Redux supports [own bindings](./api.md#cleo-redux-bindings) and commands made with [SDK](./using-sdk.md). It uses command definitions for the Unknown host from Sanny Builder Library (available for [32-bit](https://library.sannybuilder.com/#/unknown_x86) and [64-bit](https://library.sannybuilder.com/#/unknown_x64)).

You can use all standard JavaScript features. The list of available commands can be seen in the auto-generated file `.config/unknown.d.ts`.

## Manifest

Manifest is a file with static configuration for the given host. Only unknown hosts make use of it. The configuration should be stored in `.config\manifest.json` with the following structure:

```json
{
    "host": string,
    "host_name": string,
    "compound": boolean
}
```

- `host` should match the host's executable name. E.g. if the host runs via `application.exe`, the value is `application`. Available in scripts as the [HOST variable](./api.md#host).
- `host_name` defines the host's custom name used in the [log](./log.md)
- `compound` defines whether the host uses [compound definitions](./definitions.md). By default the host uses definitions from the file matching `<host>.json`, e.g. `application.json`. This file should be provided by the person managing integration of CLEO Redux with the given host and placed in the `.config` folder.

  When `compound` is set to `true` the host also uses command definitions for the Unknown host (e.g. `unknown_x86.json`). If this file is missing CLEO downloads it from Sanny Builder Library.

### Example

Host: [Sanny Builder 3](https://sannybuilder.com) (`sanny.exe`)

```json
{
  "host": "sanny",
  "host_name": "Sanny Builder 3",
  "compound": true
}
```

`Sanny Builder 3\CLEO\.config` folder contains `sanny.json` and `manifest.json` before the first run. The other files are downloaded or generated automatically.
