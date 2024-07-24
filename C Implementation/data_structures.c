#include "data_structures.h"

//implement a linked list and only the functions I need

/*
    This function creates a new singly linked list node with the given data. However, this is not inserted into the linked list yet.
    Returns a pointer to the newly created node.

    By Aaron Barcelita.
*/
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

/*
    This function inserts a new node with the given data into a linked list in ascending order.

    By Aaron Barcelita.
*/
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

/*
    This function frees the memory allocated for the linked list. Doing free(LinkedList) is not enough.

    By Aaron Barcelita.
*/
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

/*
    This function creates a new priority queue. The priority queue is implemented using a singly linked list.
    Returns a pointer to the newly created priority queue.

    By Aaron Barcelita.
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

/*
    This function inserts a new node with the given data into the priority queue in ascending order.

    By Aaron Barcelita.
*/
void enqueue (PriorityQueue *priorityQueue, int data) {
     singlyNode *newNode = createNode(data);
     if (priorityQueue->front == NULL) { //if the priority queue is empty
            priorityQueue->front = priorityQueue->rear = newNode;
     } else { 
        if (data < priorityQueue->front->data) { //if the data is less than the data in the first node
            newNode->nextNode = priorityQueue->front;
            priorityQueue->front = newNode;
        } else { //else, find the correct position to insert the new node by traversing the priority queue
            singlyNode *temp = priorityQueue->front;
            while (temp->nextNode != NULL && temp->nextNode->data < data) {
                temp = temp->nextNode;
            }
            newNode->nextNode = temp->nextNode;
            temp->nextNode = newNode;
            if (newNode->nextNode == NULL) { //if the new node is inserted at the end
                priorityQueue->rear = newNode;
            }
        }
     }
}

/*
    This function checks if the priority queue is empty.
    Returns true if the priority queue is empty, false otherwise.

    By Aaron Barcelita.
*/
bool isEmptyQueue(PriorityQueue *priorityQueue) {
    return priorityQueue->front == NULL;
}

/*
    This function removes the node at the front of the priority queue.
    Returns the data of the removed node.

    By Aaron Barcelita.
*/
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

/*
    This function returns the data of the node at the front of the priority queue.

    By Aaron Barcelita.
*/
int peek(PriorityQueue *priorityQueue) {
    if (isEmptyQueue(priorityQueue)) {
        printf("Queue is empty. Nothing to peek.\n");
        return -1;
    } else {
        return priorityQueue->front->data;
    }
}

/*
    This function frees the memory allocated for the priority queue. Doing free(PriorityQueue) is not enough.

    By Aaron Barcelita.
*/
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
    This function creates a new stack. The stack is implemented using a singly linked list.
    Returns a pointer to the newly created stack.

    By Aaron Barcelita.
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

/*
    This function pushes a new node with the given data onto the stack.

    By Aaron Barcelita.
*/
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

/*
    This function checks if the stack is empty.
    Returns true if the stack is empty, false otherwise.

    By Aaron Barcelita.
*/
bool isEmptyStack(Stack *stack) {
    return stack->top == NULL;
}

/*
    This function removes the node at the top of the stack.
    Returns the data of the removed node.

    By Aaron Barcelita.
*/
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

/*
    This function returns the data of the node at the top of the stack.

    By Aaron Barcelita.
*/
int peekStack(Stack *stack) {
    if (isEmptyStack(stack)) {
        printf("Stack is empty. Nothing to peek.\n");
        return -1;
    }
    return stack->top->data;
}

/*
    This function frees the memory allocated for the stack. Doing free(Stack) is not enough.

    By Aaron Barcelita.
*/
void freeStack(Stack *stack) {
    while(!isEmptyStack(stack)) {
        pop(stack);
    }
    free(stack);
}

