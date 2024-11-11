#include "protocol_i.h"
#include "furi.h"

// #######################
// ## Ibutton Protocols ##
// #######################
#define DS1990_DATA_SIZE (8)
#define Metakom_DATA_SIZE (4)
#define Cyfral_DATA_SIZE (2)

const uint8_t uid_list_ds1990[][DS1990_DATA_SIZE] = {
    {0x01, 0xBE, 0x40, 0x11, 0x5A, 0x36, 0x00, 0xE1}, //– код универсального ключа, для Vizit
    {0x01, 0xBE, 0x40, 0x11, 0x5A, 0x56, 0x00, 0xBB}, //- проверен работает
    {0x01, 0xBE, 0x40, 0x11, 0x00, 0x00, 0x00, 0x77}, //- проверен работает
    {0x01, 0xBE, 0x40, 0x11, 0x0A, 0x00, 0x00, 0x1D}, //- проверен работает Визит иногда КЕЙМАНЫ
    {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2F}, //- проверен(метаком, цифрал, ВИЗИТ).
    {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x9B}, //- проверен Визит, Метакомы, КОНДОР
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x14}, //???-Открываает 98% Метаком и некоторые Цифрал
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x90, 0x19, 0xFF}, //???-Отлично работает на старых домофонах
    {0x01, 0x6F, 0x2E, 0x88, 0x8A, 0x00, 0x00, 0x4D}, //???-Открывать что-то должен
    {0x01, 0x53, 0xD4, 0xFE, 0x00, 0x00, 0x7E, 0x88}, //???-Cyfral, Metakom
    {0x01, 0x53, 0xD4, 0xFE, 0x00, 0x00, 0x00, 0x6F}, //???-домофоны Визит (Vizit) - до 99%
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D}, //???-домофоны Cyfral CCD-20 - до 70%
    {0x01, 0x00, 0xBE, 0x11, 0xAA, 0x00, 0x00, 0xFB}, //???-домофоны Кейман (KEYMAN)
    {0x01, 0x76, 0xB8, 0x2E, 0x0F, 0x00, 0x00, 0x5C}, //???-домофоны Форвард
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x14}, // Only FF
    {0x01, 0x78, 0x00, 0x48, 0xFD, 0xFF, 0xFF, 0xD1}, // StarNew Uni5
    {0x01, 0xA9, 0xE4, 0x3C, 0x09, 0x00, 0x00, 0xE6}, // Eltis Uni
};

const uint8_t uid_list_metakom[][Metakom_DATA_SIZE] = {
    {0x00, 0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF, 0xFF}, // Only FF
    {0x11, 0x11, 0x11, 0x11}, // Only 11
    {0x22, 0x22, 0x22, 0x22}, // Only 22
    {0x33, 0x33, 0x33, 0x33}, // Only 33
    {0x44, 0x44, 0x44, 0x44}, // Only 44
    {0x55, 0x55, 0x55, 0x55}, // Only 55
    {0x66, 0x66, 0x66, 0x66}, // Only 66
    {0x77, 0x77, 0x77, 0x77}, // Only 77
    {0x88, 0x88, 0x88, 0x88}, // Only 88
    {0x99, 0x99, 0x99, 0x99}, // Only 99
    {0x12, 0x34, 0x56, 0x78}, // Incremental UID
    {0x9A, 0x78, 0x56, 0x34}, // Decremental UID
    {0x04, 0xd0, 0x9b, 0x0d}, // ??
    {0x34, 0x00, 0x29, 0x3d}, // ??
    {0x04, 0xdf, 0x00, 0x00}, // ??
    {0xCA, 0xCA, 0xCA, 0xCA}, // ??
};

const uint8_t uid_list_cyfral[][Cyfral_DATA_SIZE] = {
    {0x00, 0x00}, // Null bytes
    {0xFF, 0xFF}, // Only FF
    {0x11, 0x11}, // Only 11
    {0x22, 0x22}, // Only 22
    {0x33, 0x33}, // Only 33
    {0x44, 0x44}, // Only 44
    {0x55, 0x55}, // Only 55
    {0x66, 0x66}, // Only 66
    {0x77, 0x77}, // Only 77
    {0x88, 0x88}, // Only 88
    {0x99, 0x99}, // Only 99
    {0x12, 0x34}, // Incremental UID
    {0x56, 0x34}, // Decremental UID
    {0xCA, 0xCA}, // ??
    {0x8E, 0xC9}, // Elevator code
    {0x6A, 0x50}, // VERY fresh code from smartkey
};

// ###########################
// ## Rfid_125khz Protocols ##
// ###########################
#define THREEBYTE_DATA_SIZE (3) // H10301
#define FOURBYTE_DATA_SIZE (4) // PAC/Stanley, IoProxXSF, Indala26, Viking, Pyramid, Keri
#define FIVEBYTE_DATA_SIZE (5) // EM4100, Joblotron
#define SIXBYTE_DATA_SIZE (6) // HIDProx, Paradox
#define EIGHTBYTE_DATA_SIZE (8) // Electra, Idteck, Gallagher, Nexwatch

