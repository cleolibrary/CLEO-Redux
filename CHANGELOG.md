### 0.5.0 - September 25, 2021

- add support for GTA III 1.0 and GTA VC 1.0
- add support for auto-incrementing variables `TIMERA` and `TIMERB`
- add permission levels for unsafe opcodes
- add two unsafe opcodes: 0A8C WRITE_MEMORY and 0A8D READ_MEMORY
- fix: custom opcodes did not work in main.scm
- fix: gosub did not work in CS scripts
- fix: race condition caused false-positive timeouts for JS scripts

### 0.4.0 - September 02, 2021

- add bindings for all opcodes in JS scripts
- CLEO can now generate a \*.d.ts file for autocomplete in VS Code
- add hot reload for \*.js files
- fix an issue with the opcodes not being logged in the cleo.log even with LogOpcodes=1

### 0.3.1 - August 21, 2021

- add `op` binding to execute any opcode from JavaScript code
- add `GAME` constant to check the current host game
- CLEO now keeps its settings in `CLEO/.config/cleo.ini` created on the first run
- JavaScript support can be disabled using `AllowJs=0` setting

### 0.3.0 - August 17, 2021

- add experimental VM executing ECMAScript 5 (JavaScript)

### 0.2.1 - August 14, 2021

- watch CLEO directory and start/stop scripts if the CS file got removed

### 0.2.0 - August 13, 2021

- add hot reload

### 0.1.2 - August 13, 2021

- add support for reVC

### 0.1.1 - August 12, 2021

- initial release
