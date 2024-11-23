#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>
#include "config.h"

// Função para ler o JSON do SPIFFS
DynamicJsonDocument readJSON() {
  // Define o tamanho máximo esperado para o JSON
  DynamicJsonDocument doc(256);

  // Inicializa o SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar o sistema de arquivos SPIFFS");
    return doc; // Retorna documento vazio
  }

  // Para Debug: Listar arquivos no SPIFFS
  // Serial.println("Arquivos disponíveis no SPIFFS:");
  // File root = SPIFFS.open("/");
  // File file = root.openNextFile();
  // while (file) {
  //   Serial.println(file.name());
  //   file = root.openNextFile();
  // }

  // Abre o arquivo JSON
  File configurations = SPIFFS.open("/config/configurations.json", "r");
  if (!configurations) {
    Serial.println("Falha ao abrir o arquivo JSON!");
    return doc; // Retorna documento vazio
  }

  // Verifica o tamanho do arquivo
  size_t size = configurations.size();
  if (size == 0) {
    Serial.println("Arquivo JSON está vazio!");
    return doc; // Retorna documento vazio
  }

  // Lê o conteúdo do arquivo para uma string
  String content = configurations.readString();

  // Para Debug: Verifica o conteúdo do arquivo 
  // Serial.println("Conteúdo do arquivo JSON:");
  // Serial.println(content);

  // Deserializa o JSON
  DeserializationError error = deserializeJson(doc, content);
  if (error) {
    Serial.print("Falha ao carregar JSON: ");
    Serial.println(error.c_str());
  }

  return doc;
}
