// Script by Vital (Vitaly Pavlovich Ulyanov)
/// <reference path="./.config/vc.d.ts"/>

if (HOST !== "vc" && HOST !== "reVC") {
  exit("Sorry, this script is for GTA VC only");
}

const gangs = [0, 1, 2, 3, 4, 5, 6];
const primary_weapons = [19, 21, 22, 23, 24, 25, 26, 27];
const secondary_weapons = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 17, 18];

while (true) {
  wait(3000);

  gangs.forEach((gang) => {
    Gang.SetWeapons(
      gang,
      primary_weapons[Math.RandomIntInRange(0, primary_weapons.length)],
      secondary_weapons[Math.RandomIntInRange(0, secondary_weapons.length)]
    );
  });
}
