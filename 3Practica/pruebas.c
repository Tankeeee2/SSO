#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            printf("Argumento %d: %s\n", i, argv[i]);
        }
    } else {
        printf("No se han proporcionado argumentos.\n");
    }
    return 0;
}
