/// <reference path=".config/gta3.d.ts" />

if (GAME !== "re3" && GAME !== "reVC") {
  exit("Only for re3 or reVC");
}

wait(1000);
var addr = Memory.Translate("CGarages::RespraysAreFree");
if (addr) {
  Memory.WriteU8(addr, true, false);
  showTextBox("Resprays are free now!");
}
