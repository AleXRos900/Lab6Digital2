/*
 * Lab2Nucleo.c
 *
 * Created: 25/03/2025 18:27:01
 * Author : Alex
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

#include "UART/UART.h"

volatile uint8_t lastPortDState = 0;
volatile char * Direc;
volatile uint8_t NewDat = 0; 

void setup(void)
{
	initUART9600();
	
	DDRD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTD |= ((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));	
	
	PCICR |= (1 << PCIE2);
	PCMSK2 = 0xFF;	

	sei();
}


int main(void)
{
	setup();
    /* Replace with your application code */
    while (1) 
    {
		if (NewDat == 1){WriteTextUART(Direc); NewDat = 0;}
    }
}

ISR(PCINT2_vect)
{
	uint8_t currentState = PIND;
	uint8_t changed = currentState ^ lastPortDState;
	
	if(changed & (1 << PD2)) {
		if(!(currentState & (1 << PD2))) 
		{
			Direc = "DERECHA\r\n";
			NewDat = 1;
		}
	}
	if(changed & (1 << PD3)) {
		if(!(currentState & (1 << PD3))) 
		{
			Direc = "IZQUIERDA\r\n";
			NewDat = 1;
		}
	}
	if(changed & (1 << PD4)) {
		if(!(currentState & (1 << PD4))) 
		{
			Direc = "ARRIBA\r\n";
			NewDat = 1;
		}
	}
	if(changed & (1 << PD5)) {
		if(!(currentState & (1 << PD5))) 
		{
			Direc = "ABAJO\r\n";
			NewDat = 1;
		}
	}
	if(changed & (1 << PD6)) {
		if(!(currentState & (1 << PD6))) 
		{
			Direc = "BOTA\r\n";
			NewDat = 1;
		}
	}
	if(changed & (1 << PD7)) {
		if(!(currentState & (1 << PD7))) 
		{
			Direc = "BOTB\r\n";
			NewDat = 1;
		}
	}
	
	lastPortDState = currentState;
	
	_delay_ms(20);
}
