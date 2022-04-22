use ctor::*;

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
extern crate cleo_redux_sdk;

mod r#impl;

#[ctor]
fn init() {
    use cleo_redux_sdk::{log, register_command};
    use r#impl::{find_procedure, free_dynamic_library, load_dynamic_library};

    log("Dylib plugin 1.1");

    register_command("LOAD_DYNAMIC_LIBRARY", load_dynamic_library, Some("dll"));
    register_command("FREE_DYNAMIC_LIBRARY", free_dynamic_library, Some("dll"));
    register_command("GET_DYNAMIC_LIBRARY_PROCEDURE", find_procedure, Some("dll"));
}
