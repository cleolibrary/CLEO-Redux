use cleo_redux_sdk::*;
use libloading;

/// https://library.sannybuilder.com/#/unknown_x86/dylib/LOAD_DYNAMIC_LIBRARY
pub extern "C" fn load_dynamic_library(ctx: Context) -> HandlerResult {
    let libname = get_string_param(ctx);

    // if libname is just a file name then load it as is - subject to DLL search order
    // https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-search-order
    let path = if libname.contains("\\") || libname.contains("/") {
        resolve_path(&libname)
    } else {
        std::path::PathBuf::from(&libname)
    };

    log(format!("loading dynamic library {libname}"));

    match unsafe { libloading::Library::new(path) } {
        Ok(handle) => {
            let addr = Box::into_raw(Box::new(handle));
            set_int_param(ctx, addr as isize);
            update_compare_flag(ctx, true);
        }
        Err(error) => {
            log(format!("{error}"));
            update_compare_flag(ctx, false);
            set_int_param(ctx, 0);
        }
    }
    HandlerResult::CONTINUE
}

/// https://library.sannybuilder.com/#/unknown_x86/dylib/FREE_DYNAMIC_LIBRARY
pub extern "C" fn free_dynamic_library(ctx: Context) -> HandlerResult {
    log(format!("disposing dynamic library"));

    let addr = get_int_param(ctx);
    unsafe {
        std::mem::drop(Box::from_raw(addr as *mut libloading::Library));
    }
    HandlerResult::CONTINUE
}

/// https://library.sannybuilder.com/#/unknown_x86/dylib/GET_DYNAMIC_LIBRARY_PROCEDURE
pub extern "C" fn find_procedure(ctx: Context) -> HandlerResult {
    let symbol = get_string_param(ctx);
    let lib = get_int_param(ctx) as *mut libloading::Library;

    unsafe {
        let addr = lib
            .as_mut()
            .and_then(|lib| lib.get::<usize>(symbol.as_bytes()).ok())
            .and_then(|addr| Some(*addr as isize))
            .unwrap_or(0);

        set_int_param(ctx, addr);
        update_compare_flag(ctx, addr > 0);
    }
    HandlerResult::CONTINUE
}
