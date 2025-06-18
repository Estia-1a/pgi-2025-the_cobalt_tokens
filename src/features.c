#include <estia-image.h>
#include <stdio.h>
#include <limits.h>
#include "features.h"
#include "utils.h"
#include <stdlib.h>

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld()
{
    printf("Hello World !");
}

void first_pixel(char *filename)
{

    unsigned char *data;
    int width, height, channel_count;

    if (read_image_data(filename, &data, &width, &height, &channel_count) != 0)
    {
        int R = data[0], G = data[1], B = data[2];

        printf("first_pixel : %d, %d, %d", R, G, B);
        free_image_data(data);
    }
    else
    {
        printf("Erreur avec l'image: %s\n", filename);
    }
}

void dimension(char *filename)
{

    unsigned char *data;
    int width, height, channel_count;

    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0)
    {
        printf("Erreur avec le fichier: %s\n", filename);
    }
    else
    {
        printf("dimension: %d, %d\n", width, height);
        free_image_data(data);
    }
}

void second_line(char *filename)
{

    int index, width, height, channel_count, R, G, B;
    unsigned char *data;

    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0)
    {
        printf("Erreur avec le fichier: %s\n", filename);
    }
    else if (height < 2)
    {
        printf("Erreur : L'image doit avoir au moins 2 lignes de pixel\n");
    }
    else
    {

        index = width * 3;

        R = data[index];
        G = data[index + 1];
        B = data[index + 2];

        printf("second_line: %d, %d, %d\n", R, G, B);
        free_image_data(data);
    }
}

void tenth_pixel(char *filename)
{
    unsigned char *data;
    int width, height, channel_count;

    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0)
    {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }

    if (width * height < 10)
    {
        printf("Erreur : L'image doit contenir au moins 10 pixels\n");
        free_image_data(data);
        return;
    }

    int index = 9 * channel_count;

    int R = data[index];
    int G = data[index + 1];
    int B = data[index + 2];

    printf("tenth_pixel: %d, %d, %d\n", R, G, B);

    free_image_data(data);
}

void print_pixel(char *filename, int x, int y)
{
    unsigned char *data;
    int width, height, channel_count;

    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0)
    {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }

    pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
    if (pixel == NULL)
    {
        printf("Coordonnées invalides : (%d, %d)\n", x, y);
    }
    else
    {
        printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    }

    free_image_data(data);
}

void max_pixel(char *filename)
{
    int W, H, x, y, max_somme = -1, max_x = 0, max_y = 0, channel_count;
    unsigned char *data;

    int result = read_image_data(filename, &data, &W, &H, &channel_count);
    if (result == 0)
    {
        printf("Erreur avec le fichier %s\n", filename);
        return;
    }

    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            int index = (y * W + x) * channel_count;
            int R, G, B;

            R = data[index];
            G = data[index + 1];
            B = data[index + 2];

            int somme = R + G + B;

            if (somme > max_somme)
            {
                max_somme = somme;
                max_x = x;
                max_y = y;
            }
        }
    }
    int max_index = (max_y * W + max_x) * channel_count;
    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, data[max_index], data[max_index + 1], data[max_index + 2]);
}

void min_component(char *filename, char component)
{
    int channels, H, W;
    unsigned char *data = NULL;

    int result = read_image_data(filename, &data, &W, &H, &channels);
    if (result == 0)
    {
        printf("Erreur avec le chargement de l'image : %s\n", filename);
        return;
    }

    int min_x = 0, min_y = 0;
    int min_valeur = 256;
    int y, x;
    int valeur = 0;

    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            pixelRGB* pix = get_pixel(data, W, H, channels, x, y);
            if (component == 'R')
            {
                valeur = pix->R;
            }
            else if (component == 'G')
            {
                valeur = pix->G;
            }
            else if (component == 'B')
            {
                valeur = pix->B;
            }
            else
            {
                printf("composant non valide : %c\n", component);
            }

            if (valeur < min_valeur)
            {
                min_valeur = valeur;
                min_x = x;
                min_y = y;
            }
        }
        
    }
    printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_valeur);
        free_image_data(data);
}

void min_pixel(char *filename){
    int W, H, x, y, min_somme=256*3+1, min_x=0, min_y=0, channel_count;
    unsigned char *data;

    int result = read_image_data(filename, &data, &W, &H, &channel_count);
    if (result == 0)
    {
        printf("Erreur avec le fichier %s\n", filename);
        return;
    }

    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            int index = (y * W + x) * channel_count;
            int R, G, B;

            R = data[index];
            G = data[index + 1];
            B = data[index + 2];

            int somme = R + G + B;

            if (somme<min_somme){
                min_somme=somme;
                min_x=x;
                min_y=y;
            }
        }
    }
    int min_index=(min_y*W+min_x)*channel_count;
    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, data[min_index], data[min_index + 1], data[min_index + 2]) ;
}

