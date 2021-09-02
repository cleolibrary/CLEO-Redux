/// <reference no-default-lib="true"/>

// this path below assumes the spawn_infernus.js is located in re3/CLEO directory. Adjust accordingly to your setup.
/// <reference path=".config/gta3.d.ts" />

/**
 * this script spawns an Infernus in front of the player
 * when the F5 button is pressed
 */
var VK_F5 = 116;
var MI_INFERNUS = GAME === "re3" ? 101 : 141;
var player = new Player(0);

Clock.SetTimeOfDay(22, 30);

while (true) {
  wait(250);
  if (isKeyPressed(VK_F5) && player.isPlaying()) {
    loadModel(MI_INFERNUS);

    var pos = addVec(player.getCoordinates(), { x: 2.0, y: -2.0, z: 0 });
    var infernus = Car.Create(MI_INFERNUS, pos.x, pos.y, pos.z);
    var blip = Blip.AddForCar(infernus);

    showTextBox("Here is your Infernus");
    infernus.markAsNoLongerNeeded();
    Streaming.MarkModelAsNoLongerNeeded(MI_INFERNUS);

    wait(2000);
    infernus.explode();
    Camera.Shake(200);
    wait(1000);
    infernus.delete();
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
