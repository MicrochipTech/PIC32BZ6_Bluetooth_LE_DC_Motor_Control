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


#include <stdint.h>


#ifndef _API_TABLE_H
#define _API_TABLE_H

extern const void * const api_table[];

/* Enable clock to security module */
// Device out of reset, crypto block clock is disabled; ensure clock is enabled prior to using security API
#define CRYPTO_CLK_ENABLE()                  (*(volatile unsigned int *)(0x43000000)) = ((*(volatile unsigned int *)(0x43000000)) | 0x02);

/* Disable clock to security module */
//Note: Disable the clock to security module when not in use to reduce power consumption
#define CRYPTO_CLK_DISABLE()                 (*(volatile unsigned int *)(0x43000000)) = ((*(volatile unsigned int *)(0x43000000)) & 0xFFFFFFFD);

#define API_TABLE_BASE_ADDRESS                  (uint32_t)0xF000

#define ATO_CRM_AEAD                                        0
#define ATO_CRM_AEAD_CREATE_AESGCM_ENC                   	(ATO_CRM_AEAD + 0)
#define ATO_CRM_AEAD_CREATE_AESGCM_DEC                   	(ATO_CRM_AEAD + 4)
#define ATO_CRM_AEAD_CREATE_AESCCM_ENC                   	(ATO_CRM_AEAD + 8)
#define ATO_CRM_AEAD_CREATE_AESCCM_DEC                   	(ATO_CRM_AEAD + 12)
#define ATO_CRM_AEAD_FEED_AAD                            	(ATO_CRM_AEAD + 16)
#define ATO_CRM_AEAD_CRYPT                               	(ATO_CRM_AEAD + 20)
#define ATO_CRM_AEAD_PRODUCE_TAG                         	(ATO_CRM_AEAD + 24)
#define ATO_CRM_AEAD_VERIFY_TAG                          	(ATO_CRM_AEAD + 28)
#define ATO_CRM_AEAD_RESUME_STATE                        	(ATO_CRM_AEAD + 32)
#define ATO_CRM_AEAD_SAVE_STATE                          	(ATO_CRM_AEAD + 36)
#define ATO_CRM_AEAD_WAIT                                	(ATO_CRM_AEAD + 40)
#define ATO_CRM_AEAD_STATUS                              	(ATO_CRM_AEAD + 44)

#define ATO_CRM_BLOCK_CIPHER                             	(ATO_CRM_AEAD_STATUS + 4) 
#define ATO_CRM_BLKCIPHER_CREATE_AESXTS_ENC              	(ATO_CRM_BLOCK_CIPHER + 0)  //48
#define ATO_CRM_BLKCIPHER_CREATE_AESXTS_DEC              	(ATO_CRM_BLOCK_CIPHER + 4)
#define ATO_CRM_BLKCIPHER_CREATE_AESCTR_ENC              	(ATO_CRM_BLOCK_CIPHER + 8)
#define ATO_CRM_BLKCIPHER_CREATE_AESCTR_DEC              	(ATO_CRM_BLOCK_CIPHER + 12)
#define ATO_CRM_BLKCIPHER_CREATE_AESECB_ENC              	(ATO_CRM_BLOCK_CIPHER + 16)
#define ATO_CRM_BLKCIPHER_CREATE_AESECB_DEC              	(ATO_CRM_BLOCK_CIPHER + 20)
#define ATO_CRM_BLKCIPHER_CREATE_AESCBC_ENC              	(ATO_CRM_BLOCK_CIPHER + 24)
#define ATO_CRM_BLKCIPHER_CREATE_AESCBC_DEC              	(ATO_CRM_BLOCK_CIPHER + 28)
#define ATO_CRM_BLKCIPHER_CREATE_AESCFB_ENC              	(ATO_CRM_BLOCK_CIPHER + 32)
#define ATO_CRM_BLKCIPHER_CREATE_AESCFB_DEC              	(ATO_CRM_BLOCK_CIPHER + 36)
#define ATO_CRM_BLKCIPHER_CREATE_AESOFB_ENC              	(ATO_CRM_BLOCK_CIPHER + 40)
#define ATO_CRM_BLKCIPHER_CREATE_AESOFB_DEC              	(ATO_CRM_BLOCK_CIPHER + 44)
#define ATO_CRM_BLKCIPHER_CRYPT                          	(ATO_CRM_BLOCK_CIPHER + 48)
#define ATO_CRM_BLKCIPHER_RUN                            	(ATO_CRM_BLOCK_CIPHER + 52)
#define ATO_CRM_BLKCIPHER_RESUME_STATE                   	(ATO_CRM_BLOCK_CIPHER + 56)
#define ATO_CRM_BLKCIPHER_SAVE_STATE                     	(ATO_CRM_BLOCK_CIPHER + 60)
#define ATO_CRM_BLKCIPHER_WAIT                           	(ATO_CRM_BLOCK_CIPHER + 64)
#define ATO_CRM_BLKCIPHER_STATUS                         	(ATO_CRM_BLOCK_CIPHER + 68)

