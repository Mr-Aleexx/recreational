#include <stdio.h>

int main () {
    char* file_name = "/dev/null";
    FILE *dev_null =  fopen(file_name, "r") ;
    
    if (dev_null == NULL) {
        printf("Error reading the file %s\n", file_name);
        return 1;
    }

    char c;
    while((c = fgetc(dev_null)) != EOF) {
        putchar(c);
    }
    
    fclose(dev_null);
    return 0;
}
