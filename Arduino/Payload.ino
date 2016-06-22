/*****************************************************
 * Payload.ino
 * Written By Kenny H
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
*****************************************************/
//new code !!
#include <Payload.h> // includes for I2C, SPI, SD, Si7021, BMP180 and SPI

//Creates an instance for the Si7021
HTU21D sensor;

//Creates an instance of the BMP180
SFE_BMP180 pressure;

//variable to hold weather recordings
//Si7021 temp, Si7021 Humidity, BMP180 temp, BMP180 pressure
float weather[] = {0, 0, 0, 0};

//GPS States
enum states {
  NO_READ,
  READ
};

uint8_t state = NO_READ;

void setup () {
  //enable sensors
  sensor.begin();
  pressure.begin();
  
  //enable USB
  SerialUSB.begin(9600);
  Serial1.begin(9600);
  while (!Serial1 || !SerialUSB);

  //Show setup is complete
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  SerialUSB.println("Setup Complete");
}

void loop () {
  switch (state) {
    case READ: //tells to read from Serial1
    {
      String incomingString = Serial1.readStringUntil('*');
      state = NO_READ;
      SerialUSB.println(incomingString);
      break;
    } 
    case NO_READ: //Does Other Stuff
    {
      pollSerial();
      break;
    }
  }
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//function to read temp and humidity over Si7021
void getWeather() {

}

//prints info from Si7021 - only for testing
void printInfo() {

}

//functions for SD
void initSD () {

}
void writeToSD () {
  
}

//functions for GPS
void pollSerial () {
  if (Serial1.available() > 0) {
    if (Serial1.find('R')){
      if (Serial1.find('M')) {
        if (Serial1.find('C')) {
          state = READ;
        }
      }
    }
  }
}
