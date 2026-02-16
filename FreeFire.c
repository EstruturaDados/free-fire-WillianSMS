#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor
Item* mochila[MAX_ITENS];
int totalItens = 0;

// Lista
No* inicioLista = NULL;

// ==========================
// Funções para VETOR (PROTÓTIPOS)
// ========================== 
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void ordenarVetor();
void buscarBinariaVetor();

// ==========================
// Funções para LISTA (PROTÓTIPOS)
// ========================== 
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();

// ==========================
//      Código principal
// ========================== 
int main() {
    int estrutura, opcao;
    
    // Escolha de opções entre Vetor e Lista Encadeada
    printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n");
    scanf("%d", &estrutura);

    // Laço de Repetição do Programa Principal (main)
    do {
        printf("\n==============================\n");
        printf("    MOCHILA DE SOBREVIVENCIA\n");
        printf("==============================\n");

        if (estrutura == 1) {
            // LISTA DE OPÇÕES PARA VETORES
            printf("Itens no Vetor: %d/%d\n", totalItens, MAX_ITENS);
            printf("1. Inserir Item\n");
            printf("2. Remover Item\n");
            printf("3. Listar Itens\n");
            printf("4. Buscar Sequencial\n");
            printf("5. Ordenar Vetor\n");
            printf("6. Buscar Binaria\n");
        } else {
            // LISTA DE OPÇÕES PARA LISTA ENCADEADAS
            printf("Itens na Lista Encadeada\n");
            printf("1. Inserir Item\n");
            printf("2. Remover Item\n");
            printf("3. Listar Itens\n");
            printf("4. Buscar Sequencial\n");
        }
        printf("0. Sair\n");
        scanf("%d", &opcao);

        // CONDICIONAL PARA REALIZAR O SWITCH DE VETOR OU DE LISTA ENCADEADA
        if (estrutura == 1) {
            // Switch para o Vetor
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
                case 5: 
                    ordenarVetor(); 
                    break;
                case 6: 
                    buscarBinariaVetor(); 
                    break;
            }
        } else {
            // Switch para Lista Encadeada
            switch (opcao) {
                case 1: 
                    inserirItemLista(); 
                    break;
                case 2: 
                    removerItemLista(); 
                    break;
                case 3: 
                    listarItensLista(); 
                    break;
                case 4: 
                    buscarSequencialLista(); 
                    break;
            }
        }
    } while (opcao != 0);

    return 0;
}

// ==========================
//    Implementação VETOR
// ========================== 

// Função de inserir item do modo Vetor
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item* novo = (Item*) malloc(sizeof(Item));
    printf("Nome: "); scanf("%s", novo->nome);
    printf("Tipo: "); scanf("%s", novo->tipo);
    printf("Quantidade: "); scanf("%d", &novo->quantidade);
    mochila[totalItens++] = novo;
    printf("Item adicionado!\n");
}

// Função de remover item do modo Vetor
void removerItem() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);
    int i, encontrado = -1;
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i]->nome, nome) == 0) { encontrado = i; break; }
    }
    if (encontrado == -1) { printf("Item não encontrado!\n"); return; }
    free(mochila[encontrado]);
    for (i = encontrado; i < totalItens - 1; i++) mochila[i] = mochila[i+1];
    totalItens--;
    printf("Item removido!\n");
}

// Função de listar os itens do modo Vetor
void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("-----------------------------------------\n");
    printf("NOME         | TIPO       | QUANTIDADE\n");
    printf("-----------------------------------------\n");
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("%-12s | %-10s | %d\n", mochila[i]->nome, mochila[i]->tipo, mochila[i]->quantidade);
        }
    }
    printf("-----------------------------------------\n");
}

// Função de busca de item do modo Vetor
void buscarItem() {
    char nome[30]; int comparacoes = 0;
    printf("Nome do item a buscar: "); scanf("%s", nome);
    for (int i = 0; i < totalItens; i++) {
        comparacoes++;
        if (strcmp(mochila[i]->nome, nome) == 0) {
            printf("Item encontrado: %s | %s | %d\n", mochila[i]->nome, mochila[i]->tipo, mochila[i]->quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
    }
    printf("Item não encontrado! Comparacoes: %d\n", comparacoes);
}

// Função de ordenar (organizar) o vetor, pois busca binária só pode ser realizada com um lista organizada por ordem alfabética
void ordenarVetor() {
    for (int i = 0; i < totalItens; i++) {
        for (int j = i+1; j < totalItens; j++) {
            if (strcmp(mochila[i]->nome, mochila[j]->nome) > 0) {
                Item* temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

// Função que realiza a busca binária
void buscarBinariaVetor() {
    char nome[30]; int inicio = 0, fim = totalItens-1, comparacoes = 0;
    printf("Nome do item a buscar (Binaria): "); scanf("%s", nome);
    while (inicio <= fim) {
        int meio = (inicio+fim)/2;
        comparacoes++;
        int cmp = strcmp(mochila[meio]->nome, nome);
        if (cmp == 0) {
            printf("Item encontrado: %s | %s | %d\n", mochila[meio]->nome, mochila[meio]->tipo, mochila[meio]->quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        } else if (cmp < 0) inicio = meio+1;
        else fim = meio-1;
    }
    printf("Item não encontrado! Comparacoes: %d\n", comparacoes);
}

// ==========================
//   Implementação LISTA
// ========================== 

// Função de inserir item na lista encadeada
void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));
    printf("Nome: "); scanf("%s", novo->dados.nome);
    printf("Tipo: "); scanf("%s", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicioLista;
    inicioLista = novo;
    printf("Item adicionado na lista!\n");
}

// Função de remover item na lista encadeada
void removerItemLista() {
    char nome[30];
    printf("Nome do item a remover (Lista): "); scanf("%s", nome);
    No* atual = inicioLista; No* anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual; atual = atual->proximo;
    }
    if (atual == NULL) { printf("Item não encontrado!\n"); return; }
    if (anterior == NULL) inicioLista = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual);
    printf("Item removido da lista!\n");
}

// Função de listar os itens na lista encadeada
void listarItensLista() {
    No* atual = inicioLista;
    printf("\n--- ITENS NA LISTA ---\n");
    printf("-----------------------------------------\n");
    printf("NOME         | TIPO       | QUANTIDADE\n");
    printf("-----------------------------------------\n");
    if (atual == NULL) {
        printf("Lista vazia!\n");
    } else {
        while (atual != NULL) {
            printf("%-12s | %-10s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            atual = atual->proximo;
        }
    }
    printf("-----------------------------------------\n");
}

// Função para a busca sequêncial na lista encadeada
void buscarSequencialLista() {
    char nome[30]; 
    int comparacoes = 0;
    printf("Nome do item a buscar (Lista): "); 
    scanf("%s", nome);

    No* atual = inicioLista;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado! Comparacoes: %d\n", comparacoes);
}
