if (HOST !== "re3" && HOST !== "reVC") {
  exit("Only for re3 or reVC");
}

wait(1000);
const addr = Memory.Translate("CGarages::RespraysAreFree");
if (addr) {
  Memory.WriteU8(addr, true, false);
  showTextBox("Resprays are free now!");
}
