#include <Wire.h>
#include <Adafruit_INA219.h>
#include <BH1750.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(2,3);
Adafruit_INA219 ina219;
BH1750 GY30;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial.begin(9600);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }
  Wire.begin();
  ina219.begin();
  GY30.begin();

  Serial.println("Measuring voltage and current with INA219 ...");
  Serial.println("Measuring Lux level");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Hello Worlds");     

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  float lux = GY30.readLightLevel();
  
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  byte dataToSend[12];
  memcpy(dataToSend, &current_mA, sizeof(current_mA));
  memcpy(dataToSend + sizeof(current_mA), &loadvoltage,sizeof(loadvoltage));
  memcpy(dataToSend + sizeof(current_mA) + sizeof(loadvoltage), &power_mW, sizeof(power_mW));
  memcpy(dataToSend + sizeof(current_mA) + sizeof(loadvoltage) + sizeof(power_mW), &lux, sizeof(lux));

  // Serial.println(shuntvoltage);
  // Serial.println(busvoltage);
  // Serial.println(current_mA);
  // Serial.println(power_mW);
  // Serial.println(loadvoltage);
  // Serial.println(lux);
  
  //send data 
  Serial.write(dataToSend,sizeof(dataToSend));
  delay(3000);
 
}
