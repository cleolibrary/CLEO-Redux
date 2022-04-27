/// <reference path="../.config/sa.d.ts" />
/*
    Basic game overlay

    Required,
        CLEO4
        CLEORedux 0.9.3
            ImGuiRedux plugin
            IniFile plugin

    Author: Grinch_
*/

if (HOST != "gta3" && HOST != "vc" && HOST != "sa") {
  exit(
    "Game Overlay: Unsupported game/ version. Only GTA3, VC and SA v1.0 (Not Definitive Edition) are supported."
  );
}

// Display Pos
const DISPLAY_TOP_LEFT = 0;
const DISPLAY_TOP_RIGHT = 1;
const DISPLAY_BOTTOM_LEFT = 2;
const DISPLAY_BOTTOM_RIGHT = 3;

const gOffset = 10.0;
const gPlayer = new Player(0);
const gPlayerChar = gPlayer.getChar();

// overlay window size
let gWindowSize = [0, 0];

// load ini data
const gSelectedPos = IniFile.ReadInt("./overlay.ini", "CONFIG", "DISPLAY_POS");
const gShowFPS = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_FPS");
const gShowVehInfo = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_VEH_INFO");
const gShowCoord = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_COORD");
const gShowLoc = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_LOCATION");

const CTheZones__FindSmallestZoneForPosition = Memory.Fn.Cdecl(0x572360);
const CText__Get = Memory.Fn.Thiscall(0x6a0050, 0xc1b340);

while (true) {
  wait(0);

  ImGui.BeginFrame("GRINCH_OVERLAY");

  let pos = calcPosition();

  // ImGui Window
  ImGui.SetNextWindowPos(pos[0], pos[1], 1);
  ImGui.SetNextWindowTransparency(0.5);

  ImGui.Begin("Overlay", true, true, true, false, true);
  gWindowSize = [ImGui.GetWindowSize()];

  if (gShowCoord) {
    let coord = gPlayerChar.getCoordinates();
    ImGui.Text(
      `Coord: ${coord.x.toFixed(0)}, ${coord.y.toFixed(0)}, ${coord.z.toFixed(
        0
      )}`
    );
  }

  if (gShowFPS) {
    ImGui.Text("Frames: " + Game.GetFramerate());
  }

  if (gShowLoc) {
    if (HOST == "sa") {
      let intID = Streaming.GetAreaVisible();
      let townName = getTownName();

      if (intID == 0) {
        // exterior
        let coord = gPlayerChar.getCoordinates();

        let mem = Memory.Allocate(0xc);
        Memory.WriteFloat(mem, coord.x, false);
        Memory.WriteFloat(mem + 0x4, coord.y, false);
        Memory.WriteFloat(mem + 0x8, coord.z, false);

        let pZone = CTheZones__FindSmallestZoneForPosition(mem, 1);
        let ptr = CText__Get(pZone + 0x8);

        let cityName = "";
        for (let i = 0; i < 32; i++) {
          let c = String.fromCharCode(Memory.ReadU8(ptr + i, true));

          if (c == "\0") break;

          cityName += c;
        }

        Memory.Free(mem);
        ImGui.Text(`Location: ${cityName}, ${townName}`);
      } else {
        ImGui.Text(`Interior: ${intID}, ${townName}`);
      }
    } else if (HOST == "vc") {
      ImGui.Text("Vice City");
    } else {
      ImGui.Text("Liberty City");
    }
  }

  if (gPlayerChar.isInAnyCar() && gShowVehInfo) {
    let hVeh = gPlayerChar.getCarIsUsing();
    ImGui.Text("Veh Health: " + hVeh.getHealth());
    ImGui.Text("Veh Speed: " + hVeh.getSpeed().toFixed(0));
  }

  ImGui.End();
  ImGui.EndFrame();
}

function calcPosition() {
  let displaySize = ImGui.GetDisplaySize();
  if (gSelectedPos == DISPLAY_TOP_LEFT) {
    return [gOffset, gOffset];
  }

  if (gSelectedPos == DISPLAY_TOP_RIGHT) {
    return [displaySize.width - gOffset - gWindowSize[0], gOffset];
  }

  if (gSelectedPos == DISPLAY_BOTTOM_LEFT) {
    return [gOffset, displaySize.height - gOffset - gWindowSize[1]];
  }

  if (gSelectedPos == DISPLAY_BOTTOM_RIGHT) {
    return [
      displaySize.width - gOffset - gWindowSize[0],
      displaySize.height - gOffset - gWindowSize[1],
    ];
  }
}

function getTownName() {
  let cityID = gPlayer.getCityIsIn();

  switch (cityID) {
    case 0:
      return "CS";
    case 1:
      return "LS";
    case 2:
      return "SF";
    case 3:
      return "LV";
    default:
      // Set this to SA if player out of bounds
      return "SanAndreas";
  }
}
