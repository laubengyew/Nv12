#include <Arduino.h>
// int variableValue = 1; // Initialize variable value to 1

// void setup() {
//   Serial.begin(9600); // Start serial communication with Arduino
//   Serial3.begin(9600); // Start serial communication with Serial3 display
// }

// void loop() {
//   // Update variable value
//   variableValue++;
//   if (variableValue > 100) {
//     variableValue = 1; // Reset variable value to 1
//   }
  
//   // Send variable value to Serial3 display
//   Serial3.print("n0.val=");
//   Serial3.print(variableValue);
//   Serial3.write(0xFF);
//   Serial3.write(0xFF);
//   Serial3.write(0xFF);
//   delay(1000); // Wait for 1 second
//   if (Serial3.available()) {
//     String response = Serial3.readStringUntil('\n');
//     Serial.println(response);
//   }
// }



// int led = 13;//LED pin
// int sensor = 3; //sensor pin
// int val; //numeric variable
// void setup()
// {
//   Serial.begin(9600);
// 	pinMode(led, OUTPUT); //set LED pin as output
// 	pinMode(sensor, INPUT); //set sensor pin as input
//   // Serial.println("Low");
// }
// void loop()
// {
// 	val = digitalRead(sensor); //Read the sensor
// 	if(val == LOW) //when magnetic field is detected, turn led on
// 	{
// 		digitalWrite(led, HIGH);
//     Serial.println(sensor);
// 	}
// 	else
// 	{
// 		digitalWrite(led, LOW);
//     Serial.println(sensor);
// 	}
//   // Serial.println("Low");
//   // delay(100);
// }

// int sensorPin = 2; // KY-003 sensor connected to digital pin 2
// int sensorValue; // variable to store the sensor value

// void setup() {
//   Serial.begin(9600); // start serial communication at 9600 bps
// }

// void loop() {
//   sensorValue = digitalRead(sensorPin); // read the sensor value
//   Serial.println(sensorValue); // print the sensor value to the serial monitor
//   //delay(1000); // wait for 1 second before reading the sensor again
// }

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


