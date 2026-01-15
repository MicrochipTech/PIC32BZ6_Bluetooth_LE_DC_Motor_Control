 /* Copyright (c) 2019-2020 Silex Insight. All Rights reserved. 
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
#ifndef INTERNAL_HEADER_FILE
#define INTERNAL_HEADER_FILE

#include <stdint.h>
#include <stddef.h>

#ifndef CRM_EXTRA_IN_DESCS
#define CRM_EXTRA_IN_DESCS 0
#endif
#ifndef CRM_HASH_PRIV_SZ
#define CRM_HASH_PRIV_SZ 344
#endif

#define CRM_BLKCIPHER_PRIV_SZ 16
#define CRM_AEAD_PRIV_SZ (70)

struct crm_regs;
struct crm_blkcipher_cmdma_cfg;
struct crm_aead_cmdma_cfg;
struct crmhashalg;

/** A cryptomaster DMA descriptor */
struct crmdesc {
    char *addr;
    struct crmdesc *next;
    uint32_t sz;
    uint32_t dmatag;
};


/** Input and output descriptors and related state for cmdma */
struct crm_dmaslot {
    uint32_t cfg;
    struct crmdesc outdescs[5];
};


/** DMA controller
 *
 * For internal use only. Don't access directly.
 */
struct crm_dmactl {
    struct crm_regs *regs;
    struct crmdesc *d;
    struct crmdesc *out;
    char *mapped;
    struct crm_dmaslot dmamem;
};

/** Key reference
 *
 * Used for making a reference to a key stored in memory or to a key selected
 * by an identifier.
 * Created by CRM_KEYREF_LOAD_MATERIAL() or CRM_KEYREF_LOAD_BY_ID(). Used by blkcipher and
 * aead creation functions.
 *
 * All members should be considered INTERNAL and may not be accessed directly.
 */
struct crmkeyref {
    const char *key;
    size_t sz;
    uint32_t cfg;
};

/** An AEAD operation
 *
 * To be used with crm_aead_*() functions.
 *
 * All members should be considered INTERNAL and may not be accessed
 * directly.
 */
struct crmaead {
    const struct crm_aead_cmdma_cfg *cfg;
    const char *expectedtag;
    uint8_t tagsz;
    uint8_t headersz;
    uint32_t discardaadsz;
    uint32_t datainsz;
    uint64_t dataintotalsz;
    uint64_t totalaadsz;
    uint8_t granularity;
    int is_in_ctx;
    size_t ctxsz;
    unsigned int compatible;
    const struct crmkeyref *key;
    struct crm_dmactl dma;
    struct crmdesc allindescs[7];
    uint8_t extramem[CRM_AEAD_PRIV_SZ];
};


/** A simple block cipher operation
 *
 * To be used with crm_blkcipher_*() functions.
 *
 * All members should be considered INTERNAL and may not be accessed
 * directly.
 */
struct crmblkcipher {
    const struct crm_blkcipher_cmdma_cfg *cfg;
    size_t inminsz;
    size_t granularity;
    uint32_t mode;
    unsigned int compatible;
    const struct crmkeyref *key;
    struct crm_dmactl dma;
    struct crmdesc allindescs[5];
    char extramem[CRM_BLKCIPHER_PRIV_SZ];
};


/** A hash operation.
 *
 * To be used with crm_hash_*() functions.
 *
 * All members should be considered INTERNAL and may not be accessed
 * directly.
 */
struct crmhash {
    const struct crmhashalg *algo;
    const struct crm_digesttags *dmatags;
    uint32_t cntindescs;
    size_t totalsz;
    uint32_t feedsz;
    void(*digest)(struct crmhash* c, char *digest);
    struct crm_dmactl dma;
    struct crmdesc allindescs[7 + CRM_EXTRA_IN_DESCS];
    uint8_t extramem[CRM_HASH_PRIV_SZ];
};


/** A operation to load a countermeasures mask into the hardware.
 *
 * To be used with crm_cm_*() functions.
 *
 * All members should be considered INTERNAL and may not be accessed
 * directly.
 */
struct crmcmmask {
    struct crm_dmactl dma;
    struct crmdesc allindescs[1];
};


/** A simple MAC(message authentication code) operation
 *
 * To be used with crm_mac_*() functions.
 *
 * All members should be considered INTERNAL and may not be accessed
 * directly.
 */
struct crmmac {
    const struct crm_mac_cmdma_cfg *cfg;
    uint32_t cntindescs;
    uint32_t feedsz;
    int macsz;
    unsigned int compatible;
    const struct crmkeyref *key;
    struct crm_dmactl dma;
    struct crmdesc allindescs[5];
    uint8_t extramem[16];
};

#endif
