#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial espSerial(2,3);

//variables ..........

float current_mA;
float loadvoltage;
float power_mW;
float luxRoom;
float luxVideo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Hello now we push data to ESP");
  espSerial.begin(115200);
  delay(5000);
}

void loop() {
  String data = readDataFromSerial();
  if(data.length() > 0){
    parseData(data, current_mA,loadvoltage,power_mW,luxRoom,luxVideo);
  }

  if(espSerial.available()){
    String data = espSerial.readStringUntil('\n');
    if (sscanf(data.c_str(), "%f,%f", &current_mA, &loadvoltage,&power_mW,power_mW) == 2) {
      Serial.print("Received current_mA: ");
      Serial.println(current_mA, 2); // 2 decimal places
      Serial.print("Received loadvoltage: ");
      Serial.println(loadvoltage, 2); 
      Serial.print("Received power_mW: ");
      Serial.println(power_mW, 2); // 2 decimal places
      Serial.print("Received luxRoom: ");
      Serial.println(luxRoom, 2); 
      Serial.print("Received luxVideo: ");
      Serial.println(luxVideo, 2); // 2 decimal places
    }
  }
  Serial.print("Current: ");
  Serial.print(current_mA);
  Serial.print(" mA, Voltage: ");
  Serial.print(loadvoltage);
  Serial.print(" V, Light1: ");
  Serial.print(power_mW);
  Serial.print(", Light2: ");
  Serial.println(luxRoom);
  Serial.print(", Light2: ");
  Serial.println(luxVideo);

}

String readDataFromSerial(){
  String data = "";
  while(espSerial.available()){
    char c = espSerial.read();
    if(c=='\n'){
      char c = espSerial.read();
      if(c == '\n'){
        break;
      }
      data += c;
    }
  }
  return data; 
}

void parseData(String data, float &current_mA,float &loadvoltage,float &power_mW,float &luxRoom,float &luxVideo){
  int commaIndex1 = data.indexOf(',');
  int commaIndex2,commaIndex3,commaIndex4;

  if(commaIndex1 != -1){
    commaIndex2 = data.indexOf(',',commaIndex1 +1);
    if(commaIndex2 != -1){
      commaIndex3 = data.indexOf(',',commaIndex2 + 1);
      if(commaIndex3 != -1){
        commaIndex4 = data.indexOf(',',commaIndex3+1);
        if(commaIndex4 != -1){
          current_mA = atof(data.substring(0, commaIndex1).c_str());
          loadvoltage = atof(data.substring(commaIndex1 + 1,commaIndex2).c_str());
          power_mW = atof(data.substring(commaIndex2 + 1,commaIndex3).c_str());
          luxRoom = atof(data.substring(commaIndex3 + 1, commaIndex4).c_str());
          luxVideo = atof(data.substring(commaIndex4 + 1).c_str());
        
        }
      }
    }
  }
}
