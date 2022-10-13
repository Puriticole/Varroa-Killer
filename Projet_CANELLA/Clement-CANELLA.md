//Gestion destruction varroa

Séance 1 : Création du compte github, avce un espace pour le rapport de chacun. 

           Répartition des taches: 
           Léo Lecuivre / Nans Cost Faig --> systeme de comptage des Varroa mort / tapis roulant
           Maxime Frantzen / Clément Canella --> asservissement de la température / Quantité de CO2 dans la ruche
           
           Objectif pour mon binome :
           -> Trouver le taux de CO2 létal pour les Varroas
           -> Température max supportée par les Varroa de 41 - 42°C 
           -> Mettre en place une instrumentation capable de réguler la température ou le taux de CO2
           -> Tester la propagation du CO2 dans une ruche
           -> Capteur de CO2 : CSS 811
           -> Capteur de température : 18B20 & BME 280
           
Séance 2 : Régulation de la quantité de CO2 pour maxime et Régulation de la température pour moi
           
           -> CO2 :
           -> Nous avons récuperer la carte comportant un capteur de CO2 (CSS811) 
           -> Lecture de la doc de la carte afin de savoir comment la cabler à une carte arduino. 
           
           -> Température :
           -> Découverte du capteur 18B20 (https://www.carnetdumaker.net/articles/mesurer-une-temperature-avec-un-capteur-1-wire-ds18b20-et-une-carte-arduino-genuino/)
           -> Arduino (Heltec wifi lora) 
           -> Cablage des capteurs 18B20 https://www.raspberryme.com/micropython-capteur-de-temperature-ds18b20-avec-esp32-et-esp8266/
           ->                            https://arduino-france.site/ds18b20-arduino/
           
Séance 3 : Cablage de la carte ESP32 avec FTDI USB to Serial Cable 
![image](https://user-images.githubusercontent.com/112617884/189360778-c8886a6e-c592-4317-80cd-269decfa1934.png)
![image](https://user-images.githubusercontent.com/112617884/189360934-a841aa2a-c13c-46d5-93b7-5d133744d8dc.png)
Branchement de la carte permetant de téléverser les programes sur la carte ESP32
           
Séance 4 : Fin du cablage de la carte ESP32 avec FTDI USB to Serial Cable 

           -> Nous n'utilisons pas les ports DTR et CTS de la carte FTDI
           -> Nous arrivons a communiquer avec la ESP32
       
Séance 5 :  03-10
           -> téléchargement des bibliothèques OneWire et DallasTemperature
           -> communication avec le capteur 18B20 (réception de la température)
           -> Nom du fichier : com18B20_03-10.ino
           
Scéance 6 : 13-10
            ![image](https://user-images.githubusercontent.com/112617884/195543164-0bad06e8-7334-4703-aa76-3087dcb779f7.png)

