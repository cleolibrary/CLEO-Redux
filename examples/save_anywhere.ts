import { KeyCode } from './.config/enums';

while (true) {
  wait(250);

  if (Pad.IsKeyPressed(KeyCode.F4)) {
    Game.ActivateSaveMenu();
    wait(1000);
  }
}
