#pragma once


/* ���Ϸκ��� �׷��� �����ϴ� �Լ� */
bool construct_graph_from_file(Graph* graph, FILE* fp) {
	/*
		INPUT:
			Graph* graph: �׷��� ����ü ������
			FILE* fp: ���� ������

		OUTPUT:
			bool: �׷��� ���� ���� ����

		DESCRIPTION:
			�� �Լ��� ���Ϸκ��� �׷����� �����ϴ� �Լ��Դϴ�.
			���� �����ͷκ��� ���� ������ �о �׷����� ���� ������ �߰��մϴ�.
			hint : insert_node, insert_edge �Լ� ���
	*/

	char line[100];		// ���� �� ���� ������ ����
	char* token;		// strtok �Լ��� ���� ������
	int v1, v2;			// ��� ��ȣ (v1: ��� ���, v2: ���� ���)
	double cost;		// ������ ����ġ

	/* ==================== FILL YOUR CODE ==================== */
	//fp ���� line ���پ� �������� �ݺ�
	while (fgets(line, sizeof(line), fp) != NULL) 
	{
		//v1 ��ū (���)
		token = strtok(line, " ");
		v1 = atoi(token);

		//v2 ��ū (����)
		token = strtok(NULL, " ");
		v2 = atoi(token);

		//cost ��ū (����ġ)
		token = strtok(NULL, " ");
		cost = atof(token);

		//�׷����� ��� �� ����ġ ����
		insert_node(graph, v1);
		insert_node(graph, v2);
		insert_edge(graph, v1, v2, cost);
		printf("%d, %d, %d ���ԿϷ� \n", v1, v2, cost);
	
	}

	/* ================= YOUR CODE ENDS HERE ================== */

	return true;
}


/* ��� �߰� �Լ� */
bool insert_node(Graph* graph, int node) {
	/*
		INPUT:
			Graph* graph: �׷��� ����ü ������
			int node: �߰��� ��� ��ȣ

		OUTPUT:
			bool: ��� �߰� ���� ����

		DESCRIPTION:
			�� �Լ��� �׷����� ��带 �߰��ϴ� �Լ��Դϴ�.
			hint: graph->is_node �迭�� graph->n ���� ���

	*/

	// ��� ��ȣ�� ��ȿ����, �̹� �����ϴ� ������� Ȯ��
	if (node < 0 || node >= MAX_NODE || graph->is_node[node] == true)
		return false;

	/* ==================== FILL YOUR CODE ==================== */
	
	//�׷��� ����ü�� is_node �� n ����
	graph->is_node[node] = true;
	graph->n++;

	/* ================= YOUR CODE ENDS HERE ================== */

	return true;
}


/* ��� ���� �Լ� */
bool delete_node(Graph* graph, int node) {
	/*
		INPUT:
			Graph* graph: �׷��� ����ü ������
			int node: ������ ��� ��ȣ

		OUTPUT:
			bool: ��� ���� ���� ����

		DESCRIPTION:
			�� �Լ��� �׷������� ��带 �����ϴ� �Լ��Դϴ�.
			��带 ������ ���, �ش� ���� ����� ������ ��� ���ŵǾ�� �մϴ�.
	*/

	// ��� ��ȣ�� ��ȿ����, �����ϴ� ������� Ȯ��
	if (node < 0 || node >= MAX_NODE || graph->is_node[node] == false)
		return false;

	// �ش� ���� ����� ���� ���Ÿ� ���� ���� ����
	GraphPointer curr, prev;

	/* ==================== FILL YOUR CODE ==================== */
	
	// �ش� ���� ����� ��� ���� ���� -> delete_ edge ��������
	for (int i = 0; i < MAX_NODE; i++) {
		if (graph->adj_mat[node][i] != DBL_MAX) {
			delete_edge(graph, node, i);
		}
	}
	
	/* ================= YOUR CODE ENDS HERE ================== */

	graph->is_node[node] = false;
	graph->n--;

	return true;

}


