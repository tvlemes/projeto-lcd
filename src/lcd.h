#include <TFT_eSPI.h>

#ifndef LCD
#define LCD

extern TFT_eSPI tft;

// Variáveis globais do menu
extern bool itemSelected;
extern const char* menuLabels[]; // Declaração de menuLabels
extern int currentItem;          // Declaração de currentItem

void init_lcd();
void board();
void drawMenu(int NUM_ITEMS);
void about();
void tp();
void hd();

#endif
