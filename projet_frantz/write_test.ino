 /******************************************************************************
Ecriture de la mesure d'un capteur sur un fichier au format csv.
Etat : en cour de codage, non fonctionnel.
******************************************************************************/
#include <Wire.h>

//Commande du CCS811
#include <SparkFunCCS811.h> //Click here to get the library: http://librarymanager/All#SparkFun_CCS811

//Libraire d'écriture
#include <SPI.h>
#include <SD.h>

//Constantes
#define CCS811_ADDR_L 0x5B //Default I2C Address
#define CCS811_ADDR_H 0x5A //Alternate I2C Address

//Définition des entrées de nos capteurs

//U5
#define PIN_NOT_WAKE_3 27
#define PIN_NOT_INT_3 35
#define ADD3 12

//U4
#define PIN_NOT_WAKE_2 26
#define PIN_NOT_INT_2 32
#define ADD2 4

//U3
#define PIN_NOT_WAKE_1 16
#define PIN_NOT_INT_1 17
#define ADD1 2


#define SDA 21
#define SCL 22

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

//Création des objects

CCS811 U5(CCS811_ADDR_H);
CCS811 U4(CCS811_ADDR_H);
CCS811 U3(CCS811_ADDR_H);

File mesure;


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
  pinMode(PIN_NOT_WAKE_3, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_3, 1); //Start asleep
  
  pinMode(ADD2, OUTPUT);
  digitalWrite(ADD2, LOW);
  //Configure the wake line
  pinMode(PIN_NOT_WAKE_2, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_2, 1); //Start asleep
  
  pinMode(ADD1, OUTPUT);
  digitalWrite(ADD1, LOW);
  pinMode(PIN_NOT_WAKE_1, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_1, 1); //Start asleep
  
  Wire.begin(SDA,SCL);

  //Démarage du capteur 3 :

  //demarrage_capteur(U3, PIN_NOT_WAKE_1, PIN_NOT_INT_1, MODE_ALL_CCS);

  //Démarage du capteur 4 :

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

  /*

  digitalWrite(PIN_NOT_WAKE_2, 1); //Sleep
  
  //Saut de line pour faciliter la lecture
  Serial.println();Serial.println();

  //Démarage du capteur 5 :

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

  delay(100);
  digitalWrite(PIN_NOT_WAKE_3, 1); //Sleep

  //Saut de line pour faciliter la lecture
  Serial.println();Serial.println();
  */

  //Vérification de la présence d'une SD 

  
  Serial.print("Initializing µSD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("µSD initialization done.");

  


}
//---------------------------------------------------------------
void loop()
{
  

/*
  //Look for interrupt request from CCS811
  if (digitalRead(PIN_NOT_INT_1) == 0)
  {
    //Wake up the CCS811 logic engine
    digitalWrite(PIN_NOT_WAKE_1, 0);
    //Need to wait at least 50 us
    delay(1);
    //Interrupt signal caught, so cause the CCS811 to run its algorithm
    U3.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    Serial.print("U3_CO2[");
    Serial.print(U3.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000);
    Serial.print("]");
    Serial.println();

    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_1, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast
*/

  //Look for interrupt request from CCS811
  if (digitalRead(PIN_NOT_INT_2) == 0)
  {

    

    //Wake up the CCS811 logic engine
    digitalWrite(PIN_NOT_WAKE_2, 0);
    //Need to wait at least 50 us
    delay(1);
    //Interrupt signal caught, so cause the CCS811 to run its algorithm
    U4.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    mesure = SD.open("mesure.csv", FILE_WRITE);
    if(mesure) {
      mesure.print(millis()/1000);
      mesure.print(",");
      mesure.println(U4.getCO2()); // !!! BIEN PENSER A RETIRER LE LN ET LE METTRE SUR U5 POUR LA VERSION FINALE.
      Serial.print("succés de l'écriture");
    }else{
      Serial.println("echec de l'écriture");
    }
    mesure.close();
    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_2, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast

/*

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
    Serial.println();

    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_3, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast
  */
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
