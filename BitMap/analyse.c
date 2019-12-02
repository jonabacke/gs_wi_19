/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



// Includes
#include "analyse.h"
#include "general.h"
#include "stdio.h"


// Globale Variablen
static int32_t width;
static int32_t height;



/*
* Untersucht die Bilddatei auf Rechtecke und ermittelt Anzahl, Farbe und Eckpunktkoordinaten der gefundenen Rechtecke.
* Daraus wird außerdem das Volumen errechnet.
* Rechtecke muessen ausgefuellt und bunt und duerfen nicht weiss sein, da der Hintergrund bereits weiss ist. Ausserdem muessen
* die Eckpunkte, sowie die Kanten klar definiert sein, also sich in der Farbe von der Umgebung unterscheiden.
* 
* @param struct tagBitMap8Bit *picture8Bit	Pointer auf BildStruct
*/
int32_t getRect8Bit(struct tagBitMap8Bit *picture8Bit) {
    // Initialisieren der Rechteck-Liste
	struct tagRectListElement *listHead = NULL;
	// Reservieren von Heap-Speicher fuer die Rechteck-Liste
    listHead = (struct tagRectListElement*) malloc(sizeof(struct tagRectListElement));
		// Fehlerbehandlung
		if (NULL == listHead) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}
    struct tagRectListElement *listPointer = NULL;
    listHead -> next = NULL;

    int32_t amount = 0;
    width = 0;
    height = 0;
    uint8_t color = 0;

    width = picture8Bit -> infoHeader.biWidth;
    height = picture8Bit -> infoHeader.biHeight;
	
	// Das Bild-Struct wird systematisch pixelweise auf Rechtecke untersucht
    for (int32_t y = 0; y < height - 1; y++) {
        for (int32_t x = 0; x < width - 1; x++) {
			// Pointer schon in einem gefundenen Rechteck?
            if (!isInRect(listHead, &x, y)) {
                color = picture8Bit -> pixel[y][x];
				// Pruefen der Farbwerte der angrenzenden Pixel
                if (picture8Bit -> pixel[y][x + 1] == color &&
                    picture8Bit -> pixel[y + 1][x] == color &&
                    picture8Bit -> pixel[y + 1][x + 1] == color) {
                    listPointer = listHead;
                    while (listPointer -> next != NULL) {
                        listPointer = listPointer -> next;
                    }
					// neues Rechteck anlegen
                    listPointer -> next = makeNewRect(picture8Bit, x, y);
                    if (listPointer -> next != NULL) {
                        amount++;
                    }
                }
            }
        }
    }
    printf("bgClr: %d \n", picture8Bit -> pixel[0][0]);
    printf(" Anzahl: %d \n", amount);
    listPointer = listHead;
    while (listPointer->next != NULL) {
        listPointer = listPointer -> next;
        printf("untenRechts: (%d, %d)\t untenLinks: (%d, %d)\t obenRechts: (%d, %d)\t obenlinks: (%d, %d)\t color: %d \t volumen: %d \n", 
        listPointer -> rect -> position -> topRight[0], listPointer -> rect -> position -> topRight[1], listPointer -> rect -> position -> topLeft[0],
        listPointer -> rect -> position -> topLeft[1],  listPointer -> rect -> position -> btmRight[0], listPointer -> rect -> position -> btmRight[1],
        listPointer -> rect -> position -> btmLeft[0],  listPointer -> rect -> position -> btmLeft[1],  listPointer -> rect -> color, listPointer -> rect -> volume);
    }
    colorGreenRectToBlue(picture8Bit);

    return amount;
}

int8_t static isInRect(struct tagRectListElement *listHead, int32_t *x, int32_t y) {
    struct tagRectListElement *listPointer = listHead;
    while (listPointer -> next != NULL) {
        listPointer = listPointer -> next;
        if (*x >= listPointer -> rect -> position -> topLeft[0] && *x <= listPointer -> rect -> position -> topRight[0] &&  //check if in rect left-right
            y >=  listPointer -> rect -> position -> topRight[1] && y <= listPointer -> rect -> position -> btmRight[1]) {   //check if in rect top-bottom
            *x =  listPointer -> rect -> position -> topRight[0];                                                      //move x to the right
            return 1;
        }
    }
    return 0;
}

