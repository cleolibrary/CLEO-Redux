
- Download and install [Ultimate ASI Loader x64](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest/version.zip) by ThirteenAG (place `version.dll` to the `Gameface\Binaries\Win64` directory)
- Copy `cleo_redux64.asi` to the same directory.

- Run the game once and you should get a new CLEO directory created in the same directory. If that did not happen, check below.

### What if I can't find the CLEO directory?

For many people running their game with CLEO Redux installed results in the immediate crash. It happens if there is no write permissions in the current directory (`Win64`). To remediate this issue CLEO fallbacks to using alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`. `cleo_redux.log` and the `CLEO` directory can be found there. See also the [troubleshooting guide](TROUBLESHOOTING.md).
