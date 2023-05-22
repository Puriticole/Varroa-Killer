/*
 *  Programme de test des 3 capteurs de CO2 avec ecriture des résultats sur carte SD
 */


#define DEBUG // A commenter en version finale -- permet d'afficher les taux de CO2 dans le port Série
//#define DEBUG_FICHIER // A commenter en version finale -- permet l'affichage de la bonne exécutions des fonctions relative au fichier, très poluant.


#include <Wire.h>

#include <SparkFunCCS811.h> //Click here to get the library: http://librarymanager/All#SparkFun_CCS811 //Capteurs CO2

#define CCS811_ADDR_L 0x5B //Default I2C Address
#define CCS811_ADDR_H 0x5A //Alternate I2C Address

//Définition des entrées de nos capteurs

//U5
#define PIN_NOT_WAKE_3 27 //Permet de commander l'endormissement du capteur
#define PIN_NOT_INT_3 35 //Pin d'intéruption, à observer  pour connaitre quand le capteur à fini son timer, cf MODE_ALL_CCS
#define ADD3 12 //Pin d'adresse, si valeur LOW = Alternative adresss, si HIGH = default Adress

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
#define MODE_ALL_CCS 2

//Déclartion des objets capteurs pour l'utilisation de la lib SparkFunCCS811

CCS811 U5(CCS811_ADDR_H);
CCS811 U4(CCS811_ADDR_H);
CCS811 U3(CCS811_ADDR_H);



//Communication SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"

//Définition des port utilisé par le BS SPI

#define MISO   19
#define MOSI   23
#define SCLK   18
#define CS     33


#define MESURE 13 //TRES IMPORTANT -- Gestion de l'alimentation des capteurs
#define PROGRAMME 0 //Fonctionne en PULL UP, résistance de tirage haut. Quand appui  IO0 = GND. -- Pour arréter la mesure


bool stoppen_mesure = false; //-- Pour arréter la mesure



/*
 * Permet de rajouter une virgule dans le corps du fichier csv donné en argurment.
 * 
 */
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

/*
 * Création du fichier
 */


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

/*
 * Permet de rajouter un texte en const char au coprs du fichier à la fin de celui-ci.
 * 
 */

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

/*
 * Affiche le fichier dans le port Série.
 */


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

    //Increment boot number and print it every reboot -- pour nom dynamique des fichier de mesure non fonctionnel
    //++bootCount;

    //Alimentation de l'ensemble des capteurs
    pinMode(MESURE, OUTPUT);
    digitalWrite(MESURE, HIGH);

    //Gestion du bouton PROG -- arrêt de la mesure
    pinMode(PROGRAMME, INPUT);


    Serial.begin(115200);
    SPI.begin(SCLK,MISO,MOSI,CS); //déclaration des pins utilisés par le BUS SPI, car valeur de base ne colle pas avec notre besoin

    //Retour Série pour confirmation de présence d'une Carte SD
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


  //aide à la lecture dans port Série
  Serial.println("############# INITIALISATION DE U3 ###############");

  //Démarrage du capteur 3 :
  
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

  digitalWrite(PIN_NOT_WAKE_1, 1); //Sleep

  //Delay qui sera repercuté entre les deux mesures
  delay(500);

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

  digitalWrite(PIN_NOT_WAKE_2, 1); //Sleep

  //Delay qui sera repercuté entre les deux mesures
  delay(500);
  
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

  
  digitalWrite(PIN_NOT_WAKE_3, 1); //Sleep

  delay(500);

  //Saut de line pour faciliter la lecture
  Serial.println();Serial.println();


  //Création du fichier

  //Pour la mobilitée du nom ne fontionne pas
