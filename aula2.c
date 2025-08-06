#include <stdio.h>

int returnEnd(char *n, char *c) {
    for(int i = 0; n[i] != '\0'; i++) {
        if(n[i] == *c) {
            printf("Caractere '%c' encontrado na posicao %d.\n", *c, i);
            return 1;
        } 
    }

    printf("Caractere '%c' nao encontrado na string.\n", *c);
    return 0;
}

int main() {
    char n[100];
    char c;

    printf("Digite uma string: ");
    fgets(n, sizeof(n), stdin);
    printf("Digite um caractere: ");
    scanf(" %c", &c);

    returnEnd(n, &c);

    return 0;
}