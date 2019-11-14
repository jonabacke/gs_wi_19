/**
  ******************************************************************************
  * @file         output.h
  * @praktikum    GSP
  * @semester     SS2019  
  * @author       Johanna Ahlf 2237120, Tobias Hardjowirogo 2387188
  * @Aufgaben-Nr  02
  ******************************************************************************
  */
	
	
	
#ifndef OUTPUT_H
#define OUTPUT_H



/**
 * @brief  Ausgabe auf Display
 * @param  None
 * @return None 
 */
void setDisplay(void);



/**
 * @brief  Gibt die aktuelle Richtung aus
 * @param  None
 * @return None 
 */
void setDirection(void);



/**
 * @brief  Gibt den aktuellen Zaehlerstand aus
 * @param  None
 * @return None 
 */
void setCounter(void);



/**
 * @brief  Rechnet Schritte in Grad um und gibt den Wert aus
 * @param  None
 * @return None 
 */
void setDeg(void);



/**
 * @brief  Gibt den Winkel pro Sekunde aus
 * @param  None
 * @return None 
 */
void getRot(void);



#endif

