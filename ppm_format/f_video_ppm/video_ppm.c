#include <stdio.h>

#define S_FACTOR 30

int main(int argc, char* argv[]) {
    char file_names[256];

    for (int i = 0 ; i < 60 ; i++) {
        snprintf(file_names, sizeof(file_names), "ftppm_%02d.ppm",i);
        const char* file_name = file_names;

        FILE *p_file = fopen(file_name, "wb");
        int width  = 16 * S_FACTOR;
        int height = 9  * S_FACTOR;

        //printf("Image size : %d:%d\n", width, height);

        fprintf(p_file, "P6\n");
        fprintf(p_file, "%d %d\n", width, height);
        fprintf(p_file, "255\n");

        for (int y = 0 ; y < height ; y++) {
            for (int x = 0 ; x < width ; x++) {
                unsigned char r,g,b;
                if (((x + i)/S_FACTOR + (y + i)/S_FACTOR)%2) {
                    r = 0xFF;
                    g = 0xFF;
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
        printf("Generated file n°%d successfully!\n", i + 1);
    }

    return 0;
}
