#include "SoundSystem.h"

#include <algorithm>
#include <cmath>

#include "AudioStream.h"
#include "AudioStream3D.h"
#include "Log.h"

namespace audio
{
    Vec3 SoundSystem::position;
    Vec3 SoundSystem::direction(0.0f, 1.0f, 0.0f);
    Vec3 SoundSystem::velocity;
    float SoundSystem::timeStep          = 0.02f;
    float SoundSystem::masterSpeed       = 1.0f;
    float SoundSystem::masterVolumeSfx   = 1.0f;
    float SoundSystem::masterVolumeMusic = 1.0f;
    bool SoundSystem::useFloatAudio      = false;

    namespace
    {
        void EnumerateDevices(int& defaultDevice);

        void EnumerateDevices(int& defaultDevice)
        {
            defaultDevice = -1;

            BASS_DEVICEINFO info = {"Unknown device", nullptr, 0};
            for (DWORD index = 0; BASS_GetDeviceInfo(index, &info); ++index)
            {
                const bool enabled = (info.flags & BASS_DEVICE_ENABLED) != 0;
                if ((info.flags & BASS_DEVICE_DEFAULT) && defaultDevice == -1) defaultDevice = static_cast<int>(index);

                LogInfo(
                    "audio device %u: %s%s%s", index, info.name != nullptr ? info.name : "?",
                    enabled ? "" : " (disabled)", (info.flags & BASS_DEVICE_DEFAULT) ? " (default)" : ""
                );
            }
        }
    } // namespace

    SoundSystem::~SoundSystem()
    {
        LogInfo("Finalizing SoundSystem");
        Clear();

        if (initialized)
        {
            BASS_Free();
            initialized = false;
        }

        // Not BassUnload(): this runs during process detach, where FreeLibrary would
        // unload code that may still be referenced. The OS reclaims it.
    }

    bool SoundSystem::Init(const Config& config, const char* asiFolder)
    {
        if (initialized) return true;

        if (!BassLoaded() && !BassLoad(asiFolder))
        {
            LogError("SoundSystem not initialized: BASS library unavailable");
            return false;
        }

        masterVolumeSfx   = config.masterVolumeSfx;
        masterVolumeMusic = config.masterVolumeMusic;
        configVolumeSfx   = config.masterVolumeSfx;
        configVolumeMusic = config.masterVolumeMusic;
        loggedSpeed       = -1.0f;
        loggedSfxScale    = -1.0f;
        loggedMusicScale  = -1.0f;
        loggedAtMs        = 0;

        int defaultDevice = -1;
        EnumerateDevices(defaultDevice);

        int deviceIndex = defaultDevice;

        if (config.audioDevice != -1)
        {
            BASS_DEVICEINFO forcedInfo = {"Unknown device", nullptr, 0};
            if (BASS_GetDeviceInfo(static_cast<DWORD>(config.audioDevice), &forcedInfo) &&
                (forcedInfo.flags & BASS_DEVICE_ENABLED))
            {
                LogInfo("Forcing audio device #%d: %s", config.audioDevice, forcedInfo.name);
                deviceIndex = config.audioDevice;
            }
            else
            {
                LogWarning("Failed to force audio device #%d; using default #%d", config.audioDevice, deviceIndex);
            }
        }
        else
        {
            LogInfo("Selecting default audio device #%d", deviceIndex);
        }

        BASS_SetConfig(BASS_CONFIG_FLOATDSP, TRUE);

        // A null window lets BASS create its own; the engine never needs the game's.
        HWND window = GetForegroundWindow();

        if (BASS_Init(deviceIndex, 44100, BASS_DEVICE_3D, window, nullptr) && BASS_Set3DFactors(1.0f, 0.0f, 1.0f))
        {
            HSTREAM floatable = BASS_StreamCreate(44100, 1, BASS_SAMPLE_FLOAT, nullptr, nullptr);
            if (floatable)
            {
                useFloatAudio = true;
                BASS_StreamFree(floatable);
            }

            if (BASS_GetInfo(&soundDevice)) LogInfo("BASS output: %d Hz", soundDevice.freq);

            initialized = true;
            LogInfo(
                "SoundSystem initialized (float audio: %s, master SFX %.2f, master music %.2f)",
                useFloatAudio ? "yes" : "no", masterVolumeSfx, masterVolumeMusic
            );
            return true;
        }

        LogError("Could not initialize BASS sound system. Error code: %d", BASS_ErrorGetCode());
        return false;
    }