const uint8_t uid_list_5byte[][FIVEBYTE_DATA_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Only FF
    {0x11, 0x11, 0x11, 0x11, 0x11}, // Only 11
    {0x22, 0x22, 0x22, 0x22, 0x22}, // Only 22
    {0x33, 0x33, 0x33, 0x33, 0x33}, // Only 33
    {0x44, 0x44, 0x44, 0x44, 0x44}, // Only 44
    {0x55, 0x55, 0x55, 0x55, 0x55}, // Only 55
    {0x66, 0x66, 0x66, 0x66, 0x66}, // Only 66
    {0x77, 0x77, 0x77, 0x77, 0x77}, // Only 77
    {0x88, 0x88, 0x88, 0x88, 0x88}, // Only 88
    {0x99, 0x99, 0x99, 0x99, 0x99}, // Only 99
    {0x12, 0x34, 0x56, 0x78, 0x9A}, // Incremental UID
    {0x9A, 0x78, 0x56, 0x34, 0x12}, // Decremental UID
    {0x04, 0xd0, 0x9b, 0x0d, 0x6a}, // From arha
    {0x34, 0x00, 0x29, 0x3d, 0x9e}, // From arha
    {0x04, 0xdf, 0x00, 0x00, 0x01}, // From arha
    {0xCA, 0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_6byte[][SIXBYTE_DATA_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Only FF
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11}, // Only 11
    {0x22, 0x22, 0x22, 0x22, 0x22, 0x22}, // Only 22
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33}, // Only 33
    {0x44, 0x44, 0x44, 0x44, 0x44, 0x44}, // Only 44
    {0x55, 0x55, 0x55, 0x55, 0x55, 0x55}, // Only 55
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66}, // Only 66
    {0x77, 0x77, 0x77, 0x77, 0x77, 0x77}, // Only 77
    {0x88, 0x88, 0x88, 0x88, 0x88, 0x88}, // Only 88
    {0x99, 0x99, 0x99, 0x99, 0x99, 0x99}, // Only 99
    {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}, // Incremental UID
    {0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_4byte[][FOURBYTE_DATA_SIZE] = {
    {0x00, 0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF, 0xFF}, // Only FF
    {0x11, 0x11, 0x11, 0x11}, // Only 11
    {0x22, 0x22, 0x22, 0x22}, // Only 22
    {0x33, 0x33, 0x33, 0x33}, // Only 33
    {0x44, 0x44, 0x44, 0x44}, // Only 44
    {0x55, 0x55, 0x55, 0x55}, // Only 55
    {0x66, 0x66, 0x66, 0x66}, // Only 66
    {0x77, 0x77, 0x77, 0x77}, // Only 77
    {0x88, 0x88, 0x88, 0x88}, // Only 88
    {0x99, 0x99, 0x99, 0x99}, // Only 99
    {0x12, 0x34, 0x56, 0x78}, // Incremental UID
    {0x9A, 0x78, 0x56, 0x34}, // Decremental UID
    {0x04, 0xd0, 0x9b, 0x0d}, // From arha
    {0x34, 0x00, 0x29, 0x3d}, // From arha
    {0x04, 0xdf, 0x00, 0x00}, // From arha
    {0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_3byte[][THREEBYTE_DATA_SIZE] = {
    {0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF}, // Only FF
    {0x11, 0x11, 0x11}, // Only 11
    {0x22, 0x22, 0x22}, // Only 22
    {0x33, 0x33, 0x33}, // Only 33
    {0x44, 0x44, 0x44}, // Only 44
    {0x55, 0x55, 0x55}, // Only 55
    {0x66, 0x66, 0x66}, // Only 66
    {0x77, 0x77, 0x77}, // Only 77
    {0x88, 0x88, 0x88}, // Only 88
    {0x99, 0x99, 0x99}, // Only 99
    {0x12, 0x34, 0x56}, // Incremental UID
    {0x56, 0x34, 0x12}, // Decremental UID
    {0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_8byte[][EIGHTBYTE_DATA_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Null bytes
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Only FF
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}, // Only 11
    {0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22}, // Only 22
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33}, // Only 33
    {0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44}, // Only 44
    {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55}, // Only 55
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66}, // Only 66
    {0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77}, // Only 77
    {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88}, // Only 88
    {0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99}, // Only 99
    {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF}, // Incremental UID
    {0xFF, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

#if defined(RFID_125_PROTOCOL)
const FuzzerProtocol fuzzer_proto_items[] = {
    // EM4100
    {
        .name = "EM4100",
        .data_size = FIVEBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_5byte,
                .len = COUNT_OF(uid_list_5byte),
            },
    },
    // HIDProx
    {
        .name = "HIDProx",
        .data_size = SIXBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_6byte,
                .len = COUNT_OF(uid_list_6byte),
            },
    },
    // PAC
    {
        .name = "PAC/Stanley",
        .data_size = FOURBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_4byte,
                .len = COUNT_OF(uid_list_4byte),
            },
    },
    // H10301
    {
        .name = "H10301",
        .data_size = THREEBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_3byte,
                .len = COUNT_OF(uid_list_3byte),
            },
    },
    // IoProxXSF
    {
        .name = "IoProxXSF",
        .data_size = FOURBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_4byte,
                .len = COUNT_OF(uid_list_4byte),
            },
    },
    // Paradox
    {
        .name = "Paradox",
        .data_size = SIXBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_6byte,
                .len = COUNT_OF(uid_list_6byte),
            },
    },
    // Indala26
    {
        .name = "Indala26",
        .data_size = FOURBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_4byte,
                .len = COUNT_OF(uid_list_4byte),
            },
    },
    // Viking
    {
        .name = "Viking",
        .data_size = FOURBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_4byte,
                .len = COUNT_OF(uid_list_4byte),
            },
    },
   // Pyramid
    {
        .name = "Pyramid",
        .data_size = FOURBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_4byte,
                .len = COUNT_OF(uid_list_4byte),
            },
    },
   // Keri
    {
        .name = "Keri",
        .data_size = FOURBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_4byte,
                .len = COUNT_OF(uid_list_4byte),
            },
    },
   // Jablotron
    {
        .name = "Jablotron",
        .data_size = FIVEBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_5byte,
                .len = COUNT_OF(uid_list_5byte),
            },
    },
   // Electra
    {
        .name = "Electra",
        .data_size = EIGHTBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_8byte,
                .len = COUNT_OF(uid_list_8byte),
            },
    },
   // Idteck
    {
        .name = "Idteck",
        .data_size = EIGHTBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_8byte,
                .len = COUNT_OF(uid_list_8byte),
            },
    },
   // Gallagher
    {
        .name = "Gallagher",
        .data_size = EIGHTBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_8byte,
                .len = COUNT_OF(uid_list_8byte),
            },
    },
   // Nexwatch
    {
        .name = "Nexwatch",
        .data_size = EIGHTBYTE_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_8byte,
                .len = COUNT_OF(uid_list_8byte),
            },
    },
};
#else
const FuzzerProtocol fuzzer_proto_items[] = {
    // DS1990
    {
        .name = "DS1990",
        .data_size = DS1990_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_ds1990,
                .len = COUNT_OF(uid_list_ds1990),
            },
    },
    // Metakom
    {
        .name = "Metakom",
        .data_size = Metakom_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_metakom,
                .len = COUNT_OF(uid_list_metakom),
            },
    },
    // Cyfral
    {
        .name = "Cyfral",
        .data_size = Cyfral_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_cyfral,
                .len = COUNT_OF(uid_list_cyfral),
            },
    },
};
#endif

