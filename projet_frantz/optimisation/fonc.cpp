#include "fonc.h"

void declaration_adress(int add){
  pinMode(add, OUTPUT);
  digitalWrite(add, LOW);
}


void demarrage_capteur(CCS811 U, int pinWake, int pinInt, int modeFonc){

  digitalWrite(pinWake, 0); //Start

  //Affichages des codes d'erreurs : 

  //This begins the CCS811 sensor and prints error status of .beginWithStatus()
  CCS811Core::CCS811_Status_e returnCode = U.beginWithStatus();
  Serial.print("CCS811_3 begin exited with: ");
  //Pass the error code to a function to print the results
  Serial.println(U.statusString(returnCode));

  //Mode
  returnCode = U.setDriveMode(modeFonc);
  Serial.print("Mode request exited with: ");
  Serial.println(U.statusString(returnCode));

  //Configure and enable the interrupt line,
  //then print error status
  pinMode(pinInt, INPUT_PULLUP);
  returnCode = U.enableInterrupts();
  Serial.print("Interrupt configuation exited with: ");
  Serial.println(U.statusString(returnCode));

  delay(100);
  digitalWrite(pinWake, 1); //Sleep

}
