// C++ code
//
/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

#define DISTpin 7 // output pin Distance Pin is attached to
#define PHOTOpin A5 // output pin photoPin is attached to

int pos_9 = 0;
int pos_6 = 0;
int pos_5 = 0;

Servo servo_9;
Servo servo_6;
Servo servo_5;

long cm = 0;


long readUltrasonicDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  servo_9.attach(9, 500, 2500);
  servo_6.attach(6, 500, 2500);
  servo_5.attach(5, 500, 2500);
  
  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize thermoPin
  pinMode(PHOTOpin, INPUT);

}

void loop()
{
  int sensor_bright = analogRead(PHOTOpin);
  
  if (sensor_bright > 600){
    
    cm = 0.01723 * readUltrasonicDistance(DISTpin, DISTpin);
    int slow = setSpeedWithDist(cm);
    
    Serial.println(slow);
    
    for (int pos = 0; pos <= 180; pos += 1) {
      pos_9 += 25;
      pos_6 = pos;
      pos_5 += slow;
      
      
      if (pos_9 > 180){
       	pos_9 = 180;        
      }
      if (pos_6 > 180){
       	pos_6 = 180;        
      }
      if (pos_5 > 180){
       	pos_5 = 180;        
      }
      
      
      servo_9.write(pos_9); //tremble
      servo_6.write(pos_6); //classique
      servo_5.write(pos_5);  
      
      
      delay(7);
      pos_9 -= 25;
      servo_9.write(pos_9);

      delay(10);
    }
    
    for (int pos = 180; pos >= 0; pos -= 1) {
      pos_9 += 25;
      pos_6 = pos;
      pos_5 -= slow;
      
      if (pos_9 < 0){
       	pos_9 = 0;        
      }
      if (pos_6 < 0){
       	pos_6 = 0;        
      }
      if (pos_5 < 0){
       	pos_5 = 0;        
      }
      
      servo_9.write(pos_9); //tremble
      servo_6.write(pos_6); //classique
      servo_5.write(pos_5); //dépend de la distance
      
      
      delay(5);
      pos_9 -= 25;
      servo_9.write(pos_9);

      delay(10);
    }
    
  }
}


long setSpeedWithDist(int dist){
 int speed = map(dist, 30, 340, 0, 10);
 if (dist < 30){
   speed = 0;
 }
  
  return speed;
  
}