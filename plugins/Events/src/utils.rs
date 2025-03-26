
#[macro_export]
macro_rules! detour {
    ( $addr: expr => $cb: expr ) => {{
        let hook = minhook::MinHook::create_hook($addr as _, $cb as _).unwrap();
        minhook::MinHook::enable_hook($addr as _).unwrap();
        let result = std::mem::transmute(hook);
        result
    }};
}
