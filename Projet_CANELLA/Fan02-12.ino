int pwmChannel = 0; //Choisit le canal 0
int frequence = 1000; //Fréquence PWM de 1 KHz
int resolution = 8; // Résolution de 8 bits, 256 valeurs possibles
int pwmPin = 12;

void setup(){
  Serial.begin(115200);
    // Configuration du canal 0 avec la fréquence et la résolution choisie
    ledcSetup(pwmChannel, frequence, resolution);

    // Assigne le canal PWM au pin 23
    ledcAttachPin(pwmPin, pwmChannel);

    // Créer la tension en sortie choisi
    ledcWrite(pwmChannel, 150); //1.65 V
    pinMode(14,OUTPUT);
}

void loop(){
digitalWrite(14,!digitalRead(14));
Serial.println(digitalRead(14));
delay(100);

}
