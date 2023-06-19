
#[macro_export]
macro_rules! detour {
    ( $addr: expr => $cb: expr ) => {{
        let hook = retour::RawDetour::new($addr as *const (), $cb as *const ()).unwrap();
        hook.enable().unwrap();
        let result = std::mem::transmute(hook.trampoline());
        std::mem::forget(hook);
        result
    }};
}
