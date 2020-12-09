/**************************************************************************//**
 * @file     user.c
 * @version  V0.9
 * $Revision: 01 $
 * @brief
 *           Demonstrate how to use LIB pre-build function to implement BLE
 *           HOGP application.
 *           This demo includes keyboard, mouse, volume control
 * @note
 *
 ******************************************************************************/
#include <stdio.h>
#include "BleAppSetting.h"
#include "host.h"
#include "rf_phy.h"
#include "porting_misc.h"
#include "ble_cmd.h"
#include "ble_event.h"

#ifdef _DEBUG_MSG_USER_
#include <stdio.h>
#endif  //(#ifdef _DEBUG_MSG_USER_)

uint8_t connId = 0;   //Current connection Id
Uint8 ble_state = STATE_BLE_STANDBY;
extern uint32_t g_pairinKey;

/* Function prototype declaration */
static void BleEvent_Callback(BleCmdEvent event, void* param);

#if (BLE_DEMO==DEMO_HOGP)
Uint8 HID_report_MS_key_temp;         //mouse control value. It is a counter
#ifdef _PROFILE_HOGP_
#ifdef _PROFILE_HOGP_COMSUMER_
Uint8 STATE_HID_reportCS;             //consumer state
Uint8 HID_report_CS_key_temp;         //consumer control value. Here use to control volume
const Uint8 HID_RPT_CS_KEY_DEMO[][2] =
{
    {0xE9, 0x00,},  //vol+
    {0xEA, 0x00,},  //vol-
    {0xE2, 0x00,},  //Mute
    {0xB0, 0x00,},  //Play
    {0xB1, 0x00,},  //Pause
    {0xB3, 0x00,},  //Fast forward
    {0xB4, 0x00,},  //Rewind
    {0xB5, 0x00,},  //Scan next track
    {0xB6, 0x00,},  //Scan previous track
    {0xB7, 0x00,},  //Stop
    {0xB8, 0x00,},  //Eject
    {0x8A, 0x01,},  //Email reader
    {0x96, 0x01,},  //Internet browser
    {0x9E, 0x01,},  //Terminal lock/screensaver
    {0xC6, 0x01,},  //Research/search browser
    {0x2D, 0x02,},  //Zoom in
};
#endif  //(#ifdef _PROFILE_HOGP_COMSUMER_)
#ifdef _PROFILE_HOGP_KEYBOARD_
Uint8 STATE_HID_reportKB;             //keyboard state
Uint8 HID_report_KB_key_temp;         //keyboard control value
#endif  //(#ifdef _PROFILE_HOGP_KEYBOARD_)
//#ifdef _PROFILE_HOGP_MOUSE_
//Uint8 STATE_HID_reportMS;             //mouse state
//#endif  //(#ifdef _PROFILE_HOGP_MOUSE_)

#define STATE_HID_REPORT_CS_INITIAL             0
#define STATE_HID_REPORT_CS_DATA_UPD            0x01

#define STATE_HID_REPORT_KB_INITIAL             0
#define STATE_HID_REPORT_KB_DATA_UPD            0x01

#endif  //(#ifdef _PROFILE_HOGP_)
#endif  //#if (BLE_DEMO==DEMO_HOGP)


#if (BLE_DEMO==DEMO_TRSPX_UART_SLAVE)
extern void UART_TX_Send(uint32_t len, uint8_t *ptr);                         //show data on UART
#endif
#ifdef _DEBUG_MSG_USER_
uint8_t gateTimeline = 0;
#endif  //(#ifdef _DEBUG_MSG_USER_)


#pragma push
//#pragma Otime
#pragma Ospace

//Advertising parameters


//Target BD_ADDR (eg: 1CBA8C20C501, SensorTag)
#define TARGET_ADDR0  0x01
#define TARGET_ADDR1  0xC5
#define TARGET_ADDR2  0x20
#define TARGET_ADDR3  0x8C
#define TARGET_ADDR4  0xBA
#define TARGET_ADDR5  0x1C

//Directed Target BD_ADDR (TBD)
#define DIR_TARGET_ADDR0  0x66
#define DIR_TARGET_ADDR1  0x55
#define DIR_TARGET_ADDR2  0x44
#define DIR_TARGET_ADDR3  0x33
#define DIR_TARGET_ADDR4  0x22
#define DIR_TARGET_ADDR5  0x11

//Scan Parameters
#define SCAN_WINDOW                10U    //10*0.625ms=6.25ms
#define SCAN_INTERVAL              10U    //10*0.625ms=6.25ms

