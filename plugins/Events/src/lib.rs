use ctor::*;
#[macro_use]
extern crate lazy_static;
#[macro_use]
mod utils;
mod cworld_add;
// extern crate cleo_redux_sdk;

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
extern "C" {}

#[ctor]
fn init() {
    cleo_redux_sdk::log("Events plugin 0.1");
    cworld_add::register_hook();
}
