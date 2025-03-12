
// https://github.com/WifWaf/MH-Z19/blob/master/examples/BasicUsage/BasicUsage.ino
#include <Arduino.h>
#include "MHZ19.h"
#include <HardwareSerial.h>
#define RX_PIN 16
#define TX_PIN 17
#define BAUDRATE 9600

void setup_calibration();
void setup_measurement();
void loop_measurement();

MHZ19 myMHZ19;
HardwareSerial mySerial(2); // Usamos UART2

unsigned long getDataTimer = 0;

unsigned long timeCalibrating = 30 * 60 * 1000;

void setup()
{
    setup_measurement();
}

void loop()
{
    loop_measurement();
}

void setup_measurement()
{
    Serial.begin(115200);                                 // UART0 (USB para monitor serie)
    mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN); // UART2 para el MH-Z19B
    myMHZ19.begin(mySerial);
    myMHZ19.setFilter(true, true);
    myMHZ19.autoCalibration(false); // Desactivar autocalibración
    delay(5000);
    if (myMHZ19.errorCode == RESULT_OK)
    {
        Serial.println("Autocalibración desactivada.");
    }
    else
    {
        Serial.print("Error desactivando autocalibración. Código: ");
        Serial.println(myMHZ19.errorCode);
    }
}

void setup_calibration()
{
    Serial.begin(115200);
    delay(5000);
    mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN); // Iniciar comunicación con el sensor
    delay(5000);
    Serial.println("Iniciando MH-Z19...");
    myMHZ19.begin(mySerial); // Asignamos Serial1 al sensor
    delay(5000); // Esperamos a que el sensor esté listo

    Serial.println("Esperando estabilización del sensor (30 min recomendados)...");
    delay(timeCalibrating); // Esperamos 30 segundos (idealmente 30 minutos en aire limpio)

    Serial.println("Calibrando el sensor...");
    myMHZ19.calibrate(); // Ejecutamos la calibración
   

    if (myMHZ19.errorCode == RESULT_OK)
    {
        Serial.println("Calibración exitosa.");
        delay(10000); 
    }
    else
    {
        Serial.print("Error en la calibración. Código: ");
        Serial.println(myMHZ19.errorCode);
    }

    Serial.println("Desactivando autocalibración...");
    myMHZ19.autoCalibration(false); // Desactivar autocalibración

    if (myMHZ19.errorCode == RESULT_OK)
    {
        Serial.println("Autocalibración desactivada.");
    }
    else
    {
        Serial.print("Error desactivando autocalibración. Código: ");
        Serial.println(myMHZ19.errorCode);
    }

    Serial.println("Proceso finalizado.");
}

void loop_measurement()
{
    if (millis() - getDataTimer >= 2000)
    {
        Serial.println("------------------");
        // get sensor readings as signed integer
        int CO2Unlimited = myMHZ19.getCO2(true);
        Serial.print("CO2: ");
        Serial.print(CO2Unlimited);
        Serial.println(" PPM");
        int temp = myMHZ19.getTemperature(); // Request Temperature (as Celsius)
        Serial.print("Temperature (C): ");
        Serial.println(temp);
        getDataTimer = millis(); // Update interval
    }
}
