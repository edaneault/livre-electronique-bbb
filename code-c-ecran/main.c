#include <stdio.h>

#include "waveshare.h"
char buffer_texte[1000];


int i = 0;
//Le nom de ces variables seront a changer pour les vrais boutons
int BoutonSelection;
int FlecheBas;
int FlecheHaut;


int fct_AffichageSelection(void)//Permet d'afficher a chaque fois toutes les options
{
	wsClear();
	
	wsDisplayText(0,1*34, "Livre 01", 8);
	wsDisplayText(0,2*34, "Livre 02", 8);
	wsDisplayText(0,3*34, "Livre 03", 8);
	wsDisplayText(0,4*34, "Livre 04", 8);
	wsDisplayText(0,5*34, "Livre 05", 8);
	wsDisplayText(0,6*34, "Livre 06", 8);
	wsDisplayText(0,7*34, "Livre 07", 8);
	wsDisplayText(0,8*34, "Livre 08", 8);
	wsDisplayText(0,9*34, "Livre 09", 8);
	wsDisplayText(0,10*34, "Livre 10", 8);
	wsDisplayText(0,11*34, "Livre 11", 8);
	wsDisplayText(0,12*34, "Livre 12", 8);
	wsDisplayText(0,13*34, "Livre 13", 8);
	wsDisplayText(0,14*34, "Livre 14", 8);
	
	wsDisplayText(0,15*34, "Livre Internet", 14);
	wsDisplayText(0,16*34, "Shutdown", 8);
}

int fct_Selection(void)//Fonction d'affichage pour selectionner le livre avec une ligne en dessous
{	
	wsInit();
	
	fct_AffichageSelection();//Affiche toutes les options
	wsDrawLine(0,1*34+2,20,1*34+2);
	
	wsRefresh();
	
	while(BoutonSelection != 1)//On navigue tant que nous n'avons pas appuye sur "enter"
	{
		if(FlecheBas == 1)//On sous-ligne les livres vers le bas
		{
			i = i + 1;
			fct_AffichageSelection();//Affiche a chaque fois toutes les selections
			wsDrawLine(0,i*34+2,20,i*34+2);//On dessine la ligne juste en dessous du nom du livre(2 pixels en dessous)
			wsRefresh();//Actualiser l'ecran
			if(i > 16)
			{
				i = 0;
			}
		}
		
		if(FlecheHaut == 1)//On sous-ligne les livres vers le haut
		{
			i = i - 1;
			fct_AffichageSelection();//Affiche a chaque fois toutes les selections
			wsDrawLine(0,i*34+2,20,i*34+2);//On dessine la ligne juste en dessous du nom du livre(2 pixels en dessous)
			wsRefresh();//Actualiser l'ecran
			if(i < 0)
			{
				i = 0;
			}
		}
	}
}
int main(void)
{

	fct_Selection(); //Fonction d'affichage pour selectionner le livre

        if (wsInit() == 0) {
                printf("Yeah\n");
        } else {
                printf("Awww\n");
        }

        FILE *fp;
        char c;
        int n = 0;

        fp = fopen("book_to_read.txt","r");

        if(fp == NULL) {
		perror("Error in opening file");
		return(-1);
	}

	for(int a = 0; a < 1000; a++) {
	      c = fgetc(fp);
	      if( feof(fp) ) {
	           break ;
	      }

	      buffer_texte[a] = c;
        }

        fclose(fp);

        wsClear();

	wsDisplayText(10, 0, buffer_texte, 65);
	wsDisplayText(10, 28, &buffer_texte[65], 65);
	wsDisplayText(10, 56, &buffer_texte[130], 65);
	wsDisplayText(10, 84, &buffer_texte[195], 65);
	wsDisplayText(10, 112, &buffer_texte[260], 65);
	wsDisplayText(10, 140, &buffer_texte[365], 65);
	wsDisplayText(10, 168, &buffer_texte[425], 65);
	wsDisplayText(10, 196, &buffer_texte[490], 65);
	wsDisplayText(10, 224, &buffer_texte[555], 65);
	wsDisplayText(10, 252, &buffer_texte[620], 65);
	wsDisplayText(10, 280, &buffer_texte[685], 65);
	wsDisplayText(10, 308, &buffer_texte[750], 65);
	wsDisplayText(10, 414, &buffer_texte[815], 65);
	wsDisplayText(10, 442, &buffer_texte[880], 65);
	wsDisplayText(10, 470, &buffer_texte[945], 65);
	wsDisplayText(10, 498, &buffer_texte[1010], 65);
	wsDisplayText(10, 526, &buffer_texte[1075], 65);
	wsDisplayText(10, 554, &buffer_texte[1140], 65);
	wsDisplayText(10, 582, &buffer_texte[1205], 65);
	wsDisplayText(10, 610, &buffer_texte[1270], 65);


        wsRefresh();

        return 0;
}
