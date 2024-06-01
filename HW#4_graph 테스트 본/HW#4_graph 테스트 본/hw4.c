/*	=================================================================
*	HW4: Graph Traversal and Path Finding
*	Filename: hw4.c
*	Creator: Han-Jin Lee
*	Created: 03/21/2024
*	Purpose: main function for DS_HW4
*	===============================================================*/


/* 헤더파일 포함 */
#include "preImplemented.h"
#include "implementation.h"


/* main 함수 */
void main() {

	// 0. 파일 읽기
	char filename[100];

	printf("그래프 데이터 파일 이름 입력 : ");
	gets(filename);
	
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("파일 열기 실패\n");
		exit(1);
	}

	// 1. 그래프 구성
	Graph G;

	printf("그래프 종류 (0: 무방향, 1: 방향) : ");
	int is_directed;
	scanf("%d", &is_directed);
	getchar();

	init_graph(&G, is_directed == 1 ? true : false);
	construct_graph_from_file(&G, fp);
	fclose(fp);


	// 2. 명령어 처리
	char input[100], command[100];
	char* token;

	while (true) {
		printf(">>> ");
		gets(input);

		token = strtok(input, " ");
		strcpy(command, token);

		if (strcmp(command, "node") == 0) {					// 2-1. 정점 삽입 및 삭제
			
			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("ins 또는 del 입력이 필요합니다.\n");
				continue;
			}
			else if (strcmp(token, "ins") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 입력이 필요합니다.\n");
					continue;
				}
				int v = atoi(token);
				if (insert_node(&G, v))
					print_graph_info(&G);
				else
					printf("삽입 실패!\n");

			}
			else if (strcmp(token, "del") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 입력이 필요합니다.\n");
					continue;
				}
				int v = atoi(token);
				if (delete_node(&G, v))
					print_graph_info(&G);
				else
					printf("삭제 실패!\n");

			}
			else {
				printf("잘못된 명령어\n");
				continue;
			}

		}
		else if (strcmp(command, "edge") == 0) {			// 2-2. 간선 삽입 및 삭제

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("ins 또는 del 입력이 필요합니다.\n");
				continue;
			}
			else if (strcmp(token, "ins") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 및 가중치 입력이 필요합니다.\n");
					continue;
				}
				int v1 = atoi(token);

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 및 가중치 입력이 필요합니다.\n");
					continue;
				}
				int v2 = atoi(token);

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 및 가중치 입력이 필요합니다.\n");
					continue;
				}
				double cost = atof(token);

				if (insert_edge(&G, v1, v2, cost))
					print_graph_info(&G);
				else
					printf("삽입 실패!\n");

			}
			else if (strcmp(token, "del") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 및 가중치 입력이 필요합니다.\n");
					continue;
				}
				int v1 = atoi(token);

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("정점 번호 및 가중치 입력이 필요합니다.\n");
					continue;
				}
				int v2 = atoi(token);

				if (delete_edge(&G, v1, v2))
					print_graph_info(&G);
				else
					printf("삭제 실패!\n");

			}
			else {
				printf("잘못된 명령어\n");
				continue;
			}

		}
		else if (strcmp(command, "dfs") == 0) {			// 2-3. DFS 탐색
			
			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("시작 정점 입력이 필요합니다.\n");
				continue;
			}
			int start_node = atoi(token);

			printf("반복문 버전 DFS 탐색 순서 :\n");
			DFS_iterative(&G, start_node);
			
			printf("\n재귀함수 버전 DFS 탐색 순서 :\n");
			bool visited[MAX_NODE] = { false, };
			DFS_recursive(&G, start_node, visited);

			printf("\n");

		}
		else if (strcmp(command, "bfs") == 0) {			// 2-4. BFS 탐색

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("시작 정점 입력이 필요합니다.\n");
				continue;
			}
			int start_node = atoi(token);

			printf("BFS 탐색 순서 :\n");
			BFS(&G, start_node);
			printf("\n");

		}
		else if (strcmp(command, "dij") == 0) {			// 2-5. dijkstra 알고리즘

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("시작 정점 입력이 필요합니다.\n");
				continue;
			}
			int start_node = atoi(token);

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("도착 정점 입력이 필요합니다.\n");
				continue;
			}
			int end_node = atoi(token);

			printf("Dijkstra 알고리즘 결과 :\n");
			PathInfo result = dijkstra(&G, start_node, end_node);
			print_path_info(&result, start_node, false);

		}
		else if (strcmp(command, "befo") == 0) {		// 2-6. bellman-ford 알고리즘

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("시작 정점 입력이 필요합니다.\n");
				continue;
			}
			int start_node = atoi(token);

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("도착 정점 입력이 필요합니다.\n");
				continue;
			}
			int end_node = atoi(token);

			printf("Bellman-Ford 알고리즘 결과 :\n");
			PathInfo result = bellman_ford(&G, start_node, end_node);
			print_path_info(&result, start_node, false);

		}
		else if (strcmp(command, "flwa") == 0) {		// 2-7. floyd-warshall 알고리즘

			printf("Floyd-Warshall 알고리즘 결과 :\n");
			PathInfo result = floyd_warshall(&G);
			print_path_info(&result, -1, true);

		}
		else if (strcmp(command, "print") == 0)
			print_graph_info(&G);
		else if (strcmp(command, "exit") == 0)
			break;
		else
			printf("잘못된 명령어\n");
	}
}