/* ���� �߰� �Լ� */
bool insert_edge(Graph* graph, int v1, int v2, double cost) {
	/*

		INPUT:
			Graph* graph: �׷��� ����ü ������
			int v1: ��� ��� ��ȣ
			int v2: ���� ��� ��ȣ
			double cost: ������ ����ġ

		OUTPUT:
			bool: ���� �߰� ���� ����

		DESCRIPTION:
			�� �Լ��� �׷����� ������ �߰��ϴ� �Լ��Դϴ�.
			adj_list�� ������ �迭�� ������ �߰��� ���,
			������������ ���ĵ� ���·� �����ؾ� �մϴ�.
			hint: insert_ordered_list �Լ� ���

	*/

	// ��� ��ȣ�� ��ȿ����, �̹� �����ϴ� �������� Ȯ��
	if (v1 < 0 || v1 >= MAX_NODE ||
		v2 < 0 || v2 >= MAX_NODE ||
		graph->is_node[v1] == false ||
		graph->is_node[v2] == false ||
		graph->adj_mat[v1][v2] != INF)
		return false;

	/* ==================== FILL YOUR CODE ==================== */
	
	
	// ���� �׷������� ���ο� ���� �ٸ��� ó��
	if (graph->is_directed) {
		// ���� �׷����� ���, �ܹ��� ���� �߰�
		insert_ordered_list(&(graph->adj_list[v1]), v2, cost);
		graph->adj_mat[v1][v2] = cost;
	}
	else {
		// ������ �׷����� ���, ����� ���� �߰�
		// ���� ����Ʈ�� ���� �߰�
		insert_ordered_list(&(graph->adj_list[v1]), v2, cost);
		insert_ordered_list(&(graph->adj_list[v2]), v1, cost);
		// ���� ��Ŀ� ���� �߰�
		graph->adj_mat[v1][v2] = cost;
		graph->adj_mat[v2][v1] = cost;
	}

	/* ================= YOUR CODE ENDS HERE ================== */
}


