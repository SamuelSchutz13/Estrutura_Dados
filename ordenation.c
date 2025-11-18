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
            printf("Erro ao alocar memória\n");
            exit(1);
        }

        novoNo->valor = rand() % tamanhoMax;
        novoNo->prox = *inicioLista;
        *inicioLista = novoNo;
    }

    printf("Quantidade de números: %d | Tamanho máximo: %d\n\n", 
           quantidade, tamanhoMax);
}

Lista* copiarLista(Lista *inicioLista) {
    if(!inicioLista) {
        return NULL;
    }

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

void medirTempo(void (*funcaoOrdenacao)(Lista *),
    Lista *inicioLista,
    const char *nomeAlgoritmo) {

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
        printf("Lista vazia, não ordena\n");
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

void selectionSort(Lista *inicioLista) {
    if(!inicioLista) {
        printf("Lista vazia, não ordena\n");
        return;
    }

    Lista *i, *j, *minimo;

    for(i = inicioLista; i != NULL; i = i->prox) {
        minimo = i;

        for(j = i->prox; j != NULL; j = j->prox) {
            if(j->valor < minimo->valor) {
                minimo = j;
            }
        }

        if(minimo != i) {
            int temp = i->valor;
            i->valor = minimo->valor;
            minimo->valor = temp;
        }
    }
}

void insertionSort(Lista *inicioLista) {
    
}

void quickSort(Lista *inicioLista) {
 
}

int main() {
    Lista *listaInicial = NULL;
    int opcao, quantidade, tamanhoMax;

    printf("Informe a quantidade de números a serem ordenados: ");
    scanf("%d", &quantidade);

    printf("Informe o tamanho máximo dos números: ");
    scanf("%d", &tamanhoMax);

    randomizarNumeros(&listaInicial, quantidade, tamanhoMax);

    printf("Números gerados:\n");
    imprimirLista(listaInicial);

    do {
        printf("==========================================\n");
        printf("Escolha uma opção de ordenação:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        printf("==========================================\n");

        switch(opcao) {
        case 1: {
            Lista *copia = copiarLista(listaInicial);
            printf("\nLista não ordenada:\n");
            imprimirLista(listaInicial);
            medirTempo(bubbleSort, copia, "Bubble Sort");
            break;
        }
        case 2: {
            Lista *copia = copiarLista(listaInicial);
            printf("\nLista não ordenada:\n");
            imprimirLista(listaInicial);
            medirTempo(selectionSort, copia, "Selection Sort");
            break;
        }
        case 3:
            printf("Lista não ordenada:\n");
            imprimirLista(listaInicial);
            break;

        case 4:
            printf("Lista não ordenada:\n");
            imprimirLista(listaInicial);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    liberarLista(listaInicial);
    return 0;
}
