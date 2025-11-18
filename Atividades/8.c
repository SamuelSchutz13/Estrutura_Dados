#include <stdio.h>
#include <stdlib.h>

typedef struct sRegistro{
    int valor;
    struct sRegistro *prox;
} REGISTRO;

void inserir(REGISTRO **topo, int valor){
    REGISTRO *p = (REGISTRO *) malloc(sizeof(REGISTRO));
    p->valor = valor;
    p->prox  = *topo;
    *topo    = p;
}

void imprimir(REGISTRO *p){
    printf("\nPilha atual: \n\n");
    while (p != NULL){
        printf("| %d |\n", p->valor);
        printf("------\n");
        p = p->prox;
    }
}

void excluir(REGISTRO **topo){
    if (*topo == NULL)
        return;
    REGISTRO *p = *topo;
    *topo = p->prox;
    free(p);
}

int main () {

    REGISTRO *topo = NULL;

    inserir(&topo, 10);
    inserir(&topo, 20);
    inserir(&topo, 30);
    imprimir(topo);
    excluir(&topo);
    imprimir(topo);

    return 0;
}