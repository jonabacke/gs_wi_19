/**
  ******************************************************************************
  * @file         gpio.h
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */



#ifndef GPIO_H
#define GPIO_H



/**
 * @brief  Schaltet LED ein
 * @param  pin: Pin wird auf low gesetzt
 * @return Return 
 */
int setLED(int pin);



/**
 * @brief  Schaltet LED aus
 * @param  pin: Pin wird auf high gesetzt
 * @return Return 
 */
int clearLED(int pin);



/**
 * @brief  Liest Pin aus
 * @param  input: off oder on
 * @param  pin: Pin der ausgelesen wird
 * @return Return 
 */
int readPin(int* input, int pin);



/**
* @brief 	Gibt den aktuellen Zaehlerstand binaer codiert 
*					(nur die unteren 8 Bit) auf den LEDS D21 bis D28 aus
*
* @param Der aktuelle Zaehlerstand
*
* @return Return
*/ 
int setCounterLED(int);



#endif


