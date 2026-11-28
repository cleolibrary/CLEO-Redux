#include "CommandDispatcher.h"
#include <cfloat>
#include <utility>
#include "engine/AudioStream3D.h"
#include "engine/Log.h"

namespace audio
{
    namespace
    {
        // AudioStreamAction, as scripts see it.
        enum StreamAction
        {
            ActionStop   = 0,
            ActionPlay   = 1,
            ActionPause  = 2,
            ActionResume = 3,
        };

        void WarnNon3d(const char* commandName)
        {
            LogWarning("3D audio stream command '%s' used with a non-3D audio stream; ignored", commandName);
        }
    } // namespace

    CommandDispatcher::CommandDispatcher(SoundSystem& soundSystem_, const IEntityResolver* entities_)
        : soundSystem(soundSystem_), entities(entities_)
    {
    }

    void CommandDispatcher::LoadAudioStream(Context context)
    {
        LoadStream(context, false);
    }

    void CommandDispatcher::Load3dAudioStream(Context context)
    {
        LoadStream(context, true);
    }

    void CommandDispatcher::SetStreamState(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const int action    = static_cast<int>(GetIntParam(context));

        if (stream == nullptr) return;

        switch (action)
        {
        case ActionStop:
            stream->Stop();
            break;
        case ActionPlay:
            stream->Play();
            break;
        case ActionPause:
            stream->Pause();
            break;
        case ActionResume:
            stream->Resume();
            break;
        default:
            LogWarning("Unknown AudioStreamAction (%d); ignored", action);
            break;
        }
    }

    void CommandDispatcher::RemoveStream(Context context)
    {
        auto* stream = reinterpret_cast<AudioStream*>(GetIntParam(context));
        // calling remove on nullptr is a no-op, not an error
        if (stream == nullptr) return;

        soundSystem.DestroyStream(stream);
    }

    void CommandDispatcher::GetStreamLength(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const float length  = stream != nullptr ? stream->GetLength() : 0.0f;

        SetIntParam(context, static_cast<intptr_t>(static_cast<int>(length)));
    }

    void CommandDispatcher::GetStreamState(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const int state =
            stream != nullptr ? static_cast<int>(stream->GetState()) : static_cast<int>(AudioStream::Stopped);

        SetIntParam(context, state);
    }

    void CommandDispatcher::GetStreamVolume(Context context)
    {
        WriteStreamFloat(context, &AudioStream::GetVolume);
    }

    void CommandDispatcher::SetStreamVolume(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const float volume  = GetFloatParam(context);

        if (stream != nullptr) stream->SetVolume(volume);
    }

    void CommandDispatcher::SetStreamLooped(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const bool looped   = GetIntParam(context) != 0;

        if (stream != nullptr) stream->SetLooping(looped);
    }

    void CommandDispatcher::IsStreamPlaying(Context context)
    {
        AudioStream* stream = ReadStream(context);
        UpdateCompareFlag(context, stream != nullptr && stream->GetState() == AudioStream::Playing);
    }

    void CommandDispatcher::GetStreamDuration(Context context)
    {
        AudioStream* stream = ReadStream(context);

        float duration = 0.0f;
        if (stream != nullptr)
        {
            duration          = stream->GetLength();
            const float speed = stream->GetSpeed();

            // At zero speed the stream would never end.
            duration = speed <= 0.0f ? FLT_MAX : duration / speed;
        }

        SetFloatParam(context, duration);
    }

    void CommandDispatcher::GetStreamSpeed(Context context)
    {
        WriteStreamFloat(context, &AudioStream::GetSpeed);
    }

    void CommandDispatcher::SetStreamSpeed(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const float speed   = GetFloatParam(context);

        if (stream != nullptr) stream->SetSpeed(speed);
    }

    void CommandDispatcher::SetStreamVolumeWithTransition(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const float volume  = GetFloatParam(context);
        const float timeMs  = static_cast<float>(GetIntParam(context));

        if (stream != nullptr) stream->SetVolume(volume, 0.001f * timeMs);
    }

    void CommandDispatcher::SetStreamSpeedWithTransition(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const float speed   = GetFloatParam(context);
        const float timeMs  = static_cast<float>(GetIntParam(context));

        if (stream != nullptr) stream->SetSpeed(speed, 0.001f * timeMs);
    }

    void CommandDispatcher::GetStreamProgress(Context context)
    {
        WriteStreamFloat(context, &AudioStream::GetProgress);
    }

    void CommandDispatcher::SetStreamProgress(Context context)
    {
        AudioStream* stream  = ReadStream(context);
        const float progress = GetFloatParam(context);

        if (stream != nullptr) stream->SetProgress(progress);
    }

    void CommandDispatcher::GetStreamProgressSeconds(Context context)
    {
        AudioStream* stream = ReadStream(context);

        float seconds = 0.0f;
        if (stream != nullptr) seconds = stream->GetProgress() * stream->GetLength();

        SetFloatParam(context, seconds);
    }

