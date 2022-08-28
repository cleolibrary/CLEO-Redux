# Troubleshooting

## CLEO does not work with re3 or reVC

{{#include ./re3-reVC-notes.md}}

## Game crashes with CLEO on San Andreas: The Definitive Edition

- make sure you installed the 64-bit version of Ultimate ASI Loader ([direct link to the latest release](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest/version.zip)).
  - Put `version.dll` to `Gameface\Binaries\Win64`
- make sure you run the latest CLEO Redux version (0.8.2 and above)
- delete config files from `Documents\Rockstar Games\GTA San Andreas Definitive Edition\Config\WindowsNoEditor`
- run the game (or Rockstar Games Launcher) as administrator

If CLEO can't create files in `Gameface\Binaries\Win64` it uses another path at `C:\Users\<your_usename>\AppData\Roaming\CLEO Redux`. There should be `cleo_redux.log` and the CLEO folder where all your scripts go.

## Scripts stopped working after CLEO Redux update

In rare cases there might be an error in command definitions in Sanny Builder Library. Delete the [definition file](./definitions.md) from the `.config` folder and restart the game. CLEO will redownload the latest version of the file. If the problem persists, report the issue using links below.

## Game is stuck loading

If the last entry in [cleo_redux.log](./log.md) is "Checking for updates..." CLEO can't access GitHub API. It might a temporary issue or your IP address is blocked from GitHub. Open [cleo.ini](./config.md), change `CheckUpdates` to `0` and restart the game.

## Nothing happens when I run the game, not even a log file is there

Check that you have installed Ultimate ASI Loader correctly. Sometimes you might need to give its dll file another name for the game to load it. Refer to [this documentation](./installation.md#dependency-on-asi-loader).

## My problem is not listed there

- Check the [GitHub tickets](https://github.com/cleolibrary/CLEO-Redux/issues)
- Check the [Feature support page](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix)
- Ask a question in [our Discord](https://discord.gg/d5dZSfgBZr)
