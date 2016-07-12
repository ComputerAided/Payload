/*****************************************************
 * Payload.ino
 * Written By Kenny H
 * THE SOFTWARE IS PROVIDED "AS-IS", AND "WITH ALL FAULTS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.
*****************************************************/
#include <Payload.h> // includes for I2C, SPI, SD, Si7021, BMP180 and SPI
#define ALTITUDE 1655

#define debug 1

//Creates an instance for the Si7021
HTU21D sensor;

//Creates an instance of the BMP180
SFE_BMP180 pressure;

//variable to hold weather recordings
//Si7021 temp, Si7021 Humidity, BMP180 temp, BMP180 pressure, Absolute Pressure
float weather[] = {0, 0, 0, 0, 0};

void setup () {
  //enable USB
  Serial.begin(9600);
  while (!Serial);

  //enable sensors
  sensor.begin();
  //get calibration data from BMP180
  if (pressure.begin())
    Serial.println("BMP180 Success");
  else
  {
    Serial.println("BMP180 init Fail");
    while(1); //halt program
  }
  

  //Show setup is complete
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  Serial.println("Setup Complete");
}

void loop () {
  getWeather();
  for (int i = 0; i < 5; i ++) {
    Serial.println(weather[i]);
  }
  delay(5000);
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//function to read temp and humidity and pressure over the sensors
void getWeather() {
  //gets data from the Si7021
  float humd = sensor.readHumidity();
  float temp = sensor.readTemperature();

  weather[0] = temp;
  weather[1] = humd;

  //gets data from BMP180
  char status;
  double T, P, p0, a;

  //gets pressure readings
  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      #if debug
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      Serial.print((9.0/5.0)*T+32.0,2);
      Serial.println(" deg F");
      #endif
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          #if debug
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");
          #endif
          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          #if debug
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");
          #endif
          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.

          a = pressure.altitude(P,p0);
          #if debug
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
          #endif
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  weather[2] = T;
  weather[3] = p0;
  weather[4] = P;
}


