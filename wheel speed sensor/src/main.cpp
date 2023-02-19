#include <Arduino.h>

const int sensorPin = 2; // KY-003 sensor connected to digital pin 2
volatile int sensorCount = 0; // variable to count the number of times the sensor is triggered
unsigned long lastTime = 0; // variable to store the last time the sensor was triggered
unsigned long currentTime; // variable to store the current time
unsigned long deltaTime; // variable to store the time difference between the last two sensor triggers
float wheelCircumference = 20.0; // the circumference of the wheel in millimeters
float wheelSpeed; // variable to store the calculated wheel speed in kilometers per hour

void countPulses() {
  sensorCount++; // increment the pulse count when the sensor is triggered
}

void setup() {
  Serial.begin(9600); // start serial communication at 9600 bps
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulses, RISING); // attach an interrupt to the sensor pin to count pulses on the rising edge
}

void loop() {
  currentTime = millis(); // get the current time
  deltaTime = currentTime - lastTime; // calculate the time difference between the last two sensor triggers
  if (deltaTime >= 500) { // calculate the wheel speed every half second
    wheelSpeed = (wheelCircumference * sensorCount) / (deltaTime / 1000.0); // calculate the wheel speed in meters per second
    wheelSpeed = wheelSpeed * 3.6; // convert to kilometers per hour
    wheelSpeed = wheelSpeed/10;
    Serial.print("Speed: "); // print label to the serial monitor
    Serial.print(wheelSpeed); // print the wheel speed to the serial monitor
    Serial.println(" km/h"); // print the unit to the serial monitor
    lastTime = currentTime; // store the current time as the last time
    sensorCount = 0; // reset the pulse count
  }
}