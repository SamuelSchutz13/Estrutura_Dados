#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Lista {
    int numero;
    struct Lista *prox;
} Lista;

int randomizarNumeros(Lista **inicio, int qntd, int tam) {
    Lista *novo = (Lista*) malloc(qntd * sizeof(Lista));
    if (!novo) {
        printf("Erro ao alocar memoria.\n");
        return -1;
    }

    for (int i = 0; i < qntd; i++) {
        novo[i].numero = rand() % tam;
        novo[i].prox = (i < qntd - 1) ? &novo[i + 1] : NULL;
    }

    *inicio = novo;
    return 0;

    printf("Quantidade de numeros: %d | Tamanho maximo: %d\n\n", qntd, tam);
}

void imprimirLista(Lista *inicio) {
    Lista *aux = inicio;

    while(aux != NULL) {
        printf("%d ", aux->numero);
        aux = aux->prox;
    }
    
    printf("\n");
}

void bubbleSort(Lista *inicio) {
    if (!inicio) return;

    int trocou;
    Lista *p1;
    Lista *p2 = NULL;

    do {
        trocou = 0;
        p1 = inicio;

        while(p1->prox != p2) {
            if(p1->numero > p1->prox->numero) {
                int temp = p1->numero;
                p1->numero = p1->prox->numero;
                p1->prox->numero = temp;
                trocou = 1;
            }

            p1 = p1->prox;
        }

        p2 = p1;
    } while(trocou);

    printf("Numeros ordenados com Bubble Sort:\n");
    imprimirLista(inicio);
}

int main() {
    Lista *inicio = NULL;
    int opt, qntd, tam;

    printf("Informe a quantidade de numero a serem ordenados: ");
    scanf("%d", &qntd);

    printf("Informe o tamanho maximo dos numeros a serem gerados: ");
    scanf("%d", &tam);

    randomizarNumeros(&inicio, qntd, tam);

    printf("Numeros gerados: \n");  
    imprimirLista(inicio);

    do {
        printf("Escolha uma opcao de ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opt);

        switch(opt) {
        case 1:
            bubbleSort(inicio);
            break;
        case 2:
            printf("Selection Sort selecionado.\n");
            break;
        case 3:
            printf("Insertion Sort selecionado.\n");
            break;
        case 4:
            printf("Quick Sort selecionado.\n");
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }  while(opt != 0);

    free(inicio);
    return 0;
}
