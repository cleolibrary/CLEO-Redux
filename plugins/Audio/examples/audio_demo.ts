// in-game demo for the audio plugin (GTA III and VC).
//
// Put this file in <game>/scripts/CLEO/, then start a game
// and press the number keys. Press the same key again to stop a demo.
//
//   1 progress      2 volume       3 volume fade   4 speed
//   5 speed fade    6 3D orbit     7 3D fixed point 8 pause test
//   9 seek
//

const PLAY = 1; // AudioStreamAction.Play
const SFX = 1; // AudioStreamType.Sfx
const MUSIC = 2; // AudioStreamType.Music

const MENU =
  "AUDIO DEMO  press 1-9~n~1 prog  2 vol  3 vol fade~n~4 speed  5 spd fade  6 3D orbit~n~7 point  8 pause  9 seek";

// Audio file to play (check if they exist)
const AUDIO = "audio\\bclosed.mp3";

const KEYS = [49, 50, 51, 52, 53, 54, 55, 56, 57];
let pchar = new Player(0).getChar();

function getPressedNumber(): number {
  for (let i = 0; i < 9; i++) {
    if (pressed(KEYS[i])) return i + 1;
  }
  return 0;
}

while (true) {
  wait(0);
  status(MENU);

  switch (getPressedNumber()) {
    case 1:
      demoProgress();
      break;
    case 2:
      demoVolume();
      break;
    case 3:
      demoVolumeFade();
      break;
    case 4:
      demoSpeed();
      break;
    case 5:
      demoSpeedFade();
      break;
    case 6:
      demo3dOrbit();
      break;
    case 7:
      demo3dPoint();
      break;
    case 8:
      demoPause();
      break;
    case 9:
      demoSeek();
      break;
  }
}

function load2d(): any {
  log(`[audio-demo] load2d=${AUDIO}`);
  return AudioStream.Load(AUDIO);
}

function load3d(): any {
  log(`[audio-demo] load3d=${AUDIO}`);
  return AudioStream3D.Load(AUDIO);
}

function demoProgress(): void {
  log("[audio-demo] 1 progress");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(MUSIC);
  s.setLooped(true);
  s.setState(PLAY);

  TIMERA = 0;
  TIMERB = 0;

  do {
    if (TIMERB > 2000) {
      log("[audio-demo] 1 progress=" + s.getProgress().toFixed(3));
      TIMERB = 0;
    }
    status(`1 PROGRESS  ${pct(s.getProgress())}  ${s.getProgressSeconds().toFixed(2)}/${s.getLength()}s`);
    wait(0);
  } while (TIMERA < 8000 && !pressed(KEYS[0]));

  s.remove();
}

function demoVolume(): void {
  log("[audio-demo] 2 volume");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(SFX);
  s.setLooped(true);
  s.setVolume(1.0);
  s.setState(PLAY);

  TIMERA = 0;
  do {
    let t = TIMERA / 1000.0;
    let v = 0.05 + 0.95 * (1.0 - Math.cos(t * Math.PI)) * 0.5;
    s.setVolume(v);
    status(`2 VOLUME  ${v.toFixed(2)}`);
    wait(0);
  } while (TIMERA < 8000 && !pressed(KEYS[1]));

  s.remove();
}

function demoVolumeFade(): void {
  log("[audio-demo] 3 volume fade");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(SFX);
  s.setLooped(true);
  s.setVolume(1.0);
  s.setState(PLAY);

  TIMERA = 0;
  TIMERB = 0;

  let target = 0.1;
  do {
    if (TIMERB > 1500) {
      target = target > 0.5 ? 0.1 : 1.0;
      s.setVolumeWithTransition(target, 1200);
      TIMERB = 0;
    }
    status(`3 VOLUME FADE: ${target.toFixed(2)}  now ${s.getVolume().toFixed(2)}`);
    wait(0);
  } while (TIMERA < 9000 && !pressed(KEYS[2]));

  s.remove();
}

function demoSpeed(): void {
  log("[audio-demo] 4 speed");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(SFX);
  s.setLooped(true);
  s.setVolume(1.0);
  s.setState(PLAY);

  TIMERA = 0;
  do {
    let t = TIMERA / 1000.0;
    let v = 1.25 + 0.75 * Math.cos(t * Math.PI);
    s.setSpeed(v);
    status(`4 SPEED  ${v.toFixed(2)}x  duration ${s.getDuration().toFixed(2)}s`);
    wait(0);
  } while (TIMERA < 8000 && !pressed(KEYS[3]));

  s.remove();
}

