# Embedding to custom host

> This documentation is being worked on.

CLEO Redux can be embedded and run JS scripts on any host. To achieve it the target process should load `cleo_redux.asi` and launch the runtime. This feature is highly experimental and subject to change at any moment.

## Loading into custom process

There are multiple ways of loading ASI file into the target process. [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) is one of them. The host can load CLEO ASI file as a dynamic library when needed.


## Starting CLEO runtime

To start the runtime on an unknown host automatically, open a [config file](./config.md) and set `EnableSelfHost` to `1`. When loaded as a self host CLEO Redux scans the [CLEO directory](./cleo-directory.md) for plugins and scripts and runs them.

The host can start the runtime and advance its main loop using SDK methods `RuntimeInit` and `RuntimeNextTick`.

## Available Commands

In self-hosted mode CLEO Redux supports native [bindings](./js-bindings.md) and commands made with [the SDK](./using-sdk.md).