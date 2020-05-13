#include <iostream>
using namespace std;
bool visited[1000];
bool exist;
int num = 0;
int path[1000] = {-1};
int n = 5;
char data[5] = {'A','B','C','D','E'};
int w[5][5]= {{0,1,0,1,0},
              {0,0,1,1,0},
              {0,0,0,0,1},
              {0,0,1,0,0},
              {1,0,0,0,0}};
void DFS(int u, int cnt)
{
	visited[u] = true;
	path[cnt] = u;
	if (cnt == n)
	{
		exist = 1;
		return;	
	}
	for (int i = 0; i < n && !exist; i++)
	{
		if(!visited[i] && w[u][i])
		{
			DFS(i, cnt + 1);
			visited[i] = false;
		}
	}
}
int main()
{
	cout << endl;
	cout << "int w[5][5]= {{0,1,0,1,0}," << endl;
	cout << "              {0,0,1,1,0}," << endl;
	cout << "              {0,0,0,0,1}," << endl;
	cout << "              {0,0,1,0,0}," << endl;
	cout << "              {1,0,0,0,0}};" << endl;
	for(int i = 0; i < n; i++)
	{
		exist = 0;
		DFS(i, 1);
		num++;
		if (exist)
		{
			cout << "一条哈密顿路径为：";
			cout << data[path[1]];
			for (int j = 2; j <= n; j++)
			{
				cout << "-" << data[path[j]];
			}
			cout << "。 " << endl;
			break;
		}
	}
	if (!exist) {cout << "没有哈密顿路径。" << endl;}
	return 0;
}