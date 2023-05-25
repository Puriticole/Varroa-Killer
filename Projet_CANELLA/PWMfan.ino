int pwmChannel = 0; //Choisit le canal 0
int frequence = 1000; //Fréquence PWM de 1 KHz
int resolution = 8; // Résolution de 8 bits, 256 valeurs possibles
int pwmPin = 16;
int val;

void setup(){
  Serial.begin(115200);
 
    // Configuration du canal 0 avec la fréquence et la résolution choisie
    ledcSetup(pwmChannel, frequence, resolution);

    // Assigne le canal PWM au pin 23
    ledcAttachPin(pwmPin, pwmChannel);

    // Créer la tension en sortie choisi
    
}

void loop(){
  int val = 4095;
  Serial.println(val); // donne une valeure de 0 à 4095
  ledcWrite(pwmChannel, val); //1.65 V
  delay(500);
  

}
