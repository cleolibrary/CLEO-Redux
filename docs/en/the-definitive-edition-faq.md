Here you can find answers to the frequently asked questions about support for The Trilogy remaster.
- [What versions are supported?](#what-versions-are-supported)
- [Is there any difference from support of the classic games?](#is-there-any-difference-from-support-of-the-classic-games)
- [What commands/opcodes are available?](#what-commandsopcodes-are-available)
- [How do I know what commands can I use in JavaScript?](#how-do-i-know-what-commands-can-i-use-in-javascript)
- [Can I work with the game memory or call the game functions?](#can-i-work-with-the-game-memory-or-call-the-game-functions)
- [How do I compile CLEO scripts for the Triogy with Sanny Builder?](#how-do-i-compile-cleo-scripts-for-the-triogy-with-sanny-builder)
- [I can't find an answer to my question here, where do I go?](#i-cant-find-an-answer-to-my-question-here-where-do-i-go)

### What versions are supported?

> The versions listed below refer to the executable file and can be checked by right-clicking the game’s executable (`LibertyCity.exe`, `ViceCity.exe`, or `SanAndreas.exe`) and opening Properties → Details → File Version.

| Game\Platform                                  | Rockstar Games (RGL)                                                                                                                                                         | Steam                                                         | Epic Games |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------- | ------------------- |
| GTA III: The Definitive Edition       | 1.0.0.14718 (Title Update 1.03)<br>1.0.0.15284 (Title Update 1.04)<br>1.0.8.11827 (Title Update 1.04.5)<br>1.0.17.38838<br>1.0.17.39540<br>1.0.112.6680                               | 1.0.17.38838<br>1.0.17.39540<br>1.0.112.6680<br>1.0.113.21181 | 1.0.17.39540        |
| GTA Vice City: The Definitive Edition | 1.0.0.14718 (Title Update 1.03)<br>1.0.0.15399 (Title Update 1.04)<br>1.0.8.11827 (Title Update 1.04.5)<br>1.0.17.38838<br>1.0.17.39540<br>1.0.112.6680                               | 1.0.17.38838<br>1.0.17.39540<br>1.0.112.6680<br>1.0.113.21181 | 1.0.17.39540        |
| San Andreas: The Definitive Edition   | 1.0.0.14296<br>1.0.0.14388<br>1.0.0.14718 (Title Update 1.03)<br>1.0.0.15483 (Title Update 1.04)<br>1.0.8.11827 (Title Update 1.04.5)<br>1.0.17.38838<br>1.0.17.39540<br>1.0.112.6680 | 1.0.17.38838<br>1.0.17.39540<br>1.0.112.6680<br>1.0.113.21181 | 1.0.17.39540        |

### Is there any difference from support of the classic games?

In short, yes. [See this page](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix) for detail on what's supported and what's not.

### What commands/opcodes are available?

CLEO Redux supports all native commands provided by the game engine. You can find the list of all commands in the [Sanny Builder library](https://library.sannybuilder.com/#/sa_unreal). 

In addition to that, CLEO Redux adds [new commands via plugins](https://library.sannybuilder.com/#/unknown_x64/script).

### How do I know what commands can I use in JavaScript?

After each game run, CLEO generates a `.d.ts` file in the `CLEO\.config` directory. It's called `gta3.d.ts`, `vc.d.ts` or `sa.d.ts` depending on the game. This file lists all supported functions and methods that you can use in JavaScript code.

To enable autocomplete in VS Code save your script file with `.ts` extension.

### Can I work with the game memory or call the game functions?

Yes, check the [Memory guide](using-memory-64.md).

### How do I compile CLEO scripts for the Triogy with Sanny Builder?

CLEO Redux provides limited support of compiled scripts (.CS) for the San Andreas: Definitive Edition only. It is recommended to write scripts using JavaScript or TypeScript.

To compile CLEO scripts for San Andreas: The Definitive Edition using Sanny Builer use SA Mobile mode. 

### I can't find an answer to my question here, where do I go?

- Check the [troubleshooting guide](troubleshooting.md).
- Check the [GitHub tickets](https://github.com/cleolibrary/CLEO-Redux/issues)
- Check the [Feature support page](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix)
- Ask a question in [our Discord](https://cleo.li/discord)
