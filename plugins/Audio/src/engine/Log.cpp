#include "Log.h"

#include <cstdarg>
#include <cstdio>

#include "cleo_redux_sdk.h"

namespace audio
{
    namespace
    {
        const char* LevelTag(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Warning:
                return "[WARN] ";
            case LogLevel::Error:
                return "[ERROR] ";
            default:
                return "";
            }
        }

        void Emit(LogLevel level, const char* format, va_list args)
        {
            char buffer[1024];
            const int tag = std::snprintf(buffer, sizeof(buffer), "%s", LevelTag(level));
            std::vsnprintf(buffer + tag, sizeof(buffer) - static_cast<size_t>(tag), format, args);

            ::Log(buffer);
        }
    } // namespace

    void LogInfo(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Emit(LogLevel::Info, format, args);
        va_end(args);
    }

    void LogWarning(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Emit(LogLevel::Warning, format, args);
        va_end(args);
    }

    void LogError(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Emit(LogLevel::Error, format, args);
        va_end(args);
    }
} // namespace audio
