#pragma once


/* 파일로부터 그래프 구성하는 함수 */
bool construct_graph_from_file(Graph* graph, FILE* fp) {
	/*
		INPUT:
			Graph* graph: 그래프 구조체 포인터
			FILE* fp: 파일 포인터

		OUTPUT:
			bool: 그래프 구성 성공 여부

		DESCRIPTION:
			이 함수는 파일로부터 그래프를 구성하는 함수입니다.
			파일 포인터로부터 파일 내용을 읽어서 그래프에 노드와 엣지를 추가합니다.
			hint : insert_node, insert_edge 함수 사용
	*/

	char line[100];		// 파일 한 줄을 저장할 버퍼
	char* token;		// strtok 함수를 위한 포인터
	int v1, v2;			// 노드 번호 (v1: 출발 노드, v2: 도착 노드)
	double cost;		// 엣지의 가중치

	/* ==================== FILL YOUR CODE ==================== */
	//fp 에서 line 한줄씩 가져오기 반복
	while (fgets(line, sizeof(line), fp) != NULL) 
	{
		//v1 토큰 (출발)
		token = strtok(line, " ");
		v1 = atoi(token);

		//v2 토큰 (도착)
		token = strtok(NULL, " ");
		v2 = atoi(token);

		//cost 토큰 (가중치)
		token = strtok(NULL, " ");
		cost = atof(token);

		//그래프에 노드 및 가중치 저장
		insert_node(graph, v1);
		insert_node(graph, v2);
		insert_edge(graph, v1, v2, cost);
		printf("%d, %d, %d 삽입완료 \n", v1, v2, cost);
	
	}

	/* ================= YOUR CODE ENDS HERE ================== */

	return true;
}


/* 노드 추가 함수 */
bool insert_node(Graph* graph, int node) {
	/*
		INPUT:
			Graph* graph: 그래프 구조체 포인터
			int node: 추가할 노드 번호

		OUTPUT:
			bool: 노드 추가 성공 여부

		DESCRIPTION:
			이 함수는 그래프에 노드를 추가하는 함수입니다.
			hint: graph->is_node 배열과 graph->n 변수 사용

	*/

	// 노드 번호가 유효한지, 이미 존재하는 노드인지 확인
	if (node < 0 || node >= MAX_NODE || graph->is_node[node] == true)
		return false;

	/* ==================== FILL YOUR CODE ==================== */
	
	//그래프 구조체의 is_node 와 n 변경
	graph->is_node[node] = true;
	graph->n++;

	/* ================= YOUR CODE ENDS HERE ================== */

	return true;
}


