# TP de Bus et Réseaux industriels (ESE)
## Clarisse CHENG, Adrien LENOIR

### Séance 1 :

#### Notes :
* Adresse I2C possibles pour le BMP280 :
L'adresse 7 bit du composant est "111011" pour les 6 premiers bits, le 7eme pouvant changer lors de l'utilisation via le port SDO. Il ne faut pas laisser tel quel le pin SDO, sinon l'adresse restera indéfinie. Le CSB doit être connecté à VDDIO pour selectionner la communication en I2C. GND doit être connecté à VDDIO via une résistance de pull-up externe. Pour utiliser le mode lecture (-> 111011x1), il faut d'abord générer un "start" ou un "stop" en mode écriture (-> 111011x1)

![img](Communication_I2C.png)

Les timings de communication en I2C avec le capteur sont présentés dans le chronogramme suivant

![img](Communication_I2C_diagram.png)

Enrichi par les valeurs suivantes

![img](Communication_I2C_timings.png)

Il faut songer à ajouter à ces valeurs :
** 100 ns entre SDK et SDI (dans ce sens) en entrées dans les modes "standard" et "rapid", et seulement 20 ns dans le mode "high-speed";
** 140 ns entre SDK et SDI (dans ce sens) en sorties dans les modes "standard" et "rapid", et seulement 70 ns dans le mode "high-speed".

Le pin-out du capteur est décrit ci-après :

![img](Communication_I2C_connexion.png)

![img](Communication_I2C_connexion_tab.png)

* Le registre 0xD0 permet l'identification du composant, ici, 0x58.
* Le bit de contrôle 0xF4 permet la selection du mode de fonctionnement, ses deux bits de poids le plus faible "Mode[1:0]" doivent être placés à 0b11.
#### PAUSE ICI
* Les registres contenant l'étalonage du composant
* Les registres contenant la valeur de température (et le format)
* Les registres contenant la valeur de pression (et le format)
* Les fonctions permettant le calcul de la température et de la pression compenssée, en entier sur 32 bits : On peut trouver les formules de compensation à la fin de la documentation du capteur BMP280.


### Séance 2 :

### Séance 3 :

### Séance 4 :
Afin de pouvoir utiliser correctement la carte moteur, on utilise une fréquence de communication CAN de 500 kbits/s.
Les broches PB8 et PB9 sont de la carte Nucleo sont configurées en CAN_Rx et CAN_Tx respectivement.

Après de nombreux échecs de mise en rotation du moteur, il a fallu réinitialiser la carte de commande car elle ne fonctionnait plus.
