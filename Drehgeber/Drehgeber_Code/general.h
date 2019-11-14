/**
  ******************************************************************************
  * @file         general.h
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */

#ifndef GENERAL_H
#define GENERAL_H
  
#include <stdint.h>

typedef uint8_t CHAR;
typedef uint16_t SHORT;

#define OFF 				1
#define ON					0 

//Definitionen für IO Ports
#define PE0					0
#define PE1					1

#define BUTTON_PORT		GPIOE
#define BUTTON_S6			6
#define BUTTON_S7			7

#define LED_PORT			GPIOG
#define LED_D17				17
#define LED_D18				18
#define LED_D19				19
#define LED_D20				20
#define LED_D21				21
#define LED_D22				22
#define LED_D23				23
#define LED_D24				24
#define LED_D25				25
#define LED_D26				26
#define LED_D27				27
#define LED_D28				28

#define FALSE_PIN			-1
#define ERROR_STATE		-2

#endif
