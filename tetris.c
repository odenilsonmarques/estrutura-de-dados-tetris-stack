#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

// definição da estrutura para representar uma peça do Tetris
typedef struct {
    char nome; // tipo da peça
    int id;    // identificador único
} Peca;

// definição da fila para armazenar as peças
Peca fila[MAX];
int inicio = 0, fim = -1;
int contadorID = 0;

// função para gerar uma nova peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;

    return nova;
}

// função para adicionar uma nova peça à fila
void enqueue() {
    if (fim == MAX - 1) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }

    fila[++fim] = gerarPeca();
    printf("Nova peça adicionada!\n");
}

// funcão para remover a peça da frente da fila (jogar a peça)
void dequeue() {
    if (inicio > fim) {
        printf("Fila vazia!\n");
        return;
    }

    Peca removida = fila[inicio++];
    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// função para exibir as peças na fila
void mostrarFila() {
    printf("\nFila de peças:\n");

    if (inicio > fim) {
        printf("Fila vazia!\n");
        return;
    }

    for (int i = inicio; i <= fim; i++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
    }
    printf("\n");
}

// função para inicializar a fila com peças aleatórias
void inicializarFila() {
    for (int i = 0; i < MAX; i++) {
        enqueue();
    }
}

int main() {
    int op;

    srand(time(NULL)); // inicializa random

    inicializarFila();

    do {
        mostrarFila();

        printf("\n1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("Encerrando jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}