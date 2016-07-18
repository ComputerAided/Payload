#include <SoftwareSerial.h>

SoftwareSerial ss(4, 3);

#include <TinyGPS.h>

TinyGPS gps;

void setup () {
  Serial.begin(9600);
  ss.begin(9600);
}


void loop () {
  float lat, lon, alt;
  unsigned long age;

  //gets position and prints over Serial
  gps.f_get_position(&lat, &lon, &age);
  printFloat(lat, TinyGPS::GPS_INVALID_F_ANGLE, 6, false);
  Serial.print(',');
  printFloat(lon, TinyGPS::GPS_INVALID_F_ANGLE, 6, true);
  Serial.println(age);

  //prints altitude
  alt = gps.f_altitude();
  printFloat(alt, TinyGPS::GPS_INVALID_ALTITUDE, 0, true);
  
  //prints time
  printTime(gps);
  Serial.println();
  smartDelay(1000);
}


// ------------------------ Functions ------------------------ //
void printTime (TinyGPS &gps) {
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE) {
    Serial.println("Time Not Valid");
  } else {
    hour -= 6;
    Serial.print(month);
    Serial.print('/');
    Serial.print(day);
    Serial.print('/');
    Serial.print(year);
    Serial.print(' ');
    Serial.print(hour);
    Serial.print(':');
    Serial.print(minute);
    Serial.print(':');
    Serial.print(second);
    Serial.print(':');
    Serial.println(hundredths);
  }
}


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

//function to print floating point variables
void printFloat (float val, float inval, int prec, bool nl) {
  if (val == inval) {
    if (nl == true) {
      Serial.println("Not Valid");
    } else {
      Serial.print("Not Valid");
    }
      
  } else {
    if (nl == true) {
      Serial.println(val, prec);
    } else {
      Serial.print(val, prec);
    }
    
  }
}




