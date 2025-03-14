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

/**
 * @file    main.c
 * @brief   BLE_FreeRTOS
 * @details This example demonstrates FreeRTOS with BLE capabilities.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "mxc_device.h"
#include "wut.h"
#include "lp.h"
#include "led.h"
#include "board.h"

/* Stringification macros */
#define STRING(x) STRING_(x)
#define STRING_(x) #x

extern void bleStartup(void);

/***** Functions *****/

/* =| vAssertCalled |==============================
 *
 *  Called when an assertion is detected. Use debugger to backtrace and 
 *  continue.
 *
 * =======================================================
 */
void vAssertCalled(const char *const pcFileName, uint32_t ulLine)
{
    volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    /* Parameters are not used. */
    (void)ulLine;
    (void)pcFileName;

    __asm volatile("cpsid i");
    {
        /* You can step out of this function to debug the assertion by using
        the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
        value. */
        while (ulSetToNonZeroInDebuggerToContinue == 0) {}
    }
    __asm volatile("cpsie i");
}

/* =| vApplicationIdleHook |==============================
 *
 *  Call the user defined function from within the idle task.  This
 *  allows the application designer to add background functionality
 *  without the overhead of a separate task.
 *  NOTE: vApplicationIdleHook() MUST NOT, UNDER ANY CIRCUMSTANCES,
 *  CALL A FUNCTION THAT MIGHT BLOCK.
 *
 * =======================================================
 */
void vApplicationIdleHook(void)
{
    /* Sleep while idle */
    LED_Off(SLEEP_LED);

    MXC_LP_EnterSleepMode();

    LED_On(SLEEP_LED);
}

/* =| main |==============================================
 *
 * This program demonstrates FreeRTOS tasks, mutexes.
 *
 * =======================================================
 */
int main(void)
{
    /* Print banner (RTOS scheduler not running) */
    printf("\n-=- %s BLE FreeRTOS (%s) Demo -=-\n", STRING(TARGET), tskKERNEL_VERSION_NUMBER);
#if configUSE_TICKLESS_IDLE
    printf("Tickless idle is enabled\n");
    /* Initialize CPU Active LED */
    LED_On(SLEEP_LED);
    LED_On(DEEPSLEEP_LED);
#endif
    printf("SystemCoreClock = %d\n", SystemCoreClock);

    /* Delay to prevent bricks */
    volatile int i;
    for (i = 0; i < 0x3FFFFF; i++) {}

    GPIO_PrepForSleep();

    /* Start the BLE application */
    bleStartup();

    /* Start scheduler */
    vTaskStartScheduler();

    /* This code is only reached if the scheduler failed to start */
    printf("ERROR: FreeRTOS did not start due to above error!\n");
    while (1) {
        __NOP();
    }

    /* Quiet GCC warnings */
    return -1;
}

typedef struct __attribute__((packed)) ContextStateFrame {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t return_address;
    uint32_t xpsr;
} sContextStateFrame;

/*****************************************************************/
void HardFault_Handler(void)
{
    __asm(" TST LR, #4\n"
          " ITE EQ \n"
          " MRSEQ R0, MSP \n"
          " MRSNE R0, PSP \n"
          " B HardFault_Decoder \n");
}

/*****************************************************************/
/* Disable optimizations for this function so "frame" argument */
/* does not get optimized away */
__attribute__((optimize("O0"))) void HardFault_Decoder(sContextStateFrame *frame)
{
    /* Hang here */
    while (1) {}
}
