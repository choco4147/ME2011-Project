#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Servo.h>

Servo srv;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(115200);
  bmp.begin_I2C();
  srv.attach(12);

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  pinMode(13,OUTPUT);
  pinMode(11, INPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  
  // a bunch of random variables i need, mostly for state detection
  // eg am i on the pad, launched, landed
  bool armed = false;
  bool launched = false;
  bool landed = false;
  int vote = 0;
  double pA = getA();
  double pS = 0;
  int LED = 0;
  int pos = 0;

  // records launch site alt, max alt and speed
  float asl = getA();
  float maxA = getA()-asl;
  float maxS = 0;

  // press button to arm for flight
  while(armed == false){
    digitalWrite(13,HIGH);
    if(digitalRead(11) == HIGH){armed=true;}
  }
  
  srv.write(180);
  delay(250);
  srv.write(0); 

  // on the pad, not launched. constantly runs launch detection code
  while(!launched){

    // if altitude or speed is increasing, vote to launch. otherwise vote = 0
    if(getA() > pA || getIAS() > pS){ vote = vote+1;}
    else { vote = 0;}

    delay(50);

    // super awful LED blink code
    LED = LED+1;
    if (LED==10){digitalWrite(13,HIGH);} 
    else if (LED == 20){digitalWrite(13,LOW); LED=0;}

    // if launch detected, set launched to true
    if(vote == 10) {launched = true; vote = 0;LED=0;}
    
  }

  // in the air, launched. responds to flight and runs landing detection code
  while (launched) {
    // update max speed and altitude
    if(getA()-asl > maxA){maxA = getA()-asl;}
    if(getIAS()>maxS){maxS = getIAS();}
    
    // landing detection
    if(getA() < pA && digitalRead(11) == HIGH){ vote = vote+1;}
    else { vote = 0;}
    if(vote>10){launched=false; landed=true;}
    delay(50);

    // super awful LED blink code
    if(LED==0){digitalWrite(13,LOW); LED = 1;} 
    else {digitalWrite(13,HIGH); LED = 0;}

    controls(getIAS(),getA()-asl);
  }

// on the ground, rocket has landed
  while (landed) {
    int t = 0;
    int h = 0;
    int te = 0;
    int o = 0;
    int temp = maxA;
    while (temp - 1000 >= 0) {t = t+1; temp = temp-1000;}
    while (temp - 100 >= 0) {h = h+1; temp = temp - 100;}
    while (temp - 10 >= 0) {te = te + 1; temp = temp - 10;}
    while (temp - 1 >= 0) { o = o+1; temp = temp-1;}

    while(true) {
      delay(7500);
      for(int i = 0; i < t; i = i+1) {
        digitalWrite(13,HIGH); delay(300); digitalWrite(13,LOW); delay(300);
      }
      delay(2000);
      for(int i = 0; i < h; i = i+1) {
        digitalWrite(13,HIGH); delay(300); digitalWrite(13,LOW); delay(300);
      }
      delay(2000);
      for(int i = 0; i < te; i = i+1) {
        digitalWrite(13,HIGH); delay(300); digitalWrite(13,LOW); delay(300);
      }
      delay(2000);
      for(int i = 0; i < o; i = i+1) {
        digitalWrite(13,HIGH); delay(300); digitalWrite(13,LOW); delay(300);
      }

      
    }
    
    
  }
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

float getIAS() {
  float d = 0.0765;
  float ias = sqrt((2 * 32.174 * getPD() * 144) / d);
  return ias;
}

// runs all my fancy controls code :)
void controls(float s, float a) {
  srv.write(s*180/600);
}
