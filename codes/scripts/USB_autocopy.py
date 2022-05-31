# NOM: Rubino Sebastian et Simon Lachapelle

# COURS: systemes d'exp
# ENSEIGNANT: Emile Daneault
# DESCRIPTION: 	
# Ce code permet deux choses importantes pour le projet final. Premierement, ce script remet le mount sur un folder temporaire dans lequel nous allons chercher 
# les fichiers de n'importe quelle clé usb qui se branche sur notre port USB.
# Ensuite, ce script va faire une comparaison entre nos fichiers textes locaux (les livres qui existent deja dans notre dossier de livres) et nos fichiers textes
# qui se trouvent dans notre repertoire monté avec le port USB. Finalement, chaque fichier .txt (du dossier monté) qui ne se trouve pas dans le dossier de destination
# sera copié et disponible pour une lecture.
#
# 
# ATTENTION: Les manipulations qui suivent doivent se faire avant de lancer le script.
# Ces instructions indiquent étape par étape les manipulations à faire pour créer avec succes
# un dossier local dans lequel le mount de n'importe quelle clé usb pourra se créer. 
# Le BBB doit deja être connecté en ssh car, les étapes à suivre se font sur le BBB.
# 
# 
# 1) 	Creer un dossier (source) dans lequel vous allez faire un mount. Ce dossier doit pouvoir être traité sans sudo.
# 	Idealement, ce dossier doit être facile d'y acceder.
# 	exemple: usb, usb_mount, usb_source, etc.
# 	
# 2)	(Si pas fait) Creer un autre dossier (destination) dans lequel vous allez eventuellement copier vos fichiers dans un dossier
# 	de lecture local. C'est ici que l'application qui va afficher les caracteres sur l'ecran va venir chercher
# 	les livres. Encore une fois, faire un dossier facil d'access et qui n'a pas besoin de l'autorisation root.
# 	exemple:  usb_destination, dossier_lecture, livres, etc.
# 	
# 2.1)	Mettre à jour les chemins dans le script python (source et destination) aux lignes 36 et 37. Cette étape peut se faire à la fin.
# 	
# 3)	Connecter une clé usb (idéalement vide) dans le port usb et attendre quelques secondes avant de faire l'étape 4.
# 
# 4)	Sur le terminal, faire la commande suivante: sudo blkid
# 
# 4.1)	Trouver la partition dans laquelle se situe notre cle usb. Normalement, cette partition change à chaque
# 	nouvelle connection donc, n'ayez pas peur de recommencer l'étape 3 si jamais vous êtes dans le doute.
# 	exemple: /dev/sda1, /dev/sdb2, etc
# 
# 5)	Sur le terminal, faire la commande suivante: udevadm info --name=/dev/[la partition trouvé au 4.1] | grep disk/by-path
# 
# 5.1)	Sur la ligne S, copier le id de la plateforme du port USB.
# 	exemple: < S: disk/by-path/pci-0000:00:06.0-usb-0:2:1.0-scsi-0:0:0:0-part1 >
# 	La partie qui nous interese, c'est: pci-0000:00:06.0-usb-0:2:1.0-scsi-0:0:0:0-part1
# 	
# 6)	Sur le terminal, faire: sudo nano /etc/fstab
# 
# 7)	Dans l'editeur texte, allez à la derniere ligne (une ligne vide) est écrire vos informations avec le format suivant et enregistrez:
# 	
# 	/dev/disk/by-path/[votre id trouvé à l'étape 5.1] [chemin destination crée à l'étape 2] auto defaults,nofail 0 0
# 	
# 	voici une exemple concret:
# 	
# 	/dev/disk/by-path/pci-0000:00:06.0-usb-0:2:1.0-scsi-0:0:0:0-part1 /home/debian/USB auto defaults,nofail 0 0
# 
# 	*attention aux espaces! car si le fichier fstab est mal configuré, le Beaglebone ne va pas demarrer. Il faudra y acceder par linux
# 	pour changer le fichier fstab.
# 
# 8)	Faites un redemarrage de votre systeme. Vous pouvez faire: sudo reboot
# 
# 9)	C'est prêt! vous êtes prêt à connecter une clé usb avec des fichiers.
# 
# 
# En cas de doute, ne pas modifier le script ni les etapes. Consultez l'auteur pour toute question.


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
				