#define ATO_CRM_CMMASK                                   	(ATO_CRM_BLKCIPHER_STATUS + 4) 
#define ATO_CRM_CM_LOAD_MASK                             	(ATO_CRM_CMMASK + 0) //120
#define ATO_CRM_CM_LOAD_MASK_WAIT                        	(ATO_CRM_CMMASK + 4)
#define ATO_CRM_CM_LOAD_MASK_STATUS                      	(ATO_CRM_CMMASK + 8)

#define ATO_CRM_HASH                                     	(ATO_CRM_CM_LOAD_MASK_STATUS + 4)
#define ATO_CRM_HASH_CREATE                              	(ATO_CRM_HASH + 0) //132
#define ATO_CRM_HASH_GET_ALG_DIGESTSZ                    	(ATO_CRM_HASH + 4)
#define ATO_CRM_HASH_GET_ALG_BLOCKSZ                     	(ATO_CRM_HASH + 8)
#define ATO_CRM_HASH_FEED                                	(ATO_CRM_HASH + 12)
#define ATO_CRM_HASH_RESUME_STATE                        	(ATO_CRM_HASH + 16)
#define ATO_CRM_HASH_SAVE_STATE                          	(ATO_CRM_HASH + 20)
#define ATO_CRM_HASH_DIGEST                              	(ATO_CRM_HASH + 24)
#define ATO_CRM_HASH_WAIT                                	(ATO_CRM_HASH + 28)
#define ATO_CRM_HASH_STATUS                              	(ATO_CRM_HASH + 32)
#define ATO_CRM_HASH_GET_DIGESTSZ                        	(ATO_CRM_HASH + 36)
#define ATO_CRM_HASH_GET_BLOCKSZ                         	(ATO_CRM_HASH + 40)
#define ATO_CRM_HASH_ABANDON                             	(ATO_CRM_HASH + 44)

#define ATO_CRM_SHA_1                                    	(ATO_CRM_HASH_ABANDON + 4)
#define ATO_CRM_HASH_CREATE_SHA1                         	(ATO_CRM_SHA_1 + 0) // 180

#define ATO_CRM_SHA_2                                    	(ATO_CRM_HASH_CREATE_SHA1 + 4)
#define ATO_CRM_HASH_CREATE_SHA224                       	(ATO_CRM_SHA_2 + 0) //184
#define ATO_CRM_HASH_CREATE_SHA256                       	(ATO_CRM_SHA_2 + 4)
#define ATO_CRM_HASH_CREATE_SHA384                       	(ATO_CRM_SHA_2 + 8)
#define ATO_CRM_HASH_CREATE_SHA512                       	(ATO_CRM_SHA_2 + 12)

#define ATO_CRM_INTERRUPTS                               	(ATO_CRM_HASH_CREATE_SHA512 + 4)
#define ATO_CRM_INTERRUPTS_ENABLE                        	(ATO_CRM_INTERRUPTS + 0) //200
#define ATO_CRM_INTERRUPTS_DISABLE                       	(ATO_CRM_INTERRUPTS + 4)

