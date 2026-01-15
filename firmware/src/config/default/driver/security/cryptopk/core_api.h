/** Asymmetric cryptographic acceleration core interface
 *
 * @file
 */
/*
 * Copyright (c) 2018-2020 Silex Insight sa
 * Copyright (c) 2014-2020 Beerten Engineering scs
 * SPDX-License-Identifier: BSD-3-Clause
 */
// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef CORE_HEADER_FILE
#define CORE_HEADER_FILE

#include <stdint.h>
#include <stddef.h>
#include "driver/security/cryptopk/cmddefs_api.h"
#include "driver/security/api_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CRM_PK_OP_DEFAULT_ENDIANNESS
/** Default operand endianness
 *
 * 0: little endian
 * 1: big endian
 */
#define CRM_PK_OP_DEFAULT_ENDIANNESS 1
#endif

/**
 * @addtogroup CRM_PK_CORE
 *
 * @{
 */


/** Acceleration request
 *
 * A public key operation for offload on a hardware accelerator
 *
*/
typedef struct crm_pk_accel crm_pk_accel;


/** CryptoPK and hardware constraints */
struct crm_pk_constraints {
   /** Maximum simultaneous requests any application can configure. */
    int maxpending;
};


/** Return CryptoPK constraints
 *
 * If maxpending in crm_pk_constraints is 0, than CryptoPK cannot be used
 * with the given environment.
 *
 * @param[in] index Index should always be 0
 * @param[in] usermemsz User memory size provided in bytes. Should be non zero for
 * BA414 AHBMaster and BA414 baremetal with no static memory
 * @return Constraints of CryptoPK
 */
typedef struct crm_pk_constraints (*FUNC_CRM_PK_LIST_CONSTRAINTS)(int index, int usermemsz);
#define CRM_PK_LIST_CONSTRAINTS         ((FUNC_CRM_PK_LIST_CONSTRAINTS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_LIST_CONSTRAINTS)))

/** Description of the (hardware) accelerator capabilities and features.*/
struct crm_pk_capabilities {
   /** Maximum pending requests at any time. */
   int maxpending;
   /** Maximum operand size for prime field operands. 0 when not supported. */
   int max_gfp_opsz;
   /** Maximum operand size for elliptic curve operands. 0 when not supported. */
   int max_ecc_opsz;
   /** Maximum operand size for binary field operands. 0 when not supported. */
   int max_gfb_opsz;
   /** Operand size for IK operands. 0 when not supported. */
   int ik_opsz;
};


/** Opaque structure for offload with CryptoPK library */
struct crm_pk_cnx;


/** Return the crypto acceleration capabilities and features
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @return NULL on failure
 * @return Capabilities of the accelerator on success
 */
typedef const struct crm_pk_capabilities *(*FUNC_CRM_PK_FETCH_CAPABILITIES)(struct crm_pk_cnx *cnx);
#define CRM_PK_FETCH_CAPABILITIES         ((FUNC_CRM_PK_FETCH_CAPABILITIES)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_FETCH_CAPABILITIES)))


/** Library configuration for CRM_PK_OPEN() */
struct crm_pk_config {
    /** Maximum simultaneous requests the application will start.
     *
     * Set to 0 to use library default.
     */
    int maxpending;

    /** Device index to use.
     *
     * For special use cases with multiple independent hardware
     * accelerators. In case of doubt, leave to 0.
     */
    int devidx;

    /** User memory */
    long long *usrmem;

    /** Size of user provided memory */
    size_t usrmemsz;

    /** Personalization string for IK */
    uint32_t *personalization;

    /** Personalization string size in 32 bit words
     *
     * If the size is 0 the personalization string
     * is considered NULL and will not be used.
     */
    int personalization_sz;
};


/** Open CryptoPK and related hardware and allocate internal resources
 *
 * @param[in] cfg Configuration to customize CryptoPK to
 * application specific needs.
 * @return NULL on failure
 * @return Connection structure for future CryptoPK calls on success.
 * Can be used with CryptoPK functions to run operations.
 *
 * @see CRM_PK_CLOSE()
 */
