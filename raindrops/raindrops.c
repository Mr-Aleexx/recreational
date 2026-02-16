#include <stdio.h>
#include <termios.h>


struct termios config;

void term_config() {
    config.c_lflag &= ECHO;
}

int main() {

    term_config();

    printf("Hello World!\n");


    return 0;
}
