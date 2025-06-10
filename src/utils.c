#include <estia-image.h>
#include "utils.h"
#include <stddef.h>

/**
 * @brief Here, you have to define functions of the pixel struct : getPixel and setPixel.
 * 
 */

pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y) {
    if (data == NULL){
        return NULL;
    } else if (x >= width){
        return NULL;
    } else if (y >= height){
        return NULL;
    } else if (n < 3){
        return NULL;
    }

    return (pixelRGB*) &data[(y * width + x) * n];
}