#include <xc.h>
#include "LCD.h"

#define _XTAL_FREQ  4000000UL


void LCD_Init(void){
    LCD_TRIS&=0x00;
    LCD_PORT=0x00;
    
    LCD_ClrRS(); 
    LCD_WriteNibble(0x3);
    __delay_ms(15);
    LCD_WriteNibble(0x3);
    __delay_ms(2);
    LCD_WriteNibble(0x3);
    LCD_WriteNibble(0x2);
    LCD_Command(0x28);
    LCD_Command(0x0F);
    LCD_Command(0x06);
    LCD_Command(0x01);
    __delay_ms(2);
}
void LCD_Print(char *ptr){
    while (*ptr){
        LCD_DataWrite(*ptr);
        ptr++;
    }
}
void LCD_WriteNibble(char x){
    LCD_Data(x);
    LCD_SetE();
    __delay_us(1);
    LCD_ClrE();
    __delay_us(10);
}
void LCD_Command(char x){
    LCD_ClrRS();
    LCD_WriteNibble(x>>4);
    LCD_WriteNibble(x);
}
void LCD_DataWrite(char x){
    LCD_SetRS();
    LCD_WriteNibble(x>>4);
    LCD_WriteNibble(x);
}
void LCD_GotoXY(char X,char Y){
    char cmd;
    switch(Y){
        case 1:
        cmd=LCD_LINE1;
        break;
        case 2:
        cmd=LCD_LINE2;
        break;
        case 3:
        cmd=LCD_LINE3;
        break;
        case 4:
        cmd=LCD_LINE4;
        break;
        default:
        cmd=LCD_LINE1;
    }   
    cmd+=X;
    LCD_Command(cmd);
}
void LCD_ClearLine(char Line)
{
    switch(Line)
    {
        case 0:
        case 1:
            LCD_GotoXY(0,1);
            LCD_Print(BLANK);
            LCD_GotoXY(0,1);
            break;
             case 2:
            LCD_GotoXY(0,2);
            LCD_Print(BLANK);
            LCD_GotoXY(0,2);
            break;
             case 3:
            LCD_GotoXY(0,3);
            LCD_Print(BLANK);
            LCD_GotoXY(0,3);
            break;
             case 4:
            LCD_GotoXY(0,4);
            LCD_Print(BLANK);
            LCD_GotoXY(0,4);
            break;
    }
}
void LCD_Cursor(char x)
{
    LCD_Command(x);
}
void LCD_WriteCGRAM(char *ptr,char no){
    LCD_Command(0x40 + no%8);
    for(char i=0;i<8;i++){
        LCD_DataWrite(*ptr++);
    }
    LCD_Clear();
}
