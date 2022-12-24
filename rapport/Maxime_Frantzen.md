_________________________________________________________________________________________________________
Première entrée - 01.09.2022 - 11h22 
 
## Sélection du projet d'extermination de varroa.
### Division de l'équipe en deux binome:
- Coste--Faig & LeCuivre : Comptage des varroas avec une caméra et gestion de l'évacuation des cadavres avec un tapis roulant.
- Canella & Frantzen : Régulation de l'injection de CO2 & de la température dans la ruche dans le but d'exterminer les varroa.
    
### Objectif pour notre binôme 
Répérage des différentes techniques de déparasitage des varroas 
- Trouver le taux de CO2 mortel pour les varroa et les abeilles ainsi que le temps d'exposition.
- On sait que les varroa ne survivent pas au-dessus de 41-42°C, les abeilles survivent jusqu'a 45°C.
  - Reste à trouuver le temps d'exposition mortel. 
    - Va cantifier la difficultée de la régulation de tempréature dans la ruche.
- Piste sur les accariens. En effet, les organismes ont l'air semblable.
  - Huiles essentiels ?
    
Repérage des différents composants pour le système 
- CO2 = CSS 811
- Temp = 18B20 & BME 280

Réflection sur un méthode de test de l'éfficacité de la propagation du CO2 dans la ruche.
- Test dans une ruche vide avec 3 ou 4 capteurs CO2 en fonction de la hauteur. 
 
 
 
Le projet nous impose l'utilisation d'un ESP32, du logiciel Eagle pour la conception des circuits imprimés & l'IDE Arduino.


____________________________________________________________________________________________________________________________
Seconde entrée - 02.09.2022 - 17h45 - Sophia Antipolis - Polytech

## Définition des des objectifs de la séance 
 Faire fonctionner le capteur pour la mise en place d'une expérimentation sur une séance prochaine en réalistite.

 Action de la séance :
 - Installation de toute les libraires et modules nécéssaires au bon fonctionnnement de l'esp32 et du capteur de CO2 CCS811 ;
 - Tentative de mise en route du capteur ;
 - Recherhce dans la librairue du capteur le bon contructeur afin de changer les pins de connections.
   - Si impossible, je rechercherais une autre librairie.
 - Visite du rucher de Polytech.

Objectif de la prochaine séance : Faire fonctionner le capteur CCS811. Une fois fait, rajouter les deux autres capteurs et faire fonctionner le bus.
L'objectif est que dans deux séances, nous puissions mettre en place une expérimentation par rapport à la diffusion du CO2 dans la ruche.


_____________________________________________________________________________________________________________________________
Troisième entrée - 09.09.2022 - 18h51 - Sophia Antipolis - Polytech

## Objectif de la séance 
Partiellement atteint.
Le capteur CCS811 U5 sur la carte CO2 est désormais fonctionnel. Nous pouvons récupérer la valeur de CO2 en ppm ( partie par millions ) compossant l'environnement du capteur. On observe une consommation d'environ 30 à 40 mA lorsque celui-ci est fonctionnel. Cela est cohérent par rapport à la valeur de la datasheet.
Nous avons aussi l'information sur COVT (composés oragniques totaux volatils), cependant cette information ne nous intéresse pas.

Je n'ai pas pu atteindre les autres objectifs fixé par manque de temps et de matériel. Nous n'avions pas les deux capteurs supplémentaires sous la main.
De plus, j'ai rencontrés plusieurs difficultés sur la mise en oeuvre du capteur de CO2 : 
   - Problème de software, je n'arrivais pas à téléversé le programme sur la carte. J'ai demandé de l'aide à mes camarades concernant la manipulation de téléversement.
   - Problème d'alimentation. Le capteur est effet alimenté par un circuit secondaire de tension, nommé VCO2. Celui-ci est piloté par une sortie de l'ESP32. N'ayant pas concu la carte, il m'a fallu d'abord prendre connaissance de l'information.
   - Problème sur la pin Wake. Il a fallu initialiser cette pin Wake à la masse pour que "réveiller" le capteur. Cette pin nous permettra de mettre en sommeil le capteur. Je n'ai pas encore mesuré la différence de consommation entre le capteur non alimenté et le capteur en mode sommeil.
   - Problème de stabilité en alimentation de la carte. J'ai remarqué plusieurs faux contact qui sont reliés à la position de la carte. Si la carte viens à bouger quelque peu, il peu avoir des problèmes d'alimentation ou de communication série. De plus, le port USB de mon ordinateur ne fournie qu'une tension de 2.7V au système. Ce qui n'atteint pas la tension nominale préconisée par la datasheet.

