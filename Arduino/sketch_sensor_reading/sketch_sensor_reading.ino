#include <Wire.h>
#include <Adafruit_INA219.h>
#include <BH1750.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//Adafruit_INA219 ina219;
BH1750 lightSensor;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //Serial.print("Hello");
  Serial.begin(9600);
  

  Wire.begin();
  // ina219.begin();
  Serial.println("Initialize");

  lightSensor.begin();
  Serial.println("Measuring Lux level");

  // lightSensor1.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  // lightSensor2.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

  //if (! ina219.begin()) {
  //  Serial.println("Failed to find INA219 chip");
  //  while (3) { delay(10); }
  //}

  Serial.println("Measuring voltage and current with INA219 ...");
  Serial.println("Measuring Lux level");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello Worlds");     

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  
  float lux = lightSensor.readLightLevel();
  // float lightLevel1 = lightSensor1.readLightLevel();
  // float lightLevel2 = lightSensor2.readLightLevel();
  
  // shuntvoltage = ina219.getShuntVoltage_mV();
  // busvoltage = ina219.getBusVoltage_V();
  // current_mA = ina219.getCurrent_mA();
  // power_mW = ina219.getPower_mW();
  // loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  //light sensor
  Serial.print("Sensor1: ");
  Serial.print(lux);
  Serial.print(" Sensor2: ");
  Serial.print(lux);
  Serial.println();

  // //power sencor
  // Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  // Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  // Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  // Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  // Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  // Serial.println("");
  //Serial.println((String)"Light = " + lux + "lx'");

  delay(3000);
}
