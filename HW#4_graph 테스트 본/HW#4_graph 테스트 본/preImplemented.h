/*	=================================================================
*	HW4: Graph Traversal and Path Finding
*	Filename: preImplemented.h
*	Creator: Han-Jin Lee
*	Created: 03/21/2024
*	Purpose: pre-implemented header file for DS_HW4
*	===============================================================*/


#pragma once


/* scanf 및 fscanf 사용을 위한 보안 경고 무시 */
#define _CRT_SECURE_NO_WARNINGS


/* 라이브러리 및 헤더파일 포함 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>


/* 타입 및 전역변수 선언 */
#define MAX_NODE 15				// 최대 정점 개수
#define INF DBL_MAX				// 무한대 값
#define IMPOSSIBLE -3141592		// 불가능한 값


/* 인접 리스트로 표현하기 위한 구조체 선언 */
typedef struct Node* GraphPointer;
typedef struct Node {
	int node;				// 정점
	double cost;			// 가중
	GraphPointer link;		// 다음 노드를 가리키는 포인터
} GraphNode;


/* 그래프 구조체 선언 */
typedef struct {
	bool is_directed;						// 방향 그래프 여부
	int n;									// 정점의 개수
	bool is_node[MAX_NODE];					// 정점의 존재 여부
	GraphPointer adj_list[MAX_NODE];		// 인접 리스트
	double adj_mat[MAX_NODE][MAX_NODE];		// 인접 행렬
} Graph;


/* 스택 구조체 선언 */
typedef struct {
	int top;				// 스택의 top	
	int stack[MAX_NODE];	// 스택
} Stack;


/* 큐 구조체 선언 */
typedef struct {
	int front, rear;			// 큐의 front, rear
	int queue[MAX_NODE + 1];	// 큐
} Queue;


/* 길찾기 알고리즘 결과 구조체 선언 */
typedef struct {
	int path[MAX_NODE];				// 경로 (dijkstra, bellman-ford 에서 사용)
	double dist[MAX_NODE];			// 시작 정점으로부터의 거리 (dijkstra, bellman-ford 에서 사용)
	double A[MAX_NODE][MAX_NODE];	// 최단 거리 (floyd-warshall 에서 사용)
} PathInfo;


/* 그래프 초기화 함수 */
void init_graph(Graph* G, bool is_directed) {
	/* 이 함수는 그래프 구조체 G를 초기화하는 함수입니다. */

	// 방향 그래프 여부를 저장
	G->is_directed = is_directed;

	// 정점의 개수를 0으로 초기화
	G->n = 0;

	// 정점의 존재 여부, 인접 리스트, 인접 행렬을 초기화
	for (int i = 0; i < MAX_NODE; i++) {
		G->is_node[i] = false;
		G->adj_list[i] = NULL;
		for (int j = 0; j < MAX_NODE; j++)
			G->adj_mat[i][j] = INF;
	}
}


/* 스택 초기화 함수 */
void init_stack(Stack* S) {
	/* 이 함수는 스택 구조체 S를 초기화하는 함수입니다. */

	// 스택의 탑을 -1로 초기화
	S->top = -1;
}


/* 스택 push 함수 */
bool push(Stack* S, int item) {
	/* 이 함수는 스택 구조체 S에 item을 push하는 함수입니다. */

	// 스택이 가득 찼을 경우
	if (S->top == MAX_NODE - 1)
		return false;

	// item을 스택에 push
	S->stack[++S->top] = item;
	return true;
}


/* 스택 pop 함수 */
int pop(Stack* S) {
	/* 이 함수는 스택 구조체 S에서 item을 pop하는 함수입니다. */

	// 스택이 비어있을 경우
	if (S->top == -1)
		return IMPOSSIBLE;

	// 스택에서 item을 pop
	return S->stack[S->top--];
}


