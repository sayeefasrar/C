#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,"Usage: ./recover card.raw\n");
        return 1;
    }
    
    char *infile = argv[1];
    
    FILE *inptr = fopen (infile, "r");
    
    if (inptr == NULL)
    {
        fprintf (stderr, "Usage: Cannot open %s\n", infile);
        return 2;
    }
    
    //fread(&inptr, 512, 1, infile);
    //int *buffer = malloc(512);
    uint8_t *buffer = malloc(512 * sizeof(uint8_t));
    char filename[50];
    int nameTracker = 0;
    FILE *img = NULL;
    
    do{
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf (filename, "%03i.jpg", nameTracker);
            nameTracker++;
            img = fopen(filename, "w");
            fwrite (buffer, 512, 1, img);
                         
        }
        
        else
        {
            if (img !=NULL)
            {
                fwrite (buffer, 512, 1, img);
            }
        }
        
    } while ( fread (buffer, 512, 1, inptr) == 1);
    //free(buffer);
}