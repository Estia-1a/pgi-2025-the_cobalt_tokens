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



























































void tenth_pixel(char* filename) {
    unsigned char* data;
    int width, height, channel_count;

    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
    int R, G, B;

    int index = 9 * channel_count;
    R = data[index];
    G = data[index + 1];
    B = data[index + 2];

    printf("tenth_pixel: %d, %d, %d\n", R, G, B);

    free_image_data(data);
}
