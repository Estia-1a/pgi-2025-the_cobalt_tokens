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