## Apprentissage de la séance 
J'ai pu comprendre une petite partie des mécanisme de l'ESP32. De plus, afin de régler le problème de stabilité en tension, j'ai pu tester d'alimenter la carte avec une alimentation stabilisé en 3.3V.

## Objectif de la prochaine séance 
Soudure du capteurs de CO2 supplémentaire.
Mise en place d'un bus I2C pour la mise en oeuvre de plusieurs capteurs CO2 (au moins 2).
Préparation d'un test dans une ruche avec une injection de CO2 pour déterminer la faisabilité de l'extermination des parasites.


__________________________________________________________________________________________________________________________________
Quatrième entrée - 16.09.2022 - 8h17 - Sophia Antipolis - Polytech

## Objectif de la séance 
Non atteint, remis à la prochaine séance.
Cause : Le capteur en CO2 nécessaire à la réalisation des objectifs n'a pas été approvisionné. 
Nouvelle mission confiée : Faire fonctionner le capteur BMP280 sur le PCB CO2. De plus, je dois améliorer le programme du CSS811 pour intégrer ses fonctions spécifiques.

## Actions de la séance :

Repérage de la faisabilité du fonctionnement du BMP280 sur le PCB. L'empreinte sur celui-ci n'est pas la bonne. En effet, le capteur comporte 6 pins et l'empreinte 4.
La solution choisie est de souder une interface pour connecter notre capteur avec des fils.

J'ai ensuite lu la datasheet du CSS811 pour trouver les infomations suivantes :
- Mesure toutes les 10 secondes (mode 2)
- Validité des données
- Comment récupérer l'information en mode 2 
Je n'ai pas encore toruvé toutes les informations.

Pour finir, j'ai aidé mon binôme sur la réalistion de l'électronique d'interface dans le but de téléverser des programmes sur un chip ESP-32 sans interface.

## Apprentissage de la séance
J'ai appris le positionnement d'un condensateur de déphasage dans un système, qui doit être le plus proche du chip possible.
De plus, nous avons aussi appris que le chip ESP32 se reset au démarrage si celui-ci ne reçoit pas la puissance nécessaire à son initialisation.
Pour finir, placer un condensateur entre la pin EN (sert au reset du chip) et le GND du chip, permet de fixer le potentiel de la pin EN pendant l'alimentation du chip. Cette astuce évite un rebootage en boucle de l'ESP32.

J'ai appris les différents fonctionnements possible du CSS811, notamment en agissant sur ses registres. Ces différents type de fonctionnement permettront d'économiser l'énergie.

## Objectif de la prochaine séance 

Faire fonctionner le capteur BMP280. 
Mise à jour du programme du CSS811 pour prise en compte des fonctions d'économies d'énergies.
Souder et faire fonctionner les deux CSS811 en I2C.
Report des objectifs de la séance précédente.

_____________________________________________________________________________________________________________________________________
Cinqième entrée - 03.10.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 
Non atteint, remis à la prochaine séance.
Cause : Manque d'information sur l'existence de la libraire SparkFunCSS8111.

## Actions de la séance :

Lecture de la datasheet du capteur et questionnement sur la communication I2C et l'accession des registres du capteurs. Repérages des registres et des bits nécessaire à la réalisation des objectifs demandés. Ecriture d'un programmme béta.

## Apprentissage de la séance

Le fonctionnement du capteur, la communication I2C. L'excistence d'une blibliothéque faite par le fabricant regroupant toutes les fonctions que j'ai voulu coder. 


## Objectif de la prochaine séance 

Faire fonctionner le capteur BMP280. 
Mise à jour du programme du CSS811 pour prise en compte des fonctions d'économies d'énergies.
Souder et faire fonctionner les deux CSS811 en I2C.
Report des objectifs de la séance précédente.