function demoSpeedFade(): void {
  log("[audio-demo] 5 speed fade");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(SFX);
  s.setLooped(true);
  s.setVolume(1.0);
  s.setState(PLAY);

  TIMERA = 0;
  TIMERB = 0;

  let target = 0.5;
  do {
    if (TIMERB > 1500) {
      target = target > 1.0 ? 0.5 : 2.0;
      s.setSpeedWithTransition(target, 1200);
      TIMERB = 0;
    }
    status(`5 SPEED FADE: ${target.toFixed(2)}x  now ${s.getSpeed().toFixed(2)}x`);
    wait(0);
  } while (TIMERA < 9000 && !pressed(KEYS[4]));

  s.remove();
}

function demo3dOrbit(): void {
  log("[audio-demo] 6 3D orbit");
  let s = load3d();
  if (!s) return noAudio();

  s.setType(SFX);
  s.setSourceSize(2.0);
  s.setLooped(true);
  let origin = pchar ? pchar.getCoordinates() : { x: 0.0, y: 0.0, z: 0.0 };
  s.setPlayAtCoords(origin.x, origin.y, origin.z);
  s.setState(PLAY);

  TIMERA = 0;
  TIMERB = 0;
  do {
    let t = TIMERA / 1000.0;
    let p = pchar ? pchar.getCoordinates() : origin;
    let a = t * 0.7;
    let sx = p.x + Math.cos(a) * 6.0;
    let sy = p.y + Math.sin(a) * 6.0;
    let sz = p.z + 0.5;
    s.setPlayAtCoords(sx, sy, sz);

    if (TIMERB > 1000) {
      status(
        `[audio-demo] 6 src=${sx.toFixed(1)},${sy.toFixed(1)},${sz.toFixed(1)} state=${s.getState()} playing=${s.isPlaying()} progress=${s.getProgress().toFixed(3)}`,
      );
      TIMERB = 0;
    }
    status(`6 3D ORBIT  source circles you at 6 m~n~listen for panning and pitch shift`);
    wait(0);
  } while (TIMERA < 14000 && !pressed(KEYS[5]));

  s.remove();
}

function demo3dPoint(): void {
  log("[audio-demo] 7 3D fixed point");
  let s = load3d();
  if (!s) return noAudio();

  let p = pchar ? pchar.getCoordinates() : { x: 0.0, y: 0.0, z: 0.0 };
  let sx = p.x;
  let sy = p.y;
  let sz = p.z;

  s.setType(SFX);
  s.setSourceSize(1.0);
  s.setLooped(true);
  s.setPlayAtCoords(sx, sy, sz);
  s.setState(PLAY);

  TIMERA = 0;

  do {
    let distance = 0.0;
    if (pchar) {
      let q = pchar.getCoordinates();
      let dx = q.x - sx;
      let dy = q.y - sy;
      let dz = q.z - sz;
      distance = Math.sqrt(dx * dx + dy * dy + dz * dz);
    }
    status(`7 3D FIXED POINT  walk away~n~distance ${distance.toFixed(1)} m`);
    wait(0);
  } while (TIMERA < 60000 && !pressed(KEYS[6]));

  s.remove();
}

function demoPause(): void {
  log("[audio-demo] 8 pause test");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(MUSIC);
  s.setLooped(true);
  s.setVolume(0.8);
  s.setState(PLAY);

  TIMERA = 0;
  TIMERB = 0;

  do {
    if (TIMERB > 2000) {
      log("[audio-demo] 8 progress=" + s.getProgress().toFixed(3));
      TIMERB = 0;
    }
    status(`8 PAUSE TEST  ${pct(s.getProgress())}~n~open the pause menu: sound and~n~counter must stop, then resume`);
    wait(0);
  } while (TIMERA < 25000 && !pressed(KEYS[7]));

  s.remove();
}

function demoSeek(): void {
  log("[audio-demo] 9 seek");
  let s = load2d();
  if (!s) return noAudio();

  s.setType(SFX);
  s.setLooped(true);
  s.setVolume(1.0);
  s.setState(PLAY);

  TIMERA = 0;
  TIMERB = 0;
  let step = 0;
  do {
    if (TIMERB > 1500) {
      step = (step + 1) % 3;
      if (step === 0) s.setProgress(0.0);
      else if (step === 1) s.setProgress(0.5);
      else s.setProgressSeconds(s.getLength() * 0.25);
      TIMERB = 0;
    }
    status(`9 SEEK  ${pct(s.getProgress())}  ${s.getProgressSeconds().toFixed(2)}s`);
    wait(0);
  } while (TIMERA < 10000 && !pressed(KEYS[8]));

  s.remove();
}

function pressed(code: number): boolean {
  return Pad.IsKeyDown(code);
}

function status(text: string): void {
  FxtStore.insert("_aud1", text, true);
  Text.PrintNow("_aud1", 200, 1);
}

function noAudio(): void {
  log("[audio-demo] cannot open bclosed.mp3");
  status(`Cannot open audio~n~check if audio\\bclosed.mp3 exists`);
  wait(2500);
}

function pct(value: number): string {
  return (value * 100).toFixed(1) + "%";
}
