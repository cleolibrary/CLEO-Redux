use cleo_redux_sdk::*;
use std::mem::size_of;
use winapi::um::winuser::{
    GetAsyncKeyState, SendInput, INPUT, INPUT_KEYBOARD, INPUT_MOUSE, KEYEVENTF_KEYUP,
    MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP,
    MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP, VK_LBUTTON,
    VK_MBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, XBUTTON1, XBUTTON2,
};

#[derive(Copy, Clone)]
struct KeyState {
    is_pressed: bool,
    is_toggled: bool,
}

enum State {
    Up,
    Down,
}

static mut KEYS: [KeyState; 255] = [KeyState {
    is_pressed: false,
    is_toggled: false,
}; 255];

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

pub extern "C" fn hold_key(ctx: Context) -> HandlerResult {
    let key = get_int_param(ctx) as _;
    send_key_event(key, State::Down);
    HandlerResult::CONTINUE
}

pub extern "C" fn release_key(ctx: Context) -> HandlerResult {
    let key = get_int_param(ctx) as _;
    send_key_event(key, State::Up);
    HandlerResult::CONTINUE
}

pub extern "C" fn on_before_scripts_callback(_current_time: u32, _time_step: i32) {
    // state change
    // 0 -> 0 // pressed=false, keydown=false, keyup=false
    // 0 -> 1 // pressed=true, keydown=true, keyup=false
    // 1 -> 0 // pressed=false, keydown=false, keyup=true
    // 1 -> 1 // pressed=true, keydown=false, keyup=false

    for i in 0..255u8 {
        let key_state = unsafe { GetAsyncKeyState(i as i32) };
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

fn send_key_event(key: i32, state: State) {
    unsafe {
        let type_ = match key {
            VK_LBUTTON | VK_RBUTTON | VK_MBUTTON | VK_XBUTTON1 | VK_XBUTTON2 => INPUT_MOUSE,
            _ => INPUT_KEYBOARD,
        };

        let mut input = INPUT {
            type_,
            u: std::mem::zeroed(),
        };

        match key {
            VK_LBUTTON | VK_RBUTTON | VK_MBUTTON | VK_XBUTTON1 | VK_XBUTTON2 => {
                let mi = input.u.mi_mut();
                mi.dx = 0;
                mi.dy = 0;
                mi.dwFlags = get_flag(key as _, &state);
                if key == VK_XBUTTON1 {
                    mi.mouseData = XBUTTON1 as _;
                }
                if key == VK_XBUTTON2 {
                    mi.mouseData = XBUTTON2 as _;
                }
            }
            _ => {
                let ki = input.u.ki_mut();
                ki.wVk = key as _;
                ki.dwFlags = get_flag(key as _, &state);
            }
        };

        SendInput(1, &mut input, size_of::<INPUT>() as _);
    }
}

fn get_flag(key: i32, state: &State) -> u32 {
    match (key, state) {
        (VK_LBUTTON, State::Down) => MOUSEEVENTF_LEFTDOWN,
        (VK_RBUTTON, State::Down) => MOUSEEVENTF_RIGHTDOWN,
        (VK_MBUTTON, State::Down) => MOUSEEVENTF_MIDDLEDOWN,
        (VK_XBUTTON1, State::Down) => MOUSEEVENTF_XDOWN,
        (VK_XBUTTON2, State::Down) => MOUSEEVENTF_XDOWN,
        (VK_LBUTTON, State::Up) => MOUSEEVENTF_LEFTUP,
        (VK_RBUTTON, State::Up) => MOUSEEVENTF_RIGHTUP,
        (VK_MBUTTON, State::Up) => MOUSEEVENTF_MIDDLEUP,
        (VK_XBUTTON1, State::Up) => MOUSEEVENTF_XUP,
        (VK_XBUTTON2, State::Up) => MOUSEEVENTF_XUP,
        (_, State::Down) => 0,
        (_, State::Up) => KEYEVENTF_KEYUP,
    }
}
