#pragma once

// Writes the plugin's lines into CLEO's own log.

namespace audio
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error,
    };

    void LogInfo(const char* format, ...);
    void LogWarning(const char* format, ...);
    void LogError(const char* format, ...);
} // namespace audio
