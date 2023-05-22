#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(17, 16); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11

int objectCount = 0; // Variable pour stocker le nombre d'objets détectés

#define MAX_OBJECTS 500  // Nombre maximal d'objets à stocker dans le tableau
HUSKYLENSResult objects[MAX_OBJECTS]; // Tableau pour stocker les objets détectés
int objectIndex = 0;  // Index pour le prochain objet à stocker

void printResult(HUSKYLENSResult result);

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }

    pinMode(0, INPUT_PULLUP); // Configurer le bouton sur le pin 0 en mode INPUT_PULLUP
    pinMode(25, OUTPUT); // Configurer la LED sur le pin 25 en mode OUTPUT
}

void loop() {
    if (digitalRead(0) == LOW) { // Si le bouton sur le pin 3 est pressé
        objectCount = 0; // Réinitialiser le compteur
        objectIndex = 0; // Réinitialiser l'index du tableau
        delay(50); // Délai pour éviter les rebonds
    }

    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);

            if (result.command == COMMAND_RETURN_BLOCK) {
                // Vérifier si les coordonnées du bloc sont les mêmes qu'un bloc déjà détecté
                bool isDuplicate = false;
                for (int i = 0; i < objectIndex; i++) {
                    if (abs(result.xCenter - objects[i].xCenter) <= 10 && abs(result.yCenter - objects[i].yCenter) <= 10) {
                        isDuplicate = true;
                        break;
                    }
                }

                if (!isDuplicate) {
                    // Ajouter le nouvel objet au tableau
                    objects[objectIndex] = result;
                    objectIndex++;
                    objectCount++; // Incrémenter le compteur pour chaque objet détecté

                    // Faire clignoter la LED 5 fois
                for (int i = 0; i < 5; i++) {
                  digitalWrite(LED_BUILTIN, HIGH);
                  delay(100);
                  digitalWrite(LED_BUILTIN, LOW);
                  delay(100);
                  
                }
                }
            }
        }    
        Serial.println(String() + F("Total Objects Detected: ") + objectCount); // Afficher le nombre d'objets détectés
    }
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}
