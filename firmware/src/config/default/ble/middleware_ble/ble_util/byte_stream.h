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
  Byte Stream Header File

  Company:
    Microchip Technology Inc.

  File Name:
   byte_stream.h

  Summary:
    Provides utility functions for endian conversion within the project.

  Description:
    This header defines a set of functions to handle endian conversions, which
    are essential for ensuring data integrity when transmitting bytes between
    systems with different endian representations.
 *******************************************************************************/

#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

/**
 * @addtogroup BLE_MW BLE Middleware
 * @{
 */

/**
 * @defgroup BYTE_STREAM Endian conversion 
 * @brief Provides endian conversion utilities.
 * @{
 */

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Convert a byte array to a uint16_t by reading in little endian format.
 * 
 * @param[out] p_value Pointer to the uint16_t variable where the result will be stored.
 * @param[in]  p_src   Pointer to the byte array containing the little endian data. 
 */
#define BUF_LE_TO_U16(p_value, p_src)\
    *p_value = ((uint16_t)*(p_src)) + (((uint16_t)*(p_src+1))<<8);


/**
 * @brief Convert a byte array to a uint16_t by reading in big endian format.
 * 
 * @param[out] p_value Pointer to the uint16_t variable where the result will be stored.
 * @param[in]  p_src   Pointer to the byte array containing the big endian data.
 */
#define BUF_BE_TO_U16(p_value, p_src)\
    *p_value = (((uint16_t)*(p_src))<<8) + (uint16_t)*(p_src+1);


/**
 * @brief Copy a variable length data from a source buffer to a destination, reversing the byte order.
 * 
 * @param[out] p_value Pointer to the destination buffer where the data will be copied to.
 * @param[in]  p_src   Pointer to the source buffer from which the data will be copied.
 * @param[in]  length  The length of the data to be copied.
 */
#define BUF_TO_VARIABLE(p_value, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        *(p_value+length-1-idx) = (p_src)[idx];\
    }\
}


/**
 * @brief Copy a variable length data from a source buffer to a destination without changing the byte order.
 * 
 * @param[out] p_value Pointer to the destination buffer where the data will be copied to.
 * @param[in]  p_src   Pointer to the source buffer from which the data will be copied.
 * @param[in]  length  The length of the data to be copied.
 */
#define BUF_COPY_TO_VARIABLE(p_value, p_src, length)\
        (void)memcpy((uint8_t *)p_value, (uint8_t *)(p_src), length);


/**
 * @brief Set a uint16_t value to a byte array in little endian format.
 * 
 * @param[out] p_dest Pointer to the byte array where the little endian data will be set.
 * @param[in]  src    The uint16_t value to be set in the array.
 */
#define U16_TO_BUF_LE(p_dest, src)\
    *(p_dest) = (uint8_t)src;\
    *(p_dest+1) = (uint8_t)(src >> 8);


/**
 * @brief Set a uint16_t value to a byte array in big endian format.
 * 
 * @param[out] p_dest Pointer to the byte array where the big endian data will be set.
 * @param[in]  src    The uint16_t value to be set in the array.
 */
#define U16_TO_BUF_BE(p_dest, src)\
    *(p_dest) = (uint8_t)(src>>8);\
    *(p_dest+1) = (uint8_t)src;


/**
 * @brief Set a uint32_t value to a byte array in little endian format.
 * 
 * @param[out] p_dest Pointer to the byte array where the little endian data will be set.
 * @param[in]  src    The uint32_t value to be set in the array.
 */
#define U32_TO_BUF_LE(p_dest, src)\
    *(p_dest) = (uint8_t)src;\
    *(p_dest+1) = (uint8_t)(src >> 8);\
    *(p_dest+2) = (uint8_t)(src >> 16);\
    *(p_dest+3) = (uint8_t)(src >> 24);


/**
 * @brief Sets a uint32_t value into a byte array in big endian format.
 * 
 * @param[out] p_dest Pointer to the destination byte array.
 * @param[in] src     The uint32_t value to be set.
 */
#define U32_TO_BUF_BE(p_dest, src)\
    *(p_dest) = (uint8_t)(src >> 24);\
    *(p_dest+1) = (uint8_t)(src >> 16);\
    *(p_dest+2) = (uint8_t)(src >> 8);\
    *(p_dest+3) = (uint8_t)src;


/**
 * @brief Copies a variable-length data to a destination address, reversing the byte order.
 * 
 * @param[out] p_dest   Pointer to the destination buffer.
 * @param[in] p_src     Pointer to the source data.
 * @param[in] length    The number of bytes to copy.
 */
