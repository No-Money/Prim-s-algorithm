#include <stdio.h>

#define MAX_V 7 // 최대 Vertex
#define INF 1000 // Adjacent하지 않은 Vertex 사이의 Cost

typedef char bool;
#define FALSE 0
#define TRUE 1

bool found[MAX_V]; // 특정 Vertex가 TV집합에 속하는지 검사
int key[MAX_V]; // TV 집합에 속하지 않는 Vertex 중 (u, v)에서 key[v]는 u에서 v로 가는 Edge 중 가장 작은 값을 갖게됨
int PI[MAX_V]; // predecessors index
int TV[MAX_V]; // TV 집합
int T[MAX_V][2]; // T 집합

void prim(int Graph[MAX_V][MAX_V]); // prim's algorithm 실행
int find_min(); // TV 
void print_result(); // 결과 출력

int main(void)
{
	int Graph[MAX_V][MAX_V] = {
	{0, 3, 17, 6, INF, INF},
	{3, 0, INF, 5, INF, INF, 12},
	{17, INF, 0, INF, 10, 8, INF},
	{6, 5, INF, 0, 9, INF, INF},
	{INF, INF, 10, 9, 0, 4, 2},
	{INF, INF, 8, INF, 4, 0, 14},
	{INF, 12, INF, INF, 2, 14, 0} };

	prim(Graph);

	return 0;
}

void prim(int Graph[MAX_V][MAX_V])
{
	int i, u, v; // u는 출발하는 vertex, v는 도착하는 vertex

	// 모든 vertex의 found와 key 초기화
	for (i = 0; i < MAX_V; i++) {
		found[i] = FALSE;
		key[i] = INF;
	}

	// vertex 0의 key, PI 초기화
	key[0] = 0;
	PI[0] = -1;

	for (i = 0; i < MAX_V; i++) {
		u = find_min();
		// vertex u를 각각에 업데이트
		found[u] = TRUE;
		TV[i] = u;
		T[i][0] = PI[u];
		T[i][1] = u;

		for (v = 0; v < MAX_V; v++) {
			// cycle을 형성하지 않고 && 자기 자신이 아니며 && Adjacent하고 && 최소값일 때
			if (found[v] == FALSE && Graph[u][v] != 0 && Graph[u][v] != INF && Graph[u][v] < key[v]) {
				// PI와 key값 업데이트
				PI[v] = u;
				key[v] = Graph[u][v];
			}
		}
	}
	print_result();
}

int find_min()
{
	int i, index, min = INF;

	for (i = 0; i < MAX_V; i++) {
		// T 집합에 속하지 않고 key값이 최소값일 때
		if (found[i] == FALSE && key[i] < min) {
			min = key[i];
			index = i;
		}
	}
	return index;
}

void print_result()
{
	int i;

	printf("Prim's algorithm을 이용한 minimum cost spanning tree 생성:\n");
	printf("TV={ ");
	for (i = 0; i < MAX_V; i++) {
		if (i == MAX_V - 1)
			printf("%d ", TV[i]);
		else
			printf("%d, ", TV[i]);
	}
	printf("}");
	printf(" T={ ");
	for (i = 1; i < MAX_V; i++) {
		if (i == MAX_V - 1)
			printf("(%d, %d)", T[i][0], T[i][1]);
		else
			printf("(%d, %d), ", T[i][0], T[i][1]);
	}
	printf(" }\n");
}