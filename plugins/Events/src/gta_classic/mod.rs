mod cworld_add;
mod cworld_remove;
mod entity;

pub fn register_hooks() {
    cworld_add::register_hook();
    cworld_remove::register_hook();
    generate_typings();
}

fn generate_typings() {
    let path =
        cleo_redux_sdk::get_directory_path(cleo_redux_sdk::Directory::CONFIG).join("events.d.ts");
    if let Err(e) = std::fs::write(path, include_str!("./events.d.ts")) {
        cleo_redux_sdk::log(format!("Failed to write events.d.ts: {}", e));
    };
}
