// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "LCD.h"
#include "USART.h"
#include "COMMENT.h"
#include <stdio.h>
#include <string.h>
void init (void);  
char rxdata[20];
char cmtdata[20];
char CheckEnterTemp;
void main (void){ 
    int word=111;
    char i=0;
    ei();
   init();  
   LCD_Cursor(LCD_DISPLAY_ON|LCD_UNDERLINE_ON|LCD_BLINK_ON);
    USART_Print("Turning on LED red:R-on,yellow:Y-on,blue:B-on.");
    USART_Putc(ENTER);
    USART_Print("Turning off LED red:R-off,yellow:Y-off,blue:B-off.");
     USART_Putc(ENTER);
    USART_Print("Comment-");
    USART_Putc(ENTER);
    
    while(1){
        if( USART_GetIntFlag(RX))
    {
        CheckEnterTemp=RCREG;
        if(CheckEnterTemp!=ENTER){
            if(CheckEnterTemp!=DELETE){
                word++;
        rxdata[i++%20]=CheckEnterTemp;
            }
            else if(CheckEnterTemp==DELETE && i>0 && word>0){
                i--;
            rxdata[i]=0;
            word--;
            }
            
        }
        }
        if(CheckEnterTemp==ENTER){
         
        CheckEnterTemp=0;
        for(char j=0;j<20;j++)
            cmtdata[j]=rxdata[j];
        i=0;
        for(char j=0;j<20;j++)
            rxdata[j]=0;
        
        }  
        comment_test(cmtdata,word); 
        for(char j=0;j<20;j++)
            cmtdata[j]=0;
       }}
      

void init (void)
{
    LEDPORT=0x00;
    TRISC&=~(0x1F);
    TRISC &=~(1<<6);
    USART_InitTypeDef usart;
    usart.AddressEnable=0;
    usart.BaudRate=9600;
    usart.Mode= USART_MODE_ASYNCHRONOUS;
    usart.NineBit =0;
    usart.TxInterruptEn =USART_ENABLE;
    usart.RxInterruptEn = USART_ENABLE;
    USART_Init(& usart);  
    USART_Enable(USART_ENABLE);
    USART_ReceiverEnable(USART_ENABLE);
    USART_TxInterrupt(USART_ENABLE);
    USART_TransmiterEnable(USART_ENABLE);
    USART_RxInterrupt(USART_ENABLE);
     InterruptEnable(USART_ENABLE);
    LCD_Init();
    LCD_Print("Write Comment:");
}
//void __interrupt() ISR(void)
//{
//    if( USART_GetIntFlag(RX))
//    {
//        CheckEnterTemp=RCREG;
//        if(CheckEnterTemp!=ENTER)
//        rxdata[i++%16]=CheckEnterTemp;
//        
//    }
//}