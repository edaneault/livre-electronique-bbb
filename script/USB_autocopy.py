#NOM: Rubino Sebastian
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

temps_attente_boucle = 10									#variable dans laquelle on controle la frequence (en sec) à laquelle on un tour de boucle
type_de_fichier = '.txt', '.pdf', '.epub'							#Variable pour contrôler le type de fichier qu'on veut copier: txt, jpge, png, csv, etc...

def creation_liste(chemin, extension, tableau):							#Fonction qu'on va appeler pour creer nos listes qui serviront à copier des fichiers de façon selective
	liste_base = os.listdir(chemin)								#Cree une liste de absolument tout (fichier et dossier) ce qui se trouve dans chemin
	for entree in liste_base:								#Enumere chaque valeur de la liste crée
		if entree.endswith(extension):							#Compare si le fichier enumeré correspond au type de fichier souhaité
			tableau.append(entree)							#Si le fichier correspond à notre type d'extension, on le rentre dans notre tableau
		tableau.sort()									#On met notre liste en ordre alphabetique
	#print(tableau)										#print pour debug
	return tableau										#On veut retourner le contenu de notre nouveau tableau


if __name__ == "__main__":
	while(True):										#En mettant une while, on assure que à chaque tour de boucle on recommence le process et copier en continu
		time.sleep(temps_attente_boucle)						#Temps d'attente entre chaque cycle de lecture
			
		cmd = 'sudo mount -a'								#Commande envoyé au systeme d'explotation pour mettre à jour le mount du dossier source
		os.system(cmd)									#On envoie la commande au 'terminal'
		
		source = "/home/debian/USB_MEM"							#Chemins absolus dans lequel se trouvent notre source (dossier monté) et notre destination (dossier local)
		destination = "/home/debian/USB_destination"					
		
		liste_source = []								#Dans ces variables on va mettre une liste de chaque fichier .txt dans les fichiers source/destination
		liste_destination = []
		
		######################################################				#Creation de la liste de fichiers source et destination

		creation_liste(source, type_de_fichier, liste_source)
		creation_liste(destination, type_de_fichier, liste_destination)
		
		######################################################

		for file_name in liste_source:							#Enumere les elements (fichiers) qui se trouvent dans notre tableau source
				
			source_fichier = source + '/' + file_name				#Crée un chemin absolu qui indique l'emplacement de notre fichier
			destination_fichier = destination + '/' + file_name
			
			print(file_name)							#Print pour debug / savoir quel fichier est traité
			if file_name in liste_destination:					#Verifie si le fichier en traitement se trouve dans notre liste de destination
			
				print("Le folder destination contient deja ce fichier")		#Indique à l'usager que le fichier existe deja et donc, inutile de recopier
												#Cela evite des problemes avec la memoire
			else:									#Si le fichier n'existe pas...
				shutil.copy(source_fichier, destination_fichier)		#Copie le fichier inexistant dans notre dossier de destination
				print("Le fichier n'existe pas. Copié avec sucess")		#Indique à l'usager que le fichier a été copié
		
