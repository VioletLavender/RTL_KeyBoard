#ifndef _RFFUNCTION_C_
#define _PROFILE_TAB_C_

#include <stdio.h>
#include "BleAppSetting.h"
#include "host.h"


const Uint8 ATT_HDL_INVALID[] =
{
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00
};                                                                                             //Handle, invalid


const Uint8 ATT_HDL_GAP_PRIMARY_SERVICE[] =                                                    //GAP service: Mandatory
{
    0x00, _GAP_HDL_OFFSET_BASE_,                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_PRIMARY_SERVICE,                                      //Attribute Type (0x28, 0x00)
    SIZE_OF_ATTRIBUTE_VALUE_2,
    GATT_SPEC_SERVICES_GENERIC_ACCESS, GATT_SPEC_SERVICES                                      //Attribute Value (0x00, 0x18)
};


const Uint8 ATT_HDL_GAP_CHARACTERISTIC_DEVICE_NAME[] =                                         //Mandatory
{
    0x00, (_GAP_HDL_OFFSET_BASE_+1),                                                           //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                       //Attribute Type (0x28, 0x03)
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_GAP_HDL_OFFSET_BASE_+2), 0x00,
    GATT_SPEC_CHARACTERISTIC_DEVICE_NAME, GATT_SPEC_CHARACTERISTIC                             //Attribute Value (0x00, 0x2A)
};


const Uint8 ATT_HDL_GAP_DEVICE_NAME_INIT[] =
{
    0x00, (_GAP_HDL_OFFSET_BASE_+2),                                                           //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_DEVICE_NAME,                            //Attribute Type (0x2A, 0x00)
#ifdef _PROFILE_HOGP_
    SIZE_OF_ATTRIBUTE_VALUE_7,
    'R', 'F', '_',
    'H', 'O', 'G', 'P',                                                                        //Attribute Value, "RF_HOGP"
#else
    SIZE_OF_ATTRIBUTE_VALUE_8,
    'B', 'L', 'E', '_',
    'D', 'E', 'M', 'O',                                                                        //Attribute Value, "BLE_DEMO"
#endif
};


Uint8 att_HDL_GAP_DEVICE_NAME[] =
{
    //0x00, (_GAP_HDL_OFFSET_BASE_+2),                                                         //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_DEVICE_NAME,                          //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_8,
#ifdef _PROFILE_HOGP_
    'R', 'F', '_',                                                                             //Attribute Value, "RF_HOGP"
    'H', 'O', 'G', 'P',
#else
    'B', 'L', 'E', '_',
    'D', 'E', 'M', 'O',                                                                        //Attribute Value, "BLE_DEMO"
#endif
};


const Uint8 ATT_HDL_GAP_CHARACTERISTIC_APPEARANCE[] =                                          //Mandatory
{
    0x00, (_GAP_HDL_OFFSET_BASE_+3),                                                           //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                       //Attribute Type (0x28, 0x03)
    SIZE_OF_ATTRIBUTE_VALUE_5,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_GAP_HDL_OFFSET_BASE_+4), 0x00,
    GATT_SPEC_CHARACTERISTIC_APPEARANCE, GATT_SPEC_CHARACTERISTIC                              //Attribute Value (0x01, 0x2A)
};


const Uint8 ATT_HDL_GAP_APPEARANCE[] =
{
    0x00, (_GAP_HDL_OFFSET_BASE_+4),                                                           //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_APPEARANCE,                             //Attribute Type (0x2A, 0x01)
    SIZE_OF_ATTRIBUTE_VALUE_2,
    //0x11, 0x00                                                                               //Attribute Value, according to Test Attribute Server D09r17
#if defined _PROFILE_HOGP_
#if defined _PROFILE_HOGP_MULTI_
    0xC0, 0x03,     //0x03C0: 960 -> Human Interface Device (HID), HID Generic
    //0xC1, 0x03,     //0x03C1: 961 -> Keyboard
#elif defined _PROFILE_HOGP_MOUSE_
    0xC2, 0x03,     //0x03C2: 962 -> Mouse
#elif defined _PROFILE_HOGP_KEYBOARD_
    0xC1, 0x03,     //0x03C1: 961 -> Keyboard
#elif defined _PROFILE_HOGP_COMSUMER_
    0xC0, 0x03,     //0x03C0: 960 -> Human Interface Device (HID), HID Generic
#endif
#elif defined _PROFILE_BLP_
    //0x80, 0x03,   //0x0380: 896 -> Generic Blood Pressure
    0x81, 0x03,     //0x0381: 897 -> Blood Pressure: Arm
    //0x82, 0x03,   //0x0382: 898 -> Blood Pressure: Wrist
#elif defined _PROFILE_HTP_
    //0x00, 0x03,   //0x0300: 768 -> Generic Thermometer
    0x01, 0x03,     //0x0301: 769 -> Thermometer: Ear
#elif defined _PROFILE_RSCP_
    0x40, 0x04,     //0x0440: 1088 -> Running Walking Sensor
    //0x41, 0x04,   //0x0441: 1089 -> Running Walking Sensor: In-Shoe
    //0x42, 0x04,   //0x0442: 1090 -> Running Walking Sensor: On-Shoe
    //0x43, 0x04,   //0x0443: 1091 -> Running Walking Sensor: On-Hip
#elif defined _PROFILE_CSCP_
    //0x80, 0x04,   //0x0480: 1152 -> Generic: Cycling
    //0x81, 0x04,   //0x0481: 1153 -> Cycling: Cycling Computer
    //0x82, 0x04,   //0x0482: 1154 -> Cycling: Speed Sensor
    //0x83, 0x04,   //0x0483: 1155 -> Cycling: Cadence Sensor
    //0x84, 0x04,   //0x0484: 1156 -> Cycling: Power Sensor
    0x85, 0x04,     //0x0485: 1157 -> Cycling: Speed and Cadence Sensor #endif
#elif defined _PROFILE_HRP_
    0x40, 0x03,     //0x0340: 832 -> Generic Heart rate Sensor
    //0x41, 0x03,   //0x0341: 833 -> Heart Rate Sensor: Heart Rate Belt
#else
    0x00, 0x00      //None
#endif
};
//https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.gap.appearance.xml


const Uint8 ATT_HDL_GAP_CHARACTERISTIC_RECONNECTION_ADDRESS[] =                                //Optional, if privacy feature and Peripheral privacy Flag characteristic are supported, else excluded
{
    0x00, (_GAP_HDL_OFFSET_BASE_+5),                                                           //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                       //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        //GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_GAP_HDL_OFFSET_BASE_+6), 0x00,
    GATT_SPEC_CHARACTERISTIC_RECONNECTION_ADDRESS, GATT_SPEC_CHARACTERISTIC                    //Attribute Value
};


const Uint8 ATT_HDL_GAP_RECONNECTION_ADDRESS_INIT[] =
{
    0x00, (_GAP_HDL_OFFSET_BASE_+6),                                                           //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_RECONNECTION_ADDRESS,                   //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_6,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00                                                         //Attribute Value, according to Test Attribute Server D09r17
};


Uint8 att_HDL_GAP_RECONNECTION_ADDRESS[] =
{
    //0x00, (_GAP_HDL_OFFSET_BASE_+6),                                                        //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_RECONNECTION_ADDRESS,                //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_6,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00                                                        //Attribute Value, according to Test Attribute Server D09r17
};


const Uint8 ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG[] =                             //Mandatory if privacy feature is supported, else excluded
{
    0x00, (_GAP_HDL_OFFSET_BASE_+7),                                                           //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                       //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_GAP_HDL_OFFSET_BASE_+8), 0x00,
    GATT_SPEC_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG, GATT_SPEC_CHARACTERISTIC                 //Attribute Value
};


const Uint8 ATT_HDL_GAP_PERIPHERAL_PRIVACY_FLAG[] =
{
    0x00, (_GAP_HDL_OFFSET_BASE_+8),                                                           //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG,                //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0x00                                                                                       //Attribute Value, according to Test Attribute Server D09r17
};


const Uint8 ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS[] =          //Optional
{
    0x00, (_GAP_HDL_OFFSET_BASE_+9),                                                           //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                       //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_GAP_HDL_OFFSET_BASE_+10), 0x00,
    GATT_SPEC_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS, GATT_SPEC_CHARACTERISTIC   //Attribute Value
};


const Uint8 ATT_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS[] =
{
    0x00, (_GAP_HDL_OFFSET_BASE_+10),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,  //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_8,
    0x06, 0x00,                                                                                     //Attribute Value, Minimum Connection Interval: 7.500 ms
    0x08, 0x00,                                                                                     //Attribute Value, Maximum Connection Interval: 10.00 ms
    0x00, 0x00,                                                                                     //Attribute Value, Slave Latency: 0
    0x58, 0x02,                                                                                      //Attribute Value, Timeout Multiplier: 600
};


const Uint8 ATT_HDL_GATT_PRIMARY_SERVICE[] =                                                        //GATT service: Mandatory
{
    0x00, _GATT_HDL_OFFSET_BASE_,                                                                   //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_PRIMARY_SERVICE,                                           //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    GATT_SPEC_SERVICES_GENERIC_ATTRIBUTE, GATT_SPEC_SERVICES                                        //Attribute Value
};


const Uint8 ATT_HDL_GATT_CHARACTERISTIC_SERVICE_CHANGED[] =                                         //Optional
{
    0x00, (_GATT_HDL_OFFSET_BASE_+1),                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        GATT_DECLARATIONS_PROPERTIES_INDICATE |                                                     //Indicate: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_GATT_HDL_OFFSET_BASE_+2), 0x00,
    GATT_SPEC_CHARACTERISTIC_SERVICE_CHANGED, GATT_SPEC_CHARACTERISTIC   //Attribute Value
};


const Uint8 ATT_HDL_GATT_SERVICE_CHANGED_INIT[] =
{
    0x00, (_GATT_HDL_OFFSET_BASE_+2),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_SERVICE_CHANGED,  //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_4,
    0x01, 0x00,                                                                                     //Start of Affected Attribute Handle Range
    0xFF, 0xFF,                                                                                     //End of Affected Attribute Handle Range
};      //Bluetooth Spec. Ver4.0 [Vol 3] page 529 of 656