/* ���� ���� �Լ� */
bool delete_edge(Graph* graph, int v1, int v2) {
	/*

		INPUT:
			Graph* graph: �׷��� ����ü ������
			int v1: ��� ��� ��ȣ
			int v2: ���� ��� ��ȣ

		OUTPUT:
			bool: ���� ���� ���� ����

		DESCRIPTION:
			�� �Լ��� �׷������� ������ �����ϴ� �Լ��Դϴ�.

	*/

	// ��� ��ȣ�� ��ȿ����, �����ϴ� �������� Ȯ��
	if (v1 < 0 || v1 >= MAX_NODE ||
		v2 < 0 || v2 >= MAX_NODE ||
		graph->is_node[v1] == false ||
		graph->is_node[v2] == false ||
		graph->adj_mat[v1][v2] == INF)
		return false;

	// �ش� ������ ã�� ���� ���� ����
	GraphPointer curr, prev;

	/* ==================== FILL YOUR CODE ==================== */
	
	// ���� ����Ʈ (adj_list) �� �����ֱ�   v1   ->    v2
	curr = graph->adj_list[v1];
	prev = NULL;
	
	while (curr != NULL) { // �� �ƴ϶�� ������ ���鼭 ã��
		if (curr->node == v2) {
			if (prev == NULL) { //curr�� ù ��°�ΰ��
				graph->adj_list[v1] = curr->link;
			}
			else { // �Ϲ����� ���
				prev->link = curr->link;
			}
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->link;
	}
	// ���� ����Ʈ (adj_list) �� �����ֱ�   v2   ->    v1
	curr = graph->adj_list[v2];
	prev = NULL;

	while (curr != NULL) { // �� �ƴ϶�� ������ ���鼭 ã��
		if (curr->node == v1) {
			if (prev == NULL) { //curr�� ù ��°�ΰ��
				graph->adj_list[v2] = curr->link;
			}
			else { // �Ϲ����� ���
				prev->link = curr->link;
			}
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->link;
	}

	// ���� ��Ŀ��� ���� inf �� �ٲٱ�
	graph->adj_mat[v1][v2] = DBL_MAX;
	graph->adj_mat[v2][v1] = DBL_MAX;

	/* ================= YOUR CODE ENDS HERE ================== */

	return true;
}


/* DFS - �ݺ��� ���� */
void DFS_iterative(Graph* graph, int start_node) {
	/*

		INPUT:
			Graph* graph: �׷��� ����ü ������
			int start_node: DFS Ž���� ������ ��� ��ȣ

		DESCRIPTION:
			�� �Լ��� DFS Ž���� �ݺ������� ������ �Լ��Դϴ�.
			DFS Ž���� ������ ��� ��ȣ�� �Է¹޾�, �ش� ��带 ��������
			DFS Ž���� �����մϴ�.
			DFS Ž���� ������ ����� visited �迭�� ����˴ϴ�.

	*/

	// �湮 ���θ� �����ϴ� �迭 �� ���� ����
	bool visited[MAX_NODE] = { false, };
	Stack stack;
	init_stack(&stack);

	/* ==================== FILL YOUR CODE ==================== */
	
	//���۳�� ���ÿ� �ְ� �湮
	push(&stack, start_node);
	visited[start_node] = true;
	visit(start_node);
	

	//stack�� �������� �ݺ�
	while (stack.top != -1) {
		int current_node = stack.stack[stack.top]; //top�� �ִ� �� current node�� �ν�
		GraphPointer next_node = graph->adj_list[current_node]; //�������� ���� ���
		
		//���� �� �湮�ߴ�? ����� ����? ��Ʈ��ŷ �ؾ��ϳ�? > ó������ true �� ����
		bool backtracking = true;

		while (next_node != NULL) {
			if (!visited[next_node->node]) { //false��� > �湮 ���ߴٸ� ����
				//���� �Ѽ�Ʈ
				push(&stack, next_node->node);
				visited[next_node->node] = true;
				visit(next_node->node);
				//��Ʈ��ŷ ���ص���
				backtracking = false;
				break;
			}
			next_node = next_node->link;
		}

		//���ϱ�
		if (backtracking) {
			pop(&stack);
		}
	}
	/* ================= YOUR CODE ENDS HERE ================== */

}


/* DFS - ��� ���� */
void DFS_recursive(Graph* graph, int node, bool visited[]) {
	/*

		INPUT:
			Graph* graph: �׷��� ����ü ������
			int node: DFS Ž���� ������ ��� ��ȣ
			bool visited[]: �湮 ���θ� �����ϴ� �迭

		DESCRIPTION:
			�� �Լ��� DFS Ž���� ��ͷ� ������ �Լ��Դϴ�.
			DFS Ž���� ������ ��� ��ȣ�� �Է¹޾�, �ش� ��带 ��������
			DFS Ž���� �����մϴ�.
			DFS Ž���� ������ ����� visited �迭�� ����˴ϴ�.

	*/

	/* ==================== FILL YOUR CODE ==================== */
	visit(node);
	visited[node] = true;
	
	for (GraphPointer curr = graph->adj_list[node]; curr != NULL; curr = curr->link) {
		if (!visited[curr->node]) {
			DFS_recursive(graph, curr->node, visited);
		}
	}

	/* ================= YOUR CODE ENDS HERE ================== */

}


/* BFS */
void BFS(Graph* graph, int start_node) {
	/*

		INPUT:
			Graph* graph: �׷��� ����ü ������
			int start_node: BFS Ž���� ������ ��� ��ȣ

		DESCRIPTION:
			�� �Լ��� BFS Ž���� ������ �Լ��Դϴ�.
			BFS Ž���� ������ ��� ��ȣ�� �Է¹޾�, �ش� ��带 ��������
			BFS Ž���� �����մϴ�.
			BFS Ž���� ������ ����� visited �迭�� ����˴ϴ�.

	*/

	// �湮 ���θ� �����ϴ� �迭 �� ť ����
	bool visited[MAX_NODE] = { false, };
	Queue queue;
	init_queue(&queue);

	/* ==================== FILL YOUR CODE ==================== */
	enqueue(&queue, start_node);
	visited[start_node] = true;
	visit(start_node);

	//queue���� front �� rear�� ��Ī�ϴ°� ���ٸ� = ����ִٸ�
	while (queue.front != queue.rear) {
		int current = dequeue(&queue);

		//adj_list���� ���� ��� null�� �� ������ ������ �̵�
		for (GraphPointer next_node = graph->adj_list[current]; next_node != NULL; next_node = next_node->link) {
			if (!visited[next_node->node]) {
				enqueue(&queue, next_node->node);
				visited[next_node->node] = true;
				visit(next_node->node);
			}
		}
	}
	/* ================= YOUR CODE ENDS HERE ================== */

}


/* Dijkstra �Լ� */
PathInfo dijkstra(Graph* graph, int start, int end) {
	/*

		INPUT:
			Graph* G: �׷��� ����ü ������
			int start: ���� ��� ��ȣ
			int end: ���� ��� ��ȣ

		OUTPUT:
			PathInfo: ���� ���κ��� �ٸ� �������� �ִ� ��� ����
				path: �ִ� ��θ� �����ϴ� �迭
				dist: ���� ���κ��� �ٸ� �������� �ִ� �Ÿ�
				A: ���ͽ�Ʈ�� �˰��򿡼��� ������ ����

		DESCRIPTION:
			�� �Լ��� Dijkstra �˰����� ������ �Լ��Դϴ�.
			���� ��� ��ȣ�� �Է¹޾�, �ش� ��带 ��������
			Dijkstra �˰����� �����մϴ�.
			�ִ� ��� ������ ������ �̿��� result->path �迭�� ����˴ϴ�.
			����, ��ΰ� ���� ��� result->path[0]�� IMPOSSIBLE�� ����Ǿ�� �մϴ�.

	*/

	// �ִ� ��� ������ �����ϴ� ����ü ����
	PathInfo result;
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = INF;
		result.dist[i] = INF;
		result.path[i] = IMPOSSIBLE;
	}

	// ���ͽ�Ʈ�� �˰����� ���� ���� ����
	double dist[MAX_NODE];
	int pred[MAX_NODE];
	bool visited[MAX_NODE] = { false, };

	// �ʱ�ȭ
	for (int i = 0; i < MAX_NODE; i++) {
		visited[i] = false;
		dist[i] = graph->adj_mat[start][i];
		if (dist[i] != INF)
			pred[i] = start;
		else
			pred[i] = -1;
	}
	visited[start] = true;
	dist[start] = 0;
	pred[start] = -1;

	// ��� ������ ���� ���� ����
	Stack stack;
	init_stack(&stack);

	/* ==================== FILL YOUR CODE ==================== */

	//�ּ� �Ÿ� ��带 �����ϱ�
	for (int i = 0; i < MAX_NODE - 1; i++) {
		//�ּ� dist, node ���� ���� 
		double min_dist = INF;
		int min_node = -1;
		//!visit (�湮 ���߰�) dist < min_dist (���� �ּ� �Ÿ����� ª�ٸ�) ������Ʈ
		for (int j = 0; j < MAX_NODE; j++) {
			if (!visited[j] && dist[j] < min_dist) {
				min_dist = dist[j];
				min_node = j;
			}
		}
		//�� �̻� �湮�� ��尡 ���� �� = for �ȿ� if������ ���� ���
		if (min_node == -1) break;
		visited[min_node] = true;

		//���� ��� �Ÿ� ������Ʈ
		for (int j = 0; j < MAX_NODE; j++) {
			// j ��带 �湮�� �� ������� �ϸ�, �ּ� -> j ������ ������ �ֱ� �ؾ���
			if (!visited[j] && graph->adj_mat[min_node][j] != INF) {
				double new_dist = dist[min_node] + graph->adj_mat[min_node][j];
				if (new_dist < dist[j]) {
					dist[j] = new_dist;
					pred[j] = min_node;
				}
			}
		}
	}


	/* ================= YOUR CODE ENDS HERE ================== */

	return result;

}


/* Bellman-Ford �Լ� */
PathInfo bellman_ford(Graph* graph, int start, int end) {
	/*

		INPUT:
			Graph* G: �׷��� ����ü ������
			int start: ���� ��� ��ȣ
			int end: ���� ��� ��ȣ

		OUTPUT:
			PathInfo: ���� ���κ��� �ٸ� �������� �ִ� ��� ����
				path: �ִ� ��θ� �����ϴ� �迭
				dist: ���� ���κ��� �ٸ� �������� �ִ� �Ÿ�
				A: ����-���� �˰��򿡼��� ������ ����

		DESCRIPTION:
			�� �Լ��� Bellman-Ford �˰����� ������ �Լ��Դϴ�.
			���� ��� ��ȣ�� �Է¹޾�, �ش� ��带 ��������
			Bellman-Ford �˰����� �����մϴ�.
			�ִ� ��� ������ ������ �̿��� result->path �迭�� ����˴ϴ�.
			����, ��ΰ� ���� ��� result->path[0]�� IMPOSSIBLE�� ����Ǿ�� �մϴ�.

	*/

	// �ִ� ��� ������ �����ϴ� ����ü ����
	PathInfo result;
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = INF;
		result.dist[i] = INF;
		result.path[i] = IMPOSSIBLE;
	}

	// ����-���� �˰����� ���� ���� ����
	double dist[MAX_NODE];
	int pred[MAX_NODE];

	// �ʱ�ȭ
	for (int i = 0; i < MAX_NODE; i++) {
		dist[i] = graph->adj_mat[start][i];
		if (dist[i] != INF)
			pred[i] = start;
		else
			pred[i] = -1;
	}
	dist[start] = 0;
	pred[start] = -1;

	// ��� ������ ���� ���� ����
	Stack stack;
	init_stack(&stack);

	/* ==================== FILL YOUR CODE ==================== */

;

	/* ================= YOUR CODE ENDS HERE ================== */

	return result;

}


