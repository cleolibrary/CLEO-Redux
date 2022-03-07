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
