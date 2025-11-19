#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Lista {
    int valor;
    struct Lista *prox;
} Lista;

void liberarLista(Lista *inicioLista) {
    Lista *aux;

    while(inicioLista) {
        aux = inicioLista;
        inicioLista = inicioLista->prox;
        free(aux);
    }
}

void randomizarNumeros(Lista **inicioLista, int quantidade, int tamanhoMax) {
    srand(time(NULL));
    *inicioLista = NULL;
    
    for(int i = 0; i < quantidade; i++) {
        Lista *novoNo = (Lista*) malloc(sizeof(Lista));

        if(!novoNo) {
            printf("Erro ao alocar memoria\n");
            exit(1);
        }

        novoNo->valor = rand() % tamanhoMax;
        novoNo->prox = *inicioLista;
        *inicioLista = novoNo;
    }

    printf("Quantidade de numeros: %d | Tamanho maximo: %d\n\n", quantidade, tamanhoMax);
}

Lista* copiarLista(Lista *inicioLista) {
    if(!inicioLista) return NULL;
    Lista *novaLista = NULL, *fimLista = NULL;

    while(inicioLista) {
        Lista *novoNo = (Lista*) malloc(sizeof(Lista));
        novoNo->valor = inicioLista->valor;
        novoNo->prox = NULL;

        if(!novaLista) {
            novaLista = novoNo;
            fimLista = novoNo;
        } else {
            fimLista->prox = novoNo;
            fimLista = novoNo;
        }

        inicioLista = inicioLista->prox;
    }

    return novaLista;
}

void imprimirLista(Lista *inicioLista) {
    Lista *noAtual = inicioLista;

    while(noAtual != NULL) {
        printf("%d ", noAtual->valor);
        noAtual = noAtual->prox;
    }
    printf("\n");
}

void medirTempo(void (*funcaoOrdenacao)(Lista *), Lista *inicioLista, const char *nomeAlgoritmo) {
    clock_t tempoInicio = clock();
    funcaoOrdenacao(inicioLista);
    clock_t tempoFim = clock();

    double tempoGasto = ((double)(tempoFim - tempoInicio)) / CLOCKS_PER_SEC;

    printf("\n%s - Lista ordenada:\n", nomeAlgoritmo);

    imprimirLista(inicioLista);

    printf("Tempo gasto: %.6f segundos\n", tempoGasto);
}

void bubbleSort(Lista *inicioLista) {
    if(!inicioLista) {
        printf("Lista vazia, nao ordena\n");
        return;
    }

    int houveTroca;
    Lista *noAtual;
    Lista *ultimoNo = NULL;

    do {
        houveTroca = 0;
        noAtual = inicioLista;

        while(noAtual->prox != ultimoNo) {
            if(noAtual->valor > noAtual->prox->valor) {
                int temp = noAtual->valor;
                noAtual->valor = noAtual->prox->valor;
                noAtual->prox->valor = temp;
                houveTroca = 1;
            }

            noAtual = noAtual->prox;
        }

        ultimoNo = noAtual;

    } while(houveTroca);
}

int main() {
    Lista *listaInicial = NULL;
    int opcao, quantidade, tamanhoMax;
    printf("Informe a quantidade de numeros a serem ordenados: ");
    scanf("%d", &quantidade);
    printf("Informe o tamanho maximo dos numeros: ");
    scanf("%d", &tamanhoMax);
    randomizarNumeros(&listaInicial, quantidade, tamanhoMax);
    printf("Numeros gerados:\n");
    imprimirLista(listaInicial);
    do {
        printf("==========================================\n");
        printf("Escolha uma opcao de ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("==========================================\n");
        switch(opcao) {
        case 1: {
            Lista *copia = copiarLista(listaInicial);
            printf("Lista nao ordenada:\n");
            imprimirLista(listaInicial);
            medirTempo(bubbleSort, copia, "Bubble Sort");
            break;
        }
        case 2: {
            //Lista *copia = copiarLista(listaInicial);
            printf("Lista nao ordenada:\n");
            imprimirLista(listaInicial);
            //medirTempo(mergeSort, copia, "Merge Sort");
            break;
        }
        case 3: {
            Lista *copia = copiarLista(listaInicial);
            printf("Lista nao ordenada:\n");
            imprimirLista(listaInicial);
            medirTempo(insertionSort, copia, "Insertion Sort");
            break;
        }
        case 4:
            //Lista *copia = copiarLista(listaInicial);
            printf("Lista nao ordenada:\n");
            imprimirLista(listaInicial);
            //medirTempo(quickSort, copia, "Quick Sort");
            break;
        case 0:
            printf("Saindo do sistema\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    liberarLista(listaInicial);
    return 0;
}