//Initial Connection Parameters
#define CONN_SUPERVISION_TIMEOUT   60U    //60*10ms=600ms
#define CONN_SLAVE_LATENCY         0U     //0~499, 0 means slave listen at every anchor point


#define SIZE_OF_CODE_BLE_ADV_DATA_USER               (\
  SIZE_OF_CODE_BLE_ADV_DATA_FLAGS+\
  SIZE_OF_CODE_BLE_ADV_DATA_AD_TYPE_SERVICE+\
  SIZE_OF_CODE_BLE_ADV_DATA_AD_TYPE_APPEARANCE+\
  0x00)

const struct BLE_Scan_Param SET_SCAN_PARA =
{
    SCAN_TYPE_PASSIVE,
    SCAN_INTERVAL,                 //Scan interval. Default is 10*0.625ms; Uint16 HCI_LE_Scan_Interval;
    SCAN_WINDOW,                   //Scan window. Default is 10*0.625ms; Uint16 HCI_LE_Scan_Window;
    ADV_FILTER_POLICY_ACCEPT_ALL,  //Filter policy. Default is accept all; Uint8 HCI_InitFilterPolicy;
};

const struct BLE_Conn_Param SET_CONN_PARA =
{
    CONN_INTERVAL_MIN,             //Minimum Connection interval. Default is 38*1.25ms; Uint16 HCI_ConnIntervalMin;
    CONN_INTERVAL_MAX,             //Maximum Connection interval. Default is 42*1.25ms; Uint16 HCI_ConnIntervalMax;
    CONN_SLAVE_LATENCY,            //Slave latency. Default is 0; Uint16 HCI_ConnLatency;
    CONN_SUPERVISION_TIMEOUT,      //Supervision Timeout, Default is 60*10ms; Uint16 HCI_SvisionTimeout;
};



