pub const SDK_STRING_MAX_LEN: usize = 128;

#[allow(non_camel_case_types)]
#[repr(C)]
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
pub enum HostId {
    RE3 = 1,
    REVC = 2,
    GTA3 = 3,
    VC = 4,
    SA = 5,
    GTA3_UNREAL = 6,
    VC_UNREAL = 7,
    SA_UNREAL = 8,
    UNKNOWN = 255,
}

#[allow(non_camel_case_types)]
type c_char = i8;
pub type Context = *const std::ffi::c_void;
pub type CustomCommand = extern "C" fn(Context) -> HandlerResult;

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
extern "C" {
    /// since v1
    ///
    /// Returns the current SDK version as an integer number.
    fn GetSDKVersion() -> i32;
    /// since v1
    ///
    /// Returns the current host (game) id
    fn GetHostId() -> HostId;
    /// since v1
    ///
    /// Resolves a path to the absolute path
    ///     - absolute path gets resolved as is
    /// - path starting with "CLEO/" gets resolved relative to the CLEO directory
    ///    * either {game}\CLEO or
    ///    * {user}\AppData\Roaming\CLEO Redux\CLEO
    ///  - all other paths get resolved relative to the cwd (game directory)
    fn ResolvePath(src: *const c_char, dest: *mut c_char);
    /// since v1
    ///
    /// Returns the absolute path to the CLEO directory
    fn GetCLEOFolder(dest: *mut c_char);
    /// since v1
    ///
    /// Returns the absolute path to the current working directory (normally the game directory)
    fn GetCwd(dest: *mut c_char);
    /// since v1
    ///
    /// Prints a new entry to the cleo_redux.log
    fn Log(text: *const c_char);
    /// since v1
    ///
    /// Registers a new callback handler for the command with the given name. Permission token is required for unsafe operations interacting with the user environment (e.g. mem, fs, net)
    fn RegisterCommand(name: *const c_char, cb: CustomCommand, permission: *const c_char);
    /// since v1
    ///
    /// Reads an integer argument (either 32 or 64 bit depending on the target platform) from the script input
    fn GetIntParam(ctx: Context) -> isize;
    /// since v1
    ///
    /// Reads a floating-point argument from the script input
    fn GetFloatParam(ctx: Context) -> f32;
    /// since v1
    ///
    /// Copies atmost {maxlen} bytes of a UTF-8 encoded character sequence in the script input to {dest}
    fn GetStringParam(ctx: Context, dest: *mut c_char, maxlen: u8);
    /// since v1
    ///
    /// Writes the integer {value} (either 32 or 64 bit depending on the target platform) to the script output
    fn SetIntParam(ctx: Context, value: isize);
    /// since v1
    ///
    /// Writes the floating-point {value} to the script output
    fn SetFloatParam(ctx: Context, value: f32);
    /// since v1
    ///
    /// Copies a null-terminated UTF-8 encoded character sequence from {src} to the script output
    fn SetStringParam(ctx: Context, src: *const c_char);
    /// since v1
    ///
    /// Sets the status of the current condition
    fn UpdateCompareFlag(ctx: Context, result: bool);
    /// since v2
    ///
    /// Copies atmost {maxlen} bytes of a UTF-8 encoded host name to {dest}
    fn GetHostName(dest: *mut c_char, maxlen: u8);
    /// since v2
    ///
    /// Sets the new host name (available in scripts as the HOST constant)
    fn SetHostName(src: *const c_char);
    /// since v2
    ///
    /// Initializes or reloads CLEO runtime
    fn RuntimeInit();
    /// since v2
    ///
    /// Iterates the main loop
    fn RuntimeNextTick(current_time: u32, time_step: i32);

}

macro_rules! sz {
    ($name:expr) => {
        std::ffi::CString::new($name).unwrap().as_ptr()
    };
}

/// since v1
///
/// Registers a new callback handler for the command with the given name. Permission token is required for unsafe operations interacting with the user environment (e.g. mem, fs, net)
#[allow(dead_code)]
pub fn register_command(name: &str, cb: CustomCommand, permission: Option<&str>) {
    unsafe {
        match permission {
            Some(token) => RegisterCommand(sz!(name), cb, sz!(token)),
            None => RegisterCommand(sz!(name), cb, std::ptr::null()),
        };
    }
}

