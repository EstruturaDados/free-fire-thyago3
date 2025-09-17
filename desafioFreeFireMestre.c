#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

Item mochila[MAX_ITENS];
int numItens = 0;
int ordenadaPorNome = 0; // 1 se estiver ordenada por nome

void limparTela() {
    for(int i=0;i<30;i++) printf("\n");
}

void listarItens() {
    printf("\n%-30s %-20s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("--------------------------------------------------------------------\n");
    for(int i=0;i<numItens;i++) {
        printf("%-30s %-20s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

void inserirItem() {
    if(numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    getchar();
    printf("Nome: ");
    fgets(mochila[numItens].nome, TAM_NOME, stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome,"\n")]=0;
    printf("Tipo: ");
    fgets(mochila[numItens].tipo, TAM_TIPO, stdin);
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo,"\n")]=0;
    printf("Quantidade: ");
    scanf("%d",&mochila[numItens].quantidade);
    printf("Prioridade (1-5): ");
    scanf("%d",&mochila[numItens].prioridade);
    numItens++;
    ordenadaPorNome = 0;
}

void removerItem() {
    if(numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    getchar();
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca,TAM_NOME,stdin);
    nomeBusca[strcspn(nomeBusca,"\n")]=0;
    int encontrado = 0;
    for(int i=0;i<numItens;i++) {
        if(strcmp(mochila[i].nome,nomeBusca)==0) {
            for(int j=i;j<numItens-1;j++) mochila[j]=mochila[j+1];
            numItens--;
            encontrado = 1;
            printf("Item removido.\n");
            break;
        }
    }
    if(!encontrado) printf("Item nao encontrado.\n");
}

int insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;
    for(int i=1;i<numItens;i++) {
        Item chave = mochila[i];
        int j = i-1;
        while(j>=0) {
            comparacoes++;
            int cmp = 0;
            if(criterio == NOME) cmp = strcmp(mochila[j].nome,chave.nome);
            else if(criterio == TIPO) cmp = strcmp(mochila[j].tipo,chave.tipo);
            else if(criterio == PRIORIDADE) cmp = (mochila[j].prioridade < chave.prioridade) ? 1 : 0;
            if(cmp>0) {
                mochila[j+1]=mochila[j];
                j--;
            } else break;
        }
        mochila[j+1]=chave;
    }
    if(criterio==NOME) ordenadaPorNome=1;
    else ordenadaPorNome=0;
    return comparacoes;
}

void menuDeOrdenacao() {
    printf("\nEscolha o criterio de ordenacao:\n");
    printf("1 - Nome\n2 - Tipo\n3 - Prioridade\n");
    int op;
    scanf("%d",&op);
    CriterioOrdenacao crit;
    if(op==1) crit=NOME;
    else if(op==2) crit=TIPO;
    else crit=PRIORIDADE;
    int comps = insertionSort(crit);
    printf("Itens ordenados.\nComparacoes realizadas: %d\n",comps);
}

void buscaBinariaPorNome() {
    if(!ordenadaPorNome) {
        printf("A mochila precisa estar ordenada por nome!\n");
        return;
    }
    getchar();
    char chave[TAM_NOME];
    printf("Digite o nome do item a buscar: ");
    fgets(chave,TAM_NOME,stdin);
    chave[strcspn(chave,"\n")]=0;
    int inicio=0, fim=numItens-1, comparacoes=0, encontrado=-1;
    while(inicio<=fim) {
        int meio=(inicio+fim)/2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome,chave);
        if(cmp==0) {encontrado=meio; break;}
        else if(cmp<0) inicio=meio+1;
        else fim=meio-1;
    }
    if(encontrado!=-1) {
        printf("Item encontrado:\n");
        printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n", mochila[encontrado].nome,mochila[encontrado].tipo,mochila[encontrado].quantidade,mochila[encontrado].prioridade);
        printf("Comparacoes: %d\n",comparacoes);
    } else {
        printf("Item nao encontrado. Comparacoes: %d\n",comparacoes);
    }
}

void exibirMenu() {
    printf("\n=== Menu Mochila ===\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Busca binaria por nome\n");
    printf("0 - Sair\n");
    if(ordenadaPorNome) printf("(Lista atualmente ordenada por nome)\n");
}

int main() {
    int opcao;
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);
        switch(opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao!=0);
    return 0;
}
