
/*
 *  Programme de test des 3 capteurs de CO2 avec ecriture des résultats sur carte SD
 */


#define DEBUG // A commenter en version finale 
//#define DEBUG_FICHIER // A commenter en version finale 


#include <Wire.h>

#include <SparkFunCCS811.h> //Click here to get the library: http://librarymanager/All#SparkFun_CCS811

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

CCS811 U5(CCS811_ADDR_H);
CCS811 U4(CCS811_ADDR_H);
CCS811 U3(CCS811_ADDR_H);



//Communication SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define MISO   19
#define MOSI   23
#define SCLK   18
#define CS     33


#define MESURE 13
#define PROGRAMME 0 //Fonctionne en PULL UP, résistance de tirage haut. Quand appui  IO0 = GND. 


RTC_DATA_ATTR int bootCount = 0;
String nom_fichier = "/mesure";

bool stoppen_mesure = false;


void appendComma(fs::FS &fs, const char * path){
  #ifdef DEBUG_FICHIER
    Serial.printf("Appending comma to file: %s\n", path);
    #endif

    File file = fs.open(path, FILE_APPEND);

    #ifdef DEBUG_FICHIER
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    #endif
    if(file.print(";")){
      #ifdef DEBUG_FICHIER
        Serial.println("Comma append");
      #endif
    } else {
      #ifdef DEBUG_FICHIER
        Serial.println("Append failed");
      #endif
    }
    file.close();
}


void createFile(fs::FS &fs, const char * path){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    #ifdef DEBUG_FICHIER
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    #endif
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  #ifdef DEBUG_FICHIER
    Serial.printf("Appending to file: %s\n", path);
  #endif
    File file = fs.open(path, FILE_APPEND);
   #ifdef DEBUG_FICHIER
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    #endif
    if(file.print(message)){
      #ifdef DEBUG_FICHIER
        Serial.println("Message appended");
        #endif
    } else {
      #ifdef DEBUG_FICHIER
        Serial.println("Append failed");
       #endif
    }
    file.close();
}



void readFile(fs::FS &fs, const char * path){
  #ifdef DEBUG_FICHIER
    Serial.printf("Reading file: %s\n", path);
    #endif

    File file = fs.open(path);
    if(!file){
      #ifdef DEBUG_FICHIER
        Serial.println("Failed to open file for reading");
       #endif
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}


void setup() {

    //Increment boot number and print it every reboot
    ++bootCount;

    //Alimentation du lecteur SD
    pinMode(MESURE, OUTPUT);
    digitalWrite(MESURE, HIGH);

    //Gestion du bouton PROG
    pinMode(PROGRAMME, INPUT);


    Serial.begin(115200);
    SPI.begin(SCLK,MISO,MOSI,CS);


    if(!SD.begin(CS)){
        Serial.println("Card Mount Failed");
   }
   
   
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }


  pinMode(ADD1, OUTPUT);
  digitalWrite(ADD1, LOW);
  pinMode(PIN_NOT_WAKE_1, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_1, 1); //Start asleep

  pinMode(ADD2, OUTPUT);
  digitalWrite(ADD2, LOW);
  //Configure the wake line
  pinMode(PIN_NOT_WAKE_2, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_2, 1); //Start asleep

  pinMode(ADD3, OUTPUT);
  digitalWrite(ADD3, LOW);
  pinMode(PIN_NOT_WAKE_3, OUTPUT);
  digitalWrite(PIN_NOT_WAKE_3, 1); //Start asleep
 
  
  Wire.begin(SDA,SCL);

  //Démarage du capteur 3 :

  Serial.println("############# INITIALISATION DE U3 ###############");
  
  digitalWrite(PIN_NOT_WAKE_1, 0); //Start

  //Affichages des codes d'erreurs : 
  //This begins the CCS811 sensor and prints error status of .beginWithStatus()
  CCS811Core::CCS811_Status_e returnCode_1 = U3.beginWithStatus();
  Serial.print("CCS811_3 begin exited with: ");
  //Pass the error code to a function to print the results
  Serial.println(U3.statusString(returnCode_1));

  //Mode
  returnCode_1 = U3.setDriveMode(MODE_ALL_CCS);
  Serial.print("Mode request exited with: ");
  Serial.println(U3.statusString(returnCode_1));

  //Configure and enable the interrupt line,
  //then print error status
  pinMode(PIN_NOT_INT_1, INPUT_PULLUP);
  returnCode_1 = U3.enableInterrupts();
  Serial.print("Interrupt configuation exited with: ");
  Serial.println(U3.statusString(returnCode_1));

  delay(100);
  digitalWrite(PIN_NOT_WAKE_1, 1); //Sleep


  //Démarage du capteur 4 :

  Serial.println("############# INITIALISATION DE U4 ###############");

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
  
  //Démarage du capteur 5 :

  Serial.println("############# INITIALISATION DE U5 ###############");

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


  //Création du fichier

  //Pour la mobilitée du nom nne fontionne pas
//  char cstr[16];
//
//  nom_fichier = nom_fichier + itoa(bootCount, cstr, 10);

    createFile(SD, "/mesure1.csv");

    appendFile(SD, "/mesure1.csv", "Temps (s)");
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "CO2 U3");
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "TVOC U3");
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "CO2 U4");
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "TVOC U4");
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "CO2 U5");
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "TVOC U5");
    appendFile(SD, "/mesure1.csv", "\n");

    readFile(SD, "/mesure1.csv");
    Serial.println();

}



