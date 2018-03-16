#ifndef SAMPLE_DATA_H_
#define SAMPLE_DATA_H_
/* This file is used to store all the keys used for testing purposes */

/* Vendor Key for Signature */
static const uint8_t vendor_priv_g[32] = {
    0xf7,0xfd,0xc9,0x84,0x7a,0x1f,0xb2,0xac,0xed,0xc4,0x22,0x72,0x3b,0x88,0x5d,0x35,
    0xca,0x62,0x8c,0x51,0xce,0x41,0xe4,0x38,0xf0,0x64,0xe2,0xce,0xa5,0x9d,0xef,0x49
};
static const uint8_t vendor_x_g[32] = {
    0x8b,0x27,0x39,0x67,0x01,0x4b,0x1c,0xae,0xfe,0x8a,0x18,0x6e,0xea,0x27,0x86,0x34,
    0x0e,0xea,0x35,0x3d,0x8c,0x65,0xf6,0x59,0xfc,0xcb,0x23,0xd7,0xfa,0xab,0x7b,0x18
};
static const uint8_t vendor_y_g[32] = {
    0x14,0x75,0x33,0xec,0x17,0xb7,0x54,0x50,0xca,0x98,0x35,0xad,0x58,0xbe,0xd5,0xfa,
    0x48,0xbc,0xa0,0x24,0x81,0xba,0xfa,0x3d,0xcd,0x8d,0x5a,0x7f,0x40,0xbc,0x70,0x94
};

/* Server Key for Signature */
static const uint8_t server_priv_g[32] = {
    0xf7,0x60,0x33,0x57,0xde,0x87,0x5e,0x0b,0x34,0x1f,0xb2,0x9e,0x60,0x07,0xcc,0x7c,
    0xea,0x51,0x16,0x35,0xe9,0x2e,0x7c,0x8d,0xaf,0x0e,0x10,0xee,0x12,0xc0,0x10,0xfb
};
static const uint8_t server_x_g[32] = {
    0xb6,0xe6,0x42,0xdc,0x2a,0x08,0x77,0x81,0x84,0xaa,0x2b,0x77,0xcd,0x2d,0xcb,0xce,
    0xe1,0xa3,0x67,0xc0,0x20,0x7f,0xa1,0x4a,0x6a,0x7d,0x3b,0xd5,0x98,0x4c,0xb6,0x67
};
static const uint8_t server_y_g[32] = {
    0x9a,0x57,0x4a,0x7c,0xfb,0x8b,0xea,0x9b,0xe2,0xa7,0x59,0x96,0x52,0x72,0x26,0x6a,
    0xba,0x46,0x6d,0xf6,0x9f,0x64,0x70,0xeb,0x65,0x05,0x70,0xdf,0x47,0xee,0xa0,0x68
};

/* Client key for DTLS client authentication */
static const uint8_t dtls_client_priv_g[64] = {
    0x47,0x94,0x08,0xba,0x3c,0x18,0xcf,0xcc,0x21,0x6c,0x09,0x2b,0x81,0x57,0x66,0xfc,
    0x8f,0x74,0x4a,0x12,0x00,0x41,0x72,0xb7,0xca,0x9d,0xae,0x9b,0x40,0xc9,0x37,0xf9,
    0x20,0x50,0xa7,0xe1,0xfe,0x7f,0x00,0x00,0x38,0x50,0xa7,0xe1,0xfe,0x7f,0x00,0x00,
    0xa0,0x4f,0xa7,0xe1,0xfe,0x7f,0x00,0x00,0xe8,0x50,0xa7,0xe1,0xfe,0x7f,0x00,0x00
};
static const uint8_t dtls_client_x_g[32] = {
    0xa3,0x31,0x85,0x2a,0xe8,0x08,0x43,0xc0,0x48,0xd5,0x5e,0x03,0xd2,0x4a,0xc5,0x8c,
    0x0a,0xf0,0x00,0x85,0x99,0xe2,0x7f,0xec,0xc2,0x49,0xc8,0xe7,0x22,0xd3,0xff,0x37
};
static const uint8_t dtls_client_y_g[32] = {
    0x28,0xbe,0x69,0xbf,0xd8,0x1d,0xde,0x1c,0xab,0x12,0x35,0xb4,0x1c,0x39,0x19,0xf1,
    0x25,0xf9,0x29,0x87,0x6b,0x11,0xef,0xa3,0x4f,0x32,0xfc,0x0c,0xe8,0xc8,0x59,0xd8
};

