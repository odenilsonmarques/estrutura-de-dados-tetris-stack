#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// estrutura para representar uma peça

typedef struct {
    char nome;
    int id;
} Peca;

// variáveis

// Fila circular
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, tamanho = 0;

// Pilha
Peca pilha[TAM_PILHA];
int topo = -1;

// Controle de ID
int contadorID = 0;

// função para gerar uma peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;

    return p;
}

// funções para fila
void enqueue(Peca p) {
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;

    if (tamanho < TAM_FILA)
        tamanho++;
    else
        inicio = (inicio + 1) % TAM_FILA; // sobrescreve (não deve ocorrer aqui)
}

Peca dequeue() {
    Peca p = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    tamanho--;
    return p;
}

// funções para pilha
int push(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia!\n");
        return 0;
    }
    pilha[++topo] = p;
    return 1;
}

int pop(Peca* p) {
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return 0;
    }
    *p = pilha[topo--];
    return 1;
}

// função para mostrar o estado atual da fila e pilha
void mostrarEstado() {
    printf("\nFila: ");
    for (int i = 0; i < tamanho; i++) {
        int idx = (inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }

    printf("\nPilha (Topo -> Base): ");
    if (topo == -1) {
        printf("vazia");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }
    printf("\n");
}

// função para inicializar a fila com peças aleatórias
void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }
}

// funções para as operações do jogo
void jogarPeca() {
    Peca p = dequeue();
    printf("Jogou: [%c %d]\n", p.nome, p.id);

    enqueue(gerarPeca());
}

void reservarPeca() {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Não pode reservar.\n");
        return;
    }

    Peca p = dequeue();

    if (push(p)) {
        printf("Reservou: [%c %d]\n", p.nome, p.id);
        enqueue(gerarPeca());
    }
}

void usarReserva() {
    Peca p;

    if (pop(&p)) {
        printf("Usou reserva: [%c %d]\n", p.nome, p.id);
        enqueue(gerarPeca());
    }
}


int main() {
    int op;

    srand(time(NULL));

    inicializarFila();

    do {
        mostrarEstado();

        printf("\n1 Jogar peça\n");
        printf("2 Reservar peça\n");
        printf("3 Usar peça reservada\n");
        printf("0 Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarReserva(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}