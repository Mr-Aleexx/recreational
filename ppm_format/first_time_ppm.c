#include <stdio.h>

#define S_FACTOR 100

int main(int argc, char* argv[]) {
    // ftppm = first_time_ppm
    
    char* file_name = argv[1];
    if (argc < 2) {
        printf("Error\n Usage : ./first_time_ppm <output_file.ppm>\n");
        return 0;
    }

    FILE *p_file = fopen(file_name, "wb");
    int width  = 16 * S_FACTOR;
    int height = 9  * S_FACTOR;
    
    printf("Image size : %d:%d\n", width, height);

    fprintf(p_file, "P6\n");
    fprintf(p_file, "%d %d\n", width, height);
    fprintf(p_file, "255\n");

    for (int y = 0 ; y < height ; y++) {
        for (int x = 0 ; x < width ; x++) {
            unsigned char r,g,b;
            if ((x/S_FACTOR + y/S_FACTOR)%2) {
                r = 0xFF;
                g = 0x00;
                b = 0x00;
                //printf("r,b,g : %d,%d,%d\n", r, g, b);
            }
            else {
                r = 0x00;
                g = 0x00;
                b = 0x00;
            }

            fputc(r,p_file);
            fputc(g,p_file);
            fputc(b,p_file);
        }
    }
    fclose(p_file);
    printf("Generated : %s successfully!\n", file_name);
    return 0;
}