#define ATO_CRM_KEYREF                                   	(ATO_CRM_INTERRUPTS_DISABLE + 4)
#define ATO_CRM_KEYREF_LOAD_MATERIAL                     	(ATO_CRM_KEYREF + 0) //208
#define ATO_CRM_KEYREF_LOAD_BY_ID                        	(ATO_CRM_KEYREF + 4)

#define ATO_CRM_MAC                                      	(ATO_CRM_KEYREF_LOAD_BY_ID + 4)
#define ATO_CRM_MAC_FEED                                 	(ATO_CRM_MAC + 0) //216
#define ATO_CRM_MAC_GENERATE                             	(ATO_CRM_MAC + 4)
#define ATO_CRM_MAC_RESUME_STATE                         	(ATO_CRM_MAC + 8)
#define ATO_CRM_MAC_SAVE_STATE                           	(ATO_CRM_MAC + 12)
#define ATO_CRM_MAC_WAIT                                 	(ATO_CRM_MAC + 16)
#define ATO_CRM_MAC_STATUS                               	(ATO_CRM_MAC + 20)

#define ATO_CRM_CMAC                                     	(ATO_CRM_MAC_STATUS + 4)
#define ATO_CRM_MAC_CREATE_AESCMAC                       	(ATO_CRM_CMAC + 0) //240

#define ATO_CRM_HMAC                                     	(ATO_CRM_MAC_CREATE_AESCMAC + 4)
#define ATO_CRM_MAC_CREATE_HMAC_SHA1                     	(ATO_CRM_HMAC + 0) //244
#define ATO_CRM_MAC_CREATE_HMAC_SHA2_224                 	(ATO_CRM_HMAC + 4)
#define ATO_CRM_MAC_CREATE_HMAC_SHA2_256                 	(ATO_CRM_HMAC + 8)
#define ATO_CRM_MAC_CREATE_HMAC_SHA2_384                 	(ATO_CRM_HMAC + 12)
#define ATO_CRM_MAC_CREATE_HMAC_SHA2_512                 	(ATO_CRM_HMAC + 16)

#define ATO_CRM_TRNG                                     	(ATO_CRM_MAC_CREATE_HMAC_SHA2_512 + 4)
#define ATO_CRM_TRNG_INIT                                	(ATO_CRM_TRNG + 0) //264
#define ATO_CRM_TRNG_GET                                 	(ATO_CRM_TRNG + 4)

#define ATO_CRM_PK_CORE                                  	(ATO_CRM_TRNG_GET + 4)
#define ATO_CRM_PK_LIST_CONSTRAINTS                      	(ATO_CRM_PK_CORE + 0) //272
#define ATO_CRM_PK_FETCH_CAPABILITIES                    	(ATO_CRM_PK_CORE + 4)
#define ATO_CRM_PK_OPEN                                  	(ATO_CRM_PK_CORE + 8)
#define ATO_CRM_PK_CLOSE                                 	(ATO_CRM_PK_CORE + 12)
#define ATO_CRM_PK_ACQUIRE_REQ                           	(ATO_CRM_PK_CORE + 16)
#define ATO_CRM_PK_GET_REQ_ID                            	(ATO_CRM_PK_CORE + 20)
#define ATO_CRM_PK_SET_USER_CONTEXT                      	(ATO_CRM_PK_CORE + 24)
#define ATO_CRM_PK_GET_USER_CONTEXT                      	(ATO_CRM_PK_CORE + 28)
#define ATO_CRM_PK_GET_OPSIZE                            	(ATO_CRM_PK_CORE + 32)
#define ATO_CRM_PK_LIST_ECC_INSLOTS                      	(ATO_CRM_PK_CORE + 36)
#define ATO_CRM_PK_LIST_GFP_INSLOTS                      	(ATO_CRM_PK_CORE + 40)
#define ATO_CRM_PK_RUN                                   	(ATO_CRM_PK_CORE + 44)
#define ATO_CRM_PK_GET_STATUS                            	(ATO_CRM_PK_CORE + 48)
#define ATO_CRM_PK_WAIT                                  	(ATO_CRM_PK_CORE + 52)
//#define ATO_CRM_PK_CLEARIRQ                             	(ATO_CRM_PK_CORE + 56)
#define ATO_CRM_PK_POP_FINISHED_REQ                      	(ATO_CRM_PK_CORE + 56)
#define ATO_CRM_PK_GET_GLOBAL_NOTIFICATION_ID            	(ATO_CRM_PK_CORE + 60)
#define ATO_CRM_PK_GET_REQ_COMPLETION_ID                 	(ATO_CRM_PK_CORE + 64)
#define ATO_CRM_PK_GET_OUTPUT_OPS                        	(ATO_CRM_PK_CORE + 68)
#define ATO_CRM_PK_RELEASE_REQ                           	(ATO_CRM_PK_CORE + 72)

