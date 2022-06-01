#Description: 	Ce script, qui est à sa première version, a comme fonction de donner
#		un nouveau format à un fichier afin de respecter les besoins d'un écran.
#		En termes simples, ce script compte la quantité de caracteres dans chaque mot
#		et determine, à l'aide d'une variable "limite", si ce mot peut être ajouté
#		ou si ce mot doit passer à la ligne suivante.


fichier_lecture = "/home/debian/explotation/testing local/test.txt"
A = open(fichier_lecture, 'r')
read_data = A.read()

liste = read_data.split()

liste_b = ''
d = 0
somme_char = 0
r = 0
limite = 60					#limite qui ajuste la quantité maximale de mots par ligne

for e in liste:					#boucle for qui ajoute un espace à chaque element pour la nouvelle mise en forme.
	r += 1
	liste[r-1] = liste[r-1] + ' '
	#print(liste)				print pour debug

for e in liste:					#boucle qui va traiter chaque mot avec son espace respectif
	d += 1
	f = len(liste[d-1])			#calcule la quantité de lettres et espaces dans un mot
	somme_char += f				#on additionne cette quantité pour la comparer à une limite
	if somme_char <= limite:		#si somme de caracteres est plus petit ou égal à limite voulue...
		liste_b += liste[d-1]		#on ajoute les mots dans notre str
	elif somme_char > limite:		#si la somme depase la limite voulue...
		liste_b += '\n' + liste[d-1]	#alors on introduit une nouvelle ligne et on insere le mot

		val_ajoute = len(liste[d-1])	#on calcule la valeur du dernier mot ajouté
		somme_char = 0 + val_ajoute	#on remet à zero notre compteur de caracteres en ajoutant la quantité de lettres du mot en nouvelle ligne

print(liste_b)

	
