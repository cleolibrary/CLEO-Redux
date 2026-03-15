use ctor::*;
use std::{collections::BTreeMap, fs::read_to_string, path::Path};

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]
unsafe extern "C" {}

#[ctor]
fn init() {
    cleo_redux_sdk::log("FXT Loader 1.0");
    cleo_redux_sdk::register_loader("*.fxt", loader);
    let path = cleo_redux_sdk::get_directory_path(cleo_redux_sdk::Directory::CONFIG)
        .join("fxt_loader.d.ts");
    if let Err(e) = std::fs::write(path, include_str!("./fxt_loader.d.ts")) {
        cleo_redux_sdk::log(format!("Failed to write fxt_loader.d.ts: {}", e));
    };
}

pub extern "C" fn loader(file_name: *const cleo_redux_sdk::c_char) -> *mut cleo_redux_sdk::c_void {
    let file_name = cleo_redux_sdk::to_rust_string(file_name);
    serialize_file(Path::new(&file_name)).unwrap_or(std::ptr::null_mut())
}

fn serialize_file(path: &Path) -> Option<*mut cleo_redux_sdk::c_void> {
    let file = read_to_string(path).ok()?;
    let parsed = parse_fxt(&file);

    if parsed.is_empty() {
        return None;
    }

    let serialized = serde_json::to_string(&parsed).ok()?;
    let buffer = cleo_redux_sdk::alloc_mem(serialized.len() + 1);
    unsafe { buffer.copy_from(serialized.as_ptr() as _, serialized.len()) }
    Some(buffer)
}

/// Parses FXT file content into a key-value map.
///
/// FXT format: each line contains `<KEY> <TEXT>` separated by the first space.
/// Lines starting with `#` or `;` are comments and are skipped.
/// Empty lines are skipped.
fn parse_fxt(content: &str) -> BTreeMap<String, String> {
    content
        .lines()
        .map(|line| line.trim())
        .filter(|line| !line.is_empty() && !line.starts_with('#') && !line.starts_with(';'))
        .filter_map(|line| line.split_once(' '))
        .map(|(key, value)| (key.to_owned(), value.to_owned()))
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_fxt() {
        let content =
            "KEY1 Text value 1\nKEY2 Text value 2\n# comment\n; another comment\n\nKEY3 Text3";
        let result = parse_fxt(content);
        assert_eq!(result.len(), 3);
        assert_eq!(result["KEY1"], "Text value 1");
        assert_eq!(result["KEY2"], "Text value 2");
        assert_eq!(result["KEY3"], "Text3");
    }

    #[test]
    fn test_parse_fxt_empty() {
        let content = "# only comments\n; here too\n";
        let result = parse_fxt(content);
        assert!(result.is_empty());
    }
}
