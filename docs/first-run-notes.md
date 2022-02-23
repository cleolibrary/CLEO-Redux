There could be a noticeable lag during the first game run as CLEO Redux downloads the files necessary for [JavaScript support](#javascript-support). It won't happen on subsequent runs.

A new folder named `CLEO` should appear in the game directory. This is the primary location for all CLEO scripts, plugins and configs.

> If CLEO fails to create new files in the game directory due to the lack of write permissions, it fallbacks to using alternate path at `C:\Users\<your_username>\AppData\Roaming\CLEO Redux`. `cleo_redux.log` and the `CLEO` directory can be found there.
