/*
   Créateur : Frantzen
   Date de la création : 03.10.2022
   But : Fonctionnement du capteur CO2 avec le registre

*/


#define STATUS_REG 0x00
#define MEAS_MODE_REG 0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA 0x05
#define NTC_REG 0x06
#define THRESHOLDS 0x10
#define BASELINE 0x11
#define HW_ID_REG 0x20
#define ERROR_ID_REG 0xE0
#define APP_START_REG 0xF4
#define SW_RESET 0xFF


#define CCS_811_ADDRESS 0x5A
#define GPIO_WAKE 0x5
#define DRIVE_MODE_IDLE 0x0
#define DRIVE_MODE_1SEC 0x10
#define DRIVE_MODE_10SEC 0x20
#define DRIVE_MODE_60SEC 0x30
#define INTERRUPT_DRIVEN 0x8
#define THRESHOLDS_ENABLED 0x4

u8 i2c_buff[8];
bool wake_gpio_enabled = true;
void i2c_write(u8 address, u8 register, u8 *tx_data_ptr, u8 length);
void i2c_read(u8 address, u8 *rx_data_ptr, u8 length);
void gpio_write(u8 gpio_id, u8 level);




#define MEASURE 13
#define WAKE3 27


#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(115200);
  
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  
  pinMode(WAKE3, OUTPUT);
  digitalWrite(WAKE3, LOW);

  Serial.println("CCS811 test");
  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
  }

  //calibrate temperature sensor
  //while (!ccs.available());
}

void loop() {
  if (ccs.available()) {
    //float temp = ccs.calculateTemperature();
    if (!ccs.readData()) {
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    }
    else {
      Serial.println("ERROR!");
    }
  }
  delay(500);
}
