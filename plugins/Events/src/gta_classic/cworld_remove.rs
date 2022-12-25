use null_fn::*;

/*
    Events:
        OnVehicleDelete
        OnPedDelete
        OnObjectDelete
    Games:
        re3, reVC,
        GTA3, VC, SA,
        The Trilogy (GTA3, VC, SA)
*/

#[null_fn]
static mut CWORLD_REMOVE: extern "C" fn(*const u8) = std::ptr::null();

lazy_static! {
    static ref CWORLD_REMOVE_ADDR: Option<usize> = {
        use crate::utils::{get_exe_version, IMAGE_BASE};
        use cleo_redux_sdk::HostId;

        match cleo_redux_sdk::get_host_id() {
            HostId::RE3 | HostId::REVC => {
                match cleo_redux_sdk::get_symbol_address("CWorld::Remove") {
                    0 => None,
                    x => Some(x),
                }
            }
            HostId::GTA3 => Some(0x004AE9D0),
            HostId::VC => Some(0x004DB310),
            HostId::SA => Some(0x00563280),
            HostId::GTA3_UNREAL if get_exe_version("LibertyCity.exe") == Some((1, 0, 8, 11827)) => {
                Some(*IMAGE_BASE + 0xF34E90)
            }
            HostId::VC_UNREAL if get_exe_version("ViceCity.exe") == Some((1, 0, 8, 11827)) => {
                Some(*IMAGE_BASE + 0xF56AE0)
            }
            HostId::SA_UNREAL if get_exe_version("SanAndreas.exe") == Some((1, 0, 8, 11827)) => {
                Some(*IMAGE_BASE + 0x100AFB0)
            }
            _ => None,
        }
    };
}

extern "C" fn world_remove(entity: *const u8) {
    use super::entity::{get_entity_type, EntityType};
    use serde::Serialize;

    #[derive(Serialize)]
    struct Payload {
        address: usize,
    }

    let entity_type = unsafe { get_entity_type(entity) };

    // serialize payload and trigger event based on entity type
    match serde_json::to_string(&Payload {
        address: entity as _,
    }) {
        Ok(s) => match entity_type {
            EntityType::Vehicle => {
                cleo_redux_sdk::trigger_event("OnVehicleDelete", &s);
            }
            EntityType::Ped => {
                cleo_redux_sdk::trigger_event("OnPedDelete", &s);
            }
            EntityType::Object => {
                cleo_redux_sdk::trigger_event("OnObjectDelete", &s);
            }
            _ => {
                // ignore other types
            }
        },
        Err(e) => {
            cleo_redux_sdk::log(format!("Failed to serialize CWorld::Remove payload: {e}"));
        }
    };

    unsafe {
        // call original function
        CWORLD_REMOVE(entity);
    }
}

pub fn register_hook() {
    match *CWORLD_REMOVE_ADDR {
        Some(addr) => unsafe {
            CWORLD_REMOVE = crate::detour!(addr => world_remove as usize);
            cleo_redux_sdk::log("CWorld::Remove hook created");
        },
        None => {
            cleo_redux_sdk::log("Events plugin attempted to hook CWorld::Remove but failed to find its address. Check that your have a compatible game version");
        }
    }
}