/* Server key for DTLS server authentication */
static const uint8_t dtls_server_priv_g[64] = {
    0xa3,0x31,0x85,0x2a,0xe8,0x08,0x43,0xc0,0x48,0xd5,0x5e,0x03,0xd2,0x4a,0xc5,0x8c,
    0x0a,0xf0,0x00,0x85,0x99,0xe2,0x7f,0xec,0xc2,0x49,0xc8,0xe7,0x22,0xd3,0xff,0x37,
    0x28,0xbe,0x69,0xbf,0xd8,0x1d,0xde,0x1c,0xab,0x12,0x35,0xb4,0x1c,0x39,0x19,0xf1,
    0x25,0xf9,0x29,0x87,0x6b,0x11,0xef,0xa3,0x4f,0x32,0xfc,0x0c,0xe8,0xc8,0x59,0xd8
};
static const uint8_t dtls_server_x_g[32] = {
    0xcf,0x9c,0xf2,0xf8,0x44,0x8b,0xe2,0x7f,0xff,0xc9,0xe1,0x69,0xdb,0x84,0x7c,0xdf,
    0xe6,0xd6,0xa9,0xd3,0x5b,0xbf,0xe9,0x99,0xc9,0x48,0x47,0xe9,0x5a,0x21,0x58,0xdb
};
static const uint8_t dtls_server_y_g[32] = {
    0x20,0x90,0x2f,0xeb,0xfe,0x7f,0x00,0x00,0x38,0x90,0x2f,0xeb,0xfe,0x7f,0x00,0x00,
    0xa0,0x8f,0x2f,0xeb,0xfe,0x7f,0x00,0x00,0xe8,0x90,0x2f,0xeb,0xfe,0x7f,0x00,0x00
};

/* Tests for hashing */
static const uint8_t data_g[128] = {
    0x54,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,
    0x20,0x64,0x61,0x74,0x61,0x0a,0x54,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,
    0x73,0x61,0x6d,0x70,0x6c,0x65,0x20,0x64,0x61,0x74,0x61,0x0a,0x54,0x68,0x69,0x73,
    0x20,0x69,0x73,0x20,0x61,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x20,0x64,0x61,0x74,
    0x61,0x0a,0x54,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x73,0x61,0x6d,0x70,
    0x6c,0x65,0x20,0x64,0x61,0x74,0x61,0x0a,0x54,0x68,0x69,0x73,0x20,0x69,0x73,0x20,
    0x61,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x20,0x64,0x61,0x74,0x61,0x0a,0x54,0x68,
    0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x21,0x0a
};
static const uint8_t hash_g[32] = {
    0xc8,0x05,0x66,0x45,0xd0,0x5d,0xb1,0x61,0x73,0x6f,0x84,0x50,0xce,0xab,0xc1,0x0a,
    0x89,0xd8,0xd0,0x83,0xa3,0xab,0xd0,0x46,0xf4,0xa4,0xec,0xa6,0x0a,0xa7,0x6f,0x65
};

/* Tests for ecc signatures */
static const uint8_t vendor_r_g[32] = {
    0xa6,0xf1,0xe1,0xa8,0x2f,0x7c,0x1e,0x63,0x67,0x10,0xc7,0x18,0xbf,0x22,0x51,0x08,
    0xb7,0x0a,0x93,0xcf,0x47,0xad,0xac,0xb9,0xa4,0xc4,0xe0,0x1f,0xfe,0x5c,0x43,0x9f,
};
static const uint8_t vendor_s_g[32] = {
    0x7f,0xf6,0x77,0x2e,0x24,0x69,0xe8,0x9f,0x96,0x9c,0x65,0x2b,0xed,0x08,0x52,0xeb,
    0xa4,0x56,0x57,0x29,0x85,0x1e,0x21,0xf8,0x9c,0xd9,0x4f,0xc7,0x62,0x99,0x5f,0xcb,
};

/* Generic device identity */
identity_t identity_g = {
    .udid = 0x0101,
    .random = 0x0202
};
#endif // SAMPLE_DATA_H_
