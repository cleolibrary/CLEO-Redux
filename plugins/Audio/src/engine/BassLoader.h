#pragma once

// Dynamic BASS binding: the plugin never links bass.lib. The DLL is looked up next to
// cleo_redux.asi (the SDK's Directory::ASI) and then through the normal search order;
// without it the plugin still loads and every audio call becomes a no-op.

#ifndef NOMINMAX
#define NOMINMAX // std::min/std::max must not be macro-expanded
#endif
#include <windows.h>

#define NOBASSOVERLOADS // no wide-string inline overloads
#include "bass.h"

namespace audio
{
    struct BassApi
    {
        HMODULE module = nullptr;
        DWORD version  = 0;

        decltype(&::BASS_GetVersion) GetVersion     = nullptr;
        decltype(&::BASS_ErrorGetCode) ErrorGetCode = nullptr;

        decltype(&::BASS_SetConfig) SetConfig         = nullptr;
        decltype(&::BASS_GetDeviceInfo) GetDeviceInfo = nullptr;
        decltype(&::BASS_Init) Init                   = nullptr;
        decltype(&::BASS_Free) Free                   = nullptr;
        decltype(&::BASS_GetInfo) GetInfo             = nullptr;

        decltype(&::BASS_Set3DFactors) Set3DFactors   = nullptr;
        decltype(&::BASS_Set3DPosition) Set3DPosition = nullptr;
        decltype(&::BASS_Apply3D) Apply3D             = nullptr;

        decltype(&::BASS_StreamCreate) StreamCreate         = nullptr;
        decltype(&::BASS_StreamCreateFile) StreamCreateFile = nullptr;
        decltype(&::BASS_StreamCreateURL) StreamCreateURL   = nullptr;
        decltype(&::BASS_StreamFree) StreamFree             = nullptr;

        decltype(&::BASS_ChannelGetAttribute) ChannelGetAttribute       = nullptr;
        decltype(&::BASS_ChannelSetAttribute) ChannelSetAttribute       = nullptr;
        decltype(&::BASS_ChannelFlags) ChannelFlags                     = nullptr;
        decltype(&::BASS_ChannelBytes2Seconds) ChannelBytes2Seconds     = nullptr;
        decltype(&::BASS_ChannelSeconds2Bytes) ChannelSeconds2Bytes     = nullptr;
        decltype(&::BASS_ChannelGetLength) ChannelGetLength             = nullptr;
        decltype(&::BASS_ChannelSetPosition) ChannelSetPosition         = nullptr;
        decltype(&::BASS_ChannelGetPosition) ChannelGetPosition         = nullptr;
        decltype(&::BASS_ChannelPlay) ChannelPlay                       = nullptr;
        decltype(&::BASS_ChannelPause) ChannelPause                     = nullptr;
        decltype(&::BASS_ChannelIsActive) ChannelIsActive               = nullptr;
        decltype(&::BASS_ChannelSet3DAttributes) ChannelSet3DAttributes = nullptr;
        decltype(&::BASS_ChannelSet3DPosition) ChannelSet3DPosition     = nullptr;
    };

    extern BassApi g_bass; // all null until BassLoad() succeeds

    // Needs BASS >= 2.4.18.3 (as CLEO5 does). On failure it logs why and returns false;
    // creating a stream then just fails.
    bool BassLoad(const char* asiFolder = nullptr);

    bool BassLoaded();

    // The caller frees its BASS streams first (BASS_Free), and this runs on the game
    // thread - never from a helper thread.
    void BassUnload();
} // namespace audio

#define BASS_GetVersion (audio::g_bass.GetVersion)
#define BASS_ErrorGetCode (audio::g_bass.ErrorGetCode)
#define BASS_SetConfig (audio::g_bass.SetConfig)
#define BASS_GetDeviceInfo (audio::g_bass.GetDeviceInfo)
#define BASS_Init (audio::g_bass.Init)
#define BASS_Free (audio::g_bass.Free)
#define BASS_GetInfo (audio::g_bass.GetInfo)
#define BASS_Set3DFactors (audio::g_bass.Set3DFactors)
#define BASS_Set3DPosition (audio::g_bass.Set3DPosition)
#define BASS_Apply3D (audio::g_bass.Apply3D)
#define BASS_StreamCreate (audio::g_bass.StreamCreate)
#define BASS_StreamCreateFile (audio::g_bass.StreamCreateFile)
#define BASS_StreamCreateURL (audio::g_bass.StreamCreateURL)
#define BASS_StreamFree (audio::g_bass.StreamFree)
#define BASS_ChannelGetAttribute (audio::g_bass.ChannelGetAttribute)
#define BASS_ChannelSetAttribute (audio::g_bass.ChannelSetAttribute)
#define BASS_ChannelFlags (audio::g_bass.ChannelFlags)
#define BASS_ChannelBytes2Seconds (audio::g_bass.ChannelBytes2Seconds)
#define BASS_ChannelSeconds2Bytes (audio::g_bass.ChannelSeconds2Bytes)
#define BASS_ChannelGetLength (audio::g_bass.ChannelGetLength)
#define BASS_ChannelSetPosition (audio::g_bass.ChannelSetPosition)
#define BASS_ChannelGetPosition (audio::g_bass.ChannelGetPosition)
#define BASS_ChannelPlay (audio::g_bass.ChannelPlay)
#define BASS_ChannelPause (audio::g_bass.ChannelPause)
#define BASS_ChannelIsActive (audio::g_bass.ChannelIsActive)
#define BASS_ChannelSet3DAttributes (audio::g_bass.ChannelSet3DAttributes)
#define BASS_ChannelSet3DPosition (audio::g_bass.ChannelSet3DPosition)