    void SoundSystem::Process(const IGameState& state, bool isPaused, unsigned int currentTimeMs, float frameTimeMs)
    {
        if (!initialized) return;

        if (isPaused)
        {
            if (!paused) Pause();
            return;
        }

        if (paused) Resume();

        // The timer delta when there is one (as CLEO5 does), otherwise the callback's
        // frame time.
        const unsigned int now = currentTimeMs;
        float deltaSeconds     = 0.0f;

        if (previousTimeMs != 0 && now > previousTimeMs)
            deltaSeconds = 0.001f * static_cast<float>(now - previousTimeMs);
        else if (frameTimeMs > 0.0f)
            deltaSeconds = 0.001f * frameTimeMs;

        previousTimeMs = now;
        timeStep       = std::clamp(deltaSeconds, 0.0f, 1.0f); // no huge jump after a load

        masterSpeed = std::clamp(state.timeScale(), 0.0f, 10.0f);

        float sfxScale   = 1.0f;
        float musicScale = 1.0f;

        if (const auto mix = state.mix())
        {
            sfxScale   = mix->sfxVolume;
            musicScale = mix->musicVolume;
        }

        masterVolumeSfx   = configVolumeSfx * sfxScale;
        masterVolumeMusic = configVolumeMusic * musicScale;

        // The only way to observe the mix from outside the game; at most twice a
        // second, and only when something moved.
        const bool mixChanged = std::abs(masterSpeed - loggedSpeed) > 0.01f ||
                                std::abs(sfxScale - loggedSfxScale) > 0.01f ||
                                std::abs(musicScale - loggedMusicScale) > 0.01f;

        if (mixChanged && (loggedSpeed < 0.0f || now - loggedAtMs >= 500))
        {
            LogInfo(
                "Audio plugin: mix timeScale=%.3f sfx=%.3f music=%.3f (master sfx %.3f music %.3f)", masterSpeed,
                sfxScale, musicScale, masterVolumeSfx, masterVolumeMusic
            );
            loggedSpeed      = masterSpeed;
            loggedSfxScale   = sfxScale;
            loggedMusicScale = musicScale;
            loggedAtMs       = now;
        }

        // Builds we cannot read a camera from still get 2D playback.
        const auto camera  = state.camera();
        bool listenerValid = false;

        if (camera.has_value())
        {
            // No fresh listener position on a camera cut. The remasters cannot report
            // the switch, so ComputeListenerVelocity() also drops a teleporting frame.
            const bool skipFrame = state.cameraJustChanged();

            velocity =
                skipFrame
                    ? Vec3()
                    : ComputeListenerVelocity(position, camera->position, velocity, timeStep, haveListenerPosition);

            position             = camera->position;
            direction            = camera->forward;
            listenerValid        = !skipFrame;
            haveListenerPosition = true;

            if (listenerValid)
            {
                auto bassPos = ToBass(position);
                auto bassVel = ToBass(velocity);
                auto bassDir = ToBass(direction);
                auto bassUp  = ToBass(camera->up);
                BASS_Set3DPosition(&bassPos, &bassVel, &bassDir, &bassUp);
            }
        }
        else
        {
            haveListenerPosition = false;
            velocity             = Vec3();
        }

        for (auto stream : streams)
            stream->Process();

        if (listenerValid) BASS_Apply3D();
    }

    AudioStream* SoundSystem::CreateStream(const char* filepath, bool in3d)
    {
        if (!initialized)
        {
            LogWarning("Cannot create audiostream '%s': SoundSystem is not initialized", filepath);
            return nullptr;
        }

        AudioStream* result = in3d ? static_cast<AudioStream*>(new AudioStream3D(filepath))
                                   : static_cast<AudioStream*>(new AudioStream(filepath));
        if (!result->IsOk())
        {
            delete result;
            return nullptr;
        }

        streams.insert(result);
        return result;
    }

    void SoundSystem::DestroyStream(AudioStream* stream)
    {
        if (streams.erase(stream))
            delete stream;
        else
            LogWarning("Unloading of audiostream that is not in the list of loaded streams");
    }

    bool SoundSystem::HasStream(AudioStream* stream) const
    {
        return streams.find(stream) != streams.end();
    }

    void SoundSystem::Clear()
    {
        for (auto stream : streams)
            delete stream;
        streams.clear();

        // Clear() runs on runtime re-init, where the host timers restart.
        previousTimeMs       = 0;
        haveListenerPosition = false;
    }

    void SoundSystem::Pause()
    {
        paused = true;
        for (auto stream : streams)
            stream->Pause(false);
    }

    void SoundSystem::Resume()
    {
        paused = false;
        for (auto stream : streams)
        {
            if (stream->GetState() == AudioStream::Playing) stream->Resume();
        }
    }

    Vec3 ComputeListenerVelocity(
        const Vec3& previousPosition, const Vec3& newPosition, const Vec3& previousVelocity, float timeStep,
        bool havePreviousPosition
    )
    {
        // The first frame has nothing to compare against, and a stalled frame has no
        // usable time step.
        if (!havePreviousPosition || timeStep <= 0.0f) return Vec3();

        const Vec3 delta = newPosition - previousPosition;

        // A camera cut is not a velocity (see the declaration in SoundSystem.h).
        if (delta.magnitude() > kMaxListenerJump) return Vec3();

        Vec3 frameVelocity = delta / timeStep;

        const float speed = frameVelocity.magnitude();
        if (speed > kMaxListenerSpeed) frameVelocity = frameVelocity * (kMaxListenerSpeed / speed);

        // Smooths the jitter of a mouse-driven camera.
        return (previousVelocity * 2.0f + frameVelocity) / 3.0f;
    }
} // namespace audio