const Uint8 ATT_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    0x00, (_GATT_HDL_OFFSET_BASE_+3),                                                               //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_GATT_SERVICE_CHANGED[] =
{
    //0x00, (_GATT_HDL_OFFSET_BASE_+2),                                                             //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_SERVICE_CHANGED,  //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_4,
    0x00, 0x00,                                                                                     //Start of Affected Attribute Handle Range
    0x00, 0x00,                                                                                     //End of Affected Attribute Handle Range
};      //Bluetooth Spec. Ver4.0 [Vol 3] page 529 of 656


Uint8 att_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_GATT_HDL_OFFSET_BASE_+3),                                                             //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_DIS_PRIMARY_SERVICE[] =                                                         //Device Information Service
{
    0x00, _DIS_HDL_OFFSET_BASE_,                                                                    //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_PRIMARY_SERVICE,                                           //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    GATT_SPEC_SERVICES_DEVICE_INFORMATION, GATT_SPEC_SERVICES                                       //Attribute Value
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_SERIAL_NUMBER_STRING[] =                                     //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+1),                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+2), 0x00,
    GATT_SPEC_CHARACTERISTIC_SERIAL_NUMBER_STRING, GATT_SPEC_CHARACTERISTIC                         //Attribute Value
};


const Uint8 ATT_HDL_DIS_SERIAL_NUMBER_STRING[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+2),                                                                //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_SERIAL_NUMBER_STRING,                        //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_4,
    0x31, 0x35, 0x38, 0x37                                                                          //Attribute Value, "1587"
};


const Uint8 ATT_HDL_DIS_SERIAL_NUMBER_STRING_PRESENTATION_FORMAT[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+3),                                                                //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UTF8S,                                                               //Attribute Value, Format: UTF-8 string
    0x00,                                                                                           //Attribute Value, Exponent: 0
    0x00, 0x00,                                                                                     //Attribute Value, Unit: [0x0000] **The Unit is a UUID**
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Attribute Value, Name Space: 0x01
    0x00, 0x00                                                                                      //Attribute Value, Description: 0x0000
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_MANUFACTURER_NAME_STRING[] =                                 //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+4),                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+5), 0x00,
    GATT_SPEC_CHARACTERISTIC_MANUFACTURER_NAME_STRING, GATT_SPEC_CHARACTERISTIC                     //Attribute Value
};


const Uint8 ATT_HDL_DIS_MANUFACTURER_NAME_STRING[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+5),                                                                //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_MANUFACTURER_NAME_STRING,                    //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_6,
    'R', 'F', '_', 'B', 'L', 'E'                                                                    //Attribute Value, "RF_BLE"
};


const Uint8 ATT_HDL_DIS_MANUFACTURER_NAME_STRING_PRESENTATION_FORMAT[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+6),                                                                //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UTF8S,                                                               //Attribute Value, Format: UTF-8 string
    0x00,                                                                                           //Attribute Value, Exponent: 0
    0x00, 0x00,                                                                                     //Attribute Value, Unit: [0x0000] **The Unit is a UUID**
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Attribute Value, Name Space: 0x01
    0x00, 0x00                                                                                      //Attribute Value, Description: 0x0000
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_SYSTEM_ID[] =                                                //Optonal
{
    0x00, (_DIS_HDL_OFFSET_BASE_+7),                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+8), 0x00,
    GATT_SPEC_CHARACTERISTIC_SYSTEM_ID, GATT_SPEC_CHARACTERISTIC                                    //Attribute Value
};


const Uint8 ATT_HDL_DIS_SYSTEM_ID[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+8),                                                                //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_SYSTEM_ID,                                   //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_8,
    0x55, 0xAA, 0x55, 0xAA, 0x55,                                                                   //Attribute Value, Manufacturer
    0xAA, 0x55, 0xAA                                                                                //Attribute Value, Organizationally Unique ID
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_FIRMWARE_REVISION_STRING[] =                                 //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+9),                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+10), 0x00,
    GATT_SPEC_CHARACTERISTIC_FIRMWARE_REVISION_STRING, GATT_SPEC_CHARACTERISTIC                     //Attribute Value
};


const Uint8 ATT_HDL_DIS_FIRMWARE_REVISION_STRING[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+10),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_FIRMWARE_REVISION_STRING,                    //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_4,
    0x30, 0x31, 0x2E, 0x31                                                                          //Attribute Value, "01.1"
};


const Uint8 ATT_HDL_DIS_FIRMWARE_REVISION_STRING_PRESENTATION_FORMAT[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+11),                                                               //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UTF8S,                                                               //Attribute Value, Format: UTF-8 string
    0x00,                                                                                           //Attribute Value, Exponent: 0
    0x00, 0x00,                                                                                     //Attribute Value, Unit: [0x0000] **The Unit is a UUID**
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Attribute Value, Name Space: 0x01
    0x00, 0x00                                                                                      //Attribute Value, Description: 0x0000
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_MODEL_NUMBER_STRING[] =                                      //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+12),                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+13), 0x00,
    GATT_SPEC_CHARACTERISTIC_MODEL_NUMBER_STRING, GATT_SPEC_CHARACTERISTIC                          //Attribute Value
};


const Uint8 ATT_HDL_DIS_MODEL_NUMBER_STRING[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+13),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_MODEL_NUMBER_STRING,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_6,
    'R', 'F', '_', 'B', 'L', 'E'                                                                    //Attribute Value, "RF_BLE"
};


const Uint8 ATT_HDL_DIS_MODEL_NUMBER_STRING_PRESENTATION_FORMAT[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+14),                                                               //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UTF8S,                                                               //Attribute Value, Format: UTF-8 string
    0x00,                                                                                           //Attribute Value, Exponent: 0
    0x00, 0x00,                                                                                     //Attribute Value, Unit: [0x0000] **The Unit is a UUID**
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Attribute Value, Name Space: 0x01
    0x00, 0x00                                                                                      //Attribute Value, Description: 0x0000
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_HARDWARE_REVISION_STRING[] =                                 //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+15),                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+16), 0x00,
    GATT_SPEC_CHARACTERISTIC_HARDWARE_REVISION_STRING, GATT_SPEC_CHARACTERISTIC                     //Attribute Value
};


const Uint8 ATT_HDL_DIS_HARDWARE_REVISION_STRING[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+16),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_HARDWARE_REVISION_STRING,                    //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_3,
    0x55, 0x30, 0x31                                                                                //Attribute Value, "U01"
};


const Uint8 ATT_HDL_DIS_HARDWARE_REVISION_STRING_PRESENTATION_FORMAT[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+17),                                                               //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UTF8S,                                                               //Attribute Value, Format: UTF-8 string
    0x00,                                                                                           //Attribute Value, Exponent: 0
    0x00, 0x00,                                                                                     //Attribute Value, Unit: [0x0000] **The Unit is a UUID**
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Attribute Value, Name Space: 0x01
    0x00, 0x00                                                                                      //Attribute Value, Description: 0x0000
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_SOFTWARE_REVISION_STRING[] =                                 //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+18),                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+19), 0x00,
    GATT_SPEC_CHARACTERISTIC_SOFTWARE_REVISION_STRING, GATT_SPEC_CHARACTERISTIC                     //Attribute Value
};


const Uint8 ATT_HDL_DIS_SOFTWARE_REVISION_STRING[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+19),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_SOFTWARE_REVISION_STRING,                    //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_4,
    0x30, 0x30, 0x39, 0x33                                                                          //Attribute Value, "0093"
};


const Uint8 ATT_HDL_DIS_SOFTWARE_REVISION_STRING_PRESENTATION_FORMAT[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+20),                                                               //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UTF8S,                                                               //Attribute Value, Format: UTF-8 string
    0x00,                                                                                           //Attribute Value, Exponent: 0
    0x00, 0x00,                                                                                     //Attribute Value, Unit: [0x0000] **The Unit is a UUID**
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Attribute Value, Name Space: 0x01
    0x00, 0x00                                                                                      //Attribute Value, Description: 0x0000
};


const Uint8 ATT_HDL_DIS_CHARACTERISTIC_PNP_ID[] =                                                   //Optional
{
    0x00, (_DIS_HDL_OFFSET_BASE_+21),                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x02,
    (
        //Characteristic Properties, Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_DIS_HDL_OFFSET_BASE_+22), 0x00,
    GATT_SPEC_CHARACTERISTIC_PNP_ID, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_DIS_PNP_ID[] =
{
    0x00, (_DIS_HDL_OFFSET_BASE_+22),                                                               //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_PNP_ID,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    BLE_GATT_DIS_PNPID_VID_SOURCE_BLUETOOTH_SIG,                                                    //Vendor ID Source, identifies the source of the Vendor ID field.
    BLE_COMPANY_ID_L, BLE_COMPANY_ID_H,                                                             //Vendor ID
    0x00, 0x00,                                                                                     //Product ID: Manufacturer managed identifier for this product
    0x00, 0x00                                                                                      //Product Version: Manufacturer managed version for this product
};


#ifdef _PROFILE_BAS_
const Uint8 ATT_HDL_BAS_PRIMARY_SERVICE[] =
{
    0x00, _BAS_HDL_OFFSET_BASE_,                                                                    //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_PRIMARY_SERVICE,                                           //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    GATT_SPEC_SERVICES_BATTERY_SERVICE, GATT_SPEC_SERVICES                                          //Attribute Value
};


const Uint8 ATT_HDL_BAS_CHARACTERISTIC_BATTERY_LEVEL[] =
{
    0x00, (_BAS_HDL_OFFSET_BASE_+1),                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_BAS_HDL_OFFSET_BASE_+2), 0x00,
    GATT_SPEC_CHARACTERISTIC_BATTERY_LEVEL, GATT_SPEC_CHARACTERISTIC                                //Attribute Value
};


const Uint8 ATT_HDL_BAS_BATTERY_LEVEL_INIT[] =
{
    0x00, (_BAS_HDL_OFFSET_BASE_+2),                                                                //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BATTERY_LEVEL,                               //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    100,                                                                                            //Attribute Value
};

/*
const Uint8 ATT_HDL_BAS_BATTERY_LEVEL_PRESENTATION_FORMAT[] =
{
    0x00, 0x43,                                                                                     //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_PRESENTATION_FORMAT,                          //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_7,
    GATT_CHARACTERISTIC_FORMAT_UINT8,                                                               //Format: unsigned 8-bit integer
    0x00,                                                                                           //Exponent
    0x00,0x00,                                                                                      //UNIT: UUID
    GATT_CHARACTERISTIC_BLUETOOTH_NAMESPACE_BLUETOOTH_SIG,                                          //Namespace: Bluetooth SIG Assigned Numbers
    0x00,0x00                                                                                       //Description: 0x0000
};
*/

const Uint8 ATT_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =                                //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_BAS_HDL_OFFSET_BASE_+3),                                                                //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_BAS_BATTERY_LEVEL[] =
{
    //0x00, (_BAS_HDL_OFFSET_BASE_+2),                                                              //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BATTERY_LEVEL,                             //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    100,                                                                                            //Attribute Value
};


Uint8 att_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_BAS_HDL_OFFSET_BASE_+3),                                                              //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_BAS_CHARACTERISTIC_BATTERY_POWER_STATE[] =
{
    0x00, (_BAS_HDL_OFFSET_BASE_+4),                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_BAS_HDL_OFFSET_BASE_+5), 0x00,
    GATT_SPEC_CHARACTERISTIC_BATTERY_POWER_STATE, GATT_SPEC_CHARACTERISTIC                          //Attribute Value
};


