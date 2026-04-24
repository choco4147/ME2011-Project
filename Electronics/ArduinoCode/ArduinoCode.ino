 
void setup() {
  Serial.begin(115200);
}

void loop() {

}

// gets pressure (psi)
float getP(){
  
}

// gets temperature (deg F) 
float getT() {
  
}

// gets pressure differential (psi) from differential pressure sensor
float getPD(){
  float vMin = 0.2;
  float vMax = 4.7;
  float pRange = 1.45038;
  int oPitot = analogRead(A0);
  float vPitot = oPitot*5.0/1023.0;
  float pDiff = pRange*(1-((vMax-vPitot)/(vMax-vMin)));
  if (pDiff < 0) {pDiff = 0;}
  return pDiff;
}