    void CommandDispatcher::SetStreamProgressSeconds(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const float seconds = GetFloatParam(context);

        if (stream == nullptr) return;

        const float length = stream->GetLength();
        stream->SetProgress(length > 0.0f ? seconds / length : 0.0f);
    }

    void CommandDispatcher::GetStreamType(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const int type = stream != nullptr ? static_cast<int>(stream->GetType()) : static_cast<int>(StreamType::None);

        SetIntParam(context, type);
    }

    void CommandDispatcher::SetStreamType(Context context)
    {
        AudioStream* stream = ReadStream(context);
        const int type      = static_cast<int>(GetIntParam(context));

        if (stream != nullptr) stream->SetType(static_cast<StreamType>(type));
    }

    void CommandDispatcher::SetPlayAtCoords(Context context)
    {
        AudioStream* stream = Read3dStream(context, "SET_PLAY_3D_AUDIO_STREAM_AT_COORDS");

        const float x = GetFloatParam(context);
        const float y = GetFloatParam(context);
        const float z = GetFloatParam(context);

        if (stream != nullptr) stream->Set3dPosition(Vec3(x, y, z));
    }

    void CommandDispatcher::SetPlayAtObject(Context context)
    {
        SetPlayAtEntity(context, EntityKind::Object, "SET_PLAY_3D_AUDIO_STREAM_AT_OBJECT");
    }

    void CommandDispatcher::SetPlayAtChar(Context context)
    {
        SetPlayAtEntity(context, EntityKind::Ped, "SET_PLAY_3D_AUDIO_STREAM_AT_CHAR");
    }

    void CommandDispatcher::SetPlayAtCar(Context context)
    {
        SetPlayAtEntity(context, EntityKind::Vehicle, "SET_PLAY_3D_AUDIO_STREAM_AT_CAR");
    }

    void CommandDispatcher::SetSourceSize(Context context)
    {
        AudioStream* stream = Read3dStream(context, "SET_AUDIO_STREAM_SOURCE_SIZE");
        const float radius  = GetFloatParam(context);

        if (stream != nullptr) stream->Set3dSourceSize(radius);
    }

    void CommandDispatcher::SetPlayAtEntity(Context context, EntityKind kind, const char* commandName)
    {
        AudioStream* stream = Read3dStream(context, commandName);
        const int handle    = static_cast<int>(GetIntParam(context));

        if (stream == nullptr) return;

        if (entities == nullptr)
        {
            if (!warnedUnsupported3d)
            {
                warnedUnsupported3d = true;
                LogWarning("Audio plugin: '%s' is not supported on this host (no entity pools); ignored", commandName);
            }
            return;
        }

        std::unique_ptr<IPlaceable> placeable = entities->Resolve(kind, handle);
        if (placeable == nullptr)
        {
            LogWarning(
                "Audio plugin: '%s' got an invalid %s handle %d; ignored", commandName, EntityKindName(kind), handle
            );
            return;
        }

        // The stream owns the placeable from here on. It reads this host's pools
        // through a reference, so it must not outlive them - and OnRuntimeInit does
        // clear the streams before it replaces the host.
        stream->SetHostOwned(std::move(placeable), Vec3(0.0f, 0.0f, 0.0f));
    }

    void CommandDispatcher::LoadStream(Context context, bool in3d)
    {
        char source[STR_MAX_LEN] = {0};
        // GetStringParam copies at most maxlen bytes and does not terminate, so ask
        // for one less than the buffer and let the zero fill terminate it.
        GetStringParam(context, source, static_cast<unsigned char>(STR_MAX_LEN - 1));

        char resolved[kPathBufferSize] = {0};
        const char* path               = source;

        // A URL goes to BASS as-is; everything else is resolved like any other CLEO
        // file path.
        if (source[0] != '\0' && !IsNetworkSource(source))
        {
            ResolvePath(source, resolved);
            path = resolved;
        }

        AudioStream* stream = soundSystem.CreateStream(path, in3d);

        SetIntParam(context, reinterpret_cast<intptr_t>(stream));
        UpdateCompareFlag(context, stream != nullptr);
    }

    void CommandDispatcher::WriteStreamFloat(Context context, float (AudioStream::*getter)() const)
    {
        AudioStream* stream = ReadStream(context);
        SetFloatParam(context, stream != nullptr ? (stream->*getter)() : 0.0f);
    }

    AudioStream* CommandDispatcher::ReadStream(Context context)
    {
        auto* stream = reinterpret_cast<AudioStream*>(GetIntParam(context));
        if (stream == nullptr) return nullptr;

        if (!soundSystem.HasStream(stream))
        {
            // Stale or forged handle: don't touch the memory.
            LogWarning("Invalid or already closed audio stream handle %p", static_cast<void*>(stream));
            return nullptr;
        }

        return stream;
    }

    AudioStream* CommandDispatcher::Read3dStream(Context context, const char* commandName)
    {
        AudioStream* stream = ReadStream(context);
        if (stream == nullptr) return nullptr;

        if (!stream->Is3d())
        {
            WarnNon3d(commandName);
            return nullptr;
        }

        return stream;
    }
} // namespace audio
