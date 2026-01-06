// Ide Loader (IdeLoader.cleo, IdeLoader64.cleo)
declare module "*.ide" {
  enum IdeKey {
    _2dfx = "2dfx",
    amat = "amat",
    anim = "anim",
    cars = "cars",
    hier = "hier",
    hand = "hand",
    mlo = "mlo",
    objs = "objs",
    path = "path",
    peds = "peds",
    tanm = "tanm",
    tobj = "tobj",
    tree = "tree",
    txdp = "txdp",
    weap = "weap",
  }
  const value: Record<IdeKey, string[]>;
  export default value;
}

declare module "*.zon" {
  enum ZonKey {
    zone = "zone",
  }
  const value: Record<ZonKey, string[]>;
  export default value;
}