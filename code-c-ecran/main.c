#include <stdio.h>
#include <stdlib.h>

#include "waveshare.h"


int main(void)
{
        if (wsInit() == 0) {
                printf("Yeah\n");
        } else {
                printf("Awww\n");
        }

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
