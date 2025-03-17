#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

//3.1
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int value) {
    if (!isFull(s)) {
        s->data[++s->top] = value;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    }
    return -1;
}

//3.2
typedef struct {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}

int isQueueFull(Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(Queue *q, int value) {
    if (!isQueueFull(q)) {
        q->data[q->rear] = value;
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
}

int dequeue(Queue *q) {
    if (!isQueueEmpty(q)) {
        int value = q->data[q->front];
        q->front = (q->front + 1) % MAX_SIZE;
        return value;
    }
    return -1;
}
//3.3
typedef struct {
    char text[100];
    int line;
} Edit;

typedef struct {
    Edit edits[MAX_SIZE];
    int top;
} UndoStack;

void initUndoStack(UndoStack *s) {
    s->top = -1;
}

void addEdit(UndoStack *s, const char *text, int line) {
    if (s->top < MAX_SIZE - 1) {
        s->top++;
        strncpy(s->edits[s->top].text, text, 99);
        s->edits[s->top].text[99] = '\0';
        s->edits[s->top].line = line;
    }
}

void undo(UndoStack *s) {
    if (s->top >= 0) {
        s->top--;
    }
}
//3.4
typedef struct {
    int id;
    char message[256];
} Transmission;

typedef struct {
    Transmission buffer[MAX_SIZE];
    int front, rear;
} BufferQueue;

void initBuffer(BufferQueue *q) {
    q->front = q->rear = 0;
}

void addToBuffer(BufferQueue *q, int id, const char *message) {
    if ((q->rear + 1) % MAX_SIZE != q->front) {
        q->buffer[q->rear].id = id;
        strncpy(q->buffer[q->rear].message, message, 255);
        q->buffer[q->rear].message[255] = '\0';
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
}

void processBuffer(BufferQueue *q) {
    if (q->front != q->rear) {
        printf("Processing message from ID %d: %s\n", q->buffer[q->front].id, q->buffer[q->front].message);
        q->front = (q->front + 1) % MAX_SIZE;
    }
}
