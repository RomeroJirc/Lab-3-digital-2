/*
 * Lab 3 Digital ESCLAVO.c
 *
 * Created: 26/07/2024 09:13:16 a. m.
 * Author : josei
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "SPI/SPI.h"
#include "ADC/ADC.h"

volatile uint8_t ValorADC1 = 0;
volatile uint8_t ValorADC2 = 0;

int main(void)
{
	cli();
    InitSPI(SPI_SLAVE_SS, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	initADC();
	SPCR |= (1<<SPIE);			//ACTIVAR ISR SPI
	sei();
    while (1) 
    {
		ValorADC1 = ADC_CHANEL_SELECT(0);
		_delay_ms(10);
   		ValorADC2 = ADC_CHANEL_SELECT(1);
   		_delay_ms(10);
		
    }
}

// ISR(ADC_vect){
// 	ValorADC = ADCH;
// 	ADCSRA |= (1<<ADIF);
// }

ISR(SPI_STC_vect){
	uint8_t spiValor = SPDR;
	if(spiValor == 99){
		spiWrite(ValorADC1);
	}

 	else if(spiValor == 100){
 		spiWrite(ValorADC2);
 }
}
