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
	ERR = -1,
	// Soft error, the command failed, but script may continue
	FAILED = -2
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
	IV = 9,
	BULLY = 10,
	RELCS = 11,
	REVCS = 12,
	RESA = 13,
	MANIFEST = 254,
	UNKNOWN = 255
};

enum class Directory
{
	// /CLEO directory
	CLEO = 0,
	// /CLEO/.config
	CONFIG = 1,
	// /CLEO/CLEO_TEXT
	TEXT = 2,
	// /CLEO/CLEO_PLUGINS
	PLUGINS = 3,
	// Current working directory
	CWD = 4,
	// Host root directory
	HOST = 5,
	// since v8
	// Directory cleo_redux.asi was loaded from (not necessarily the host directory,
	// an ASI loader may place it in a subfolder)
	ASI = 6,
};

typedef void* Context;
typedef intptr_t isize;

// The type of a command parameter, as seen by a plugin JIT backend.
typedef enum CleoParamType {
	// A 4-byte signed integer (also: engine enums and `name` hashes)
	CLEO_PARAM_INT = 0,
	// A 4-byte IEEE-754 value
	CLEO_PARAM_FLOAT = 1,
	// A 1-byte boolean
	CLEO_PARAM_BOOL = 2,
	// A REDengine-style string value
	CLEO_PARAM_STRING = 3,
	// A vector; `size` is the element count (usually 3)
	CLEO_PARAM_VECTOR = 4,
	// A class instance (a handle); `class_name` names the declared class
	CLEO_PARAM_HANDLE = 5,
	// An unclassified value
	CLEO_PARAM_ANY = 6,
	// A value this ABI cannot pass (arrays, structs, out parameters)
	CLEO_PARAM_UNSUPPORTED = 7
} CleoParamType;

typedef struct CleoParam {
	CleoParamType type;
	// NUL-terminated class name when type is HANDLE/ANY; NULL otherwise
	const char* class_name;
	// Element count for a VECTOR; 0 otherwise
	uint32_t size;
} CleoParam;

// A borrowed view of a command, valid only for the CleoJitBackend::create call.
typedef struct CleoCommand {
	const char* name;
	const char* member;
	int32_t is_static;
	int32_t is_condition;
	const CleoParam* inputs;
	uint32_t input_count;
	const CleoParam* outputs;
	uint32_t output_count;
} CleoCommand;

typedef void* JitState;

// The vtable a plugin installs with RegisterJitBackend. `abi_version` must match
// the value the running CLEO Redux build expects (currently 1).
typedef struct CleoJitBackend {
	uint32_t abi_version;
	JitState (*create)(const CleoCommand* command);
	void (*destroy)(JitState state);
	void (*input_int)(JitState state, int64_t value);
	void (*input_float)(JitState state, float value);
	void (*input_string)(JitState state, const char* value);
	void (*input_vector)(JitState state, float x, float y, float z);
	void (*input_global_var)(JitState state, uint64_t index);
	void (*end_of_arguments)(JitState state);
	void (*before_alloc)(JitState state);
	void (*alloc_int)(JitState state);
	void (*alloc_float)(JitState state);
	void (*alloc_string)(JitState state);
	void (*alloc_vector)(JitState state, uint64_t size);
	int64_t (*get_int)(JitState state, uint64_t index);
	float (*get_float)(JitState state, uint64_t index);
	// Copies a NUL-terminated result string into dest (at most max_len bytes)
	void (*get_string)(JitState state, uint64_t index, char* dest, uint64_t max_len);
	int64_t (*get_handle)(JitState state, uint64_t index);
	HandlerResult (*execute)(JitState state, const char* command_name);
} CleoJitBackend;

typedef HandlerResult (*CommandHandler)(Context);
typedef void* (*CustomLoader)(const char*);
typedef void (*OnTickCallback)(unsigned int current_time, int time_step);
typedef void (*OnGameProcessCallback)(unsigned int current_time, int time_step, bool is_paused, bool is_restarting);
typedef void (*OnRuntimeInitCallback)();
typedef void (*OnShowTextBoxCallback)(const char*);

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
	// deprecated: use GetDirectoryPath
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
	// since v3
	// Registers a new loader for files matching a glob pattern
	void RegisterLoader(const char* glob, CustomLoader loader);
	// since v3
	// Allocates a memory chunk with size in bytes. Memory is guaranteed to be zero initialized
	void* AllocMem(size_t size);
	// since v3
	// Frees up the memory chunk allocated with AllocMem
	void FreeMem(void *ptr);
	// since v4
	// Registers a new callback invoked on each main loop iteration (before scripts are executed)
	void OnBeforeScripts(OnTickCallback callback);
	// since v4
	// Registers a new callback invoked on each main loop iteration (after scripts are executed)
	void OnAfterScripts(OnTickCallback callback);
	// since v8
	// Registers a new callback invoked on every game loop iteration (before CGame::Process), including frames where scripts are not executed (e.g. while the game is paused).
	// is_paused mirrors CTimer::m_UserPause || CTimer::m_CodePause; is_restarting is true when the runtime is being (re)initialized.
	void OnBeforeGameProcess(OnGameProcessCallback callback);
	// since v8
	// Registers a new callback invoked on every game loop iteration (after CGame::Process), including frames where scripts are not executed (e.g. while the game is paused).
	// is_paused mirrors CTimer::m_UserPause || CTimer::m_CodePause; is_restarting is true when the runtime is being (re)initialized.
	void OnAfterGameProcess(OnGameProcessCallback callback);
	// since v4
	// Registers a new callback invoked on each runtime init event (new game, saved game load, or SDK's RuntimeInit)
    void OnRuntimeInit(OnRuntimeInitCallback callback);
	// since v5
	// Registers a new callback invoked on a ShowTextBox function call. Providing a callback shadows built-in ShowTextBox implementation.
    void OnShowTextBox(OnShowTextBoxCallback callback);
    /// since v6
	/// Returns the absolute path to the CLEO root directory, one of its sub-directories, or the directory cleo_redux.asi was loaded from
    void GetDirectoryPath(Directory dir, char* dest);
    /// since v6
    /// Returns CLEO Redux version as a string
    void GetCLEOVersion(char* dest);
    /// since v6
    /// Returns a memory address for the given symbol, or 0 if not found
    void* GetSymbolAddress(const char* symbol);
    /// since v6
    /// Returns number of active CS scripts
    size_t GetNumberOfActiveCSScripts();
    /// since v6
    /// Returns number of active JS scripts
    size_t GetNumberOfActiveJSScripts();
	/// since v6
	/// Is end of arguments reached
	bool IsEndOfArguments(Context ctx);
	/// since v7
	/// Triggers an event with the given name and data
	void TriggerEvent(const char* name, const char* data);
	/// since v8
	/// Registers a JIT backend for the given host name. The backend owns every
	/// command of that host and takes precedence over individually registered
	/// commands. The backend struct must stay valid for the lifetime of the process.
	void RegisterJitBackend(const char* host_name, const CleoJitBackend* backend);
}

