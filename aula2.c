#include <stdio.h>
#include <string.h>

char *searchChar(char *n, char c) {
    for(int i = 0; i < strlen(n); i++) {
        if(n[i] == c) {
            return &n[i]+1;
        } 
    }

    return NULL;
}

int main() {
    char n[100], c;

    printf("Digite uma string: ");
    fgets(n, sizeof(n), stdin);
    printf("Digite um caractere: ");
    scanf(" %c", &c);

    if(searchChar(n, c) !=  NULL) {
        printf("Caractere '%c' encontrado: ': %s\n", c, searchChar(n, c));
    } else {
        printf("Caractere '%c' nao encontrado na string.\n", c);
    }

    return 0;
}