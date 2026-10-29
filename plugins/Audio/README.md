# Audio

Port of CLEO5's `SA.Audio` plugin for CLEO Redux: play `.mp3`, `.wav` and `.ogg` files with 2D or 3D sound, from JS/TS scripts. Powered by [BASS](https://www.un4seen.com/bass.html).

## Install

- Copy `bass.dll` (at least 2.4.18.3) next to `cleo_redux.asi`. For 64-bit hosts, use `bass64.dll` instead.
- Copy `Audio.cleo` (`Audio64.cleo` for 64-bit hosts) into `CLEO/CLEO_PLUGINS/`.

Optionally copy `audio.ini` to tweak the audio device and master volume.

## Host support

| Feature                               | III 1.0 EN                              | VC 1.0 US | III / VC DE | SA DE | Other Games      |
| ------------------------------------- | --------------------------------------- | --------- | ----------- | ----- | ---------------- |
| 2D playback, all formats, URL streams | yes                                     | yes       | yes         | yes   | yes              |
| Volume                                | `audio.ini` × in-game SFX/music sliders | same      | same        | same  | `audio.ini` only |
| Slow motion changes pitch             | yes                                     | yes       | yes         | yes   | no (stays 1.0)   |
| 3D sound with live listener           | yes                                     | yes       | yes         | yes   | no               |
| `AT_CHAR` / `AT_CAR` / `AT_OBJECT`    | yes                                     | yes       | yes         | yes   | no               |
| Pause / menu freeze                   | yes                                     | yes       | yes         | yes   | yes              |

For GTA SA 1.0 it is recommended to use CLEO5's `SA.Audio` plugin instead.

## Example Usage

```js
const music = AudioStream.Load("CLEO\\music.mp3");
if (music) {
  music.setType(AudioStreamType.Music); // AudioStreamType.Music
  music.setLooped(true);
  music.setVolume(0.8);
  music.setState(AudioStreamAction.Play);
}

// 3D: attach to a car, or pin to coordinates
const horn = AudioStream3D.Load("CLEO\\horn.wav");
horn.setPlayAtCoords(100.0, 200.0, 12.5);
horn.setSourceSize(2.0);
horn.setState(AudioStreamAction.Play);
```

Documentation: https://library.sannybuilder.com/#/unknown_x86/script/extensions/audio

## In-game demo

See `examples/audio_demo.ts`. Drop it in the CLEO folder, put `bclosed.mp3` in `<game>/audio/`, install the Input plugin (`Input.cleo` / `Input64.cleo` in `CLEO_PLUGINS`) because the demo uses `Pad.IsKeyDown`, start a game and press the number keys; the same key again stops a demo.

```
1 progress   2 volume   3 volume fade   4 speed   5 speed fade
6 3D orbit   7 3D fixed point   8 pause test   9 seek
```

## audio.ini

Sits next to the plugin. All keys optional:

```ini
AudioDevice=-1     ; -1 = system default, otherwise a BASS device number
MasterVolumeSfx=1.0
MasterVolumeMusic=1.0
```

SFX streams follow the in-game SFX volume, Music streams follow the music volume.

The `MasterVolume*` values multiply on top of that (`1.0` = as loud as the game), so raise them for louder-than-game plugins.
