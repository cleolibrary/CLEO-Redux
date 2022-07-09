use ctor::*;
#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
extern crate cleo_redux_sdk;

mod r#impl;

#[ctor]
fn init() {
    use cleo_redux_sdk::{
        log, on_after_scripts, on_before_scripts, on_runtime_init, register_command,
    };
    use r#impl::*;

    log("Input plugin 1.2");
    register_command("IS_KEY_PRESSED", is_key_pressed, None);
    register_command("IS_KEY_DOWN", is_key_down, None);
    register_command("IS_KEY_UP", is_key_up, None);
    register_command("GET_LAST_KEY", get_last_key, None);
    register_command("TEST_CHEAT", test_cheat, None);
    register_command("HOLD_KEY", hold_key, None);
    register_command("RELEASE_KEY", release_key, None);

    // update state on host events
    on_before_scripts(on_before_scripts_callback);
    on_after_scripts(on_after_scripts_callback);
    on_runtime_init(on_runtime_init_callback);
}
