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

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
// #include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
#include <ti/drivers/pin/PINCC26XX.h>

/* Board Header files */
#include "Board.h"

/* Pin driver handles */
static PIN_Handle buttonPinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State buttonPinState;

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
PIN_Config buttonPinTable[] = {
		Board_KEY_LEFT  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
		Board_KEY_RIGHT  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};



/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config ledPinTable[] = {
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
	Board_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

void LED_INIT(void){

	   /* Open LED pins */
	    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
	    if(!ledPinHandle) {
	        System_abort("Error initializing board LED pins\n");
	    }

	    PIN_setOutputValue(ledPinHandle, Board_LED1, 0);
	    PIN_setOutputValue(ledPinHandle, Board_LED2, 0);


}

void BUTTON_INIT(void){

	   buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
	        if(!buttonPinHandle) {
	            System_abort("Error initializing button pins\n");
	    }


	    // SET INTERRUPT
		PIN_setInterrupt(buttonPinHandle, Board_KEY_LEFT|PIN_IRQ_NEGEDGE);
		PIN_setInterrupt(buttonPinHandle, Board_KEY_RIGHT|PIN_IRQ_NEGEDGE);


}

void button_press(void){
	CPUdelay(8000*100);


	 //clear interrupt
	      PINCC26XX_clrPendInterrupt(Board_KEY_LEFT);
	      PINCC26XX_clrPendInterrupt(Board_KEY_RIGHT);
	 //blink LED based on button
	      if (!PIN_getInputValue(Board_KEY_LEFT)) {

	    	  PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
	      }

	      else if(!PIN_getInputValue(Board_KEY_RIGHT)){
	    	  PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));

	      }
	      else if((!PIN_getInputValue(Board_KEY_LEFT))&&(!PIN_getInputValue(Board_KEY_RIGHT))){
	    	  // DO NOTHING
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


    LED_INIT();
    BUTTON_INIT();


    /* Start BIOS */
    BIOS_start();

    return (0);
}
