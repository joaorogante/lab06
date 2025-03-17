#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int valor;
    struct Celula *proximo;
    struct Celula *anterior;
} Celula;

typedef struct {
    Celula *head;
    Celula *tail;
    int qtde;
} Queue;

//Criação de células e filas 

Celula *cria_celula(int valor) {
    Celula *celula = (Celula*)malloc(sizeof(Celula));
    celula->valor = valor;
    celula->proximo = NULL;
    celula->anterior = NULL;
    return celula;
}

Queue *cria_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->qtde = 0;
    return queue;
}

// Funções de enfileirar e desenfileirar  

// Insere no final da fila (tail)
void enqueue(Queue *queue, int valor) {
    Celula *nova = cria_celula(valor);

    if (queue->head == NULL) {
        // Se fila vazia, head e tail passam a ser 'nova'
        queue->head = nova;
        queue->tail = nova;
    } else {
        // Insere após o tail atual
        queue->tail->proximo = nova;
        nova->anterior = queue->tail;
        queue->tail = nova;
    }

    queue->qtde++;
}

// Remove do início da fila (head)
int dequeue(Queue *queue) {
    if (queue->head == NULL) {
        // Fila vazia, pode retornar algo para indicar falha
        return -1; 
    }

    Celula *removida = queue->head;
    int valor = removida->valor;

    // Ajusta ponteiros
    queue->head = removida->proximo;
    if (queue->head) {
        queue->head->anterior = NULL;
    } else {
        // Se ficou vazio, tail vira NULL também
        queue->tail = NULL;
    }

    free(removida);
    queue->qtde--;
    return valor;
}
//Exibição normal (head->tail) e invertida (tail->head) 
void show(Queue *queue) {
    Celula *atual = queue->head;
    while (atual != NULL) {
        printf("%d", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void show_invertido(Queue *queue) {
    Celula *atual = queue->tail;
    while (atual != NULL) {
        printf("%d", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

//Soma “grande” usando as filas 

int main(void) {
    Queue *qnum1 = cria_queue();
    Queue *qnum2 = cria_queue();
    Queue *res = cria_queue();

    char num1[100];
    char num2[100];

    // Lê cada número como string
    fgets(num1, sizeof(num1), stdin);
    fgets(num2, sizeof(num2), stdin);

    // Preenche as filas com os dígitos
    // assumindo que ambas as linhas têm o mesmo tamanho ou até encontrar '\n'
    int i = 0;
    while (num1[i] != '\n' && num1[i] != '\0') {
        enqueue(qnum1, (int)(num1[i]) - 48); // char -> int
        enqueue(qnum2, (int)(num2[i]) - 48);
        i++;
    }

    // Agora, somamos de trás para frente (tail), pois é ali que estão os dígitos menos significativos
    Celula *p1 = qnum1->tail;
    Celula *p2 = qnum2->tail;

    int carry = 0;  // vai-um
    while (p1 != NULL || p2 != NULL || carry > 0) {
        int d1 = 0, d2 = 0;

        if (p1 != NULL) {
            d1 = p1->valor;
            p1 = p1->anterior;
        }
        if (p2 != NULL) {
            d2 = p2->valor;
            p2 = p2->anterior;
        }

        int soma = d1 + d2 + carry;
        carry = soma / 10;
        soma = soma % 10;

        // Armazenamos o dígito somado em 'res'
        
        enqueue(res, soma);
    }

    // pois a soma gerou a fila "de trás pra frente"
    show_invertido(res);

    return 0;
}

