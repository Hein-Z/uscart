#include"COMMENT.h"
#include"LCD.h"
#include"USART.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
void comment_test(char CMT[],int del){
    char chr,i=0;
     while (CMT[i]) { 
        chr = CMT[i]; 
        CMT[i]= toupper(chr); 
        i++; 
    } 
  
    comment(CMT,del);
    }
void comment(char CMT[],int del){
    static char state=0;
    static int count=0;
    static int animate=0;
    state=0;
     enum cmd{delete=1,y_o,y_f,i_o,i_f,g_o,g_f,b_o,b_f,r_o,r_f,error,close_all};
    if(strcmp(CMT,"CLR")==0){
        for(char i=0; i<del;i++)
                USART_Putc(DELETE);
        state=delete;}
     else if(strcmp(CMT,"Y-ON")==0)
        state=y_o;
    else if(strcmp(CMT,"Y-OFF")==0)
        state=y_f;
     else if(strcmp(CMT,"G-ON")==0)
        state=g_o;
    else if(strcmp(CMT,"G-OFF")==0)
        state=g_f;
     else if(strcmp(CMT,"R-ON")==0)
        state=r_o;
    else if(strcmp(CMT,"R-OFF")==0)
        state=r_f;
     else if(strcmp(CMT,"B-ON")==0)
        state=b_o;
    else if(strcmp(CMT,"B-OFF")==0)
        state=b_f;
     else if(strcmp(CMT,"I-ON")==0)
        state=i_o;
    else if(strcmp(CMT,"I-OFF")==0)
        state=i_f;
     else if(strcmp(CMT,"CLOSE-ALL")==0)
        state=close_all;
     else if(strcmp(CMT,"ANIMATE")==0){
         animate=1;
         count=0;
     }
    else if(strcmp (CMT,'\0')==0)
        state=0;
    else
        state=error;
    switch (state){
        case delete:
            LCD_ClearLine(1);
             LCD_Print("CLEAR Terminal");
             count=0;
            break;
        case y_o: 
            count=0;
            animate=0;
            cmt->yellow|=1;
           LCD_ClearLine(1);
           LCD_Print("Yellow LED_ON");
           break;
        case y_f:
            count=0;
            animate=0;
             cmt->yellow&=0;
            LCD_ClearLine(1);
           LCD_Print("Yellow LED_OFF");
        
            break;
            
            
        case i_o:
            count=0;
            animate=0;
        cmt->biby|=1;
        LCD_ClearLine(1);
        LCD_Print("Biby LED_ON");
        break;
        
        case i_f:
            count=0;
            animate=0;
             cmt->biby&=0;
         LCD_ClearLine(1);
           LCD_Print("Biby LED_OFF");
         break;
           
        case r_o:
            count=0;
            animate=0;
            cmt->red|=1;
        LCD_ClearLine(1);
           LCD_Print("Red LED_ON");
           break;
        case r_f:
        count=0;
        animate=0;
             cmt->red&=0;
             LCD_ClearLine(1);
           LCD_Print("Red LED_OFF");
        
            break;
        case g_o:
           count=0;
           animate=0;
            cmt->green|=1;
        LCD_ClearLine(1);
           LCD_Print("Green LED_ON");
           break;
        case g_f:
            count=0;
            animate=0;
             cmt->green&=0;
             LCD_ClearLine(1);
           LCD_Print("Green LED_OFF");
             
            break;
        case b_o:
             count=0;
             animate=0;
            cmt->blue|=1;
        LCD_ClearLine(1);
           LCD_Print("Blue LED_ON");
        
           break;
        case b_f:
            count=0;
            animate=0;
             cmt->blue&=0;
        LCD_ClearLine(1);
           LCD_Print("blue LED_OFF");
        
         break;
         case close_all:
             count=0;
             animate=0;
            LCD_ClearLine(1);
            LCD_Print("Close All LED");
            cmt->LED&=0;
            break;
        case 0:count++;
        if(count==0x0FFF){
            count=0;
            LCD_ClearLine(1);
            LCD_Print("Write Comment:");
        }
        if(animate){
           static char k=0;
            animate++;
            if(animate<819){
                k++;
                animate=1;
                if(k==6)
                    k=0;
            }
            cmt->LED=1<<k;
        }
            break;
        
        case error:
            count=0;
            LCD_ClearLine(1);
           LCD_Print("ERROR");
            break;
        default:
            state=0;
            break;
    }
}
