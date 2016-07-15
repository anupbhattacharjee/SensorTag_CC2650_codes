/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty_min.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
// #include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header files */
#include "Board.h"

/*Driver Libs*/
#include <driverlib/sys_ctrl.h>
#include <driverlib/prcm.h>
#include <driverlib/timer.h>
#include <driverlib/osc.h>
#include <inc/hw_ints.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>

int count=0;
/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config ledPinTable[] = {
    Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

void timer_init(void){

		PRCMPowerDomainOn(PRCM_DOMAIN_PERIPH);
		PRCMLoadSet();
		PRCMPeripheralSleepEnable(PRCM_PERIPH_TIMER2);
		PRCMLoadSet();
		PRCMPeripheralDeepSleepEnable(PRCM_PERIPH_TIMER2);
		PRCMLoadSet();
		PRCMPeripheralRunEnable(PRCM_PERIPH_TIMER2);
		PRCMLoadSet();

		TimerDisable(GPT2_BASE, TIMER_A);
		TimerLoadSet(GPT2_BASE, TIMER_A, 24000000);
		TimerIntClear(GPT2_BASE, TIMER_TIMA_TIMEOUT);
		TimerIntEnable(GPT2_BASE, TIMER_TIMA_TIMEOUT);
		TimerEnable(GPT2_BASE, TIMER_A);


}


void post_sem(void){

	TimerIntClear(GPT2_BASE, TIMER_TIMA_TIMEOUT);
	if(count%2==0){

		//post sem
		Semaphore_post(led);
		Semaphore_post(led2);


	}
	else{
		Semaphore_post(led);


	}

	count++;

}

void led_init(void){

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
    if(!ledPinHandle) {
        System_abort("Error initializing board LED pins\n");
    }

    PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
    PIN_setOutputValue(ledPinHandle, Board_LED2, 1);
}

void led_toggle(void){

	while(1){

		Semaphore_pend(led,BIOS_WAIT_FOREVER);
		PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
	}
}

void led_toggle2(void){

	while(1){

		Semaphore_pend(led2,BIOS_WAIT_FOREVER);
		PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));
	}
}
/*
 *  ======== main ========
 */
int main(void)
{


    /* Call board init functions */
    Board_initGeneral();
    // Board_initI2C();
    // Board_initSPI();
    // Board_initUART();
    // Board_initWatchdog();

    /*Timer Init*/
    timer_init();

    /*LED init*/
    led_init();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
