#include <stdio.h>

#define MAX_V 7 // �ִ� Vertex
#define INF 1000 // Adjacent���� ���� Vertex ������ Cost

typedef char bool;
#define FALSE 0
#define TRUE 1

bool found[MAX_V]; // Ư�� Vertex�� TV���տ� ���ϴ��� �˻�
int key[MAX_V]; // TV ���տ� ������ �ʴ� Vertex �� (u, v)���� key[v]�� u���� v�� ���� Edge �� ���� ���� ���� ���Ե�
int PI[MAX_V]; // predecessors index
int TV[MAX_V]; // TV ����
int T[MAX_V][2]; // T ����

void prim(int Graph[MAX_V][MAX_V]); // prim's algorithm ����
int find_min(); // TV 
void print_result(); // ��� ���

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
	int i, u, v; // u�� ����ϴ� vertex, v�� �����ϴ� vertex

	// ��� vertex�� found�� key �ʱ�ȭ
	for (i = 0; i < MAX_V; i++) {
		found[i] = FALSE;
		key[i] = INF;
	}

	// vertex 0�� key, PI �ʱ�ȭ
	key[0] = 0;
	PI[0] = -1;

	for (i = 0; i < MAX_V; i++) {
		u = find_min();
		// vertex u�� ������ ������Ʈ
		found[u] = TRUE;
		TV[i] = u;
		T[i][0] = PI[u];
		T[i][1] = u;

		for (v = 0; v < MAX_V; v++) {
			// cycle�� �������� �ʰ� && �ڱ� �ڽ��� �ƴϸ� && Adjacent�ϰ� && �ּҰ��� ��
			if (found[v] == FALSE && Graph[u][v] != 0 && Graph[u][v] != INF && Graph[u][v] < key[v]) {
				// PI�� key�� ������Ʈ
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
		// T ���տ� ������ �ʰ� key���� �ּҰ��� ��
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

	printf("Prim's algorithm�� �̿��� minimum cost spanning tree ����:\n");
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