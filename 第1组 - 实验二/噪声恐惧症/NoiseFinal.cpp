#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "LinkStack.h"
#include "Assistance.h"
using namespace std;

#define infi 1000000

int main()
{
	int vexNum, info, ques;
	int arcs[100][100];
	int dist[100][100];
	int path[100][100];

	for (int u = 0; u < 100; u++)
		for (int v = 0; v < 100; v++)
			arcs[u][v] = infi;

	ifstream fin;
	ofstream fout;
	fin.open("noise3.txt");
	if (!fin.is_open())
	{
		cout << "无法打开文件！" << endl;
		return 0;
	}
	string line;

	getline(fin, line);
	stringstream sline(line);
	sline >> vexNum >> info >> ques;

	if (vexNum > 100 || info > 1000) {cout << "顶点数必须小于100个，边的信息必须少于1000条。" << endl; return 0;}

	for (int i = 0; i < info; i++)
	{
		int a, b, val;
		getline(fin, line);
		stringstream sline(line);
		sline >> a >> b >> val;
		--a; --b;
		arcs[a][b] = val;
	}

	for (int u = 0; u < vexNum; u++)
	{
		for (int v = u; v < vexNum; v++)
		{
			arcs[v][u] = arcs[u][v];
		}
		arcs[u][u] = 0;
	}
		
	for (int u = 0; u < vexNum; u++)
		for (int v = 0; v < vexNum; v++)
		{
			dist[u][v] = arcs[u][v];
			dist[v][u] = arcs[u][v];
		}

	for (int u = 0; u < vexNum; u++)
		for (int v = 0; v < vexNum; v++)
		{
			if (u != v && dist[u][v] < infi)
               path[u][v] = u;
			else
               path[u][v] = -1;									
		}

	for (int k = 0; k < vexNum; k++)
		for (int i = 0; i < vexNum; i++)
			for (int j = 0; j < vexNum; j++)
			{
				dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
				path[i][j] = path[k][j];
			}

	fout.open("nnoise.txt");
	for (int i = 0; i < ques; i++)
	{
		int a, b;
		getline(fin, line);
		stringstream sline(line);
		sline >> a >> b;
		if (a > vexNum || b > vexNum) {fout << "no path"; cout << "no path"; continue;}
		--a; --b;
		if (dist[a][b] != infi) 
		{
			fout << dist[a][b]; cout << dist[a][b];
		}
		else {fout << "no path"; cout << "no path";}
		if (i != ques - 1) {fout << endl; cout << endl;}
	}
	fin.close();
	fout.close();
	return 0;
}