/* 큐 초기화 함수 */
void init_queue(Queue* Q) {
	/* 이 함수는 큐 구조체 Q를 초기화하는 함수입니다. */

	// 큐의 front, rear를 0으로 초기화
	Q->front = 0;
	Q->rear = 0;
}


/* 큐 enqueue 함수 */
bool enqueue(Queue* Q, int item) {
	/* 이 함수는 큐 구조체 Q에 item을 enqueue하는 함수입니다. */

	// 큐가 가득 찼을 경우
	if ((Q->rear + 1) % (MAX_NODE + 1) == Q->front)
		return false;

	// item을 큐에 enqueue
	Q->rear = (Q->rear + 1) % (MAX_NODE + 1);
	Q->queue[Q->rear] = item;
	return true;
}


/* 큐 dequeue 함수 */
int dequeue(Queue* Q) {
	/* 이 함수는 큐 구조체 Q에서 item을 dequeue하는 함수입니다. */

	// 큐가 비어있을 경우
	if (Q->front == Q->rear)
		return IMPOSSIBLE;

	// item을 큐에서 dequeue
	Q->front = (Q->front + 1) % (MAX_NODE + 1);
	return Q->queue[Q->front];
}


/* 정점 정렬 추가 함수 */
void insert_ordered_list(GraphPointer* head, int v, double cost) {
	/* 이 함수는 정점을 오름차순으로 정렬하여 인접 리스트에 추가하는 함수입니다. */

	// 새로운 노드 생성
	GraphPointer new_node = (GraphPointer)malloc(sizeof(GraphNode));
	new_node->node = v;
	new_node->cost = cost;
	new_node->link = NULL;

	if (*head == NULL || (*head)->node >= v) { // 리스트가 비어있거나 첫 노드가 삽입 노드보다 크거나 같은 경우
		new_node->link = *head;
		*head = new_node;
	}
	else {
		GraphPointer current = *head;
		while (current->link != NULL && current->link->node < v) // 삽입 위치 찾기
			current = current->link;
		new_node->link = current->link;
		current->link = new_node;
	}
}


/* 그래프 정보 출력 */
void print_graph_info(Graph* G) {
	/* 이 함수는 그래프 구조체 G의 정보를 출력하는 함수입니다. */

	// 방향 그래프 여부 출력
	printf("Directed Graph: %s\n", G->is_directed ? "True" : "False");

	// 정점의 개수 및 정점 출력
	printf("Number of Nodes: %d\n", G->n);
	for (int i = 0; i < MAX_NODE; i++)
		if (G->is_node[i])
			printf("%d ", i);
	printf("\n");

	// 인접 리스트 출력
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

	// 인접 행렬 출력
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


/* 그래프 노드 방문 */
void visit(int v) {
	/* 이 함수는 정점 v를 방문하는 함수입니다. */

	// 정점 v를 방문했음을 표시
	printf("%d ", v);
}


/* 경로 출력 함수 */
void print_path_info(PathInfo* path_info, int start_node, bool is_floyd) {
	/* 이 함수는 길찾기 알고리즘 결과 구조체 path_info를 출력하는 함수입니다. */

	if (!is_floyd) {
		// 시작 정점 출력
		printf("Start Node: %d\n", start_node);

		// 경로 출력
		printf("Path: ");
		if (path_info->path[0] == IMPOSSIBLE)
			printf("No Path\n");
		else {
			for (int i = 0; i < MAX_NODE; i++)
				if (path_info->path[i] != IMPOSSIBLE)
					printf("%d -> ", path_info->path[i]);
			printf("\b\b\b  \n");
		}
		// 시작 정점으로부터의 거리 출력
		printf("Distance: \n");
		for (int i = 0; i < MAX_NODE; i++)
			if (path_info->dist[i] != INF)
				printf("\t%d: %.1lf\n", i, path_info->dist[i]);
		printf("\n");
	}
	else {
		// 최단 거리 출력
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


/* 함수 프로토타입 선언 (구현해야 하는 함수들입니다.) */
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