#include <TFT_eSPI.h>
#include "utils.h"
#include "lcd.h"

#define BUTTON_BACK 25

// Inicializa display e touch - BÁSICO PARA MOSTRAR IMAGEM
TFT_eSPI tft; // Já foi declarado no lcd.h
 
 /* Variáveis*/
 /* **************************************************************** */

/* Definição dos itens do menu */
const char* menuLabels[] = { "Hora/Data", "Temperatura", "Umidade do Ar", "About" };

/* Variável para controlar o menu */
int currentItem = 0; // Índice do item atual
bool itemSelected = false; // Estado da seleção do menu
  /* **************************************************************** */


/* Função para inicializar o LCD */
/* **************************************************************** */
void init_lcd(){

    /* CONFIGURAÇÕES BIBLIOTECA LCD */
    /* ************************************************* */
    tft.init();
    tft.setRotation(2); // Rotação do display
    tft.fillScreen(TFT_WHITE); // Cor de fundo do LCD
    // tft.setTextColor(TFT_BLACK, TFT_WHITE); // Cor de fundo da Fonte e cor de Fonte 
    // tft.drawString("Teste de Touch!", 30, 20, 4); // Texto | Linha | Top | Tamanho da Fonte 
    /* ************************************************* */

}
/* **************************************************************** */


/* Função para mostrar o About */
/* **************************************************************** */
void about(){
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_PURPLE, TFT_WHITE);  
  tft.drawString("Dashboard", 40, 15, 4);
  tft.setTextColor(TFT_GREEN, TFT_WHITE);  
  tft.drawString("ESP32", 110, 48, 4);
  tft.drawString("------------------------------------", 0, 72, 4);

  tft.setTextColor(TFT_OLIVE, TFT_WHITE);  
  tft.drawString("Desenvolvido por:", 18, 142, 4);
  tft.setTextColor(TFT_MAGENTA, TFT_WHITE);  
  tft.drawString("Thiago Lemes", 42, 180, 4);


  tft.setTextColor(TFT_BLACK, TFT_WHITE);  
  tft.drawString("V1.0", 100, 285, 4);

  while (true) {
    bool buttonBackState = digitalRead(BUTTON_BACK);
    if (buttonBackState == LOW) {  // Se botão de voltar for pressionado
        delay(100);                // Debounce simples
        break;                     // Sai do loop e volta ao menu
    }
    delay(500); // Reduz a carga do loop
  }
}
/* **************************************************************** */


/* Função para criação do Menu */
/* **************************************************************** */
void drawMenu(int NUM_ITEMS){

  /* Menu */
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_MAROON, TFT_WHITE);
  tft.drawString("Menu", 92, 15, 4);
  tft.drawString("-----------------------------------------", 10, 42, 2);

  /* Itens do Menu*/
  for (int i = 0; i < NUM_ITEMS; i++) {
    if (i == currentItem) {
      // Destaca o item atual
      tft.setTextColor(TFT_GREEN, TFT_WHITE);
    } else {
      // Itens não selecionados
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    }
    // if(menuLabels[i] == "Temperatura"){
    //   tft.drawString(menuLabels[i], 0, 80 + (i * 40), 4); 
    // }
    if(menuLabels[i] == "Umidade do Ar"){
      tft.drawString(menuLabels[i], 45, 80 + (i * 40), 4); 
    }
    else{
      tft.drawString(menuLabels[i], 45, 80 + (i * 40), 4); 
    }
  }
}
/* **************************************************************** */


void board(){

    // Limpa a Tela
    tft.fillScreen(TFT_WHITE);
    
    // Titulo
    tft.setTextColor(TFT_MAROON, TFT_WHITE);
    tft.drawString("Hora/Data", 68, 15, 4);
    tft.drawString("-----------------------------------------", 10, 42, 2);

    // Função para pegar a Data e Hora
    TimeParts tm = timeNow();

    tft.setTextColor(TFT_PURPLE, TFT_WHITE);
    tft.drawString(tm.hour,   90, 80, 6);   // Hora
    tft.drawString("hs",   105, 123, 4);   // Hora

    tft.setTextColor(TFT_PURPLE, TFT_WHITE);
    tft.drawString(tm.minute, 90, 165, 6);   // Minuto
    tft.drawString("min", 95, 210, 4);   // Minuto

    // tft.setTextColor(TFT_PURPLE, TFT_WHITE); 
    // tft.drawString(tm.second, 20, 205, 6);  // Segundo
    // tft.drawString("sec",   20, 280, 4);  

    tft.setTextColor(TFT_MAROON, TFT_WHITE);  
    tft.drawString(tm.date,   55, 260, 4);  // Data

    while (true) {
        bool buttonBackState = digitalRead(BUTTON_BACK);
        if (buttonBackState == LOW) {  // Se botão de voltar for pressionado
            delay(100);                // Debounce simples
            break;                     // Sai do loop e volta ao menu
        }
        delay(500); // Reduz a carga do loop
    }
}

