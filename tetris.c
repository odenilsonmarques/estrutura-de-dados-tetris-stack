#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

// variáveis para fila e pilha
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, tamanho = 0;

// Pilha
Peca pilha[TAM_PILHA];
int topo = -1;

// Controle de ID
int contadorID = 0;

// função para gerar uma peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I','O','T','L'};
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
        inicio = (inicio + 1) % TAM_FILA;
}

Peca dequeue() {
    Peca p = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    tamanho--;
    return p;
}

// funções para pilha
int push(Peca p) {
    if (topo == TAM_PILHA - 1) return 0;
    pilha[++topo] = p;
    return 1;
}

int pop(Peca* p) {
    if (topo == -1) return 0;
    *p = pilha[topo--];
    return 1;
}

// função para mostrar o estado atual da fila e pilha
void mostrar() {
    printf("\nFila: ");
    for (int i = 0; i < tamanho; i++) {
        int idx = (inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }

    printf("\nPilha (Topo->Base): ");
    if (topo == -1) printf("vazia");
    else {
        for (int i = topo; i >= 0; i--)
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// função para inicializar a fila com peças aleatórias
void inicializar() {
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(gerarPeca());
}

// funções para as operações do jogo
void jogar() {
    Peca p = dequeue();
    printf("Jogou: [%c %d]\n", p.nome, p.id);
    enqueue(gerarPeca());
}

// função para reservar a peça da frente da fila
void reservar() {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia!\n");
        return;
    }

    Peca p = dequeue();
    push(p);
    printf("Reservou: [%c %d]\n", p.nome, p.id);

    enqueue(gerarPeca());
}

// função para usar a peça da reserva
void usarReserva() {
    Peca p;
    if (!pop(&p)) {
        printf("Pilha vazia!\n");
        return;
    }

    printf("Usou: [%c %d]\n", p.nome, p.id);
    enqueue(gerarPeca());
}

// função para trocar o topo da pilha com a frente da fila
void trocarTopo() {
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return;
    }

    int idx = inicio;

    Peca temp = fila[idx];
    fila[idx] = pilha[topo];
    pilha[topo] = temp;

    printf("Troca realizada!\n");
}

// função para trocar os 3 elementos do topo da pilha com os 3 da frente da fila
void trocaMultipla() {
    if (tamanho < 3 || topo < 2) {
        printf("Nao ha elementos suficientes!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idx = (inicio + i) % TAM_FILA;

        Peca temp = fila[idx];
        fila[idx] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("Troca multipla realizada!\n");
}


int main() {
    int op;
    srand(time(NULL));

    inicializar();

    do {
        mostrar();

        printf("\n1 Jogar\n");
        printf("2 Reservar\n");
        printf("3 Usar reserva\n");
        printf("4 Trocar topo com frente\n");
        printf("5 Troca multipla (3x3)\n");
        printf("0 Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch(op) {
            case 1: jogar(); break;
            case 2: reservar(); break;
            case 3: usarReserva(); break;
            case 4: trocarTopo(); break;
            case 5: trocaMultipla(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while(op != 0);

    return 0;
}