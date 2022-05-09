/* By Beatrice Farb and Sophia Clark, 2022
* Code sampled from: 
*  * ADAFRUIT 31865 example code in Arduino IDE
*  * https://how2electronics.com/diy-turbidity-meter-using-turbidity-sensor-arduino/
*  * https://how2electronics.com/tds-sensor-arduino-interfacing-water-quality-monitoring/
*/

// track delays
int delays = 0;

#include <EEPROM.h>
#include <Wire.h> 
#include <Adafruit_MAX31865.h>
#include "GravityTDS.h"

// starting address for value storage
int address = 0;

// temperature stuff
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
#define RREF      430.0 // The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RNOMINAL  100.0 // The 'nominal' 0-degrees-C resistance of the sensor 100.0 for PT100, 1000.0 for PT1000

// TDS stuff
#define TdsSensorPin A1
GravityTDS gravityTds;
float temperature = 25, tdsValue = 0;

// turbidity stuff 
#define TurbiditySensorPin A0
float volt;
float ntu;

void setup() {
  Serial.begin(9600);

  // temp
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary

  // TDS
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
}

void loop() {
  // temp 
    uint16_t rtd = thermo.readRTD();
    float temperature = thermo.temperature(RNOMINAL, RREF);

  // tds  
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  // sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    
  // turbidity 
    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(TurbiditySensorPin)/1023)*5;
    }
    volt = volt/800;

  // round the outputs for storage
    // temperature = round_to_dp(temperature, 2);
    // tdsValue = round_to_dp(tdsValue, 0);
    volt = round_to_dp(volt,2);
  
  // printing everything 
    Serial.println(temperature);
    Serial.println(tdsValue);
    Serial.println(volt);

  // adding to EEPROM
    EEPROM.put(address, temperature);
    address += sizeof(float);
    EEPROM.put(address, tdsValue);
    address += sizeof(float);
    EEPROM.put(address, volt);


  // increment addresses
    address = address + sizeof(float);

  // delay
    delay(1080000);

}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}  
