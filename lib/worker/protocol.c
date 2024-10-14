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
    {0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66},
    {0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B},
    {0x01, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0},
    {0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48},
    {0x01, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13},
    {0x01, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE},
    {0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5},
    {0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD7},
    {0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8C},
    {0x01, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61},
    {0x01, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A},
    {0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA2},
    {0x01, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF9},
    {0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14},
    {0x01, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x63},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xD1},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x81},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xFC},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xDF},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x10},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x5C},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xA6},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x02},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x4A},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xE0},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x67},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xBE},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x8B},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFF},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x12},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xA1},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0xFE},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x43},
    {0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x57},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x1D},
    {0x01, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0xFC},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x9E},
    {0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x86},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xC0},
    {0x01, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x2D},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x22},
    {0x01, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0xC9},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x7C},
    {0x01, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x62},
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x79},
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0xE3},
    {0x01, 0x10, 0x01, 0x10, 0x01, 0x10, 0x01, 0x8A},
    {0x01, 0x10, 0x01, 0x10, 0x01, 0x00, 0x00, 0x38},
    {0x01, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x19},
    {0x01, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x68},
    {0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x5D},
    {0x01, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0xB6},
    {0x01, 0x11, 0x11, 0x22, 0x22, 0x33, 0x33, 0x68},
    {0x01, 0x11, 0x11, 0x22, 0x22, 0x00, 0x00, 0x4C},
    {0x01, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x91},
    {0x01, 0x12, 0x12, 0x12, 0x12, 0x00, 0x00, 0xCD},
    {0x01, 0x12, 0x31, 0x23, 0x12, 0x31, 0x23, 0x94},
    {0x01, 0x12, 0x31, 0x23, 0x12, 0x00, 0x00, 0xBC},
    {0x01, 0x12, 0x34, 0x12, 0x34, 0x12, 0x34, 0x4E},
    {0x01, 0x12, 0x34, 0x12, 0x34, 0x00, 0x00, 0xEC},
    {0x01, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xFD},
    {0x01, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x32},
    {0x01, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x9D},
    {0x01, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0xB9},
    {0x01, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0xA4},
    {0x01, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x23},
    {0x01, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC4},
    {0x01, 0x55, 0x55, 0x55, 0x55, 0x00, 0x00, 0xA8},
    {0x01, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x64},
    {0x01, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x2C},
    {0x01, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x04},
    {0x01, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0xA7},
    {0x01, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x16},
    {0x01, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x01},
    {0x01, 0x87, 0x65, 0x43, 0x21, 0x00, 0x00, 0xC6},
    {0x01, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x76},
    {0x01, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x8A},
    {0x01, 0x98, 0x76, 0x54, 0x32, 0x10, 0x00, 0x77},
    {0x01, 0x98, 0x76, 0x54, 0x32, 0x00, 0x00, 0x9B},
    {0x01, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xD6},
    {0x01, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x0E},
    {0x01, 0xAB, 0xCD, 0xEF, 0x00, 0x00, 0x00, 0x84},
    {0x01, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xD3},
    {0x01, 0xAB, 0xCD, 0xAB, 0xCD, 0x00, 0x00, 0x29},
    {0x01, 0xAB, 0xCA, 0xBC, 0xAB, 0xCA, 0xBC, 0x70},
    {0x01, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xB6},
    {0x01, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x85},
    {0x01, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xF2},
    {0x01, 0xBA, 0xBA, 0xBA, 0xBA, 0x00, 0x00, 0x5B},
    {0x01, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x8F},
    {0x01, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x1F},
    {0x01, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xEF},
    {0x01, 0xDD, 0xDD, 0xDD, 0xDD, 0x00, 0x00, 0x94},
    {0x01, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0x4F},
    {0x01, 0xEE, 0xEE, 0xEE, 0xEE, 0x00, 0x00, 0x10},
    {0x01, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x3D},
    {0x01, 0x12, 0x34, 0x56, 0x78, 0x9A, 0x00, 0xAC},
    {0x01, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x88},
    {0x01, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x6A},
    {0x01, 0x12, 0x34, 0x56, 0x78, 0x9A, 0x12, 0x8D},
    {0x01, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x88},
    {0x01, 0xCB, 0xA9, 0x87, 0x65, 0x43, 0x21, 0xE6},
    {0x01, 0xCB, 0xA9, 0x87, 0x65, 0x00, 0x00, 0x55},
    {0x01, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x02},
    {0x01, 0xFE, 0xDC, 0xBA, 0x98, 0x00, 0x00, 0xA4},
    {0x01, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0x0E},
    {0x01, 0xCA, 0xCA, 0xCA, 0xCA, 0x00, 0x00, 0xE9},
    {0x01, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x6B},
    {0x01, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x45},
    {0x01, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0x0A},
    {0x01, 0xCA, 0xFE, 0xCA, 0xFE, 0x00, 0x00, 0x32},
    {0xFF, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5D},
    {0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0},
    {0xFF, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEB},
    {0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73},
    {0xFF, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28},
    {0xFF, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5},
    {0xFF, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9E},
    {0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC},
    {0xFF, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB7},
    {0xFF, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5A},
    {0xFF, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99},
    {0xFF, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2},
    {0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F},
    {0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x58},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xEA},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xBA},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xC7},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE4},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x2B},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x67},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x9D},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x39},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x71},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xDB},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x5C},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x85},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xB0},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xC4},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x9A},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0xC5},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x78},
    {0xFF, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x6C},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x26},
    {0xFF, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0xC7},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0xA5},
    {0xFF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0xBD},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFB},
    {0xFF, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x16},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x19},
    {0xFF, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0xF2},
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x47},
    {0xFF, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x59},
    {0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x42},
    {0xFF, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0xD8},
    {0xFF, 0x10, 0x01, 0x10, 0x01, 0x10, 0x01, 0xB1},
    {0xFF, 0x10, 0x01, 0x10, 0x01, 0x00, 0x00, 0x03},
    {0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x22},
    {0xFF, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x53},
    {0xFF, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x66},
    {0xFF, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x8D},
    {0xFF, 0x11, 0x11, 0x22, 0x22, 0x33, 0x33, 0x53},
    {0xFF, 0x11, 0x11, 0x22, 0x22, 0x00, 0x00, 0x77},
    {0xFF, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0xAA},
    {0xFF, 0x12, 0x12, 0x12, 0x12, 0x00, 0x00, 0xF6},
    {0xFF, 0x12, 0x31, 0x23, 0x12, 0x31, 0x23, 0xAF},
    {0xFF, 0x12, 0x31, 0x23, 0x12, 0x00, 0x00, 0x87},
    {0xFF, 0x12, 0x34, 0x12, 0x34, 0x12, 0x34, 0x75},
    {0xFF, 0x12, 0x34, 0x12, 0x34, 0x00, 0x00, 0xD7},
    {0xFF, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xC6},
    {0xFF, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x09},
    {0xFF, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xA6},
    {0xFF, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x82},
    {0xFF, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x9F},
    {0xFF, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x18},
    {0xFF, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xFF},
    {0xFF, 0x55, 0x55, 0x55, 0x55, 0x00, 0x00, 0x93},
    {0xFF, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x5F},
    {0xFF, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x17},
    {0xFF, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x3F},
    {0xFF, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x9C},
    {0xFF, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x2D},
    {0xFF, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x3A},
    {0xFF, 0x87, 0x65, 0x43, 0x21, 0x00, 0x00, 0xFD},
    {0xFF, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x4D},
    {0xFF, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0xB1},
    {0xFF, 0x98, 0x76, 0x54, 0x32, 0x10, 0x00, 0x4C},
    {0xFF, 0x98, 0x76, 0x54, 0x32, 0x00, 0x00, 0xA0},
    {0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xED},
    {0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x35},
    {0xFF, 0xAB, 0xCD, 0xEF, 0x00, 0x00, 0x00, 0xBF},
    {0xFF, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xE8},
    {0xFF, 0xAB, 0xCD, 0xAB, 0xCD, 0x00, 0x00, 0x12},
    {0xFF, 0xAB, 0xCA, 0xBC, 0xAB, 0xCA, 0xBC, 0x4B},
    {0xFF, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x8D},
    {0xFF, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0xBE},
    {0xFF, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xC9},
    {0xFF, 0xBA, 0xBA, 0xBA, 0xBA, 0x00, 0x00, 0x60},
    {0xFF, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xB4},
    {0xFF, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x24},
    {0xFF, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xD4},
    {0xFF, 0xDD, 0xDD, 0xDD, 0xDD, 0x00, 0x00, 0xAF},
    {0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0x74},
    {0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0x00, 0x00, 0x2B},
    {0xFF, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x06},
    {0xFF, 0x12, 0x34, 0x56, 0x78, 0x9A, 0x00, 0x97},
    {0xFF, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0xB3},
    {0xFF, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x51},
    {0xFF, 0x12, 0x34, 0x56, 0x78, 0x9A, 0x12, 0xB6},
    {0xFF, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0xB3},
    {0xFF, 0xCB, 0xA9, 0x87, 0x65, 0x43, 0x21, 0xDD},
    {0xFF, 0xCB, 0xA9, 0x87, 0x65, 0x00, 0x00, 0x6E},
    {0xFF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x39},
    {0xFF, 0xFE, 0xDC, 0xBA, 0x98, 0x00, 0x00, 0x9F},
    {0xFF, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0x35},
    {0xFF, 0xCA, 0xCA, 0xCA, 0xCA, 0x00, 0x00, 0xD2},
    {0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x50},
    {0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x7E},
    {0xFF, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0x31},
    {0xFF, 0xCA, 0xFE, 0xCA, 0xFE, 0x00, 0x00, 0x09},
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
#define EM4100_DATA_SIZE (5)
#define HIDProx_DATA_SIZE (6)
#define PAC_DATA_SIZE (4)
#define H10301_DATA_SIZE (3)
#define IOPROXXSF_DATA_SIZE (4)
#define PARADOX_DATA_SIZE (6)
#define INDALA26_DATA_SIZE (4)
#define VIKING_DATA_SIZE (4)
#define PYRAMID_DATA_SIZE (4)
#define KERI_DATA_SIZE (4)
#define JABLOTRON_DATA_SIZE (5)

