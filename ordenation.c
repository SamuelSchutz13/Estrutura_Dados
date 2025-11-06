#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Lista {
    int numero;
    struct Lista *prox;
} Lista;

void randomizarNumeros(Lista **inicio, int qntd, int tam) {
    srand(time(NULL));
    *inicio = NULL;

    for(int i = 0; i < qntd; i++) {
        Lista *novo = (Lista*) malloc(sizeof(Lista));

        if(!novo) {
            printf("Erro ao alocar memoria.\n");
            exit(1);
        }

        novo->numero = rand() % tam;
        novo->prox = *inicio;
        *inicio = novo;
    }

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

void medirTempo(void (*funcaoOrdenacao)(Lista *), Lista *inicio, const char *nome) {
    clock_t inicioTempo, fimTempo;
    double tempoGasto;

    inicioTempo = clock();
    funcaoOrdenacao(inicio);
    fimTempo = clock();

    tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;

    printf("%s\n - Lista ordenada:\n", nome);
    imprimirLista(inicio);

    printf("Tempo gasto: %.6f segundos\n\n", tempoGasto);
}


void bubbleSort(Lista *inicio) {
    if(!inicio) {
        printf("Lista vazia, nao ordena.\n");
        return;
    }

    int houveTroca;
    Lista *atual;
    Lista *ultimo = NULL;

    do {
        houveTroca = 0;
        atual = inicio;

        while(atual->prox != ultimo) {
            if(atual->numero > atual->prox->numero) {
                int temp = atual->numero;
                atual->numero = atual->prox->numero;
                atual->prox->numero = temp;
                houveTroca = 1;
            }

            atual = atual->prox;
        }

        ultimo = atual;
    } while(houveTroca);
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
    printf("\n");

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
            medirTempo(bubbleSort, inicio, "Bubble Sort");
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
            printf("Saindo\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while(opt != 0);

    free(inicio);
    return 0;
}
