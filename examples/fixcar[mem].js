/// <reference path=".config/vc.d.ts" />

const LEFTMOUSEBUTTON = 1;
var player = new Player(0);

while (true) {
  if (Pad.IsKeyDown(LEFTMOUSEBUTTON)) {
    if (player.isInAnyCar()) {
      //GET VEHICLE STRUCT USING Memory.GetVehiclePointer METHOD. PASS VEHICLE POINTER AS A PARAMETER USING player.storeCarIsInNoSave().
      var vehicle = player.storeCarIsInNoSave();
      var vehicleStruct = Memory.GetVehiclePointer(vehicle);

      //TO GET THE VEHICLE TYPE, WE NEED TO ADD AN OFFSET TO THE VEHICLE POINTER(OFFSET: "0x29c" (https://gtamods.com/wiki/Memory_Addresses_(VC) GO TO THIS ADDRESS AND LOOK AT THE END OF CVEHICLE TABLE.)).
      var vehicleType = Memory.Read(vehicleStruct + 0x29c, 4, false);
      //https://gtamods.com/wiki/Function_Memory_Addresses_(VC) YOU CAN FIND FUNCTION ADDRESSES FROM HERE.
      //MEMORY ADDRESS: 0x588530(for vehicle type = 0) | FUNCTION:Fix((void)) | DESCRIPTION: Completely fixes the car in spray shops. See this(https://gtamods.com/wiki/0A30#For_GTA_III_and_Vice_City) for a practical usage.
      //                0x609f00(for if vehicle type is different than 0)
      /*
        VEHICLE TYPES
        0 = general
        1 = boat
        2 = train (unused)
        3 = NPC police helicopter
        4 = NPC plane
        5 = bike
      */
      if (vehicleType == 0) {
        Memory.CallMethod(0x588530, vehicleStruct, 0, 0);
      } else {
        Memory.CallMethod(0x609f00, vehicleStruct, 0, 0);
      }
      vehicle.setHealth(1000);
    }
  }
  wait(10);
}
