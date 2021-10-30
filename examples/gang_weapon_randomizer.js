// Script by Vital (Vitaly Pavlovich Ulyanov)
/// <reference path=".config/vc.d.ts"/>

if (GAME === "vc") {
  var gangs = [0, 1, 2, 3, 4, 5, 6],
    primary_weapons = [19, 21, 22, 23, 24, 25, 26, 27],
    secondary_weapons = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 17, 18];
  var gn_len = gangs.length,
    pr_weap_len = primary_weapons.length,
    sc_weap_len = secondary_weapons.length;

  while (true) {
    wait(3000);

    for (var i = 0; i < gn_len; i++) {
      Gang.SetWeapons(
        gangs[i],
        primary_weapons[Math.RandomIntInRange(0, pr_weap_len)],
        secondary_weapons[Math.RandomIntInRange(0, sc_weap_len)]
      );
    }
  }
} else {
  log("Sorry, this script is for GTA VC only")
}