const Uint8 ATT_HDL_BAS_BATTERY_POWER_STATE_INIT[] =
{
    0x00, (_BAS_HDL_OFFSET_BASE_+5),                                                                //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BATTERY_POWER_STATE,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0,                                                                                              //Attribute Value
};


Uint8 att_HDL_BAS_BATTERY_POWER_STATE[] =
{
    //0x00, (_BAS_HDL_OFFSET_BASE_+5),                                                              //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BATTERY_LEVEL,                             //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    0,                                                                                              //Attribute Value
};
#endif


#ifdef _PROFILE_HOGP_
const Uint8 ATT_HDL_HIDS_PRIMARY_SERVICE[] =
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x00),                                                            //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_PRIMARY_SERVICE,                                           //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    GATT_SPEC_SERVICES_HUMAN_INTERFACE_DEVICE, GATT_SPEC_SERVICES                                   //Attribute Value
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_HID_INFORMATION[] =
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x01),
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_BASE_+0x02), 0x00,
    GATT_SPEC_CHARACTERISTIC_HID_INFORMATION, GATT_SPEC_CHARACTERISTIC                              //Attribute Value
};


const Uint8 ATT_HDL_HIDS_HID_INFORMATION[] =
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x02),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_HID_INFORMATION,                             //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_4,
    0x13, 0x02,     //bcdHID: 0x0213
    0x40,           //bCountryCode: 0x40
    0x01,           //Flags: 0x_1 (providing wake-up signal to a HID host)
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_HID_CONTROL_POINT[] =
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x03),
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        //GATT_DECLARATIONS_PROPERTIES_READ |                                                       //Notify: Optional
        GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_BASE_+0x04), 0x00,
    GATT_SPEC_CHARACTERISTIC_HID_CONTROL_POINT, GATT_SPEC_CHARACTERISTIC                            //Attribute Value
};


const Uint8 ATT_HDL_HIDS_HID_CONTROL_POINT_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x04),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_HID_CONTROL_POINT,                           //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0x01,                       //0: Suspend, 1: Exit Suspend
};


Uint8 att_HDL_HIDS_HID_CONTROL_POINT[] =
{
    //0x00, (_HOGP_HDL_OFFSET_BASE_+0x04),                                                          //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_HID_CONTROL_POINT,                         //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    0x01,                       //0: Suspend, 1: Exit Suspend
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MAP[] =
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x05),                                                            //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_BASE_+0x06), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT_MAP, GATT_SPEC_CHARACTERISTIC                                   //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MAP[] =    //Device Class Definition for Human Interface Devices (HID) Version 1.11, 6.2.2 Report Descriptor
{
    0x00, (_HOGP_HDL_OFFSET_BASE_+0x06),                                                            //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT_MAP,                                  //Attribute Type
    //(SIZE_OF_ATTRIBUTE_VALUE_0+33+2+82+2+54+2),
#ifndef _PROFILE_HOGP_EMC_
    (SIZE_OF_ATTRIBUTE_VALUE_MS+SIZE_OF_ATTRIBUTE_VALUE_KB+SIZE_OF_ATTRIBUTE_VALUE_CS),

#ifdef _PROFILE_HOGP_KEYBOARD_
    0x05, 0x01,
    0x09, 0x06,
    0xa1, 0x01,
#ifdef _PROFILE_HOGP_MULTI_
    0x85, (0x00+__PROFILE_HOGP_KEYBOARD_RPIDOFST_),
#endif
    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x03,
    0x75, 0x01,
    0x95, 0x03,
    0x15, 0x00,
    0x25, 0x01,
    0x91, 0x02,
    0x95, 0x05,
    0x91, 0x01,
    0x05, 0x07,
    0x19, 0xe0,
    0x29, 0xe7,
    0x95, 0x08,
    0x81, 0x02,
    0x75, 0x08,
    0x95, 0x01,
    0x81, 0x01,
    0x19, 0x00,
    0x29, 0x91,
    0x26, 0xff, 0x00,
    0x95, 0x06,
    0x81, 0x00,
#ifdef _PROFILE_HOGP_KEYBOARD_PHOTO_
    0x05, 0x0C,
    0x09, 0x01,
    0x15, 0x00,
    0x25, 0x01,
    0x09, 0xE9,
    0x09, 0xEA,
    0x75, 0x01,
    0x95, 0x02,
    0x81, 0x02,
    0x09, 0xE2,
    0x09, 0x00,
    0x81, 0x06,
    0x09, 0x00,
    0x95, 0x04,
    0x81, 0x02,
#endif
    0xc0,
#endif
#ifdef _PROFILE_HOGP_MOUSE_
    0x05, 0x01,
    0x09, 0x02,
    0xA1, 0x01,
    0x09, 0x01,
    0xA1, 0x00,
    0x05, 0x09,
#ifdef _PROFILE_HOGP_MULTI_
    0x85, 0x02,
#endif
    0x19, 0x01,
    0x29, 0x05,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x05,
    0x75, 0x01,
    0x81, 0x02,
    0x95, 0x01,
    0x75, 0x03,
    0x81, 0x03,
    0x05, 0x01,
    0x09, 0x30,
    0x09, 0x31,
    0x16, 0x00, 0xF8,
    0x26, 0xFF, 0x07,
    0x75, 0x10,
    0x95, 0x02,
    0x81, 0x06,
    0x09, 0x38,
    0x15, 0x80,
    0x25, 0x7F,
    0x75, 0x08,
    0x95, 0x01,
    0x81, 0x06,
    0x09, 0x01,
    0x15, 0x00,
    0x25, 0x03,
    0x95, 0x01,
    0x75, 0x02,
    0xB1, 0x02,
    0x95, 0x01,
    0x75, 0x06,
    0xB1, 0x03,

    0x05, 0x0C,
    0x95, 0x01,
    0x75, 0x10,
    0x16, 0x01, 0x80,
    0x26, 0xFF, 0x7F,
    0x0A, 0x38, 0x02,
    0x81, 0x06,

    0xC0, 0xC0,
#endif      //#ifdef _PROFILE_HOGP_MOUSE_
#ifdef _PROFILE_HOGP_COMSUMER_
    0x05, 0x0C,
    0x09, 0x01,
    0xA1, 0x01,
#ifdef _PROFILE_HOGP_MULTI_
    0x85, 0x03,
#endif
    0x19, 0x00,
    0x2A, 0x9C, 0x02,
    0x15, 0x00,
    0x26, 0x9C, 0x02,
    0x75, 0x10,
    0x95, 0x01,
    0x81, 0x00,
    0xC0,
#endif
#else       //#ifndef _PROFILE_HOGP_EMC_
#ifdef _PROFILE_HOGP_EMC_1501_
#ifdef _PROFILE_HOGP_EMC_1503_
    (SIZE_OF_ATTRIBUTE_VALUE_124-23+5-6+20+66),
#else
    (SIZE_OF_ATTRIBUTE_VALUE_124-23+5-6+66),
#endif
    0x05, 0x01,
    0x09, 0x06,
    0xA1, 0x01,
    0x85, 0x02,
    0x05, 0x07,
    0x19, 0xE0,
    0x29, 0xE7,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,
    0x75, 0x08,
    0x95, 0x01,
    0x81, 0x01,
    0x19, 0x00,
    0x29, 0x65,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x06,
    0x81, 0x00,
    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x05,
    0x91, 0x02,
    0x75, 0x03,
    0x95, 0x01,
    0x91, 0x01,
    0xC0,

    0x05, 0x01,
    0x09, 0x02,
    0xA1, 0x01,
    0x85, 0x01,
    0x09, 0x01,
    0xA1, 0x00,
    0x05, 0x09,
    0x19, 0x01,
    0x29, 0x02,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x02,
    0x81, 0x02,
    0x95, 0x06,
    0x81, 0x03,
    0x05, 0x01,
    0x09, 0x30,
    0x09, 0x31,
    0x09, 0x38,
    0x15, 0x81,
    0x25, 0x7F,
    0x75, 0x08,
    0x95, 0x03,
    0x81, 0x06,
    0xC0,
    0x06, 0x00, 0xFF,
    0x85, 0x0D,
    0x09, 0xC5,
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x14,
    0xB1, 0x02,
    0x85, 0x0C,
    0x09, 0xC6,
    0x95, 0x14,
    0x75, 0x08,
    0xB1, 0x02,
    0x85, 0x0B,
    0x09, 0xC7,
    0x95, 0x14,
    0x75, 0x08,
    0xB1, 0x02,
    0x09, 0x01,
    0x85, 0x5D,
    0x95, 0x14,
    0x75, 0x08,
    0x81, 0x06,
#ifdef _PROFILE_HOGP_EMC_1503_
    0x85, 0x81,
    0x09, 0x01,
    0x95, 0x14,
    0x75, 0x08,
    0x81, 0x06,
    0x85, 0x82,
    0x09, 0x01,
    0x95, 0x14,
    0x75, 0x08,
    0x81, 0x06,
#endif
    0xC0
#else
    (SIZE_OF_ATTRIBUTE_VALUE_124+51),
    0x05, 0x01,
    0x09, 0x06,
    0xA1, 0x01,
    0x85, 0x02,
    0x05, 0x07,
    0x19, 0xE0,
    0x29, 0xE7,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,
    0x75, 0x08,
    0x95, 0x01,
    0x81, 0x01,
    0x19, 0x00,
    0x29, 0x65,
    //0x15, 0x00,
    //0x25, 0x65,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x06,
    0x81, 0x00,
    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x05,
    0x91, 0x02,
    0x75, 0x03,
    0x95, 0x01,
    0x91, 0x01,
    0xC0,
    0x05, 0x01,
    0x09, 0x02,
    0xA1, 0x01,
    0x09, 0x01,
    0xA1, 0x00,
    0x05, 0x09,
    0x85, 0x01,
    0x19, 0x01,
    0x29, 0x03,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x03,
    0x81, 0x02,
    0x75, 0x05,
    0x95, 0x01,
    0x81, 0x01,
    0x05, 0x01,
    0x09, 0x30,
    0x09, 0x31,
    0x15, 0x81,
    0x25, 0x7F,
    0x75, 0x08,
    0x95, 0x02,
    0x81, 0x06,
    0x09, 0x38,
    0x95, 0x01,
    0x81, 0x06,
    0xC0,
    0xC0,
    0x06, 0x12, 0x0F,
    0x0A, 0x12, 0x0F,
    0xA1, 0x01,
    0x85, 0x81,
    0x09, 0x01,
    0x75, 0x08,
    0x95, 0x14,
    0x16, 0x00, 0x00,
    0x26, 0xFF, 0x00,
    0x81, 0x00,
    0x09, 0x00,
    0x85, 0x05,
    0x75, 0x08,
    0x95, 0x07,
    0xB1, 0x02,
    0x09, 0x00,
    0x85, 0x08,
    0x95, 0x07,
    0xB1, 0x02,
    0x09, 0x00,
    0x85, 0x09,
    0x95, 0x07,
    0xB1, 0x02,
    0xC0,
#endif
#endif      //#ifndef _PROFILE_HOGP_EMC_
};


