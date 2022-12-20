use version_info;
lazy_static! {
    pub static ref IMAGE_BASE: usize =
        unsafe { winapi::um::libloaderapi::GetModuleHandleA(std::ptr::null()) as usize };
}

#[macro_export]
macro_rules! detour {
    ( $addr: expr => $cb: expr ) => {{
        let hook = detour::RawDetour::new($addr as *const (), $cb as *const ()).unwrap();
        hook.enable().unwrap();
        let result = std::mem::transmute(hook.trampoline());
        std::mem::forget(hook);
        result
    }};
}

pub fn get_exe_version(exe_name: &str) -> Option<(u32, u32, u32, u32)> {
    version_info::get_file_version(exe_name)
}
