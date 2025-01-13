#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a; // Puntero `p` apunta a `a`

    printf("Valor de 'a': %d\n", a); // Imprime 10
    printf("Dirección de 'a' (&a): %p\n", &a); // Dirección de `a`
    printf("Valor de 'p'(p): %p\n", p); // Dirección almacenada en `p` (misma que la de `a`)
    printf("Valor apuntado por 'p'(*p): %d\n", *p); // 10 (valor de `a` al que apunta `p`)

    *p = 20; // Cambia el valor de `a` a 20
    printf("----------------------------\n");

    printf("Valor de 'a': %d\n", a); // Imprime 10
    printf("Dirección de 'a' (&a): %p\n", &a); // Dirección de `a`
    printf("Valor de 'p'(p): %p\n", p); // Dirección almacenada en `p` (misma que la de `a`)
    printf("Valor apuntado por 'p'(*p): %d\n", *p); // 10 (valor de `a` al que apunta `p`)
    printf("Valor de &p): %d\n", &p); // 10 (valor de `a` al que apunta `p`)

    return 0;
}