#ifdef _PROFILE_HOGP_COMSUMER_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_CSI[] =
{
    0x00, _HOGP_HDL_OFFSET_CONSUMER_,                                                               //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_CONSUMER_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_CSI_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_CONSUMER_+0x01),                                                        //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_CSI[] =
{
    //0x00, (_HOGP_HDL_OFFSET_CONSUMER_+0x01),                                                      //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_6,
    0x00, 0x00,
};


const Uint8 ATT_HDL_HIDS_REPORT_CSI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =                    //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_CONSUMER_+0x02),                                                        //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_REPORT_CSI_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_CONSUMER_+0x02),                                                      //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_HIDS_REPORT_CSI_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_CONSUMER_+0x03),                                                        //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    (0x00+__PROFILE_HOGP_CS_RPIDOFST_),                                                             //Attribute Value, Report ID
    0x01                                                                                            //Attribute Value, Report Type: Input (0x01)
};
#endif      //#ifdef _PROFILE_HOGP_COMSUMER_

#ifndef _PROFILE_HOGP_EMC_
#ifdef _PROFILE_HOGP_MOUSE_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MSI[] =
{
    0x00, _HOGP_HDL_OFFSET_MOUSE_,                                                                  //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_MOUSE_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MSI_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x01),                                                           //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_MSI[] =
{
    //0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x01),                                                         //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_6,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const Uint8 ATT_HDL_HIDS_REPORT_MSI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =                    //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x02),                                                           //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_REPORT_MSI_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x02),                                                         //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_HIDS_REPORT_MSI_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x03),                                                           //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    (0x00+__PROFILE_HOGP_MS_RPIDOFST_),                                                             //Attribute Value, Report ID
    0x01                                                                                            //Attribute Value, Report Type: Input (0x01)
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MSF[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x04),
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_MOUSE_+0x05), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MSF_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x05),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0x03                                                                                            //Attribute Value
};


Uint8 att_HDL_HIDS_REPORT_MSF[] =
{
    //0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x05),                                                         //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    0x03,                                                                                           //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MSF_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x06),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    (0x00+__PROFILE_HOGP_MS_RPIDOFST_),                                                             //Attribute Value, Report ID
    0x03                                                                                            //Attribute Value, Report Type: Feature (0x03)
};


const Uint8 ATT_HDL_HIDS_REPORT_MSF_USER_DESCRIPTION[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x07),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_USER_DESCRIPTION,                             //Attribute Type
    (SIZE_OF_ATTRIBUTE_VALUE_0+65),
    0x42, 0x4C, 0x45, 0x20, 0x4D, 0x4F, 0x55, 0x53,
    0x45, 0x20, 0x52, 0x45, 0x53, 0x4F, 0x4C, 0x55,
    0x54, 0x49, 0x4F, 0x4E, 0x20, 0x49, 0x4E, 0x20,
    0x43, 0x50, 0x49, 0x0A, 0x20, 0x30, 0x20, 0x3D,
    0x20, 0x34, 0x30, 0x30, 0x0A, 0x20, 0x31, 0x20,
    0x3D, 0x20, 0x38, 0x30, 0x30, 0x0A, 0x20, 0x32,
    0x20, 0x3D, 0x20, 0x31, 0x32, 0x30, 0x30, 0x0A,
    0x20, 0x33, 0x20, 0x3D, 0x20, 0x31, 0x36, 0x30,
    0x30,
};
#endif      //#ifdef _PROFILE_HOGP_MOUSE_


#ifdef _PROFILE_HOGP_KEYBOARD_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBI[] =
{
    0x00, _HOGP_HDL_OFFSET_KB_,                                                                     //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_KB_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_KBI_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x01),                                                              //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
#ifdef _PROFILE_HOGP_KEYBOARD_PHOTO_
    SIZE_OF_ATTRIBUTE_VALUE_9,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#else
    SIZE_OF_ATTRIBUTE_VALUE_8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#endif
};


Uint8 att_HDL_HIDS_REPORT_KBI[] =
{
    //0x00, (_HOGP_HDL_OFFSET_KB_+0x01),                                                            //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_9,
#ifdef _PROFILE_HOGP_KEYBOARD_PHOTO_
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#else
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#endif
};


const Uint8 ATT_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =                    //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x02),                                                              //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_KB_+0x02),                                                            //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_HIDS_REPORT_KBI_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x03),                                                              //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    (0x00+__PROFILE_HOGP_KEYBOARD_RPIDOFST_),                                                       //Attribute Value, Report ID
    0x01                                                                                            //Attribute Value, Report Type: Input (0x01)
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBO[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x04),
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_KB_+0x05), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_KBO_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x05),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0x03                                                                                            //Attribute Value
};


Uint8 att_HDL_HIDS_REPORT_KBO[] =
{
    //0x00, (_HOGP_HDL_OFFSET_KB_+0x05),                                                            //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    0x03,                                                                                           //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_KBO_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x06),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    (0x00+__PROFILE_HOGP_KEYBOARD_RPIDOFST_),                                                       //Attribute Value, Report ID : 01
    0x02                                                                                            //Attribute Value, Report Type: Output (0x02)
};
#endif      //#ifdef _PROFILE_HOGP_MOUSE_
#else       //#ifndef _PROFILE_HOGP_EMC_
#ifdef _PROFILE_HOGP_MOUSE_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MSI[] =
{
    0x00, _HOGP_HDL_OFFSET_MOUSE_,                                                                  //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_MOUSE_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MSI_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x01),                                                           //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_4,
    0x00, 0x00, 0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_MSI[] =
{
    //0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x01),                                                         //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_4,
    0x00, 0x00, 0x00, 0x00,                                                                         //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};


const Uint8 ATT_HDL_HIDS_REPORT_MSI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =                    //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x02),                                                           //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_REPORT_MSI_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x02),                                                         //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_HIDS_REPORT_MSI_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x03),                                                           //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
#ifdef _PROFILE_HOGP_EMC_1501_
    0x01,
#else
    0x02,                                                                                           //Attribute Value, Report ID
#endif
    0x01                                                                                            //Attribute Value, Report Type: Input (0x01)
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MSF[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x04),
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_MOUSE_+0x05), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MSF_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x05),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0x03                                                                                            //Attribute Value
};


Uint8 att_HDL_HIDS_REPORT_MSF[] =
{
    //0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x05),                                                         //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    0x03,                                                                                           //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_MSF_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x06),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
#ifdef _PROFILE_HOGP_EMC_1501_
    0x01,
#else
    0x02,                                                                                           //Attribute Value, Report ID
#endif
    0x03                                                                                            //Attribute Value, Report Type: Feature (0x03)
};


const Uint8 ATT_HDL_HIDS_REPORT_MSF_USER_DESCRIPTION[] =
{
    0x00, (_HOGP_HDL_OFFSET_MOUSE_+0x07),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CHARACTERISTIC_USER_DESCRIPTION,                             //Attribute Type
    (SIZE_OF_ATTRIBUTE_VALUE_0+7),
    0x46, 0x6F, 0x72, 0x20, 0x45, 0x4D, 0x43
};
#endif      //#ifdef _PROFILE_HOGP_MOUSE_


#ifdef _PROFILE_HOGP_KEYBOARD_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBI[] =
{
    0x00, _HOGP_HDL_OFFSET_KB_,                                                                     //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_KB_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC                                       //Attribute Value
};


