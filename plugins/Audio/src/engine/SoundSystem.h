#pragma once

#include <set>

#include "BassLoader.h"
#include "Config.h"
#include "GameState.h"
#include "Vec3.h"

namespace audio
{
    class AudioStream;
    // A frame-to-frame listener move larger than this is a camera cut, not movement.
    inline constexpr float kMaxListenerJump = 50.0f; // metres per frame
    // No player camera gets near this, so a stalled frame cannot make doppler scream.
    inline constexpr float kMaxListenerSpeed = 200.0f; // metres per second

    // CLEO5's CSoundSystem, with dynamic BASS and audio.ini masters.
    class SoundSystem
    {
        friend class AudioStream;
        friend class AudioStream3D;

      public:
        SoundSystem() = default;
        ~SoundSystem();

        SoundSystem(const SoundSystem&)            = delete;
        SoundSystem& operator=(const SoundSystem&) = delete;

        bool Init(const Config& config, const char* asiFolder = nullptr);
        bool Initialized() const { return initialized; }

        AudioStream* CreateStream(const char* filepath, bool in3d = false);
        void DestroyStream(AudioStream* stream);

        bool HasStream(AudioStream* stream) const;
        void Clear();

        void Pause();
        void Resume();

        // Pause and time come from CLEO's per-frame callback, which stays correct while
        // paused; `state` supplies the camera, the game speed and the mixer.
        void Process(const IGameState& state, bool isPaused, unsigned int currentTimeMs, float frameTimeMs);

        static Vec3 position;
        static Vec3 direction;
        static Vec3 velocity;
        static float timeStep; // seconds

        // Sfx and Music streams pitch with the game speed, so slow motion sounds slow.
        static float masterSpeed;

        // audio.ini master * in-game slider, or the ini value alone without a mixer.
        static float masterVolumeSfx;
        static float masterVolumeMusic;

        static bool useFloatAudio;

      private:
        std::set<AudioStream*> streams;
        BASS_INFO soundDevice       = {0};
        bool initialized            = false;
        bool paused                 = false;
        unsigned int previousTimeMs = 0;
        bool haveListenerPosition   = false;

        float configVolumeSfx   = 1.0f;
        float configVolumeMusic = 1.0f;

        // Last logged mix, so the line only appears when something changed.
        float loggedSpeed       = -1.0f;
        float loggedSfxScale    = -1.0f;
        float loggedMusicScale  = -1.0f;
        unsigned int loggedAtMs = 0;
    };

    // Game coordinates (X right, Y forward, Z up) -> BASS (X right, Y up, Z forward).
    inline BASS_3DVECTOR ToBass(const Vec3& v)
    {
        return BASS_3DVECTOR(v.x, v.z, v.y);
    }

    // How fast the listener (the player's camera) is moving, which BASS uses to shift
    // pitch - the doppler effect. Smoothed, so a shaky mouse camera does not wobble.
    // Zero on the first frame (nothing to compare against yet) and when the camera
    // jumps: a cutscene, a load or a respawn looks like a huge speed but is not real
    // movement. III/VC report the jump themselves through CameraView::JustChanged; the
    // remasters do not, so there a move bigger than kMaxListenerJump counts as a jump.
    Vec3 ComputeListenerVelocity(
        const Vec3& previousPosition, const Vec3& newPosition, const Vec3& previousVelocity, float timeStep,
        bool havePreviousPosition
    );
} // namespace audio
