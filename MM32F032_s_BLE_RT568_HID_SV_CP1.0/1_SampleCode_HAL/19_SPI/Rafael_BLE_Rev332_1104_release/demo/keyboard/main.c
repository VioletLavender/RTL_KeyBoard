/**************************************************************************//**
 * @file     main.c
 * @version  V0.9
 * $Revision: 01 $
 * @brief
 *           Demonstrate BLE operation.
 *           Includes the basic initialization and the loop for kernel(BLE) operations.
 * @note
 *
 ******************************************************************************/
#define __MAIN_C__


#include <stdio.h>
#include "main.h"
#include "rf_phy.h"
#include "porting_spi.h"
#include "porting_misc.h"
#include "porting_LLtimer.h"
#include "systick.h"
#include "uart.h"
#include "spi.h"
#include "mcu_definition.h"

#define HOGP_PAIRING_KEY  654321                 //pairing key. uint32
uint32_t g_pairinKey = HOGP_PAIRING_KEY;
void RF_Open()
{
    void SPI_DMA_25xxTest(void) ;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Wait RF PHY stable ,delay 25ms */
    SysTick_DelayMs(25);


    /* RF_RESET_CLOCK  enable */
    RCC_AHBPeriphClockCmd(RF_RESET_CLOCK, ENABLE);
    /* Configure RF_RESET_PIN in output pushpull mode */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin   = RF_RESET_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(RF_RESET_PORT, &GPIO_InitStructure);

    /* Reset RF by using RF_RESET_PIN */
    GPIO_SetBits(RF_RESET_PORT, RF_RESET_PIN);
    SysTick_DelayMs(1);
    GPIO_ResetBits(RF_RESET_PORT, RF_RESET_PIN);
    SysTick_DelayMs(1);
    GPIO_SetBits(RF_RESET_PORT, RF_RESET_PIN);


    SysTick_DelayMs(50);

    /* SPI IO remapping */
    RF_SpiIoMapping();

    /* Initialize RF PHY */
    RF_Init();                   //EnableGpioInterrupt in the end of this function

}

extern Uint8 att_HDL_BAS_BATTERY_LEVEL[];

/*!
   \brief main loop for initialization and BLE kernel
*/
int main(void)
{
    BLE_Addr_Param bleAddrParam;

    extern BleStackStatus Ble_Kernel_Root(void);
    extern void BleApp_Main(void);
    extern void BleApp_Init(void);
    SysTick_Init(1000);

    NVIC_SetPriority(EXTI4_15_IRQn, 0);  //set GPIO_INT highest priority

    /* Config UART1 with parameter(115200, N, 8, 1) for printf */
    UARTx_Configure(DEBUG_UART, 115200, UART_WordLength_8b, UART_StopBits_1,  \
                    UART_Parity_No);


    /* Enable the BLE RF PHY */
    RF_Open();

    printf("-------------------\n");
    printf("  BLE Start.....\n");
    printf("-------------------\n");

    printf("Chip_ID=0x%x\n", ChipId_Get());


    /* Set BD ADDR */
    bleAddrParam.addrType = PUBLIC_ADDR;
    bleAddrParam.addr[0] = 0x11;
    bleAddrParam.addr[1] = 0x22;
    bleAddrParam.addr[2] = 0x33;
    bleAddrParam.addr[3] = 0x54;
    bleAddrParam.addr[4] = 0x55;
    bleAddrParam.addr[5] = 0x56;
    setBLE_BleDeviceAddr(&bleAddrParam);

    BleApp_Init();

    while (1)
    {
        /* Run BLE kernel, the task priority is LL > Host */
        if (Ble_Kernel_Root() == BLESTACK_STATUS_FREE)
        {
            BleApp_Main();


        }
    }
}



