#include <stdio.h>

#define MAX_REG 10

typedef struct {
    float altura;
    float profundidade;
    float largura;
} REGISTRO;
    
void createRegister(REGISTRO reg[], int *n) {
   if(*n < MAX_REG) {
        printf("Informe a altura: ");
        scanf("%f", &reg[*n].altura);
        printf("Informe a profundidade: ");
        scanf("%f", &reg[*n].profundidade);
        printf("Informe a largura: ");
        scanf("%f", &reg[*n].largura);
        (*n)++;

        printf("Registro criado com sucesso!\n");   
    } else {
       printf("Limite de registros atingido.\n");
    }
}

void editRegister(REGISTRO reg[], int *n) {
    if(*n > 0) {
        int index;
        printf("Informe o indice do registro a ser editado (0 a %d): ", *n - 1);
        scanf("%d", &index);

        if(index >= 0 && index < *n) {
            printf("Informe a nova altura: ");
            scanf("%f", &reg[index].altura);
            printf("Informe a nova profundidade: ");
            scanf("%f", &reg[index].profundidade);
            printf("Informe a nova largura: ");
            scanf("%f", &reg[index].largura);
            printf("Registro editado com sucesso!\n");
        } else {
            printf("Indice invalido\n");
        }
    } else {
        printf("Nenhum registro disponivel para edicao\n");
    }
}

void deleteRegister(REGISTRO reg[], int *n) {
    if(*n > 0) {
        int index;
        printf("Informe o indice do registro a ser excluido (0 a %d): ", *n - 1);
        scanf("%d", &index);

       if(index >= 0 && index < *n) {
            for(int i = index; i < *n - 1; i++) {
                reg[i] = reg[i + 1];
            } (*n)--;
            
            printf("Registro excluido com sucesso!\n");
        } else {
            printf("Indice invalido\n");
        }
    } else {
        printf("Nenhum registro disponivel para exclusao\n");
    }
}

void listRegisters(REGISTRO reg[], int *n) {
    for(int i = 0; i < *n; i++) {
        printf("Registro %d: Altura = %.2f, Profundidade = %.2f, Largura = %.2f\n", i+1, reg[i].altura, reg[i].profundidade, reg[i].largura);
    }

}

int main() {
    REGISTRO reg[MAX_REG];
    int n = 0;
    int opt;

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
                createRegister(reg, &n);
                break;
            case 2:
                editRegister(reg, &n);
                break;
            case 3:
                deleteRegister(reg, &n);
                break;
            case 4:
                listRegisters(reg, &n);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    };

    return 0;
}
