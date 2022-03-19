# Compiled Scripts

CLEO Redux can execute scripts compiled in the game's native [binary SCM format](https://gtamods.com/wiki/SCM_Instruction). Such scripts have a `.cs` extension. They are subject to the [limitations](https://docs.sannybuilder.com/scm-documentation/gta-limits) of SCM code.

[Check the FAQ](the-definitive-edition-faq.md#how-do-i-compile-cleo-scripts-with-sanny-builder) for the information on CS support in the remastered games.

## Writing a Compiled Script

> For a detailed step-by-step tutorial [visit this page](https://gtamods.com/wiki/CLEO/Tutorial). It's applicable to CLEO Redux.

To create a new script use [Sanny Builder 3](https://sannybuilder.com) in GTA III, GTA VC or GTA SA edit modes respectively. Add a directive `{$CLEO .cs}` at the top of your script, write the code and run "Compile and Copy". Sanny Builder will create a new CS file in the CLEO directory. 

At the moment CLEO Redux only provides a few custom commands. Most of the commands implemented in CLEO Library or its plugins are not available yet.

There are a few basic rules to follow when writing compiled scripts:

1) One file - one script. CLEO only supports one script per file.

2) Never use opcode `004E` to terminate a script. This opcode is only supported in the `main.scm`. Use [0A93](https://library.sannybuilder.com/#/sa/CLEO/0A93?p=1&v=1) instead.

3) Minimize the usage of global variables as they might conflict with other scripts. Some well-known variables such `$PLAYER_CHAR`, `$PLAYER_ACTOR` and `$ONMISSION` can be used.

CLEO Redux does not support saving the script status (a feature of CLEO Library) and there are no plans on adding this feature.


