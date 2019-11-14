/**
  ******************************************************************************
  * @file         state.c
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */
	
	
	
#include <stdint.h>
#include <errno.h>
#include "tft.h"
#include "state.h"
#include "general.h"
#include "gpio.h"
#include "output.h"



State_Type curr_state;
int count = 0;
uint8_t dir = 0;



uint16_t (*state_table[])(uint8_t pulse_state, uint8_t *ptr, int buttonpressed) = {s_p, a_p, b_p, c_p, d_p, e_p};

uint16_t statetable(int curr_state, uint8_t pulse_state, uint8_t* ptr, int buttonpressed) {
	return state_table[curr_state](pulse_state, ptr, buttonpressed);
}



//??????
uint16_t s_p(uint8_t pulse_state, uint8_t *ptr, int buttonpressed) {
	switch(pulse_state) {
		case 1: 
			curr_state = A_P; 
			count = 0; 
			dir = 0; 
			break;
		case 2: 
			curr_state = B_P; 
			count = 0; 
			dir = 0; 
			break;
		case 3: 
			curr_state = C_P; 
			count = 0; 
			dir = 0; 
			break;
		case 4: 
			curr_state = D_P; 
			count = 0; 
			dir = 0; 
			break;
		default: ;
	}
	*ptr = dir;
	return count;
}



uint16_t a_p(uint8_t pulse_state, uint8_t *ptr, int buttonpressed) {
	switch(pulse_state) {
		case 4:
			curr_state = D_P;
			count--;
			dir = 2;
			clearLED(LED_D20);
			setLED(LED_D19);
			break;
		case 3:
			curr_state = E_P;
			dir = 0;
			setLED(LED_D18);
			errno = ERROR_STATE;
			return count;
		case 1:
			curr_state = A_P;
			dir = 0;
			break;
		case 2:
			curr_state = B_P;
			count ++;
			dir = 3;
			clearLED(LED_D19);
			setLED(LED_D20);
			break;
		default: curr_state = START;
	}
	*ptr = dir;
	return count;
}



uint16_t b_p(uint8_t pulse_state, uint8_t *ptr, int buttonpressed){
//logic for curr_state update depends on pulse_state
	switch(pulse_state){
		case 1:
			curr_state = A_P;
			count--;
			dir = 2;
			clearLED(LED_D20);
			setLED(LED_D19);
			break; //RW
		case 4:
			curr_state = E_P;
			dir = 0;
			setLED(LED_D18);
			errno = ERROR_STATE;
			return count;	// ND
		case 2:
			curr_state = B_P;
			dir = 0;
			break; // ND
		case 3:
			curr_state = C_P;
			count++;
			dir = 3;
			clearLED(LED_D19);
			setLED(LED_D20);
			break; //VW
		default: curr_state = START;// falsche Kodierung
	}
	// direction update
	*ptr = dir;
	return count;
}



uint16_t c_p(uint8_t pulse_state, uint8_t *ptr, int buttonpressed){
	switch(pulse_state){
		case 2:
			curr_state = B_P;
			count--;
			dir = 2;
			clearLED(LED_D20);
			setLED(LED_D19);
			break; //RW
		case 1:
			curr_state = E_P;
			dir = 0;
			setLED(LED_D18);
			errno = ERROR_STATE;
			return count;	// ND
		case 3:
			curr_state = C_P;
			dir = 0;
			break; // ND
		case 4:
			curr_state = D_P;
			count++;
			dir = 3;
			clearLED(LED_D19);
			setLED(LED_D20);
			break; //VW
		default: curr_state = START; // falsche Kodierung
	}
	// direction update
	*ptr = dir;
	return count;
}



uint16_t d_p(uint8_t pulse_state, uint8_t *ptr, int buttonpressed){
	switch(pulse_state){
		case 3:
			curr_state = C_P;
			count--;
			dir = 2;
			clearLED(LED_D20);
			setLED(LED_D19);
			break; //RW
		case 2:
			curr_state = E_P;
			dir = 0;
			setLED(LED_D18);
			errno = ERROR_STATE;
			return count;	// ND
		case 4:
			curr_state = D_P;
			dir = 0;
			break; // ND
		case 1:
			curr_state = A_P;
			count++;
			dir = 3;
			clearLED(LED_D19);
			setLED(LED_D20);
			break; //VW
		default: curr_state = START;// falsche Kodierung
	}
	// direction update
	*ptr = dir;
	return count;
}



//?????
uint16_t e_p(uint8_t pulse_state, uint8_t *ptr, int buttonpressed) {
	
	int bp = buttonpressed;
	
	if (bp == 1){
		curr_state = START;}
	else{
		curr_state = E_P;}
		
	return 0;
}





/**
 * @brief  Setzt den Zaehler auf 0
 * @param  None
 * @return Return 
 */
int resetCounter(void) {

		count = 0;
		TFT_gotoxy(22,5);
		TFT_puts("          ");
	
		return 0;
}



/**
 * @brief  Setzt die Error-LED zurueck
 * @param  None
 * @return Return 
 */
int resetError(void){
	
	clearLED(LED_D18);
	
	return 0;
}



/**
 * @brief  Liest Kanal A und B aus
 * @param  pulse_state: aktueller Zustand
 * @return Return 
 */
int getState(int* pulse_state) {
	int kanalA = 0;
	int kanalB = 0;
	readPin(&kanalA, PE1);
	readPin(&kanalB, PE0);
	
	if (kanalA) {
		if (kanalB) {
			*pulse_state = C_P;
		} 
		else {
			*pulse_state = B_P;
		}
	} 
	else {
		if (kanalB) {
			*pulse_state = D_P;
		} 
		else {
			*pulse_state = A_P;
		}
	}
	return 0;
}



/**
 * @brief  Gibt die aktuelle Drehrichtung zurueck
 * @param  none
 * @return aktuelle Drehrichtung 
 */
uint8_t getDirection(void){
	return dir;
}



/**
 * @brief  Gibt den aktuellen Zaehlerstand zurueck
 * @param  none
 * @return aktueller Zaehlerstand 
 */
int getCount(void){
	return count;
}




