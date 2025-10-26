// this path below assumes the script file is located in CLEO directory. Adjust accordingly to your setup.
/// <reference path="./.config/gta3.d.ts" />
import { KeyCode } from "./.config/enums";

/**
 * this script spawns an Infernus in front of the player
 * when the F5 button is pressed
 */
const MI_INFERNUS = getInfernusMI();
const player = new Player(0);

while (true) {
  wait(250);
  if (Pad.IsKeyPressed(KeyCode.F5) && player.isPlaying()) {
    loadModel(MI_INFERNUS);

    const pos = addVec(player.getChar().getCoordinates(), { x: 2.0, y: -2.0, z: 0 });
    const infernus = Car.Create(MI_INFERNUS, pos.x, pos.y, pos.z);
    const blip = Blip.AddForCar(infernus);

    showTextBox("Here is your Infernus");
    infernus.markAsNoLongerNeeded();
    Streaming.MarkModelAsNoLongerNeeded(MI_INFERNUS);

    wait(2000);
    blip.remove();
  }
}

function loadModel(mi) {
  Streaming.RequestModel(mi);

  while (!Streaming.HasModelLoaded(mi)) {
    wait(250);
  }
}

function addVec(v1, v2) {
  return { x: v1.x + v2.x, y: v1.y + v2.y, z: v1.z + v2.z };
}

function getInfernusMI() {
  switch (HOST) {
    case "re3":
    case "gta3":
    case "gta3_unreal":
      return 101;
    case "reVC":
    case "vc":
    case "vc_unreal":
      return 141;
    case "sa":
    case "sa_unreal":
      return 411;
  }
}
