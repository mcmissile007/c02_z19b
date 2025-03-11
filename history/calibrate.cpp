#include <Arduino.h>
#include "MHZ19.h"
#include <HardwareSerial.h>  // Usamos HardwareSerial con ESP32

#define RX_PIN 16  
#define TX_PIN 17  
#define BAUDRATE 9600  // Velocidad de comunicación del sensor

HardwareSerial mySerial(2);  // Usamos Serial2 en ESP32
MHZ19 myMHZ19;

void setup() {
    Serial.begin(115200);
    mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);  // Iniciar comunicación con el sensor

    Serial.println("Iniciando MH-Z19...");
    myMHZ19.begin(mySerial);  // Asignamos Serial1 al sensor
    
    delay(5000);  // Esperamos a que el sensor esté listo

    Serial.println("Esperando estabilización del sensor (30 min recomendados)...");
    delay(30000);  // Esperamos 30 segundos (idealmente 30 minutos en aire limpio)

    Serial.println("Calibrando el sensor...");
    myMHZ19.calibrate();  // Ejecutamos la calibración

    if (myMHZ19.errorCode == RESULT_OK) {
        Serial.println("Calibración exitosa.");
    } else {
        Serial.print("Error en la calibración. Código: ");
        Serial.println(myMHZ19.errorCode);
    }

    Serial.println("Desactivando autocalibración...");
    myMHZ19.autoCalibration(false);  // Desactivar autocalibración

    if (myMHZ19.errorCode == RESULT_OK) {
        Serial.println("Autocalibración desactivada.");
    } else {
        Serial.print("Error desactivando autocalibración. Código: ");
        Serial.println(myMHZ19.errorCode);
    }

    Serial.println("Proceso finalizado. Reinicia el ESP32 para continuar.");
}

void loop() {
    // No hace nada en el loop, solo calibramos en setup()
}
