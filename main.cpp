#include <fstream>
#include <iostream>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

png_infop info_ptr;
png_bytepp row_pointers;


// Encode the 4 channels
void encode_channels(int red, int green, int blue, int opacity)
{
    // From " " to "176"
    int min = 40;
    int max = 176;
    
    // y = (red + green + blue + opacity) % 176;

    printf("%c", ((red + green + blue + opacity) % max) + 40);
}


void read_png(char *file_name)
{
    FILE *fp = fopen(file_name, "rb+");
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    row_pointers = png_get_rows(png_ptr, info_ptr);

    // Print each pixel value
    for(int i = 0; i < png_get_image_height(png_ptr, info_ptr); i++)
    {
        for(int j = 0; j < png_get_image_width(png_ptr, info_ptr) * 4; j = j + 4)
        {
            //printf("%d %d %d ", row_pointers[i][j], row_pointers[i][j+1], row_pointers[i][j + 2]);
            // print " " if transparent
            // if(row_pointers[i][j] == 0 && row_pointers[i][j+1] == 0 && row_pointers[i][j+2] == 0 && row_pointers[i][j + 3] == 0)
            // {
            //     printf(" ");
            // }else
            // {
            //     printf("w");
            // }
            encode_channels(row_pointers[i][j], row_pointers[i][j+1], row_pointers[i][j + 2], row_pointers[i][j+3]);
        }

        printf("\n");
    }


    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(fp);
}

void write_png(char *file_name)
{
    FILE *fp = fopen(file_name, "wb+");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

int main()
{
    
    // ofstream myFile;
    // myFile.open("textArt.txt");
    // myFile << "This gonna be a Text Art";
    // myFile.close();
    char name[] = "pic.png";
    char name2[] = "output.png";
    read_png(name);
    write_png(name2);



    return 0;
}