const Uint8 ATT_HDL_HIDS_REPORT_KBI_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x01),                                                              //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                      //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_KBI[] =
{
    //0x00, (_HOGP_HDL_OFFSET_KB_+0x01),                                                            //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const Uint8 ATT_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =                    //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x02),                                                              //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_KB_+0x02),                                                            //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_HIDS_REPORT_KBI_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_KB_+0x03),                                                              //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    (0x00+__PROFILE_HOGP_KEYBOARD_RPIDOFST_),                                                       //Attribute Value, Report ID
    0x01                                                                                            //Attribute Value, Report Type: Input (0x01)
};
#endif      //#ifdef _PROFILE_HOGP_KEYBOARD_


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_81[] =
{
    0x00, _HOGP_HDL_OFFSET_81_,
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_81_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC
};


const Uint8 ATT_HDL_HIDS_REPORT_81_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_81_+0x01),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
    SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_81[] =
{
    //0x00, (_HOGP_HDL_OFFSET_81_+0x01),
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
    //SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};


const Uint8 ATT_HDL_HIDS_REPORT_81_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_81_+0x02),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,
    0x00
};


Uint8 att_HDL_HIDS_REPORT_81_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_81_+0x02),
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),
    0x00
};


const Uint8 ATT_HDL_HIDS_REPORT_81_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_81_+0x03),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,
    SIZE_OF_ATTRIBUTE_VALUE_2,
//#ifdef _PROFILE_HOGP_EMC_1501_
//    0x5D,
//#else
    0x81,
//#endif
    0x01
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_82[] =
{
    0x00, _HOGP_HDL_OFFSET_82_,
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_82_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC
};


const Uint8 ATT_HDL_HIDS_REPORT_82_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_82_+0x01),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
    SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_82[] =
{
    //0x00, (_HOGP_HDL_OFFSET_82_+0x01),
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
    //SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};


const Uint8 ATT_HDL_HIDS_REPORT_82_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_82_+0x02),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,
    0x00
};


Uint8 att_HDL_HIDS_REPORT_82_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_82_+0x02),
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),
    0x00
};


const Uint8 ATT_HDL_HIDS_REPORT_82_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_82_+0x03),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x82,
    0x01
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_5D[] =
{
    0x00, _HOGP_HDL_OFFSET_5D_,
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_5D_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC
};


const Uint8 ATT_HDL_HIDS_REPORT_5D_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_5D_+0x01),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
    SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};


Uint8 att_HDL_HIDS_REPORT_5D[] =
{
    //0x00, (_HOGP_HDL_OFFSET_5D_+0x01),
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
    //SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};


const Uint8 ATT_HDL_HIDS_REPORT_5D_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_5D_+0x02),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,
    0x00
};


Uint8 att_HDL_HIDS_REPORT_5D_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_5D_+0x02),
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),
    0x00
};


const Uint8 ATT_HDL_HIDS_REPORT_5D_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_5D_+0x03),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x5D,
    0x01
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_05[] =
{
    0x00, _HOGP_HDL_OFFSET_05_,
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_05_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC
};


const Uint8 ATT_HDL_HIDS_REPORT_05_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_05_+0x01),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
#ifdef _PROFILE_HOGP_EMC_1501_
    SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
#else
    SIZE_OF_ATTRIBUTE_VALUE_7,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif
};


Uint8 att_HDL_HIDS_REPORT_05[] =
{
    //0x00, (_HOGP_HDL_OFFSET_05_+0x01),
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
#ifdef _PROFILE_HOGP_EMC_1501_
    //SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
#else
    //SIZE_OF_ATTRIBUTE_VALUE_7,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif
};


/*
const Uint8 ATT_HDL_HIDS_REPORT_05_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_05_+0x02),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,
    0x00
};


Uint8 att_HDL_HIDS_REPORT_05_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_05_+0x02),
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    {
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    },
    0x00
};
*/


const Uint8 ATT_HDL_HIDS_REPORT_05_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_05_+0x03-0x01),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,
    SIZE_OF_ATTRIBUTE_VALUE_2,
#ifdef _PROFILE_HOGP_EMC_1501_
    0x0B,
#else
    0x05,
#endif
    0x03
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_08[] =
{
    0x00, _HOGP_HDL_OFFSET_08_,
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_08_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC
};


const Uint8 ATT_HDL_HIDS_REPORT_08_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_08_+0x01),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
#ifdef _PROFILE_HOGP_EMC_1501_
    SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
#else
    SIZE_OF_ATTRIBUTE_VALUE_7,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif
};


Uint8 att_HDL_HIDS_REPORT_08[] =
{
    //0x00, (_HOGP_HDL_OFFSET_08_+0x01),
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
#ifdef _PROFILE_HOGP_EMC_1501_
    //SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
#else
    //SIZE_OF_ATTRIBUTE_VALUE_7,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif
};


/*
const Uint8 ATT_HDL_HIDS_REPORT_08_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_08_+0x02),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,
    0x00
};


Uint8 att_HDL_HIDS_REPORT_08_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_08_+0x02),
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    {
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    },
    0x00
};
*/


const Uint8 ATT_HDL_HIDS_REPORT_08_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_08_+0x03-0x01),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,
    SIZE_OF_ATTRIBUTE_VALUE_2,
#ifdef _PROFILE_HOGP_EMC_1501_
    0x0C,
#else
    0x08,
#endif
    0x03
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_REPORT_09[] =
{
    0x00, _HOGP_HDL_OFFSET_09_,
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |
        GATT_DECLARATIONS_PROPERTIES_READ |
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_09_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_REPORT, GATT_SPEC_CHARACTERISTIC
};


const Uint8 ATT_HDL_HIDS_REPORT_09_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_09_+0x01),
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
#ifdef _PROFILE_HOGP_EMC_1501_
    SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
#else
    SIZE_OF_ATTRIBUTE_VALUE_7,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif
};


Uint8 att_HDL_HIDS_REPORT_09[] =
{
    //0x00, (_HOGP_HDL_OFFSET_09_+0x01),
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,
#ifdef _PROFILE_HOGP_EMC_1501_
    //SIZE_OF_ATTRIBUTE_VALUE_20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
#else
    //SIZE_OF_ATTRIBUTE_VALUE_7,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif
};


const Uint8 ATT_HDL_HIDS_REPORT_09_REPORT_REFERENCE[] =
{
    0x00, (_HOGP_HDL_OFFSET_09_+0x03-0x01),
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_REPORT_REFERENCE,
    SIZE_OF_ATTRIBUTE_VALUE_2,
#ifdef _PROFILE_HOGP_EMC_1501_
    0x0D,
#else
    0x09,
#endif
    0x03
};
#endif      //#ifndef _PROFILE_HOGP_EMC_


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_PROTOCOL_MODE[] =
{
    0x00, _HOGP_HDL_OFFSET_RPT_REF_,                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        //GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_RPT_REF_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_PROTOCOL_MODE, GATT_SPEC_CHARACTERISTIC                                //Attribute Value
};


const Uint8 ATT_HDL_HIDS_PROTOCOL_MODE_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_RPT_REF_+0x01),                                                         //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_PROTOCOL_MODE,                               //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    1,                                                                                              //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};


Uint8 att_HDL_HIDS_PROTOCOL_MODE[] =
{
    //0x00, (_HOGP_HDL_OFFSET_RPT_REF_+0x01),                                                       //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_PROTOCOL_MODE,                             //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    1,                                                                                              //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};



#ifdef _PROFILE_HOGP_BOOT_
#ifdef _PROFILE_HOGP_KEYBOARD_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT[] =
{
    0x00, _HOGP_HDL_OFFSET_BOOT_KB_,                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_BOOT_KB_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT, GATT_SPEC_CHARACTERISTIC                   //Attribute Value
};


const Uint8 ATT_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x01),                                                         //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT,                  //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_9,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                                            //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};


Uint8 att_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT[] =
{
    //0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x01),                                                       //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_9,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                                            //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};


const Uint8 ATT_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =    //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x02),                                                         //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x02),                                                       //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};


const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT[] =
{
    0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x03),                                                         //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        //GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_BOOT_KB_+0x04), 0x00,
    GATT_SPEC_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT, GATT_SPEC_CHARACTERISTIC                  //Attribute Value
};


const Uint8 ATT_HDL_HIDS_BOOT_KEYBOARD_OUTPUT_REPORT_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x04),                                                         //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT,                 //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_1,
    0x00,                                                                                           //Attribute Value,
};


Uint8 att_HDL_HIDS_BOOT_KEYBOARD_OUTPUT_REPORT[] =
{
    //0x00, (_HOGP_HDL_OFFSET_BOOT_KB_+0x04),                                                       //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_1,
    0x00,                                                                                           //Attribute Value,
};
#endif //#ifdef _PROFILE_HOGP_KEYBOARD_


#ifdef _PROFILE_HOGP_MOUSE_
const Uint8 ATT_HDL_HIDS_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT[] =
{
    0x00, _HOGP_HDL_OFFSET_BOOT_MS_,                                                                //Handle
    GATT_DECLARATIONS, GATT_DECLARATIONS_CHARACTERISTIC,                                            //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_5,
    //0x11,
    (
        //Characteristic Properties
        //GATT_DECLARATIONS_PROPERTIES_BROADCAST |                                                  //Read: Mandatory
        GATT_DECLARATIONS_PROPERTIES_READ |                                                         //Notify: Optional
        //GATT_DECLARATIONS_PROPERTIES_WRITE_WITHOUT_RESPONSE |
        GATT_DECLARATIONS_PROPERTIES_WRITE |
        GATT_DECLARATIONS_PROPERTIES_NOTIFY |
        //GATT_DECLARATIONS_PROPERTIES_INDICATE |
        //GATT_DECLARATIONS_PROPERTIES_AUTHENTICATED_SIGNED_WRITES |
        //GATT_DECLARATIONS_PROPERTIES_EXTENDED_PROPERTIES |
        0x00
    ),
    (_HOGP_HDL_OFFSET_BOOT_MS_+0x01), 0x00,
    GATT_SPEC_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT, GATT_SPEC_CHARACTERISTIC                      //Attribute Value
};


