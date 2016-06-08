
/*****************************************************
 * Payload.ino
 * Written By Kenny H
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
 * Not yet finished
*****************************************************/
#include <Payload.h> // includes for I2C, SPI, SD, Si7021, BMP180 and SPI
//output over Serial USB
#define debug 0

//Creates an instance for the Si7021
HTU21D sensor;

//Creates an instance of the BMP180
SFE_BMP180 pressure;

//variable to hold weather recordings
//SI7021 temp, Si7021 Humidity, BMP180 temp, BMP180 pressure
float weather[] = {0, 0, 0, 0};

//GPS States
enum states: uint8_t { 
  NORMAL,
  STARTED,
  V, 
  VT,
  VTG,
  G,
  GG,
  GGA
};

uint8_t state = NORMAL;


void setup () {
  sensor.begin();
  pressure.begin();
}

void loop () {
  
}

//function to read temp and humidity over Si7021
void getWeather() {

}

//prints info from Si7021 - only for testing
#if debug
void printInfo() {

}
#endif

//functions for SD
void initSD () {

}
void writeToSD () {
  
}

//functions for GPS
void getGPSData () {
  Serial1.begin(9600);
  
}

//
