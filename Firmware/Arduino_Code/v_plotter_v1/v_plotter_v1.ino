#include <ESP32Servo.h>
Servo myservo;    // erzeugt ein Servomotor-Objekt
                  // maximal können acht Servomotor-Objekte erzeugt werden

int pos = 0;      // Variable, die die Servoposition (Winkel) speichert

uint8_t leftStepPin = 23;
uint8_t leftDirPin = 19;

uint8_t rightStepPin = 21;
uint8_t rightDirPin = 22;

int servoPin = 26;

int steps = 4000; // you should increase this if you are using
                  // some of microstepping modes
int usDelay = 950;// minimal is 950 for full step mode and NEMA15 motor
                  // minimal is 35 for sixteenth step mode

                  
void setup() {
  Serial.begin(115200);
  pinMode(leftStepPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);
  pinMode(rightStepPin, OUTPUT);
  pinMode(rightDirPin, OUTPUT);
  //myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin);
}


void loop() {
  
  digitalWrite(leftDirPin, HIGH); // motor direction cw
  Serial.println("Left Motor Clockwise");
  for(int x = 0; x < steps; x++) {
    digitalWrite(leftStepPin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(leftStepPin, LOW);
    delayMicroseconds(usDelay);
  }
  delay(1000);
  digitalWrite(leftDirPin, LOW); // motor direction ccw
  Serial.println("Left Motor Counterclockwise");
  for(int x = 0; x < steps; x++) {
    digitalWrite(leftStepPin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(leftStepPin, LOW);
    delayMicroseconds(usDelay);
  }
  delay(1000);
  digitalWrite(rightDirPin, HIGH); // motor direction cw
  Serial.println("Right Motor Clockwise");
  for(int x = 0; x < (steps*10); x++) {
    digitalWrite(rightStepPin, HIGH);
    delayMicroseconds(usDelay/10);
    digitalWrite(rightStepPin, LOW);
    delayMicroseconds(usDelay/10);
  }
  delay(1000);
  digitalWrite(rightDirPin, LOW); // motor direction ccw
  Serial.println("Right Motor Counterclockwise");
  for(int x = 0; x < steps; x++) {
    digitalWrite(rightStepPin, HIGH);
    delayMicroseconds(usDelay/5);
    digitalWrite(rightStepPin, LOW);
    delayMicroseconds(usDelay/5);
  }
  delay(1000);
  
  Serial.println("Start of Servo Test");

  for(pos = 30; pos < 150; pos += 5) {  // von 30 bis 150 Grad, in Schritten von einem Grad
    myservo.write(pos);                   // sagt dem Servomotor, in welche Position sich drehen soll      
    delay(500);      // wartet 500 Millisekunden   
    Serial.println(pos);
  }    
  for(pos = 150; pos>=30; pos-=5) {     // und das gleiche zurück
    myservo.write(pos);
    delay(500);
    Serial.println(pos);
  }
}
