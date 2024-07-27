#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct singlyNodeTag {
    int data;
    struct singlyNodeTag *nextNode;
} singlyNode;

typedef struct PriorityQueueTag {
    singlyNode *front;
    singlyNode *rear;
} PriorityQueue;

typedef struct StackTag {
    singlyNode *top;
} Stack;

//linked list function prototypes
singlyNode* createNode (int data);
void insertAtEnd(singlyNode **head, int data);
void freeLinkedList(singlyNode **head);

//priority queue function prototypes
PriorityQueue* createPriorityQueue();
void enqueue(PriorityQueue *priorityQueue, int data);
bool isEmptyQueue(PriorityQueue *priorityQueue);
int dequeue(PriorityQueue *priorityQueue);
void freePriorityQueue(PriorityQueue *priorityQueue);

//stack function prototypes
Stack* createStack();
void push(Stack *stack, int data);
int pop(Stack *stack);
bool isEmptyStack(Stack *stack);
void freeStack(Stack *stack);

#endif