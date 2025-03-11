
//https://github.com/WifWaf/MH-Z19/blob/master/examples/BasicUsage/BasicUsage.ino
#include <Arduino.h>
#include "MHZ19.h"                        
#include <HardwareSerial.h>
#define RX_PIN 16
#define TX_PIN 17
#define BAUDRATE 9600                       


MHZ19 myMHZ19;
HardwareSerial mySerial(2);  // Usamos UART2

unsigned long getDataTimer = 0;

void setup()
{
  
    Serial.begin(115200);     // UART0 (USB para monitor serie)
    mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);  // UART1 para el MH-Z19B                                
    myMHZ19.begin(mySerial);   
    myMHZ19.setFilter(true, true);
    myMHZ19.autoCalibration(false);  // Desactivar autocalibración
    delay(5000);
    if (myMHZ19.errorCode == RESULT_OK) {
        Serial.println("Autocalibración desactivada.");
    } else {
        Serial.print("Error desactivando autocalibración. Código: ");
        Serial.println(myMHZ19.errorCode);
    }                               

}

void loop()
{
    if (millis() - getDataTimer >= 2000) 
    {

        Serial.println("------------------");
        // get sensor readings as signed integer        
        int CO2Unlimited = myMHZ19.getCO2(true);
        Serial.print("CO2: ");
        Serial.print(CO2Unlimited);
        Serial.println(" PPM");
        int temp = myMHZ19.getTemperature();// Request Temperature (as Celsius)
        Serial.print("Temperature (C): ");
        Serial.println(temp);
        getDataTimer = millis();   // Update interval
    }
}

