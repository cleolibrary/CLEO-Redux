#define _CRT_SECURE_NO_WARNINGS

#include "Config.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "Log.h"

namespace audio
{
    namespace
    {
        std::string Trim(const std::string& text);
        bool EqualsIgnoreCase(const std::string& left, const char* right);
        bool ParseFloat(const std::string& text, float& value);
        bool ParseInt(const std::string& text, int& value);
        void WarnInvalid(int lineNumber, const std::string& key, const std::string& value);

        std::string Trim(const std::string& text)
        {
            size_t first = 0;
            while (first < text.size() && std::isspace(static_cast<unsigned char>(text[first])))
                ++first;

            size_t last = text.size();
            while (last > first && std::isspace(static_cast<unsigned char>(text[last - 1])))
                --last;

            return text.substr(first, last - first);
        }

        bool EqualsIgnoreCase(const std::string& left, const char* right)
        {
            const size_t length = std::strlen(right);
            if (left.size() != length) return false;

            for (size_t i = 0; i < length; ++i)
            {
                if (std::tolower(static_cast<unsigned char>(left[i])) !=
                    std::tolower(static_cast<unsigned char>(right[i])))
                    return false;
            }
            return true;
        }

        bool ParseFloat(const std::string& text, float& value)
        {
            if (text.empty()) return false;

            char* end           = nullptr;
            const double parsed = std::strtod(text.c_str(), &end);
            if (end == text.c_str() || *end != '\0') return false;

            value = static_cast<float>(parsed);
            return true;
        }

        bool ParseInt(const std::string& text, int& value)
        {
            if (text.empty()) return false;

            char* end         = nullptr;
            const long parsed = std::strtol(text.c_str(), &end, 10);
            if (end == text.c_str() || *end != '\0') return false;

            value = static_cast<int>(parsed);
            return true;
        }

        void WarnInvalid(int lineNumber, const std::string& key, const std::string& value)
        {
            LogWarning("audio.ini:%d: invalid %s '%s', using default", lineNumber, key.c_str(), value.c_str());
        }
    } // namespace

    bool Config::Load(const char* path)
    {
        loaded = false;

        if (path == nullptr || path[0] == '\0')
        {
            LogWarning("audio.ini path is empty; using defaults");
            return false;
        }

        std::FILE* file = std::fopen(path, "rb");
        if (file == nullptr)
        {
            LogInfo("audio.ini not found at '%s'; using defaults", path);
            return false;
        }

        char line[1024];
        int lineNumber = 0;
        while (std::fgets(line, sizeof(line), file) != nullptr)
        {
            ++lineNumber;

            const std::string text = Trim(line);
            if (text.empty() || text[0] == ';' || text[0] == '#' || text[0] == '[') continue;

            const size_t separator = text.find('=');
            if (separator == std::string::npos)
            {
                LogWarning("audio.ini:%d: expected key=value, ignoring the line", lineNumber);
                continue;
            }

            const std::string key   = Trim(text.substr(0, separator));
            const std::string value = Trim(text.substr(separator + 1));

            if (EqualsIgnoreCase(key, "AudioDevice"))
            {
                int parsed = 0;
                if (ParseInt(value, parsed) && parsed >= -1)
                    audioDevice = parsed;
                else
                    WarnInvalid(lineNumber, key, value);
            }
            else if (EqualsIgnoreCase(key, "MasterVolumeSfx"))
            {
                float parsed = 0.0f;
                if (ParseFloat(value, parsed) && parsed >= 0.0f)
                    masterVolumeSfx = parsed;
                else
                    WarnInvalid(lineNumber, key, value);
            }
            else if (EqualsIgnoreCase(key, "MasterVolumeMusic"))
            {
                float parsed = 0.0f;
                if (ParseFloat(value, parsed) && parsed >= 0.0f)
                    masterVolumeMusic = parsed;
                else
                    WarnInvalid(lineNumber, key, value);
            }
            else
            {
                LogWarning("audio.ini:%d: unknown key '%s'", lineNumber, key.c_str());
            }
        }

        std::fclose(file);
        loaded = true;

        LogInfo(
            "audio.ini loaded: AudioDevice=%d MasterVolumeSfx=%.2f MasterVolumeMusic=%.2f", audioDevice,
            masterVolumeSfx, masterVolumeMusic
        );
        return true;
    }
} // namespace audio