//  char cstr[16];
//
//  nom_fichier = nom_fichier + itoa(bootCount, cstr, 10);

    /*
     * Création de trois fichiers de mesure ayant le même corps pour concaténation finale (à réaliser par l'utilisateur sur un logiciel de type calc ou Excel.
     * Structure du fichier :
     * TEMPS (s) | CO2 U3 | TVOC U3 | CO2 U4 | TVOC U4 | CO2 U5 | TVOC U5 
     * 
     * Les | sont des ,
     * 
     * Idée d'optimisation : pourrait faire l'objet d'une fonction.
     * 
     */

    createFile(SD, "/mesure_capteur1.csv");

    appendFile(SD, "/mesure_capteur1.csv", "Temps (s)");
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "CO2 U3");
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "TVOC U3");
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "CO2 U4");
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "TVOC U4");
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "CO2 U5");
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "TVOC U5");
    appendFile(SD, "/mesure_capteur1.csv", "\n");

    createFile(SD, "/mesure_capteur2.csv");


    appendFile(SD, "/mesure_capteur2.csv", "Temps (s)");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "CO2 U3");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "TVOC U3");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "CO2 U4");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "TVOC U4");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "CO2 U5");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "TVOC U5");
    appendFile(SD, "/mesure_capteur2.csv", "\n");


    createFile(SD, "/mesure_capteur3.csv");

    appendFile(SD, "/mesure_capteur3.csv", "Temps (s)");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "CO2 U3");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "TVOC U3");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "CO2 U4");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "TVOC U4");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "CO2 U5");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "TVOC U5");
    appendFile(SD, "/mesure_capteur3.csv", "\n");


    
    Serial.println(); //Amériolartion de la lisibilité du port Série.

}



void loop() {
  // put your main code here, to run repeatedly:
  if(!stoppen_mesure){ // == premier itération du porgramme, car après bloqué dans la boucle while
    Serial.println("###### DEBUT DE LA MESURE ######");
  }
  
  while(!stoppen_mesure){ // tant que la mesure n'est pas arrété, on mesure.

  /*
   * Pourrait faire l'objet du développement d'une fonction ou plusieurs, car même code pour les 3 capteurs (à part quelques attributs)
   * Je vais seulement commenter le premier bloc car c'est la même logique ensuite
   */
   
  if (digitalRead(PIN_NOT_INT_1) == 0) //Observation de la pin d'interuption, passe à 0 quand le capteur à fini de dormir.
  {
    //Wake up the CCS811 logic engine
    digitalWrite(PIN_NOT_WAKE_1, 0); //Permet d'alimenter entièrement le capteur / partie logique
    //Need to wait at least 50 us
    delay(1);
    //Interrupt signal caught, so cause the CCS811 to run its algorithm
    U3.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    
    #ifdef DEBUG //Affiche dans le port Série le taux de CO2 et le coup d'horloge depuis le démarage du programme
    Serial.print("U3_CO2[");
    Serial.print(U3.getCO2());
    Serial.print("] s[");
    Serial.print(millis()/1000);
    Serial.print("]");
    Serial.println();
    #endif

    //Déclation des valeurs pour écriture dans le fichier -- nécéssité de conversion.
    int temps = millis()/1000; //Pour avoir un temps en seconde
    int co2 = U3.getCO2();
    int TVOC = U3.getTVOC();
    char cstr[16];
     
    appendFile(SD, "/mesure_capteur1.csv", itoa(temps, cstr, 10)); //Fonction ITOA permet de convertir un int en const char.
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", itoa(co2, cstr, 10));
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", itoa(TVOC, cstr, 10));
    appendComma(SD, "/mesure_capteur1.csv");
    appendFile(SD, "/mesure_capteur1.csv", "\n"); //retour à la ligne pour écrire une nouvelle ligne comme voulue dans le protocole csv.

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

    appendFile(SD, "/mesure_capteur2.csv", itoa(temps, cstr, 10));
    appendComma(SD, "/mesure_capteur2.csv"); //Espace pour concatanation
    appendComma(SD, "/mesure_capteur2.csv");
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", itoa(co2, cstr, 10));
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", itoa(TVOC, cstr, 10));
    appendComma(SD, "/mesure_capteur2.csv");
    appendFile(SD, "/mesure_capteur2.csv", "\n");


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

    appendFile(SD, "/mesure_capteur3.csv", itoa(temps, cstr, 10));
    appendComma(SD, "/mesure_capteur3.csv"); //Espace pour concatanation
    appendComma(SD, "/mesure_capteur3.csv");
    appendComma(SD, "/mesure_capteur3.csv");
    appendComma(SD, "/mesure_capteur3.csv");
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", itoa(co2, cstr, 10));
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", itoa(TVOC, cstr, 10));
    appendComma(SD, "/mesure_capteur3.csv");
    appendFile(SD, "/mesure_capteur3.csv", "\n");


    //Now put the CCS811's logic engine to sleep
    digitalWrite(PIN_NOT_WAKE_3, 1);
    //Need to be asleep for at least 20 us
    delay(1);
  }
  delay(1); //cycle kinda fast

   if(!digitalRead(PROGRAMME)){ //Observation du bouton pour arrêt de mesure.
    stoppen_mesure = true;
    Serial.println("###### ARRET DE LA MESURE ######");
  }
  }    
  }
  
