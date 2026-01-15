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

/*******************************************************************************
  BLE DTM Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dtm.h

  Summary:
    This header file defines the BLE DTM interface functions for the application developer.

  Description:
    This header file declares the BLE DTM interface functions and events for the application developer.
    The "BLE_DTM_Init" function must be invoked within the "APP_Initialize" function to
    initialize this module within the system. This setup is necessary for conducting
    RF tests in compliance with the Bluetooth RF-PHY Test Specifications.
 *******************************************************************************/
#ifndef BLE_DTM_H
#define BLE_DTM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdbool.h>
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/**
 * @defgroup BLE_DTM BLE Direct Test Mode
 * @brief Defines the interface for the BLE DTM functions provided by the BLE Library.
 * 
 * This file includes definitions and prototypes for the BLE DTM,
 *       providing an API for application-level interaction with the BLE stack.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @addtogroup BLE_DTM_DEFINES Defines
 * @{
 */

/**
 * @defgroup BLE_DTM_CHANNEL_RANGE Receiver or transmitter channel range
 * @brief Defines the range of channels for RX/TX during Direct Test Mode (DTM).
 * @{
 */
#define BLE_DTM_CHANNEL_MIN                                     (0x00U)        /**< Minimum channel number allowed for DTM.*/
#define BLE_DTM_CHANNEL_MAX                                     (0x27U)        /**< Maximum channel number allowed for DTM. */
/** @} */


/**
 * @defgroup BLE_DTM_TRANSMITTER_PAYLOAD_TYPE Transmitter payload types
 * @brief Defines the payload types for the transmitter during DTM.
 * @{
 */
#define BLE_DTM_TX_TEST_PAYLOAD_0                               (0x00U)        /**< Payload pattern: PRBS9 sequence "11111111100000111101â?¦" (transmission order). */
#define BLE_DTM_TX_TEST_PAYLOAD_1                               (0x01U)        /**< Payload pattern: Repeated "11110000" (transmission order). */
#define BLE_DTM_TX_TEST_PAYLOAD_2                               (0x02U)        /**< Payload pattern: Repeated "10101010" (transmission order). */
#define BLE_DTM_TX_TEST_PAYLOAD_3                               (0x03U)        /**< Payload pattern: PRBS15 sequence. */
#define BLE_DTM_TX_TEST_PAYLOAD_4                               (0x04U)        /**< Payload pattern: Repeated "11111111" (transmission order). */
#define BLE_DTM_TX_TEST_PAYLOAD_5                               (0x05U)        /**< Payload pattern: Repeated "00000000" (transmission order). */
#define BLE_DTM_TX_TEST_PAYLOAD_6                               (0x06U)        /**< Payload pattern: Repeated "00001111" (transmission order). */
#define BLE_DTM_TX_TEST_PAYLOAD_7                               (0x07U)        /**< Payload pattern: Repeated "01010101" (transmission order). */
/** @} */


/**
 * @defgroup BLE_DTM_TRANSMITTER_PHY_TYPE Transmitter PHY types
 * @brief Defines the PHY types for the transmitter during DTM.
 * @{
 */
#define BLE_DTM_TX_1M                           				        (0x01U)        /**< Transmitter uses the LE 1M PHY. */
#define BLE_DTM_TX_2M                           				        (0x02U)        /**< Transmitter uses the LE 2M PHY.  */
#define BLE_DTM_TX_CODED_S_8                    				        (0x03U)        /**< Transmitter uses the LE Coded PHY with S=8 data coding. */
#define BLE_DTM_TX_CODED_S_2                    				        (0x04U)        /**< Transmitter uses the LE Coded PHY with S=2 data coding. */
/** @} */


/**
 * @defgroup BLE_DTM_RECEIVER_PHY_TYPE Receiver PHY types
 * @brief Defines the PHY types for the receiver during DTM.
 * @{
 */
#define BLE_DTM_RX_1M                              				      (0x01U)        /**< Receiver uses the LE 1M PHY. */
#define BLE_DTM_RX_2M                              				      (0x02U)        /**< Receiver uses the LE 2M PHY. */
#define BLE_DTM_RX_CODED                           				      (0x03U)        /**< Receiver uses the LE Coded PHY. */
/** @} */


/**
 * @defgroup BLE_DTM_CW_CHANNEL_RANGE Continuous wave (CW) channel range
 * @brief Defines the channel range for Continuous Wave (CW) testing during DTM.
 * @{
 */
#define BLE_DTM_CW_CHANNEL_MIN                                  (0x00U)        /**< Minimum channel number allowed for CW testing. */
#define BLE_DTM_CW_CHANNEL_MAX                                  (0x4EU)        /**< Maximum channel number allowed for CW testing. */
/** @} */

