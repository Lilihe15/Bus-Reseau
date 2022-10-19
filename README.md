# TP de Bus et Réseaux industriels (ESE)
## Clarisse CHENG, Adrien LENOIR

### Séance 1 :

#### Notes :
* Numéro de la boîte à bec : 4
* Adresse I2C possibles pour le BMP280 : Connexion de CSB sur VDDIO L'adresse 7 bit du composant est "111011" pour les 6 premiers bits, le 7eme pouvant changer lors de l'utilisation via le port SDO. Il ne faut pas laisseer le pin SDO, sinon l'adresse restera indéfinie. Le CSB doit être connecté à VDDIO pour selectionner la communication en I2C.
* Le registre et la valeur permettant d'identifier le composant :
* Le registre et la valeur permettant de mettre le composant en mode normal :
* Les registres contenant l'étalonage du composant
* Les registres contenant la valeur de température (et le format)
* Les registres contenant la valeur de pression (et le format)
* Les fonctions permettant le calcul de la température et de la pression compenssée, en entier sur 32 bits.
