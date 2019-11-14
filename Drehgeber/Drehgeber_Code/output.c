/**
  ******************************************************************************
  * @file         output.c
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */
	
	
	
#include <stdio.h>

#include "tft.h"
#include "TI_Lib.h"
#include "timer.h"
#include "output.h"
#include "state.h"
#include "gpio.h"
//#include "timer.c"

uint32_t lastTime = 0;
uint32_t currTime = 0;
int deg = 0;							//	float deg = counter / (1200/360);
int letzterWinkel = 0;


/**
 * @brief  Ausgabe auf Display
 * @param  None
 * @return None 
 */
void setDisplay(void){
	TFT_cursor_off();
	TFT_set_window(0,1,1,50,30);
	TFT_gotoxy(1,3);
	TFT_puts("Richtung: ");
	TFT_gotoxy(1,5);
	TFT_puts("Anzahl der Schritte: ");
	TFT_gotoxy(1,7);
	TFT_puts("Drehgeschwindigkeit in Grad/Sek.: ");
	TFT_gotoxy(1,11);
	TFT_puts("Winkel in Grad: ");
}



/**
 * @brief  Gibt die aktuelle Richtung aus
 * @param  None
 * @return None 
 */
void setDirection(void){
	// aktuellen Richtungswert aus state abrufen
	uint8_t dir = getDirection();
	
	if(dir == 2){
		TFT_gotoxy(11,3);
		TFT_puts("             ");
		TFT_gotoxy(11,3);
		TFT_puts("rueckwaerts");
	}
	else if(dir == 3){
		TFT_gotoxy(11,3);
		TFT_puts("             ");
		TFT_gotoxy(11,3);
		TFT_puts("vorwaerts");
	}
}



/**
 * @brief  Gibt den aktuellen Zaehlerstand aus
 * @param  None
 * @return None 
 */
void setCounter(void){
	// aktuellen Zaehlerstand aus state abrufen
	int counter = getCount();
	
	// gibt den Zaehlerstand zur binaeren codierung und Ausgabe weiter
	setCounterLED(counter);
	
	char txt[10];
	sprintf(txt, "%d", counter);
	
	TFT_gotoxy(22,5);
	TFT_puts("          ");
	
	TFT_gotoxy(22,5);
	TFT_puts(txt);
}



/**
 * @brief  Rechnet Schritte in Grad um und gibt den Wert aus
 * @param  None
 * @return None 
 */
void setDeg(void){
	int counter = getCount();
	// Umrechnung Schritte --> Grad
	deg = counter * 3;			//3600 Grad / 1200 = 0,3 (je 300 counts pro Phase)

	char txt[10];
	sprintf(txt, "%d.%d", deg/10, deg%10);
	
	TFT_gotoxy(17,11);
	TFT_puts(txt);
}



/**
 * @brief  Gibt den Winkel pro Sekunde aus
 * @param  None
 * @return None 
 */
void getRot(void){
	
	int counter = getCount();
	// keine negativen Schritte
	if(counter < 0){
		counter = counter * (-1);
	}
		
	int aktuellerWinkel = deg;
	
	int rot = aktuellerWinkel - letzterWinkel; //aktueller Winkel/Sek.
	
	char txt[10];
	sprintf(txt, "%d.%d", rot/10, rot%10);
	TFT_gotoxy(1,8);
	TFT_puts("          ");
	
	TFT_gotoxy(1,8);
	TFT_puts(txt);
	
	letzterWinkel = aktuellerWinkel;
}

