#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>
//ce code utilise la bibliothèque PID pour contrôler la température en utilisant une régulation PID. 
//La température mesurée est comparée à la température de consigne, et la sortie du PID est utilisée pour contrôler les 
//résistances thermiques en utilisant le PWM. Si la température mesurée est inférieure à la température de consigne, 
//les résistances thermiques sont activées à un niveau élevé, ce qui augmente la température. Si la température mesurée 
//est supérieure à la température de consigne, les résistances thermiques sont activées à un niveau faible, ce qui réduit 
//la température. Le code s'adapte automatiquement en fonction de la différence entre la température mesurée et la température 
//de consigne pour maintenir la température proche de la température de consigne.


// Pin utilisé pour connecter le DS18B20
#define ONE_WIRE_BUS 2

// Objet OneWire pour gérer les capteurs
OneWire oneWire(ONE_WIRE_BUS);

// Objet DallasTemperature pour gérer la température
DallasTemperature sensors(&oneWire);

double Setpoint, Input, Output;

PID myPID(&Input, &Output, &Setpoint, 2, 5, 1, DIRECT);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Setpoint = 25; // Valeur de consigne pour la température en degrés Celsius
  myPID.SetMode(AUTOMATIC);
  
  // Configurer les sorties pour les résistances thermiques et les ventilateurs
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}
//La température mesurée est lue à partir de tous les capteurs DS18B20 en utilisant la fonction sensors.requestTemperatures() 
//et la fonction sensors.getTempCByIndex(). La moyenne de la température est ensuite calculée en divisant la somme de toutes 
//les températures par le nombre de capteurs. La température moyenne est assignée à la variable Input, qui est utilisée comme 
//entrée pour le régulateur PID. Le PID calcule ensuite la valeur de sortie en utilisant la fonction myPID.Compute(). 
//Cette valeur de sortie est utilisée pour contrôler les résistances thermiques et les ventilateurs.
void loop() {
  // Lire la température à partir de tous les capteurs
  sensors.requestTemperatures();
  double temp = 0;
  for (int i = 0; i < 6; i++) {
    temp += sensors.getTempCByIndex(i);
  }
  Input = temp / 6; // Calculer la moyenne de la température

  // Calculer la valeur de sortie à partir du PID
  myPID.Compute();

  // Écrire les valeurs de sortie sur les broches PWM
  analogWrite(13, Output);
  analogWrite(12, Output);

  // Imprimer les valeurs pour le débogage
  Serial.print("Input: ");
  Serial.print(Input);
  Serial.print("  Output: ");
  Serial.print(Output);
  Serial.print("  Setpoint: ");
  Serial.println(Setpoint);

  delay(100);
}
