/*
Author: L3nny_P34s4n7
Email: contact@leonardovichi.com
Date: 2024-08-10
License: MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CONNECTIONS
-----------

PN532 RFID NFC
SDA > SDA or A4
SCL > SCL or A5

 */

#include <Wire.h>
#include <Adafruit_PN532.h>

// Definindo os pinos utilizados para I2C
#define SDA_PIN A4
#define SCL_PIN A5

// Inicializando o PN532
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

void setup(void) {
  Serial.begin(115200);
  Serial.println("Inicializando NFC...");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Não encontrou a placa PN53x");
    while (1); // parar se não encontrar o módulo
  }

  Serial.print("Encontrou o chip PN5"); 
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Versão do firmware: ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  nfc.SAMConfig(); // Configura o módulo para operações normais
  Serial.println("Esperando por um cartão NFC...");
}

void loop(void) {
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer para armazenar o UID
  uint8_t uidLength;                        // Comprimento do UID
  uint8_t data[16];                         // Buffer para armazenar dados do bloco
  uint8_t key[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };  // Chave padrão

  // Tentando ler o cartão NFC
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    Serial.println("Cartão NFC encontrado!");

    // Imprimindo o UID
    Serial.print("UID: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(uid[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Tentativa de autenticação do bloco 1
    if (nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 1, 0, key)) {
      Serial.println("Autenticação bem-sucedida.");

      // Tentando ler os dados gravados (bloco 1)
      if (nfc.mifareclassic_ReadDataBlock(1, data)) {
        Serial.print("Dados gravados (bloco 1): ");
        for (int i = 0; i < 16; i++) {
          Serial.print(data[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
      } else {
        Serial.println("Falha na leitura do bloco 1.");
      }
    } else {
      Serial.println("Falha na autenticação.");
    }

    Serial.println("----- Fim das Informações do Cartão -----\n");
    delay(2000);
  } else {
    Serial.println("Aguardando um cartão...");
    delay(1000);
  }
}
