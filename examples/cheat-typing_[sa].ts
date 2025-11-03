import { KeyCode } from "./.config/enums";

// press a key from 1 to 5 to emulate a cheat code typing
// Input plugin 1.1+ is required

HOST === "sa" || exit("This script is only for SA");

while (true) {
  wait(0);
  if (Pad.IsKeyDown(KeyCode.Num1)) {
    type("TURNDOWNTHEHEAT");
  }
  if (Pad.IsKeyDown(KeyCode.Num2)) {
    type("ROCKETMAN");
  }
  if (Pad.IsKeyDown(KeyCode.Num3)) {
    type("JUMPJET");
  }
  if (Pad.IsKeyDown(KeyCode.Num4)) {
    type("SPEEDITUP");
  }
  if (Pad.IsKeyDown(KeyCode.Num5)) {
    type("SLOWITDOWN");
  }
}

// split the cheat into characters and press each one
function type(cheat) {
  cheat.split("").forEach((c) => press(c.charCodeAt(0)));
}

// emulate the key press, hold a key and release it
function press(key) {
  Pad.HoldKey(key);
  wait(0);
  Pad.ReleaseKey(key);
  wait(0);
}
