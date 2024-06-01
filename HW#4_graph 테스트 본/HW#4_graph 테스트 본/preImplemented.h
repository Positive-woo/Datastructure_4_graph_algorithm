/*	=================================================================
*	HW4: Graph Traversal and Path Finding
*	Filename: preImplemented.h
*	Creator: Han-Jin Lee
*	Created: 03/21/2024
*	Purpose: pre-implemented header file for DS_HW4
*	===============================================================*/


#pragma once


/* scanf �� fscanf ����� ���� ���� ��� ���� */
#define _CRT_SECURE_NO_WARNINGS


/* ���̺귯�� �� ������� ���� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>


/* Ÿ�� �� �������� ���� */
#define MAX_NODE 15				// �ִ� ���� ����
#define INF DBL_MAX				// ���Ѵ� ��
#define IMPOSSIBLE -3141592		// �Ұ����� ��


/* ���� ����Ʈ�� ǥ���ϱ� ���� ����ü ���� */
typedef struct Node* GraphPointer;
typedef struct Node {
	int node;				// ����
	double cost;			// ����
	GraphPointer link;		// ���� ��带 ����Ű�� ������
} GraphNode;


/* �׷��� ����ü ���� */
typedef struct {
	bool is_directed;						// ���� �׷��� ����
	int n;									// ������ ����
	bool is_node[MAX_NODE];					// ������ ���� ����
	GraphPointer adj_list[MAX_NODE];		// ���� ����Ʈ
	double adj_mat[MAX_NODE][MAX_NODE];		// ���� ���
} Graph;


/* ���� ����ü ���� */
typedef struct {
	int top;				// ������ top	
	int stack[MAX_NODE];	// ����
} Stack;


/* ť ����ü ���� */
typedef struct {
	int front, rear;			// ť�� front, rear
	int queue[MAX_NODE + 1];	// ť
} Queue;


/* ��ã�� �˰��� ��� ����ü ���� */
typedef struct {
	int path[MAX_NODE];				// ��� (dijkstra, bellman-ford ���� ���)
	double dist[MAX_NODE];			// ���� �������κ����� �Ÿ� (dijkstra, bellman-ford ���� ���)
	double A[MAX_NODE][MAX_NODE];	// �ִ� �Ÿ� (floyd-warshall ���� ���)
} PathInfo;


/* �׷��� �ʱ�ȭ �Լ� */
void init_graph(Graph* G, bool is_directed) {
	/* �� �Լ��� �׷��� ����ü G�� �ʱ�ȭ�ϴ� �Լ��Դϴ�. */

	// ���� �׷��� ���θ� ����
	G->is_directed = is_directed;

	// ������ ������ 0���� �ʱ�ȭ
	G->n = 0;

	// ������ ���� ����, ���� ����Ʈ, ���� ����� �ʱ�ȭ
	for (int i = 0; i < MAX_NODE; i++) {
		G->is_node[i] = false;
		G->adj_list[i] = NULL;
		for (int j = 0; j < MAX_NODE; j++)
			G->adj_mat[i][j] = INF;
	}
}


/* ���� �ʱ�ȭ �Լ� */
void init_stack(Stack* S) {
	/* �� �Լ��� ���� ����ü S�� �ʱ�ȭ�ϴ� �Լ��Դϴ�. */

	// ������ ž�� -1�� �ʱ�ȭ
	S->top = -1;
}


/* ���� push �Լ� */
bool push(Stack* S, int item) {
	/* �� �Լ��� ���� ����ü S�� item�� push�ϴ� �Լ��Դϴ�. */

	// ������ ���� á�� ���
	if (S->top == MAX_NODE - 1)
		return false;

	// item�� ���ÿ� push
	S->stack[++S->top] = item;
	return true;
}


/* ���� pop �Լ� */
int pop(Stack* S) {
	/* �� �Լ��� ���� ����ü S���� item�� pop�ϴ� �Լ��Դϴ�. */

	// ������ ������� ���
	if (S->top == -1)
		return IMPOSSIBLE;

	// ���ÿ��� item�� pop
	return S->stack[S->top--];
}


/* ť �ʱ�ȭ �Լ� */
void init_queue(Queue* Q) {
	/* �� �Լ��� ť ����ü Q�� �ʱ�ȭ�ϴ� �Լ��Դϴ�. */

	// ť�� front, rear�� 0���� �ʱ�ȭ
	Q->front = 0;
	Q->rear = 0;
}


/* ť enqueue �Լ� */
bool enqueue(Queue* Q, int item) {
	/* �� �Լ��� ť ����ü Q�� item�� enqueue�ϴ� �Լ��Դϴ�. */

	// ť�� ���� á�� ���
	if ((Q->rear + 1) % (MAX_NODE + 1) == Q->front)
		return false;

	// item�� ť�� enqueue
	Q->rear = (Q->rear + 1) % (MAX_NODE + 1);
	Q->queue[Q->rear] = item;
	return true;
}


