# Proposition pour la fin de projet
Le mot d’ordre c’est : Simple mais qui démontre le plus de fonctionnement possible.

# Montage clé USB
On modifie le code de Sebastian/Simon pour que :

- Si une clé USB est vide, on crée un répertoire nommé « bibliotheque601 » dessus.
- Ce répertoire contient 14 fichiers : livre01.txt, livre02.txt, livre03.txt, etc.
- Ce répertoire existe aussi sur le BBB
- Si on insère une clé USB avec des fichiers livre01.txt, livre02.txt différents de ceux sur le BBB, on écrase les livres du BBB avec ceux de la clé USB.

On a donc 14 livres sur le livre électronique, et une façon de les changer.

# Livre du net (Gutenberg)
On modifie le code de Hugo / Léonard pour que :

- Quand on lance le BBB, il récupère le premier livre sur https://gutenberg.org/browse/scores/top
- Il place ce livre dans bibliotheque601 sous le nom « livrenet.txt »

# Boîtier
On complète le case acrylique de démonstration. Le design doit être simple mais fonctionnel.

# Boutons (GPIO)
On modifie le code de GPIO de Brian/Bob :

- De concert avec le design du case pour pouvoir détecter quand un des trois boutons a été pesé.
- On utilise le même design que dans le projet 1 pour transmettre l’information, avec un fichier dans /tmp/ qui contient S000Ar0Go0Av0. 
- Le code en C va pouvoir lire ce fichier quand il veut pour avoir l’état des boutons.

# Lecture du texte
On complète le code de lecture de texte de Tommy Lee :

- Il faut être capable de changer le fichier lu (livre01.txt, livre02.txt, etc.)
- Il faut être capable d’afficher une page entière.
- Il faut être capable de changer de page vers l’avant et l’arrière.

# Interface graphique
On ajoute du code qui génère une interface simple :

- On utilise wxDisplayText pour afficher les options
- On utilise wsDrawLine pour sélectionner une option avec les boutons (souligné = sélectionné)
- Les options :
    * Livre1 à Livre14
    * Livre du net
    * Éteindre
- Peser le bouton « Go » ouvre le fichier pour les livres
- Peser « go » sur « Éteindre » charge l’image de veille et éteint le BBB.
- Ouvrir un livre = L’afficher à l’écran. Gauche droite changer de page. Go ramène au menu.

# systemd
On configure systemd pour orchestrer le tout et faire le lancement automatique.

# Documentation et release
On documente bien le tout et on le publie sur github pour avoir notre release.