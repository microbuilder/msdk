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

#ifndef EXAMPLES_MAX78002_USB_MAXUSB_USB_HIDKEYBOARD_DESCRIPTORS_H_
#define EXAMPLES_MAX78002_USB_MAXUSB_USB_HIDKEYBOARD_DESCRIPTORS_H_

#include <stdint.h>
#include "usb.h"
#include "hid_kbd.h"

MXC_USB_device_descriptor_t __attribute__((aligned(4))) device_descriptor = {
    0x12, /* bLength                           */
    0x01, /* bDescriptorType = Device          */
    0x0200, /* bcdUSB USB spec rev (BCD)         */
    0x00, /* bDeviceClass = Unspecified        */
    0x00, /* bDeviceSubClass                   */
    0x00, /* bDeviceProtocol                   */
    0x40, /* bMaxPacketSize0 is 64 bytes       */
    0x0B6A, /* idVendor (Maxim Integrated)       */
    0x003C, /* idProduct                         */
    0x0100, /* bcdDevice                         */
    0x01, /* iManufacturer Descriptor ID       */
    0x02, /* iProduct Descriptor ID            */
    0x03, /* iSerialNumber Descriptor ID       */
    0x01 /* bNumConfigurations                */
};

__attribute__((aligned(4))) struct __attribute__((packed)) {
    MXC_USB_configuration_descriptor_t config_descriptor;
    MXC_USB_interface_descriptor_t interface_descriptor;
    hid_descriptor_t hid_descriptor;
    MXC_USB_endpoint_descriptor_t endpoint_descriptor;
} config_descriptor = { {
                            0x09, /*  bLength                          */
                            0x02, /*  bDescriptorType = Config         */
                            0x0022, /*  wTotalLength(L/H) = 34 bytes     */
                            0x01, /*  bNumInterfaces                   */
                            0x01, /*  bConfigurationValue              */
                            0x00, /*  iConfiguration                   */
                            0xA0, /*  bmAttributes (bus-powered, remote wakeup) */
                            0x32, /*  MaxPower is 100ma (units are 2ma/bit) */
                        },
                        {
                            /*  First Interface Descriptor */
                            0x09, /*  bLength                          */
                            0x04, /*  bDescriptorType = Interface (4)  */
                            0x00, /*  bInterfaceNumber                 */
                            0x00, /*  bAlternateSetting                */
                            0x01, /*  bNumEndpoints (one for OUT)      */
                            0x03, /*  bInterfaceClass = HID            */
                            0x00, /*  bInterfaceSubClass               */
                            0x00, /*  bInterfaceProtocol               */
                            0x00, /*  iInterface */
                        },
                        {
                            /* HID Descriptor */
                            0x09, /*  bFunctionalLength                */
                            0x21, /*  bDescriptorType = HID            */
                            0x0110, /*  bcdHID Rev 1.1                   */
                            0x00, /*  bCountryCode                     */
                            0x01, /*  bNumDescriptors                  */
                            0x22, /*  bDescriptorType = Report         */
                            0x002b, /*  wDescriptorLength                */
                        },
                        {
                            /*  IN Endpoint 3 (Descriptor #1) */
                            0x07, /*  bLength                          */
                            0x05, /*  bDescriptorType (Endpoint)       */
                            0x83, /*  bEndpointAddress (EP3-IN)        */
                            0x03, /*  bmAttributes (interrupt)         */
                            0x0040, /*  wMaxPacketSize                   */
                            0x0a /*  bInterval (milliseconds)         */
                        } };

__attribute__((aligned(4))) uint8_t report_descriptor[] = {
    0x05, 0x01, /*  Usage Page (generic desktop)      */
    0x09, 0x06, /*  Usage (keyboard)                  */
    0xa1, 0x01, /*  Collection                        */
    0x05, 0x07, /*    Usage Page 7 (keyboard/keypad)  */
    0x19, 0xe0, /*    Usage Minimum = 224             */
    0x29, 0xe7, /*    Usage Maximum = 231             */
    0x15, 0x00, /*    Logical Minimum = 0             */
    0x25, 0x01, /*    Logical Maximum = 1             */
    0x75, 0x01, /*    Report Size = 1                 */
    0x95, 0x08, /*    Report Count = 8                */
    0x81, 0x02, /*   Input(Data,Variable,Absolute)    */
    0x95, 0x01, /*    Report Count = 1                */
    0x75, 0x08, /*    Report Size = 8                 */
    0x81, 0x01, /*   Input(Constant)                  */
    0x19, 0x00, /*    Usage Minimum = 0               */
    0x29, 0x65, /*    Usage Maximum = 101             */
    0x15, 0x00, /*    Logical Minimum = 0             */
    0x25, 0x65, /*    Logical Maximum = 101           */
    0x75, 0x08, /*    Report Size = 8                 */
    0x95, 0x01, /*    Report Count = 1                */
    0x81, 0x00, /*   Input(Data,Variable,Array)       */
    0xc0 /*  End Collection                    */
};

__attribute__((aligned(4))) uint8_t lang_id_desc[] = {
    0x04, /* bLength */
    0x03, /* bDescriptorType */
    0x09, 0x04 /* bString = wLANGID (see usb_20.pdf 9.6.7 String) */
};

__attribute__((aligned(4))) uint8_t mfg_id_desc[] = {
    0x22, /* bLength */
    0x03, /* bDescriptorType */
    'M',  0, 'a', 0, 'x', 0, 'i', 0, 'm', 0, ' ', 0, 'I', 0, 'n', 0,
    't',  0, 'e', 0, 'g', 0, 'r', 0, 'a', 0, 't', 0, 'e', 0, 'd', 0,
};

__attribute__((aligned(4))) uint8_t prod_id_desc[] = {
    0x2c, /* bLength */
    0x03, /* bDescriptorType */
    'M',  0, 'A', 0, 'X', 0, '3', 0, '2', 0, '6', 0, '5', 0, '0', 0, ' ', 0, 'H', 0, 'I', 0,
    'D',  0, ' ', 0, 'K', 0, 'e', 0, 'y', 0, 'b', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0,
};

__attribute__((aligned(4))) uint8_t serial_id_desc[] = { 0x20, /* bLength */
                                                         0x03, /* bDescriptorType */
                                                         '0',  0, '0', 0, '0', 0, '0', 0, '0', 0,
                                                         '0',  0, '0', 0, '0', 0, '1', 0 };

#endif // EXAMPLES_MAX78002_USB_MAXUSB_USB_HIDKEYBOARD_DESCRIPTORS_H_
