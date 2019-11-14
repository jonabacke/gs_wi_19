/**
  ******************************************************************************
  * @file         gpio.c
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */
#include <errno.h>

#include "TI_memory_map.h"	//Zugriff auf Hardware
#include "gpio.h"
#include "general.h"



/**
 * @brief  Schaltet LED ein
 * @param  pin: Pin wird auf low gesetzt
 * @return Return 
 */
int setLED(int pin) {
	if ((pin < 18) || (pin > 28)) {
		errno = FALSE_PIN;
		return -1;
	} 
	else {
		LED_PORT->BSRRL = 0x01 << (pin - 13);
	}
	return 0;
}



/**
 * @brief  Schaltet LED aus
 * @param  pin: Pin wird auf high gesetzt
 * @return Return 
 */
int clearLED(int pin) {
	if ((pin < 18) || (pin > 28)) {
		errno = FALSE_PIN;
		return -1;
	} 
	else {
		LED_PORT->BSRRH = 0x01 << (pin - 13);
	}
	return 0;
}



/**
 * @brief  Liest Pin aus
 * @param  input: off oder on
 * @param  pin: Pin der ausgelesen wird
 * @return Return 
 */
int readPin(int* input, int pin) {
	int mask = 0x01 << pin;
	
	if( (pin < 0)||(pin > 28)){
		errno = FALSE_PIN;
		return -1;
	} 
	else {
		if(mask != ((GPIOE -> IDR) & mask)){
			*input = OFF;	//1
		}
		else{
			*input = ON;	//0
		}
	}
	return 0;
}




/**
* @brief 	Gibt den aktuellen Zaehlerstand binaer codiert 
*					(nur die unteren 8 Bit) auf den LEDS D21 bis D28 aus
*
* @param Der aktuelle Zaehlerstand
*
* @return Return
*/ 
int setCounterLED(int Value){	
	LED_PORT->ODR = ((0xFF & Value) << 8);	//
	return 0;
}
