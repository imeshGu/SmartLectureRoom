#include <SoftwareSerial.h>
SoftwareSerial TESTSerial(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Hello now we push data to ESP");
  TESTSerial.begin(115200);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  String incomingString = "";
  boolean stringReady = false;
  while(TESTSerial.available()){
    incomingString = TESTSerial.readString();
    stringReady = true;
  }
  if(stringReady){
    Serial.print("Received -" + incomingString);
  }
 
}
