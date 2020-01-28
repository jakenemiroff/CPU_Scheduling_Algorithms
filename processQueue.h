#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
   
   int name;
   int duration;
   struct Node *next;

} Node;

typedef struct Queue {

    struct Node *front, *rear;
    int queueIndex;
    int timeQuantum;
    int size;

} Queue;

Queue* createQueue();

Node* createNode(Queue* queue, int value);

void enQueue(Queue *queue, int value);	

void enQueueNode(Queue *queue, Node* newNode);

void sortedEnqueueNode(Queue *queue, Node* newNode);

Node* deQueue(Queue *queue);

void display(Queue *queue);

void buildQueue(Queue *queue, char line[]);

Queue* sortQueue(Queue *queue);

void freeQueueSpace(Queue* queue);