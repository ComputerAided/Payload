/*****************************************************
 * Payload.ino
 * Written By Kenny H
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
 * 
 * 
 * Compiled Using Arduino IDE v1.6.5
 * 
 * Assumed hardware is the Sparkfun Samd21 mini breakout
 * 
*****************************************************/

//Dependency for HTU21D and BMP180
#include <Wire.h>

//Dependency for SD.h
#include <SPI.h>

// GPS parsing library
#include <TinyGPS.h>

// Controld the BMP180
#include <SFE_BMP180.h>

// Controls the Si7021*
// *SparkFun's Si7021 Library didn't work on the SAMD21 Mini Breakout, but this library does.
#include <SparkFunHTU21D.h>

// Writes data to the SD Card
#include <SD.h>

//Defines
#define FAIL 5
#define NO_VALID_FIX 6
#define chipSelect 8

//Constructors
SFE_BMP180 pressure;
HTU21D sensor;

TinyGPS gps;
File dataFile;

//global variables
volatile float si7021[2] = {0, 0};
volatile double bmp180[3] = {0, 0, 0};

float lat, lon, alt;
unsigned long age;
int year;
byte month, day, hour, minute, second, hundredths;


void setup() {
  //enable the sensors
  sensor.begin();
  if (pressure.begin()) {
  } else {
    pinMode(FAIL, OUTPUT);
    while (1) {
      digitalWrite(FAIL, HIGH);
      delay(1000);
      digitalWrite(FAIL, LOW);
      delay(1000);
    }
  }

  //enable the GPS input
  Serial1.begin(9600);

  //enable the SD card
  if (!SD.begin(chipSelect)) {
    pinMode(5, OUTPUT);
    while (1) {
      digitalWrite(5, HIGH);
      delay(1000);
      digitalWrite(5, LOW);
      delay(1000);
    }
  }

  //set this pin output
  pinMode(NO_VALID_FIX, OUTPUT);

  delay(10800000); //delay 3 hrs (Might be changed soon!)
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  getHumidity();
  getAtmosphericPressure(alt);

  String dataString = assembleString();

  
  dataFile = SD.open("test.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  
  smartdelay(1000);
}

//gets data from the Si7021
void getHumidity () {
  float temp = sensor.readTemperature();
  float humd = sensor.readHumidity();

  si7021[0] = temp;
  si7021[1] = humd;
}

//gets data from the bmp180
void getAtmosphericPressure (float alt) {
  char status;
  double T, P, p0;

  status = pressure.startTemperature(); //start a temperature measurement
  if (status != 0) {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0) {
      status = pressure.startPressure(3);
      if (status != 0) {
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0) {
          p0 = pressure.sealevel(P, alt);
        }
      }
    }
  }

  bmp180[0] = T;
  bmp180[1] = P;
  bmp180[2] = p0;
}

//delay that collects GPS data
void smartdelay (unsigned long ms) {
  unsigned long start = millis();
  do
  {
    while (Serial1.available()) {
      gps.encode(Serial1.read());
    }
  } while (millis() - start < ms);
}

//Assembles a string to write to the SD Card
String assembleString() {
  //Assembles the string with the time
  String timeString = "";
  if (age == TinyGPS::GPS_INVALID_AGE) {
    timeString += 'n';
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d.%02d", year, day, month, hour, minute, second, hundredths);
    timeString += String(sz);
  }

  //fetch lat, lon, and alt
  gps.f_get_position(&lat, &lon, &age);
  alt = gps.f_altitude();

  //assemble string with geographic coordinates
  String geoString = "";
  if (age == TinyGPS::GPS_INVALID_AGE) {
    geoString += "position not valid";
    digitalWrite(NO_VALID_FIX, HIGH);
    pinMode(NO_VALID_FIX, HIGH);
  } else {
    geoString += String(lat, 6);
    geoString += ',';
    geoString += String(lon, 6);
    geoString += ',';
    geoString += String(alt, 6);
    geoString += ',';
    geoString += String(age);
    digitalWrite(NO_VALID_FIX, LOW);
  }

  //Assemble the final string that contains the data
  String dataString = "";
  dataString += String(si7021[0]);
  dataString += ',';
  dataString += String(si7021[1]);
  dataString += ',';
  dataString += String(bmp180[0]);
  dataString += ',';
  dataString += String(bmp180[1]);
  dataString += ',';
  dataString += String(bmp180[2]);
  dataString += ',';
  dataString += timeString;
  dataString += ',';
  dataString += geoString;
  dataString += "\r\n";

  return dataString;
}

