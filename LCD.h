/* 
 * File:   LCD.h
 * Author: acer
 *
 * Created on January 23, 2020, 1:54 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#define LCD_TRIS          TRISD
#define LCD_PORT         PORTD
#define LCD_SetRS()     LCD_PORT|=1<<4
#define LCD_ClrRS()      LCD_PORT&=~(1<<4)
#define LCD_SetE()       LCD_PORT|=1<<5
#define LCD_ClrE()        LCD_PORT&=~(1<<5)
#define LCD_Data(x)     LCD_PORT&=0xF0;\
                                   LCD_PORT|=(x) & 0x0F;
#define LCD_Home()     LCD_Command(0x02);__delay_ms(2)
#define LCD_Clear()      LCD_Command(0x01);__delay_ms(2)
#define LCD_DISPLAY_SHIFT_LEFT        LCD_Command(0x18)
#define LCD_DISPLAY_SHIFT_RIGHT        LCD_Command(0x1C)
#define LCD_CURSOR_SHIFT_LEFT        LCD_Command(0x14)
#define LCD_CURSOR_SHIFT_RIGHT        LCD_Command(0x10)
    
#define LCD_UNDERLINE_ON (0x08|1<<1)
#define LCD_BLINK_ON (0x08|1)
#define LCD_DISPLAY_ON (0x08|1<<2)
    
#define LCD_LINE1       (1<<7|0)
#define LCD_LINE2       (1<<7|0x40)
#define LCD_LINE3       (1<<7|0x14)
#define LCD_LINE4       (1<<7|0x54)
#define BLANK             "                    "   
    
void LCD_Init(void);
void LCD_WriteNibble(char x);
void LCD_Command(char x);
void LCD_DataWrite(char x);
void LCD_Print(char *ptr);
void LCD_GotoXY(char X,char Y);
void LCD_ClearLine(char line);
void LCD_WriteCGRAM(char *ptr,char no);
void LCD_Cursor(char x);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

