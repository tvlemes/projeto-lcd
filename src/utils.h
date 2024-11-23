#include <utility>
#include <SPIFFS.h>
#include <Arduino.h>

#ifndef UTILS
#define UTILS



// void sensorDHT11();

// Captura a Temperatura e Humidade do Ar atual
void updateSensorReadings();

// extern float temperature;
// extern float humidity;

float returnTemperature();
float returnHumidity();

// Captura a Data e Hora atual
// Definição da estrutura TimeParts
struct TimeParts {
    String hour;
    String minute;
    String second;
    String date;
};
TimeParts timeNow();

// Função para ler a Temperatura interna do ESP32
float temp();

// Função para retornar o Espaço em Disco
std::pair<int, int> storage();

// Inicializando LEDs
extern int ledRed; // LED VERMELHO
extern int ledYellow; // AMARELO
extern int ledGreen; // LED VERDE
extern int ledRGB; 
void setupLEDs();

#endif