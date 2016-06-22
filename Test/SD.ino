/*****************************************************
 * SD.ino
 * Written By Joe Q
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
String GPSData = "$GPRMC, 161229.487, A, 3723.24756, N, 12158.34162, W, 0.13, 309.62, 120598, ,*10
";

void setup () {
  
}

void loop () {
  
}
