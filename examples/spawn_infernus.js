/**
 * this script spawns an Infernus in front of the player
 * when the F5 button is pressed
 */

var VK_F5 = 116;
var MI_INFERNUS = GAME === "re3" ? 101 : 141;

setTimeOfDay(12, 30);

while (true) {
  wait(250);
  if (isKeyPressed(VK_F5)) {
    loadModel(MI_INFERNUS);

    var pos = addVec(getPlayerPos(), { x: 2.0, y: -2.0, z: 0 });
    createCar(MI_INFERNUS, pos);

    showTextBox("Here is your Infernus");

    wait(2000);
  }
}

function isKeyPressed(key) {
  return op(0x0ab0, key);
}

function getPlayerPos() {
  return op(0x00a0, getPlayerActor());
}

function loadModel(mi) {
  op(0x0247, mi);

  while (!op(0x0248, mi)) {
    wait(250);
  }
}

function createCar(mi, pos) {
  op(0x00a5, mi, pos.x, pos.y, pos.z);
}

function addVec(v1, v2) {
  return { x: v1.x + v2.x, y: v1.y + v2.y, z: v1.z + v2.z };
}

function setTimeOfDay(hours, mins) {
  op(0x00c0, hours, mins);
}

function getPlayerActor() {
  return op(0x01f5, 0);
}
