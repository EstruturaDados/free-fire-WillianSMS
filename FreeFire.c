#include <stdio.h>   // Entrada e saída padrão (printf, scanf, fgets)
#include <stdlib.h>  // Funções de alocação de memória e utilidades (malloc, free)
#include <string.h>  // Manipulação de strings (strcmp, strcspn)
#include <time.h>    // Medição de tempo de execução (clock, CLOCKS_PER_SEC)

#define MAX_ITENS 10   // limite da mochila
#define MAX_COMP 20    // limite da torre de fuga

// Struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct que representa cada componente da torre de fuga
// Contém nome, tipo e prioridade (1 a 10)
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

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

// ====== Protótipos da Torre de Fuga ======

// Cadastro e exibição
void inserirComponente(Componente torre[], int *totalComp);
void mostrarComponentesTorre(Componente torre[], int totalComp);

// Algoritmos de ordenação
void bubbleSortNome(Componente v[], int n);
void insertionSortTipo(Componente v[], int n);
void selectionSortPrioridade(Componente v[], int n);

// Busca binária
int buscaBinariaPorNome(Componente v[], int n, char chave[]);

// Medição de tempo (função genérica)
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n);

// ==========================
//      Código principal
// ========================== 
int main() {
    int sistema, opcao;

    // Menu inicial para escolher qual módulo usar
    printf("=====================================\n");
    printf("   ESCOLHA O SISTEMA DE SOBREVIVENCIA\n");
    printf("=====================================\n");
    printf("1 - Mochila de Sobrevivencia\n");
    printf("2 - Torre de Fuga\n");
    printf("0 - Sair\n");
    scanf("%d", &sistema);
    getchar(); // limpar buffer

    if (sistema == 1) {
        // ==========================
        // MÓDULO MOCHILA DE SOBREVIVÊNCIA
        // ==========================
        do {
            printf("\n==============================\n");
            printf("    MOCHILA DE SOBREVIVENCIA\n");
            printf("==============================\n");

            printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n0 - Sair\n");
            scanf("%d", &opcao);

            if (opcao == 1) {
                int escolha;
                do {
                    printf("\nItens no Vetor: %d/%d\n", totalItens, MAX_ITENS);
                    printf("1. Inserir Item\n");
                    printf("2. Remover Item\n");
                    printf("3. Listar Itens\n");
                    printf("4. Buscar Sequencial\n");
                    printf("5. Ordenar Vetor\n");
                    printf("6. Buscar Binaria\n");
                    printf("0. Voltar\n");
                    scanf("%d", &escolha);

                    switch (escolha) {
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
                } while (escolha != 0);
            } else if (opcao == 2) {
                int escolha;
                do {
                    printf("\nItens na Lista Encadeada\n");
                    printf("1. Inserir Item\n");
                    printf("2. Remover Item\n");
                    printf("3. Listar Itens\n");
                    printf("4. Buscar Sequencial\n");
                    printf("0. Voltar\n");
                    scanf("%d", &escolha);

                    switch (escolha) {
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
                } while (escolha != 0);
            }
        } while (opcao != 0);

    } else if (sistema == 2) {
        // ==========================
        // MÓDULO TORRE DE FUGA
        // ==========================
        Componente torre[MAX_COMP];
        int totalComp = 0;

        do {
            printf("\n==============================\n");
            printf("        TORRE DE FUGA\n");
            printf("==============================\n");
            printf("1. Inserir Componente\n");
            printf("2. Mostrar Componentes\n");
            printf("3. Ordenar por Nome (Bubble Sort)\n");
            printf("4. Ordenar por Tipo (Insertion Sort)\n");
            printf("5. Ordenar por Prioridade (Selection Sort)\n");
            printf("6. Busca Binária por Nome\n");
            printf("0. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            getchar(); // limpar buffer

            switch (opcao) {
                case 1:
                    inserirComponente(torre, &totalComp);
                    break;
                case 2:
                    mostrarComponentesTorre(torre, totalComp);
                    break;
                case 3:
                    medirTempo(bubbleSortNome, torre, totalComp);
                    mostrarComponentesTorre(torre, totalComp);
                    break;
                case 4:
                    medirTempo(insertionSortTipo, torre, totalComp);
                    mostrarComponentesTorre(torre, totalComp);
                    break;
                case 5:
                    medirTempo(selectionSortPrioridade, torre, totalComp);
                    mostrarComponentesTorre(torre, totalComp);
                    break;
                case 6: {
                    char chave[30];
                    printf("Digite o nome do componente a buscar: ");
                    fgets(chave, sizeof(chave), stdin);
                    chave[strcspn(chave, "\n")] = '\0';
                    buscaBinariaPorNome(torre, totalComp, chave);
                    break;
                }
                case 0:
                    printf("Encerrando o sistema da Torre de Fuga...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
            }
        } while (opcao != 0);
    }

    printf("Programa finalizado.\n");
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

// Função para inserir um novo componente no vetor da torre
// Usa fgets para permitir nomes e tipos com espaços
void inserirComponente(Componente torre[], int *totalComp) {
    if (*totalComp >= MAX_COMP) {
        printf("Limite de componentes atingido!\n");
        return;
    }

    printf("Nome: ");
    fgets(torre[*totalComp].nome, sizeof(torre[*totalComp].nome), stdin);
    torre[*totalComp].nome[strcspn(torre[*totalComp].nome, "\n")] = '\0'; // remove \n

    printf("Tipo: ");
    fgets(torre[*totalComp].tipo, sizeof(torre[*totalComp].tipo), stdin);
    torre[*totalComp].tipo[strcspn(torre[*totalComp].tipo, "\n")] = '\0'; // remove \n

    printf("Prioridade (1-10): ");
    scanf("%d", &torre[*totalComp].prioridade);
    getchar(); // limpa buffer do teclado

    (*totalComp)++;
    printf("Componente cadastrado!\n");
}

// Exibe todos os componentes cadastrados de forma formatada
void mostrarComponentes(Componente torre[], int totalComp) {
    printf("\n--- COMPONENTES DA TORRE (%d/%d) ---\n", totalComp, MAX_COMP);
    printf("-------------------------------------------------\n");
    printf("NOME                | TIPO           | PRIORIDADE\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < totalComp; i++) {
        printf("%-20s | %-13s | %d\n",
               torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
    printf("-------------------------------------------------\n");
}

// Ordena os componentes por nome usando Bubble Sort
// Conta comparações e mede tempo de execução
void bubbleSortNome(Componente v[], int n) {
    int comp = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            comp++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }

    clock_t fim = clock();
    printf("Bubble Sort concluído! Comparações: %d | Tempo: %.5f s\n",
           comp, (double)(fim-inicio)/CLOCKS_PER_SEC);
}

// Ordena os componentes por tipo usando Insertion Sort
// Conta comparações e mede tempo de execução
void insertionSortTipo(Componente v[], int n) {
    int comp = 0;
    clock_t inicio = clock();

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comp++;
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }

    clock_t fim = clock();
    printf("Insertion Sort concluído! Comparações: %d | Tempo: %.5f s\n",
           comp, (double)(fim-inicio)/CLOCKS_PER_SEC);
}

// Ordena os componentes por prioridade usando Selection Sort
// Conta comparações e mede tempo de execução
void selectionSortPrioridade(Componente v[], int n) {
    int comp = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comp++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }

    clock_t fim = clock();
    printf("Selection Sort concluído! Comparações: %d | Tempo: %.5f s\n",
           comp, (double)(fim-inicio)/CLOCKS_PER_SEC);
}

// Busca binária por nome (só funciona após ordenação por nome)
// Retorna índice do componente ou -1 se não encontrado
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n-1, comp = 0;

    while (inicio <= fim) {
        int meio = (inicio+fim)/2;
        comp++;
        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) {
            printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                   v[meio].nome, v[meio].tipo, v[meio].prioridade);
            printf("Comparações: %d\n", comp);
            return meio;
        } else if (cmp < 0) {
            inicio = meio+1;
        } else {
            fim = meio-1;
        }
    }

    printf("Componente não encontrado! Comparações: %d\n", comp);
    return -1;
}

// Exibe todos os componentes cadastrados da torre de fuga
void mostrarComponentesTorre(Componente torre[], int totalComp) {
    printf("\n--- COMPONENTES DA TORRE (%d/%d) ---\n", totalComp, MAX_COMP);
    printf("-------------------------------------------------\n");
    printf("NOME                | TIPO           | PRIORIDADE\n");
    printf("-------------------------------------------------\n");

    if (totalComp == 0) {
        printf("Nenhum componente cadastrado!\n");
    } else {
        for (int i = 0; i < totalComp; i++) {
            printf("%-20s | %-13s | %d\n",
                   torre[i].nome, torre[i].tipo, torre[i].prioridade);
        }
    }

    printf("-------------------------------------------------\n");
}

// Função genérica para medir tempo de execução de um algoritmo de ordenação
// Recebe um ponteiro para função (algoritmo) e os parâmetros necessários
// Mostra o tempo gasto em segundos
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();   // marca o início
    algoritmo(v, n);            // executa o algoritmo passado como parâmetro
    clock_t fim = clock();      // marca o fim

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.5f segundos\n", tempo);
}
