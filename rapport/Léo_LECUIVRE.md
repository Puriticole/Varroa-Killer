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

Séance n°9 : 24/11/2022

- Toujours des problèmes avec l'ESP intégré
- Ajout des librairies manquantes
- Le téléversement est possible mais l'ESP n'est pas reconnu "ESP Timeout"

Séance n°10 : 1/12/2022

- Prise de photo et stockage sur carte SD via IDE Arduino
- ESP ne fonctionne toujours pas
- Possible que le Firmware de la puce ne soit pas présent/à jour

Séance n°11 : 1/12/2022

- Tentative de mise à jour du firmware
- Mise à jour impossible car ??
- Apparement impossible d'utiliser l'ESP intégré à la carte

Séance n°12 : 20/12/2022

- Après recherche, Abandon de l'utilisation de l'ESP pour envoyer les données de comptage et les photos
- Le process de comptage et l'affichage se fera en local 
- Début du design de l'interface via le LCD

Séance n°13 : 06/01/2023

- Suite de la programmation du LCD
- Test sur Maixduino impossible car la carte n'est pas là








