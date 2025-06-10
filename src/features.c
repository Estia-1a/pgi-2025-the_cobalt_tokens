#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void first_pixel (char *filename){

    unsigned char* data;
    int width, height, channel_count;
 
    if (read_image_data(filename, &data, &width, &height, &channel_count)!=0) {
       int R=data[0], G=data[1], B=data[2];
        
        printf("first_pixel : %d, %d, %d", R, G, B);
        free_image_data(data);
    } else { 
        printf("Erreur avec l'image: %s\n", filename);
    }
}


void dimension(char* filename) {
    
    unsigned char* data;
    int width, height, channel_count;

    if (read_image_data(filename, &data, &width, &height, &channel_count)==0) {
        printf("Erreur avec le fichier: %s\n", filename);
    } else {
        printf("dimension: %d, %d\n", width, height);
        free_image_data(data);
    }
}

void second_line(char *filename){
    
    int index, width, height, channel_count, R, G, B;
    unsigned char* data;

    
    if (read_image_data(filename, &data, &width, &height, &channel_count)==0) {
        printf("Erreur avec le fichier: %s\n", filename);

    } else if (height < 2 ){
        printf ("Erreur : L'image doit avoir au moins 2 lignes de pixel\n");
    } else {

        index = width * 3;  

        R = data[index];
        G = data[index + 1];
        B = data[index + 2];

        printf("second_line: %d, %d, %d\n", R, G, B);
        free_image_data(data);
            
    }
    int R, G, B;
 
    int index = 9 * channel_count;
    R = data[index];
    G = data[index + 1];
    B = data[index + 2];
 
    printf("tenth_pixel: %d, %d, %d\n", R, G, B);
 
    free_image_data(data);
}


void print_pixel( char *filename, int x, int y ){
     unsigned char *data;
    int width, height, channel_count;

     if (read_image_data(filename, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }

    pixelRGB* pixel = get_pixel(data, width, height, channel_count, x, y);
    if (pixel == NULL) {
        printf("Coordonnées invalides : (%d, %d)\n", x, y);
    } else {
        printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    }

    free_image_data(data);
}

