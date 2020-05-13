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
              {1,0,1,0,0},
              {1,0,0,1,0}};
void DFS(int u, int cnt)
{
	if (u != 0) visited[u] = true;
	path[cnt] = u;
	if (cnt == n)
	{
		exist = 1;
		return;	
	}
	for (int i = 0; i < n && !exist; i++)
	{
		if(!visited[i] && w[u][i] && i != path[cnt + 1])
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
	cout << "              {1,0,1,0,0}," << endl;
	cout << "              {1,0,0,1,0}};" << endl;
	for(int i = 0; i < n; i++)
	{
		exist = 0;
		DFS(i, 1);
		if (exist && w[path[n]][path[1]]) 
		{
			cout << "有哈密顿回路。路径为：";
			cout << data[path[1]];
			for (int j = 2; j <= n; j++)
			{
				cout << "-" << data[path[j]];
			}
			cout << "-" << data[path[1]] << "。 " << endl;
		break;
		}
	}
	if (!exist) cout << "没有哈密顿回路。" << endl;
	return 0;
}