struct tagRectListElement* makeNewRect(struct tagBitMap8Bit *picture8Bit, int32_t x, int32_t y) {
    struct tagRectListElement *listElement;
	// Reservieren von Heap-Speicher fuer die Rechteck-Liste
    listElement = (struct tagRectListElement*) malloc(sizeof(struct tagRectListElement));
		// Fehlerbehandlung
		if (NULL == listElement) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}
	// Reservieren von Heap-Speicher fuer die Elemente der Rechteck-Liste
    listElement -> rect = (struct tagRect*) malloc(sizeof(struct tagRect));
		// Fehlerbehandlung
		if (NULL == listElement -> rect) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}
	// Reservieren von Heap-Speicher fuer die Positionsdaten der Rechtecke	
    listElement -> rect -> position = (struct tagPosition*) malloc(sizeof(struct tagPosition));
		// Fehlerbehandlung
		if (NULL == listElement -> rect -> position) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}
    listElement -> rect -> position -> btmLeft[1] = 0;
    listElement -> rect -> position -> btmLeft[0] = 0;
    listElement -> rect -> position -> topLeft[0] = 0;
    listElement -> rect -> position -> topLeft[1] = 0;
    listElement -> rect -> position -> btmRight[0] = 0;
    listElement -> rect -> position -> btmRight[1] = 0;
    listElement -> rect -> position -> topRight[0] = 0;
    listElement -> rect -> position -> topRight[1] = 0;
    listElement -> rect -> color = 0;
    listElement -> rect -> volume = 0;
    int32_t rectWidth = width - 1; 
    int32_t rectHeight = height - 1; 
    uint8_t color = picture8Bit -> pixel[y][x];

    for (int32_t i = y; i < rectHeight; i++) {
        for (int32_t j = x; j < rectWidth; j++) {

            if (color != picture8Bit -> pixel[i][j] && i == y) {
                // i==y erste Zeile checken um die Breite herauszufinden
                rectWidth = j - 1;
            } 
			else if (color != picture8Bit -> pixel[i][j]) {
                rectHeight = i - 1;
            }
        }
    }
    if (isRect(x, y, rectHeight, rectWidth, picture8Bit)) {
        listElement -> rect -> position -> topLeft[0] = x;
        listElement -> rect -> position -> topLeft[1] = y;
        listElement -> rect -> position -> topRight[0] = rectWidth;
        listElement -> rect -> position -> topRight[1] = y;
        listElement -> rect -> position -> btmLeft[0] = x;
        listElement -> rect -> position -> btmLeft[1] = rectHeight;
        listElement -> rect -> position -> btmRight[0] = rectWidth;
        listElement -> rect -> position -> btmRight[1] = rectHeight;
        listElement -> rect -> volume = (rectHeight - y + 1) * (rectWidth - x + 1);
        listElement -> rect -> color = color;
        listElement -> next = NULL;
        return listElement;
    }
	// Kein Rechteck --> Heap-Speicher wieder freigeben
    else {
        free(listElement -> rect -> position);
        free(listElement -> rect);
        free(listElement);
        return NULL;
    }
}

uint8_t static isRect(int32_t x, int32_t y, int32_t rectHeight, int32_t rectWidth, struct tagBitMap8Bit *picture8Bit) {
    uint8_t color = picture8Bit -> pixel[y][x];

    /*
    *   testen ob Rechteck weiss ist
    */
    if (picture8Bit -> rgbPalette[picture8Bit -> pixel[y][x]].rgbBlue == 0xff &&
		picture8Bit -> rgbPalette[picture8Bit -> pixel[y][x]].rgbGreen == 0xff &&
		picture8Bit -> rgbPalette[picture8Bit -> pixel[y][x]].rgbRed == 0xff) {
			return 0;
    }
    for (int32_t i = y; i <= rectHeight; i++) {
		// linke Seite testen --> muss Seite nicht testen falls am linken BildRand
        if (x > 0) {
            if (picture8Bit -> pixel[i][x - 1] == color) {
                return 0;
            }
        }
		//rechte Seite testen -- muss Seite nicht testen falls am rechten Rand
        if ((rectWidth + 1 < width)) {
            if (picture8Bit -> pixel[i][rectWidth + 1] == color) {
                return 0;
            }    
        }
    }

    for (int32_t i = x; i < rectWidth; i++) {
		// untere Seite Testen --> nicht testen falls unterer BildRand
        if (y > 0) {
            if (picture8Bit->pixel[y - 1][i] == color) {
                return 0;
            }
        }
		// untere Seite testen --> nicht testen falls unterer Rand
        if ((rectHeight + 1 < height)) {
            if (picture8Bit->pixel[rectHeight + 1][i] == color) {
                return 0;
            }         
        }
    }
    return 1;
}

uint8_t colorGreenRectToBlue(struct tagBitMap8Bit *picture8Bit)
{
    for (size_t i = 0; i < 256; i++)
    {
        if (picture8Bit -> rgbPalette[i].rgbBlue == 0x00 &&
            picture8Bit -> rgbPalette[i].rgbGreen == 0xff &&
            picture8Bit -> rgbPalette[i].rgbRed == 0x00) {
				perror("found");
				picture8Bit -> rgbPalette[i].rgbBlue = 0xff;
				picture8Bit -> rgbPalette[i].rgbGreen = 0x00;
        }      
    }   
}



// int32_t getRect24Bit(struct tagBitMap24Bit *picture24Bit)
// {
//     struct tagRectListElement *listHead = NULL;
//     listHead = (struct tagRectListElement*) malloc(sizeof(struct tagRectListElement));
//     struct tagRectListElement *listPointer = NULL;

//     listHead->next = NULL;

//     int32_t amount = 0;
//     width = 0;
//     height = 0;
//     uint32_t color = 0;

//     width = picture24Bit->infoHeader.biWidth;
//     height = picture24Bit->infoHeader.biHeight;

//     for (int32_t y = 0; y < height - 1; y++)
//     {
//         for (int32_t x = 0; x < width - 1; x++)
//         {
//             //if (!isInRect(listHead, &x, y))
//             {
//                 color = picture24Bit->pixel[y]->rgbBlue << 16 | picture24Bit->pixel[y]->rgbGreen << 8 | picture24Bit->pixel[y]->rgbRed;

//                 if (picture24Bit->pixel[y] + 3 == color &&
//                     picture24Bit->pixel[y + 1] == color &&
//                     picture24Bit->pixel[y + 1] + 3 == color) {
//                     listPointer = listHead;
//                     while (listPointer->next != NULL) {
//                         listPointer = listPointer->next;
//                     }
//                     listPointer->next = makeNewRect(picture24Bit, x, y);
//                     if (listPointer->next != NULL)
//                     {
//                         amount++;
//                     }
//                     //printf(" amount: %d \n", amount);
//                 }
//             }
            
//         }
        
//     }

//     printf("%x %x \n", picture24Bit->pixel[0]->rgbBlue, picture24Bit->pixel[0]->rgbBlue + 3);
    
// }