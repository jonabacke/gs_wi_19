/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include "stdint.h"
#include "general.h"
#ifndef expand

#define expand

/**
 * @brief verschiebt die Pointer auf den Anfang der nächsten Zeile
 * @param x x-Position
 * @param y y-Position
 * @param picture8Bit Picture das modifiziert werden soll
 * */
uint8_t endOfLine(int32_t * x, int32_t * y, struct tagBitMap8Bit *picture8Bit);

/**
 * @brief setzt den Bool für das BitmapEnde auf false(0);
 * @param isNotFinished bool für ende BitMap
 * */
uint8_t endOfBitmap(int8_t*);

/**
 * @brief verschiebt die Pointer um xMove nach rechts und yMove nach oben
 * @param x x-Pointer
 * @param y y-Pointer
 * @param xMove die anzahl um die es nach rechts verschoben werden soll
 * @param yMove die anzahl um die es nach oben verschoben werden soll
 * */
uint8_t deltaMove(int32_t * x, int32_t * y, int32_t xMove, int32_t yMove);

/**
 * @brief im absolutModus werden die felder wie sie kommen beschrieben. Die Anzahl muss dabei durch 2 Teilbar sein sonst muss mit 0 aufgefüllt werden
 * @param x x-Pointer
 * @param y y-Pointer
 * @param buffer buffer aus dem die WErte gelesen werden
 * @param picture Bild in das WErte geschrieben werden sollen
 * @param width Breite des Bildes
 * @param bufferPointer pointer für den Buffer
 * */
uint8_t absoluteMode(int32_t * x, int32_t * y, uint8_t* buffer, struct tagBitMap8Bit* picture, int32_t width, int32_t * bufferPointer);

/**
 * @brief hier werden gleiche werte in das Bild geschrieben 
 * @param x x-Pointer
 * @param y y-Pointer
 * @param amount anzahl Werte
 * @param value Wert
 * @param picture Datei in die geschrieben werden soll
 * @param width breite des bildes
 * */
uint8_t writeInPixelBuffer(int32_t * x, int32_t * y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, int32_t width);

#endif
