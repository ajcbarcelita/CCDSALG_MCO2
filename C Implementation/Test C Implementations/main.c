#include "data_structures.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

    PriorityQueue *PriorityQueue = createPriorityQueue();
    enqueue(PriorityQueue, 5);
    enqueue(PriorityQueue, 3);
    enqueue(PriorityQueue, 7);
    enqueue(PriorityQueue, 1);
    printf("Peek: %d\n", peek(PriorityQueue));
    printf("Dequeue: %d\n", dequeue(PriorityQueue));
    printf("Peek: %d\n", peek(PriorityQueue));
    printf("Dequeue: %d\n", dequeue(PriorityQueue));
    printf("Peek: %d\n", peek(PriorityQueue));
    printf("Dequeue: %d\n", dequeue(PriorityQueue));
    printf("Peek: %d\n", peek(PriorityQueue));
    printf("Dequeue: %d\n", dequeue(PriorityQueue));
    printf("Peek: %d\n", peek(PriorityQueue));
    printf("Dequeue: %d\n", dequeue(PriorityQueue));
    return 0;
}