/* Função para mostrar a Temperatura do Ambiente */
/* **************************************************************** */
void tp(){
  // Limpa a tela com cor de fundo
  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_MAROON, TFT_WHITE);
  tft.drawString("Temperatura", 52, 15, 4);
  tft.drawString("-----------------------------------------", 10, 42, 2);

  // Dimensões do display
  int screenWidth = 240;  // Largura do display
  int screenHeight = 320; // Altura do display

  // Dimensões do retângulo
  int rectWidth = 200;    // Largura do retângulo
  int rectHeight = 100;   // Altura do retângulo
  int rectX = (screenWidth - rectWidth) / 2;  // Centraliza na largura
  int rectY = (screenHeight - rectHeight) / 2; // Centraliza na altura

  // Definir cores
  uint16_t rectColor = TFT_GREENYELLOW;    // Cor do retângulo

  // Desenha o retângulo preenchido
  tft.fillRect(rectX, rectY, rectWidth, rectHeight, rectColor);

  tft.setTextColor(TFT_MAROON, TFT_GREENYELLOW);  
  tft.drawString("Temperatura", 45, 130, 4);

  tft.drawString(String(returnTemperature()), 66, 160, 4);
  tft.drawString(" C", 135, 160, 4);

  if(returnTemperature() >= 51){
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, HIGH);
  }
  if(returnTemperature() >= 40 && returnTemperature() <= 50){
    digitalWrite(ledRed, HIGH);
  }
  if(returnTemperature() >= 33 && returnTemperature() <= 35){
    digitalWrite(ledYellow, HIGH);
  }
  if(returnTemperature() >= 22 && returnTemperature() <= 32 ){
    digitalWrite(ledGreen, HIGH);
  }
  else{
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, HIGH);
  }

  while (true) {
     bool buttonBackState = digitalRead(BUTTON_BACK);
     if (buttonBackState == LOW) {  // Se botão de voltar for pressionado
         delay(100);                // Debounce simples
         break;                     // Sai do loop e volta ao menu
     }
     delay(500); // Reduz a carga do loop
  }
}
/* **************************************************************** */

/* Função para mostrar a Umidade do Ar no Ambiente*/
/* **************************************************************** */
void hd(){
  // Limpa a tela com cor de fundo
  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_MAROON, TFT_WHITE);
  tft.drawString("Umidade do Ar", 35, 15, 4);
  tft.drawString("-----------------------------------------", 10, 42, 2);

  // Dimensões do display
  int screenWidth = 240;  // Largura do display
  int screenHeight = 320; // Altura do display

  // Dimensões do retângulo
  int rectWidth = 200;    // Largura do retângulo
  int rectHeight = 100;   // Altura do retângulo
  int rectX = (screenWidth - rectWidth) / 2;  // Centraliza na largura
  int rectY = (screenHeight - rectHeight) / 2; // Centraliza na altura

  // Definir cores
  uint16_t rectColor = TFT_GREENYELLOW;    // Cor do retângulo

  // Desenha o retângulo preenchido
  tft.fillRect(rectX, rectY, rectWidth, rectHeight, rectColor);

  tft.setTextColor(TFT_VIOLET, TFT_GREENYELLOW);  
  tft.drawString("Umidade do Ar", 30, 130, 4);

  tft.drawString(String(returnHumidity()), 66, 160, 4);
  tft.drawString(" %", 135, 160, 4);

  if(returnHumidity() >= 101){
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, HIGH);
  }
  if(returnHumidity() >= 60 && returnHumidity() <= 100){
    digitalWrite(ledGreen, HIGH);
  }
  if(returnHumidity() >= 40 && returnHumidity() <= 60){
    digitalWrite(ledYellow, HIGH);
  }
  if(returnHumidity() >= 0 && returnHumidity() <= 30){
    digitalWrite(ledRed, HIGH);
  }else{
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, HIGH);
  }

  while (true) {
     bool buttonBackState = digitalRead(BUTTON_BACK);
     if (buttonBackState == LOW) {  // Se botão de voltar for pressionado
         delay(100);                // Debounce simples
         break;                     // Sai do loop e volta ao menu
     }
     delay(500); // Reduz a carga do loop
  }
}
/* **************************************************************** */

    