/// <reference path=".config/gta3.d.ts" />
// Player Skin Selector, use [ and ] to switch between different models
// original script by DK22Pac https://sannybuilder.com/forums/viewtopic.php?id=1177
// version for re3 by Seemann https://github.com/x87

import { KeyCode } from './.config/enums';

if (HOST !== "re3") {
  exit("This script is only for re3");
}

const setModelIndex = Memory.Translate("CPed::SetModelIndex");
if (!setModelIndex) {
  exit("Can't find address for CPed::SetModelIndex");
}

const getPed = Memory.Translate("CPools::GetPed");
if (!getPed) {
  exit("Can't find address for CPools::GetPed");
}

let index = 0;
const player = new Player(0);
const skins = setupSkinIds();

// main loop
while (true) {
  wait(250);
  if (player.isPlaying()) {
    if (checkKeyReleased(KeyCode.Oem4)) { // [ key
      changeSkin(prevSkin());
    } else if (checkKeyReleased(KeyCode.Oem6)) { // ] key
      changeSkin(nextSkin());
    }
  }
}

// initialize allowed ped models (skip models 26, 27, 28, 29)
function setupSkinIds() {
  const ids = [];
  for (let i = 0; i < 83; i++) {
    if (i >= 26 && i <= 29) {
      continue;
    }
    ids.push(i);
  }
  return ids;
}

// get next id in the skins array
function nextSkin() {
  if (++index >= skins.length) {
    index = 0;
  }
  return skins[index];
}

// get previous id in the skins array
function prevSkin() {
  if (--index < 0) {
    index = skins.length - 1;
  }
  return skins[index];
}

// check if the player has stopped pressing the key
function checkKeyReleased(key) {
  if (Pad.IsKeyPressed(key)) {
    while (Pad.IsKeyPressed(key)) {
      if (!player.isPlaying()) {
        return false;
      }
      wait(0);
    }
    return true;
  }
  return false;
}

// load model with index mi and change player model
function changeSkin(mi) {
  if (!Streaming.HasModelLoaded(mi)) {
    Streaming.RequestModel(mi);

    while (!Streaming.HasModelLoaded(mi)) {
      if (!player.isPlaying()) {
        return;
      }
      wait(0);
    }
  }

  const struct = Memory.Fn.Cdecl(getPed)(player.getChar()); // analogous to 0A96 GET_PED_POINTER

  Memory.Fn.Thiscall(setModelIndex, struct)(mi); // analogous to 0AA6: call_method address setModelIndex struct struct num_params 1 pop 0 func_params mi

  Streaming.MarkModelAsNoLongerNeeded(mi);
}