/* ť dequeue �Լ� */
int dequeue(Queue* Q) {
	/* �� �Լ��� ť ����ü Q���� item�� dequeue�ϴ� �Լ��Դϴ�. */

	// ť�� ������� ���
	if (Q->front == Q->rear)
		return IMPOSSIBLE;

	// item�� ť���� dequeue
	Q->front = (Q->front + 1) % (MAX_NODE + 1);
	return Q->queue[Q->front];
}


/* ���� ���� �߰� �Լ� */
void insert_ordered_list(GraphPointer* head, int v, double cost) {
	/* �� �Լ��� ������ ������������ �����Ͽ� ���� ����Ʈ�� �߰��ϴ� �Լ��Դϴ�. */

	// ���ο� ��� ����
	GraphPointer new_node = (GraphPointer)malloc(sizeof(GraphNode));
	new_node->node = v;
	new_node->cost = cost;
	new_node->link = NULL;

	if (*head == NULL || (*head)->node >= v) { // ����Ʈ�� ����ְų� ù ��尡 ���� ��庸�� ũ�ų� ���� ���
		new_node->link = *head;
		*head = new_node;
	}
	else {
		GraphPointer current = *head;
		while (current->link != NULL && current->link->node < v) // ���� ��ġ ã��
			current = current->link;
		new_node->link = current->link;
		current->link = new_node;
	}
}


/* �׷��� ���� ��� */
void print_graph_info(Graph* G) {
	/* �� �Լ��� �׷��� ����ü G�� ������ ����ϴ� �Լ��Դϴ�. */

	// ���� �׷��� ���� ���
	printf("Directed Graph: %s\n", G->is_directed ? "True" : "False");

	// ������ ���� �� ���� ���
	printf("Number of Nodes: %d\n", G->n);
	for (int i = 0; i < MAX_NODE; i++)
		if (G->is_node[i])
			printf("%d ", i);
	printf("\n");

	// ���� ����Ʈ ���
	printf("Adjacency List:\n");
	for (int i = 0; i < MAX_NODE; i++) {
		if (!G->is_node[i])
			continue;
		printf("%d: ", i);
		GraphPointer current = G->adj_list[i];
		while (current != NULL) {
			printf("(%d, %.1lf)\t", current->node, current->cost);
			current = current->link;
		}
		printf("\n");
	}

	// ���� ��� ���
	printf("Adjacency Matrix:\n");
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++) {
			if (G->adj_mat[i][j] == INF)
				printf("INF\t");
			else
				printf("%.1lf\t", G->adj_mat[i][j]);
		}
		printf("\n");
	}
}


/* �׷��� ��� �湮 */
void visit(int v) {
	/* �� �Լ��� ���� v�� �湮�ϴ� �Լ��Դϴ�. */

	// ���� v�� �湮������ ǥ��
	printf("%d ", v);
}


/* ��� ��� �Լ� */
void print_path_info(PathInfo* path_info, int start_node, bool is_floyd) {
	/* �� �Լ��� ��ã�� �˰��� ��� ����ü path_info�� ����ϴ� �Լ��Դϴ�. */

	if (!is_floyd) {
		// ���� ���� ���
		printf("Start Node: %d\n", start_node);

		// ��� ���
		printf("Path: ");
		if (path_info->path[0] == IMPOSSIBLE)
			printf("No Path\n");
		else {
			for (int i = 0; i < MAX_NODE; i++)
				if (path_info->path[i] != IMPOSSIBLE)
					printf("%d -> ", path_info->path[i]);
			printf("\b\b\b  \n");
		}
		// ���� �������κ����� �Ÿ� ���
		printf("Distance: \n");
		for (int i = 0; i < MAX_NODE; i++)
			if (path_info->dist[i] != INF)
				printf("\t%d: %.1lf\n", i, path_info->dist[i]);
		printf("\n");
	}
	else {
		// �ִ� �Ÿ� ���
		printf("Shortest Distance:\n");
		for (int i = 0; i < MAX_NODE; i++) {
			for (int j = 0; j < MAX_NODE; j++) {
				if (path_info->A[i][j] == INF)
					printf("INF\t");
				else
					printf("%.1lf\t", path_info->A[i][j]);
			}
			printf("\n");
		}
	}
}


/* �Լ� ������Ÿ�� ���� (�����ؾ� �ϴ� �Լ����Դϴ�.) */
bool construct_graph_from_file(Graph* graph, FILE* fp);
bool insert_node(Graph* graph, int node);
bool delete_node(Graph* graph, int node);
bool insert_edge(Graph* graph, int v1, int v2, double cost);
bool delete_edge(Graph* graph, int v1, int v2);
void DFS_iterative(Graph* graph, int start_node);
void DFS_recursive(Graph* graph, int node, bool visited[]);
void BFS(Graph* graph, int start_node);
PathInfo dijkstra(Graph* graph, int start, int end);
PathInfo bellman_ford(Graph* graph, int start, int end);
PathInfo floyd_warshall(Graph* graph);