_____________________________________________________________________________________________________________________________________
Sixième entrée - 13.10.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 
Prise en main de la librairie SparkFun

## Actions de la séance :

Test des programmes d'exemples de la librairie Sparkfun et mise en place du squelette du programme principal.

## Apprentissage de la séance

Utilisation des fonctions de la librairie. Compréhensions de la fonction mode.


## Objectif de la prochaine séance 

Mise à jour du programme pour prise en compte des fonctions d'économies d'énergies


_____________________________________________________________________________________________________________________________________
Entrée 7 - 28.10.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 

Mise à jour du programme pour prise en compte des fonctions d'économies d'énergies

## Actions de la séance :

Redaction du code pour un seul capteur. Arrive à faire fonctionner un seul capteur avec le mode d'économie d'énergie.

## Apprentissage de la séance

Les adresses du capteurs et son fonctionnement. De plus, connaissance de la carte réceptrice notamment du pin Mesure


## Objectif de la prochaine séance 

Faire fonctionner deux capteurs CCS811 ensemble.

_____________________________________________________________________________________________________________________________________
Entrée 8 - 18.11.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 
Faire fonctionner deux capteurs CCS811 ensemble.

## Actions de la séance :

Soudure du second capteur en respectant le brochage. Petit soucis avec le matériel qui à causé une petite perte de temps (env 30min). Réflexion sur les méthodes de communication et comment les coder.

## Apprentissage de la séance

Compréhension des différentes adresses du capteurs et comment les changer. Compréhensio du squellete que devrait avoir le programme pour faire fonctionner
le capteur.

## Objectif de la prochaine séance 

Faire fonctionner deux capteurs CCS811 ensemble.

_____________________________________________________________________________________________________________________________________
Entrée 9 - 25.11.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 

Faire fonctionner deux capteurs CCS811 ensemble.

## Actions de la séance :

Reprise du code pour le fonctionnement des deux capteurs. Fonctionnel !
Soudage du troisième capteur CSS811.

## Apprentissage de la séance

Le fonctionnement du capteur, la communication I2C. L'excistence d'une blibliothéque faite par le fabricant regroupant toutes les fonctions que j'ai voulu coder. 


## Objectif de la prochaine séance 

Faire fonctionnner 3 capteurs.

_____________________________________________________________________________________________________________________________________
Entrée 10 - 01.12.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 
Faire fonctionnner 3 capteurs CCS811.

## Actions de la séance :

Ecriture du troisième code pour le fonctionnment des trois capteurs.
Cepndant je rencontre une erreurs inabituelle : A fatal error occurred: MD5 of file does not match data in flash!

Après quelques recherche, je trouve un moyen de la corriger en remettant l'ESP32 à ses valeurs d'usine avec la commande suivnate : 

esptool --port <YOUR PORT> write_flash_status --non-volatile 0

 soltuion trouvée sur ce site : https://community.m5stack.com/topic/838/a-fatal-error-occurred-md5-of-file-does-not-match-data-in-flash/5


## Apprentissage de la séance

Résolution de l'erreur évoqué ci dessus.


## Objectif de la prochaine séance 
 
Faire fonctionner les trois capteurs.

_____________________________________________________________________________________________________________________________________
Entrée 11 - 09.12.2022 - 16h36 - Sophia Antipolis


## Objectif de la séance 

Faire fonctionner les trois capteurs.

## Actions de la séance :

Mise à jour du code. Code fonctionnel pour les trois capteurs. Soummission de la réussite à M.PETER. Le nouvel objectif est désormais de stocker les données de la mesure dans un fichier pour ensuite le récupérer. Recherhce de solution d'écriture, de stockage et de transfert.

## Apprentissage de la séance

Méthode de stockage pour ESP32 et transfert des fichiers. Gestionnaire de fichier spécial pour ESP32.

## Objectif de la prochaine séance 

Ecrire un porgramme fonctionel de stockage des données récupérer par les capteurs. Réussir le trasnfert des données entre l'ESP32 et mon pc.

_____________________________________________________________________________________________________________________________________
Entrée 12 - 20.12.2022 - 11h39 - Sophia Antipolis


## Objectif de la séance 



## Actions de la séance :



## Apprentissage de la séance



## Objectif de la prochaine séance 

