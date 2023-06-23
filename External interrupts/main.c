////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                  External Interrupt0 of PIC18F4550                                                             //
//                                                                                                                //
//                                                                                                                //
//Author : aizazkhan022017@gmail.com                                                                              //
//                                                                                                                //
//                                                                                                                //
//                                                                                                                //
//NOTE:                                                                                                           //
//     1) I did'nt add PORTB Pull-up Resistors (I comment it because i have external Pull-up Resistor)            //
//        if you want to enable edd this line before while(1) INTCON2bits.RBPU =0;                                //
//                                                                                                                //
//                                                                                                                //
//                                                                                                                //
//                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <xc.h>                                                                                                      

#define _XTAL_FREQ 4000000 // 4MHz, used by the delay_ms() function

void main()
{
    // Configure I/O ports
    TRISBbits.RB0 = 1; // push button
    TRISD = 0; // Configure PortD as output port
    
    // Interrupt Configuration
    INTCONbits.INT0IF = 0; // Clear INT0 flag
    INTCONbits.INT0IE = 1; // Enable INT0
    INTCON2bits.INTEDG0 = 1; // Set Rising Edge Trigger for INT0
    
    // ADC Configuration
    ADCON1 = 0x0F; // Configure I/O pins as digital
    
    // Global Interrupt Enable
    INTCONbits.GIE = 1;

    while (1)
    {
        LATD = 0x55; // Set value at PortD
        __delay_ms(500); // Delay for 1 sec
    }
}

void __interrupt() isr(void) // Interrupt ISR
{
    if (INTCONbits.INT0IF == 1)
    {
        INTCONbits.INT0IF = 0; // Clear the INT0 flag
        LATD = ~LATD; // Invert the value at PortD
    }
}
