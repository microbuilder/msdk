/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. (now owned by 
 * Analog Devices, Inc.),
 * Copyright (C) 2023-2024 Analog Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LIBRARIES_MAXUSB_INCLUDE_ENUMERATE_ENUMERATE_H_
#define LIBRARIES_MAXUSB_INCLUDE_ENUMERATE_ENUMERATE_H_

/**
 * @file  enumerate.h
 * @brief USB Device Enumeration Routines
 */

#include <usb_protocol.h>

#ifdef __cplusplus
extern "C" {
#endif

/// User can register callbacks for various control endpoint requests
typedef enum {
  ENUM_CLASS_REQ,
  ENUM_VENDOR_REQ,
  ENUM_SETCONFIG,
  ENUM_SETINTERFACE,
  ENUM_GETINTERFACE,
  ENUM_SETFEATURE,
  ENUM_CLRFEATURE,
  ENUM_NUM_CALLBACKS
} enum_callback_t;

/// User also can register device, config, and string descriptors
typedef enum {
  ENUM_DESC_DEVICE    = 0,  /// index qualifier ignored
  ENUM_DESC_CONFIG    = 1,  /// index qualifier ignored
  ENUM_DESC_OTHER     = 2,  /// other speed qualifier
  ENUM_DESC_QUAL      = 3,  /// device qualifier
  ENUM_DESC_STRING    = 4,  /// index is used to futher qualify string descriptor
  ENUM_NUM_DESCRIPTORS
} enum_descriptor_t;

/**
 *  \brief    Initialize the enumeration module
 *  \details  Initialize the enumeration module
 *  \return   Zero (0) for success, non-zero for failure
 */
int enum_init(void);

/**
 *  \brief    Register a descriptor
 *  \details  Register a descriptor
 *  \param    type    type of descriptor being registered
 *  \param    desc    pointer to the descriptor
 *  \param    index   index of the string descriptor. ignored for other descriptor types
 *  \return   Zero (0) for success, non-zero for failure
 */
int enum_register_descriptor(enum_descriptor_t type, const uint8_t *desc, uint8_t index);

/**
 *  \brief    Register an enumeration event callback
 *  \details  Register an enumeration event callback
 *  \param    type    event upon which the callback will occur
 *  \param    func    function to be called
 *  \param    cbdata   data to be passed to the callback function
 *  \return   Zero (0) for success, non-zero for failure
 */
int enum_register_callback(enum_callback_t type, int (*func)(MXC_USB_SetupPkt *sup, void *cbdata), void *cbdata);

/**
 *  \brief    Query an enumeration event callback
 *  \details  Retrieves the callback for an enumeration event
 *  \param    type    event upon which the callback will occur
 *  \param    func    function to be called
 *  \param    cbdata   data to be passed to the callback function
 *  \return   Zero (0) for success, non-zero for failure
 */
int enum_query_callback(enum_callback_t type, int (**func)(MXC_USB_SetupPkt *indata, void *cbdata), void **cbdata);

/**
 *  \brief    Register a handler for device class descriptors
 *  \details  Register a handler for devuce class descriptors. The handler is used to respond to device class
 *            get descriptor requests from the host. The handler function shall update desc and desclen with
 *            a pointer to the descriptor and its length.
 *  \param    func    function to be called
 *  \return   Zero (0) for success, non-zero for failure
 */
int enum_register_getdescriptor(void (*func)(MXC_USB_SetupPkt *sup, const uint8_t **desc, uint16_t *desclen));

/**
 *  \brief    Query the callback for device class descriptors
 *  \details  Retrieves the callback for an enumeration event
 *  \param    func    function to be called
 *  \return   Zero (0) for success, non-zero for failure
 */
int enum_query_getdescriptor(void (**func)(MXC_USB_SetupPkt *sup, const uint8_t **desc, uint16_t *desclen));

/**
 *  \brief    Gets the current configuration value.
 *  \details  Gets the current configuration value.
 *  \return   The current configuration value.
 */
uint8_t enum_getconfig(void);

/**
 *  \brief    Clears the configuration value.
 *  \details  Clears the configuration value. This function should be called when a host disconnect is detected.
 */
void enum_clearconfig(void);

#ifdef __cplusplus
}
#endif

#endif //LIBRARIES_MAXUSB_INCLUDE_ENUMERATE_ENUMERATE_H_
