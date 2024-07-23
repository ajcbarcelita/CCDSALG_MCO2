#include "data_structures.h"

//implement a linked list

singlyNode* createNode (int data) {
    singlyNode *newNode = (singlyNode*)malloc(sizeof(singlyNode));
    if (newNode == NULL) {
        printf("Memory allocation for new node has failed. Terminating program...\n");
        free(newNode);
        exit(-1);
    }
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}

void insertInAscendingOrder(singlyNode **head, int data) {
    singlyNode *newNode = createNode(data);
    if (*head == NULL || (*head)->data >= data) {  //if linked list is empty or the data is less than the data in the first node
        newNode->nextNode = *head;
        *head = newNode;
    } else { //else, find the correct position to insert the new node by traversing the linked list
        singlyNode *temp = *head;
        while (temp->nextNode != NULL && temp->nextNode->data < data) { //stop traversing when the next node is NULL or the next node's data is greater than the data to be inserted
            temp = temp->nextNode;
        }
        //insert the new node after 
        newNode->nextNode = temp->nextNode;
        temp->nextNode = newNode;
    }
}

singlyNode* searchNode(singlyNode *head, int key) {
    singlyNode *current = head;
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->nextNode;
    }
    return NULL;
}

int countSize (singlyNode *head) {
    int count = 0;
    singlyNode *current = head;
    while (current != NULL) {
        count++;
        current = current->nextNode;
    }
    return count;
}

void freeLinkedList(singlyNode **head) {
    singlyNode *current = *head;
    singlyNode *nextNode;
    while (current != NULL) {
        nextNode = current->nextNode;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}
 
//implement an ASCENDING ORDER PRIORITY queue (FIFO) using a SINGLY linked list
/*
    - enqueue (inset at end)
    - dequeue (delete from front)
    - peek (get front element)
    - isEmpty

    we will not use an a priority value of int type for simplicity, since the data can serve as an implicit priority value  
    take note, lower value -> higher priority
*/

PriorityQueue* createPriorityQueue()
{
    PriorityQueue *priorityQueue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (priorityQueue == NULL) {
        printf("Memory allocation for priority queue has failed. Terminating program...\n");
        exit(-1);
    }
    priorityQueue->front = priorityQueue->rear = NULL;
    return priorityQueue;
}

void enqueue (PriorityQueue *priorityQueue, int data) {
     singlyNode *newNode = createNode(data);
     if (priorityQueue->front == NULL) {
            priorityQueue->front = priorityQueue->rear = newNode;
     } else {
        if (data < priorityQueue->front->data) {
            newNode->nextNode = priorityQueue->front;
            priorityQueue->front = newNode;
        } else {
            singlyNode *temp = priorityQueue->front;
            while (temp->nextNode != NULL && temp->nextNode->data < data) {
                temp = temp->nextNode;
            }
            newNode->nextNode = temp->nextNode;
            temp->nextNode = newNode;
            if (newNode->nextNode == NULL) {
                priorityQueue->rear = newNode;
            }
        }
     }
}

bool isEmptyQueue(PriorityQueue *priorityQueue) {
    return priorityQueue->front == NULL;
}

int dequeue(PriorityQueue *priorityQueue) {
    if (isEmptyQueue(priorityQueue)) {
        printf("Priority Queue is empty. Nothing to dequeue.\n");
        return -1;
    } else {
        singlyNode *temp = priorityQueue->front;
        int data = temp->data;
        priorityQueue->front = priorityQueue->front->nextNode;
        free(temp);
        return data;
    }
}

int peek(PriorityQueue *priorityQueue) {
    if (isEmptyQueue(priorityQueue)) {
        printf("Queue is empty. Nothing to peek.\n");
        return -1;
    } else {
        return priorityQueue->front->data;
    }
}

void freePriorityQueue(PriorityQueue *priorityQueue) {
    if (priorityQueue != NULL) {
        singlyNode *current = priorityQueue->front;
        singlyNode *nextNode;
        while (current != NULL) {
            nextNode = current->nextNode;
            free(current);
            current = nextNode;
        }
        priorityQueue->front = priorityQueue->rear = NULL;
        free(priorityQueue);
    }
}

/*
    Stack Implementation
*/
Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation for stack has failed. Terminating program...\n");
        exit(-1);
    }
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int data) {
    singlyNode* newNode = createNode(data);
    if (newNode == NULL) {
        printf("Memory allocation for new node has failed. Terminating program...\n");
        exit(-1);
    }
    newNode->data = data;
    newNode->nextNode = stack->top;
    stack->top = newNode;
}

bool isEmptyStack(Stack *stack) {
    return stack->top == NULL;
}

int pop(Stack *stack) {
    if(isEmptyStack(stack)) {
        printf("Stack is empty. Nothing to pop.\n");
        return -1;
    } else {
        singlyNode *temp = stack->top;
        int data = temp->data;
        stack->top = stack->top->nextNode;
        free(temp);
        return data;
    }
}

int peekStack(Stack *stack) {
    if (isEmptyStack(stack)) {
        printf("Stack is empty. Nothing to peek.\n");
        return -1;
    }
    return stack->top->data;
}


void freeStack(Stack *stack) {
    while(!isEmptyStack(stack)) {
        pop(stack);
    }
    free(stack);
}