/* 노드 제거 함수 */
bool delete_node(Graph* graph, int node) {
	/*
		INPUT:
			Graph* graph: 그래프 구조체 포인터
			int node: 제거할 노드 번호

		OUTPUT:
			bool: 노드 제거 성공 여부

		DESCRIPTION:
			이 함수는 그래프에서 노드를 제거하는 함수입니다.
			노드를 제거할 경우, 해당 노드와 연결된 엣지도 모두 제거되어야 합니다.
	*/

	// 노드 번호가 유효한지, 존재하는 노드인지 확인
	if (node < 0 || node >= MAX_NODE || graph->is_node[node] == false)
		return false;

	// 해당 노드와 연결된 엣지 제거를 위한 변수 선언
	GraphPointer curr, prev;

	/* ==================== FILL YOUR CODE ==================== */
	
	// 해당 노드와 연결된 모든 엣지 제거 -> delete_ edge 가져오기
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


/* 엣지 추가 함수 */
bool insert_edge(Graph* graph, int v1, int v2, double cost) {
	/*

		INPUT:
			Graph* graph: 그래프 구조체 포인터
			int v1: 출발 노드 번호
			int v2: 도착 노드 번호
			double cost: 엣지의 가중치

		OUTPUT:
			bool: 엣지 추가 성공 여부

		DESCRIPTION:
			이 함수는 그래프에 엣지를 추가하는 함수입니다.
			adj_list로 구현된 배열에 엣지를 추가할 경우,
			오름차순으로 정렬된 상태로 유지해야 합니다.
			hint: insert_ordered_list 함수 사용

	*/

	// 노드 번호가 유효한지, 이미 존재하는 엣지인지 확인
	if (v1 < 0 || v1 >= MAX_NODE ||
		v2 < 0 || v2 >= MAX_NODE ||
		graph->is_node[v1] == false ||
		graph->is_node[v2] == false ||
		graph->adj_mat[v1][v2] != INF)
		return false;

	/* ==================== FILL YOUR CODE ==================== */
	
	
	// 방향 그래프인지 여부에 따라 다르게 처리
	if (graph->is_directed) {
		// 방향 그래프의 경우, 단방향 엣지 추가
		insert_ordered_list(&(graph->adj_list[v1]), v2, cost);
		graph->adj_mat[v1][v2] = cost;
	}
	else {
		// 무방향 그래프의 경우, 양방향 엣지 추가
		// 인접 리스트에 엣지 추가
		insert_ordered_list(&(graph->adj_list[v1]), v2, cost);
		insert_ordered_list(&(graph->adj_list[v2]), v1, cost);
		// 인접 행렬에 엣지 추가
		graph->adj_mat[v1][v2] = cost;
		graph->adj_mat[v2][v1] = cost;
	}

	/* ================= YOUR CODE ENDS HERE ================== */
}


/* 엣지 제거 함수 */
bool delete_edge(Graph* graph, int v1, int v2) {
	/*

		INPUT:
			Graph* graph: 그래프 구조체 포인터
			int v1: 출발 노드 번호
			int v2: 도착 노드 번호

		OUTPUT:
			bool: 엣지 제거 성공 여부

		DESCRIPTION:
			이 함수는 그래프에서 엣지를 제거하는 함수입니다.

	*/

	// 노드 번호가 유효한지, 존재하는 엣지인지 확인
	if (v1 < 0 || v1 >= MAX_NODE ||
		v2 < 0 || v2 >= MAX_NODE ||
		graph->is_node[v1] == false ||
		graph->is_node[v2] == false ||
		graph->adj_mat[v1][v2] == INF)
		return false;

	// 해당 엣지를 찾기 위한 변수 선언
	GraphPointer curr, prev;

	/* ==================== FILL YOUR CODE ==================== */
	
	// 인접 리스트 (adj_list) 팔 끊어주기   v1   ->    v2
	curr = graph->adj_list[v1];
	prev = NULL;
	
	while (curr != NULL) { // 널 아니라면 앞으로 가면서 찾기
		if (curr->node == v2) {
			if (prev == NULL) { //curr이 첫 번째인경우
				graph->adj_list[v1] = curr->link;
			}
			else { // 일반적인 경우
				prev->link = curr->link;
			}
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->link;
	}
	// 인접 리스트 (adj_list) 팔 끊어주기   v2   ->    v1
	curr = graph->adj_list[v2];
	prev = NULL;

	while (curr != NULL) { // 널 아니라면 앞으로 가면서 찾기
		if (curr->node == v1) {
			if (prev == NULL) { //curr이 첫 번째인경우
				graph->adj_list[v2] = curr->link;
			}
			else { // 일반적인 경우
				prev->link = curr->link;
			}
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->link;
	}

	// 인접 행렬에서 엣지 inf 로 바꾸기
	graph->adj_mat[v1][v2] = DBL_MAX;
	graph->adj_mat[v2][v1] = DBL_MAX;

	/* ================= YOUR CODE ENDS HERE ================== */

	return true;
}


/* DFS - 반복문 버전 */
void DFS_iterative(Graph* graph, int start_node) {
	/*

		INPUT:
			Graph* graph: 그래프 구조체 포인터
			int start_node: DFS 탐색을 시작할 노드 번호

		DESCRIPTION:
			이 함수는 DFS 탐색을 반복문으로 구현한 함수입니다.
			DFS 탐색을 시작할 노드 번호를 입력받아, 해당 노드를 시작으로
			DFS 탐색을 수행합니다.
			DFS 탐색을 수행한 결과는 visited 배열에 저장됩니다.

	*/

	// 방문 여부를 저장하는 배열 및 스택 선언
	bool visited[MAX_NODE] = { false, };
	Stack stack;
	init_stack(&stack);

	/* ==================== FILL YOUR CODE ==================== */
	
	//시작노드 스택에 넣고 방문
	push(&stack, start_node);
	visited[start_node] = true;
	visit(start_node);
	

	//stack이 빌때까지 반복
	while (stack.top != -1) {
		int current_node = stack.stack[stack.top]; //top에 있는 값 current node로 인식
		GraphPointer next_node = graph->adj_list[current_node]; //다음값은 인접 노드
		
		//인접 다 방문했니? 방법이 없나? 백트래킹 해야하나? > 처음에는 true 로 시작
		bool backtracking = true;

		while (next_node != NULL) {
			if (!visited[next_node->node]) { //false라면 > 방문 안했다면 입장
				//세줄 한세트
				push(&stack, next_node->node);
				visited[next_node->node] = true;
				visit(next_node->node);
				//백트래킹 안해도됨
				backtracking = false;
				break;
			}
			next_node = next_node->link;
		}

		//팝하기
		if (backtracking) {
			pop(&stack);
		}
	}
	/* ================= YOUR CODE ENDS HERE ================== */

}


/* DFS - 재귀 버전 */
void DFS_recursive(Graph* graph, int node, bool visited[]) {
	/*

		INPUT:
			Graph* graph: 그래프 구조체 포인터
			int node: DFS 탐색을 시작할 노드 번호
			bool visited[]: 방문 여부를 저장하는 배열

		DESCRIPTION:
			이 함수는 DFS 탐색을 재귀로 구현한 함수입니다.
			DFS 탐색을 시작할 노드 번호를 입력받아, 해당 노드를 시작으로
			DFS 탐색을 수행합니다.
			DFS 탐색을 수행한 결과는 visited 배열에 저장됩니다.

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
			Graph* graph: 그래프 구조체 포인터
			int start_node: BFS 탐색을 시작할 노드 번호

		DESCRIPTION:
			이 함수는 BFS 탐색을 구현한 함수입니다.
			BFS 탐색을 시작할 노드 번호를 입력받아, 해당 노드를 시작으로
			BFS 탐색을 수행합니다.
			BFS 탐색을 수행한 결과는 visited 배열에 저장됩니다.

	*/

	// 방문 여부를 저장하는 배열 및 큐 선언
	bool visited[MAX_NODE] = { false, };
	Queue queue;
	init_queue(&queue);

	/* ==================== FILL YOUR CODE ==================== */
	enqueue(&queue, start_node);
	visited[start_node] = true;
	visit(start_node);

	//queue안의 front 랑 rear가 지칭하는게 같다면 = 비어있다면
	while (queue.front != queue.rear) {
		int current = dequeue(&queue);

		//adj_list에서 다음 노드 null이 될 때까지 앞으로 이동
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


/* Dijkstra 함수 */
PathInfo dijkstra(Graph* graph, int start, int end) {
	/*

		INPUT:
			Graph* G: 그래프 구조체 포인터
			int start: 시작 노드 번호
			int end: 도착 노드 번호

		OUTPUT:
			PathInfo: 시작 노드로부터 다른 노드까지의 최단 경로 정보
				path: 최단 경로를 저장하는 배열
				dist: 시작 노드로부터 다른 노드까지의 최단 거리
				A: 다익스트라 알고리즘에서는 사용되지 않음

		DESCRIPTION:
			이 함수는 Dijkstra 알고리즘을 구현한 함수입니다.
			시작 노드 번호를 입력받아, 해당 노드를 시작으로
			Dijkstra 알고리즘을 수행합니다.
			최단 경로 정보는 스택을 이용해 result->path 배열에 저장됩니다.
			만약, 경로가 없는 경우 result->path[0]에 IMPOSSIBLE이 저장되어야 합니다.

	*/

	// 최단 경로 정보를 저장하는 구조체 선언
	PathInfo result;
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = INF;
		result.dist[i] = INF;
		result.path[i] = IMPOSSIBLE;
	}

	// 다익스트라 알고리즘을 위한 변수 선언
	double dist[MAX_NODE];
	int pred[MAX_NODE];
	bool visited[MAX_NODE] = { false, };

	// 초기화
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

	// 경로 저장을 위한 스택 선언
	Stack stack;
	init_stack(&stack);

	/* ==================== FILL YOUR CODE ==================== */

	//최소 거리 노드를 선택하기
	for (int i = 0; i < MAX_NODE - 1; i++) {
		//최소 dist, node 변수 선언 
		double min_dist = INF;
		int min_node = -1;
		//!visit (방문 안했고) dist < min_dist (현재 최소 거리보다 짧다면) 업데이트
		for (int j = 0; j < MAX_NODE; j++) {
			if (!visited[j] && dist[j] < min_dist) {
				min_dist = dist[j];
				min_node = j;
			}
		}
		//더 이상 방문할 노드가 없을 때 = for 안에 if문으로 못들어간 경우
		if (min_node == -1) break;
		visited[min_node] = true;

		//인접 노드 거리 업데이트
		for (int j = 0; j < MAX_NODE; j++) {
			// j 노드를 방문한 적 없었어야 하며, 최소 -> j 노드까지 간선이 있긴 해야함
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


/* Bellman-Ford 함수 */
PathInfo bellman_ford(Graph* graph, int start, int end) {
	/*

		INPUT:
			Graph* G: 그래프 구조체 포인터
			int start: 시작 노드 번호
			int end: 도착 노드 번호

		OUTPUT:
			PathInfo: 시작 노드로부터 다른 노드까지의 최단 경로 정보
				path: 최단 경로를 저장하는 배열
				dist: 시작 노드로부터 다른 노드까지의 최단 거리
				A: 벨만-포드 알고리즘에서는 사용되지 않음

		DESCRIPTION:
			이 함수는 Bellman-Ford 알고리즘을 구현한 함수입니다.
			시작 노드 번호를 입력받아, 해당 노드를 시작으로
			Bellman-Ford 알고리즘을 수행합니다.
			최단 경로 정보는 스택을 이용해 result->path 배열에 저장됩니다.
			만약, 경로가 없는 경우 result->path[0]에 IMPOSSIBLE이 저장되어야 합니다.

	*/

	// 최단 경로 정보를 저장하는 구조체 선언
	PathInfo result;
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = INF;
		result.dist[i] = INF;
		result.path[i] = IMPOSSIBLE;
	}

	// 벨만-포드 알고리즘을 위한 변수 선언
	double dist[MAX_NODE];
	int pred[MAX_NODE];

	// 초기화
	for (int i = 0; i < MAX_NODE; i++) {
		dist[i] = graph->adj_mat[start][i];
		if (dist[i] != INF)
			pred[i] = start;
		else
			pred[i] = -1;
	}
	dist[start] = 0;
	pred[start] = -1;

	// 경로 저장을 위한 스택 선언
	Stack stack;
	init_stack(&stack);

	/* ==================== FILL YOUR CODE ==================== */

;

	/* ================= YOUR CODE ENDS HERE ================== */

	return result;

}


/* Floyd-Warshall 함수 */
PathInfo floyd_warshall(Graph* graph) {
	/*

		INPUT:
			Graph* G: 그래프 구조체 포인터

		OUTPUT:
			PathInfo: 시작 노드로부터 다른 노드까지의 최단 경로 정보
				path: 플로이드-워셜 알고리즘에서는 사용되지 않음
				dist: 플로이드-워셜 알고리즘에서는 사용되지 않음
				A: 플로이드-워셜 알고리즘에서 사용되는 2차원 배열

		DESCRIPTION:
			이 함수는 Floyd-Warshall 알고리즘을 구현한 함수입니다.
			그래프를 입력받아, 모든 노드 쌍에 대한 최단 경로를 구합니다.
			최단 경로 정보는 A 배열에 저장됩니다.

	*/

	// 최단 경로 정보를 저장하는 구조체 선언
	PathInfo result;
	for (int i = 0; i < MAX_NODE; i++) {
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = INF;
		result.dist[i] = INF;
		result.path[i] = IMPOSSIBLE;
	}

	// A 배열 초기화
	double A[MAX_NODE][MAX_NODE];
	for (int i = 0; i < MAX_NODE; i++)
		for (int j = 0; j < MAX_NODE; j++)
			A[i][j] = graph->adj_mat[i][j];

	/* ==================== FILL YOUR CODE ==================== */



	/* ================= YOUR CODE ENDS HERE ================== */

	// 결과 저장
	for (int i = 0; i < MAX_NODE; i++)
		for (int j = 0; j < MAX_NODE; j++)
			result.A[i][j] = A[i][j];

	return result;
}