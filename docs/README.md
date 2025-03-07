# Documentation

## Recherche et conception

J'étais un peu perdu de base, je savais pas exactement quoi faire ni ce que je pouvais faire. Je me suis dis qu'il fallait faire quelque chose qui me plaisait alors j'ai cherché un jeu pas trop difficile à coder que je pourrai recréer avec une nouvelle façon de jouer. C'est là que m'est venu l'idée du Pong. Vu que j'avais l'idée, j'ai été voir si c'était possible, j'ai cherché des projets similaire et j'ai trouvé quelqu'un qui avait créer un Pong sur un Arduino Uno aussi. 

La vidéo : https://www.youtube.com/watch?v=ZRL0GUqebFs
Le code : [https://www.youtube.com/watch?v=ZRL0GUqebFs](https://educ8s.tv/arduino-pong-game/) (à télécharger)

## Circuit électronique

Attention à l'écran que l'on utilise lors du projet. Il faut juste adapter le code avec la bonne largeur et la bonne hauteur d'écran dans le code.

### Schéma

![Description de l'image](/docs/assets/pong_bb.png)

### BOM

| Réf | Composant      | Quantité | Description                            | Fournisseur / Lien                                            |
| --- | -------------- | -------- | -------------------------------------- | ------------------------------------------------------------- |
| 1   | Arduino Uno R3 | 1        | Microcontrôleur ATmega328P             | [Arduino](https://store.arduino.cc/products/arduino-uno-rev3) |
| 2   | Breadboard     | 1        | Plaque de prototypage                  | [Arduino](https://store.arduino.cc/products/arduino-uno-rev3) |
| 3   | HC-SR04        | 2        | Capteur de distance à ultra son        | [Lien](https://fr.aliexpress.com/item/1005003516264431.html) |
| 4   | Purecrea       | 1        |  OLED Display Blue I2c                 | [Lien](https://www.galaxus.ch/en/s1/product/purecrea-oled-display-blue-i2c-128x32-091-development-boards-kits-36688816?utm_campaign=organicshopping&utm_source=google&utm_medium=organic&utm_content=8244233&supplier=8244233&gQT=0) |

## Programme

Dans le code, pour gérer l'affichage de l'écran j'ai utilisé 2 librairie : 
- Adafruit_GFX
- Adafruit_SSD1306

Le code est assez simple, on affiche un écran d'accueil à l'allumage, au bout de 3 secondes la partie se lance. Dès qu'un joueur obtient 7 points, un écran annonce le vainqueur puis une autre partie recommence.

## Roadmap

Ce qui aurait encore pu être améliorer : 
- faire que la partie ne se lance que lorsque les 2 joueurs positionnent leurs mains devant le capteur afin de dire qu'ils sont prêt
- réglage de bug de positition de la palette, desfois la palette donne un effet de téléportation
- Ajout d'un Buzzer et d'un son
- Ajout d'un mode solo