const Uint8 ATT_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_INIT[] =
{
    0x00, (_HOGP_HDL_OFFSET_BOOT_MS_+0x01),                                                         //Handle
    GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT,                     //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_6,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                             //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};


Uint8 att_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT[] =
{
    //0x00, (_HOGP_HDL_OFFSET_BOOT_MS_+0x01),                                                       //Handle
    //GATT_SPEC_CHARACTERISTIC, GATT_SPEC_CHARACTERISTIC_REPORT,                                    //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_6,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                             //Attribute Value, 0x00: Boot Protocol Mode, 0x01: Report Protocol Mode
};


const Uint8 ATT_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =       //Mandatory if the Battery Level characteristic properties supports notification
{
    0x00, (_HOGP_HDL_OFFSET_BOOT_MS_+0x02),                                                         //Handle
    GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                         //Attribute Type
    SIZE_OF_ATTRIBUTE_VALUE_2,
    0x00,                                                                                           //Attribute Value
    0x00                                                                                            //Attribute Value,
};


Uint8 att_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION[] =
{
    //0x00, (_HOGP_HDL_OFFSET_BOOT_MS_+0x02),                                                       //Handle
    //GATT_DESCRIPTORS, GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION,                       //Attribute Type
    //SIZE_OF_ATTRIBUTE_VALUE_2,
    (
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_NOTIFICATION |
        //GATT_DESCRIPTORS_CLIENT_CHARACTERISTIC_CONFIGURATION_INDICATION |
        0x00
    ),                                                                                              //Attribute Value, R/W: Mandatory
    0x00                                                                                            //Attribute Value,
};
#endif      //#ifdef _PROFILE_HOGP_MOUSE_
#endif      //#ifdef _PROFILE_HOGP_BOOT_
#endif


const Uint8 ATT_PERMISSION_NULL[] =                     //Bluetooth Spec, Ver4.0 [Vol 3] page 535 of 656
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_PRIMARY_SERVICE[] =                     //Bluetooth Spec, Ver4.0 [Vol 3] page 535 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_SECONDARY_SERVICE[] =                   //Bluetooth Spec, Ver4.0 [Vol 3] page 535 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_INCLUDE[] =                             //Bluetooth Spec, Ver4.0 [Vol 3] page 536 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_CHARACTERISTIC[] =                      //Bluetooth Spec, Ver4.0 [Vol 3] page 537 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_CHARACTERISTIC_AGGREGATE_FORMAT[] =     //Bluetooth Spec, Ver4.0 [Vol 3] page 547 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_CHARACTERISTIC_EXTENDED_PROPERTIES[] =  //Bluetooth Spec, Ver4.0 [Vol 3] page 540 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT[] =  //Bluetooth Spec, Ver4.0 [Vol 3] page 543 of 656
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GAP_DEVICE_NAME_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GAP_APPEARANCE[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GAP_RECONNECTION_ADDRESS_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GAP_PERIPHERAL_PRIVACY_FLAG[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GATT_SERVICE_CHANGED_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_SERIAL_NUMBER_STRING[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        //ATT_TYPE_FORMAT_ATT_CHR_ACSS_USER |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_MANUFACTURER_NAME_STRING[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_SYSTEM_ID[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_FIRMWARE_REVISION_STRING[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_MODEL_NUMBER_STRING[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_HARDWARE_REVISION_STRING[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_SOFTWARE_REVISION_STRING[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_DIS_PNP_ID[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};

#ifdef _PROFILE_BAS_
const Uint8 ATT_PERMISSION_HDL_BAS_BATTERY_LEVEL_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_BAS_BATTERY_POWER_STATE[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};
#endif


#ifdef _PROFILE_HOGP_
const Uint8 ATT_PERMISSION_HDL_HIDS_PROTOCOL_MODE_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT_REPORT_REFERENCE[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT_MAP[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_CLIENT_CHRCT_CONFIG_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_CLIENT_CHRCT_CONFIG_INIT[] =
{
    (
        ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_BOOT_KEYBOARD_OUTPUT_REPORT_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_HID_INFORMATION[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_HID_CONTROL_POINT_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        //ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT1_INIT[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT1_REPORT_REFERENCE[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};


const Uint8 ATT_PERMISSION_HDL_HIDS_REPORT1_USER_DESCRIPTION[] =
{
    (
        //ATT_PERMISSION_READ |
        //ATT_PERMISSION_WRITE |
        //ATT_PERMISSION_ENC_READ |
        //ATT_PERMISSION_ENC_WRITE |
        ATT_PERMISSION_AUTHE_READ |
        //ATT_PERMISSION_AUTHE_WRITE |
        //ATT_PERMISSION_AUTHO_READ |
        //ATT_PERMISSION_AUTHO_WRITE |
        0x00
    ),
    (
        ATT_TYPE_FORMAT_16UUID |
        //ATT_TYPE_FORMAT_128UUID |
        0x00
    ),
};
#endif


/*!
    \brief  Table combines the content of handles corresponding to each GATT declarations and characteristics.
*/
const Uint8 *ATTRIBUTE_SERVER_PARAM[SIZE_ATTRIBUTE_SERVER] =
{
    &ATT_HDL_INVALID[5],
    &ATT_HDL_GAP_PRIMARY_SERVICE[5],
    &ATT_HDL_GAP_CHARACTERISTIC_DEVICE_NAME[5],
    //&ATT_HDL_GAP_DEVICE_NAME_INIT[5],
    att_HDL_GAP_DEVICE_NAME,
    &ATT_HDL_GAP_CHARACTERISTIC_APPEARANCE[5],
    &ATT_HDL_GAP_APPEARANCE[5],
    &ATT_HDL_GAP_CHARACTERISTIC_RECONNECTION_ADDRESS[5],
    att_HDL_GAP_RECONNECTION_ADDRESS,
    &ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG[5],
    &ATT_HDL_GAP_PERIPHERAL_PRIVACY_FLAG[5],
    &ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS[5],
    &ATT_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS[5],
    &ATT_HDL_GATT_PRIMARY_SERVICE[5],
    &ATT_HDL_GATT_CHARACTERISTIC_SERVICE_CHANGED[5],
    att_HDL_GATT_SERVICE_CHANGED,
    att_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION,
    &ATT_HDL_DIS_PRIMARY_SERVICE[5],
    &ATT_HDL_DIS_CHARACTERISTIC_SERIAL_NUMBER_STRING[5],
    &ATT_HDL_DIS_SERIAL_NUMBER_STRING[5],
    &ATT_HDL_DIS_SERIAL_NUMBER_STRING_PRESENTATION_FORMAT[5],
    &ATT_HDL_DIS_CHARACTERISTIC_MANUFACTURER_NAME_STRING[5],
    &ATT_HDL_DIS_MANUFACTURER_NAME_STRING[5],
    &ATT_HDL_DIS_MANUFACTURER_NAME_STRING_PRESENTATION_FORMAT[5],
    &ATT_HDL_DIS_CHARACTERISTIC_SYSTEM_ID[5],
    &ATT_HDL_DIS_SYSTEM_ID[5],
    &ATT_HDL_DIS_CHARACTERISTIC_FIRMWARE_REVISION_STRING[5],
    &ATT_HDL_DIS_FIRMWARE_REVISION_STRING[5],
    &ATT_HDL_DIS_FIRMWARE_REVISION_STRING_PRESENTATION_FORMAT[5],
    &ATT_HDL_DIS_CHARACTERISTIC_MODEL_NUMBER_STRING[5],
    &ATT_HDL_DIS_MODEL_NUMBER_STRING[5],
    &ATT_HDL_DIS_MODEL_NUMBER_STRING_PRESENTATION_FORMAT[5],
    &ATT_HDL_DIS_CHARACTERISTIC_HARDWARE_REVISION_STRING[5],
    &ATT_HDL_DIS_HARDWARE_REVISION_STRING[5],
    &ATT_HDL_DIS_HARDWARE_REVISION_STRING_PRESENTATION_FORMAT[5],
    &ATT_HDL_DIS_CHARACTERISTIC_SOFTWARE_REVISION_STRING[5],
    &ATT_HDL_DIS_SOFTWARE_REVISION_STRING[5],
    &ATT_HDL_DIS_SOFTWARE_REVISION_STRING_PRESENTATION_FORMAT[5],
    &ATT_HDL_DIS_CHARACTERISTIC_PNP_ID[5],
    &ATT_HDL_DIS_PNP_ID[5],
#ifdef _PROFILE_HRP_
    &ATT_HDL_HRS_PRIMARY_SERVICE[5],
    &ATT_HDL_HRS_CHARACTERISTIC_HEART_RATE_MEASUREMENT[5],
    att_HDL_HRS_HEART_RATE_MEASUREMENT,
    att_HDL_HRS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    &ATT_HDL_HRS_CHARACTERISTIC_BODY_SENSOR_LOCATION[5],
    att_HDL_HRS_BODY_SENSOR_LOCATION,
#endif
#ifdef _PROFILE_BAS_
    &ATT_HDL_BAS_PRIMARY_SERVICE[5],
    &ATT_HDL_BAS_CHARACTERISTIC_BATTERY_LEVEL[5],
    att_HDL_BAS_BATTERY_LEVEL,
    //&ATT_HDL_BAS_BATTERY_LEVEL_PRESENTATION_FORMAT[5],
    att_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION,
    &ATT_HDL_BAS_CHARACTERISTIC_BATTERY_POWER_STATE[5],
    att_HDL_BAS_BATTERY_POWER_STATE,
#endif
#ifdef _PROFILE_HOGP_
    &ATT_HDL_HIDS_PRIMARY_SERVICE[5],
    &ATT_HDL_HIDS_CHARACTERISTIC_HID_INFORMATION[5],
    &ATT_HDL_HIDS_HID_INFORMATION[5],
    &ATT_HDL_HIDS_CHARACTERISTIC_HID_CONTROL_POINT[5],
    att_HDL_HIDS_HID_CONTROL_POINT,
    &ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MAP[5],
    &ATT_HDL_HIDS_REPORT_MAP[5],
#ifdef _PROFILE_HOGP_KEYBOARD_
    &ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBI[5],
    att_HDL_HIDS_REPORT_KBI,
    att_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION,
    &ATT_HDL_HIDS_REPORT_KBI_REPORT_REFERENCE[5],
    &ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBO[5],
    att_HDL_HIDS_REPORT_KBO,
    &ATT_HDL_HIDS_REPORT_KBO_REPORT_REFERENCE[5],
#endif

    &ATT_HDL_HIDS_CHARACTERISTIC_PROTOCOL_MODE[5],
    att_HDL_HIDS_PROTOCOL_MODE,
#endif
};



/*!
    \brief  Table combines the description of handles corresponding to each GATT declarations and characteristics.
*/
//code Uint8 code *ATTRIBUTE_SERVER_PARAM[] =
const Uint8 *ATTRIBUTE_SERVER[SIZE_ATTRIBUTE_SERVER] =
{
    ATT_HDL_INVALID,
    ATT_HDL_GAP_PRIMARY_SERVICE,
    ATT_HDL_GAP_CHARACTERISTIC_DEVICE_NAME,
    ATT_HDL_GAP_DEVICE_NAME_INIT,
    ATT_HDL_GAP_CHARACTERISTIC_APPEARANCE,
    ATT_HDL_GAP_APPEARANCE,
    ATT_HDL_GAP_CHARACTERISTIC_RECONNECTION_ADDRESS,
    ATT_HDL_GAP_RECONNECTION_ADDRESS_INIT,
    ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG,
    ATT_HDL_GAP_PERIPHERAL_PRIVACY_FLAG,
    ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_HDL_GATT_PRIMARY_SERVICE,
    ATT_HDL_GATT_CHARACTERISTIC_SERVICE_CHANGED,
    ATT_HDL_GATT_SERVICE_CHANGED_INIT,
    ATT_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_HDL_DIS_PRIMARY_SERVICE,
    ATT_HDL_DIS_CHARACTERISTIC_SERIAL_NUMBER_STRING,
    ATT_HDL_DIS_SERIAL_NUMBER_STRING,
    ATT_HDL_DIS_SERIAL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_HDL_DIS_CHARACTERISTIC_MANUFACTURER_NAME_STRING,
    ATT_HDL_DIS_MANUFACTURER_NAME_STRING,
    ATT_HDL_DIS_MANUFACTURER_NAME_STRING_PRESENTATION_FORMAT,
    ATT_HDL_DIS_CHARACTERISTIC_SYSTEM_ID,
    ATT_HDL_DIS_SYSTEM_ID,
    ATT_HDL_DIS_CHARACTERISTIC_FIRMWARE_REVISION_STRING,
    ATT_HDL_DIS_FIRMWARE_REVISION_STRING,
    ATT_HDL_DIS_FIRMWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_DIS_CHARACTERISTIC_MODEL_NUMBER_STRING,
    ATT_HDL_DIS_MODEL_NUMBER_STRING,
    ATT_HDL_DIS_MODEL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_HDL_DIS_CHARACTERISTIC_HARDWARE_REVISION_STRING,
    ATT_HDL_DIS_HARDWARE_REVISION_STRING,
    ATT_HDL_DIS_HARDWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_DIS_CHARACTERISTIC_SOFTWARE_REVISION_STRING,
    ATT_HDL_DIS_SOFTWARE_REVISION_STRING,
    ATT_HDL_DIS_SOFTWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_DIS_CHARACTERISTIC_PNP_ID,
    ATT_HDL_DIS_PNP_ID,
#ifdef _PROFILE_BAS_
    ATT_HDL_BAS_PRIMARY_SERVICE,
    ATT_HDL_BAS_CHARACTERISTIC_BATTERY_LEVEL,
    ATT_HDL_BAS_BATTERY_LEVEL_INIT,
    //ATT_HDL_BAS_BATTERY_LEVEL_PRESENTATION_FORMAT,
    ATT_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_HDL_BAS_CHARACTERISTIC_BATTERY_POWER_STATE,
    ATT_HDL_BAS_BATTERY_POWER_STATE_INIT,
#endif
#ifdef _PROFILE_HOGP_
    ATT_HDL_HIDS_PRIMARY_SERVICE,
    ATT_HDL_HIDS_CHARACTERISTIC_HID_INFORMATION,
    ATT_HDL_HIDS_HID_INFORMATION,
    ATT_HDL_HIDS_CHARACTERISTIC_HID_CONTROL_POINT,
    ATT_HDL_HIDS_HID_CONTROL_POINT_INIT,
    ATT_HDL_HIDS_CHARACTERISTIC_REPORT_MAP,
    ATT_HDL_HIDS_REPORT_MAP,
#ifdef _PROFILE_HOGP_KEYBOARD_
    ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBI,
    ATT_HDL_HIDS_REPORT_KBI_INIT,
    ATT_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_HDL_HIDS_REPORT_KBI_REPORT_REFERENCE,
    ATT_HDL_HIDS_CHARACTERISTIC_REPORT_KBO,
    ATT_HDL_HIDS_REPORT_KBO_INIT,
    ATT_HDL_HIDS_REPORT_KBO_REPORT_REFERENCE,
#endif
		ATT_HDL_HIDS_CHARACTERISTIC_PROTOCOL_MODE,
    ATT_HDL_HIDS_PROTOCOL_MODE_INIT,
#endif
};




/*!
    \brief  Table combines the permission setting corresponding to each GATT declarations and characteristics.
*/
const Uint8 *ATTRIBUTE_SERVER_PERMISSION[SIZE_ATTRIBUTE_SERVER] =
{
    ATT_PERMISSION_NULL,                                                //ATT_HDL_INVALID,
    ATT_PERMISSION_PRIMARY_SERVICE,                                     //ATT_HDL_GAP_PRIMARY_SERVICE,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_GAP_CHARACTERISTIC_DEVICE_NAME,
    ATT_PERMISSION_HDL_GAP_DEVICE_NAME_INIT,                            //ATT_HDL_GAP_DEVICE_NAME,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_GAP_CHARACTERISTIC_APPEARANCE,
    ATT_PERMISSION_HDL_GAP_APPEARANCE,                                  //ATT_HDL_GAP_APPEARANCE,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_GAP_CHARACTERISTIC_RECONNECTION_ADDRESS,
    ATT_PERMISSION_HDL_GAP_RECONNECTION_ADDRESS_INIT,                   //ATT_HDL_GAP_RECONNECTION_ADDRESS_INIT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG,
    ATT_PERMISSION_HDL_GAP_PERIPHERAL_PRIVACY_FLAG,                     //ATT_HDL_GAP_PERIPHERAL_PRIVACY_FLAG,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_PERMISSION_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,  //ATT_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_PERMISSION_PRIMARY_SERVICE,                                     //ATT_HDL_GATT_PRIMARY_SERVICE,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_GATT_CHARACTERISTIC_SERVICE_CHANGED,
    ATT_PERMISSION_HDL_GATT_SERVICE_CHANGED_INIT,                       //ATT_HDL_GATT_SERVICE_CHANGED_INIT,
    ATT_PERMISSION_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,   //ATT_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT
    ATT_PERMISSION_PRIMARY_SERVICE,                                     //ATT_HDL_DIS_PRIMARY_SERVICE,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_SERIAL_NUMBER_STRING,
    ATT_PERMISSION_HDL_DIS_SERIAL_NUMBER_STRING,                        //ATT_HDL_DIS_SERIAL_NUMBER_STRING,
    ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_DIS_SERIAL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_MANUFACTURER_NAME_STRING,
    ATT_PERMISSION_HDL_DIS_MANUFACTURER_NAME_STRING,                    //ATT_HDL_DIS_MANUFACTURER_NAME_STRING,
    ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_DIS_MANUFACTURER_NAME_STRING_PRESENTATION_FORMAT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_SYSTEM_ID,
    ATT_PERMISSION_HDL_DIS_SYSTEM_ID,                                   //ATT_HDL_DIS_SYSTEM_ID,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_FIRMWARE_REVISION_STRING,
    ATT_PERMISSION_HDL_DIS_FIRMWARE_REVISION_STRING,                    //ATT_HDL_DIS_FIRMWARE_REVISION_STRING,
    ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_DIS_FIRMWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_MODEL_NUMBER_STRING,
    ATT_PERMISSION_HDL_DIS_MODEL_NUMBER_STRING,                         //ATT_HDL_DIS_MODEL_NUMBER_STRING,
    ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_DIS_MODEL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_HARDWARE_REVISION_STRING,
    ATT_PERMISSION_HDL_DIS_HARDWARE_REVISION_STRING,                    //ATT_HDL_DIS_HARDWARE_REVISION_STRING,
    ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_DIS_HARDWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_SOFTWARE_REVISION_STRING,
    ATT_PERMISSION_HDL_DIS_SOFTWARE_REVISION_STRING,                    //ATT_HDL_DIS_SOFTWARE_REVISION_STRING,
    ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_DIS_SOFTWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_DIS_CHARACTERISTIC_PNP_ID,
    ATT_PERMISSION_HDL_DIS_PNP_ID,                                      //ATT_HDL_DIS_PNP_ID,
#ifdef _PROFILE_BAS_
    ATT_PERMISSION_PRIMARY_SERVICE,                                     //ATT_HDL_BAS_PRIMARY_SERVICE,
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_BAS_CHARACTERISTIC_BATTERY_LEVEL,
    ATT_PERMISSION_HDL_BAS_BATTERY_LEVEL_INIT,                          //ATT_HDL_BAS_BATTERY_LEVEL_INIT,
    //ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_BAS_BATTERY_LEVEL_PRESENTATION_FORMAT,
    ATT_PERMISSION_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,    //ATT_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT
    ATT_PERMISSION_CHARACTERISTIC,                                      //ATT_HDL_BAS_CHARACTERISTIC_BATTERY_POWER_STATE,
    ATT_PERMISSION_HDL_BAS_BATTERY_POWER_STATE,                         //ATT_HDL_BAS_BATTERY_POWER_STATE_INIT
#endif
#ifdef _PROFILE_HOGP_
    ATT_PERMISSION_PRIMARY_SERVICE,
    ATT_PERMISSION_CHARACTERISTIC,
    ATT_PERMISSION_HDL_HIDS_HID_INFORMATION,
    ATT_PERMISSION_CHARACTERISTIC,
    ATT_PERMISSION_HDL_HIDS_HID_CONTROL_POINT_INIT,
    ATT_PERMISSION_CHARACTERISTIC,
    ATT_PERMISSION_HDL_HIDS_REPORT_MAP,
#ifdef _PROFILE_HOGP_KEYBOARD_
    ATT_PERMISSION_CHARACTERISTIC,
    ATT_PERMISSION_HDL_HIDS_REPORT_INIT,
    ATT_PERMISSION_HDL_HIDS_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_PERMISSION_HDL_HIDS_REPORT_REPORT_REFERENCE,
    ATT_PERMISSION_CHARACTERISTIC,
    ATT_PERMISSION_HDL_HIDS_REPORT1_INIT,
    ATT_PERMISSION_HDL_HIDS_REPORT1_REPORT_REFERENCE,
#endif
   ATT_PERMISSION_CHARACTERISTIC,
    ATT_PERMISSION_HDL_HIDS_PROTOCOL_MODE_INIT,
#endif
};


/*!
    \brief  No operation while attribute write related command occurs.
    \param  length length of conents writing to the GATT characteristic.
    \param  srcCMD address of conents writing to the GATT characteristic.
*/
void ATT_HDL_Wr_NULL(uint8_t connID, uint8_t length, uint8_t *srcCMD)
{
}


/*!
    \brief  Attribute write related command will call the function
            to corresponding GATT characteristic.
    \param  length length of conents writing to the GATT characteristic.
    \param  srcCMD address of conents writing to the GATT characteristic.
*/
void (* const ATT_Write[])(uint8_t connID, uint8_t length, uint8_t *srcCMD) =
{
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_INVALID,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_PRIMARY_SERVICE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_DEVICE_NAME,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_DEVICE_NAME,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_APPEARANCE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_APPEARANCE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_RECONNECTION_ADDRESS,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_RECONNECTION_ADDRESS_INIT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_PERIPHERAL_PRIVACY_FLAG,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GATT_PRIMARY_SERVICE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GATT_CHARACTERISTIC_SERVICE_CHANGED,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GATT_SERVICE_CHANGED_INIT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_PRIMARY_SERVICE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_SERIAL_NUMBER_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_SERIAL_NUMBER_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_SERIAL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_MANUFACTURER_NAME_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_MANUFACTURER_NAME_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_MANUFACTURER_NAME_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_SYSTEM_ID,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_SYSTEM_ID,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_FIRMWARE_REVISION_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_FIRMWARE_REVISION_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_FIRMWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_MODEL_NUMBER_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_MODEL_NUMBER_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_MODEL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_HARDWARE_REVISION_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_HARDWARE_REVISION_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_HARDWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_SOFTWARE_REVISION_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_SOFTWARE_REVISION_STRING,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_SOFTWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_PNP_ID,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_DIS_PNP_ID,
#ifdef _PROFILE_BAS_
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_BAS_PRIMARY_SERVICE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_BAS_CHARACTERISTIC_BATTERY_LEVEL,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_BAS_BATTERY_LEVEL_INIT,
    //ATT_PERMISSION_CHARACTERISTIC_PRESENTATION_FORMAT,                  //ATT_HDL_BAS_BATTERY_LEVEL_PRESENTATION_FORMAT,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_BAS_CHARACTERISTIC_BATTERY_POWER_STATE,
    ATT_HDL_Wr_NULL,                                                    //ATT_HDL_BAS_BATTERY_POWER_STATE_INIT
#endif
#ifdef _PROFILE_HOGP_
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
#ifdef _PROFILE_HOGP_KEYBOARD_
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
#endif
   ATT_HDL_Wr_NULL,
    ATT_HDL_Wr_NULL,
#endif
};


void ATT_HDL_Rd_NULL(uint8_t connID, uint8_t *srcCMD)
{
}
/*!
    \brief  Attribute read related command will call the function
            corresponding to GATT characteristic.
    \param  length length of conents reading from the GATT characteristic.
    \param  srcCMD address of conents reading from the GATT characteristic.
*/
void (* const ATT_Read[])(uint8_t connID, uint8_t *srcCMD) =
{
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_INVALID,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_PRIMARY_SERVICE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_DEVICE_NAME,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_DEVICE_NAME,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_APPEARANCE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_APPEARANCE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_RECONNECTION_ADDRESS,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_RECONNECTION_ADDRESS_INIT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_PERIPHERAL_PRIVACY_FLAG,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GATT_PRIMARY_SERVICE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GATT_CHARACTERISTIC_SERVICE_CHANGED,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GATT_SERVICE_CHANGED_INIT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_PRIMARY_SERVICE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_SERIAL_NUMBER_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_SERIAL_NUMBER_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_SERIAL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_MANUFACTURER_NAME_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_MANUFACTURER_NAME_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_MANUFACTURER_NAME_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_SYSTEM_ID,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_SYSTEM_ID,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_FIRMWARE_REVISION_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_FIRMWARE_REVISION_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_FIRMWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_MODEL_NUMBER_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_MODEL_NUMBER_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_MODEL_NUMBER_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_HARDWARE_REVISION_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_HARDWARE_REVISION_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_HARDWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_SOFTWARE_REVISION_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_SOFTWARE_REVISION_STRING,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_SOFTWARE_REVISION_STRING_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_CHARACTERISTIC_PNP_ID,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_DIS_PNP_ID,
#ifdef _PROFILE_BAS_
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_BAS_PRIMARY_SERVICE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_BAS_CHARACTERISTIC_BATTERY_LEVEL,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_BAS_BATTERY_LEVEL_INIT,
    //                                                                  //ATT_HDL_BAS_BATTERY_LEVEL_PRESENTATION_FORMAT,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_BAS_CHARACTERISTIC_BATTERY_POWER_STATE,
    ATT_HDL_Rd_NULL,                                                    //ATT_HDL_BAS_BATTERY_POWER_STATE_INIT
#endif
#ifdef _PROFILE_HOGP_
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
#ifdef _PROFILE_HOGP_KEYBOARD_
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
#endif
    ATT_HDL_Rd_NULL,
    ATT_HDL_Rd_NULL,
#endif
};

Uint8 size_ATTRIBUTE_SERVER = (sizeof(ATTRIBUTE_SERVER)/sizeof(ATTRIBUTE_SERVER[0]));

#ifdef _SMP_ON_
#ifdef _BOND_ON_
const Uint8 *ATTRIBUTE_SERVER_BOND[SIZE_ATTRIBUTE_SERVER_BOND] =
{
    ATT_HDL_GAP_DEVICE_NAME_INIT,
#ifdef _PROFILE_BAS_
    ATT_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
#endif

#ifdef _PROFILE_HOGP_
#ifdef _PROFILE_HOGP_COMSUMER_
    ATT_HDL_HIDS_REPORT_CSI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
#endif
#ifdef _PROFILE_HOGP_MOUSE_
    ATT_HDL_HIDS_REPORT_MSI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_HDL_HIDS_REPORT_MSF_INIT,
#endif
#ifdef _PROFILE_HOGP_KEYBOARD_
    ATT_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
#endif
#ifdef _PROFILE_HOGP_BOOT_
#ifdef _PROFILE_HOGP_KEYBOARD_
    ATT_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
#endif
#ifdef _PROFILE_HOGP_MOUSE_
    ATT_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
#endif
#endif
#endif  //#ifdef _PROFILE_HOGP_

#ifdef _PROFILE_GLS_
    ATT_HDL_GLS_GLUCOSE_MEASUREMENT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_HDL_GLS_GLUCOSE_MEASUREMENT_CONTEXT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
    ATT_HDL_GLS_RECORD_ACCESS_CONTROL_POINT_CLIENT_CHARACTERISTIC_CONFIGURATION_INIT,
#endif
};
const Uint8 *ATTRIBUTE_SERVER_BOND_PARAM[SIZE_ATTRIBUTE_SERVER_BOND] =
{
    att_HDL_GAP_DEVICE_NAME,
#ifdef _PROFILE_BAS_
    att_HDL_BAS_CLIENT_CHARACTERISTIC_CONFIGURATION,
#endif
#ifdef _PROFILE_HOGP_
#ifdef _PROFILE_HOGP_COMSUMER_
    att_HDL_HIDS_REPORT_CSI_CLIENT_CHARACTERISTIC_CONFIGURATION,
#endif
#ifdef _PROFILE_HOGP_MOUSE_
    att_HDL_HIDS_REPORT_MSI_CLIENT_CHARACTERISTIC_CONFIGURATION,
    att_HDL_HIDS_REPORT_MSF,
#endif
#ifdef _PROFILE_HOGP_KEYBOARD_
    att_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION,
#endif
#ifdef _PROFILE_HOGP_BOOT_
#ifdef _PROFILE_HOGP_KEYBOARD_
    att_HDL_HIDS_BOOT_KEYBOARD_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION,
#endif
#ifdef _PROFILE_HOGP_MOUSE_
    att_HDL_HIDS_BOOT_MOUSE_INPUT_REPORT_CLIENT_CHARACTERISTIC_CONFIGURATION,
#endif
#endif
#endif  //#ifdef _PROFILE_HOGP
#ifdef _PROFILE_GLS_
    att_HDL_GLS_GLUCOSE_MEASUREMENT_CLIENT_CHARACTERISTIC_CONFIGURATION,
    att_HDL_GLS_GLUCOSE_MEASUREMENT_CONTEXT_CLIENT_CHARACTERISTIC_CONFIGURATION,
    att_HDL_GLS_RECORD_ACCESS_CONTROL_POINT_CLIENT_CHARACTERISTIC_CONFIGURATION,
#endif
};
Uint8 size_ATTRIBUTE_SERVER_BOND = (sizeof(ATTRIBUTE_SERVER_BOND)/sizeof(ATTRIBUTE_SERVER_BOND[0]));
#endif
#endif

#endif