typedef struct {
    const char* menu_label;
    FuzzerAttackId attack_id;
} FuzzerMenuItems;

const FuzzerMenuItems fuzzer_menu_items[] = {
    {"Default Values", FuzzerAttackIdDefaultValues},
#ifdef RFID_125_PROTOCOL
    {"BF Customer ID", FuzzerAttackIdBFCustomerID},
#endif
    {"Load File", FuzzerAttackIdLoadFile},
    {"Load UIDs from file", FuzzerAttackIdLoadFileCustomUids},
};

FuzzerPayload* fuzzer_payload_alloc() {
    FuzzerPayload* payload = malloc(sizeof(FuzzerPayload));
    payload->data = malloc(sizeof(payload->data[0]) * MAX_PAYLOAD_SIZE);

    return payload;
}

void fuzzer_payload_free(FuzzerPayload* payload) {
    furi_assert(payload);

    if(payload->data) {
        free(payload->data);
    }
    free(payload);
}

const char* fuzzer_proto_get_name(FuzzerProtocolsID index) {
    return fuzzer_proto_items[index].name;
}

uint8_t fuzzer_proto_get_count_of_protocols() {
    return COUNT_OF(fuzzer_proto_items);
}

uint8_t fuzzer_proto_get_max_data_size() {
    return MAX_PAYLOAD_SIZE;
}

uint8_t fuzzer_proto_get_def_emu_time() {
    return PROTOCOL_DEF_EMU_TIME;
}

uint8_t fuzzer_proto_get_def_idle_time() {
    return PROTOCOL_DEF_IDLE_TIME;
}

const char* fuzzer_proto_get_menu_label(uint8_t index) {
    return fuzzer_menu_items[index].menu_label;
}

FuzzerAttackId fuzzer_proto_get_attack_id_by_index(uint8_t index) {
    return fuzzer_menu_items[index].attack_id;
}

uint8_t fuzzer_proto_get_count_of_menu_items() {
    return COUNT_OF(fuzzer_menu_items);
}
