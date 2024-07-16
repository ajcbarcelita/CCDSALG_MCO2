#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

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
void insertAtBeginning(singlyNode **head, int data);
void insertAtEnd(singlyNode **head, int data);
void insertAtPosition(singlyNode **head, int data, int pos);
void deleteFirstNode(singlyNode **head);
void deleteLastNode(singlyNode **head);
void deleteAtPosition(singlyNode **head, int pos);
singlyNode* searchNode(singlyNode *head, int data);
int countSize(singlyNode *head);
void freeLinkedList(singlyNode **head);


#endif