//LCD and Ultrasonic sensor code Neel Bullywon
/*
*/
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define trigPin 10 // (Trigger connects to digital pin 10.)
#define echoPin 9 // (Echo connects to digital pin 9.)
//define led pins
#define greenLed 0
#define yellowLed 1
#define redLed 13
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Covid Monitor");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}
void loop() {
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
// print the number of seconds since reset:
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance=(duration/2) / 29.2;
  delay (200);
  lcd.print(distance);

  if (distance>250){
    digitalWrite(greenLed, HIGH); 
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
  }

  if (distance<250 && distance>200){
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
  }

  if (distance<200){
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
  }
}