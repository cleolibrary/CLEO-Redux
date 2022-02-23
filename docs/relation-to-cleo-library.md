# Relation to CLEO Library

CLEO is a common name for the custom libraries designed and created for GTA III, Vice City or San Andreas. Each version can be found and downloaded [here](https://cleo.li/download.html). CLEO Redux is _another_ CLEO implementation made from scratch with a few distinctive features, such as single code base for all games, or support for JavaScript code.

At the moment CLEO Redux can not be considered as a complete replacement for CLEO Library due to the lack of support for many widely used CLEO commands. To solve this issue and get the best out of the two libraries, CLEO Redux supports two different usage strategies.

CLEO Redux can run as a standalone software, or as an addon to CLEO Library. In the first case your game directory would only contain `cleo_redux.asi` (or `cleo_redux64.asi`) file. In the second case, your game directory would have both `cleo.asi` (or `III.CLEO.asi` or `VC.CLEO.asi`) and `cleo_redux.asi` (or `cleo_redux64.asi`).

## Running CLEO Redux as a standalone software

As a standalone software CLEO Redux runs compiled scripts and JavaScript and provides access to all native script commands. It also provides a limited set of [custom commands](./custom-commands.md) backward-compatible to CLEO Library. Existing CLEO scripts may not work if they use custom commands (for example from a third-party plugin) not supported by CLEO Redux.

This mode does not work in the classic GTA San Andreas.

## Running CLEO Redux as an addon to CLEO library

As an addon CLEO Redux runs alongside CLEO Library delegating it all the care for custom scripts. It means all custom scripts and plugins made for CLEO Library will continue working exactly the same. CLEO Redux only manages JS scripts. All custom commands become available to JavaScript runtime, which means you can use commands currently not implemented natively in CLEO Redux, for example for [files](https://library.sannybuilder.com/#/gta3/classes/File) or [dynamic libraries](https://library.sannybuilder.com/#/gta3/classes/DynamicLibrary).

This mode works in classic GTA III, GTA Vice City and GTA San Andreas where CLEO Library exists.