const uint8_t uid_list_em4100[][EM4100_DATA_SIZE] = {
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

const uint8_t uid_list_hid[][HIDProx_DATA_SIZE] = {
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

const uint8_t uid_list_pac[][PAC_DATA_SIZE] = {
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

const uint8_t uid_list_h10301[][H10301_DATA_SIZE] = {
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

const uint8_t uid_list_ioproxxsf[][IOPROXXSF_DATA_SIZE] = {
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

const uint8_t uid_list_paradox[][PARADOX_DATA_SIZE] = {
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
    {0xFF, 0xDE, 0xBC, 0x9A, 0x78, 0x56}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_indala26[][INDALA26_DATA_SIZE] = {
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
    {0xFF, 0xDE, 0xBC, 0x9A}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_viking[][VIKING_DATA_SIZE] = {
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
    {0xFF, 0xDE, 0xBC, 0x9A}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_pyramid[][PYRAMID_DATA_SIZE] = {
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
    {0xFF, 0xDE, 0xBC, 0x9A}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_keri[][KERI_DATA_SIZE] = {
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
    {0xFF, 0xDE, 0xBC, 0x9A}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

const uint8_t uid_list_jablotron[][JABLOTRON_DATA_SIZE] = {
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
    {0xFF, 0xDE, 0xBC, 0x9A, 0x78}, // Decremental UID
    {0xCA, 0xCA, 0xCA, 0xCA, 0xCA}, // From arha
};

#if defined(RFID_125_PROTOCOL)
const FuzzerProtocol fuzzer_proto_items[] = {
    // EM4100
    {
        .name = "EM4100",
        .data_size = EM4100_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_em4100,
                .len = COUNT_OF(uid_list_em4100),
            },
    },
    // HIDProx
    {
        .name = "HIDProx",
        .data_size = HIDProx_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_hid,
                .len = COUNT_OF(uid_list_hid),
            },
    },
    // PAC
    {
        .name = "PAC/Stanley",
        .data_size = PAC_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_pac,
                .len = COUNT_OF(uid_list_pac),
            },
    },
    // H10301
    {
        .name = "H10301",
        .data_size = H10301_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_h10301,
                .len = COUNT_OF(uid_list_h10301),
            },
    },
    // IoProxXSF
    {
        .name = "IoProxXSF",
        .data_size = IOPROXXSF_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_ioproxxsf,
                .len = COUNT_OF(uid_list_ioproxxsf),
            },
    },
    // Paradox
    {
        .name = "Paradox",
        .data_size = PARADOX_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_paradox,
                .len = COUNT_OF(uid_list_paradox),
            },
    },
    // Indala26
    {
        .name = "Indala26",
        .data_size = INDALA26_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_indala26,
                .len = COUNT_OF(uid_list_indala26),
            },
    },
    // Viking
    {
        .name = "Viking",
        .data_size = VIKING_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_viking,
                .len = COUNT_OF(uid_list_viking),
            },
    },
   // Pyramid
    {
        .name = "Pyramid",
        .data_size = PYRAMID_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_pyramid,
                .len = COUNT_OF(uid_list_pyramid),
            },
    },
   // Keri
    {
        .name = "Keri",
        .data_size = KERI_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_keri,
                .len = COUNT_OF(uid_list_keri),
            },
    },
   // Jablotron
    {
        .name = "Jablotron",
        .data_size = JABLOTRON_DATA_SIZE,
        .dict =
            {
                .val = (const uint8_t*)&uid_list_jablotron,
                .len = COUNT_OF(uid_list_jablotron),
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