const uint8_t SET_ADV_DATA[] =   //Adv data format. Set according to user select profile. See Bluetooth Spec. Ver5.0 [Vol 3], Part C, Section 11
{
    /* Length(1 byte) */
    SIZE_OF_CODE_BLE_ADV_DATA_USER,                     //Uint8 HCI_Adv_Data_Length; 1 byte
    //Uint8 HCI_Adv_Data[LEN_ADV_SCAN_DATA_MAX];

    /* Data: include AD_Type(n bytes), AD_Data(length-n bytes) */
    //GAP_AD_TYPE_LENGTH_2, GAP_AD_TYPE_FLAGS, 0x06,      //LE General Discoverable Mode, Bluetooth Spec. Ver5.0 [Vol 3], Part C, Section 11
    GAP_AD_TYPE_LENGTH_2, GAP_AD_TYPE_FLAGS, 0x05,      //LE Limit Discoverable Mode, Bluetooth Spec. Ver5.0 [Vol 3], Part C, Section 11
    //GAP_AD_TYPE_LENGTH_2, GAP_AD_TYPE_FLAGS, 0x04,      //LE Non Discoverable Mode, Bluetooth Spec. Ver5.0 [Vol 3], Part C, Section 11
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_GLUCOSE, GATT_SPEC_SERVICES,

#if defined _PROFILE_HOGP_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_HUMAN_INTERFACE_DEVICE, GATT_SPEC_SERVICES,
#if defined _PROFILE_HOGP_MULTI_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0xC0, 0x03,   //0x03C0: 960 -> Human Interface Device (HID), HID Generic
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0xC1, 0x03,   //0x03C0: 961 -> Keyboard
#elif defined _PROFILE_HOGP_MOUSE_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0xC2, 0x03,   //0x03C2: 962 -> Mouse
#elif defined _PROFILE_HOGP_KEYBOARD_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0xC0, 0x03,   //0x03C1: 961 -> Keyboard
#elif defined _PROFILE_HOGP_COMSUMER_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0xC0, 0x03,   //0x03C0: 960 -> Human Interface Device (HID), HID Generic
#endif
#elif defined _PROFILE_BLP_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_BLOOD_PRESSURE, GATT_SPEC_SERVICES,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x80, 0x03,   //0x0380: 896 -> Generic Blood Pressure
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x81, 0x03,   //0x0381: 897 -> Blood Pressure: Arm
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x82, 0x03,   //0x0382: 898 -> Blood Pressure: Wrist
#elif defined _PROFILE_HTP_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_HEALTH_THERMOMETER, GATT_SPEC_SERVICES,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x00, 0x03,   //0x0300: 768 -> Generic Thermometer
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x01, 0x03,   //0x0301: 769 -> Thermometer: Ear
#elif defined _PROFILE_RSCP_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_RUNNING_SPEED_AND_CADENCE, GATT_SPEC_SERVICES,
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x40, 0x04,   //0x0440: 1088 -> Running Walking Sensor
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x41, 0x04,   //0x0441: 1089 -> Running Walking Sensor: In-Shoe
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x42, 0x04,   //0x0442: 1090 -> Running Walking Sensor: On-Shoe
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x43, 0x04,   //0x0443: 1091 -> Running Walking Sensor: On-Hip
#elif defined _PROFILE_CSCP_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_CYCLING_SPEED_AND_CADENCE, GATT_SPEC_SERVICES,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x80, 0x04,   //0x0480: 1152 -> Generic: Cycling
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x81, 0x04,   //0x0481: 1153 -> Cycling: Cycling Computer
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x82, 0x04,   //0x0482: 1154 -> Cycling: Speed Sensor
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x83, 0x04,   //0x0483: 1155 -> Cycling: Cadence Sensor
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x84, 0x04,   //0x0484: 1156 -> Cycling: Power Sensor
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x85, 0x04,   //0x0485: 1157 -> Cycling: Speed and Cadence Sensor
#elif defined _PROFILE_HRP_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_HEART_RATE, GATT_SPEC_SERVICES,
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x40, 0x03,   //0x0340: 832 -> Generic Heart rate Sensor
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x41, 0x03,   //0x0341: 833 -> Heart Rate Sensor: Heart Rate Belt
#elif defined _PROFILE_LNS_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_LOCATION_AND_NAVIGATION, GATT_SPEC_SERVICES,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x41, 0x14,   //0x1441: 5185 -> Location Display Device
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x42, 0x14,   //0x1442: 5186 -> Location and Navigation Display Device
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x43, 0x14,   //0x1443: 5187 -> Location Pod
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x44, 0x14,   //0x1444: 5188 -> Location and Navigation Pod
#elif defined _PROFILE_GLS_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_GLUCOSE, GATT_SPEC_SERVICES,
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x00, 0x04,   //0x0400: 1024 -> Generic Glucose Meter
#elif defined _PROFILE_CPS_
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_CYCLING_POWER, GATT_SPEC_SERVICES,
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x84, 0x04,   //0x0484: 1156 -> Cycling: Power Sensor
#else
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_MORE_16B_UUID, GATT_SPEC_SERVICES_DEVICE_INFORMATION, GATT_SPEC_SERVICES,
    GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_APPEARANCE, 0x00, 0x00,   //0x0000: 0 -> Reserved
#endif

    //GAP_AD_TYPE_LENGTH_15, GAP_AD_TYPE_LOCAL_NAME_COMPLETE,
    //0x57, 0x61, 0x68, 0x6f,
    //0x6f, 0x20, 0x48, 0x52,
    //0x4d, 0x20, 0x56, 0x31,
    //0x2e, 0x37,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,
    //0xC0, 0x00,    //https://www.bluetooth.com/specifications/assigned-numbers/company-identifiers/
    //GAP_AD_TYPE_LENGTH_2, GAP_AD_TYPE_TX_POWER_LEVEL, 0x88,
    //GAP_AD_TYPE_LENGTH_5, GAP_AD_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE,
    //0x64, 0x00, 0xC8, 0x00,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_SOLICITATION_16B_UUID,
    //0x09, 0x53,
    //GAP_AD_TYPE_LENGTH_3, GAP_AD_TYPE_SERVICE_DATA, 0x00, 0x05,
};


const uint8_t SET_SCAN_RSP[] =          //Scan response data format. See Bluetooth Spec. Ver5.0 [Vol 3], Part C, Section 11
{
    9,                                  //Length: 1byte; Uint8 HCI_Scan_Rsp_Length;
    8,                                  //AD length, Uint8 HCI_Scan_Rsp[LEN_ADV_SCAN_DATA_MAX];
    GAP_AD_TYPE_LOCAL_NAME_COMPLETE,    //AD Data: 1st byte

    'R', 'F', '_',                      //AD Data: other bytes
    'H', 'O', 'G', 'P',                 //"RF_HOGP" => 7 characters, it's name shown on scan list
};



void BleApp_Init(void)
{
    BLE_IO_Caps ioCaps;

    /* register command event callback function */
    setBLE_RegisterBleEvent(BleEvent_Callback);

    /* set BLE IO Capabilities */
    ioCaps.IO_Param = DISPLAY_ONLY;
    setBLE_IOCapabilities(&ioCaps);
}


