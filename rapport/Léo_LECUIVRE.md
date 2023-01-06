Cahier De Suivi :
/--------------------/
Création 01/09/2022
/--------------------/

Séance n°1 : 

- Création du Git relatif au projet
- Répartition des diffrerntes taches (Première passe provisoire)
- Début des recherches sur les varroa et les differentes soution d'élimination
- Première approche du tapis roulant

Définition des rôles des binômes :

- COSTE--FAIG, LECUIVRE ---> Systéme d'evacuation des varroa morts qui sont tombés, sur un tapis. Comptage des varroa sur le tapis pour se rendre compte de l'efficacité du système d'elimination.
 
 
- FRANTZEN, CANELLA ---> Réalisation d'un system d'elimination des varroa en utilisant la chaleur ou du co2

Séance n°2 :

- Découverte de la Carte Maixduino
- Installation de l'environnement arduino necessaire au fonctionnement de maixduino sur ide arduino
- allumage de leds via le maixduino
- Géstion de l'affichage sur écran LCD 

Séance n°3 :

- Reprise de la découverte de la Carte Maixduino
- Découverte de la caméra du maixduino
- affichage de la caméra du maixduino sur ecran LCD
- Début de la phase de découverte de la détéction de formes sur image via python

Séance n°4 :

- Reprise de la phase de découverte de la détéction de formes sur image via python
- prise de photos via l'IDE Arduino
- recherches pour librairies détéction de formes approfondies (visage, yeux, annimaux, ...)
- Réfléxion sur la faisabilité de la détéction de formes via IDE Arduino (Les librairies de détéction de formes n'existent que sur Python)

Séance n°5 : 03/10/2022

- Recherches sur la faisabilité du traitement d'une image via IDE Arduino en passant par des librairies python
- Solution introuvable pour analyse des images via IDE Arduino
- Dirrection sur python pour réaliser le projet
- Test approfondi sur les librairies et codes python pour detection de formes
- Qualité médiocre des images en live car memoire saturé

Séance n°6 : 13/10/2022

- Lectures de DataSheets sur le maixduino
- La camméra n'a pas un angle de vue suffisant pour voir tout le tapis
- Elle serait trop en hauteur 
- Recherche d'une lentille grand angle pour contourner le problème

Séance n°7 : 28/10/2022

- Analyse des Pins de la caméra pour voir si une autre grand angle est compatible
- Test du module ESP32 sur maixduino
- Connexion sur un réseau wifi connu
- Echanges de données
- Tentative d'envoi de fichiers 

Séance n°8 : 18/11/2022

- Avec une aide sur le traitement des images sur Arduino/fonctionnement de l'ESP intégré 
- Essais de l'ESP sur la carte Maixduino avec ces infos
- Mise en place difficile à cause de plusieurs librairies inexistantes.

9iéme seance 24/11/22 : On a des problemes pour la mise en application sur la carte Maxduino à travers l'IDE Arduino.

10iéme seance 1/12/22 : On a reussi a faire fonctionner le maixduino à travers l'IDE Arduino. On essaye de faire fonctionner le WiFi de l'ESP32 pour pouvoir transmettre des données.

11iéme seance 9/12/22 : Le WIFI de l'ESP32 ne fonctionne pas avec les librairies.

12ième seance 20/12/22 : Suite au recherche du Mr Peter, le WiFi n'a pas utilité dans le projet, on va utiliser l'ecran LCD pour faire le comptage des varroas.





