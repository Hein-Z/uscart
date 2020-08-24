/* 
 * File:   USART.h
 * Author: ME
 *
 * Created on January 25, 2020, 2:49 PM
 */

#ifndef USART_H
#define	USART_H
#include<xc.h>
#ifdef	__cplusplus
extern "C" {
#endif
#define USART_ENABLE  1
#define USART_DISABLE 0
#define USART_MODE_ASYNCHRONOUS 0
#define USART_MODE_SYSCHRONOUS 1
#define TX  1
#define RX  0 
#define ENTER 0x0D
    
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000   // Default Frequency
#endif
    
    typedef struct{
        unsigned int BaudRate;
        struct{
            char Mode:1;
            char NineBit:1;
            char AddressEnable:1;
            char TxInterruptEn:1;
            char RxInterruptEn:1;
            char Unused:3;
        };
    }USART_InitTypeDef;
    enum {FALSE,TRUE=~FALSE};
    void USART_Init(USART_InitTypeDef* USARTInit);
    void USART_Enable(char En);
    char USART_GetIntFlag(char TxRx);
    void USART_ClrIntFlag(char TxRx);
    void USART_AddressEnable(char En);
    void USART_TransmiterEnable(char En);
    void USART_ReceiverEnable(char En);
    void USART_Putc(char ch);
    char USART_Getc(void);
    inline char USART_GetFERR(void);
    inline char USART_GetOERR(void);
    inline char USART_GetTRMT(void);
    void USART_Print(char * ch);
    void USART_PrintDecimal(int num);
    void USART_Putc9(unsigned int data);
    void USART_RxInterrupt(char En);
    void USART_TxInterrupt(char En);
      void USART_ClrRxFlag(void);
    void InterruptEnable(char En);

#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

