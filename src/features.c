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
    int width, height, channel_count, index, R, G, B;

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

    index = 9 * channel_count;

    R = data[index];
    G = data[index + 1];
    B = data[index + 2];

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
    int W, H, x, y, max_somme, max_x, max_y, channel_count, result, index, R, G, B, somme, max_index;
    unsigned char *data;

    max_y = 0;
    max_x = 0;
    max_somme = -1;

    result = read_image_data(filename, &data, &W, &H, &channel_count);
    if (result == 0)
    {
        printf("Erreur avec le fichier %s\n", filename);
        return;
    }

    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            index = (y * W + x) * channel_count;
            
            R = data[index];
            G = data[index + 1];
            B = data[index + 2];

            somme = R + G + B;

            if (somme > max_somme)
            {
                max_somme = somme;
                max_x = x;
                max_y = y;
            }
        }
    }
    max_index = (max_y * W + max_x) * channel_count;
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
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
    int nouv_W = H;  
    int nouv_H = W;
    unsigned char *new_data = malloc(nouv_W * nouv_H * 3);
    for (i = 0; i < H; i++) {  
        for (j = 0; j < W; j++) {  
   
            int ancienne_pos = (i * W + j) * 3;
            int nouv_ligne = W - 1 - j;
            int nouv_colonne = i;
            int nouv_pos = (nouv_ligne * nouv_W + nouv_colonne) * 3;
            
            new_data[nouv_pos] = data[ancienne_pos]; 
            new_data[nouv_pos + 1] = data[ancienne_pos + 1];  
            new_data[nouv_pos + 2] = data[ancienne_pos + 2];
        }
    }
    write_image_data("image_out.bmp", new_data, nouv_W, nouv_H);
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
void color_gray(char *filename){
    unsigned char *data;
    int i, width, height, channel_count, total_pixels, pixel_start;
    unsigned char gray_value;

    read_image_data(filename, &data, &width, &height, &channel_count);

    total_pixels = width * height;

    for (i = 0; i < total_pixels; i++) {
        pixel_start = i * channel_count;

        
        gray_value = (data[pixel_start] + data[pixel_start + 1] + data[pixel_start + 2]) / 3;
        
        data[pixel_start] = gray_value;
        data[pixel_start + 1] = gray_value;
        data[pixel_start + 2] = gray_value;
    }

    write_image_data("image_out.bmp", data, width, height);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}

void mirror_horizontal(char *filename) {
    unsigned char *data;
    int W, H, channel_count, i, j;

    int resultat = read_image_data(filename, &data, &W, &H, &channel_count);
    if (resultat == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
    unsigned char *new_data = malloc(W * H * 3);
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            int pos_old = (i * W + j) * 3;
            int pos_new = (i * W + (W - 1 - j)) * 3;

            new_data[pos_new] = data[pos_old];
            new_data[pos_new + 1] = data[pos_old + 1];
            new_data[pos_new + 2] = data[pos_old + 2];
        }
    }

    write_image_data("image_out.bmp", new_data, W, H);
    printf("image_out.bmp\n");
    free_image_data(data);
    free(new_data);
}

void mirror_vertical(char *filename) {
    unsigned char *data;
    int W, H, channel_count, i, j;

    int resultat = read_image_data(filename, &data, &W, &H, &channel_count);
    if (resultat == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }

    unsigned char *new_data = malloc(W * H * 3);

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            int pos_old = (i * W + j) * 3;
            int pos_new = ((H - 1 - i) * W + j) * 3;

            new_data[pos_new] = data[pos_old];
            new_data[pos_new + 1] = data[pos_old + 1];
            new_data[pos_new + 2] = data[pos_old + 2];
        }
    }

    write_image_data("image_out.bmp", new_data, W, H);
    printf("image_out.bmp\n");
    free_image_data(data);
    free(new_data);
}

