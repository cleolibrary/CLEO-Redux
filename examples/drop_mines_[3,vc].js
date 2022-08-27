/// <reference path=".config/gta3.d.ts" />

// Mine Drop script. Press M while in car to drop a mine. Don't forget to drive away
// as the mine will be activated in 1.5 seconds!

!["gta3", "vc", "gta3_unreal", "vc_unreal"].includes(HOST) &&
  exit("only for GTA III or Vice City");

export const PickupType = {
  None: 0,
  InShop: 1,
  OnStreet: 2,
  Once: 3,
  OnceTimeout: 4,
  Collectable1: 5,
  InShopOutOfStock: 6,
  Money: 7,
  MineInactive: 8,
  MineArmed: 9,
  NauticalMineInactive: 10,
  NauticalMineArmed: 11,
  FloatingPackage: 12,
  FloatingPackageFloating: 13,
  OnStreetSlow: 14,
};

const ACTIVATE_KEY = 0x4d; // M
const MI_MINE = GAME.startsWith("gta3") ? 1324 : 338;
const p = new Player(0);
let mines = [];
const COOLDOWN = 1500;
TIMERA = COOLDOWN;

while (true) {
  wait(250);
  if (
    TIMERA >= COOLDOWN &&
    p.isPlaying() &&
    p.isInAnyCar() &&
    Pad.IsKeyPressed(ACTIVATE_KEY)
  ) {
    const playerCar = p.getChar().storeCarIsInNoSave();

    const { x, y } = playerCar.getCoordinates();
    const time = Clock.GetGameTimer();
    mines.push({
      x,
      y,
      time,
      inactiveMine: Pickup.Create(MI_MINE, PickupType.MineInactive, x, y, -100),
    });

    TIMERA = 0;
  }

  if (mines.length) {
    activateMines();
  }
}

function activateMines() {
  const currentTime = Clock.GetGameTimer();
  mines = mines.filter(({ x, y, time, inactiveMine }) => {
    const msPassed = currentTime - time;
    if (msPassed > COOLDOWN) {
      inactiveMine.remove();
      Pickup.Create(MI_MINE, PickupType.MineArmed, x, y, -100);
      return false;
    }
  });
  return true;
}