#define ATO_CRM_ECC_CURVES                               	(ATO_CRM_PK_RELEASE_REQ + 4)
#define ATO_CRM_PK_CREATE_ECP_CURVE                      	(ATO_CRM_ECC_CURVES + 0) //348
#define ATO_CRM_PK_CREATE_ECB_CURVE                      	(ATO_CRM_ECC_CURVES + 4)
#define ATO_CRM_PK_DESTROY_EC_CURVE                      	(ATO_CRM_ECC_CURVES + 8)
#define ATO_CRM_PK_GET_CURVE_NISTP192                    	(ATO_CRM_ECC_CURVES + 12)
#define ATO_CRM_PK_GET_CURVE_NISTP256                    	(ATO_CRM_ECC_CURVES + 16)
#define ATO_CRM_PK_GET_CURVE_NISTP384                    	(ATO_CRM_ECC_CURVES + 20)
#define ATO_CRM_PK_GET_CURVE_NISTP521                    	(ATO_CRM_ECC_CURVES + 24)
#define ATO_CRM_PK_GET_CURVE_ED25519                     	(ATO_CRM_ECC_CURVES + 28)
#define ATO_CRM_PK_GET_CURVE_ED448                       	(ATO_CRM_ECC_CURVES + 32)
#define ATO_CRM_PK_GET_CURVE_X25519                      	(ATO_CRM_ECC_CURVES + 36)
#define ATO_CRM_PK_GET_CURVE_X448                        	(ATO_CRM_ECC_CURVES + 40)
#define ATO_CRM_PK_GET_CURVE_SECP256K1                   	(ATO_CRM_ECC_CURVES + 44)
#define ATO_CRM_PK_GET_CURVE_FP256                       	(ATO_CRM_ECC_CURVES + 48)
#define ATO_CRM_PK_WRITE_CURVE_GEN                       	(ATO_CRM_ECC_CURVES + 52)
#define ATO_CRM_PK_CURVE_OPSIZE                          	(ATO_CRM_ECC_CURVES + 56)

#define ATO_CRM_ED25519                                  	(ATO_CRM_PK_CURVE_OPSIZE + 4)
#define ATO_CRM_ED25519_PTMULT                           	(ATO_CRM_ED25519 + 0) //408
#define ATO_CRM_ASYNC_ED25519_PTMULT_GO                  	(ATO_CRM_ED25519 + 4)
#define ATO_CRM_ASYNC_ED25519_PTMULT_END                 	(ATO_CRM_ED25519 + 8)
#define ATO_CRM_ED25519_SIGN                             	(ATO_CRM_ED25519 + 12)
#define ATO_CRM_PK_ASYNC_ED25519_SIGN_GO                 	(ATO_CRM_ED25519 + 16)
#define ATO_CRM_ASYNC_ED25519_SIGN_END                   	(ATO_CRM_ED25519 + 20)
#define ATO_CRM_ED25519_VERIFY                           	(ATO_CRM_ED25519 + 24)
#define ATO_CRM_ASYNC_ED25519_VERIFY_GO                  	(ATO_CRM_ED25519 + 28)

