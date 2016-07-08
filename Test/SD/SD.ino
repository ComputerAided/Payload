/*****************************************************
 * SD.ino
 * Written By Joe Q. and Kenny H.
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
*****************************************************/
/*****************************************************
 * Resources:
 * https://learn.sparkfun.com/tutorials/microsd-breakout-with-level-shifter-hookup-guide
 * https://www.arduino.cc/en/Reference/SD
 * https://www.arduino.cc/en/Tutorial/Datalogger
*****************************************************/

#include <Payload.h>

// Example variables to log - log these variables in the same .txt file multiple times.
float weather[3] = {32.2, 20, 32.3, 30.13};
<<<<<<< HEAD:Test/SD/SD.ino
double lat, lon;
void setup () {
 SerialUSB.begin(9600);
 
 SerialUSB.print("Initializing SD card...");

 
  if (!SD.begin(chipSelect)) {
    SerialUSB.println("Card failed, or not present");
   
    return;
  }
  SerialUSB.println("card initialized.");
}
}
=======
String GPSData = "$GPRMC, 161229.487, A, 3723.24756, N, 12158.34162, W, 0.13, 309.62, 120598, ,*10
";

void setup() {
  //
  Serial.begin(""9600);
  Serial.print("hello world");
  
 
} 
>>>>>>> Sensor-update:Test/SD.ino

void loop() {
  //
 File fd;
  for (int i = 0; i < 4; i++) [
    fd.println(weather[i]);
    
    
    File dataFile = .open () {
    if (datafile) {
    dataFileln("")
    
}

void writeToSD

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
   for (int i = 0; i < 4; i++) {
    dataFile.println(weather[i]);
   }
   dataFile.println(lon);
   dataFile.println(lat);
   dataFile.close();
    
    SerialUSB.println("succesfully logged!");
  }
  
  else {
    SerialUSB.println("error opening datalog.txt");
  }
