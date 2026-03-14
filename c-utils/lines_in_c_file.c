#include <stdio.h>

#define MAX_N_FILE 10



int number_of_lines(char* p_file) {
    int n = 0;
    
    FILE* file = fopen(p_file, "r");
        
    if (!file) {
        printf("Error reading file\n");
        return -1;
    }

    int c;
    while((c = getc(file)) != EOF) {
        if (c == '\n') {
            n += 1;
        } 
    }

    fclose(file);
    return n;
}

void  print_file(char * p_file) {
    
}


int main (int argc, char* argv[]) {
    
    if (argc > MAX_N_FILE) {
        printf("Error max number of files reached\n");
        return 0;
    }

    int n   = 0;
    int res = 0;
    for (int i = 1 ; i < argc ; i++) {
        n = number_of_lines(argv[i]);
        printf("There is %d lines in the file : %s\n", n, argv[i]);
        res += n;
        
     }

    printf("The total number of lines is %d\n", res);

    return 0;
}
