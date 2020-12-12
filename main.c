#include <stdio.h>
#include <string.h>

#include "make.c"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("error: too few arguments");
        return 1;
    }

    char* PATH = argv[1];

    phrase* buffer[ROW_SIZE];

    FILE* fp;

    if ((fp = fopen(PATH, "r")) == NULL) {
        puts("error: cannot open the file");
        return 1;
    }

    int size = buffer_get(buffer, fp);

    fclose(fp);

    if (argc < 3) {
        eval(NULL, buffer, size);
    } else {
        eval(argv[2], buffer, size);
    }
    
    return 0;
}