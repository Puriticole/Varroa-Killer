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

           -> Il faut regarder la régulation de la dissipation de la puissance dans les résistances thermiques grace au PWM (pulse width modulation) 
              P= Pinstantané * t/T
           -> Le lien vers le ventilo choisi : https://fr.aliexpress.com/item/1005003284761769.html?spm=a2g0o.detail.1000014.11.8ab61ca2U5oJsV&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.14452.226710.0&scm_id=1007.14452.226710.0&scm-url=1007.14452.226710.0&pvid=3db608ed-b30f-4c5d-a034-b0428ab793c1&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.14452.226710.0,pvid:3db608ed-b30f-4c5d-a034-b0428ab793c1,tpp_buckets:668%232846%238107%231934&pdp_ext_f=%7B%22sku_id%22%3A%2212000025019612448%22%2C%22sceneId%22%3A%2230050%22%7D&pdp_npi=2%40dis%21EUR%211.89%211.65%21%21%21%21%21%40211b442116656511210336684e0b5d%2112000025019612448%21rec&ad_pvid=202210130152010484380121356153317682_2

Séance 7 : 28-10

           -> J'ai recu le ventilateur qu'il faudra mettre en oeuvre à la prochaine scénance. 
           -> J'ai Connectée les pin des thermomètres sur la meme entrée de la carte et addapté le code en fonction. 
           -> Fonctionne bien mais a parfois des problèmes de téléversement. 
          
Séance 8 : 18-11

           -> J'ai placé tous les capteurs de températures sur une breadboard séparée de la carte esp32 et des boutons, ce qui simplifie la lisibilité du circuit. 
           -> J'ai pu tester le fonctionnement de 4 capteurs 18B20 sur la meme entrée de l'ESP32 ce qui à bien fonctionner.
           -> Je suis passé sur 
           -> J'ai soudé les différents composants de la carte de régulation des résistances thermiques et des ventilateurs. 
           -> Petite mise à jours au niveau du code. 
           
Séance 9 : 25-11

           -> J'ai finalisé les soudures de la carte permettant la régulation des résistances thermiques et des ventilateurs.
           -> J'ai ajouter au montage éléctrique la carte soudée ainsi qu'un ventilateur. 
           -> je me suis renseigné pour controler les ventilateurs via la carte ESP32 en pwm
           
Séance 10 : 01-12

           -> J'arrive a faire tourner les ventilateurs mais pas encore à réguler leurs vitesse de rotaion. 
           -> J'ai commencé à réaliser le code Arduino qui nous permetra de controler les ventilateurs. 
           
Séance 11 : 09-12

           -> J'ai mis a jours le code permettant de reguler la vitesse des ventilateurs, le code fonctionne.
           -> Un probleme est survenu au niveau de la carte d'adaptation ESP/ ventilateur 
           
Séance 12 : 20-12 

           -> J'ai commencé à souder les ventilateurs sur le toit de la ruche
           -> La modulation de la vitesse des ventilateurs fonctionne
           -> Une des prochaines étapes est d'asservir la vitesse des ventilateurs avec la température de la ruche.
           
Séance 13 : 06-01

           -> J'ai fini de souder les ventillateurs ainsi que les résistances thermiques 
           -> IL me reste à rendre entièrement fonctionnel le code permettant l'asservissement de la température de la ruche
           
           
Séance 16-03 : 

           -> J'ai relié la carte ESP aux thermomètres, pour le moment je n'arrive pas à lire les température 

Séance 23-03 : 

           -> J'ai essayé de résoudre le probleme de température sans succés pour le moment. Je suis repassé sur la détection d'un seul capteur 
Séance 28-03 :

           -> J'ai reussi à résoudre le probleme de lecture des thermomètres. 
           -> Je commence à connecter les ventilateurs ainsi que les résistances thermiques.
Séance 06-04 : 

           -> J'ai souder les ventilateurs à la carte. 
           -> Il y a un court circuit que j'ai localisé et que je tente de résoudre. 

Séance 20-04 :

           -> J'ai trouvé d'ou venait le problème de court circuit, les ventilateurs une fois alimenté tournent sans problème, leur vitesse est variable. 
           -> J'ai rencontré un problème en fin de séances sur mes test pour faire varier la vitesse de rotation des ventilateurs en fonction de la température. 
           L'ESP à été définitivement endomagé, il faudra procéder à un échange. 
