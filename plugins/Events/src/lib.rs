use ctor::*;
#[macro_use]
extern crate lazy_static;
#[macro_use]
mod utils;
mod gta_classic;

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
extern "C" {}

#[ctor]
fn init() {
    cleo_redux_sdk::log("Events plugin 1.0");
    gta_classic::register_hooks();
}
