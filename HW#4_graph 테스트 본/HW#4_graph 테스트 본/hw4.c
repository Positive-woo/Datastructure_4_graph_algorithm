/*	=================================================================
*	HW4: Graph Traversal and Path Finding
*	Filename: hw4.c
*	Creator: Han-Jin Lee
*	Created: 03/21/2024
*	Purpose: main function for DS_HW4
*	===============================================================*/


/* ������� ���� */
#include "preImplemented.h"
#include "implementation.h"


/* main �Լ� */
void main() {

	// 0. ���� �б�
	char filename[100];

	printf("�׷��� ������ ���� �̸� �Է� : ");
	gets(filename);
	
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("���� ���� ����\n");
		exit(1);
	}

	// 1. �׷��� ����
	Graph G;

	printf("�׷��� ���� (0: ������, 1: ����) : ");
	int is_directed;
	scanf("%d", &is_directed);
	getchar();

	init_graph(&G, is_directed == 1 ? true : false);
	construct_graph_from_file(&G, fp);
	fclose(fp);


	// 2. ��ɾ� ó��
	char input[100], command[100];
	char* token;

	while (true) {
		printf(">>> ");
		gets(input);

		token = strtok(input, " ");
		strcpy(command, token);

		if (strcmp(command, "node") == 0) {					// 2-1. ���� ���� �� ����
			
			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("ins �Ǵ� del �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			else if (strcmp(token, "ins") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				int v = atoi(token);
				if (insert_node(&G, v))
					print_graph_info(&G);
				else
					printf("���� ����!\n");

			}
			else if (strcmp(token, "del") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				int v = atoi(token);
				if (delete_node(&G, v))
					print_graph_info(&G);
				else
					printf("���� ����!\n");

			}
			else {
				printf("�߸��� ��ɾ�\n");
				continue;
			}

		}
		else if (strcmp(command, "edge") == 0) {			// 2-2. ���� ���� �� ����

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("ins �Ǵ� del �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			else if (strcmp(token, "ins") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �� ����ġ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				int v1 = atoi(token);

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �� ����ġ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				int v2 = atoi(token);

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �� ����ġ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				double cost = atof(token);

				if (insert_edge(&G, v1, v2, cost))
					print_graph_info(&G);
				else
					printf("���� ����!\n");

			}
			else if (strcmp(token, "del") == 0) {

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �� ����ġ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				int v1 = atoi(token);

				token = strtok(NULL, " ");
				if (token == NULL) {
					printf("���� ��ȣ �� ����ġ �Է��� �ʿ��մϴ�.\n");
					continue;
				}
				int v2 = atoi(token);

				if (delete_edge(&G, v1, v2))
					print_graph_info(&G);
				else
					printf("���� ����!\n");

			}
			else {
				printf("�߸��� ��ɾ�\n");
				continue;
			}

		}
		else if (strcmp(command, "dfs") == 0) {			// 2-3. DFS Ž��
			
			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("���� ���� �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			int start_node = atoi(token);

			printf("�ݺ��� ���� DFS Ž�� ���� :\n");
			DFS_iterative(&G, start_node);
			
			printf("\n����Լ� ���� DFS Ž�� ���� :\n");
			bool visited[MAX_NODE] = { false, };
			DFS_recursive(&G, start_node, visited);

			printf("\n");

		}
		else if (strcmp(command, "bfs") == 0) {			// 2-4. BFS Ž��

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("���� ���� �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			int start_node = atoi(token);

			printf("BFS Ž�� ���� :\n");
			BFS(&G, start_node);
			printf("\n");

		}
		else if (strcmp(command, "dij") == 0) {			// 2-5. dijkstra �˰���

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("���� ���� �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			int start_node = atoi(token);

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("���� ���� �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			int end_node = atoi(token);

			printf("Dijkstra �˰��� ��� :\n");
			PathInfo result = dijkstra(&G, start_node, end_node);
			print_path_info(&result, start_node, false);

		}
		else if (strcmp(command, "befo") == 0) {		// 2-6. bellman-ford �˰���

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("���� ���� �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			int start_node = atoi(token);

			token = strtok(NULL, " ");
			if (token == NULL) {
				printf("���� ���� �Է��� �ʿ��մϴ�.\n");
				continue;
			}
			int end_node = atoi(token);

			printf("Bellman-Ford �˰��� ��� :\n");
			PathInfo result = bellman_ford(&G, start_node, end_node);
			print_path_info(&result, start_node, false);

		}
		else if (strcmp(command, "flwa") == 0) {		// 2-7. floyd-warshall �˰���

			printf("Floyd-Warshall �˰��� ��� :\n");
			PathInfo result = floyd_warshall(&G);
			print_path_info(&result, -1, true);

		}
		else if (strcmp(command, "print") == 0)
			print_graph_info(&G);
		else if (strcmp(command, "exit") == 0)
			break;
		else
			printf("�߸��� ��ɾ�\n");
	}
}