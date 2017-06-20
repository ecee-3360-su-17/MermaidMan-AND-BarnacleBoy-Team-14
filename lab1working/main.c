
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


void blink(int n);
char convert_to_morse(int n);

extern int fib(int n);

    int main(void) {

    //int n;
    volatile uint32_t ui32Loop;

     // Enable the GPIO port that is used for the on-board LED.
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

     // Check if the peripheral access is enabled.
     while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}


     // Enable the GPIO pin for the LED .  Set the direction as output, and
     // enable the GPIO pin for digital function.
     GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);        //RED LED
     GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);        //BLUE LED


   while(1){

       blink(fib(8));

     }


}

//n represents fib
void blink(int n){

    int i;
    volatile uint32_t ui32Loop;


/*------------------------------------------------------------------------------------------------
---------------------------------IF CONDITION FOR DOUBLE DIGIT------------------------------------
--------------------------------------------------------------------------------------------------
----Checks the state where the n value is double digits and treats them as 2 individual digits----
-------------------------------------------------------------------------------------------------*/

    if(n > 9 && n <= 99){
        int a = n/10;   //tens digit
        int b = n%10;   //ones digit

        char pat_a = convert_to_morse(a);   //convert tens digit to morse
        char pat_b = convert_to_morse(b);   //convert ones digit to morse

//--------------------------------------------------------------------------------------------------
//------------------------------MORSE CODE CONVERSION FOR 10's DIGIT--------------------------------
//--------------------------------------------------------------------------------------------------

        for(i = 0; i < 5; i++){
            int state_a = (pat_a << i) & 0b10000;

            //SET RED LED STATE (short)
            if(state_a == 0){
                //LED ON
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

                //SHORT DELAY
                 for(ui32Loop = 0; ui32Loop < 1500000; ui32Loop++){}

                //LED OFF
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
            }

            //SET BLUE LED STATE (long)
            else if(state_a >= 1){
                //LED ON
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

                 //LONG DELAY
                 for(ui32Loop = 0; ui32Loop < 3000000; ui32Loop++){}

                 //LED OFF
                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
                  }
            //WAIT BETWEEN DIGITS (delay between each blink)
            for(ui32Loop = 0; ui32Loop < 100000; ui32Loop++){}
        }

        //WAIT BETWEEN NUMBERS
        for(ui32Loop = 0; ui32Loop < 500000; ui32Loop++){}

//--------------------------------------------------------------------------------------------------
//------------------------------MORSE CODE CONVERSION FOR 1's DIGIT--------------------------------
//--------------------------------------------------------------------------------------------------

        for(i = 0; i < 5; i++){
            int state_b = (pat_b << i) & 0b10000;

             //SET RED LED STATE (short)
             if(state_b == 0){
                 //LED ON
                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

                 //SHORT DELAY
                 for(ui32Loop = 0; ui32Loop < 1500000; ui32Loop++){}

                 //LED OFF
                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
               }

                 //SET BLUE LED STATE (long)
                 else if(state_b >= 1){
                     //LED ON
                     GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

                      //LONG DELAY
                      for(ui32Loop = 0; ui32Loop < 3000000; ui32Loop++){}

                      //LED OFF
                      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
                  }
                  //WAIT BETWEEN DIGITS (delay between each blink)
                  for(ui32Loop = 0; ui32Loop < 100000; ui32Loop++){}
           }
           //LONG WAIT BETWEEN NUMBERS
           for(ui32Loop = 0; ui32Loop < 1000000; ui32Loop++){}

    }

//--------------------------------------------------------------------------------------------------
//--------------------------------ELSE CONDITION FOR SINGLE DIGIT-----------------------------------
//--------------------------------------------------------------------------------------------------

    else{
        char pattern = convert_to_morse(n);

        for(i = 0; i < 5; i++){

            int state = (pattern << i) & 0b10000;

            //SET RED LED STATE (short)
            if(state == 0){
                //LED ON
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

                //SHORT DELAY
                for(ui32Loop = 0; ui32Loop < 1500000; ui32Loop++){}

                //LED OFF
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
            }

            //SET BLUE LED STATE (long)
            else if(state >= 1){
                //LED ON
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

                //LONG DELAY
                for(ui32Loop = 0; ui32Loop < 3000000; ui32Loop++){}

                 //LED OFF
                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
            }

            //WAIT BETWEEN DIGITS (delay between each blink)
            for(ui32Loop = 0; ui32Loop < 100000; ui32Loop++){}
        }

        //LONG WAIT BETWEEN NUMBERS
        for(ui32Loop = 0; ui32Loop < 1000000; ui32Loop++){}
    }

}



//Convert to morse code
char convert_to_morse(int n){
    switch(n){
    case 0:
        return 0b11111;
        //break;
    case 1:
        return 0b01111;
        //break;
    case 2:
        return 0b00111;
        //break;
    case 3:
        return 0b00011;
        //break;
    case 4:
        return 0b00001;
        //break;
    case 5:
        return 0b00000;
        //break;
    case 6:
        return 0b10000;
       //break;
    case 7:
        return 0b11000;
        //break;
    case 8:
        return 0b11100;
        //break;
    case 9:
        return 0b11110;
        //break;
    default:
        break;

    }

    return n;
}
