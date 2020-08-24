#include "USART.h"

    void USART_Init(USART_InitTypeDef * USARTInit)
    {
        unsigned int temp,spbrg,actualbaud,error=0;
        char i=0;
        char n[3]={64,16,4};
        temp = USARTInit->BaudRate;
        do{
            
            spbrg= _XTAL_FREQ/temp/n[i]-1;
            actualbaud= _XTAL_FREQ/n[i]/(spbrg+1);
            if (actualbaud>temp)
                 error = (actualbaud-temp);//*100.0/temp;
            else
                 error = (temp-actualbaud);//*100.0/temp;
            
            error = error*100.0/temp;
            i++;
        }while(error>=1);
        
        i--;
        SPBRG=spbrg;
        switch(i)
        {
            case 0:
                
                break;
            case 1:
                
                if(spbrg>255)
                {
                    SPBRGH=spbrg>>8;
                    BAUDCTL |=1<<3;  // BRG16=1 
                    
                }
                else
                {
                    TXSTA |=1<<2;   // BRGH=1
                }
                    
                break;
            case 2:
                 TXSTA |=1<<2;   // BRGH=1
                 BAUDCTL |=1<<3;  // BRG16=1 
                 SPBRGH=spbrg>>8;
                break;
        }
        if( USARTInit->RxInterruptEn)
            USART_RxInterrupt(USART_ENABLE);
        
        if(USARTInit->TxInterruptEn)
            USART_TxInterrupt(USART_ENABLE);
            
        if(USARTInit->NineBit)
            TXSTA |= 1<<6;
        
        if(USARTInit->AddressEnable)
            RCSTA|=1<<3;
        
        
    }

    void USART_Enable(char En)
    {
        if (En)
            RCSTA |=1<<7;
        else
            RCSTA &=~(1<<7);
    }
    void USART_RxInterrupt(char En)
    {
        if (En)
            PIE1 |=1<<5;
        else
            PIE1 &=~(1<<5);
        
    }
    void USART_TxInterrupt(char En)
    {
         if (En)
            PIE1 |=1<<4;
        else
            PIE1 &=~(1<<4);
    }
    char USART_GetIntFlag(char TxRx){
        char n;
        if(TxRx)
            n=4;
        else
            n=5;
               return (PIR1 & (1<<n)) ? TRUE:FALSE;
        
            
    }
        
//    void USART_ClrIntFlag(char TxRx)
//    {
//        
//    }
    
    void USART_AddressEnable(char En)
    {
        if(En)
            RCSTA |=1<<3;
        else
            RCSTA &=~(1<<3);
            
    }
    void USART_TransmiterEnable(char En)
    {
        if(En)
            TXSTA |=1<<5;
        else
        {
            while(~USART_GetTRMT())
                  ;
            TXSTA &=~(1<<5);
        }
    }
    void InterruptEnable(char En){
        if(En)
            INTCON|=(1<<6)|(1<<7);
        else
            INTCON&=~((1<<6)|(1<<7));
            
    }
    void USART_ReceiverEnable(char En)
    {
        if(En)
            RCSTA |=1<<4;
        else
            RCSTA &=~(1<<4);
    }
    void USART_Putc(char ch)
    {
        while(!USART_GetIntFlag(TX))
               ;
        TXREG = ch;
    }
    char USART_Getc(void)
    {
        if(USART_GetOERR())
        {
             USART_ReceiverEnable(USART_DISABLE);
             USART_ReceiverEnable(USART_ENABLE);
        }
         if( USART_GetIntFlag(RX)){
             return RCREG;
         }
         else 
             return 0;
    }
    void USART_ClrRxFlag(void){
        PIR1 &= ~(1<<5);
    }
    inline char USART_GetFERR(void)
    {
        return (RCSTA & (1<<2)) ? TRUE:FALSE;
    }
    inline char USART_GetOERR(void)
    {
        return (RCSTA & (1<<1)) ? TRUE:FALSE;
    }
    inline char USART_GetTRMT(void)
    {
        return (TXSTA & (1<<1)) ? TRUE:FALSE;
    }
    void USART_Print(char * ch)
    {
        while(*ch)
            USART_Putc(*ch++);
    }
    void USART_PrintDecimal(int num)
    {
          
    }
    void USART_Putc9(unsigned int data)
    {
        
    }
