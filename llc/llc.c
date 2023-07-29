#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char* sys = malloc(sizeof(char) * 35);
    sprintf(sys, "llc %s -o a.s", argv[1]);

    printf("%s\n", sys);
    system(sys);

    sprintf(sys, "gcc a.s -o a.out");
    printf("%s\n", sys);
    system(sys);

    free(sys);
    return 0;
}
