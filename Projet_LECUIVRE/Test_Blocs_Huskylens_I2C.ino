#include <HuskyLens_I2C.h>

HuskyLens I2C(0x32);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  I2C.begin();
  I2C.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
  I2C.writeLearned(1); //Activer le mode d'apprentissage
}

void loop() {
  I2C.request();
  if(I2C.available()){
    int objCount = I2C.readObjCount();
    for(int i = 0; i < objCount; i++){
      int id = I2C.readID(i);
      int x = I2C.readX(i);
      int y = I2C.readY(i);
      int width = I2C.readWidth(i);
      int height = I2C.readHeight(i);
      String label = I2C.readLabel(i);
      Serial.print("Objet : ");
      Serial.print(label);
      Serial.print(", x : ");
      Serial.print(x);
      Serial.print(", y : ");
      Serial.print(y);
      Serial.print(", largeur : ");
      Serial.print(width);
      Serial.print(", hauteur : ");
      Serial.println(height);
    }
  }
}
