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

        image_write();

        wsRefresh();

        return 0;
}
