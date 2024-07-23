#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.h"

/*
    The adj list implementation is done as an array of singlyNode pointers. 
    These singlyNode pointers will point to the head of each linked list.
*/
singlyNode** loadAdjacencyList(char *fileString, int *numVertices, int *numEdges) {
    FILE *fp;
    int i, j, ID1, ID2, status;

    fp = fopen(fileString, "r");
    if (fp == NULL) {
        printf("File not found. Please try again.\n");
        return NULL;
    } else {
        printf("File found. Now loading...\n");
    }

    fscanf(fp, "%d %d", numVertices, numEdges);
    singlyNode **adjList = malloc(*numVertices * sizeof(singlyNode*));
    if (adjList == NULL) {
        printf("Memory allocation for adjacency list has failed. Terminating program...\n");
        free(adjList);
        fclose(fp);
        exit(-1);
    }

    for (i = 0; i < *numVertices; i++) {
        adjList[i] = NULL;
    }

    while (fscanf(fp, "%d %d", ID1, ID2) == 2) {
        insertInAscendingOrder(&adjList[ID1], ID2);
    }

    fclose(fp);
    return adjList;
}

bool hasEdge_AdjList(singlyNode** adjList, int numVertices, int ID1, int ID2) {
    
}

void printAdjList(singlyNode** adjList, int numVertices) {

}

void printFriendList();
int* findConnections_BFS_AdjList();
int* findConnections_DFS_AdjList();