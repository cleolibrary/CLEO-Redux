pub const SDK_STRING_MAX_LEN: usize = 128;

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub enum HandlerResult {
    /// Proceed to the next command
    CONTINUE = 0,
    /// Pause the script and continue on the next game loop iteration
    BREAK = 1,
    /// End the script gracefully
    TERMINATE = 2,
    /// End the script and throw an error
    ERR = -1,
}

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub enum HostId {
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
    MANIFEST = 254,
    UNKNOWN = 255,
}

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub enum Directory {
    /// /CLEO directory
    CLEO = 0,
    /// /CLEO/.config
    CONFIG = 1,
    /// /CLEO/CLEO_TEXT
    TEXT = 2,
    /// /CLEO/CLEO_PLUGINS
    PLUGINS = 3,
    /// Current working directory
    CWD = 4,
    /// Host root directory
    HOST = 5,
}

#[allow(non_camel_case_types)]
pub type c_char = i8;
#[allow(non_camel_case_types)]
pub type c_void = std::ffi::c_void;

pub type Context = *const c_void;
pub type CustomCommand = extern "C" fn(Context) -> HandlerResult;
pub type CustomLoader = extern "C" fn(*const c_char) -> *mut c_void;
pub type OnTickCallback = extern "C" fn(current_time: u32, time_step: i32);
pub type OnRuntimeInitCallback = extern "C" fn();
pub type OnShowTextBoxCallback = extern "C" fn(*const c_char);

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
extern "C" {
    /// Returns the current SDK version as an integer number.
    ///
    /// since v1
    fn GetSDKVersion() -> i32;
    /// Returns the current host (game) id
    ///
    /// since v1
    fn GetHostId() -> HostId;
    /// Resolves a path to the absolute path
    ///     - absolute path gets resolved as is
    /// - path starting with "CLEO/" gets resolved relative to the CLEO directory
    ///    * either {game}\CLEO or
    ///    * {user}\AppData\Roaming\CLEO Redux\CLEO
    ///  - all other paths get resolved relative to the cwd (game directory)
    ///
    /// since v1
    fn ResolvePath(src: *const c_char, dest: *mut c_char);
    /// Returns the absolute path to the CLEO directory
    ///
    /// since v1
    /// deprecated: use GetDirectoryPath
    fn GetCLEOFolder(dest: *mut c_char);
    /// Returns the absolute path to the current working directory (normally the game directory)
    ///
    /// since v1
    fn GetCwd(dest: *mut c_char);
    /// Prints a new entry to the cleo_redux.log
    ///
    /// since v1
    fn Log(text: *const c_char);
    /// Registers a new callback handler for the command with the given name. Permission token is required for unsafe operations interacting with the user environment (e.g. mem, fs, net)
    ///
    /// since v1
    fn RegisterCommand(name: *const c_char, cb: CustomCommand, permission: *const c_char);
    /// Reads an integer argument (either 32 or 64 bit depending on the target platform) from the script input
    ///
    /// since v1
    fn GetIntParam(ctx: Context) -> isize;
    /// Reads a floating-point argument from the script input
    ///
    /// since v1
    fn GetFloatParam(ctx: Context) -> f32;
    /// Copies atmost {maxlen} bytes of a UTF-8 encoded character sequence in the script input to {dest}
    ///
    /// since v1
    fn GetStringParam(ctx: Context, dest: *mut c_char, maxlen: u8);
    /// Writes the integer {value} (either 32 or 64 bit depending on the target platform) to the script output
    ///
    /// since v1
    fn SetIntParam(ctx: Context, value: isize);
    /// Writes the floating-point {value} to the script output
    ///
    /// since v1
    fn SetFloatParam(ctx: Context, value: f32);
    /// Copies a null-terminated UTF-8 encoded character sequence from {src} to the script output
    ///
    /// since v1
    fn SetStringParam(ctx: Context, src: *const c_char);
    /// Sets the status of the current condition
    ///
    /// since v1
    fn UpdateCompareFlag(ctx: Context, result: bool);
    /// Copies atmost {maxlen} bytes of a UTF-8 encoded host name to {dest}
    ///
    /// since v2
    fn GetHostName(dest: *mut c_char, maxlen: u8);
    /// Sets the new host name (available in scripts as the HOST constant)
    ///
    /// since v2
    fn SetHostName(src: *const c_char);
    /// Initializes or reloads CLEO runtime
    ///
    /// since v2
    fn RuntimeInit();
    /// Iterates the main loop
    ///
    /// since v2
    fn RuntimeNextTick(current_time: u32, time_step: i32);
    /// Registers a new loader for files matching a glob pattern
    ///
    /// since v3
    fn RegisterLoader(glob: *const c_char, cb: CustomLoader);
    /// Allocates a memory chunk with size in bytes. Memory is guaranteed to be zero initialized
    ///
    /// since v3
    fn AllocMem(size: usize) -> *mut c_void;
    /// Frees up the memory chunk allocated with AllocMem
    ///
    /// since v3
    fn FreeMem(ptr: *mut c_void);
    /// Registers a new callback invoked on each main loop iteration (before scripts are executed)
    ///
    /// since v4
    fn OnBeforeScripts(cb: OnTickCallback);
    /// Registers a new callback invoked on each main loop iteration (after scripts are executed)
    ///
    /// since v4
    fn OnAfterScripts(cb: OnTickCallback);
    /// Registers a new callback invoked on each runtime init event (new game, saved game load, or SDK's RuntimeInit)
    ///
    /// since v4
    fn OnRuntimeInit(cb: OnRuntimeInitCallback);
    /// Registers a new callback invoked on a ShowTextBox function call. Providing a callback shadows built-in ShowTextBox implementation.
    ///
    /// since v5
    fn OnShowTextBox(cb: OnShowTextBoxCallback);
    /// Returns the absolute path to the CLEO root directory or one of its sub-directories
    ///
    /// since v6
    fn GetDirectoryPath(dir: Directory, dest: *mut c_char);
    /// Returns CLEO Redux version as a string
    ///
    /// since v6
    fn GetCLEOVersion(dest: *mut c_char);
    /// Returns a memory address for the given symbol, or 0 if not found
    ///
    /// since v6
    fn GetSymbolAddress(symbol: *const c_char) -> usize;
    /// Returns number of active CS scripts
    ///
    /// since v6
    fn GetNumberOfActiveCSScripts() -> usize;
    /// Returns number of active JS scripts
    ///
    /// since v6
    fn GetNumberOfActiveJSScripts() -> usize;
    /// Returns true if end of arguments reached
    ///
    /// since v6
    fn IsEndOfArguments(ctx: Context) -> bool;
}

