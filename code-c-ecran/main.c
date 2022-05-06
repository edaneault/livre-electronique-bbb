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

        lookatmicrosd();

        wsClear();

        image_write();

        wsRefresh();
        
        
	system("sudo shutdown -P now");

        
        return 0;
}
