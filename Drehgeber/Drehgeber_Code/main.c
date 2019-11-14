/**
  ******************************************************************************
  * @file         main.c
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
	* @brief   			Main program body
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "TI_Lib.h"
#include "tft.h"
#include "timer.h"
#include "state.h"
#include "output.h"
#include "gpio.h"


//--- For GPIOs -----------------------------
//Include instead of "stm32f4xx.h" for
//compatibility between Simulation and Board
#include "TI_memory_map.h"

//--- For Touch Keypad ----------------------
//#include "keypad.h"

//--- For Timer -----------------------------
//#include "timer.c"

/**
  * @brief  Main program
  * @param  None
  */
int main(void){	
	Init_TI_Board();
	timerinit();
	setDisplay();
	
	
	while (1) {
		uint8_t* ptr_dir;
		int dg_state;
		int buttonpressed = 0;
		
		//S6 gedrueckt -> reset error
		int input;
		readPin(&input, BUTTON_S6);
		if (input){
			buttonpressed = 1;
			resetError();
		}
		
		//S7 gedrueckt -> reset Counter
		int input2;
		readPin(&input2, BUTTON_S7);
		if (input2){
			resetCounter();
			
		}
		
		getState(&dg_state);
		//pulse_count = state_table[curr_state](dg_state, ptr_dir);
		uint16_t pulse_count = statetable(curr_state, dg_state, ptr_dir, buttonpressed);
		
		///////// LED-Ansteuerung hier?
		///////// Timer für Winkelberechnung #include "timer.h" getTimeStamp();
		//Ausgabe
		Delay(2);
		
		setLED(LED_D17);
		setDirection();
		setCounter();	
		setDeg();
		if((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF){ //wenn overflow im sr
			getRot();
			TIM2->SR = 0;
		}
		
		clearLED(LED_D17);
	}
}
// EOF


