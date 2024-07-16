#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "data_structures.h"

//implement a linked list
typedef struct singlyNodeTag {
    int data;
    struct singlyNodeTag *nextNode;
} singlyNode;

singlyNode* createNode(int data)
{
    singlyNode *newNode = (singlyNode*)malloc(sizeof(singlyNode));
    if (newNode == NULL) {
        printf("Memory allocation for new node has failed. Terminating program...\n");
        exit(-1);
    }
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}
/*
    Do the ff operations
    - create a node
    - insert a node at the beginning
    - insert a node at the end
    - insert a node at a specific position
    - delete node (and free memory afterwards)
    - search for a node
    - free linked list
*/

//if you declare a linkedlist like singlyNode* linkedList (this the head)
void insertAtBeginning(singlyNode **head, int data)
{
    singlyNode *newNode = createNode(data);
    newNode->nextNode = *head;
    *head = newNode;
}

void insertAtEnd(singlyNode **head, int data)
{
    singlyNode *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        singlyNode *temp = *head;
        while (temp->nextNode != NULL) {
            temp = temp->nextNode;
        }
        temp->nextNode = newNode;
    }
}

void insertAtPosition(singlyNode **head, int data, int pos)
{
    int i;

    if (pos < 0) {
        printf("Invalid position. Please try again.\n");
        return;
    } else if (pos == 0) {
        insertAtBeginning(head, data);
        return; 
    } else {
        singlyNode *newNode = createNode(data);
        singlyNode *temp = *head;
        for (i = 0; i < pos - 1 && temp != NULL; i++) {
            temp = temp->nextNode; //traverse to the node before the position
        }
        if (temp == NULL) {
            printf("Position is beyond size of linked list. Try again.\n");
            return;
        } else {
            newNode->nextNode = temp->nextNode; //link new node to the node after the position
            temp->nextNode = newNode; //link the node before the position to the new node
        }
    }
}

void deleteFirstNode(singlyNode **head)
{
    if (*head == NULL) {
        printf("Linked list is empty. Nothing to delete.\n");
        return;
    }
    singlyNode *temp = *head;
    *head = (*head)->nextNode;
    free(temp);
}

void deleteLastNode(singlyNode **head)
{
    if (*head == NULL) {
        printf("Linked list is empty. Nothing to delete.\n");
        return;
    }
    singlyNode *temp = *head;
    singlyNode *prev = NULL;
    while (temp->nextNode != NULL) {
        prev = temp;
        temp = temp->nextNode;
    }
    if (prev == NULL) {
        *head = NULL;
    } else {
        prev->nextNode = NULL;
    }
    free(temp);
}

void deleteNodeAtPosition(singlyNode **head, int pos)
{
    int i;
    if (*head == NULL) {
        printf("Linked list is empty. Nothing to delete.\n");
        return;
    } else if (pos < 0) {
        printf("Invalid position. Please try again.\n");
        return;
    } else if (pos == 0) {
        deleteFirstNode(head);
        return;
    }

    singlyNode *temp = *head;
    singlyNode *prev = NULL;
    for (i = 0; i < pos - 1 && temp != NULL; i++) {
        prev = temp;
        temp = temp->nextNode;
    }
    if (temp == NULL) {
        printf("Position is beyond size of linked list. Try again.\n");
        return;
    } else {
        prev->nextNode = temp->nextNode;
        free(temp);
    }
}

singlyNode* searchNode(singlyNode *head, int key)
{
    singlyNode *current = head;
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->nextNode;
    }
    return NULL;
}

int countSize (singlyNode *head)
{
    int count = 0;
    singlyNode *current = head;
    while (current != NULL) {
        count++;
        current = current->nextNode;
    }
    return count;
}

void freeLinkedList(singlyNode **head)
{
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
typedef struct PriorityQueueTag {
    singlyNode *front;
    singlyNode *rear;
} PriorityQueue;

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

void enqueue (PriorityQueue *priorityQueue, int data)
{
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

bool isEmptyQueue(PriorityQueue *priorityQueue)
{
    return priorityQueue->front == NULL;
}

int dequeue(PriorityQueue *priorityQueue)
{
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

int peek(PriorityQueue *priorityQueue)
{
    if (isEmptyQueue(priorityQueue)) {
        printf("Queue is empty. Nothing to peek.\n");
        return -1;
    } else {
        return priorityQueue->front->data;
    }
}

void freePriorityQueue(PriorityQueue *priorityQueue)
{
    if (priorityQueue != NULL) {
        singlyNode *current = priorityQueue->front;
        singlyNode *nextNode;
        while (current != NULL) {
            nextNode = current->nextNode;
            free(current);
            current = nextNode;
        }
        priorityQueue->front = priorityQueue->rear = NULL;
    
    }
}

//implement a stack (LIFO) using a SINGLY linked list
/*
    - push (insert at top)
    - pop (delete from top)
    - peek (get top element)
    - isEmpty
*/
typedef struct StackTag {
    singlyNode *top;
} Stack;

void pushStack();
int pop();
int peekStack();
int isEmptyStack();
