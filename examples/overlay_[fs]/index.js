/// <reference path=".config/sa.d.ts" />
/*
    Basic game overlay
    
    Required,
        CLEO4
        CLEORedux 0.9.3
            ImGuiRedux plugin
            IniFile plugin
    
    Author: Grinch_
*/

// Display Pos 
const DISPLAY_TOP_LEFT = 0
const DISPLAY_TOP_RIGHT = 1
const DISPLAY_BOTTOM_LEFT = 2
const DISPLAY_BOTTOM_RIGHT = 3


var gOffset = 10.0
var gWindowSize = [0, 0]
var gPlayer = new Player(0)
var gPlayerChar = gPlayer.getChar()

// load ini data
var gSelectedPos = IniFile.ReadInt(".\\overlay.ini", "CONFIG", "DISPLAY_POS")
var gShowFPS = IniFile.ReadInt(".\\overlay.ini", "CONFIG", "SHOW_FPS")
var gShowVehInfo = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_VEH_INFO")
var gShowCoord = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_COORD")
var gShowLoc = IniFile.ReadInt("./overlay.ini", "CONFIG", "SHOW_LOCATION")


const CTheZones__FindSmallestZoneForPosition = Memory.Fn.Cdecl(0x572360);
const CText__Get = Memory.Fn.Thiscall(0x6A0050, 0xC1B340)

while (true) 
{   
    if (HOST != "gta3" && HOST != "vc" && HOST != "sa")
    {
        exit("Game Overlay: Unsupported game/ version. Only GTA3, VC and SA v1.0 (Not Definitive Edition) are supported.")
    }
    wait(0) 
    
    ImGui.BeginFrame("GRINCH_OVERLAY")

    // Calc position
    let pos = []
    let displaySize = ImGui.GetDisplaySize()
    if (gSelectedPos == DISPLAY_TOP_LEFT)
        pos = [gOffset, gOffset]

    if (gSelectedPos == DISPLAY_TOP_RIGHT)
        pos = [displaySize.width - gOffset - gWindowSize[0], gOffset]

    if (gSelectedPos == DISPLAY_BOTTOM_LEFT)
        pos = [gOffset, displaySize.height - gOffset - gWindowSize[1]]

    if (gSelectedPos == DISPLAY_BOTTOM_RIGHT)
        pos = [displaySize.width - gOffset - gWindowSize[0], displaySize.height - gOffset - gWindowSize[1]]


    // ImGui Window
    ImGui.SetNextWindowPos(pos[0], pos[1], 1)
    ImGui.SetNextWindowTransparency(0.5)

    ImGui.Begin("Overlay", true, true, true, false, true)
    gWindowSize = [ImGui.GetWindowSize()]

    if (gShowCoord)
    {
        let coord = gPlayerChar.getCoordinates()
        ImGui.Text("Coord: " + coord.x.toFixed(0) + ", " + coord.y.toFixed(0) + ", " + coord.z.toFixed(0))
    }

    if (gShowFPS)
        ImGui.Text("Frames: " + Game.GetFramerate())

    if (gShowLoc)
    {
        if (HOST == "sa")
        {
            let intID = Streaming.GetAreaVisible()
            let cityID = gPlayer.getCityIsIn()
            let townName = ""
            let cityName = ""

            switch (cityID)
            {
            case 0:
                townName = "CS";
                break;
            case 1:
                townName = "LS";
                break;
            case 2:
                townName = "SF";
                break;
            case 3:
                townName = "LV";
                break;
            default:
                // Set this to SA if player out of bounds 
                townName = "SanAndreas";
            }


            if (intID == 0) // exterior
            {
                let coord = gPlayerChar.getCoordinates()

                let mem = Memory.Allocate(0xC)
                Memory.WriteFloat(mem, coord.x, false)
                Memory.WriteFloat(mem+0x4, coord.y, false)
                Memory.WriteFloat(mem+0x8, coord.z, false)

                let pZone = CTheZones__FindSmallestZoneForPosition(mem, 1)
                let ptr = CText__Get(pZone+0x8)

                for(let i = 0; i < 32; i++)
                {
                    let c = String.fromCharCode(Memory.ReadU8(ptr+i, true))

                    if (c == "\0")
                        break

                    cityName += c
                }

                Memory.Free(mem)
                ImGui.Text("Location: " + cityName + ", " + townName)
            }
            else
            {
                ImGui.Text("Interior: " + intID + ", " + townName)
            }
        }
        else if (HOST == "vc")
        {
            ImGui.Text("Vice City")
        }
        else
        {
            ImGui.Text("Liberty City")
        }
    }

    if (gPlayerChar.isInAnyCar() && gShowVehInfo)
    {
        let hVeh = gPlayerChar.getCarIsUsing()
        ImGui.Text("Veh Health: " + hVeh.getHealth());
        ImGui.Text("Veh Speed: " + hVeh.getSpeed().toFixed(0));
    }

    ImGui.End()
    ImGui.EndFrame()  
}


