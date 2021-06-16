#include <Adafruit_NeoPixel.h>

#define PIN_LEFT 2	 // input pin Neopixel is attached to
#define PIN_RIGHT 4	 // input pin Neopixel is attached to
#define PHOTOpin A5 // output pin photoPin is attached to

#define NUMPIXELS 64 // number of neopixels in strip

#define DISTpin 7 // output pin Distance Pin is attached to

Adafruit_NeoPixel LEFT_EYE = Adafruit_NeoPixel(NUMPIXELS, PIN_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RIGHT_EYE = Adafruit_NeoPixel(NUMPIXELS, PIN_RIGHT, NEO_GRB + NEO_KHZ800);

int delayval = 1; // timing delay in milliseconds

int redColor = 255;
int greenColor = 0;
int blueColor = 0;

int cm = 0;

//base coord for eye
int a = 27; 
int b = 28;
int c = 35;
int d = 36;
int sequence [] = {0,1,1,2,2,2,2,1,1,1,1,3,3,2,2,2,2,4,4,4,4,1,1,1,1,3,3,2,2};
int x = 0;


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

void setup() {
  // Initialize the NeoPixel library.
  LEFT_EYE.begin();
  RIGHT_EYE.begin();
  
  Serial.begin(9600);
  // Initialize thermoPin
  pinMode(PHOTOpin, INPUT);
}

void loop() {
  int sensor_bright = analogRead(PHOTOpin);
  
  if (sensor_bright > 600){

    moove(sequence[x]);
    x += 1;
    if (x >= sizeof(sequence)){
      //print close eyes
      x = 0;
      a = 27; 
      b = 28;
      c = 35;
      d = 36;
    } 

	cm = 0.01723 * readUltrasonicDistance(DISTpin, DISTpin);
    setBrightWithDist(cm);



    for(int i=0; i<NUMPIXELS; i++){
      LEFT_EYE.setPixelColor(i, LEFT_EYE.Color(redColor, greenColor, blueColor));
      RIGHT_EYE.setPixelColor(i, RIGHT_EYE.Color(redColor, greenColor, blueColor));
    }
    LEFT_EYE.setPixelColor(a, LEFT_EYE.Color(0, 0, 0));
    LEFT_EYE.setPixelColor(b, LEFT_EYE.Color(0, 0, 0));
    LEFT_EYE.setPixelColor(c, LEFT_EYE.Color(0, 0, 0));
    LEFT_EYE.setPixelColor(d, LEFT_EYE.Color(0, 0, 0));

    RIGHT_EYE.setPixelColor(a, RIGHT_EYE.Color(0, 0, 0));
    RIGHT_EYE.setPixelColor(b, RIGHT_EYE.Color(0, 0, 0));
    RIGHT_EYE.setPixelColor(c, RIGHT_EYE.Color(0, 0, 0));
    RIGHT_EYE.setPixelColor(d, RIGHT_EYE.Color(0, 0, 0));



    // This sends the updated pixel color to the hardware.
    LEFT_EYE.show();
    RIGHT_EYE.show();

    // Delay for a period of time (in milliseconds).
    delay(delayval);
  }else{
    x = 0;
  }
}

void moove(int direction){
  switch (direction) {
    case 1:
      // right
      a += 1;
      b += 1;
      c += 1;
      d += 1;
      break;
    case 2:
      // left
      a -= 1;
      b -= 1;
      c -= 1;
      d -= 1;
      break;
    case 3:
      // up
      a -= 8;
      b -= 8;
      c -= 8;
      d -= 8;
      break;
    case 4:
      // right
      a += 8;
      b += 8;
      c += 8;
      d += 8;
      break;
    default:
      // nothing happen
      break;   
  }
  
}


void setBrightWithDist(int dist){
 int bright = map(dist, 30, 200, 0, 255);
  
  if (dist > 200){
   	bright = 200;
  }
  
 LEFT_EYE.setBrightness(bright);
 RIGHT_EYE.setBrightness(bright);
  
}