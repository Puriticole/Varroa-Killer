 /******************************************************************************
  Wake from sleep and read interrupts

  Marshall Taylor @ SparkFun Electronics

  April 4, 2017

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library

  This example configures the nWAKE and nINT pins.
  The interrupt pin is configured to pull low when the data is
  ready to be collected.
  The wake pin is configured to enable the sensor during I2C communications

  Hardware Connections (Breakoutboard to Arduino):
  3.3V to 3.3V pin
  GND to GND pin
  SDA to A4
  SCL to A5
  NOT_INT to D6
  NOT_WAKE to D5 (For 5V arduinos, use resistor divider)
    D5---
         |
         R1 = 4.7K
         |
         --------NOT_WAKE
         |
         R2 = 4.7K
         |
        GND

  Resources:
  Uses Wire.h for i2c operation

  Development environment specifics:
  Arduino IDE 1.8.1

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).

  Please review the LICENSE.md file included with this example. If you have any questions
  or concerns with licensing, please contact techsupport@sparkfun.com.

  Distributed as-is; no warranty is given.
******************************************************************************/
#include <Wire.h>

#include <SparkFunCCS811.h> //Click here to get the library: http://librarymanager/All#SparkFun_CCS811

#define CCS811_ADDR_L 0x5B //Default I2C Address
#define CCS811_ADDR_H 0x5A //Alternate I2C Address

//Définition des entrées de nos capteurs
#define PIN_NOT_WAKE_3 27
#define PIN_NOT_INT_3 35

#define PIN_NOT_WAKE_2 26
#define PIN_NOT_INT_2 32

#define SDA 21
#define SCL 22

#define ADD3 12
#define ADD2 4

//Constante permettant la gestion de notre carte
#define MEASURE 13

CCS811 myCCS811_3(CCS811_ADDR_H);
CCS811 myCCS811_2(CCS811_ADDR_H);

bool alt = false;

long previousTime, currentTime;

//Global sensor object
//---------------------------------------------------------------
void setup()
{
  //Start the serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("...");

  //Alimentation du capteur
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);

  pinMode(ADD3, OUTPUT);
  digitalWrite(ADD3, LOW);

  pinMode(ADD2, OUTPUT);
  digitalWrite(ADD2, LOW);

  //Configure the wake line
  pinMode(PIN_NOT_WAKE_2, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_2, 1); //Start asleep

  pinMode(PIN_NOT_WAKE_3, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_3, 1); //Start asleep

  Wire.begin(SDA,SCL);

  //Démarage du capteur 2 :

  digitalWrite(PIN_NOT_WAKE_2, 0); //Demarrage

  //Affichages des codes d'erreurs : 

  //This begins the CCS811 sensor and prints error status of .beginWithStatus()
  CCS811Core::CCS811_Status_e returnCode_2 = myCCS811_2.beginWithStatus();
  Serial.print("CCS811_2 begin exited with: ");
  //Pass the error code to a function to print the results
  Serial.println(myCCS811_2.statusString(returnCode_2));

  //This sets the mode to 60 second reads, and prints returned error status.
  returnCode_2 = myCCS811_2.setDriveMode(1);
  Serial.print("Mode request exited with: ");
  Serial.println(myCCS811_2.statusString(returnCode_2));

  //Configure and enable the interrupt line,
  //then print error status
  pinMode(PIN_NOT_INT_2, INPUT_PULLUP);
  returnCode_2 = myCCS811_2.enableInterrupts();
  Serial.print("Interrupt configuation exited with: ");
  Serial.println(myCCS811_2.statusString(returnCode_2));
  
  delay(30);
  digitalWrite(PIN_NOT_WAKE_2, 1); //Sleep

  Serial.println();Serial.println();

  //Démarage du capteur 3 :

  digitalWrite(PIN_NOT_WAKE_3, 0); //Start

  //Affichages des codes d'erreurs : 

  //This begins the CCS811 sensor and prints error status of .beginWithStatus()
  CCS811Core::CCS811_Status_e returnCode_3 = myCCS811_3.beginWithStatus();
  Serial.print("CCS811_3 begin exited with: ");
  //Pass the error code to a function to print the results
  Serial.println(myCCS811_3.statusString(returnCode_3));

  //This sets the mode to 60 second reads, and prints returned error status.
  returnCode_3 = myCCS811_3.setDriveMode(1);
  Serial.print("Mode request exited with: ");
  Serial.println(myCCS811_3.statusString(returnCode_3));

  //Configure and enable the interrupt line,
  //then print error status
  pinMode(PIN_NOT_INT_3, INPUT_PULLUP);
  returnCode_3 = myCCS811_3.enableInterrupts();
  Serial.print("Interrupt configuation exited with: ");
  Serial.println(myCCS811_3.statusString(returnCode_3));

  delay(30);
  digitalWrite(PIN_NOT_WAKE_3, 1); //Sleep
}
//---------------------------------------------------------------
void loop()
{
  
  //Configuration du timer 

  currentTime = millis();
  if(currentTime-previousTime > 10000){
    alt = !alt;
    previousTime = currentTime;
  }
  
  if(alt == true) {
    digitalWrite(PIN_NOT_WAKE_3, 1); //Sleep
    digitalWrite(PIN_NOT_WAKE_2, 0); //Start
  }else{
    digitalWrite(PIN_NOT_WAKE_3, 0); //Start
    digitalWrite(PIN_NOT_WAKE_2, 1); //Sleep
  }

  //Look for interrupt request from CCS811
  if (digitalRead(PIN_NOT_INT_2) == 0)
  {
    //Wake up the CCS811 logic engine
    digitalWrite(PIN_NOT_WAKE_2, 0);
    //Need to wait at least 50 us
    delay(1);
    //Interrupt signal caught, so cause the CCS811 to run its algorithm
    myCCS811_2.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    Serial.print("CO2_2[");
    Serial.print(myCCS811_2.getCO2());
    Serial.print("] millis[");
    Serial.print(millis());
    Serial.print("]");
    Serial.println();

    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_2, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast



  //Look for interrupt request from CCS811
  if (digitalRead(PIN_NOT_INT_3) == 0)
  {
    //Wake up the CCS811 logic engine
    digitalWrite(PIN_NOT_WAKE_3, 0);
    //Need to wait at least 50 us
    delay(1);
    //Interrupt signal caught, so cause the CCS811 to run its algorithm
    myCCS811_3.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    Serial.print("CO2_3[");
    Serial.print(myCCS811_3.getCO2());
    Serial.print("] millis[");
    Serial.print(millis());
    Serial.print("]");
    Serial.println();

    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_3, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast
}

//printSensorError gets, clears, then prints the errors
//saved within the error register.
void printSensorError()
{
  uint8_t error = myCCS811_3.getErrorRegister();

  if (error == 0xFF) //comm error
  {
    Serial.println("Failed to get ERROR_ID register.");
  }
  else
  {
    Serial.print("Error: ");
    if (error & 1 << 5)
      Serial.print("HeaterSupply");
    if (error & 1 << 4)
      Serial.print("HeaterFault");
    if (error & 1 << 3)
      Serial.print("MaxResistance");
    if (error & 1 << 2)
      Serial.print("MeasModeInvalid");
    if (error & 1 << 1)
      Serial.print("ReadRegInvalid");
    if (error & 1 << 0)
      Serial.print("MsgInvalid");
    Serial.println();
  }
}
