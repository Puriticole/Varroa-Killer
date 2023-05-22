/*
   Créateur : Frantzen
   Date de la création : 02.09.2022
   But : Faire fonctionner le capteru CO2 sur la carte.

*/

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
