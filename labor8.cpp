// labor8.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;

typedef struct node {
    int data;
    struct node* next;
} node;

int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[i][j];
        }
    }
    return G;
}
 
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
 
node** createAdj(int** G, int size) {
    node** A = (node**)malloc(size * sizeof(node*));
    for (int i = 0; i < size; i++) {
        A[i] = NULL;
        node* tail = NULL;
        for (int j = 0; j < size; j++) {
            if (G[i][j] == 1) {
                node* newNode = (node*)malloc(sizeof(node));
                newNode->data = j;
                newNode->next = NULL;
                if (tail == NULL) {
                    A[i] = newNode;
                }
                else {
                    tail->next = newNode;
                }
                tail = newNode;
            }
        }
    }
    return A;
}
 
void printAdj(node** A, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        node* current = A[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}
 
 
void BFS(int** G, int size, int* vis, int s) {
    queue <int> q;
    q.push(s);
    vis[s] = 1;
 
    while (!q.empty()) {
        s = q.front();
        q.pop();
        printf("%d ", s);
        for (int i = 0; i < size; i++) {
            if (G[s][i] && !vis[i]) {
                q.push(i);
                vis[i] = 1;
 
            }
        }
    }
    for (int i = 0; i < size; i++) {
        if (!vis[i]) {
            printf("\n");
            BFS(G, size, vis, i);
        }
    }
}
 
void BFSA(node** A, int size, int* vis, int s) {
    queue <int> q;
    q.push(s);
    vis[s] = 1;
    node* current = NULL;
    while (!q.empty()) {
        current = A[q.front()];
        printf("%d ", q.front());
        q.pop();
 
        while (current) {
            if (!vis[current->data]) {
                q.push(current->data);
                vis[current->data] = 1;
            }
            current = current->next;
        }
    }
    for (int i = 0; i < size; i++) {
        if (!vis[i]) {
            printf("\n");
            BFSA(A, size, vis, i);
        }
    }
}
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
    int nG = 4;
	srand(time(NULL));

    printf("������� ���������� ������: ");
	scanf("%d", &nG);

	int** G = createG(nG);;
    node** A = createAdj(G, nG);

	printG(G,nG);

	int* vis = (int*)malloc(sizeof(int) * nG);
	for (int i = 0; i < nG; i++) vis[i] = 0;
	BFS(G, nG, vis, 0);

	for (int i = 0; i < nG; i++) vis[i] = 0;
	printf("\n");
	BFSA(A, nG, vis, 0);
	
	getchar();
	getchar();
	return 0;
}

