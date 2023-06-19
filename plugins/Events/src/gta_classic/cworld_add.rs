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
        use cleo_redux_sdk::HostId;

        match cleo_redux_sdk::get_host_id() {
            HostId::RE3
            | HostId::REVC
            | HostId::GTA3
            | HostId::VC
            | HostId::SA
            | HostId::GTA3_UNREAL
            | HostId::VC_UNREAL
            | HostId::SA_UNREAL => match cleo_redux_sdk::get_symbol_address("CWorld::Add") {
                0 => None,
                x => Some(x),
            },
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
