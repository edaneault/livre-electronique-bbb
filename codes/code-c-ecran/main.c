#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "waveshare.h"

#define GPIO_INFO_SIZE 13 
static const char GPIO_INFO_PATH[] = "/tmp/info-GPIO";

char gpioData[GPIO_INFO_SIZE + 1];
char oldGpioData[GPIO_INFO_SIZE + 1];

#define BOUTON_ARRIERE 1
#define BOUTON_GO 2
#define BOUTON_AVANT 3
#define BOUTON_AUCUN 0

#define NB_COLONNES_TEXTE       65
#define NB_LIGNES_TEXTE         65

#define HAUTEUR_LIGNE_PIXEL     25

int obtenirInfoGPIO(void)
{
        int ret;

        FILE *fGPIOInfo = fopen(GPIO_INFO_PATH, "r");
        if (fGPIOInfo == NULL) {
                return -1;
        }

        ret = fread(gpioData, sizeof(char), GPIO_INFO_SIZE, fGPIOInfo);
	if (ret == EOF) {
		return -1;
	}

        ret = fclose(fGPIOInfo);
	if (ret == EOF) {
		return -1;
	}
}

void dessinerChoixAccueil(void)
{
	wsClear();
	wsDisplayText(180, 180, "Livre 1", 7);
	wsDrawCircle(218, 230, 15);
	wsDisplayText(520, 180, "Livre 2", 7);
	wsDrawCircle(558, 230, 15);
	wsDisplayText(340, 250, "Eteindre", 8);
	wsDrawCircle(390, 300, 15);
	wsRefresh();
}

int obtenirAction(void)
{
	int ret;

	// Tant que les données sont vieilles, réessayer de les lire
	do {
		ret = obtenirInfoGPIO();
		if (ret < 0) {
			printf("Erreur : Impossible d'acceder au fichier info\n");
			exit(-1);
		}
	} while(strcmp(gpioData, oldGpioData) == 0);

	strcpy(oldGpioData, gpioData);

	if (gpioData[6] == '1') {
		return BOUTON_ARRIERE;
	} else if (gpioData[9] == '1') {
		return BOUTON_GO;
	} else if (gpioData[12] == '1') {
		return BOUTON_AVANT;
	} else {
		return BOUTON_AUCUN;
	}
}

void afficherPage(char *cheminLivre)
{
	wsClear();

	FILE *fLivre;
	fLivre = fopen(cheminLivre,"r");
	if(fLivre == NULL) {
		printf("Erreur : Impossible d'acceder au livre\n");
		exit(-1);
	}

	char tamponPage[NB_COLONNES_TEXTE+10] = {0};

	for(int i = 0; i < NB_LIGNES_TEXTE; i++) {
		// On continue pour 10 caractères pour attraper les newlines 
		fgets(tamponPage, NB_COLONNES_TEXTE+10, fLivre);

		// On retire tout ce qui n'est pas affichable pour ne pas mélanger écran
		for(int j = 0; j < NB_COLONNES_TEXTE + 10; j++) {
			if(isprint(tamponPage[j]) == 0) {
				tamponPage[j] = ' ';
			}
		}

		wsDisplayText(0, i*HAUTEUR_LIGNE_PIXEL, tamponPage, 65);

		memset(tamponPage, '\0', NB_COLONNES_TEXTE+10);

		if(feof(fLivre)) {
		     break ;
		}
	}

	wsRefresh();

	fclose(fLivre);
}

void eteindre(void)
{
        wsClear();

        // Configurer écran pour lire microsd
        lookatmicrosd();

	// Afficher image par défaut
        image_write();
        wsRefresh();
        
	// Éteindre le système
	system("sudo shutdown -P now");
}

int main(void)
{
	int ret;
	gpioData[GPIO_INFO_SIZE] = '\0';
	oldGpioData[GPIO_INFO_SIZE] = '\0';

        if (wsInit() == 0) {
                printf("Yeah\n");
        } else {
                printf("Awww\n");
        }

	dessinerChoixAccueil();

	while(1) {
		int action = obtenirAction();

		switch (action) {
			case BOUTON_ARRIERE:
				fpos_t positionLecture;
				afficherPage("/home/debian/livres/livre1.txt");
				break;

			case BOUTON_GO:
				eteindre();
				break;

			case BOUTON_AVANT:
				break;

			case BOUTON_AUCUN: // Fallthrough
			default:
				break;
		}
	}

        return 0;
}
