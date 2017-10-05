
/***************************************************************************
  Example for BME680 Weather Station
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME680.
  The BME680 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME680, please go to ------> http://www.bluedot.space

  DISCLAIMER: 
  This Sketch is based on an UNFINISHED library!
  With the current version (05 October 2017) of the BlueDot BME680 library you can read temperature, pressure and humidity.
  However only through the I2C interface.
  So far I didn't manage to calculate the IAQ index (Indoor Air Quality), based on the measured gas resistances.
  For more details, please refer to the comments on the ".cpp" and ".h" files.

 ***************************************************************************/


#include <Wire.h>
#include <avr/wdt.h>
#include "BlueDot_BME680.h"
BlueDot_BME680 bme680 = BlueDot_BME680();


void setup() {
  Serial.begin(9600);
  
  Wire.begin();                                                         //I2C Initialisation
  bme680.parameter.I2CAddress = 0x77;                                   //Setting I2C Address to 0x77 (default)


  
                                      //Check Chip ID (97, which corresponds to 0x61)
  
  bme680.parameter.sensorMode = 0b01;                                   //Setting Sensor Mode to Forced Mode (default)
  bme680.parameter.tempOversampling = 0b101;                            //Setting Temperature Oversampling factor to 16 (max)
  bme680.parameter.pressOversampling = 0b101;                           //Setting Pressure Oversampling to factor 16 (max)
  bme680.parameter.humidOversampling = 0b101;                           //Setting Humidity Oversampling to factor 16 (max)  
  bme680.parameter.IIRfilter = 0b100;                                   //Setting IIR Filter coefficient to 127 (max)


  bme680.parameter.pressureSeaLevel = 1015;                           //default value of 1013.25 hPa
  bme680.parameter.tempOutsideCelsius = 14;                             //default value of 15°C
  //bme680.parameter.tempOutsideFahrenheit = 64.4;                      //default value of 59°F

  Serial.println(F("Basic Environmental Sensor - First Test"));  
  Serial.println(bme680.init());   



}

void loop()
{
    
  bme680.writeCTRLMeas();

  Serial.print(millis());
  Serial.print("\t");
  Serial.print(bme680.readTempC());
  Serial.print("\t"); 
  Serial.print(bme680.readTempF());
  Serial.print("\t"); 
  Serial.print(bme680.convertTempKelvin());
  Serial.print("\t");
  Serial.print(bme680.readPressure());
  Serial.print("\t");
  Serial.print(bme680.readAltitudeMeter());
  Serial.print("\t");
  Serial.print(bme680.readAltitudeFeet());
  Serial.print("\t"); 
  Serial.println(bme680.readHumidity());

  delay(250);


}

