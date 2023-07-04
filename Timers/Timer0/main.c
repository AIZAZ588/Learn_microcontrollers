////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 Timer0  PIC18F4550                                                             //
//                                                                                                                //
//                                                                                                                //
//Author : aizazkhan022017@gmail.com                                                                              //
//                                                                                                                //
//                                                                                                                //
//                                                                                                                //
//NOTE:                                                                                                           //
//                                                                                                                //
//                                                                                                                //
//                                                                                                                //
//                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <xc.h>                                                                                                    

#define _XTAL_FREQ 4000000 // 4MHz

void tmr_init(void){
  T0CONbits.PSA = 0; 
  T0CONbits.T0PS = 2;
  T0CONbits.T08BIT =1;
  T0CONbits.T0CS =0;
  
  
  INTCONbits.GIE =1;
  INTCONbits.TMR0IF =0;
  INTCONbits.TMR0IE =1;
 
  
  T0CONbits.TMR0ON =1;
    
}

void __interrupt() ISR(void){
    if (INTCONbits.TMR0IE & INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF =0;
        LATDbits.LATD0 ^=1;
        return;
    }
}
int main(void){
    TRISDbits.RD0 =0;
    tmr_init();
    while(1);
}
