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

## My problem is not listed there

- Check the [GitHub tickets](https://github.com/cleolibrary/CLEO-Redux/issues)
- Check the [Feature support page](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix)
- Ask a question in [our Discord](https://discord.gg/d5dZSfgBZr)
