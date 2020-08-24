/* 
 * File:   COMMENT.h
 * Author: acer
 *
 * Created on March 25, 2020, 7:33 PM
 */

#ifndef COMMENT_H
#define	COMMENT_H

#ifdef	__cplusplus
extern "C" {

#endif
#include<xc.h>
//#define YELLOW 0
//#define BIBY      1
//#define RED       2
//#define GREEN   3
//#define BLUE     4
//#define ON_OFF      5    
//#define bitset(var,bitno) var|=1<<bitno
//#define bitclr(var,bitno)  var&=~1<<bitno
#define bittest(var,bitno) (var&(1<<bitno))
#define DELETE 0x08
#define CLR "                                                                  "
    char cmt;
    void comment(char CMT[],int del);
    void comment_test(char CMT[],int del);
    
    typedef union{
    char LED:6;
    struct {
        char yellow:1;
        char biby:1;
        char red:1;
        char green:1;
        char blue:1;
        char ntin:3;
    };
}led;
#define LEDPORT PORTC
#define cmt ((led*)&LEDPORT)
#ifdef	__cplusplus
}
#endif

#endif	/* COMMENT_H */

