#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Lista {
    int valor;
    struct Lista *proximo;
} Lista;

// ===================== FUNÇÕES AUXILIARES =====================

void liberarLista(Lista *inicioLista) {
    Lista *auxiliar = NULL; 

    while (inicioLista != NULL) {
        auxiliar = inicioLista;
        inicioLista = inicioLista->proximo;
        free(auxiliar);
    }
}

void randomizarNumeros(Lista **inicioLista, int quantidade, int tamanhoMaximo) {
    *inicioLista = NULL;

    for (int i = 0; i < quantidade; i++) {
        Lista *novoNo = (Lista*) malloc(sizeof(Lista));
        
        if (!novoNo) {
            printf("Erro ao alocar memoria\n");
            exit(1);
        }
        novoNo->valor = rand() % tamanhoMaximo;
        novoNo->proximo = *inicioLista;
        *inicioLista = novoNo;
    }

    printf("Quantidade de numeros: %d | Tamanho máximo: %d\n\n", quantidade, tamanhoMaximo);
}

Lista* copiarLista(Lista *inicioLista) {
    if(!inicioLista) return NULL;

    Lista *novaLista = NULL;
    Lista *fimLista = NULL;

    while(inicioLista) {
        Lista *novoNo = (Lista*) malloc(sizeof(Lista));
        novoNo->valor = inicioLista->valor;
        novoNo->proximo = NULL;

        if(!novaLista) {
            novaLista = novoNo;
            fimLista = novoNo;
        } else {
            fimLista->proximo = novoNo;
            fimLista = novoNo;
        }

        inicioLista = inicioLista->proximo;
    }

    return novaLista;
}

void imprimirLista(Lista *inicioLista) {
    Lista *noAtual = inicioLista;
    
    while(noAtual) {
        printf("%d ", noAtual->valor);
        noAtual = noAtual->proximo;
    }
    
    printf("\n");
}

void medirTempo(void (*funcaoOrdenacao)(Lista **), Lista *listaCopia, const char *nomeAlgoritmo) {
    clock_t tempoInicio = clock();
    funcaoOrdenacao(&listaCopia);
    clock_t tempoFim = clock();

    double tempoGasto = ((double)(tempoFim - tempoInicio)) / CLOCKS_PER_SEC;

    printf("\n%s - Lista ordenada:\n", nomeAlgoritmo);
    imprimirLista(listaCopia);
    printf("Tempo gasto: %.6f segundos\n", tempoGasto);

    liberarLista(listaCopia);
}

// ===================== SORTS =====================

void bubbleSort(Lista **inicioLista) {
    Lista *inicio = *inicioLista;
    if (!inicio) return;

    int houveTroca;
    Lista *noAtual;
    Lista *ultimoNo = NULL;

    do {
        houveTroca = 0;
        noAtual = inicio;

        while(noAtual->proximo != ultimoNo) {
            if(noAtual->valor > noAtual->proximo->valor) {
                int temp = noAtual->valor;
                noAtual->valor = noAtual->proximo->valor;
                noAtual->proximo->valor = temp;
                houveTroca = 1;
            }
            noAtual = noAtual->proximo;
        }

        ultimoNo = noAtual;
        
    } while(houveTroca);
}

void insertionSort(Lista **inicioLista) {
    Lista *ordenada = NULL;
    Lista *atual = *inicioLista;

    while(atual) {
        Lista *proximo = atual->proximo;
        if(!ordenada || atual->valor < ordenada->valor) {
            atual->proximo = ordenada;
            ordenada = atual;
        } else {
            Lista *temporario = ordenada;
            
            while(temporario->proximo && temporario->proximo->valor < atual->valor) temporario = temporario->proximo;
            atual->proximo = temporario->proximo;
            temporario->proximo = atual;
        }
        atual = proximo;
    }

    *inicioLista = ordenada;
}

Lista* dividir(Lista *inicio) {
    Lista *rapido = inicio->proximo;
    Lista *lento = inicio;
    
    while(rapido && rapido->proximo) {
        rapido = rapido->proximo->proximo;
        lento = lento->proximo;
    }
    
    Lista *metade = lento->proximo;
    lento->proximo = NULL;
    
    return metade;
}

Lista* mesclar(Lista *a, Lista *b) {
    if(!a) return b;
    if(!b) return a;
    
    Lista *resultado = NULL;
    
    if(a->valor < b->valor) {
        resultado = a;
        resultado->proximo = mesclar(a->proximo, b);
    } else {
        resultado = b;
        resultado->proximo = mesclar(a, b->proximo);
    }
    
    return resultado;
}

void mergeSort(Lista **inicioLista) {
    if(!*inicioLista || !(*inicioLista)->proximo) return;

    Lista *metade = dividir(*inicioLista);
    mergeSort(inicioLista);
    mergeSort(&metade);

    *inicioLista = mesclar(*inicioLista, metade);
}

void particao(Lista *inicio, Lista **menores, Lista **pivo, Lista **maiores) {
    *pivo = inicio;
    *menores = NULL;
    *maiores = NULL;

    Lista *atual = inicio->proximo;

    while(atual) {
        Lista *proximo = atual->proximo;
        
        if(atual->valor < (*pivo)->valor) {
            atual->proximo = *menores;
            *menores = atual;
        } else {
            atual->proximo = *maiores;
            *maiores = atual;
        }
        
        atual = proximo;
    }

    (*pivo)->proximo = NULL;
}

Lista* concatenar(Lista *menores, Lista *pivo, Lista *maiores) {
    pivo->proximo = maiores;

    if(!menores) return pivo;

    Lista *temporario = menores;
    while(temporario->proximo) temporario = temporario->proximo;
    temporario->proximo = pivo;

    return menores;
}

void quickSort(Lista **inicioLista) {
    Lista *inicio = *inicioLista;
    
    if(!inicio || !inicio->proximo) return;

    Lista *menores, *pivo, *maiores;
    particao(inicio, &menores, &pivo, &maiores);

    quickSort(&menores);
    quickSort(&maiores);

    *inicioLista = concatenar(menores, pivo, maiores);
}

// ===================== MAIN =====================

int main() {
    srand(time(NULL)); 

    Lista *listaInicial = NULL;
    int opcao, quantidade, tamanhoMaximo;

    printf("Informe a quantidade de numeros a serem ordenados: ");
    scanf("%d", &quantidade);

    printf("Informe o tamanho máximo dos numeros: ");
    scanf("%d", &tamanhoMaximo);

    randomizarNumeros(&listaInicial, quantidade, tamanhoMaximo);

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
                Lista *copia = copiarLista(listaInicial);
                printf("Lista nao ordenada:\n");
                imprimirLista(listaInicial);
                medirTempo(mergeSort, copia, "Merge Sort");
                break;
            }
            case 3: {
                Lista *copia = copiarLista(listaInicial);
                printf("Lista nao ordenada:\n");
                imprimirLista(listaInicial);
                medirTempo(insertionSort, copia, "Insertion Sort");
                break;
            }
            case 4: {
                Lista *copia = copiarLista(listaInicial);
                printf("Lista nao ordenada:\n");
                imprimirLista(listaInicial);
                medirTempo(quickSort, copia, "Quick Sort");
                break;
            }
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    liberarLista(listaInicial);
    return 0;
}
