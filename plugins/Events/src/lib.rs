use ctor::*;
#[macro_use]
extern crate lazy_static;
#[macro_use]
mod utils;
mod gta_classic;

#[ctor]
fn init() {
    cleo_redux_sdk::log("Events plugin 1.2");
    gta_classic::register_hooks();
}