#define VARIABLE_TO_BUF(p_dest, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        *(p_dest+(length-1)-idx) = *(p_src+idx);\
    }\
}


/**
 * @brief Copies a variable-length data to a destination address without changing the byte order.
 * 
 * @param[out] p_dest   Pointer to the destination buffer.
 * @param[in] p_src     Pointer to the source data.
 * @param[in] length    The number of bytes to copy.
 */
#define VARIABLE_COPY_TO_BUF(p_dest, p_src, length)\
    (void)memcpy(p_dest, p_src, length);


/**
 * @brief Retrieves a uint8_t value from a byte stream and advances the stream pointer.
 * 
 * @param p_value[out]  Pointer to the uint8_t variable where the data will be stored.
 * @param p_src[in,out]     Pointer to the pointer to the source byte stream.
 */
#define STREAM_TO_U8(p_value, p_src)\
    *p_value=*(p_src)[0];\
    (*p_src)++;


/**
 * @brief Retrieves a uint16_t value from a little endian byte stream and advances the stream pointer.
 * 
 * @param[out] p_value  Pointer to the uint16_t variable where the data will be stored.
 * @param[in,out] p_src     Pointer to the pointer to the source byte stream.
 */
#define STREAM_LE_TO_U16(p_value, p_src)\
    *p_value=((uint16_t)(*p_src)[0]) + (((uint16_t)(*p_src)[1])<<8);\
    (*p_src)+=2;


/**
 * @brief Retrieves a uint16_t value from a big endian byte stream and advances the stream pointer.
 * 
 * @param[out] p_value  Pointer to the uint16_t variable where the data will be stored.
 * @param[in,out] p_src     Pointer to the pointer to the source byte stream.
 */
#define STREAM_BE_TO_U16(p_value, p_src)\
    *p_value=((uint16_t)(*p_src)[1]) + (((uint16_t)(*p_src)[0])<<8);\
    (*p_src)+=2;


/**
 * @brief Retrieves a uint32_t value from a little endian byte stream and advances the stream pointer.
 *
 * @param[out] p_value  Pointer to the uint32_t variable where the data will be stored.
 * @param[in,out] p_src     Pointer to the pointer to the source byte stream.
 */
#define STREAM_LE_TO_U32(p_value, p_src)\
    *p_value=((uint32_t)(*p_src)[0]) + (((uint32_t)(*p_src)[1])<<8) + (((uint32_t)(*p_src)[2])<<16)+ (((uint32_t)(*p_src)[3])<<24);\
    (*p_src)+=4;


/**
 * @brief Retrieves a uint32_t value from a big endian byte stream and advances the stream pointer.
 * 
 * @param[out] p_value  Pointer to the uint32_t variable where the data will be stored.
 * @param[in,out] p_src     Pointer to the pointer to the source byte stream.
 */
#define STREAM_BE_TO_U32(p_value, p_src)\
    *p_value=((uint32_t)(*p_src)[3]) + (((uint32_t)(*p_src)[2])<<8) + (((uint32_t)(*p_src)[1])<<16)+ (((uint32_t)(*p_src)[0])<<24);\
    (*p_src)+=4;


/**
 * @brief Copies a variable-length data from a byte stream to a destination, reversing the byte order, and advances the stream pointer.
 * 
 * @param[out] p_value  Pointer to the destination buffer.
 * @param[in,out] p_src     Pointer to the pointer to the source byte stream.
 * @param[in] length    The number of bytes to copy.
 */
#define STREAM_TO_VARIABLE(p_value, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        *(p_value+length-1-idx) = (*p_src)[idx];\
    }\
    (*p_src)+=length;\
}


/**
 * @brief Copies a variable-length data from a byte stream without changing the endianess, and advances the stream pointer.
 * 
 * @param[out] p_value  Pointer to the destination where the data will be copied.
 * @param[in,out] p_src Pointer to the pointer of the source byte stream. The pointer is advanced by 'length' bytes.
 * @param[in] length    The number of bytes to copy.
 * 
 */
#define STREAM_COPY_TO_VARIABLE(p_value, p_src, length)\
        (void)memcpy((uint8_t *)p_value, (uint8_t *)(*p_src), length);\
        (*p_src)+=length;


/**
 * @brief Inserts a uint8_t value into a byte stream, and advances the stream pointer.
 *
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented.
 * @param[in] value     The uint8_t value to insert.
 */
#define U8_TO_STREAM(p_dest, value)\
    (*p_dest)[0] = value;\
    (*p_dest)++;


/**
 * @brief Inserts a uint16_t value into a byte stream in little endian format, and advances the stream pointer.
 *
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented by 2 bytes.
 * @param[in] value      The uint16_t value to insert.
 */
