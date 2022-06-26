# Installation

CLEO Redux comes with a hassle-free installer that identifies the selected game and downloads all the dependencies. Just run `cleo_redux_setup.exe` and follow its steps.

> CLEO Redux and its installer recognize the target game purely by the executable name in the selected/working directory. 
>
> * GTA III - `gta3.exe`
> * GTA VC - `gta-vc.exe`
> * GTA SA - `gta_sa.exe`, `gta-sa.exe`, or `gta_sa_compact.exe`
> * GTA IV - `GTAIV.exe`
> * re3 - `re3.exe`
> * reVC - `reVC.exe`
> * GTA III: DE - `libertycity.exe`
> * GTA VC: DE - `vicecity.exe`
> * GTA SA: DE - `sanandreas.exe`
>
> Names matching is case-insensitive. If the exe file does not contain a version information CLEO Redux always assumes version 1.0. 


Once the installation is complete, CLEO Redux is ready to use. You can now [install scripts](./installation-scripts.md) and [extra plugins](./installation-plugins.md) not included in the installer. To configure CLEO Redux check [this article](./config.md).

## CLEO Directory

CLEO directory is the primary location where you install [CLEO scripts](./installation-scripts.md), [CLEO plugins](./installation-plugins.md) and [custom texts](./using-fxt.md). CLEO Redux automatically creates this folder during installation and any time the game starts. 

In most cases this directory can be found in the game folder. If, however, CLEO lacks write permissions there and fails to create new files, it uses an alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`. `cleo_redux.log` and the `CLEO` directory can be found there.

## Dependency on ASI Loader

CLEO Redux is distributed as a dynamic-load library with an `.asi` extension. Historically ASI files have been used in GTA 3 and Vice City as addons to the Miles Sound System library (Mss32) which loads them into the game process. More recent titles didn't use MSS, so the modding community developed custom loaders commonly named "ASI Loader" to continue using ASI for any custom code to be injected into the game. 

[Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) by ThirteenAG can be used to load CLEO Redux in all games except GTA3/VC/re3/reVC. It gets downloaded during CLEO Redux setup. You may opt out of installing Ultimate ASI Loader if you have other means of injecting ASI files into the game (i.e. an alternative loader).

## Note on re3 or reVC

{{#include ./re3-reVC-notes.md}}

## Uninstallation

To uninstall CLEO Redux perform the following steps:

- Delete `cleo_redux.asi` (or `cleo_redux64.asi`).
- Delete the `CLEO` folder (optional).
- Delete the `cleo_redux.log` (optional)
