//Covid 19 Distance Sensor on Arduino
//By Neel Bullywon
//Computer Engineering TEJ4M1
//A Covid 19 Distance Sensor made on Arduino using C++. 
//Made by using an LCD and an Ultrasonic Sensor to locate 
//a person's distance and check if they are within a safe distance 
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

//define piezo
#define piezo 8
#define NOTE_C4 262

// notes in the melody:
int melody[] = {
NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
8
};

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
   // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
// to calculate the note duration, take one second
// divided by the note type.
//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
// to distinguish the notes, set a minimum time between them.
// the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
// stop the tone playing:
    noTone(8);
  }
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
    lcd.print("     Safe    ");
  }

  if (distance<250 && distance>200){
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    lcd.print(" Caution ");
    
  }

  if (distance<200){
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    lcd.print("  Warning  ");
    tone(piezo, 200, 500);
  }
}