#define ATO_CRM_ED448                                    	(ATO_CRM_ASYNC_ED25519_VERIFY_GO + 4)
#define ATO_CRM_ED448_PTMULT                             	(ATO_CRM_ED448 + 0) //440
#define ATO_CRM_ASYNC_ED448_PTMULT_GO                    	(ATO_CRM_ED448 + 4)
#define ATO_CRM_ASYNC_ED448_PTMULT_END                   	(ATO_CRM_ED448 + 8)
#define ATO_CRM_ED448_SIGN                               	(ATO_CRM_ED448 + 12)
#define ATO_CRM_PK_ASYNC_ED448_SIGN_GO                   	(ATO_CRM_ED448 + 16)
#define ATO_CRM_ASYNC_ED448_SIGN_END                     	(ATO_CRM_ED448 + 20)
#define ATO_CRM_ED448_VERIFY                             	(ATO_CRM_ED448 + 24)
#define ATO_CRM_ASYNC_ED448_VERIFY_GO                    	(ATO_CRM_ED448 + 28)

#define ATO_CRM_MONTGOMERY                               	(ATO_CRM_ASYNC_ED448_VERIFY_GO + 4)
#define ATO_CRM_X25519_PTMULT                            	(ATO_CRM_MONTGOMERY + 0) //472
#define ATO_CRM_ASYNC_X25519_PTMULT_GO                   	(ATO_CRM_MONTGOMERY + 4)
#define ATO_CRM_ASYNC_X25519_PTMULT_END                  	(ATO_CRM_MONTGOMERY + 8)
#define ATO_CRM_X448_PTMULT                              	(ATO_CRM_MONTGOMERY + 12)
#define ATO_CRM_ASYNC_X448_PTMULT_GO                     	(ATO_CRM_MONTGOMERY + 16)
#define ATO_CRM_ASYNC_X448_PTMULT_END                    	(ATO_CRM_MONTGOMERY + 20)

#define ATO_CRM_ADAPTER                                  	(ATO_CRM_ASYNC_X448_PTMULT_END + 4)
#define ATO_CRM_PK_OP2MEM_LE                             	(ATO_CRM_ADAPTER + 0) //496
#define ATO_CRM_PK_OP2MEM_BE                             	(ATO_CRM_ADAPTER + 4)
#define ATO_CRM_PK_OP2MEM                                	(ATO_CRM_ADAPTER + 8)
#define ATO_CRM_PK_OP2VMEM_LE                            	(ATO_CRM_ADAPTER + 12)
#define ATO_CRM_PK_OP2VMEM_BE                            	(ATO_CRM_ADAPTER + 16)
#define ATO_CRM_PK_OP2VMEM                               	(ATO_CRM_ADAPTER + 20)
#define ATO_CRM_PK_MEM2OP_LE                             	(ATO_CRM_ADAPTER + 24)
#define ATO_CRM_PK_MEM2OP_BE                             	(ATO_CRM_ADAPTER + 28)
#define ATO_CRM_PK_MEM2OP                                	(ATO_CRM_ADAPTER + 32)
#define ATO_CRM_OP_SIZE                                  	(ATO_CRM_ADAPTER + 36)

#define ATO_CRM_PKSTATUS                                 	(ATO_CRM_OP_SIZE + 4)
#define ATO_CRM_DESCRIBE_STATUSCODE                      	(ATO_CRM_PKSTATUS + 0) //536

