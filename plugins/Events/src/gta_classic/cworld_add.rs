use null_fn::*;
/*
    Events:
        OnVehicleCreate
        OnPedCreate
        OnObjectCreate
    Games:
        re3, reVC,
        GTA3, VC, SA,
        The Trilogy (GTA3, VC, SA)
*/

#[null_fn]
static mut CWORLD_ADD: extern "C" fn(*const u8) = std::ptr::null();

lazy_static! {
    static ref CWORLD_ADD_ADDR: Option<usize> = {
        use crate::utils::{get_exe_version, IMAGE_BASE};
        use cleo_redux_sdk::HostId;

        match cleo_redux_sdk::get_host_id() {
            HostId::RE3 | HostId::REVC => match cleo_redux_sdk::get_symbol_address("CWorld::Add") {
                0 => None,
                x => Some(x),
            },
            HostId::GTA3 => Some(0x004AE930),
            HostId::VC => Some(0x004DB3F0),
            HostId::SA => Some(0x00563220),
            HostId::GTA3_UNREAL if get_exe_version("LibertyCity.exe") == Some((1, 0, 8, 11827)) => {
                Some(*IMAGE_BASE + 0xF34DB0)
            }
            HostId::VC_UNREAL if get_exe_version("ViceCity.exe") == Some((1, 0, 8, 11827)) => {
                Some(*IMAGE_BASE + 0xF569F0)
            }
            HostId::SA_UNREAL if get_exe_version("SanAndreas.exe") == Some((1, 0, 8, 11827)) => {
                Some(*IMAGE_BASE + 0x100AF70)
            }
            _ => None,
        }
    };
}

extern "C" fn world_add(entity: *const u8) {
    use super::entity::{get_entity_type, EntityType};
    use serde::Serialize;

    #[derive(Serialize)]
    struct Payload {
        address: usize,
    }

    let entity_type = unsafe { get_entity_type(entity) };

    // call original function
    unsafe {
        CWORLD_ADD(entity);
    }

    // serialize payload and trigger event based on entity type
    match serde_json::to_string(&Payload {
        address: entity as _,
    }) {
        Ok(s) => match entity_type {
            EntityType::Vehicle => {
                cleo_redux_sdk::trigger_event("OnVehicleCreate", &s);
            }
            EntityType::Ped => {
                cleo_redux_sdk::trigger_event("OnPedCreate", &s);
            }
            EntityType::Object => {
                cleo_redux_sdk::trigger_event("OnObjectCreate", &s);
            }
            _ => {
                // ignore other types
            }
        },
        Err(e) => {
            cleo_redux_sdk::log(format!("Failed to serialize CWorld::Add payload: {e}"));
        }
    };
}

pub fn register_hook() {
    match *CWORLD_ADD_ADDR {
        Some(addr) => unsafe {
            CWORLD_ADD = crate::detour!(addr => world_add as usize);
            cleo_redux_sdk::log("CWorld::Add hook created");
        },
        None => {
            cleo_redux_sdk::log("Events plugin attempted to hook CWorld::Add but failed to find its address. Check that your have a supported game");
        }
    }
}
