
#include <Arduino.h>
#include "MHZ19.h"                        
#include <HardwareSerial.h>
 
#define RX_PIN 16
#define TX_PIN 17
#define BAUDRATE 9600                       


MHZ19 myMHZ19;
HardwareSerial mySerial(1);  // Usamos UART1

unsigned long getDataTimer = 0;

void setup()
{
  
    Serial.begin(115200);     // UART0 (USB para monitor serie)
    mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);  // UART1 para el MH-Z19B                                
    myMHZ19.begin(mySerial);   
    myMHZ19.setFilter(true, true);                               

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
        getDataTimer = millis();   // Update interval
    }
}