void color_red(char *filename){
    unsigned char *data;
    int i, width, height, channel_count, total_pixels, pixel_start;

    read_image_data(filename, &data, &width, &height, &channel_count);

    total_pixels = width * height;

    for (i = 0; i < total_pixels; i++) {
        pixel_start = i * channel_count;

        data[pixel_start + 1] = 0;
        data[pixel_start + 2] = 0;
    }


    write_image_data("image_out.bmp", data, width, height);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}

void max_component(char *filename, char component)
{
    int channels, H, W;
    unsigned char *data = NULL;

    int result = read_image_data(filename, &data, &W, &H, &channels);
    if (result == 0)
    {
        printf("Erreur avec le chargement de l'image : %s\n", filename);
        return;
    }

    int max_x = 0, max_y = 0;
    int max_valeur = 0;
    int y, x;
    int valeur = 0;

    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            pixelRGB* pix = get_pixel(data, W, H, channels, x, y);
            if (component == 'R')
            {
                valeur = pix->R;
            }
            else if (component == 'G')
            {
                valeur = pix->G;
            }
            else if (component == 'B')
            {
                valeur = pix->B;
            }
            else
            {
                printf("composant non valide : %c\n", component);
            }

            if (valeur > max_valeur)
            {
                max_valeur = valeur;
                max_x = x;
                max_y = y;
            }
        }
        
    }
    printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_valeur);
        free_image_data(data);
}



void color_green(char *filename){
    unsigned char *data;
    int i, width, height, channel_count, total_pixels, pixel_start;

    read_image_data(filename, &data, &width, &height, &channel_count);

    total_pixels = width * height;

    for (i = 0; i < total_pixels; i++) {
        pixel_start = i * channel_count;

        data[pixel_start] = 0;
        data[pixel_start + 2] = 0; 
        
    }

    write_image_data("image_out.bmp", data, width, height);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}


void color_invert(char *filename){
    unsigned char *data;
    int i, W, H, channel_count, tot_pixels, pixel_start;

        int resultat = read_image_data(filename, &data, &W, &H, &channel_count);
        if (resultat == 0) {
            printf("Erreur avec fichier : %s\n", filename);
            return;
    }

    tot_pixels = W * H;

    for (i = 0; i < tot_pixels; i++) {
        pixel_start = i * channel_count;

        data[pixel_start] = 255 - data[pixel_start];
        data[pixel_start + 1] = 255 - data[pixel_start + 1];
        data[pixel_start + 2] = 255 - data[pixel_start + 2]; 
    }

    write_image_data("image_out.bmp", data, W, H);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}

void color_blue(char *filename){
    unsigned char *data;
    int i, width, height, channel_count, total_pixels, pixel_start;

    read_image_data(filename, &data, &width, &height, &channel_count);

    total_pixels = width * height;

    for (i = 0; i < total_pixels; i++) {
        pixel_start = i * channel_count;

        data[pixel_start] = 0;
        data[pixel_start + 1] = 0; 
        
    }

    write_image_data("image_out.bmp", data, width, height);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}

void rotate_acw(char *filename){
    unsigned char *data;
    int W, H, channel_count, i, j;
    
    int resultat = read_image_data(filename, &data, &W, &H, &channel_count);
    if (resultat == 0) {
        printf("Erreur de fichier: %s\n", filename);
        return;
    }
    int new_W = H;  
    int new_H = W;
    unsigned char *new_data = malloc(new_W * new_H * 3);
    for (i = 0; i < H; i++) {  
        for (j = 0; j < W; j++) {  
   
            int pos_old = (i * W + j) * 3;
            int ligne_new = W - 1 - j;
            int colonne_new = i;
            int pos_new = (ligne_new * new_W + colonne_new) * 3;
            
            new_data[pos_new] = data[pos_old]; 
            new_data[pos_new + 1] = data[pos_old + 1];  
            new_data[pos_new + 2] = data[pos_old + 2];
        }
    }
    write_image_data("image_out.bmp", new_data, new_W, new_H);
    printf("image_out.bmp\n");
    free_image_data(data);
    free(new_data);
}

void rotate_cw(char *filename){
    unsigned char *data;
    int W, H, channel_count, i, j;
    
    int resultat = read_image_data(filename, &data, &W, &H, &channel_count);
    if (resultat == 0) {
        printf("Erreur de fichier: %s\n", filename);
        return;
    }
    int new_W = H;  
    int new_H = W;
    unsigned char *new_data = malloc(new_W * new_H * 3);
    for (i = 0; i < H; i++) {  
        for (j = 0; j < W; j++) {  
   
            int pos_old = (i * W + j) * 3;

            int ligne_new = j;
            int colonne_new = H - 1 - i;
            int pos_new = (ligne_new * new_W + colonne_new) * 3;
            
            new_data[pos_new] = data[pos_old]; 
            new_data[pos_new + 1] = data[pos_old + 1];  
            new_data[pos_new + 2] = data[pos_old + 2];
        }
    }
    write_image_data("image_out.bmp", new_data, new_W, new_H);
    printf("image_out.bmp\n");
    free_image_data(data);
    free(new_data);
}