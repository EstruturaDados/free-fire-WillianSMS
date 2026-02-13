// Incluindo as Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo vetor
#define MAX_ITENS 10

//Definindo struct
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

//vetor de ponteiro para os itens
Item* mochila[MAX_ITENS];
int totalItens = 0;

// Preparando as funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// Código principal
int main() {
    int opcao;

    do {
        printf("\n==============================\n");
        printf("    MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("==============================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, MAX_ITENS);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                inserirItem(); 
                break;
            case 2: 
                removerItem(); 
                break;
            case 3: 
                listarItens(); 
                break;
            case 4: 
                buscarItem(); 
                break;
            case 0: 
                printf("Saindo...\n"); 
                break;
            default: 
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < totalItens; i++) {
        free(mochila[i]);
    }

    return 0;
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item* novo = (Item*) malloc(sizeof(Item));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf("%s", novo->nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novo->tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nome);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i]->nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    free(mochila[encontrado]);

    for (int i = encontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;

    printf("Item removido com sucesso!\n");
}

void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("-----------------------------------------\n");
    printf("NOME         | TIPO       | QUANTIDADE\n");
    printf("-----------------------------------------\n");

    if (totalItens == 0) {
        printf("Mochila vazia!\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("%-12s | %-10s | %d\n",
                   mochila[i]->nome, mochila[i]->tipo, mochila[i]->quantidade);
        }
    }
    printf("-----------------------------------------\n");
}

void buscarItem() {
    char nome[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nome);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i]->nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i]->nome, mochila[i]->tipo, mochila[i]->quantidade);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}
