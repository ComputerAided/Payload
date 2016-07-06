/*****************************************************
 * Payload.ino
 * Written By Kenny H
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
*****************************************************/
#include <Payload.h> // includes for I2C, SPI, SD, Si7021, BMP180 and SPI

//Creates an instance for the Si7021
HTU21D sensor;

//Creates an instance of the BMP180
SFE_BMP180 pressure;

//variable to hold weather recordings
//Si7021 temp, Si7021 Humidity, BMP180 temp, BMP180 pressure
float weather[] = {0, 0, 0, 0};

void setup () {
  //enable sensors
  sensor.begin();
  pressure.begin();
  
  //enable USB
  SerialUSB.begin(9600);
  while (!SerialUSB);

  //Show setup is complete
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  SerialUSB.println("Setup Complete");
}

void loop () {
  
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//function to read temp and humidity and pressure over the sensors
void getWeather() {
  //gets data from the Si7021
  float humd = sensor.readHumidity();
  float temp = sensor.readTemperature();

  weather[0] = temp;
  weather[1] = humd;
}

//prints info from Si7021 - only for testing
void printInfo() {

}

