/// <reference path=".config/vc.d.ts" />

//GXT KEYS (SOURCE="http://spaceeinstein.altervista.org/gxt/gxt.php?game=VC&lang=EN")
const WEAPONNAMES = ["PISTOL", "INGRAM", "SHOTGN1", "RUGER"];
const NUMPAD_2 = 50;
const NUMPAD_3 = 51;
const EKEY = 69;

var cycleIndex = 0;
var showText = false;

function customPrint() {
  let textPosX = 250;
  let textPosY = 250;
  Text.UseCommands(true);
  Text.SetCenter(true);
  Text.SetScale(0.75, 2.5);
  Text.SetColor(247, 145, 221, 255); //PINK COLOR (RGBA)
  Text.Display(textPosX, textPosY, WEAPONNAMES[cycleIndex]);
  Text.UseCommands(false);
} 

while (true) {
  if (Pad.IsKeyDown(EKEY)) {
    showText = !showText;
  }
  if (showText) {
    customPrint();
  }
  
  if (Pad.IsKeyDown(NUMPAD_2)) {
    if (cycleIndex - 1 < 0) {
      cycleIndex = WEAPONNAMES.length - 1;
    } else {
      cycleIndex -= 1;
    }
  }
  
  if (Pad.IsKeyDown(NUMPAD_3)) {
    if (cycleIndex + 1 > WEAPONNAMES.length - 1) {
      cycleIndex = 0;
    } else {
      cycleIndex += 1;
    }
  }

  wait(10);
}
