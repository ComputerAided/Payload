/*****************************************************
 * Payload.ino
 * Written By Kenny H
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
 * 
 * Some functions derived from the works of SparkFun Electronics: https://www.sparkfun.com, https://github.com/SparkFun
*****************************************************/
#include <Payload.h> // Includes SD, SPI, Si7021, and I2C 

Weather sensor;

float weather[1] = [0, 0];

void setup () {
  sensor.begin();
}

void loop () {
  
}


// Functions for the Si7021

void getWeather()
{
  float humidity;
  float tempf;
  
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  tempf = sensor.getTempF();
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()
  
  weather[0] = humidity;
  weather[1] = tempf;
}
