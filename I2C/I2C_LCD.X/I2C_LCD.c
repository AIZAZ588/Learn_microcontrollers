#include <xc.h>
#include "I2C_LCD.h"
#include <pic18f4550.h>

unsigned char RS, i2c_add, BackLight_State = LCD_BACKLIGHT;

//---------------[ I2C Routines ]-------------------
//--------------------------------------------------
void I2C_Master_Init()
{
    SSPCON1 = 0x28;       // SSPEN = 1, SSPM3:SSPM0 = 1000 (I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)))
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate) - 1;
    // Configure SDA and SCL pins as inputs
    // Configure SDA and SCL pins as inputs
    TRISBbits.TRISB0 = 1; // Set RB0 as input
    TRISBbits.TRISB1 = 1; // Set RB1 as input


}

void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}

unsigned char I2C_Master_Write(unsigned char data)
{
    I2C_Master_Wait();
    SSPBUF = data;
    while (!SSPIF);       // Wait Until Completion
    SSPIF = 0;
    return ACKSTAT;
}


//======================================================

//---------------[ LCD Routines ]----------------
//------------------------------------------------------

void LCD_Init(unsigned char I2C_Add)
{
    i2c_add = I2C_Add;
    IO_Expander_Write(0x00);
    __delay_ms(30);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(LCD_RETURN_HOME);
    __delay_ms(5);
    LCD_CMD(0x20 | (LCD_TYPE << 2));
    __delay_ms(50);
    LCD_CMD(LCD_TURN_ON);
    __delay_ms(50);
    LCD_CMD(LCD_CLEAR);
    __delay_ms(50);
    LCD_CMD(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
    __delay_ms(50);
}

void IO_Expander_Write(unsigned char Data)
{
    I2C_Master_Start();
    I2C_Master_Write(i2c_add);
    I2C_Master_Write(Data | BackLight_State);
    I2C_Master_Stop();
}

void LCD_Write_4Bit(unsigned char Nibble)
{
    Nibble |= RS;
    IO_Expander_Write(Nibble | 0x04);
    IO_Expander_Write(Nibble & 0xFB);
    __delay_us(50);
}

void LCD_CMD(unsigned char CMD)
{
    RS = 0;
    LCD_Write_4Bit(CMD & 0xF0);
    LCD_Write_4Bit((CMD << 4) & 0xF0);
}

void LCD_Write_Char(char Data)
{
    RS = 1;
    LCD_Write_4Bit(Data & 0xF0);
    LCD_Write_4Bit((Data << 4) & 0xF0);
}

void LCD_Write_String(char* Str)
{
    for (int i = 0; Str[i] != '\0'; i++)
        LCD_Write_Char(Str[i]);
}

void LCD_Set_Cursor(unsigned char ROW, unsigned char COL)
{
    switch (ROW)
    {
        case 2:
            LCD_CMD(0xC0 + COL - 1);
            break;
        case 3:
            LCD_CMD(0x94 + COL - 1);
            break;
        case 4:
            LCD_CMD(0xD4 + COL - 1);
            break;
        default:
            LCD_CMD(0x80 + COL - 1);
    }
}


void LCD_SL()
{
    LCD_CMD(0x18);
    __delay_us(40);
}

void LCD_SR()
{
    LCD_CMD(0x1C);
    __delay_us(40);
}

