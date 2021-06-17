// C++ code
//
#define DISTpin 7 // output pin Distance Pin is attached to
#define PHOTOpin A5 // output pin photoPin is attached to
#define ResetPin 4 // button to reset the game
#define StopPin 2 // button to stop the game for user

#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262


int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


int buttonStateReset = 0;
int lastButtonStateReset = 0;

int buttonStateStop = 0;
int lastButtonStateStop = 0;

int cm = 0;
unsigned long start;
unsigned long time;

bool lightOn = true;
int countLight = 0;

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
  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize thermoPin
  pinMode(PHOTOpin, INPUT);
  
  // Initialize buttons
  pinMode(ResetPin, INPUT);
  pinMode(StopPin, INPUT);
  
  start = millis();  
}

void loop()
{
  int sensor_bright = analogRead(PHOTOpin);
  if (sensor_bright < 500){
    if (lightOn == false){
      countLight += 1;
    }    
    lightOn = true;
  }
  if (sensor_bright > 500){
    lightOn = false;
  }
  
  buttonStateReset = digitalRead(ResetPin);
  if (buttonStateReset != lastButtonStateReset) {
    if (buttonStateReset == HIGH) {
   	  Serial.println("reset"); 
      start = millis();
      countLight = 0;
    }else{
      Serial.println("off");
    }
  }
  lastButtonStateReset = buttonStateReset;
  
  buttonStateStop = digitalRead(StopPin);
  
  if (buttonStateStop != lastButtonStateStop) {
    if (buttonStateStop == HIGH) {
   	  //Serial.println("stop");
      //send data to bdd
      
      time = millis() - start;
      Serial.print("temps avant d'appuyer : ");
      Serial.println(time);
      Serial.print("nombre de fois que la lumiere a ete allumee : ");
      Serial.println(countLight);
      delay(1000); //pour laisser le temps à l'envoi de données
    }else{
      Serial.println("off");
    }
  }
  
  cm = 0.01723 * readUltrasonicDistance(DISTpin, DISTpin);
  int volume = setVolume(cm);
  
  analogWrite(8, volume);
  
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
  delay(10000);
  lastButtonStateStop = buttonStateStop; 
}

long setVolume(int dist){
  int volume = map(dist, 30, 340, 0, 255);
 if (dist < 30){
   volume = 0;
 }
  
 return volume;
}