/** @} */ //BLE_DTM_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DTM_STRUCTS Structures
 * @{
 */

/** @brief Structure for the BLE Direct Test Mode (DTM) transmitter test. */
typedef struct BLE_DTM_TransmitterTestParams_T
{
    uint8_t txChannel;                                              /**< The RF channel used by the transmitter. Calculated as (Frequency - 2402) / 2.
                                                                         Valid frequency range is 2402 MHz to 2480 MHz. Refer to @ref BLE_DTM_CHANNEL_RANGE for details. */
    uint8_t testDataLen;                                            /**< Length of the test packet payload in bytes. */
    uint8_t packetPayload;                                          /**< Type of payload in the test packet. Refer to @ref BLE_DTM_TRANSMITTER_PAYLOAD_TYPE for payload types. */
    uint8_t phy;                                                    /**< The PHY (physical layer) used for transmission. Refer to @ref BLE_DTM_TRANSMITTER_PHY_TYPE for supported PHY types. */
    int8_t transmitPowerLevel;                                      /**< Desired transmit power level in dBm. Range: -127 to +20.
                                                                         Use 0x7E for minimum transmit power level.
                                                                         Use 0x7F for maximum transmit power level.
                                                                         If set to any other value, the BLE stack will attempt to use the requested power level or the closest achievable level. */
} BLE_DTM_TransmitterTestParams_T;

/** @} */ //BLE_DTM_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**
 * @addtogroup BLE_DTM_FUNS Functions
 * @{
 */

/**
 * @brief Initializes the BLE Directed Test Mode (DTM) module.
 *
 * @retval MBA_RES_SUCCESS                  Successfully initializes the BLE DTM module.
 */
uint16_t BLE_DTM_Init(void);


/**
 * @brief Stops any ongoing test.
 * @note  @ref BLE_DTM_Init must be called before using this function.
 *
 * @param[out] p_packetCount                Pointer to store the packet count. For a transmitter test, this will be zero. For a receiver test, it will be the number of received packets.
 * @param[out] p_avgRssi                    Pointer to store the average RSSI value.
 *
 * @retval MBA_RES_SUCCESS                  Successfully stops the ongoing test and retrieves results.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_DTM_EndTest(uint16_t *p_packetCount, int8_t *p_avgRssi);


/**
 * @brief Starts a transmitter test where the device generates test reference packets at a fixed interval.
 * @note  @ref BLE_DTM_Init must be called before using this function.
 *
 * @param[in] p_transTestParams             Pointer to the transmitter test parameters structure. See @ref BLE_DTM_TransmitterTestParams_T.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts the BLE transmitter test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The provided parameters are invalid.
 */
uint16_t BLE_DTM_EnhancedTransmitterTest(BLE_DTM_TransmitterTestParams_T *p_transTestParams);


/**
 * @brief Starts a receiver test where the device receives test reference packets at a fixed interval.
 * @note  @ref BLE_DTM_Init must be called before using this function.
 *
 * @param[in] rxChannel                     Channel number calculated as (F â?? 2402) / 2, where F is the frequency in MHz ranging from 2402 to 2480 MHz.
 *                                          See @ref BLE_DTM_CHANNEL_RANGE for the valid ranges.
 * @param[in] phy                           PHY type setting for the test. See @ref BLE_DTM_RECEIVER_PHY_TYPE for possible values.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts the receiver test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The provided parameters are invalid.
 */
uint16_t BLE_DTM_EnhancedReceiverTest(uint8_t rxChannel, uint8_t phy);


/**
 * @brief Starts a Continuous Wave (CW) test on a specific channel and with a specific power level.
 * @note  @ref BLE_DTM_Init must be called before using this function.
 *
 * @param[in] txChannel                     Channel number calculated as (F â?? 2402), where F is the frequency in MHz ranging from 2402 to 2480 MHz. 
 *                                          See @ref BLE_DTM_CHANNEL_RANGE for the valid ranges.
 * @param[in] txPower                       Transmit power level in dBm, ranging from -127 to +20 dBm.
 *
 * @retval MBA_RES_SUCCESS                  Successfully starts the CW test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 * @retval MBA_RES_INVALID_PARA             The provided parameters are invalid.
 */
uint16_t BLE_DTM_StartCwTest(uint8_t txChannel, int8_t txPower);


/**
 * @brief Stops the Continuous Wave (CW) test.
 * @note  @ref BLE_DTM_Init must be called before using this function.
 *
 * @retval MBA_RES_SUCCESS                  Successfully stops the CW test.
 * @retval MBA_RES_OOM                      Internal memory allocation failure occurred.
 */
uint16_t BLE_DTM_StopCwTest(void);

/** @} */ //BLE_DTM_FUNS

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif//BLE_DTM_H