typedef struct crm_pk_cnx *(*FUNC_CRM_PK_OPEN)(struct crm_pk_config *cfg);
#define CRM_PK_OPEN         ((FUNC_CRM_PK_OPEN)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_OPEN)))


/** Finish using any public key acceleration.
 *
 * No other hardware acceleration function can be called after this.
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 */
typedef void (*FUNC_CRM_PK_CLOSE)(struct crm_pk_cnx *cnx);
#define CRM_PK_CLOSE         ((FUNC_CRM_PK_CLOSE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CLOSE)))


/** Encapsulated acceleration request
 *
 * This structure is used by CRM_PK_ACQUIRE_REQ()
 * and *_go() functions as a return value
 */
struct crm_pk_dreq
{
   /** The acquired acceleration request **/
   crm_pk_accel *req;
   /** The status of CRM_PK_ACQUIRE_REQ() **/
   int status;
};


/** Get a CryptoPK request instance locked to perform the given operation
 *
 * The returned crm_pk_dreq structure contains a status and a pointer to
 * a reserved hardware accelerator instance. That pointer is only valid
 * and usable if status is non-zero.
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @param[in] cmd The command definition (for example ::CRM_PK_CMD_MOD_EXP)
 * @return The acquired acceleration request for this operation
 *
 * @see CRM_PK_RELEASE_REQ()
 */
typedef struct crm_pk_dreq (*FUNC_CRM_PK_ACQUIRE_REQ)(struct crm_pk_cnx *cnx, const struct crm_pk_cmd_def *cmd);
#define CRM_PK_ACQUIRE_REQ         ((FUNC_CRM_PK_ACQUIRE_REQ)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_ACQUIRE_REQ)))


struct crm_pk_ecurve;

/** Least significant bit of Ax is 1 (flag A) */
#define PK_OP_FLAGS_EDDSA_AX_LSB (1 << 29)

/** Least significant bit of Rx is 1 (flag B) */
#define PK_OP_FLAGS_EDDSA_RX_LSB (1 << 30)


/** Return the instance number of the hardware accelerator for this request
 *
 * @param[in] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @return instance number of the hardware accelerator for this request
 */
typedef unsigned int (*FUNC_CRM_PK_GET_REQ_ID)(crm_pk_accel *req);
#define CRM_PK_GET_REQ_ID         ((FUNC_CRM_PK_GET_REQ_ID)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_REQ_ID)))


/** Add the context pointer to an acceleration request
 *
 * The attached pointer can be retrieved by CRM_PK_GET_USER_CONTEXT().
 * After CRM_PK_RELEASE_REQ(), the context pointer is not available
 * anymore.
 *
 * The context can represent any content the user may associate with the PK request.
 *
 * @param[inout] req The acquired acceleration request
 * @param[in] context Pointer to context
 *
 * @see CRM_PK_GET_USER_CONTEXT()
 */
typedef void (*FUNC_CRM_PK_SET_USER_CONTEXT)(crm_pk_accel *req, void *context);
#define CRM_PK_SET_USER_CONTEXT         ((FUNC_CRM_PK_SET_USER_CONTEXT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_SET_USER_CONTEXT)))


/** Get the context pointer from an acceleration request
 *
 * @param[in] req The acquired acceleration request
 * @return Context pointer from an acceleration request
 *
 * @see CRM_PK_SET_USER_CONTEXT()
*/
typedef void *(*FUNC_CRM_PK_GET_USER_CONTEXT)(crm_pk_accel *req);
#define CRM_PK_GET_USER_CONTEXT         ((FUNC_CRM_PK_GET_USER_CONTEXT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_USER_CONTEXT)))


/** Return the global operands size detected for the request
 *
 * @param[in] req The acquired acceleration request
 * @return Operand size for the request
 */
typedef int (*FUNC_CRM_PK_GET_OPSIZE)(crm_pk_accel *req);
#define CRM_PK_GET_OPSIZE         ((FUNC_CRM_PK_GET_OPSIZE)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_OPSIZE)))


/** Operand slot structure */
struct crm_pk_slot
{
   /** Memory address of the operand slot **/
   char *addr;
};

/** Pair of slots
 *
 * Used to store large values
 */
