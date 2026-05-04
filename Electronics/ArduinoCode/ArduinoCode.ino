#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Servo.h>

Servo srv;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;





void setup() {
  // begin serial and i2c stuff
  Serial.begin(115200);
  bmp.begin_I2C();
  srv.attach(12);

  // sets oversampling for the diff pressure sensor
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // define pins
  pinMode(13,OUTPUT); // watchdog LED
  pinMode(11, INPUT); // button
  pinMode(10,OUTPUT);
}





void loop() {
  // variables
  float asl = getA(); // launch site alt asl
  float maxA = 0; // saves flight max alt agl
  float maxS = 0; // saves flight max speed
  int maxServo = 90; // max servo angle
  int maxSpeed = 800; // max speed diff pressure sensor works at
  
  // state functions
  pad(maxServo);
  flying(asl,maxServo,maxSpeed);
  landed(round(maxS),round(maxA));
}





// gets pressure (psi)
float getP() {
  bmp.performReading();
  return (bmp.pressure / 6895);
}





// gets temperature (deg F)
float getT() {
  bmp.performReading();
  return (bmp.temperature * 9 / 5) + 32;
}





// gets altitude asl (ft)
float getA() {
  bmp.performReading();
  return bmp.readAltitude(1013.25) / 3.281;
}





// gets pressure differential (psi) from differential pressure sensor
float getPD() {
  float vMin = 0.2;
  float vMax = 4.7;
  float pRange = 1.45038;
  int oPitot = analogRead(A0);
  float vPitot = oPitot * 5.0 / 1023.0;
  float pDiff = pRange * (1 - ((vMax - vPitot) / (vMax - vMin)));
  if (pDiff < 0) {
    pDiff = 0;
  }
  return pDiff;
}





// calculates inducated airspeed
float getIAS() {
  float d = 0.0765;
  float ias = sqrt((2 * 32.174 * getPD() * 144) / d);
  return ias;
}








// code for when the rocket is waiting for launch on the pad
void pad(int maxServo) {
  // waiting to be armed, watchdog blink
  while(digitalRead(11)==LOW) {
    // blinks LEDS in watchdog pattern
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(750);
  }
  
  // armed, waiting on launch detect
  digitalWrite(13,LOW);
  srv.write(maxServo);
  delay(350);
  srv.write(0);
  bool launched = false;
  int vote = 0;
  float pA = getA();
  float pS = 0;
  while(launched==false){
    
    // launch detect vote
    if(getA() > pA || getIAS() > pS) {vote = vote + 1;}
    else{vote = 0;}
    if(vote >= 10){launched=true;}
    pA = getA();
    pS = getIAS();
    delay(50);
  }
}








// code for when the rocket is flying in the air
void flying(float asl, int maxServo, int maxSpeed) {
  // defining variables
  bool flying = true;
  float maxA = 0;
  float maxS = 0;
  float pA = getA();
  float pS = 0;
  int vote = 0;
  
  while(flying) {
    // update max speed and altitude
    if(getA()-asl > maxA) {maxA = getA()-asl;}
    if(getIAS() > maxS) {maxS = getIAS();}

    // landing detect vote
    if (abs(getIAS()) < 5 || abs(pA-getA()) < 5) {vote = vote+1;}
    else {vote = 0;}
    if (vote >= 10) {flying = false;}

    // servo code - currently set to get constant acceleration
    // based on assumption that force of drag scales with v^2
    float servoState = ((float)(maxSpeed^2)-(getIAS()^2))/((float)maxSpeed^2);
    srv.write(servoState*maxServo);

    delay(50);
  }
}








// code for when the rocket has landed on the ground
void landed(int maxS, int maxA){
  
}