void Ble_Slave_AdvInit(void)
{
    BLE_Adv_Param advParam;

    advParam.Adv_Type = ADV_TYPE_ADV_IND;
    advParam.Adv_Interval_Min = ADV_INTERVAL_MIN;
    advParam.Adv_Interval_Max = ADV_INTERVAL_MAX;
    advParam.Adv_Channel_Map = ADV_CHANNEL_ALL;
    advParam.Adv_Filter_Policy = ADV_FILTER_POLICY_ACCEPT_ALL;

    setBLE_AdvParam(advParam);
}


void Ble_Slave_StartADV(void)
{
    //setBLE_AdvParam(SET_ADV_PARA);                                            //SET_ADV_PARA can be modified by user
    Ble_Slave_AdvInit();
    setBLE_AdvData((uint8_t *)SET_ADV_DATA, sizeof(SET_ADV_DATA));            //SET_ADV_DATA can be modified by user. may depend on profile
    setBLE_ScanRspData((uint8_t *)SET_SCAN_RSP, sizeof(SET_SCAN_RSP));        //SET_SCAN_RSP can be modified by user
    setBLE_AdvEnable();
}


void Ble_Master_Init(void)
{
    BLE_Addr_Param peerAddr_Param = {PUBLIC_ADDR,{TARGET_ADDR0,TARGET_ADDR1,TARGET_ADDR2,TARGET_ADDR3,TARGET_ADDR4,TARGET_ADDR5}};
    setBLE_ConnCreate(peerAddr_Param,SET_SCAN_PARA,SET_CONN_PARA);
}

void Ble_Initial(uint8_t role)  //0: slave, 1: master, 2: both(1, 2 not support yet)
{
    if(role==BLE_LL_SLAVE_ONLY)           //Slave only
    {
        Ble_Slave_StartADV();             //This is for Slave Role. Do advertising, parameter cound be configured in user.c
    }
    else if(role==BLE_LL_MASTER_ONLY)     //Master only
    {
        Ble_Master_Init();                //This is for Master Role
    }
    else     //Slave and Master
    {
        Ble_Slave_StartADV();
        Ble_Master_Init();
    }
}

void BleApp_Main(void)
{
    uint32_t TmrGet;
    static uint32_t TmrCmp = 0;

    TmrGet = LLTimeline_Get();


    if(ble_state == STATE_BLE_STANDBY)
    {
        Ble_Slave_StartADV();
        ble_state = STATE_BLE_ADVERTISING;
        STATE_HID_reportKB = STATE_HID_REPORT_KB_INITIAL;
        HID_report_KB_key_temp = 0;
        HID_report_MS_key_temp = 0x80;
    }
    else if(ble_state == STATE_BLE_ADVERTISING)
    {
    }
    else if(ble_state == STATE_BLE_CONNECTION)
    {
        if(((TmrGet-TmrCmp)&0x0000FFFF)<0x00000190)     //<400 * 125us = 50ms
        {
            return;
        }
        else
        {
            TmrCmp = TmrGet;
        }

                if((STATE_HID_reportKB & STATE_HID_REPORT_KB_DATA_UPD) == 0)    //check keyboard report status
                {
                    if((HID_report_KB_key_temp <= 0x04) || (HID_report_KB_key_temp >= 0x27))
                    {
                        HID_report_KB_key_temp = 0x04;     //0x04 mean 'a'; 0x27 mean '9'; see USB HID spec.
                    }
                    att_HDL_HIDS_REPORT_KBI[HDL_HIDS_REPORT_TAB_KEY_DATA0] = HID_report_KB_key_temp; // repeat keyCode: 'a' 'b' ~ 'z' ~ '1' '2'  ~ '9'
                    if(ATT_HDL_Notify(connId, (uint8_t *)ATT_HDL_HIDS_REPORT_KBI_INIT, att_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION, att_HDL_HIDS_REPORT_KBI, ATT_HDL_HIDS_REPORT_KBI_INIT[4]) == BLESTACK_STATUS_SUCCESS)
                    {
                        STATE_HID_reportKB |= STATE_HID_REPORT_KB_DATA_UPD;
                        HID_report_KB_key_temp++;                                   //keyboard keycode
                    }
                }
                else    //release key
                {
                    att_HDL_HIDS_REPORT_KBI[HDL_HIDS_REPORT_TAB_KEY_DATA0] = 0x00; // release key
                    if(ATT_HDL_Notify(connId, (uint8_t *)ATT_HDL_HIDS_REPORT_KBI_INIT, att_HDL_HIDS_REPORT_KBI_CLIENT_CHARACTERISTIC_CONFIGURATION, att_HDL_HIDS_REPORT_KBI, ATT_HDL_HIDS_REPORT_KBI_INIT[4]) == BLESTACK_STATUS_SUCCESS)
                    {
                        STATE_HID_reportKB &= ~STATE_HID_REPORT_KB_DATA_UPD;
                        HID_report_MS_key_temp++;
                    }
                }
    }

} //end of BleApp_Main()
#pragma pop