#define U16_TO_STREAM_LE(p_dest, value)\
    (void)memcpy(*p_dest, (uint8_t *)&value, 2);\
    (*p_dest)+=2;


/**
 * @brief Inserts a uint16_t value into a byte stream in big endian format, and advances the stream pointer.
 * 
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented by 2 bytes.
 * @param[in] value      The uint16_t value to insert.
 */
#define U16_TO_STREAM_BE(p_dest, value)\
    (*p_dest)[0] = (uint8_t)(value>>8);\
    (*p_dest)[1] = (uint8_t)value;\
    (*p_dest)+=2;


/**
 * @brief Inserts a uint32_t value into a byte stream in little endian format, and advances the stream pointer.
 * 
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented by 4 bytes.
 * @param[in] value      The uint32_t value to insert.
 */
#define U32_TO_STREAM_LE(p_dest, value)\
    (void)memcpy(*p_dest, (uint8_t *)&value, 4);\
    (*p_dest)+=4;


/**
 * @brief Inserts a uint32_t value into a byte stream in big endian format, and advances the stream pointer.
 * 
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented by 4 bytes.
 * @param[in] value      The uint32_t value to insert.
 */
#define U32_TO_STREAM_BE(p_dest, value)\
    (*p_dest)[0] = (uint8_t)(value >> 24);\
    (*p_dest)[1] = (uint8_t)(value >> 16);\
    (*p_dest)[2] = (uint8_t)(value >> 8);\
    (*p_dest)[3] = (uint8_t)value;\
    (*p_dest)+=4;


/**
 * @brief Copies a variable-length data to a byte stream, reversing the endianess, and advances the stream pointer.
 * 
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented by 'length' bytes.
 * @param[in] p_src      Pointer to the source data.
 * @param[in] length     The number of bytes to copy.
 */
#define VARIABLE_TO_STREAM(p_dest, p_src, length)\
{\
    uint8_t idx;\
    for (idx=0; idx<length; idx++)\
    {\
        (*p_dest)[(length-1)-idx]= *(p_src+idx);\
    }\
    (*p_dest)+=length;\
}


/**
 * @brief Copies a variable-length data to a byte stream without changing the endianess, advances the stream pointer.
 * 
 * @param[in,out] p_dest Pointer to the pointer of the destination byte stream. The pointer is incremented by 'length' bytes.
 * @param[in] p_src      Pointer to the source data.
 * @param[in] length     The number of bytes to copy.
 */
#define VARIABLE_COPY_TO_STREAM(p_dest, p_src, length)\
    (void)memcpy((uint8_t *)*p_dest, (uint8_t *)p_src, length);\
    (*p_dest)+=length;


/**
 * @defgroup INTERGER_TO_ARRAY_BYTES Converts interger to array
 * @brief Macros for converting integers to an array of bytes.
 * 
 * This group of macros is used for converting integer values into arrays of bytes
 * in specific endian formats. The resulting byte arrays are suitable for serialization,
 * communication protocols, or byte-level operations.
 * 
 * @{
 */


/**
 * @brief Convert a uint16_t value to an array of bytes in little endian format.
 * 
 * This macro takes a 16-bit unsigned integer and splits it into two bytes,
 * with the least significant byte first.
 * 
 * @param n The uint16_t integer to convert.
 * @retval The lower byte followed by the higher byte of the integer.
 */
#define UINT16_TO_BYTES(n)        ((uint8_t) (n)), ((uint8_t)((n) >> 8))


/**
 * @brief Convert a uint32_t value to an array of bytes in little endian format.
 * 
 * This macro takes a 32-bit unsigned integer and splits it into four bytes,
 * with the least significant byte first.
 * 
 * @param n The uint32_t integer to convert.
 * @retval A sequence of four bytes, from the least significant to the most significant.
 */
#define UINT32_TO_BYTES(n)        ((uint8_t) (n)), ((uint8_t)((n) >> 8)), ((uint8_t)((n) >> 16)), ((uint8_t)((n) >> 24))


/**
 * @brief Convert a uint16_t value to an array of bytes in big endian format.
 * 
 * This macro takes a 16-bit unsigned integer and splits it into two bytes,
 * with the most significant byte first.
 * 
 * @param n The uint16_t integer to convert.
 * @retval The higher byte followed by the lower byte of the integer.
 */
#define UINT16_TO_BYTES_BE(n)     ((uint8_t)((n) >> 8)), ((uint8_t) (n))

/** @} */

/** @} */

/** @} */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif //BYTE_STREAM_H