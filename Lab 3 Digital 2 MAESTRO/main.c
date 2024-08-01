/*
 * Lab 3 Digital 2 MAESTRO.c
 *
 * Created: 26/07/2024 07:25:37 a. m.
 * Author : josei
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "SPI/SPI.h"
#include "UART/UART.h"
#include <stdio.h> // Incluir para usar sprintf


char lista[] = {'0','1','2','3','4','5','6','7','8','9'}; //Lista de numeros a mostrar

uint16_t ValorSPI = 0;
volatile uint8_t estado = 0;
volatile uint8_t opcion;
volatile uint8_t caracter =0;

int centenas1 = 0;
int decenas1 = 0;
int unidades1 = 0;
int centenas2 = 0;
int decenas2 = 0;
int unidades2 = 0;

void RefreshPort(uint8_t valor);
void menu(void);
float map0(float duty, float Imin, float Imax, float Omin, float Omax);

int main(void)
{
	//LEDS
	//UCSR0B = 0;	//ACTIVAR RX Y TX COMO PINES NORMALES
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	PORTD &= ~((1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD5)|(1<<PORTD6)|(1<<PORTD7));
	DDRB |= (1<<DDB0)|(1<<DDB1);
	PORTB &= ~((1<<PORTB0)|(1<<PORTB1));
	InitSPI(SPI_MASTER_OSC_DIV16, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	initUART9600();
	
	sei();
	//menu();
    while (1) 
    {
		PORTB &= ~(1<<PORTB2);	//SLAVE SELECT
		//RefreshPort(ValorSPI);
		_delay_ms(250);
//  		PORTB |= (1<<PORTB2);	//SLAVE SELECT
// 		 _delay_ms(250);
 		
		
    }
}

// void menu(void){
// 	writeTextUART("---------------------------------------");
// 	writeUART(10);
// 	writeUART(13);
// 	writeTextUART("Eliga una opcion:");
// 	writeUART(10);
// 	writeUART(13);
// 	writeUART(10);
// 	writeUART(13);
// 	writeTextUART("1. Leer Potenciometro");	//31 es 1 en Hexadecimal según ANSII
// 	writeUART(10);
// 	writeUART(13);
// 	writeUART(10);
// 	writeUART(13);
// 	writeTextUART("2. Enviar Ascii");		//32 es 2 en Hexadecimal según ANSII
// 	//writeUART('B');
// 	writeUART(10);
// 	writeUART(13);
// 	writeUART(1);
// }

float map0(float duty, float Imin, float Imax, float Omin, float Omax){
	return ((duty - Imin)*(Omax - Omin)/(Imax - Imin)) + Omin;
}

void comprobarque(char opcion){
		//PRIMERA PARTE
		
			if (caracter==0){
				if (opcion == 114){			//OPCION ES 'r'
					PORTD &= ~(1<<PORTD2);
					caracter++;
				}
				else if (opcion == 115){		//OPCION ES 's'
					PORTD |= (1<<PORTD2);
					caracter++;
				}
			}
			else if (caracter==1){
				if (opcion == 114){			//OPCION ES 'r'
					PORTD &= ~(1<<PORTD3);
					caracter++;
				}
				else if (opcion == 115){	//OPCION ES 's'
					PORTD |= (1<<PORTD3);
					caracter++;
				}
			}
			else if (caracter==2){
				if (opcion == 114){
					PORTD &= ~(1<<PORTD4);
					caracter++;
				}
				else if (opcion == 115){
					PORTD |= (1<<PORTD4);
					caracter++;
				}
			}
			else if (caracter==3){
				if (opcion == 114){
					PORTD &= ~(1<<PORTD5);
					caracter++;
				}
				else if (opcion == 115){
					PORTD |= (1<<PORTD5);
					caracter++;
				}
			}
			else if (caracter==4){
				if (opcion == 114){
					PORTD &= ~(1<<PORTD6);
					caracter++;
				}
				else if (opcion == 115){
					PORTD |= (1<<PORTD6);
					caracter++;
				}
			}
			else if (caracter==5){
				if (opcion == 114){
					PORTD &= ~(1<<PORTD7);
					caracter++;
				}
				else if (opcion == 115){
					PORTD |= (1<<PORTD7);
					caracter++;
				}
			}
			else if (caracter==6){
				if (opcion ==114){
					PORTB &= ~(1<<PORTB0);
					caracter++;
				}
				else if (opcion == 115){
					PORTB |= (1<<PORTB0);
					caracter++;
				}
			}
			else if (caracter==7){
				if (opcion == 114){
					PORTB &= ~(1<<PORTB1);
					caracter=0;
					estado=0;
				}
				else if (opcion == 115){
					PORTB |= (1<<PORTB1);
					caracter=0;
					estado=0;
				}
			}
		
		
		//SEGUNDA PARTE

 		if(opcion == 116){	//OPCION ES 't'
 		spiWrite('c');
 		ValorSPI = spiRead();
 		//ValorSPI = map0(ValorSPI, 0, 255, 0, 500);
  		
		// Enviar el valor como cadena de texto
		int centenas1 = (ValorSPI/100)*100;
		int decenas1 = ((ValorSPI/10)% 10)*10;
		int unidades1 = ValorSPI% 10;	
		ValorSPI = centenas1+decenas1+unidades1;	
//		writeUART(lista[centenas1]);
//		writeUART('.');
//   		writeUART(lista[decenas1]);
//   		writeUART(lista[unidades1]);
// 		   decenas1 = lista[decenas1];
// 		   unidades1 = lista[unidades1];
		if (ValorSPI <= 255){
 			if (ValorSPI == 0){
 				writeUART('0');
			}else if (ValorSPI >= 0 && ValorSPI < 10){
				writeUART('a');
			}else if(ValorSPI >= 10 && ValorSPI < 20){
				writeUART('b');
			}else if(ValorSPI >= 20 && ValorSPI < 30){
				writeUART('c');
			}else if(ValorSPI >= 30 && ValorSPI < 40){
				writeUART('d');
			}else if(ValorSPI >= 40 && ValorSPI < 50){
				writeUART('e');
			}else if(ValorSPI >= 50 && ValorSPI < 60){
				writeUART('f');
			}else if(ValorSPI >= 60 && ValorSPI < 70){
				writeUART('g');
			}else if(ValorSPI >= 70 && ValorSPI < 80){
				writeUART('h');
			}else if(ValorSPI >= 80 && ValorSPI < 90){
				writeUART('i');
			}else if(ValorSPI >= 90 && ValorSPI < 100){
				writeUART('j');
			}else if(ValorSPI >= 100 && ValorSPI < 110){
				writeUART('k');
			}else if(ValorSPI >= 110 && ValorSPI < 120){
				writeUART('l');
			}else if(ValorSPI >= 120 && ValorSPI < 130){
				writeUART('m');
			}else if(ValorSPI >= 130 && ValorSPI < 140){
				writeUART('n');
			}else if(ValorSPI >= 140 && ValorSPI < 150){
				writeUART('o');
			}else if(ValorSPI >= 150 && ValorSPI < 160){
				writeUART('p');
			}else if(ValorSPI >= 160 && ValorSPI < 170){
				writeUART('q');
			}else if(ValorSPI >= 170 && ValorSPI < 180){
				writeUART('1');
			}else if(ValorSPI >= 180 && ValorSPI < 190){
				writeUART('2');
			}else if(ValorSPI >= 190 && ValorSPI < 200){
				writeUART('3');
			}else if(ValorSPI >= 200 && ValorSPI < 210){
				writeUART('4');
			}else if(ValorSPI >= 210 && ValorSPI < 220){
				writeUART('5');
			}else if(ValorSPI >= 220 && ValorSPI < 230){
				writeUART('6');
			}else if(ValorSPI >= 230 && ValorSPI < 240){
				writeUART('7');
			}else if(ValorSPI >= 240 && ValorSPI < 250){
				writeUART('8');
			}else if(ValorSPI >= 250){
				writeUART('9');}
			}
			
			else if(opcion == 117){	//OPCION ES 'u'
				spiWrite('d');
				ValorSPI = spiRead();
				//ValorSPI = map0(ValorSPI, 0, 255, 0, 500);
				
				// Enviar el valor como cadena de texto
				int centenas2 = (ValorSPI/100)*100;
				int decenas2 = ((ValorSPI/10)% 10)*10;
				int unidades2 = ValorSPI% 10;
				ValorSPI = centenas2+decenas2+unidades2;
				//		writeUART(lista[centenas1]);
				//		writeUART('.');
				//   		writeUART(lista[decenas1]);
				//   		writeUART(lista[unidades1]);
				// 		   decenas1 = lista[decenas1];
				// 		   unidades1 = lista[unidades1];
				if (ValorSPI <= 255){
					if (ValorSPI == 0){
					writeUART('A');
					}else if (ValorSPI >= 0 && ValorSPI < 10){
					writeUART('B');
					}else if(ValorSPI >= 10 && ValorSPI < 20){
					writeUART('C');
					}else if(ValorSPI >= 20 && ValorSPI < 30){
					writeUART('D');
					}else if(ValorSPI >= 30 && ValorSPI < 40){
					writeUART('E');
					}else if(ValorSPI >= 40 && ValorSPI < 50){
					writeUART('F');
					}else if(ValorSPI >= 50 && ValorSPI < 60){
					writeUART('G');
					}else if(ValorSPI >= 60 && ValorSPI < 70){
					writeUART('H');
					}else if(ValorSPI >= 70 && ValorSPI < 80){
					writeUART('I');
					}else if(ValorSPI >= 80 && ValorSPI < 90){
					writeUART('J');
					}else if(ValorSPI >= 90 && ValorSPI < 100){
					writeUART('K');
					}else if(ValorSPI >= 100 && ValorSPI < 110){
					writeUART('L');
					}else if(ValorSPI >= 110 && ValorSPI < 120){
					writeUART('M');
					}else if(ValorSPI >= 120 && ValorSPI < 130){
					writeUART('N');
					}else if(ValorSPI >= 130 && ValorSPI < 140){
					writeUART('O');
					}else if(ValorSPI >= 140 && ValorSPI < 150){
					writeUART('P');
					}else if(ValorSPI >= 150 && ValorSPI < 160){
					writeUART('Q');
					}else if(ValorSPI >= 160 && ValorSPI < 170){
					writeUART('R');
					}else if(ValorSPI >= 170 && ValorSPI < 180){
					writeUART('S');
					}else if(ValorSPI >= 180 && ValorSPI < 190){
					writeUART('T');
					}else if(ValorSPI >= 190 && ValorSPI < 200){
					writeUART('U');
					}else if(ValorSPI >= 200 && ValorSPI < 210){
					writeUART('V');
					}else if(ValorSPI >= 210 && ValorSPI < 220){
					writeUART('W');
					}else if(ValorSPI >= 220 && ValorSPI < 230){
					writeUART('X');
					}else if(ValorSPI >= 230 && ValorSPI < 240){
					writeUART('Y');
					}else if(ValorSPI >= 240 && ValorSPI < 250){
					writeUART('Z');
					}else if(ValorSPI >= 250){
					writeUART('.');}
					}
					}
		}
}

ISR(USART_RX_vect){
	
	//bufferTX = UDR0;
	//while(!(UCSR0A & (1<<UDRE0)));
	//UDR0 = bufferTX;
	
	opcion = UDR0;
	//UARTCHANEL(valorUART);
	comprobarque(opcion);
	
// 	writeUART(10);
// 	writeUART(13);
}