/* Floyd-Warshall �Լ� */
PathInfo floyd_warshall(Graph* graph) {
	/*

		INPUT:
			Graph* G: �׷��� ����ü ������

		OUTPUT:
			PathInfo: ���� ���κ��� �ٸ� �������� �ִ� ��� ����
				path: �÷��̵�-���� �˰��򿡼��� ������ ����
				dist: �÷��̵�-���� �˰��򿡼��� ������ ����
				A: �÷��̵�-���� �˰��򿡼� ���Ǵ� 2���� �迭

		DESCRIPTION:
			�� �Լ��� Floyd-Warshall �˰����� ������ �Լ��Դϴ�.
			�׷����� �Է¹޾�, ��� ��� �ֿ� ���� �ִ� ��θ� ���մϴ�.
			�ִ� ��� ������ A �迭�� ����˴ϴ�.

	*/

	// �ִ� ��� ������ �����ϴ� ����ü ����
	PathInfo result;
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = INF;
		result.dist[i] = INF;
		result.path[i] = IMPOSSIBLE;
	}

	// A �迭 �ʱ�ȭ
	double A[MAX_NODE][MAX_NODE];
	for (int i = 0; i < MAX_NODE; i++)
		for (int j = 0; j < MAX_NODE; j++)
			A[i][j] = graph->adj_mat[i][j];

	/* ==================== FILL YOUR CODE ==================== */



	/* ================= YOUR CODE ENDS HERE ================== */

	// ��� ����
	for (int i = 0; i < MAX_NODE; i++)
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = A[i][j];

	return result;
}