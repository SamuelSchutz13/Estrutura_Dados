#include <stdio.h>

void printvint(int a[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

void cmpvint(int a1[], int a2[], int n) {
    for(int i = 0; i < n; i++) {
        if(a1[i] != a2[i]) {
            printf("Arrays sao diferentes %d: %d vs %d\n", i, a1[i], a2[i]);
            return;
        }
    }

    printf("Arrays sao iguais.\n");
}

void instring(char string[], char c) {
    int found = 0;

    for(int i = 0; string[i] != '\0'; i++) {
        if(string[i] == c) {
            found = 1;
            printf("Caractere '%c' encontrado na posicao %d.\n", c, i);
            break;
        }
    }

    if(!found) {
        printf("Caractere '%c' nao encontrado na string.\n", c);
    }
}

int main() {
    int inteiros[] = {1, 2, 3, 4, 5};
    int inteiro2[] = {1, 4, 3, 2, 1};
    char string1[] = "Hello, world!";

    printvint(inteiros, 5);
    cmpvint(inteiros, inteiro2, 5);
    instring(string1, 'd');

    return 0;
}