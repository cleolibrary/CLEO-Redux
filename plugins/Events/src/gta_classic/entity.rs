#[repr(C)]
pub enum EntityType {
    Nothing = 0,
    Building,
    Vehicle,
    Ped,
    Object,
    Dummy,
}

impl Into<EntityType> for u8 {
    fn into(self) -> EntityType {
        match self {
            1 => EntityType::Building,
            2 => EntityType::Vehicle,
            3 => EntityType::Ped,
            4 => EntityType::Object,
            5 => EntityType::Dummy,
            _ => EntityType::Nothing,
        }
    }
}

pub unsafe fn get_entity_type(entity: *const u8) -> EntityType {
    lazy_static! {
        static ref ENTITY_TYPE_OFFSET: isize = {
            use cleo_redux_sdk::HostId;

            match cleo_redux_sdk::get_host_id() {
                HostId::RE3 | HostId::REVC | HostId::GTA3 | HostId::VC => 0x50,
                HostId::SA => 0x36,
                HostId::GTA3_UNREAL | HostId::VC_UNREAL => 0x6C,
                HostId::SA_UNREAL => 0x6A,
                _ => 0,
            }
        };
    }
    // get entity type (lower 3 bits)
    (*entity.offset(*ENTITY_TYPE_OFFSET) & 0b111).into()
}
