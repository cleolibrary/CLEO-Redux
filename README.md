# CLEO Redux

This is the official port of CLEO Library for re3 and reVC.

At the moment it's very barebone and has a limited number of features (see below).

## Installation

CLEO Redux only supports "Windows D3D9 MSS 32bit" version of re3 and reVC.

- Download and install [re3](https://github.com/GTAmodding/re3#installation) or [reVC](https://github.com/GTAmodding/re3/tree/miami#installation)

- Download `cleo.asi` from the [Releases page](https://github.com/cleolibrary/cleo-redux/releases).

Make sure `cleo.asi`, `re3.exe` (or `reVC.exe`) and `re3.pdb` (or `reVC.pdb`) are located in the same folder.

- Create CLEO directory and [install CLEO scripts](https://cleo.li/scripts.html#how_to_install_CLEO_scripts). You can try a classic `showsavescreen.cs` from CLEO 3 (see example scripts). Press `F4` to display the save screen while on foot.

**NOTE: CLEO scripts written for GTA III/Vice City should work, but CLEO Redux does not support most of the common CLEO commands yet (see the list of supported commands below).**

If the script only uses vanilla commands, or commands listed below it should work.

## Features

- Loading and processing compiled scripts (`*.cs`) located in the CLEO directory

- Experimental support for JavaScript execution (see below).

- Hot Reload

  - CLEO monitors active scripts and reloads them in game as they change https://www.youtube.com/watch?v=WanLojClqFw.
  - Adding a new CS file in CLEO directory or deleting an existing one while the game is running starts or stops the script automatically: https://www.youtube.com/watch?v=LAi2syrsxJg

- Basic SCM log. To enable trace for executed commands open up `cleo.ini` and change `LogOpcodes` to `1`.

## Writing CLEO Scripts in JavaScript

CLEO Redux can run scripts written in [ECMAScript 5.1](https://262.ecma-international.org/5.1/). This is the foundational standard for the modern JavaScript (although not the most recent version).

Each script should be made as a text file with the `.js` file extension. Find out available commands in this [reference page](https://re.cleo.li/reference.html) and [example scripts](https://github.com/cleolibrary/CLEO-Redux/tree/master/examples).

JavaScript is enabled by default. To disable it open up `cleo.ini` and change `AllowJS` to `0`.

**Note: when JavaScript is enabled CLEO Redux needs commands definitions from https://library.sannybuilder.com/. On the first run CLEO would try to download the necessary files and put them into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download `gta3.json` or `vc.json` from the [library's repo](https://github.com/sannybuilder/library) and put them to `CLEO/.config` directory.**

### Integration with Visual Studio Code

CLEO 0.4.0 generates typings for all supported commands that you can use when writing JavaScript in VS Code. Add the two following lines in your `*.js` script to get the full autocomplete support:

```
/// <reference no-default-lib="true"/>
/// <reference path=".config/gta3.d.ts" /> // or vc.d.ts
```

The first line excludes standard JavaScript API from autocomplete as it's not supported in the CLEO runtime.

The second line instructs VS Code where to look for the commands definitions for the autocomplete feature. The `path` can be relative to the script file or be absolute. [Find out more information](https://www.typescriptlang.org/docs/handbook/triple-slash-directives.html#-reference-path-) on the official TypeScript portal.

See this demo video: https://youtu.be/jqz8_lGnG4g

## Writing Compiled CLEO Scripts (.cs)

Use [Sanny Builder 3.8.0](https://sannybuilder.com) in GTA III or GTA VC edit modes respectively. Check out [this page](https://cleo.li/scripts.html) for more information.

## Custom Commands

- 0A93
  [TERMINATE_THIS_CUSTOM_SCRIPT](https://library.sannybuilder.com/#/sa/CLEO/0A93)
- 0AB0 [IS_KEY_PRESSED](https://library.sannybuilder.com/#/sa/CLEO/0AB0)

## Links

- re3 project: https://github.com/GTAmodding/re3
- CLEO Redux: https://re.cleo.li/
