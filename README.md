# **Projet : IOT TINKERCAD** :four_leaf_clover:

### **Membres** :construction_worker:
- LIBERGE Alexis
- NEZONDET-RENAUD Nathanael
- SIMON Arnaud
- ESSAMAMI Hamza

### Idée retenue : ArduiGHOST
#### Définition
Plusieurs Arduino (ressemblant à des fantômes) avec des capteurs de distance. 

Dès qu’un individu se rapproche de l’Arduino principal, un petit bruit fantomatique est déclenché grâce à un émetteur de son, bruit qui s’arrête si l’utilisateur appuie sur un bouton poussoir.

Cet Arduino principal possède un capteur de son et une photorésistance pour collecter des données qui seront envoyées (lors de l’appui sur le bouton) à un ordinateur grâce à un module wifi. 

Il possède également un capteur de distance pour diminuer le volume de l’émetteur de son et ainsi camoufler un peu plus efficacement le bouton poussoir.

Un autre bouton poussoir / envoi via Wifi sera configuré pour réinitialiser le robot principal.

Il y aura également d’autres Arduinos servant de “distractions” / “leurres” (un qui
bouge légèrement à l’aide d’un servo moteur et l’autre qui allume des LED pour afficher un visage) 

Tous ces Arduinos se déclenchent quand il fait sombre (photorésistance) avec plus ou moins d’intensité selon la distance à laquelle se trouve l’utilisateur (empêche les individus de casser les “leurres”).

Des données seront collectées au niveau de notre Arduino principal pour évaluer le niveau de peur généré par nos Arduinos, parmi les données conservées on peut compter : 
 les décibels détectés par l’Arduino principal quand il est actif
combien de temps la “victime” met pour désactiver le robot.
le nombre de fois où la luminosité a beaucoup varié pendant l’activité de l’Arduino principal (si utilisateur “victime” rallume plusieurs fois la lumière, c’est qu’il a eu peur)

#### Matériel nécessaire
Pour notre Arduino, voici la liste des composants que nous souhaitons utiliser : 

**Robot principal** : (à désactiver pour l’utilisateur)
* Arduino UNO
* bouton poussoir (mettre fin au jeu / accès à salle suivante)
* breadboard
* photorésistance
* emetteur de son
* alimentation (batterie/cable)
* câbles jumper
* capteur de son
* capteur de distance
* Module wifi ESP8266 (pour envoyer les données)
* autre bouton poussoir / activation wifi pour reset le robot principal (ou réinitialisation quand lumière intense mais pas possible de manipuler la lumière pour le client de l’escape game)
![alt text](https://github.com/ESSAMAMI/IOT-TINKERCAD/blob/main/img/arduino_principal.png)


**Distractions / Leurres** : (robots indépendants)
**smiley** :
* Arduino UNO
* câbles jumper
* 16 bandes 8 Neopixels (ou 2 carré Neopixels 8x8)
* Photorésistance
* Capteur de distance
* Une alimentation (cable / batterie)
![alt text](https://github.com/ESSAMAMI/IOT-TINKERCAD/blob/main/img/leurre_smiley_led.png)


**poltergeist** :
* Arduino UNO
* câbles jumper
* micro servo moteurs
* photorésistance
* capteur de distance
* alimentation (cable / batterie)
![alt text](https://github.com/ESSAMAMI/IOT-TINKERCAD/blob/main/img/leurre_poltergeist.png)

### liens tinkerCAD
Circuit tinkerCAD pour notre Arduino “principal”
https://www.tinkercad.com/things/3iiGzqXA9oR

Circuit tinkerCAD pour notre Arduino “leurre” dénommé “SMILEY LED”
https://www.tinkercad.com/things/jYTFCd52xQX

Circuit tinkerCAD pour notre Arduino “leurre” dénommé “POLTERGEIST”
https://www.tinkercad.com/things/b06We0Jk3K6