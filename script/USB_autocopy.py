#NOM: Rubino Sebastian et Simon Lachapelle

#COURS: systemes d'exp
#ENSEIGNANT: Emile Daneault
#DESCRIPTION: 	ce code permet deux choses importantes pour le projet final. Premierement, avec les manipulations decrites dans le fichier "preparation_mount_port_USB",
#		ce script remet le mount sur un folder temporaire dans lequel nous allons chercher les fichiers de n'importe quelle clé usb qui se branche sur notre port USB.
#		Ensuite, ce script va faire une comparaison entre nos fichiers textes locaux (les livres qui existent deja dans notre dossier de livres) et nos fichiers textes
#		qui se trouvent dans notre repertoire monté avec le port USB. Finalement, chaque fichier .txt (du dossier monté) qui ne se trouve pas dans le dossier de destination
#		sera copié et disponible pour une lecture.
import fnmatch
import glob
import filecmp
import shutil
import os
import time

type_de_fichier = '.txt', '.pdf', '.epub'							#Variable pour contrôler le type de fichier qu'on veut copier: txt, jpge, png, csv, etc...
source = "/home/linux/TEST/USB"									#Chemins absolus dans lequel se trouvent notre source (dossier monté) et notre destination (dossier local)
destination = "/home/linux/TEST/LOCAL"
temps_attente_boucle = 5									#variable dans laquelle on controle la frequence (en sec) à laquelle on un tour de boucle
bibliotheque_folder = source + "/bibliotheque601"

def creation_liste(chemin, extension, tableau):							#Fonction qu'on va appeler pour creer nos listes qui serviront à copier des fichiers de façon selective
	liste_base = os.listdir(chemin)								#Cree une liste de absolument tout (fichier et dossier) ce qui se trouve dans chemin
	for entree in liste_base:								#Enumere chaque valeur de la liste crée
		if entree.endswith(extension):							#Compare si le fichier enumeré correspond au type de fichier souhaité
			tableau.append(entree)							#Si le fichier correspond à notre type d'extension, on le rentre dans notre tableau
		tableau.sort()									#On met notre liste en ordre alphabetique
	#print(tableau)										#print pour debug
	return tableau										#On veut retourner le contenu de notre nouveau tableau


if not os.path.exists(bibliotheque_folder):
	os.makedirs(bibliotheque_folder)
	print("Folder bibliotheque601 n'existait pas. Folder crée!")
else:
	print("Folder bibliotheque601 existait déjà")



if __name__ == "__main__":
	while(True):										#En mettant une while, on assure que à chaque tour de boucle on recommence le process et copier en continu
		time.sleep(temps_attente_boucle)						#Temps d'attente entre chaque cycle de lecture
			
		cmd = 'sudo mount -a'								#Commande envoyé au systeme d'explotation pour mettre à jour le mount du dossier source
		os.system(cmd)									#On envoie la commande au 'terminal'

		liste_source = []								#Dans ces variables on va mettre une liste de chaque fichier .txt dans les fichiers source/destination
		liste_destination = []
		
		######################################################				#Creation de la liste de fichiers source et destination

		creation_liste(bibliotheque_folder, type_de_fichier, liste_source)
		creation_liste(destination, type_de_fichier, liste_destination)
		
		for file_name in liste_source:							#Enumere les elements (fichiers) qui se trouvent dans notre tableau source
				
			source_fichier = bibliotheque_folder + '/' + file_name			#Crée un chemin absolu qui indique l'emplacement de notre fichier
			destination_fichier = destination + '/' + file_name

			print()
			print(file_name)							#Print pour debug / savoir quel fichier est traité
			if file_name in liste_destination:					#Verifie si le fichier en traitement se trouve dans notre liste de destination
				
				print("Le folder destination contient deja ce fichier...")	#Indique à l'usager que le fichier existe deja et donc, inutile de recopier
				compare_a = os.path.getmtime(source_fichier)			#fonction qui detecte EPOCH value (temps) depuis le dernier changement du fichier
				compare_b = os.path.getmtime(destination_fichier)

				if compare_a == compare_b:						#Si le fichier est exactement le même, EPOCH sera égal à la source et à la destination
					print("Aucun changement detecté dans le fichier source")	#Aucun changement sera nécessaire
				else:									#Si une modification se fait dans le fichier source (comme un nouveau livre01.txt)
					os.remove(destination_fichier)					#Alors on efface le vieux fichier pour copier le nouveau éventuellement.
					print("changement detecté à la source, ancien fichier destination effacé.")	# ex: Livre01.tx (LALA.txt - modifié:4 mai) --­> Livre01.tx (LELE.txt - modifié:5 mai)
				
			else:									#Si le fichier n'existe pas...
				shutil.copy(source_fichier, destination_fichier)		#Copie le fichier inexistant dans notre dossier de destination
				print("Le fichier n'existe pas. Copié avec sucess")		#Indique à l'usager que le fichier a été copié
				
				compare_a = os.path.getmtime(source_fichier)			
				compare_b = os.path.getmtime(destination_fichier)

				os.system('touch --date=@' + str(compare_a) + ' ' + destination_fichier) # Rend égal le EPOCH des deux fichiers pour éviter de les effacer ultérieurement
				
