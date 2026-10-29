#pragma once

namespace audio
{
    // audio.ini
    //
    //   AudioDevice=-1            -1 = system default, otherwise a BASS device index
    //   MasterVolumeSfx=1.0       plugin masters, applied by stream type (1.0 = as
    //   MasterVolumeMusic=1.0     loud as the game; the in-game sliders multiply on)
    //
    struct Config
    {
        int audioDevice         = -1;
        float masterVolumeSfx   = 1.0f;
        float masterVolumeMusic = 1.0f;

        bool Load(const char* path);

        bool loaded = false;
    };
} // namespace audio
