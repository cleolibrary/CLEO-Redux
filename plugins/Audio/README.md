# Audio

Port of CLEO5's `SA.Audio` plugin for CLEO Redux: play `.mp3` and `.wav` files with 2D or 3D sound, from JS/TS scripts. Powered by [BASS](https://www.un4seen.com/bass.html).

## Install

- Copy `bass.dll` (at least 2.4.18.3) next to `cleo_redux.asi`. For 64-bit hosts, use `bass64.dll` instead.
- Copy `Audio.cleo` (`Audio64.cleo` for 64-bit hosts) into `cleo\cleo_plugins\`.

Optionally create [`audio.ini`](#audioini) to tweak the audio device and master volume.

## Feature Matrix

| Feature                               | III / VC / SA 1.0              | III / VC / SA DE | Other Games      |
| ------------------------------------- | ------------------------------ | ---------------- | ---------------- |
| 2D playback, all formats, URL streams | yes                            | yes              | yes              |
| Volume                                | dynamic based on in-game audio | same             | only `audio.ini` |
| Slow motion changes pitch             | yes                            | yes              | no               |
| 3D sound with live listener           | yes                            | yes              | no               |
| `AT_CHAR` / `AT_CAR` / `AT_OBJECT`    | yes                            | yes              | no               |
| Pause / menu freeze                   | yes                            | yes              | yes              |

GTA SA 1.0 US is the only SA build the plugin knows addresses for; other SA builds are not supported and fall back to `audio.ini` only, with 2D playback.

## Example Usage

```js
const music = AudioStream.Load("cleo\\music.mp3");
if (music) {
  music.setType(AudioStreamType.Music); // AudioStreamType.Music
  music.setLooped(true);
  music.setVolume(0.8);
  music.setState(AudioStreamAction.Play);
}

// 3D: attach to a car, or pin to coordinates
const horn = AudioStream3D.Load("cleo\\horn.wav");
horn.setPlayAtCoords(100.0, 200.0, 12.5);
horn.setSourceSize(2.0);
horn.setState(AudioStreamAction.Play);
```

Documentation: https://library.sannybuilder.com/#/unknown_x86/script/extensions/audio

## Demo

See `examples/audio_demo.ts`.

To try in the game, copy `audio_demo.mp3` and `audio_demo.ts` to the CLEO folder (`<game>\cleo\`) and run the game. Press keys `1` through `9` to play different audio demos. Make sure to install the Input plugin (`Input.cleo` / `Input64.cleo` in `cleo_plugins`).

`examples/audio_demo.mp3` is "Improvisation with Sopranino Recorder (2015)" by piermic, released under CC0 1.0 (public domain): https://freesound.org/people/piermic/sounds/324085/

## audio.ini

Optional configuration file located in `cleo\cleo_plugins\`. Let's you set the audio device and master volume for SFX and Music streams.

```ini
AudioDevice=-1        ; -1 = system default, otherwise a BASS device number
MasterVolumeSfx=1.0   ; for SFX streams, 0.0 = muted, 1.0 = as loud as the game
MasterVolumeMusic=1.0 ; for Music streams, 0.0 = muted, 1.0 = as loud as the game
```