struct crm_pk_dblslot
{
   /** First slot **/
   struct crm_pk_slot a;
   /** Second slot **/
   struct crm_pk_slot b;
};

/** List slots for input operands for an ECC operation
 *
 * Once the function completes with ::CRM_OK,
 * write each operand to the address
 * found in the corresponding slot.
 *
 * That applies to all ECC operations.
 *
 * @param[inout] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @param[in] curve The curve used for that ECC operation
 * @param[in] flags Operation specific flags
 * @param[out] inputs List of input slots that will be filled in.
 * See inputslots.h for predefined lists of input slots per operation.
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_BUSY
 */
typedef int (*FUNC_CRM_PK_LIST_ECC_INSLOTS)(crm_pk_accel *req, const struct crm_pk_ecurve *curve, int flags, struct crm_pk_slot *inputs);
#define CRM_PK_LIST_ECC_INSLOTS         ((FUNC_CRM_PK_LIST_ECC_INSLOTS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_LIST_ECC_INSLOTS)))

/** List slots for input operands for a GF(p) modular operation.
 *
 * Once the function completes with ::CRM_OK,
 * write each operands to the address
 * found in the corresponding slot.
 *
 * That applies to all operations except ECC.
 *
 * @param[inout] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @param[in] opsizes List of operand sizes in bytes
 * @param[out] inputs List of input slots that will be filled in.
 * See inputslots.h for predefined lists of input slots per operation.
 *
 * @return ::CRM_OK
 * @return ::CRM_ERR_OPERAND_TOO_LARGE
 * @return ::CRM_ERR_BUSY
 */
typedef int (*FUNC_CRM_PK_LIST_GFP_INSLOTS)(crm_pk_accel *req, const int *opsizes, struct crm_pk_slot *inputs);
#define CRM_PK_LIST_GFP_INSLOTS         ((FUNC_CRM_PK_LIST_GFP_INSLOTS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_LIST_GFP_INSLOTS)))

/** Run the operation request in hardware.
 *
 * @pre To be called after all operands have been written in the slots
 * obtainded with CRM_PK_LIST_ECC_INSLOTS() or CRM_PK_LIST_GFP_INSLOTS().
 * After that the acceleration request is pending.
 *
 * @post The caller should wait until the operation finishes with
 * CRM_PK_WAIT() or do polling by using crm_pk_has_finished().
 *
 * @param[in] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 */
typedef void (*FUNC_CRM_PK_RUN)(crm_pk_accel *req);
#define CRM_PK_RUN         ((FUNC_CRM_PK_RUN)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_RUN)))


/** Check if the current operation is still ongoing or finished
 *
 * Read the status of a request. When the accelerator is still
 * busy, return ::CRM_ERR_BUSY. When the accelerator
 * finished, return ::CRM_OK. May only be called after CRM_PK_RUN().
 * May not be called after crm_pk_has_finished() or other functions
 * like CRM_PK_WAIT() reported that the operation finished.
 *
 * @param[in] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @return Any \ref CRM_PK_STATUS "status code"
 */
typedef int (*FUNC_CRM_PK_GET_STATUS)(crm_pk_accel *req);
#define CRM_PK_GET_STATUS         ((FUNC_CRM_PK_GET_STATUS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_STATUS)))

/** Legacy name of CRM_PK_GET_STATUS() **/
#define CRM_PK_HAS_FINISHED(req) CRM_PK_GET_STATUS(req)


/** Wait until the current operation finishes.
 *
 * After the operation finishes, return the operation status code.
 *
 * @param[in] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @return Any \ref CRM_PK_STATUS "status code"
 */
typedef int (*FUNC_CRM_PK_WAIT)(crm_pk_accel *req);
#define CRM_PK_WAIT         ((FUNC_CRM_PK_WAIT)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_WAIT)))

/** Clear the interrupt request signal
 *
 * Clear the IRQ request signal
 *
 */
typedef void (*FUNC_CRM_PK_CLEAR_IRQ)(void);
#define CRM_PK_CLEARIRQ     ((FUNC_CRM_PK_CLEAR_IRQ)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_CLEARIRQ)))

