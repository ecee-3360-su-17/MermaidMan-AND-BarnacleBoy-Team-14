/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "fib.asm"

extern int fib(int n);

int main(void) {

    int n;

     // Enable the GPIO port that is used for the on-board LED.
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

     // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
     // enable the GPIO pin for digital function.
     GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);


     while(1){
         for(n = 0; n < 21; n++){
             fib(n);
             printf("%d\n", n);
             blink(n);
         }
     }
}

//n represents fib
void blink(int n){

    int i;
    volatile uint32_t ui32Loop;

    char pattern = convert_to_morse(n);
    for(i = 0; i < 4; i++){

        int state = (pattern & 0b1) >> i;

        //SET LED STATE
        if(state == 0){
            //LED ON
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

            //SHORT DELAY
            for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++){}

            //LED OFF
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        }

        else if(state == 1){
           //LED ON
           GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

           //LONG DELAY
           for(ui32Loop = 0; ui32Loop < 400000; ui32Loop++){}

           //LED OFF
           GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        }

        //WAIT BETWEEN DIGITS (delay between each blink)
        for(ui32Loop = 0; ui32Loop < 100000; ui32Loop++){}
    }

    //LONG WAIT BETWEEN NUMBERS
    for(ui32Loop = 0; ui32Loop < 400000; ui32Loop++){}

}

//Convert to morse code
char convert_to_morse(int n){
    switch(n){
    case 0:
        return 0b11111;
        //break;
    case 1:
        return 0b01111;
        break;
    case 3:
        return 0b00111;
        break;
    case 4:
        return 0b00001;
        break;
    case 5:
        return 0b00000;
        break;
    case 6:
        return 0b10000;
        break;
    case 7:
        return 0b11000;
        break;
    case 8:
        return 0b11100;
        break;
    case 9:
        return 0b11110;
        break;
    default:
        break;

    }

    return n;
}
