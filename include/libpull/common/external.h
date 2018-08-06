/** \file external.h
 * \brief This file includes some external functions that
 * must be defined in the application. This is mandatory as
 * otherwise the final application will fail during the linking
 * process.
 * \author Antonio Langiu
 * \defgroup com_ext
 * \{
 */
#ifndef LIBPULL_COMMON_EXTERNAL_H_
#define LIBPULL_COMMON_EXTERNAL_H_

#include <libpull/memory/memory_interface.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern const mem_slot_t memory_slots[];

/** OBJ_END defines the final value used to stop the cicle on the
 * memory objects. */
#define OBJ_END -1

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* \} LIBPULL_COMMON_EXTERNAL_H_ */
