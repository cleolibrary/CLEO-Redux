use ctor::*;
use std::{fs::read_to_string, path::Path};

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
unsafe extern "C" {}

#[ctor]
fn init() {
    cleo_redux_sdk::log("IDE Loader 1.4");
    cleo_redux_sdk::register_loader("*.ide", loader);
    let path = cleo_redux_sdk::get_directory_path(cleo_redux_sdk::Directory::CONFIG)
        .join("ide_loader.d.ts");
    if let Err(e) = std::fs::write(path, include_str!("./ide_loader.d.ts")) {
        cleo_redux_sdk::log(format!("Failed to write ide_loader.d.ts: {}", e));
    };
}

pub extern "C" fn loader(file_name: *const cleo_redux_sdk::c_char) -> *mut cleo_redux_sdk::c_void {
    let file_name = cleo_redux_sdk::to_rust_string(file_name);
    serialize_file(Path::new(&file_name)).unwrap_or(std::ptr::null_mut())
}

fn serialize_file(path: &Path) -> Option<*mut cleo_redux_sdk::c_void> {
    let file = read_to_string(path).ok()?;
    let parsed = gta_ide_parser::parse(&file).ok()?;
    let serialized = serde_json::to_string(&parsed).ok()?;
    let buffer = cleo_redux_sdk::alloc_mem(serialized.len() + 1); // extra null-terminated byte
    unsafe { buffer.copy_from(serialized.as_ptr() as _, serialized.len()) }
    Some(buffer)
}
