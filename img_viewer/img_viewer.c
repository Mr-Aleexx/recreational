#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define RGB 3
#define SIGNATURE_PNG_LENGTH 8
const int png_signature_bytes[] = {137, 80, 78, 71, 13, 10, 26, 10};

void print_array(int* array, int size) {
    for (int i = 0 ; i < size - 1 ; i++) {
        printf("%d ", array[i]);
    }
    printf("%d \n" ,array[size - 1]);
}

int get_file_size(FILE* p_file) {
    fseek(p_file, 0, SEEK_END);
    return ftell(p_file);
}

void print_pixel(int r, int g, int b) {
    printf("\033[48;2;%d;%d;%dm \033[0m", r, g, b);
}

int is_png_file(FILE* p_file) {
    int c;
    int n = 0;
    while ((c = getc(p_file)) == png_signature_bytes[n] && n < SIGNATURE_PNG_LENGTH) {
        n++;
    }
    return n == SIGNATURE_PNG_LENGTH ? 1 : 0;
}

void print_file(FILE* p_file) {

    int* colors = malloc(RGB * sizeof(int));

    int c;
    int n = 0;

    while((c = getc(p_file)) != EOF) {
        colors[n] = c;
        if ((n + 1) % RGB == 0) {
            print_array(colors, RGB);
            n = -1;
        }
        n++;
    }
    printf("\n");
    free(colors);
}

void reset_file(FILE* p_file) {
    rewind(p_file);
    fseek(p_file, SIGNATURE_PNG_LENGTH, SEEK_SET);
}

void print_only_char(FILE* p_file){
    
    int n = 0;
    int c;
    int in_group = 0;

    while((c = getc(p_file)) != EOF) {
        if (isalpha(c)) {
            if (in_group) {
                printf(" ");           
            }
            printf("%c:%d", c, n);      
            in_group = 1;
        } else {
            if (in_group) {
                printf("\n");        
                in_group = 0;
            }
        }
        n++;
    }
    if (in_group) {
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("Usage : img_viwer <img>\n");
        return 1;
    }
    FILE* p_file = fopen(argv[1], "r");

    if (p_file == NULL) {
        printf("Failed to open the file");
        fclose(p_file);
        return 1;
    }

    int file_size = get_file_size(p_file);
    rewind(p_file);
    
    if (is_png_file(p_file)) {
        fseek(p_file, SIGNATURE_PNG_LENGTH, SEEK_SET);
        printf("This is a png file\n");
    }
    else {
        printf("This is NOT a png file\n");
        return 1;
    }
    //print_file(p_file);
    reset_file(p_file);
    print_only_char(p_file);
    printf("File size : %d\n", file_size);

    fclose(p_file);
    
    return 0;
}
