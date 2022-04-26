// uncomment one of these to enable autocomplete in VS Code
// /// <reference path=".config/gta3.d.ts" />
// /// <reference path=".config/vc.d.ts" />
// /// <reference path=".config/sa.d.ts" />

import { KeyCode } from './.config/enums';

while (true) {
  wait(250);

  if (Pad.IsKeyPressed(KeyCode.F4)) {
    Game.ActivateSaveMenu();
    wait(1000);
  }
}
