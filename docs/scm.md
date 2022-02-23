# SCM

CLEO Redux can execute scripts compiled in the game's native binary SCM format. Such scripts have a `.cs` extension. 

> [Check the FAQ](the-definitive-edition-faq.md#how-do-i-compile-cleo-scripts-with-sanny-builder) for the information on CS support in the remastered games.

> At the moment CLEO Redux only provides a few custom commands. Most of the commands implemented in CLEO Library or its plugins are not available yet.

## Writing a CLEO Script

To create a new script use [Sanny Builder 3](https://sannybuilder.com) in GTA III, GTA VC or GTA SA edit modes respectively. Add a directive `{$CLEO .cs}` at the top of your script and run "Compile and Copy". Sanny Builder will create a new CS file in the CLEO directory. 

CLEO scripts are subject to the [limitations of SCM code](https://docs.sannybuilder.com/scm-documentation/gta-limits). Each script has a set of local variables (16 in GTA3 and VC; 32 in San Andreas) and 2 self-incrementing counters (timers).

There are a few basic rules to follow when writing CLEO scripts:

1) One file - one script. CLEO only supports one script per file.

2) Never use opcode `004E` in the CLEO scripts. This opcode is only supported in the `main.scm`. Use opcode [0A93](https://library.sannybuilder.com/#/sa/CLEO/0A93?p=1&v=1) to terminate a CLEO script.

3) Minimize the usage of global variables in the CLEO script as it might break the game scripts in the `main.scm`. Some well-known variables such $PLAYER_CHAR, $PLAYER_ACTOR and $ONMISSION can be used.

CLEO Redux does not support saving the script status and there are no plans on adding this feature.


