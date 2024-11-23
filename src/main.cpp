#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include "utils.h"
#include "lcd.h"
#include "config.h"
#include <ArduinoJson.h>


/* Configuração inicial do Menu */
/* **************************************************************** */
/* Definição dos pinos dos botões, fora do setup() e do loop() */
#define BUTTON_UP 12    // Botão para subir no menu
#define BUTTON_DOWN 13  // Botão para descer no menu
#define BUTTON_SELECT 25 // Botão para selecionar

/* Definição dos itens do menu */
enum MenuItems { Hora_Data, Temperatura, Umidade_do_Ar, About, NUM_ITEMS };

/* Estado anterior dos botões para evitar múltiplas leituras */
bool lastButtonUpState = HIGH;
bool lastButtonDownState = HIGH;
bool lastButtonSelectState = HIGH;
// /* **************************************************************** */


// Configurações do Arquivo /config/configurations.json
DynamicJsonDocument doc = readJSON();

// Configuração da rede Wi-Fi
const char* ssid = doc["ssid"].as<const char*>(); 
const char* password = doc["password"].as<const char*>(); 

// Cria o servidor na porta 80
AsyncWebServer server(80);  


void setup() {
Serial.begin(115200);
  // Conecta-se ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicia o servidor
  server.begin();  
  Serial.println("Servidor local ESP32 iniciado!");

  // Inicializa o LCD
  // init_lcd();

  /* Inicializa o LCD */
  init_lcd(); 

  /* Tela About */
  about();
  delay(3000);

  /* Exibe o menu inicial */
  drawMenu(NUM_ITEMS);
  // board(NUM_ITEMS);

  /* Configura os pinos dos botões como entrada com pull-up */
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  pinMode(ledRGB, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRGB, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
}

int contator = 0;
void loop() {

  // Leitura dos estados dos botões
  bool buttonUpState = digitalRead(BUTTON_UP);
  bool buttonDownState = digitalRead(BUTTON_DOWN);
  bool buttonSelectState = digitalRead(BUTTON_SELECT);

  // Verifica se o botão UP foi pressionado
  if (buttonUpState == LOW && lastButtonUpState == HIGH) {
    currentItem = (currentItem - 1 + NUM_ITEMS) % NUM_ITEMS; // Vai para o item anterior (com rolagem)
    drawMenu(NUM_ITEMS);
    delay(200); // Debounce simples
  }

  // Verifica se o botão DOWN foi pressionado
  if (buttonDownState == LOW && lastButtonDownState == HIGH) {
    currentItem = (currentItem + 1) % NUM_ITEMS; // Vai para o próximo item (com rolagem)
    drawMenu(NUM_ITEMS);
    delay(200); // Debounce simples
  }

  // Verifica se o botão SELECT foi pressionado
  if (buttonSelectState == LOW && lastButtonSelectState == HIGH) {
    itemSelected = true; // Marca o item como selecionado
    delay(200);          // Debounce simples
  }

  // Atualiza o estado anterior dos botões
  lastButtonUpState = buttonUpState;
  lastButtonDownState = buttonDownState;
  lastButtonSelectState = buttonSelectState;

  // Executa ações com base na seleção do item
  if (itemSelected) {
    if (currentItem == Hora_Data) {
      tft.fillScreen(TFT_WHITE);
      board();
    }
    if (currentItem == About) {
      tft.fillScreen(TFT_WHITE);
      about();
    }
    if (currentItem == Temperatura) {
      tft.fillScreen(TFT_WHITE);
      tp();     
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
    } 
    if (currentItem == Umidade_do_Ar) {
      tft.fillScreen(TFT_WHITE);
      hd();     
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
    } 
    // else {
    //     tft.fillScreen(TFT_WHITE);
    //     tft.setTextColor(TFT_BLACK);
    //     tft.drawString("Selecionado:", 20, 50, 4);
    //     tft.drawString(menuLabels[currentItem], 20, 100, 4);
    //     delay(1000); // Pausa para exibir a seleção
    //     tft.fillScreen(TFT_WHITE);
    // }

    // Após concluir a ação, redefine a seleção e redesenha o menu
    itemSelected = false;
    drawMenu(NUM_ITEMS);
  }  
  
}



 