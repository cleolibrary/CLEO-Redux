use cleo_redux_sdk::*;
use winapi::um::winuser::GetKeyState;

#[derive(Copy, Clone)]
struct KeyState {
    is_pressed: bool,
    is_toggled: bool,
}

static mut KEYS: [KeyState; 256] = [KeyState {
    is_pressed: false,
    is_toggled: false,
}; 256];

static mut LAST_KEY: u8 = 0;
const CHEAT_STRING_LEN: usize = 30;
static mut CHEAT_STRING: [char; CHEAT_STRING_LEN] = ['\0'; CHEAT_STRING_LEN];

pub extern "C" fn is_key_pressed(ctx: Context) -> HandlerResult {
    let key = get_int_param(ctx) as usize;
    unsafe { update_compare_flag(ctx, KEYS[key].is_pressed) };
    HandlerResult::CONTINUE
}

pub extern "C" fn is_key_down(ctx: Context) -> HandlerResult {
    let key = get_int_param(ctx) as usize;
    unsafe { update_compare_flag(ctx, KEYS[key].is_pressed && KEYS[key].is_toggled) };
    HandlerResult::CONTINUE
}

pub extern "C" fn is_key_up(ctx: Context) -> HandlerResult {
    let key = get_int_param(ctx) as usize;
    unsafe { update_compare_flag(ctx, !KEYS[key].is_pressed && KEYS[key].is_toggled) };
    HandlerResult::CONTINUE
}

pub extern "C" fn get_last_key(ctx: Context) -> HandlerResult {
    unsafe { set_int_param(ctx, LAST_KEY as _) };
    HandlerResult::CONTINUE
}

pub extern "C" fn test_cheat(ctx: Context) -> HandlerResult {
    let cheat = get_string_param(ctx);
    for (i, c) in cheat.chars().rev().enumerate() {
        if i < CHEAT_STRING_LEN && c != unsafe { CHEAT_STRING[i] } {
            update_compare_flag(ctx, false);
            return HandlerResult::CONTINUE;
        }
    }
    update_compare_flag(ctx, true);
    HandlerResult::CONTINUE
}

pub extern "C" fn on_before_scripts_callback(_current_time: u32, _time_step: i32) {
    // state change
    // 0 -> 0 // pressed=false, keydown=false, keyup=false
    // 0 -> 1 // pressed=true, keydown=true, keyup=false
    // 1 -> 0 // pressed=false, keydown=false, keyup=true
    // 1 -> 1 // pressed=true, keydown=false, keyup=false

    for i in 0..=255u8 {
        let key_state = unsafe { GetKeyState(i as i32) };
        let is_pressed = key_state as u16 & 0x8000 != 0;
        unsafe {
            let key = &mut KEYS[i as usize];
            key.is_toggled = is_pressed != key.is_pressed;
            if key.is_toggled {
                LAST_KEY = i;
                if is_pressed {
                    if (LAST_KEY as char).is_ascii_alphanumeric() {
                        CHEAT_STRING[0] = LAST_KEY as char;
                    }
                }
            }
            key.is_pressed = is_pressed;
        }
    }
}

pub extern "C" fn on_after_scripts_callback(_current_time: u32, _time_step: i32) {
    unsafe {
        if CHEAT_STRING[0] != '\0' {
            for j in (1..CHEAT_STRING_LEN).rev() {
                CHEAT_STRING[j] = CHEAT_STRING[j - 1];
            }
            CHEAT_STRING[0] = '\0';
        }
    }
}

pub extern "C" fn on_runtime_init_callback() {
    // reset cheat string
    unsafe {
        CHEAT_STRING = ['\0'; CHEAT_STRING_LEN];
    }
}
