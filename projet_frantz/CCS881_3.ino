 /******************************************************************************
  Wake from sleep and read interrupts

  Marshall Taylor @ SparkFun Electronics

  April 4, 2017

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library

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

/*
 * Définition du mode de mesure des capteurs
 * Mode 0 = Idle
 * Mode 1 = 1s
 * Mode 2 = 10s
 * Mode 3 = 60s
 * Mode 4 = 250ms
 */
#define MODE_ALL_CCS 1

//Constante permettant la gestion de notre carte
#define MEASURE 13

CCS811 U5(CCS811_ADDR_H);
CCS811 U4(CCS811_ADDR_H);

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
  CCS811Core::CCS811_Status_e returnCode_2 = U4.beginWithStatus();
  Serial.print("CCS811_2 begin exited with: ");
  //Pass the error code to a function to print the results
  Serial.println(U4.statusString(returnCode_2));

  //Mode 
  returnCode_2 = U4.setDriveMode(MODE_ALL_CCS);
  Serial.print("Mode request exited with: ");
  Serial.println(U4.statusString(returnCode_2));

  //Configure and enable the interrupt line,
  //then print error status
  pinMode(PIN_NOT_INT_2, INPUT_PULLUP);
  returnCode_2 = U4.enableInterrupts();
  Serial.print("Interrupt configuation exited with: ");
  Serial.println(U4.statusString(returnCode_2));


  //Delay qui sera repercuté entre les deux mesures
  delay(100);

  digitalWrite(PIN_NOT_WAKE_2, 1); //Sleep
  
  //Saut de line pour faciliter la lecture
  Serial.println();Serial.println();

  //Démarage du capteur 3 :

  digitalWrite(PIN_NOT_WAKE_3, 0); //Start

  //Affichages des codes d'erreurs : 

  //This begins the CCS811 sensor and prints error status of .beginWithStatus()
  CCS811Core::CCS811_Status_e returnCode_3 = U5.beginWithStatus();
  Serial.print("CCS811_3 begin exited with: ");
  //Pass the error code to a function to print the results
  Serial.println(U5.statusString(returnCode_3));

  //Mode
  returnCode_3 = U5.setDriveMode(MODE_ALL_CCS);
  Serial.print("Mode request exited with: ");
  Serial.println(U5.statusString(returnCode_3));

  //Configure and enable the interrupt line,
  //then print error status
  pinMode(PIN_NOT_INT_3, INPUT_PULLUP);
  returnCode_3 = U5.enableInterrupts();
  Serial.print("Interrupt configuation exited with: ");
  Serial.println(U5.statusString(returnCode_3));

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
    U4.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    Serial.print("U4_CO2[");
    Serial.print(U4.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000);
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
    U5.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    Serial.print("U5_CO2[");
    Serial.print(U5.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000.0);
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
  uint8_t error = U5.getErrorRegister();

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