void loop() {
  // put your main code here, to run repeatedly:

Serial.println("###### DEBUT DE LA MESURE ######");

  while(!stoppen_mesure){

    //Look for interrupt request from CCS811
  if (digitalRead(PIN_NOT_INT_1) == 0)
  {
    //Wake up the CCS811 logic engine
    digitalWrite(PIN_NOT_WAKE_1, 0);
    //Need to wait at least 50 us
    delay(1);
    //Interrupt signal caught, so cause the CCS811 to run its algorithm
    U3.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    
    #ifdef DEBUG
    Serial.print("U3_CO2[");
    Serial.print(U3.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000);
    Serial.print("]");
    Serial.println();
    #endif
    
    int temps = millis()/1000;
    int co2 = U3.getCO2();
    int TVOC = U3.getTVOC();
    char cstr[16];
     
    appendFile(SD, "/mesure1.csv", itoa(temps, cstr, 10));
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", itoa(co2, cstr, 10));
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", itoa(TVOC, cstr, 10));
    appendComma(SD, "/mesure1.csv");

    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_1, 1);
    //Need to be asleep for at least 20 us
    delay(1);
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
    
    #ifdef DEBUG
    Serial.print("U4_CO2[");
    Serial.print(U4.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000);
    Serial.print("]");
    Serial.println();
    #endif

    int temps = millis()/1000;
    int co2 = U4.getCO2();
    int TVOC = U4.getTVOC();
    char cstr[16];

    appendFile(SD, "/mesure1.csv", itoa(co2, cstr, 10));
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", itoa(TVOC, cstr, 10));
    appendComma(SD, "/mesure1.csv");

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

    #ifdef DEBUG
    Serial.print("U5_CO2[");
    Serial.print(U5.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000.0);
    Serial.print("]");
    Serial.println();
    Serial.println();
    #endif

    int temps = millis()/1000;
    int co2 = U5.getCO2();
    int TVOC = U5.getTVOC();
    char cstr[16];

    appendFile(SD, "/mesure1.csv", itoa(co2, cstr, 10));
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", itoa(TVOC, cstr, 10));
    appendComma(SD, "/mesure1.csv");
    appendFile(SD, "/mesure1.csv", "\n");

    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_3, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast

   if(!digitalRead(PROGRAMME)){
    stoppen_mesure = true;
    Serial.println("###### ARRET DE LA MESURE ######");
  }
  }    
  }
  
