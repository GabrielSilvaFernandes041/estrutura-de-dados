#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a, b = 10;

    a = (int*) malloc(5 * sizeof(int));

    printf("Endereco da VARIAVEL ponteiro (&a): %p\n", (void*)&a);
    printf("Endereco para onde 'a' APONTA (a): %p\n", (void*)a);

    free(a);

    a = &b;
    printf("Novo endereco para onde 'a' aponta: %p (Endereco de b)\n", (void*)a);
    printf("Conteudo apontado (*a):             %d\n", *a);

    return 0;
}