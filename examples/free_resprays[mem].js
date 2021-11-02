/// <reference path=".config/gta3.d.ts" />

if (GAME !== "re3" && GAME !== "reVC") {
  exit("Only for re3 or reVC");
}

wait(1000);
var addr = Memory.Translate("CGarages::RespraysAreFree");
Memory.WriteU8(addr, 1, 0);

showTextBox("Resprays are free now!");
