#include <stdio.h>

#include "waveshare.h"

int main(void)
{
        if (wsInit() == 0) {
                printf("Yeah\n");
        } else {
                printf("Awww\n");
        }

        wsClear();

        for(int i = 0; i < 22; i++) {
                wsDisplayText(0,i*28, "Ceci est un livre electronique créé par des étudiants du Collège Maisonneuve", 100);
        }

        wsRefresh();

        return 0;
}