#define ATO_CRM_HASH_STRUCTS                             	(ATO_CRM_DESCRIBE_STATUSCODE + 4)
#define ATO_CRM_HASHALG_SHA1                             	(ATO_CRM_HASH_STRUCTS + 0) // 540
#define ATO_CRM_HASHALG_SHA2_224                         	(ATO_CRM_HASH_STRUCTS + 4)
#define ATO_CRM_HASHALG_SHA2_256                         	(ATO_CRM_HASH_STRUCTS + 8)
#define ATO_CRM_HASHALG_SHA2_384                         	(ATO_CRM_HASH_STRUCTS + 12)
#define ATO_CRM_HASHALG_SHA2_512                         	(ATO_CRM_HASH_STRUCTS + 16)

#define ATO_CRM_PK_COMMANDS                              	(ATO_CRM_HASHALG_SHA2_512 + 4)
#define ATO_CRM_PK_CMD_MOD_ADD                           	(ATO_CRM_PK_COMMANDS + 0) //560
#define ATO_CRM_PK_CMD_MOD_SUB                           	(ATO_CRM_PK_COMMANDS + 4)
#define ATO_CRM_PK_CMD_ODD_MOD_MULT                      	(ATO_CRM_PK_COMMANDS + 8)
#define ATO_CRM_PK_CMD_EVEN_MOD_INV                      	(ATO_CRM_PK_COMMANDS + 12)
#define ATO_CRM_PK_CMD_EVEN_MOD_REDUCE                   	(ATO_CRM_PK_COMMANDS + 16)
#define ATO_CRM_PK_CMD_ODD_MOD_REDUCE                    	(ATO_CRM_PK_COMMANDS + 20)
#define ATO_CRM_PK_CMD_ODD_MOD_DIV                       	(ATO_CRM_PK_COMMANDS + 24)
#define ATO_CRM_PK_CMD_ODD_MOD_INV                       	(ATO_CRM_PK_COMMANDS + 28)
#define ATO_CRM_PK_CMD_MOD_SQRT                          	(ATO_CRM_PK_COMMANDS + 32)
#define ATO_CRM_PK_CMD_MULT                              	(ATO_CRM_PK_COMMANDS + 36)
#define ATO_CRM_PK_CMD_MOD_EXP                           	(ATO_CRM_PK_COMMANDS + 40)
#define ATO_CRM_PK_CMD_DH_MOD_EXP_CM                     	(ATO_CRM_PK_COMMANDS + 44)
#define ATO_CRM_PK_CMD_RSA_MOD_EXP_CM                    	(ATO_CRM_PK_COMMANDS + 48)
#define ATO_CRM_PK_CMD_MOD_EXP_CRT                       	(ATO_CRM_PK_COMMANDS + 52)
#define ATO_CRM_PK_CMD_MOD_EXP_CRT_CM                    	(ATO_CRM_PK_COMMANDS + 56)
#define ATO_CRM_PK_CMD_RSA_KEYGEN                        	(ATO_CRM_PK_COMMANDS + 60)
#define ATO_CRM_PK_CMD_RSA_CRT_KEYPARAMS                 	(ATO_CRM_PK_COMMANDS + 64)
#define ATO_CRM_PK_CMD_MONTGOMERY_PTMUL                  	(ATO_CRM_PK_COMMANDS + 68)
#define ATO_CRM_PK_CMD_ECDSA_VER                         	(ATO_CRM_PK_COMMANDS + 72)
#define ATO_CRM_PK_CMD_ECDSA_GEN                         	(ATO_CRM_PK_COMMANDS + 76)
#define ATO_CRM_PK_CMD_ECC_PT_ADD                        	(ATO_CRM_PK_COMMANDS + 80)
#define ATO_CRM_PK_CMD_ECC_PTMUL                         	(ATO_CRM_PK_COMMANDS + 84)
#define ATO_CRM_PK_CMD_ECC_PTMUL_CM                      	(ATO_CRM_PK_COMMANDS + 88)
#define ATO_CRM_PK_CMD_ECC_PT_DECOMP                     	(ATO_CRM_PK_COMMANDS + 92)
#define ATO_CRM_PK_CMD_CHECK_PARAM_AB                    	(ATO_CRM_PK_COMMANDS + 96)
#define ATO_CRM_PK_CMD_CHECK_PARAM_N                     	(ATO_CRM_PK_COMMANDS + 100)
#define ATO_CRM_PK_CMD_CHECK_XY                          	(ATO_CRM_PK_COMMANDS + 104)
#define ATO_CRM_PK_CMD_ECC_PT_DOUBLE                     	(ATO_CRM_PK_COMMANDS + 108)
#define ATO_CRM_PK_CMD_ECC_PTONCURVE                     	(ATO_CRM_PK_COMMANDS + 112)
#define ATO_CRM_PK_CMD_EDDSA_PTMUL                       	(ATO_CRM_PK_COMMANDS + 116)
#define ATO_CRM_PK_CMD_EDDSA_SIGN                        	(ATO_CRM_PK_COMMANDS + 120)
#define ATO_CRM_PK_CMD_EDDSA_VER                         	(ATO_CRM_PK_COMMANDS + 124)
#define ATO_CRM_PK_CMD_DSA_SIGN                          	(ATO_CRM_PK_COMMANDS + 128)
#define ATO_CRM_PK_CMD_DSA_VER                           	(ATO_CRM_PK_COMMANDS + 132)

