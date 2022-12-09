Objectif du bimone :
  Etude et réalisation d'un systeme de tapis roulant installé sous une ruche. Celui-ci permettrait de recuperer tous ce qui tomberait à travers les grilles du fond de   la ruche. 
  En sortie de celui-ci une camera permettreait d'analyser ce qui se trouve sur le tapis afin de compter le nombre de varroa mort. 

Cahier de suivie :

- 1er seance 1/09/22 :
  Presentation et choix des projets
  Prise en main du logiciel github
  Premiere recherche documentaire
  Travail en binome avec Leo Lecuivre sur la partie motorisation du tapis roulant ainsi que de l'analyse de image par une camera.

- 2iéme seance 2/09/22 :
  Visite des ruches
  Decouverte et test de la carte Maixduino

- 3iéme seance 9/09/22 :
  Réalisation d'un plan 3d d'une ruche.
  Test de la camera du module Maixduino.
  
- 4iéme seance 15/09/22 :
  Recherche documentation pour realiser la detection des varroas garce au image de la camera. 
  Problematique : Pour tous ce qui est du traitement d'image par le module Maixduino, le configuration ce fait uniquement par du python et non grace à l'IDE arduino.
  
- 5ième seance 3/10/22 :
  On a commencé à programmer en Python afin de réaliser une detection sur image.
  
- 6ième seance 13/10/22 :
  Avancement sur la réalisation du plan 3d de la ruche ainsi que du rajout pour la systeme de recuperation des varroas morts

- 7ième seance 28/10/22 : 
  Détection d'un probleme d'angle de caméra. L'angle de vue de la caméra actuellement reliée sur la carte Maixduino est bien trop petit, ainsi pour pouvoir avoir la     totalité du tapis visible à la caméra, il faudrait que la caméra soit placée à environ 1m20 de haut ce qui est bien trop haut pour pouvoir detecter les varroas     sur le tapis.
  
- 8iéme seance 18/11/22 :
  Une aide donnée par le professeur pour la mise en application du traitement des images directement sur l'ESP32. La mise en place sur l'IDE Arduino fut compliquer.

- 9iéme seance 24/11/22 :
  On a des problemes pour la mise en application sur la carte Maxduino à travers l'IDE Arduino. 
  
- 10iéme seance 1/12/22 :
  On a reussi a faire fonctionner le maixduino à travers l'IDE Arduino. On essaye de faire fonctionner le WiFi de l'ESP32 pour pouvoir transmettre des données.

- 11iéme seance 9/12/22 :
  https://www.upesy.fr/blogs/tutorials/how-to-connect-wifi-acces-point-with-esp32
