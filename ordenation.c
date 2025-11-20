#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Lista {
    int valor;
    struct Lista *proximo;
} Lista;

// ===================== FUNÇÕES AUXILIARES =====================

// Função para liberar a memória da lista 
void liberarLista(Lista *inicioLista) {
    Lista *auxiliar = NULL; 

    // Percorre a lista e libera a memória do nó
    while (inicioLista != NULL) {
        auxiliar = inicioLista;
        inicioLista = inicioLista->proximo;
        free(auxiliar);
    }
}

// Função para gerar números aleatórios e armazenar eles na lista
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

// Função para copiar a lista criada
Lista* copiarLista(Lista *inicioLista) {
    if(!inicioLista) {
        printf("Lista vazia, não copia");
        return NULL;
    }

    Lista *novaLista = NULL;
    Lista *fimLista = NULL;

    // Percorre a lista original e cria nós nessa lista nova
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


// Função para imprimir a lista e mostra ao usuario
void imprimirLista(Lista *inicioLista) {
    Lista *noAtual = inicioLista;
    
    // Percorre e imprime os nó da lista
    while(noAtual) {
        printf("%d ", noAtual->valor);
        noAtual = noAtual->proximo;
    }
    
    printf("\n");
}

// Função para medir o tempo de execução dos 4 Sorts
void medirTempo(void (*funcaoOrdenacao)(Lista **), Lista *listaCopia, const char *nomeAlgoritmo) {
    clock_t tempoInicio = clock(); // Marca o início da execução
    funcaoOrdenacao(&listaCopia); // Chama determinada função de ordenação
    clock_t tempoFim = clock(); // Marca o fim da execução da ordenação

    double tempoGasto = ((double)(tempoFim - tempoInicio)) / CLOCKS_PER_SEC;

    // Exibe os resultados da lista ordenada/O tempo de execução da mesma
    printf("\n%s - Lista ordenada:\n", nomeAlgoritmo);
    imprimirLista(listaCopia);
    printf("Tempo gasto: %.6f segundos\n", tempoGasto);

    liberarLista(listaCopia); // Libera memória da lista copia
}

// ===================== SORTS =====================

// Função Bubble Sort
void bubbleSort(Lista **inicioLista) {
    Lista *inicio = *inicioLista;
    if (!inicio) {
        printf("Lista vazia, não ordena");
        return;
    }

    int houveTroca;
    Lista *noAtual;
    Lista *ultimoNo = NULL;

    // Realiza as passagens pela lista até que não há mais trocas
    do {
        houveTroca = 0;
        noAtual = inicio;

        while(noAtual->proximo != ultimoNo) {
            if(noAtual->valor > noAtual->proximo->valor) {
                // Troca os valores
                int temp = noAtual->valor;
                noAtual->valor = noAtual->proximo->valor;
                noAtual->proximo->valor = temp;
                houveTroca = 1;
            }
            noAtual = noAtual->proximo;
        }

        ultimoNo = noAtual;
        
    } while(houveTroca); // Repete o while até não ter mais o que trocar na lista
}

// Função Insertion Sort
void insertionSort(Lista **inicioLista) {
    Lista *ordenada = NULL;
    Lista *atual = *inicioLista;

    // Insere o nó da lista original na lista ordenada
    while(atual) {
        Lista *proximo = atual->proximo;
        
        if(!ordenada || atual->valor < ordenada->valor) {
            atual->proximo = ordenada;
            ordenada = atual;
        } else {
            Lista *temporario = ordenada;
            
            // Encontra a posição correta na lista ordenada
            while(temporario->proximo && temporario->proximo->valor < atual->valor) temporario = temporario->proximo;
            
            atual->proximo = temporario->proximo;
            temporario->proximo = atual;
        }
        atual = proximo;
    }

    *inicioLista = ordenada; // Atualiza a lista original
}

// Funções auxiliares Merge Sort (Dividir e Mesclar)
Lista* dividir(Lista *inicio) {
    Lista *rapido = inicio->proximo;
    Lista *lento = inicio;
    
    // Usa 2 ponteiros para achar o meio da lista
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
    
    // Mescla as 2 listas já ordenadas
    if(a->valor < b->valor) {
        resultado = a;
        resultado->proximo = mesclar(a->proximo, b);
    } else {
        resultado = b;
        resultado->proximo = mesclar(a, b->proximo);
    }
    
    return resultado;
}


// Função Merge Sort
void mergeSort(Lista **inicioLista) {
    if(!*inicioLista || !(*inicioLista)->proximo) return;

    Lista *metade = dividir(*inicioLista);
    mergeSort(inicioLista); // Ordena primeira metade
    mergeSort(&metade); // Ordena segunda metade

    *inicioLista = mesclar(*inicioLista, metade); // Junta ambas metades ordenadas
}

// Funções auxiliares Quick Sort (Partição, Concatenar e Ordenação)
void particao(Lista *inicio, Lista **menores, Lista **pivo, Lista **maiores) {
    *pivo = inicio;
    *menores = NULL;
    *maiores = NULL;

    Lista *atual = inicio->proximo;

    // Divide os elementos em 3 listas: menores, pivo, maiores
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

    (*pivo)->proximo = NULL; // O pivo fica isolado
}

Lista* concatenar(Lista *menores, Lista *pivo, Lista *maiores) {
    if (!menores) {
        pivo->proximo = maiores;
        return pivo;
    }

    Lista *temp = menores;
    
    // Encontra o final da lista de menores e concatena com o pivo e a de maiores
    while(temp->proximo != NULL) {
        temp = temp->proximo;
    }

    temp->proximo = pivo;
    pivo->proximo = maiores;
    
    return menores;
}

// Função Quick Sort
void quickSort(Lista **inicioLista) {
    Lista *inicio = *inicioLista;
    
    if (!inicio || !inicio->proximo) {
        printf("Lista vazia, não ordena");
        return;
    }

    Lista *menores, *pivo, *maiores;
    particao(inicio, &menores, &pivo, &maiores);

    quickSort(&menores); // Ordena menores
    quickSort(&maiores); // Ordena menores

    *inicioLista = concatenar(menores, pivo, maiores); // Junta ambas listas ordenadas
}

// ===================== MAIN =====================

int main() {
    srand(time(NULL)); // Inicializa a geração de números aleatórios

    Lista *listaInicial = NULL;
    int opcao, quantidade, tamanhoMaximo;

    printf("Informe a quantidade de numeros a serem ordenados: ");
    scanf("%d", &quantidade);

    printf("Informe o tamanho máximo dos numeros: ");
    scanf("%d", &tamanhoMaximo);

    // Chama função para gerar a lista de números aleatórios 
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
                // Cria uma cópia da lista para não alterar a original
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
                printf("Saindo do sistema\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
    
    // Libera a memória da lista original
    liberarLista(listaInicial);
    return 0;
}
