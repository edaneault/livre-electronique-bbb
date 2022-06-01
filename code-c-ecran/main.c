#include <stdio.h>

#include "waveshare.h"

int main(void)
{
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

	      //printf("%c", c);

	      buffer_texte[a] = c;
        }

        fclose(fp);

        wsClear();

        wsDisplayText(10, 0, buffer_texte, 60);
        wsDisplayText(10, 28, &buffer_texte[60], 60);
        wsDisplayText(10, 56, &buffer_texte[120], 60);

        wsRefresh();

        return 0;
}
