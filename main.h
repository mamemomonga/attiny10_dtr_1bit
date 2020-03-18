/*
 * ATTiny10
 * INT0(PB2)の信号がLOWになった回数を数える
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
    ATtiny10 SOT32
   LED2 PB0 | 1   6 | /RST
        GND | 2   5 | VCC
   LED1 PB1 | 3   4 | PB2 INT0
*/

// LED1
#define LED1     ( 1<<PB1 )
#define LED1_OUT DDRB  |=  LED1 
#define LED1_H   PORTB |=  LED1 
#define LED1_L   PORTB &=~ LED1 
#define LED1_I   PORTB ^=  LED1 

// LED2
#define LED2     ( 1<<PB0 )
#define LED2_OUT DDRB  |=  LED2 
#define LED2_H   PORTB |=  LED2 
#define LED2_L   PORTB &=~ LED2  
#define LED2_I   PORTB ^=  LED2  

// DTR(INT0)
#define DTR       ( 1<<PB2 )
#define DTR_OUT     DDRB  |=  DTR 
#define DTR_IN    { DDRB  &=~ DTR; PORTB &=~ DTR; }
#define DTR_INPU  { DDRB  &=~ DTR; PORTB |=  DTR; }
#define DTR_H       PORTB |=  DTR 
#define DTR_L       PORTB &=~ DTR 
#define DTR_IS_H  ( PINB  &   DTR )
#define DTR_IS_L !( PINB  &   DTR )

// nミリ秒の間をカウントする
#define SIGNAL_TIMEOUT 100

// カウンタ
uint8_t count;

int main(void);

void loop();
void result();

#endif
