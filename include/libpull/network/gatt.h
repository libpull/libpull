/** \file gatt.h
 * \brief Constants used to define BLE GATT Services and Characteristics.
 * \author Antonio Langiu
 * \defgroup net_gatt
 * \{
 */
#ifndef LIBPULL_NETWORK_GATT_H_
#define LIBPULL_NETWORK_GATT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <libpull/common.h>
#include <libpull/security/safestore.h>

/* These UUID has been generated using
 * https://www.uuidgenerator.net */

#define LIBPULL_SERVICE_UUID \
    0xf0, 0x08, 0xb7, 0x9c, 0x00, 0x0f, 0x86, 0x93, \
    0xf2, 0x46, 0x51, 0x14, 0x7d, 0x5b, 0x49, 0x58

#define LIBPULL_VERSION_READ_UUID \
    0xf1, 0x08, 0xb7, 0x9c, 0x00, 0x0f, 0x86, 0x93, \
    0xf2, 0x46, 0x51, 0x14, 0x7d, 0x5b, 0x49, 0x58

#define LIBPULL_VERSION_WRITE_UUID \
    0xf1, 0x08, 0xb7, 0x9c, 0x00, 0x0f, 0x86, 0x93, \
    0xf2, 0x46, 0x51, 0x14, 0x7d, 0x5b, 0x49, 0x58

#define LIBPULL_RECEIVER_MSG_UUID \
    0xf3, 0x08, 0xb7, 0x9c, 0x00, 0x0f, 0x86, 0x93, \
    0xf2, 0x46, 0x51, 0x14, 0x7d, 0x5b, 0x49, 0x58

#define LIBPULL_IMAGE_UUID \
    0xf4, 0x08, 0xb7, 0x9c, 0x00, 0x0f, 0x86, 0x93, \
    0xf2, 0x46, 0x51, 0x14, 0x7d, 0x5b, 0x49, 0x58

#define LIBPULL_STATE_UUID \
    0xf5, 0x08, 0xb7, 0x9c, 0x00, 0x0f, 0x86, 0x93, \
    0xf2, 0x46, 0x51, 0x14, 0x7d, 0x5b, 0x49, 0x58

pull_error libpull_gatt_init(safestore_t sf, mem_object_t* obj);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* \} LIBPULL_NETWORK_GATT_H_ */
