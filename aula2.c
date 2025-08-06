#include <stdio.h>
#include <string.h>

char *searchChar(char *n, char c) {
    for(int i = 0; i < strlen(n); i++) {
        if(n[i] == c) {
            return &n[i];
        } 
    }

    return NULL;
}

int main() {
    char n[100], c, *result;

    printf("Digite uma string: ");
    fgets(n, sizeof(n), stdin);
    printf("Digite um caractere: ");
    scanf(" %c", &c);

    result = searchChar(n, c);

    if(result != NULL) {
        printf("Caractere '%c' encontrado: ': %s\n", *result, result);
    } else {
        printf("Caractere '%c' nao encontrado na string.\n", c);
    }

    return 0;
}