void mirror_total(char *filename) {
    unsigned char *data;
    int W, H, channel_count, i, j;

    int resultat = read_image_data(filename, &data, &W, &H, &channel_count);
    if (resultat == 0) {
        printf("Erreur de fichier: %s\n", filename);
        return;
    }

    unsigned char *new_data = malloc(W * H * 3);

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            int pos_old = (i * W + j) * 3;
            int pos_new = ((H - 1 - i) * W + (W - 1 - j)) * 3;

            new_data[pos_new] = data[pos_old];
            new_data[pos_new + 1] = data[pos_old + 1];
            new_data[pos_new + 2] = data[pos_old + 2];
        }
    }

    write_image_data("image_out.bmp", new_data, W, H);
    printf("image_out.bmp\n");
    free_image_data(data);
    free(new_data);
}
void color_gray_luminance(char *filename){
    unsigned char *data;
    int i, width, height, channel_count, total_pixels, pixel_start;
    unsigned char gray_value;

    read_image_data(filename, &data, &width, &height, &channel_count);

    total_pixels = width * height;

    for (i = 0; i < total_pixels; i++) {
        pixel_start = i * channel_count;

        
        gray_value = (unsigned char)(0.21 * data[pixel_start] + 0.72 * data[pixel_start + 1] + 0.07 * data[pixel_start + 2]);
        
        
        data[pixel_start] = gray_value;
        data[pixel_start + 1] = gray_value;
        data[pixel_start + 2] = gray_value;    
    }

    write_image_data("image_out.bmp", data, width, height);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}
void color_desaturate(char *filename){
    unsigned char *data;
    int i, width, height, channel_count, total_pixels, pixel_start;
    unsigned char gray_value;

    read_image_data(filename, &data, &width, &height, &channel_count);

    total_pixels = width * height;

    for (i = 0; i < total_pixels; i++) {
        pixel_start = i * channel_count;

        gray_value = (unsigned char)(0.21 * data[pixel_start] + 0.72 * data[pixel_start + 1] + 0.07 * data[pixel_start + 2]);
        
        data[pixel_start] = (data[pixel_start] + gray_value) / 2;  
        data[pixel_start + 1] = (data[pixel_start + 1] + gray_value) / 2;
        data[pixel_start + 2] = (data[pixel_start + 2] + gray_value) / 2;
    }

    write_image_data("image_out.bmp", data, width, height);
    printf("image_out.bmp\n");
    
    free_image_data(data);
}
void scale_bilinear (char *filename, float scale) {
    unsigned char *data, *new_data;
    int width, height, channel_count;
    int new_width, new_height;
    int x, y, c;
    float src_x, src_y;
    int x1, y1, x2, y2;
    float dx, dy;
    unsigned char q11, q12, q21, q22;
    float value;

    read_image_data(filename, &data, &width, &height, &channel_count);

    new_width = (int)(width * scale);
    new_height = (int)(height * scale);

    new_data = (unsigned char*)malloc(new_width * new_height * channel_count);

    for (y = 0; y < new_height; y++) {
        for (x = 0; x < new_width; x++) {
            
            src_x = x / scale;
            src_y = y / scale;

            x1 = (int)src_x;
            y1 = (int)src_y;
            x2 = x1 + 1;
            y2 = y1 + 1;

            if (x2 >= width) x2 = width - 1;
            if (y2 >= height) y2 = height - 1;

            dx = src_x - x1;
            dy = src_y - y1;

            for (c = 0; c < channel_count; c++) {
                
                q11 = data[(y1 * width + x1) * channel_count + c];
                q12 = data[(y2 * width + x1) * channel_count + c];
                q21 = data[(y1 * width + x2) * channel_count + c];
                q22 = data[(y2 * width + x2) * channel_count + c];

            
                value = q11 * (1 - dx) * (1 - dy) +
                        q21 * dx * (1 - dy) +
                        q12 * (1 - dx) * dy +
                        q22 * dx * dy;

                new_data[(y * new_width + x) * channel_count + c] = (unsigned char)value;
            }
        }
    }

    write_image_data("image_out.bmp", new_data, new_width, new_height);
    printf("image_out.bmp\n");

    free_image_data(data);
    free(new_data);
}