//Transparent data receive callback
void trspx_receive_data_callback(uint8_t length, uint8_t *data)
{
}

/* GAP Callback Function */
static void BleEvent_Callback(BleCmdEvent event, void* param)
{
    switch(event)
    {
    case BLECMD_EVENT_ADV_COMPLETE:
        if(ble_state == STATE_BLE_ADVERTISING)
        {
            printf("Advertising...\n");
        }
        break;

    case BLECMD_EVENT_SCAN_REPORT:
    {
//        BLE_Event_Scan_Report *rpt = (BLE_Event_Scan_Report *)param;

//        printf("RSSI:%d\n",rpt->Rpt_Rssi);
    }
    break;

    case BLECMD_EVENT_CONN_COMPLETE:
    {
        BLE_Event_ConnParam *connParam = (BLE_Event_ConnParam *)param;
        connId = connParam->connId;
        ble_state = STATE_BLE_CONNECTION;

        printf("Connected to %02x:%02x:%02x:%02x:%02x:%02x\n",connParam->peerAddr.addr[5],
               connParam->peerAddr.addr[4],
               connParam->peerAddr.addr[3],
               connParam->peerAddr.addr[2],
               connParam->peerAddr.addr[1],
               connParam->peerAddr.addr[0]);
    }
    break;

    case BLECMD_EVENT_DISCONN_COMPLETE:
    {
        BLE_Event_DisconnParam *disconnParam = (BLE_Event_DisconnParam *)param;
        ble_state = STATE_BLE_STANDBY;

        printf("Disconnected, ID:%d, Reason:0x%X\n",disconnParam->connId, disconnParam->disconnectReason);
    }
    break;

    case BLECMD_EVENT_CONN_UPDATE_COMPLETE:
    {
        BLE_Event_ConnUpdateParam *updateConnParam = (BLE_Event_ConnUpdateParam *)param;
        printf("Connection updated, ID:%d, Status:%d, Interval:%d, Latency:%d, Timeout:%d\n", updateConnParam->connId,updateConnParam->status, updateConnParam->connInterval, updateConnParam->connLatency, updateConnParam->supervisionTimeout);
    }
    break;

    case BLECMD_EVENT_PHY_UPDATE_COMPLETE:
    {
        BLE_Event_Phy_Update_Param *phy = (BLE_Event_Phy_Update_Param *)param;
        printf("STATUS: %d, TX PHY: %d, RX PHY: %d\n",phy->status,phy->phyParam.tx_Phy, phy->phyParam.rx_Phy);
    }
    break;

    case BLECMD_EVENT_STK_GEN_METHOD:
    {
        BLE_Event_Stk_Gen_Method *passkey_method = (BLE_Event_Stk_Gen_Method *)param;
        if(passkey_method->Stk_Gen_Method == PASSKEY_ENTRY)
        {
            // I/O Capability is keyboard
            // Start scanning user-entered passkey.
        }
        else if(passkey_method->Stk_Gen_Method == PASSKEY_DISPLAY)
        {
            // I/O Capability is display
            // Generate a 6-digit random code and display it for pairing.
        }
    }
    break;

    case BLECMD_EVENT_PASSKEY_CONFIRM:
    {
        BLE_Event_PassKey_Confirm *event_param = (BLE_Event_PassKey_Confirm *)param;

        //enter a scanned Passkey or use a randomly generaated passkey.
        setBLE_Pairing_PassKey(event_param->connId, g_pairinKey);
    }
    break;

    case BLECMD_EVENT_AUTH_STATUS:
    {
        BLE_Event_Auth_Status *auth_result = (BLE_Event_Auth_Status *)param;
        printf("AUTH Report, ID:%d , STATUS:%d\n", auth_result->connId, auth_result->status);
    }
    break;

    default:
        break;
    }
}

