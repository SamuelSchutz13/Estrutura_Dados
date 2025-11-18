#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float altura;
    float profundidade;
    float largura;
} REGISTRO;

void createRegister(REGISTRO **reg, int *length) {
    printf("Altura: ");
    scanf("%f", &(*reg)[*length].altura);
    printf("Profundidade: ");
    scanf("%f", &(*reg)[*length].profundidade);
    printf("Largura: ");
    scanf("%f", &(*reg)[*length].largura);

    if(!*reg) {
        printf("Erro ao alocar memoria\n");
        return;
    }

    *reg = realloc(*reg, (*length + 1) * sizeof(REGISTRO));
    (*length)++;
}

void editRegister(REGISTRO **reg, int *length) {
    int i;
    printf("Indice do registro a ser editado: ");
    scanf("%d", &i);

    if(i < 1 || i > *length) {
        printf("Indice invalido\n");
        return;
    }

    printf("Entre com os novos valores para o registro %d\n", i);
    printf("Altura: ");
    scanf("%f", &(*reg)[i-1].altura);
    printf("Profundidade: ");
    scanf("%f", &(*reg)[i-1].profundidade);
    printf("Largura: ");
    scanf("%f", &(*reg)[i-1].largura);
}

void deleteRegister(REGISTRO **reg, int *length) {
    int i;
    printf("Indice do registro a ser excluido: ");
    scanf("%d", &i);

    if(i < 1 || i > *length) {
        printf("Indice invalido\n");
        return;
    }

    for(int j = i-1; j < *length-1; j++) {
        (*reg)[j] = (*reg)[j+1];
    }

    (*length)--;
}

void listRegisters(REGISTRO **reg, int *length) {
    for(int i = 0; i < *length; i++) {
        printf("Registro %d: Altura = %.2f, Profundidade = %.2f, Largura = %.2f\n", i+1, (*reg)[i].altura, (*reg)[i].profundidade, (*reg)[i].largura);
    }

}

int main() {
    REGISTRO *reg = NULL;
    int length = 0, opt = 0;

    while(opt != 5) {
        printf("-------------------------------------------\n");
        printf("1 - Inserir registro\n");
        printf("2 - Editar registro\n");
        printf("3 - Excluir registro\n");
        printf("4 - Listar registros\n");
        printf("5 - Sair\n");
        printf("-------------------------------------------\n");
        printf("Informe um numero para a opcao: ");
        scanf("%d", &opt);
        printf("-------------------------------------------\n");

        switch(opt) {
            case 1:
                createRegister(reg, &length);
                break;
            case 2:
                editRegister(reg, &length);
                break;
            case 3:
                deleteRegister(reg, &length);
                break;
            case 4:
                listRegisters(reg, &length);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    };

    free(reg);
    return 0;
}