/** Return the public key acceleration request which finished its operation.
 *
 * If no public key accelerator finished or none has an operation, return NULL.
 * The results from the returned crm_pk_accel should be used as soon as
 * possible and the instances given back with CRM_PK_RELEASE_REQ().
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @return NULL when no public key accelerator finished or none has an operation
 * @return The acceleration request which finished its operation
 */
typedef crm_pk_accel *(*FUNC_CRM_PK_POP_FINISHED_REQ)(struct crm_pk_cnx *cnx);
#define CRM_PK_POP_FINISHED_REQ         ((FUNC_CRM_PK_POP_FINISHED_REQ)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_POP_FINISHED_REQ)))


/** Return a platform notification that notifies when a request completed.
 *
 * The platform notification id is:
 * - -1 if not available
 * - a fd on POSIX systems
 * - an interrupt line number
 *
 * When a request completes the notification will activate.
 * The fd will become readable and the interrupt line will
 * generate an interrupt. The returned platform notification can
 * be used once. After the platform notification or after
 * CRM_PK_POP_FINISHED_REQ(), the notification id shall not
 * be used anymore.
 *
 * May not be used in combination with CRM_PK_WAIT().
 *
 * @param[inout] cnx Connection structure obtained through CRM_PK_OPEN() at startup
 * @return platform notification id
 */
typedef int (*FUNC_CRM_PK_GET_GLOBAL_NOTIFICATION_ID)(struct crm_pk_cnx *cnx);
#define CRM_PK_GET_GLOBAL_NOTIFICATION_ID         ((FUNC_CRM_PK_GET_GLOBAL_NOTIFICATION_ID)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_GLOBAL_NOTIFICATION_ID)))

/** Legacy name of CRM_PK_GET_GLOBAL_NOTIFICATION_ID() **/
#define CRM_PK_COMPLETION_FD(cnx) CRM_PK_GET_GLOBAL_NOTIFICATION_ID(cnx)


/** Return a platform notification id of completion of this request
 *
 * The platform notification id is:
 * - -1 if not available
 * - a fd on POSIX systems
 * - an interrupt line number
 *
 * When the request completes the notification will activate.
 * The fd will become readable and the interrupt line will
 * generate an interrupt. After it was used or after
 * CRM_PK_POP_FINISHED_REQ(), the fd or interrupt line
 * shall not be used anymore.
 *
 * May not be used in combination with CRM_PK_WAIT().
 *
 * @param[inout] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @return platform notification id
 */
typedef int (*FUNC_CRM_PK_GET_REQ_COMPLETION_ID)(crm_pk_accel *req);
#define CRM_PK_GET_REQ_COMPLETION_ID         ((FUNC_CRM_PK_GET_REQ_COMPLETION_ID)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_REQ_COMPLETION_ID)))


/** Fetch array of addresses to output operands
 *
 * @param[inout] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * @return Array of addresses to output operands
*/
typedef const char **(*FUNC_CRM_PK_GET_OUTPUT_OPS)(crm_pk_accel *req);
#define CRM_PK_GET_OUTPUT_OPS         ((FUNC_CRM_PK_GET_OUTPUT_OPS)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_GET_OUTPUT_OPS)))

/** Give back the public key acceleration request.
 *
 * Release the reserved resources
 *
 * @pre CRM_PK_ACQUIRE_REQ() should have been called
 * before this function is called and not
 * being in use by the hardware
 *
 * @param[inout] req The acceleration request obtained
 * through CRM_PK_ACQUIRE_REQ()
 * operation has finished
 */
typedef void (*FUNC_CRM_PK_RELEASE_REQ)(crm_pk_accel *req);
#define CRM_PK_RELEASE_REQ         ((FUNC_CRM_PK_RELEASE_REQ)(*(uint32_t *)(API_TABLE_BASE_ADDRESS + ATO_CRM_PK_RELEASE_REQ)))


/** Elliptic curve configuration and parameters.
 *
 * To be used only via the functions in ec_curves.h The internal members of the
 * structure should not be accessed directly.
 */
struct crm_pk_ecurve {
    uint32_t curveflags;
    int sz;
    const char *params;
    int offset;
    struct crm_pk_cnx *cnx;
};

/** @} */

#ifdef __cplusplus
}
#endif

#endif
