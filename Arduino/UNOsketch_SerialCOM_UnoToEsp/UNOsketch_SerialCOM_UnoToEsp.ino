//    Connection:
//
//    VCC -> 3V3 or 5V
//    GND -> GND
//    SCL -> SCL (A5 on Arduino Uno, Leonardo, etc or 21 on Mega and Due, on esp8266 free selectable)
//    SDA -> SDA (A4 on Arduino Uno, Leonardo, etc or 20 on Mega and Due, on esp8266 free selectable)
//    ADD -> (not connected) or GND
//
//    ADD pin is used to set sensor I2C address. If it has voltage greater or equal to
//    0.7VCC voltage (e.g. you've connected it to VCC) the sensor address will be
//    0x5C. In other case (if ADD voltage less than 0.7 * VCC) the sensor address will
//    be 0x23 (by default).

#include <Wire.h>

#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

// Power
#define BH1750_POWER_DOWN 0x00  // No active state
#define BH1750_POWER_ON 0x01  // Waiting for measurement command
#define BH1750_RESET 0x07  // Reset data register value - not accepted in POWER_DOWN mode

// Measurement Mode
#define CONTINUOUS_HIGH_RES_MODE 0x10  // Measurement at 1 lux resolution. Measurement time is approx 120ms
#define CONTINUOUS_HIGH_RES_MODE_2 0x11  // Measurement at 0.5 lux resolution. Measurement time is approx 120ms
#define CONTINUOUS_LOW_RES_MODE 0x13  // Measurement at 4 lux resolution. Measurement time is approx 16ms
#define ONE_TIME_HIGH_RES_MODE 0x20  // Measurement at 1 lux resolution. Measurement time is approx 120ms
#define ONE_TIME_HIGH_RES_MODE_2 0x21  // Measurement at 0.5 lux resolution. Measurement time is approx 120ms
#define ONE_TIME_LOW_RES_MODE 0x23  // Measurement at 4 lux resolution. Measurement time is approx 16ms

// I2C Address
#define BH1750_1_ADDRESS 0x23  // Sensor 1 connected to GND
#define BH1750_2_ADDRESS 0x5C  // Sensor 2 connected to VCC

// LED Blink
#define LED_PIN 13

// Definition of Variable
int16_t RawData;
int16_t SensorValue[2];
boolean blinkState = false;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200); // Baud Rate
  
  //current sensor
  ina219.begin();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  init_BH1750(BH1750_1_ADDRESS, CONTINUOUS_HIGH_RES_MODE);
  delay(120);
  RawData_BH1750(BH1750_1_ADDRESS);
  SensorValue[0] = RawData / 1.2;  

  init_BH1750(BH1750_2_ADDRESS, CONTINUOUS_HIGH_RES_MODE);
  delay(120);
  RawData_BH1750(BH1750_2_ADDRESS);
  SensorValue[1] = RawData / 1.2;

  ////////power sensor
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

  Serial.print("Video wall Lux Sensor_1 = "); Serial.print(SensorValue[0]);
  Serial.print("Room Lux | Sensor_2 = "); Serial.println(SensorValue[1]);

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

void init_BH1750(int ADDRESS, int MODE){
  //BH1750 Initializing & Reset
  Wire.beginTransmission(ADDRESS);
  Wire.write(MODE);  // PWR_MGMT_1 register
  Wire.endTransmission(true);
}

void RawData_BH1750(int ADDRESS){
  Wire.beginTransmission(ADDRESS);
  Wire.requestFrom(ADDRESS,2,true);  // request a total of 2 registers
  RawData = Wire.read() << 8 | Wire.read();  // Read Raw Data of BH1750
  Wire.endTransmission(true);
}
