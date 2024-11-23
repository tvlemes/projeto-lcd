#include "DHT.h"
#include <utility>
#include <SPIFFS.h>
#include <Arduino.h>
#include "utils.h"

/* DHT11 */
/* **************************************************************** */
// Pino digital conectado ao sensor DHT11 Sensor
#define DHTPIN 4
#define DHTTYPE DHT11
#define DEVICE_UID "TOCANTINS"

// Inicializando o DHT11 Sensor
DHT dht(DHTPIN, DHTTYPE);

int ledRed = 21; // LED VERMELHO
int ledYellow = 27; // AMARELO
int ledGreen = 15; // LED VERDE
int ledRGB = 17; // LED RGB


void setupLEDs() {
  pinMode(ledRGB, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);

  digitalWrite(ledRGB, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
}


float returnTemperature() {
  float temp = dht.readTemperature();
  return temp;
}

float returnHumidity() {
  return dht.readHumidity();
}
/* **************************************************************** */


/* Data/Hora */
/* **************************************************************** */
// Captura a Data e Hora atual
TimeParts timeNow() {
    struct tm timeinfo;

    // Configura o fuso horário para UTC-3 (Horário de Brasília, por exemplo)
    configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

    if (!getLocalTime(&timeinfo)) {
        Serial.println("Falha ao obter o horário");
        return {"00", "00", "00"}; // Retorna valores padrão em caso de erro
    }

    // Obter as partes da hora
    char hourBuffer[3];
    char minuteBuffer[3];
    char secondBuffer[3];
    char dateBuffer[12];

    strftime(hourBuffer, sizeof(hourBuffer), "%H", &timeinfo);   // Hora
    strftime(minuteBuffer, sizeof(minuteBuffer), "%M", &timeinfo); // Minuto
    strftime(secondBuffer, sizeof(secondBuffer), "%S", &timeinfo); // Segundo
    strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", &timeinfo); // Segundo

    // Retornar as partes como strings
    return {String(hourBuffer), String(minuteBuffer), String(secondBuffer), String(dateBuffer)};
}
/* **************************************************************** */


/* Temperatura Interna do ESP32 */
/* **************************************************************** */
// Função para ler a Temperatura interna do ESP32
float temp() {
  float temperature = temperatureRead(); 
  return temperature;
}
/* **************************************************************** */



/* Armazenamento Interno do ESP32 */
/* **************************************************************** */
// Função para retornar o Espaço em Disco
std::pair<int, int> storage() {
  // Obtém as informações de armazenamento
  unsigned int totalBytes = SPIFFS.totalBytes();
  unsigned int usedBytes = SPIFFS.usedBytes();

  // Retorna o par de valores
  return std::make_pair(totalBytes, usedBytes);
}
/* **************************************************************** */


/* Tutorial - Controle dos LED´s */
/* **************************************************************** */

/* Setando as portas dos LED´s no inicio do arquivo main.cpp fora do setup() e loop() */
// int ledRed = 21; // LED VERMELHO
// int ledYellow = 27; // AMARELO
// int ledGreen = 16; // LED VERDE
// int ledRGB = 17; // LED RGB

/* Estados dos LEDs (iniciam desligados), no inicio do arquivo main.cpp fora do setup() e loop() */
// bool stateLedRed = false;
// bool stateLedYellow = false;
// bool stateLedGreen = false;
// bool stateLedRGB = false;

/* pinMode e digitalWrite devem ser declaradas dentro de um contexto funcional */
/* Dentro do setup() */


/* Controle dos LED´s pelo Botton Push */
// Botão 1 - LED RGB
  // if (buttonState_1 == LOW) {
  //   stateLedRGB = !stateLedRGB; // Alterna o estado
  //   digitalWrite(ledRGB, stateLedRGB ? HIGH : LOW);
  //   Serial.println(stateLedRGB ? "LED RGB LIGADO" : "LED RGB DESLIGADO");
  //   delay(300); // Atraso para evitar múltiplos registros de clique
  // }

  // Botão 2 - LED Verde
  // if (buttonState_2 == LOW) {
  //   stateLedGreen = !stateLedGreen; // Alterna o estado
  //   digitalWrite(ledGreen, stateLedGreen ? HIGH : LOW);
  //   Serial.println(stateLedGreen ? "LED VERDE LIGADO" : "LED VERDE DESLIGADO");
  //   delay(300);
  // }

  // Botão 3 - LED Amarelo
  // if (buttonState_3 == LOW) {
  //   stateLedYellow = !stateLedYellow; // Alterna o estado
  //   digitalWrite(ledYellow, stateLedYellow ? HIGH : LOW);
  //   Serial.println(stateLedYellow ? "LED AMARELO LIGADO" : "LED AMARELO DESLIGADO");
  //   delay(300);
  // }

  // Botão 4 - LED Vermelho
  // if (buttonState_4 == LOW) {
  //   stateLedRed = !stateLedRed; // Alterna o estado
  //   digitalWrite(ledRed, stateLedRed ? HIGH : LOW);
  //   Serial.println(stateLedRed ? "LED VERMELHO LIGADO" : "LED VERMELHO DESLIGADO");
  //   delay(300);
  // }

  /* Tutorial - Push Botton */
/* **************************************************************** */

/* Configuração do Push Botton, no inicio do arquivo main.cpp fora do setup() e loop() */
// int buttonPin_1 = 12;
// int buttonPin_2 = 13;
// int buttonPin_3 = 25;
// int buttonPin_4 = 26;

/* Configura o pino do botão como entrada com pull-up interno dentro do setup() */
  // pinMode(buttonPin_1, INPUT_PULLUP);
  // pinMode(buttonPin_2, INPUT_PULLUP);
  // pinMode(buttonPin_3, INPUT_PULLUP);
  // pinMode(buttonPin_4, INPUT_PULLUP);

/* Leitura dos estados dos botões dentro do loop() */
  // int buttonState_1 = digitalRead(buttonPin_1);
  // int buttonState_2 = digitalRead(buttonPin_2);
  // int buttonState_3 = digitalRead(buttonPin_3);
  // int buttonState_4 = digitalRead(buttonPin_4);

/* Debounce simples com delay */
// delay(50);