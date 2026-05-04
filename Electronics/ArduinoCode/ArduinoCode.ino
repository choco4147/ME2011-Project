#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Servo.h>

Servo srv;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

int startTime = 0;



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
}





void loop() {
  // variables
  float asl = getA(); // launch site alt asl
  float maxA = 0; // saves flight max alt agl
  float maxS = 0; // saves flight max speed
  int maxServo = 70; // max servo angle
  int maxSpeed = 600; // max speed diff pressure sensor works at
  
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
  int t = millis() - startTime;
  // TEST MODE FOR ROBOT SHOW
  bool testing = true;

  if (testing == false) {
  bmp.performReading();
  return bmp.readAltitude(1013.25) / 3.281;
  }
  else {
    if(t<13000){ // flight
      return (sq(t-10800)/-33000)+3800;
    }
    if(13000<t && t<25600){ // parachute
      return 0.28*((t*-1)+13000)+3662;
    }
    if(25600<t) { // ground
      return 136;
    }
  }
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
  int t = millis() - startTime;
  // TESTING MODE FOR ROBOT SHOW
  bool testing = true;
  float ias;
  if (testing == false) {
  float d = 0.0765;
   ias = sqrt((2 * 32.174 * getPD() * 144) / d);
  }
  else{
    if(t<1500){ // boost
      Serial.print("boost");
      ias = sin(3.141592*t/3000)*575;
    }
    else if(1500<t && t<13000){ // coast
      Serial.print("coast");
      ias = 575-((1/13.2)*(t-1500));
    }
    else if(13000<t && t<25600) { // parachute
      Serial.print("chute");
      ias = -300;
    }
    else if(25600<t) { // ground
      Serial.print("ground");
      ias = 0;
    }
  }
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
  delay(100);
  srv.write(maxServo);
  delay(1000);
  srv.write(0);
  startTime = millis();
  Serial.print(millis());
  Serial.print(startTime);
  bool launched = false;
  int vote = 0;
  float pA = getA();
  float pS = 0;
  while(launched==false){
    
    // launch detect vote
    if(getA() > pA || getIAS() > pS) {vote = vote + 1;}
    else if (vote > 0) {vote =vote - 1;}
    else{ vote = 0;}
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
    if (abs(getIAS()) < 5 || abs(pA-getA()) < 0.5) {vote = vote+1;}
    else {vote = 0;}
    if (vote >= 10) {flying = false;}
    Serial.print(getA());
    Serial.print(" ");
    Serial.println(pA);
    // servo code - currently set to get constant acceleration
    // based on assumption that force of drag scales with v^2
    if(getIAS()>0){
      srv.write(maxServo);
      Serial.println("flying");
    }
    else{
      srv.write(maxServo*0.5);
      Serial.println("descending");
    }
    pA = getA();
    delay(50);
  }
}








// code for when the rocket has landed on the ground
void landed(int maxS, int maxA){
  srv.write(0);
  
  while(1==1){
    Serial.print("landed!");
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    delay(750);
  }
}
