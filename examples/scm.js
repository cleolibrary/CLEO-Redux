[
  "re3",
  "reVC",
  "gta3",
  "vc",
  "sa",
  "gta3_unreal",
  "vc_unreal",
  "sa_unreal",
].includes(GAME) || exit("Unsupported game");

const mainScm = Memory.Translate("CTheScripts::ScriptSpace");

if (!mainScm) {
  exit("Main.scm address not found");
}

function assert(id) {
  if (typeof id !== "number") {
    throw new Error("Global variable id must be a number");
  }
  if (id < 2 || id > 16383) {
    throw new Error(
      "Global variable is out of range. Use number between 2 and 16383 (0x3FFF)"
    );
  }
}

function readScmVariable(id) {
  assert(id);
  return Memory.ReadI32(mainScm + id * 4, false, false);
}

function writeScmVariable(id, value) {
  assert(id);
  return Memory.WriteI32(mainScm + id * 4, value, false, false);
}

export { readScmVariable, writeScmVariable };
