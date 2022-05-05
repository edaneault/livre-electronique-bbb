#include <stdio.h>

#include "waveshare.h"

char buffer_texte[1000];

i = 0;

int fct_AffichageSelection(void)
{
	wsClear();
	
	wsDisplayText(0,1*28, "Livre 01", 8);
	wsDisplayText(0,2*28, "Livre 02", 8);
	wsDisplayText(0,3*28, "Livre 03", 8);
	wsDisplayText(0,4*28, "Livre 04", 8);
	wsDisplayText(0,5*28, "Livre 05", 8);
	wsDisplayText(0,6*28, "Livre 06", 8);
	wsDisplayText(0,7*28, "Livre 07", 8);
	wsDisplayText(0,8*28, "Livre 08", 8);
	wsDisplayText(0,9*28, "Livre 09", 8);
	wsDisplayText(0,10*28, "Livre 10", 8);
	wsDisplayText(0,11*28, "Livre 11", 8);
	wsDisplayText(0,12*28, "Livre 12", 8);
	wsDisplayText(0,13*28, "Livre 13", 8);
	wsDisplayText(0,14*28, "Livre 14", 8);
	
	wsDisplayText(0,15*28, "Livre Internet", 14);
	wsDisplayText(0,16*28, "Retour", 6);
}

int fct_Selection(void)
{	
	wsInit();
	
	fct_AffichageSelection();
	
	while(BoutonSelection != 1)
	{
		if(FlecheBas == 1)
		{
			i = i + 1;
			fct_AffichageSelection();
			wsDrawLine(0,i*28+2,20,i*28+2);
			wsRefresh();
			if(i > 16)
			{
				i = 0
			}
		}
		
		if(FlecheHaut == 1)
		{
			i = i - 1;
			fct_AffichageSelection();
			wsDrawLine(0,i*28+2,20,i*28+2);
			wsRefresh();
			if(i < 0)
			{
				i = 0
			}
		}
	}
	
	wsRefresh();
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
	 wsDisplayText(10, 582 , &buffer_texte[1205], 65);
	 wsDisplayText(10, 610, &buffer_texte[1270], 65);

        wsRefresh();

        return 0;
}