macro_rules! sz {
    ($name:expr) => {
        std::ffi::CString::new($name).unwrap().as_ptr()
    };
}

/// Registers a new callback handler for the command with the given name. Permission token is required for unsafe operations interacting with the user environment (e.g. mem, fs, net)
///
/// since v1
#[allow(dead_code)]
pub fn register_command(name: &str, cb: CustomCommand, permission: Option<&str>) {
    unsafe {
        match permission {
            Some(token) => RegisterCommand(sz!(name), cb, sz!(token)),
            None => RegisterCommand(sz!(name), cb, std::ptr::null()),
        };
    }
}

/// Prints a new entry to the cleo_redux.log
///
/// since v1
pub fn log<T: Into<Vec<u8>>>(text: T) {
    unsafe { Log(sz!(text)) };
}

/// Returns the current SDK version as an integer number.
///
/// since v1
pub fn get_sdk_version() -> i32 {
    unsafe { GetSDKVersion() }
}

/// Returns the current host (game) id
///
/// since v1
pub fn get_host_id() -> HostId {
    unsafe { GetHostId() }
}

/// Reads a string argument
///
/// since v1
pub fn get_string_param(ctx: Context) -> String {
    let mut buf = [0i8; SDK_STRING_MAX_LEN];
    unsafe { GetStringParam(ctx, buf.as_mut_ptr(), SDK_STRING_MAX_LEN as _) };
    to_rust_string(buf.as_ptr())
}

/// Writes the string value
///
/// since v1
pub fn set_string_param(ctx: Context, value: String) {
    unsafe { SetStringParam(ctx, sz!(value)) };
}

/// Reads an integer argument (32 or 64 bit depending on target platform)
///
/// since v1
pub fn get_int_param(ctx: Context) -> isize {
    unsafe { GetIntParam(ctx) }
}

/// Writes the integer value (32 or 64 bit depending on target platform)
///
/// since v1
pub fn set_int_param(ctx: Context, value: isize) {
    unsafe { SetIntParam(ctx, value) };
}

/// Returns the absolute path to the CLEO directory
///
/// since v1
///
/// deprecated: use get_directory_path()
pub fn get_cleo_folder() -> std::path::PathBuf {
    get_directory_path(Directory::CLEO)
}

/// Returns the absolute path to the current working directory (normally the game directory)
///
/// since v1
pub fn get_cwd() -> std::path::PathBuf {
    let mut buf = [0i8; 256];
    unsafe { GetCwd(buf.as_mut_ptr()) };
    std::path::Path::new(&to_rust_string(buf.as_ptr())).into()
}

/// Resolves a path to the absolute path
///     - absolute path gets resolved as is
/// - path starting with "CLEO/" gets resolved relative to the CLEO directory
///    * either {game}\CLEO or
///    * {user}\AppData\Roaming\CLEO Redux\CLEO
///  - all other paths get resolved relative to the cwd (game directory)
///
/// since v1
pub fn resolve_path(path: &str) -> std::path::PathBuf {
    let mut dest = [0i8; 256];
    unsafe { ResolvePath(sz!(path), dest.as_mut_ptr()) };
    std::path::Path::new(&to_rust_string(dest.as_ptr())).into()
}

/// Reads a floating-point argument
///
/// since v1
pub fn get_float_param(ctx: Context) -> f32 {
    unsafe { GetFloatParam(ctx) }
}

