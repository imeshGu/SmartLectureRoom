#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //Serial.print("Hello");
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }
  ina219.begin();
  //if (! ina219.begin()) {
  //  Serial.println("Failed to find INA219 chip");
  //  while (3) { delay(10); }
  //}

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello Worlds");     

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}
