/* ================================================================================== */
/* ===== PROGRAMA PRINCIPAL : ATMEGA328P + TELEMETRIA + CARTÃO SD + EXPERIMENTO ===== */
/* ================================================================================== */

/*
    Pinagem:
    - Pino no arduino (Pino no ATMEGA328)
    
    - 11 (17): MOSI (NRF + SD)
    - 12 (18): MISO (NRF + SD)
    - 13 (19): SCK (NRF + SD)
    - 08 (14): CSN (NRF)
    - 07 (13): CE (NRF)
    - 10 (16): CS_PIN (SD)
    - 00 (02): RX (Comunicação serial)
    - 01 (03): TX (Comunicação serial)
*/

// Declaração de bibliotecas
#include "libs/NRF24L01_BIBLIOTECA.h"
#include "libs/ARMAZENAMENTO_BIBLIOTECA.h"
#include <SoftwareSerial.h>

#define timeOut 10

float time1;
float time2;

SoftwareSerial monitorSerial(5, 6);

void setup()
{
    monitorSerial.begin(9600);
    Serial.begin(9600);

    radio.begin();
    setAddress(0, 1);
    longRangeSettings();
}

void loop() {
    if (monitorSerial.available() > 0) {
        String message = monitorSerial.readStringUntil('\n');
        Serial.println(message);

        // Verificação do cartão SD
        time1 = millis();
        writeOnSD(message);
        time2 = millis();

        Serial.prinln(time2 - time1);

        // NRF24L01
        char str[32];
        message.toCharArray(str, 32);

        time1 = millis();
        bool teste = sendMessage(str);
        time2 = millis();

        Serial.prinln(time2 - time1);

        Serial.println(message);
        Serial.println(teste);
    }
}
