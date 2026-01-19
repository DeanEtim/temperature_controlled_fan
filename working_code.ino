#include <OneWire.h>
#include <DallasTemperature.h>

#define tempSensorPin 3
OneWire oneWire(tempSensorPin);
DallasTemperature tempSensor(&oneWire);
float Celcius = 0;
float Fahrenheit = 0;

// Declare motor driver PIns
#define motorPin 9
#define forwardDirection 10
#define reverseDirection 11

void setup(void) {
  // Initialize Serial monitor
  Serial.begin(9600);

  // Initialize temperature sensor
  tempSensor.begin();

  // define the pin modes
  pinMode(motorPin, OUTPUT);
  pinMode(forwardDirection, OUTPUT);
  pinMode(reverseDirection, OUTPUT);

  // set to clockwise rotation by default
  digitalWrite(forwardDirection, true);
  digitalWrite(reverseDirection, false);
}

void loop(void) {
  // request for the values
  tempSensor.requestTemperatures();
  Celcius = tempSensor.getTempCByIndex(0);        // In Celsius
  Fahrenheit = tempSensor.toFahrenheit(Celcius);  // in Fahrenheit
  
  // display the values on the serial monitor
  Serial.print("Celsius:  ");
  Serial.print(Celcius);
  Serial.print("\tFahrenheit: ");
  Serial.println(Fahrenheit);
  delay(300);

  int motorSpeed = map(analogRead(motorPin), 0, 1023, 90, 224);
  if (Celcius >= 30.0) {
    analogWrite(motorPin, motorSpeed);
  } else {
    analogWrite(motorPin, 0);
  }
}
