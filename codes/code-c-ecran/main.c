#include <stdio.h>
#include <stdlib.h>

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
        if (wsInit() == 0) {
                printf("Yeah\n");
        } else {
                printf("Awww\n");
        }

	wsClear();
	wsDisplayText(180, 180, "Livre 1", 7);
	wsDrawCircle(218, 230, 15);
	wsDisplayText(520, 180, "Livre 2", 7);
	wsDrawCircle(558, 230, 15);
	wsDisplayText(340, 250, "Eteindre", 8);
	wsDrawCircle(390, 300, 15);
	wsRefresh();


	while(1);

        // Determine lieu de sauvegarde de l'image de mise en veille.
        lookatmicrosd();

        wsClear();
        
        
        // Permet l'affichage de l'image de mise en veille.
        image_write();

        wsRefresh();
        
        // Evaluer la possibilite d'insertion d'un delai.
        
	system("sudo shutdown -P now");

        
        return 0;
}