#define ATO_IMG_MEM                                     	(ATO_CRM_PK_CMD_DSA_VER + 4)
#define ATO_IMG_MEM_FindValidTopologies                 	(ATO_IMG_MEM + 0) // 696
#define ATO_IMG_MEM_CacheHeader                         	(ATO_IMG_MEM + 4)
#define ATO_IMG_MEM_ValidateHeader                      	(ATO_IMG_MEM + 8)
#define ATO_IMG_MEM_CacheAndValidateHeaders             	(ATO_IMG_MEM + 12)
#define ATO_IMG_MEM_GetTopologyByAddress                	(ATO_IMG_MEM + 16)
#define ATO_IMG_MEM_SlotSort                            	(ATO_IMG_MEM + 20) // 710 -  136 API's + 43 structures   

#define ATO_PCHE                                        	(ATO_IMG_MEM_SlotSort + 4)
#define ATO_PCHE_SETUP                                  	(ATO_PCHE + 0)  //720

#define ATO_FLASH                                       	(ATO_PCHE_SETUP + 4)
#define ATO_FLASH_INITIALIZE                            	(ATO_FLASH + 0) //724
#define ATO_FLASH_READJEDECID                           	(ATO_FLASH + 4) 
#define ATO_FLASH_ERASESECTOR                           	(ATO_FLASH + 8)
#define ATO_FLASH_WRITEDATA                             	(ATO_FLASH + 12)
#define ATO_FLASH_READDATA                              	(ATO_FLASH + 16)

#define ATO_PFM                                         	(ATO_FLASH_READDATA + 4)
#define ATO_PRM_INITIALIZE                              	(ATO_PFM + 0)
#define ATO_PFM_READ                                    	(ATO_PFM + 4)
#define ATO_PFM_SINGLEDOUBLEWORDWRITE                       (ATO_PFM + 8)
#define ATO_PFM_QUADDOUBLEWORDWRITE                         (ATO_PFM + 12)
#define ATO_PFM_ROWWRITE                                	(ATO_PFM + 16)
#define ATO_PFM_PAGEERASE                               	(ATO_PFM + 20)
#define ATO_PFM_PROGRAMERASE                            	(ATO_PFM + 24)
#define ATO_PFM_PROGRAMFLASHWRITEPROTECT                	(ATO_PFM + 28)
#define ATO_PFM_PROGRAMFLASHWRITEPROTECTLOCK            	(ATO_PFM + 32)
#define ATO_PFM_ERRORGET                                	(ATO_PFM + 36)
#define ATO_PFM_ISBUSY                                  	(ATO_PFM + 40) //784

#define ATO_ROM_VERSION                                 	(ATO_PFM_ISBUSY + 4)

#define ATO_IMAGE_AUTHENTICATION                        	(ATO_ROM_VERSION + 4)
#endif