/// Writes the floating-point value
///
/// since v1
pub fn set_float_param(ctx: Context, value: f32) {
    unsafe { SetFloatParam(ctx, value) };
}

/// Sets the status of the current condition
///
/// since v1
pub fn update_compare_flag(ctx: Context, value: bool) {
    unsafe { UpdateCompareFlag(ctx, value) }
}

/// Returns a host name
/// The default value matches https://re.cleo.li/docs/en/api.html#host
/// Can be changed with SetHostName
///
/// since v2
pub fn get_host_name() -> String {
    let mut buf = [0i8; SDK_STRING_MAX_LEN];
    unsafe { GetHostName(buf.as_mut_ptr(), SDK_STRING_MAX_LEN as _) };
    to_rust_string(buf.as_ptr())
}

/// Sets the new host name (accessible in scripts via the HOST constant)
///
/// since v2
pub fn set_host_name(value: String) {
    unsafe { SetHostName(sz!(value)) };
}

/// Initializes or reloads CLEO runtime
///
/// since v2
pub fn runtime_init() {
    unsafe { RuntimeInit() }
}

/// Iterates the main loop
///
/// since v2
pub fn runtime_next_tick(current_time: u32, time_step: i32) {
    unsafe { RuntimeNextTick(current_time, time_step) }
}

pub fn to_rust_string(addr: *const i8) -> String {
    unsafe {
        std::ffi::CStr::from_ptr(addr)
            .to_owned()
            .into_string()
            .unwrap_or_default()
    }
}

/// Registers a new loader for files matching a glob pattern
///
/// since v3
#[allow(dead_code)]
pub fn register_loader(glob: &str, cb: CustomLoader) {
    unsafe {
        RegisterLoader(sz!(glob), cb);
    }
}

/// Allocates a memory chunk with size in bytes. Memory is guaranteed to be zero initialized
///
/// since v3
#[allow(dead_code)]
pub fn alloc_mem(size: usize) -> *mut c_void {
    unsafe { AllocMem(size) }
}

/// Frees up the memory chunk allocated with AllocMem
///
/// since v3
#[allow(dead_code)]
pub fn free_mem(ptr: *mut c_void) {
    unsafe { FreeMem(ptr) }
}

/// Registers a new callback invoked on each main loop iteration (before scripts are executed)
///
/// since v4
#[allow(dead_code)]
pub fn on_before_scripts(cb: OnTickCallback) {
    unsafe {
        OnBeforeScripts(cb);
    }
}

/// Registers a new callback invoked on each main loop iteration (after scripts are executed)
///
/// since v4
#[allow(dead_code)]
pub fn on_after_scripts(cb: OnTickCallback) {
    unsafe {
        OnAfterScripts(cb);
    }
}

/// Registers a new callback invoked on each runtime init event (new game, saved game load, or SDK's RuntimeInit)
///
/// since v4
#[allow(dead_code)]
pub fn on_runtime_init(cb: OnRuntimeInitCallback) {
    unsafe {
        OnRuntimeInit(cb);
    }
}

/// Registers a new callback invoked on a ShowTextBox function call. Providing a callback shadows built-in ShowTextBox implementation.
///
/// since v5
#[allow(dead_code)]
pub fn on_show_text_box(cb: OnShowTextBoxCallback) {
    unsafe {
        OnShowTextBox(cb);
    }
}

/// Returns the absolute path to the CLEO root directory or one of its sub-directories
///
/// since v6
#[allow(dead_code)]
pub fn get_directory_path(dir: Directory) -> std::path::PathBuf {
    let mut buf = [0i8; 256];
    unsafe { GetDirectoryPath(dir, buf.as_mut_ptr()) };
    std::path::Path::new(&to_rust_string(buf.as_ptr())).into()
}

/// Returns CLEO Redux version as a string
///
/// since v6
#[allow(dead_code)]
pub fn get_cleo_version() -> String {
    let mut buf = [0i8; 256];
    unsafe { GetCLEOVersion(buf.as_mut_ptr()) };
    to_rust_string(buf.as_ptr())
}

/// Returns a memory address for the given symbol, or 0 if not found
///
/// since v6
#[allow(dead_code)]
pub fn get_symbol_address(symbol: &str) -> usize {
    unsafe { GetSymbolAddress(sz!(symbol)) }
}

/// Get number of active CS scripts
///
/// since v6
#[allow(dead_code)]
pub fn get_number_of_active_cs_scripts() -> usize {
    unsafe { GetNumberOfActiveCSScripts() }
}

/// Get number of active JS scripts
///
/// since v6
#[allow(dead_code)]
pub fn get_number_of_active_js_scripts() -> usize {
    unsafe { GetNumberOfActiveJSScripts() }
}

/// Is end of arguments reached
///
/// since v6
#[allow(dead_code)]
pub fn is_end_of_arguments(ctx: Context) -> bool {
    unsafe { IsEndOfArguments(ctx) }
}
