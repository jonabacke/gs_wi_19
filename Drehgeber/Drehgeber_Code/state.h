/**
  ******************************************************************************
  * @file         state.h
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */



#ifndef STATE_H
#define STATE_H

#include "general.h"



typedef enum {START = 0, A_P, B_P, C_P, D_P, E_P} State_Type;

extern State_Type curr_state;

uint16_t statetable(int curr_state, uint8_t pulse_state, uint8_t* ptr, int buttonpressed);
uint16_t s_p(uint8_t, uint8_t *, int);// Start-Phase.
uint16_t a_p(uint8_t, uint8_t *, int);// A-Phase-Fkt. 
uint16_t b_p(uint8_t, uint8_t *, int);
uint16_t c_p(uint8_t, uint8_t *, int);
uint16_t d_p(uint8_t, uint8_t *, int);
uint16_t e_p(uint8_t, uint8_t *, int);// Fehler Phase



/**
 * @brief  Setzt den Zaehler auf 0
 * @param  None
 * @return Return 
 */
int resetCounter(void);



/**
 * @brief  Setzt die Error-LED zurueck
 * @param  None
 * @return Return 
 */
int resetError(void);



/**
 * @brief  Liest Kanal A und B aus
 * @param  pulse_state: aktueller Zustand
 * @return Return 
 */
int getState(int* pulse_state);



/**
 * @brief  Gibt die aktuelle Drehrichtung zurueck
 * @param  none
 * @return Return 
 */
uint8_t getDirection(void);



/**
 * @brief  Gibt den aktuellen Zaehlerstand zurueck
 * @param  none
 * @return Return 
 */
int getCount(void);





#endif

