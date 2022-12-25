mod cworld_add;
mod cworld_remove;
mod entity;

pub fn register_hooks() {
    cworld_add::register_hook();
    cworld_remove::register_hook();
}