/// since v1
///
/// Prints a new entry to the cleo_redux.log
pub fn log<T: Into<Vec<u8>>>(text: T) {
    unsafe { Log(sz!(text)) };
}

/// since v1
///
/// Returns the current SDK version as an integer number.
pub fn get_sdk_version() -> i32 {
    unsafe { GetSDKVersion() }
}

/// since v1
///
/// Returns the current host (game) id
pub fn get_host_id() -> HostId {
    unsafe { GetHostId() }
}

/// since v1
///
/// Reads a string argument
pub fn get_string_param(ctx: Context) -> String {
    let mut buf = [0i8; SDK_STRING_MAX_LEN];
    unsafe { GetStringParam(ctx, buf.as_mut_ptr(), SDK_STRING_MAX_LEN as _) };
    to_rust_string(buf.as_ptr())
}

/// since v1
///
/// Writes the string value
pub fn set_string_param(ctx: Context, value: String) {
    unsafe { SetStringParam(ctx, sz!(value)) };
}

/// since v1
///
/// Reads an integer argument (32 or 64 bit depending on target platform)
pub fn get_int_param(ctx: Context) -> isize {
    unsafe { GetIntParam(ctx) }
}

/// since v1
///
/// Writes the integer value (32 or 64 bit depending on target platform)
pub fn set_int_param(ctx: Context, value: isize) {
    unsafe { SetIntParam(ctx, value) };
}

/// since v1
///
/// Returns the absolute path to the CLEO directory
pub fn get_cleo_folder() -> std::path::PathBuf {
    let mut buf = [0i8; 256];
    unsafe { GetCLEOFolder(buf.as_mut_ptr()) };
    std::path::Path::new(&to_rust_string(buf.as_ptr())).into()
}

/// since v1
///
/// Returns the absolute path to the current working directory (normally the game directory)
pub fn get_cwd() -> std::path::PathBuf {
    let mut buf = [0i8; 256];
    unsafe { GetCwd(buf.as_mut_ptr()) };
    std::path::Path::new(&to_rust_string(buf.as_ptr())).into()
}

/// since v1
///
/// Resolves a path to the absolute path
///     - absolute path gets resolved as is
/// - path starting with "CLEO/" gets resolved relative to the CLEO directory
///    * either {game}\CLEO or
///    * {user}\AppData\Roaming\CLEO Redux\CLEO
///  - all other paths get resolved relative to the cwd (game directory)
pub fn resolve_path(path: &str) -> std::path::PathBuf {
    let mut dest = [0i8; 256];
    unsafe { ResolvePath(sz!(path), dest.as_mut_ptr()) };
    std::path::Path::new(&to_rust_string(dest.as_ptr())).into()
}

/// since v1
///
/// Reads a floating-point argument
pub fn get_float_param(ctx: Context) -> f32 {
    unsafe { GetFloatParam(ctx) }
}

/// since v1
///
/// Writes the floating-point value
pub fn set_float_param(ctx: Context, value: f32) {
    unsafe { SetFloatParam(ctx, value) };
}

/// since v1
///
/// Sets the status of the current condition
pub fn update_compare_flag(ctx: Context, value: bool) {
    unsafe { UpdateCompareFlag(ctx, value) }
}

/// since v2
///
/// Copies atmost {maxlen} bytes of a UTF-8 encoded host name to {dest}
pub fn get_host_name() -> String {
    let mut buf = [0i8; SDK_STRING_MAX_LEN];
    unsafe { GetHostName(buf.as_mut_ptr(), SDK_STRING_MAX_LEN as _) };
    to_rust_string(buf.as_ptr())
}

/// since v2
///
/// Sets the new host name (available in scripts as the HOST constant)
pub fn set_host_name(value: String) {
    unsafe { SetHostName(sz!(value)) };
}

/// since v2
///
/// Initializes or reloads CLEO runtime
pub fn runtime_init() {
    unsafe { RuntimeInit() }
}

/// since v2
///
/// Iterates the main loop
pub fn runtime_next_tick(current_time: u32, time_step: i32) {
    unsafe { RuntimeNextTick(current_time, time_step) }
}

fn to_rust_string(addr: *const i8) -> String {
    unsafe {
        std::ffi::CStr::from_ptr(addr)
            .to_owned()
            .into_string()
            .unwrap_or_default()
    }
}
