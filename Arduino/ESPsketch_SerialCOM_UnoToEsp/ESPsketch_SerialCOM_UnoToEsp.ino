#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial espSerial(2,3);

const char* ssid = "";
const char* password = "";
const char* server = "";
const int port = 80;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Hello now we push data to ESP");
  espSerial.begin(115200);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte ReceivingData[12];
  if(espSerial.available() >= sizeof(ReceivingData)){
    espSerial.readBytes(ReceivingData, sizeof(ReceivingData));
    
    float current_mA;
    float loadvoltage;
    float power_mW;
    int lux1;

    memcpy(&current_mA,ReceivingData,sizeof(current_mA));
    memcpy(&loadvoltage, ReceivingData + sizeof(current_mA), sizeof(loadvoltage));
    memcpy(&power_mW, ReceivingData + sizeof(current_mA) + sizeof(loadvoltage), sizeof(&power_mW));
    memcpy(&lux1, ReceivingData + sizeof(current_mA) + sizeof(loadvoltage) + sizeof(lux1), sizeof(&lux1));
 

  Serial.print("Current: ");
  Serial.print(current_mA);
  Serial.print(" mA, Voltage: ");
  Serial.print(loadvoltage);
  Serial.print(" V, Light1: ");
  Serial.print(power_mW);
  Serial.print(", Light2: ");
  Serial.println(lux1);
  // String incomingString = "";
  // boolean stringReady = false;
  // while(TESTSerial.available()){
  //   incomingString = TESTSerial.readString();
  //   stringReady = true;
  // }
  // if(stringReady){
  //   for(int i=0,i<=6,i++){
  //     String shuntvoltage = 0;
  //     String busvoltage = 0;
  //     String current_mA = 0;
  //     String loadvoltage = 0;
  //     String power_mW = 0;
  //     String lux = GY30.readLightLevel();
  //   }
  //   Serial.print("Received -" + incomingString);
  // }
  }
}

