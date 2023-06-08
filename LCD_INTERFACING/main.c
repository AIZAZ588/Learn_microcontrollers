/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>        /* XC8 General Include File */
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#define _XTAL_FREQ 8000000      //Used by the compiler for the delay_ms(x) macro

#define DATA_DIR TRISD
#define DATA PORTD
#define EN_DIR TRISAbits.RA0
#define EN PORTAbits.RA0
#define RS_DIR TRISAbits.RA1
#define RS PORTAbits.RA1

void LCD_INT(void); //initialize
void LCD_INST(char cmd);
void LCD_DATA(char data);
void LCD_TEXT(char* text);
void LCD_CURSOR(char col,char line);

void main(void) {
    LCD_INT();
    LCD_TEXT("WELCOME0");
    LCD_CURSOR(4,2);
    LCD_TEXT("AIZAZ0");
            
    while (1) {
    
    }
    return;
}
void LCD_CURSOR(char col,char line){
    if (line == 1)
    {
        LCD_INST(0b10000000 | col);
    }
    else if (line == 2)
    {
        LCD_INST(0b11000000 | col);
    }
}

void LCD_TEXT(char* text){
    while(*text != '\0')
    {
        LCD_DATA(*text);
        ++text;
    }
}
void LCD_INT(void){
    DATA_DIR = 0;
    EN_DIR = 0;
    RS_DIR = 0;
    
    //LCD_INST(0b00000001); // clear display
    LCD_INST(0b00111100); // set function
    LCD_INST(0b00000110); // set mode
    LCD_INST(0b00001111); // display on/off
    
    
}

void LCD_INST(char cmd){
    RS = 0;
    EN = 1;
    __delay_ms(1);
     DATA = cmd;
    EN = 0;
    __delay_ms(5); //5ms
    
}

void LCD_DATA(char data){
    EN = 1;
    __delay_ms(1);
     RS = 1;
     DATA = data;
    EN = 0;
    __delay_ms(5);
}
