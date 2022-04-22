#pragma once
#include <stdint.h>

#define STR_MAX_LEN 128

enum class HandlerResult
{
	// Proceed to the next command
	CONTINUE = 0,
	// Pause the script and continue on the next game loop iteration
	BREAK = 1,
	// End the script gracefully
	TERMINATE = 2,
	// End the script and throw an error
	ERR = -1
};

enum class HostId
{
	RE3 = 1,
	REVC = 2,
	GTA3 = 3,
	VC = 4,
	SA = 5,
	GTA3_UNREAL = 6,
	VC_UNREAL = 7,
	SA_UNREAL = 8,
	UNKNOWN = 255
};

typedef void* Context;
typedef HandlerResult (*CommandHandler)(Context);
typedef intptr_t isize;

extern "C" {
	// since v1
	// Returns the current SDK version as an integer number.
	long GetSDKVersion();
	// since v1
	// Returns the current host (game) id
	HostId GetHostId();
	// since v1
	// Resolves a path to the absolute path
	void ResolvePath(const char* src, char* dest);
	// since v1
	// Returns the absolute path to the CLEO directory
	void GetCLEOFolder(char* dest);
	// since v1
	// Returns the absolute path to the current working directory (normally the game directory)
	void GetCwd(char* dest);
	// since v1
	// Prints a new entry to the cleo_redux.log
	void Log(const char* text);
	// since v1
	// Registers a new callback handler for the command with the given name. Permission token is required for unsafe operations interacting with the user environment (e.g. mem, fs, net)
	void RegisterCommand(const char* name, CommandHandler handler, const char* permission = nullptr);
	// since v1
	// Reads an integer argument (either 32 or 64 bit depending on the target platform) from the script input
    isize GetIntParam(Context ctx);
	// since v1
	// Reads a floating-point argument from the script input
    float GetFloatParam(Context ctx);
	// since v1
	// Copies atmost {maxlen} bytes of a UTF-8 encoded character sequence in the script input to {dest}
	void GetStringParam(Context ctx, char* dest, unsigned char maxlen);
	// since v1
	// Writes the integer {value} (either 32 or 64 bit depending on the target platform) to the script output
    void SetIntParam(Context ctx, isize value);
	// since v1
	// Writes the floating-point {value} to the script output
    void SetFloatParam(Context ctx, float value);
	// since v1
	// Copies a null-terminated UTF-8 encoded character sequence from {src} to the script output
    void SetStringParam(Context ctx, const char* src);
	// since v1
	// Sets the status of the current condition
	void UpdateCompareFlag(Context ctx, bool result);
    // since v2
    // Copies atmost {maxlen} bytes of a UTF-8 encoded host name to {dest}
	void GetHostName(char* dest, unsigned char maxlen);
    // since v2
    // Sets the new host name (available in scripts as the HOST constant)
    void SetHostName(const char* src);
    // since v2
    // Initializes or reloads CLEO runtime
    void RuntimeInit();
    // since v2
    // Iterates the main loop
    void RuntimeNextTick(unsigned int current_time, int time_step);
}
