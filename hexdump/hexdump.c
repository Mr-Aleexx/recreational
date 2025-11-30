#include <stdio.h>
#include <stdlib.h>

int main () {
    int c;
    int mem_addr = 0;
    char* current_string = calloc(0x10, sizeof(char));
    while((c = getchar()) != EOF) {
    
        current_string[mem_addr % 0x10] = c;


        if (mem_addr % 0X10 == 0x0) {        
            printf("%08x ", mem_addr);  
        }

        if (mem_addr % 0x8 == 0) printf(" ");
        printf("%02x ", c);

        mem_addr++;
        if (mem_addr % 0x10 == 0x0) {
            printf("%s", current_string);
            printf("\n");
        } 
    }
    printf("%s", current_string);
    printf("\n%08x", mem_addr);
    printf("\n"); 
}
