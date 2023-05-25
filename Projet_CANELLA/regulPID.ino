

#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>


// Pin utilisé pour connecter les DS18B20
#define ONE_WIRE_BUS 32
#define MEASURE 13
// Objet OneWire pour gérer les capteurs
OneWire oneWire(ONE_WIRE_BUS);

// Objet DallasTemperature pour gérer la température
DallasTemperature sensors(&oneWire);

double Setpoint, Input, Output;

int numberOfDevices;

PID myPID(&Input, &Output, &Setpoint, 2, 5, 1, DIRECT);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  Setpoint = 20; // Valeur de consigne pour la température en degrés Celsius
  myPID.SetMode(AUTOMATIC);
  numberOfDevices = sensors.getDeviceCount();
  // Configurer les sorties pour les résistances thermiques et les ventilateurs
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  //pinMode(--, OUTPUT);
}
//La température mesurée est lue à partir de tous les capteurs DS18B20 en utilisant la fonction sensors.requestTemperatures() 
//et la fonction sensors.getTempCByIndex(). La moyenne de la température est ensuite calculée en divisant la somme de toutes 
//les températures par le nombre de capteurs. La température moyenne est assignée à la variable Input, qui est utilisée comme 
//entrée pour le régulateur PID. Le PID calcule ensuite la valeur de sortie en utilisant la fonction myPID.Compute(). 
//Cette valeur de sortie est utilisée pour contrôler les résistances thermiques et les ventilateurs.
void loop() {
  // Lire la température à partir de tous les capteurs
  sensors.requestTemperatures();
  float temp;
  for (int i = 0; i < 6; i++) {
    Serial.print("Temperature capteur ");
    Serial.print(i);
    Serial.print(" est : ");
    Serial.println(sensors.getTempCByIndex(i));
    temp += sensors.getTempCByIndex(i);
  }
  Input = temp / 6; // Calculer la moyenne de la température
  
    Serial.print("   La température est de : ");
    Serial.println(Input);
    delay(1000);

  // Imprimer les valeurs pour le débogage
  Serial.print("Le nombre de capteur est: ");
  Serial.println(numberOfDevices);


  delay(1000);
}
