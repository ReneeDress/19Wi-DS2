#include"Assistance.h"
// #include"MulAdjUndirGraph.h"
#include"MulAdjUndirGraph1.h"
// #include"MulAdjUndirGraph2.h"
// #include"MulAdjUndirGraph3.h"
// #include"MulAdjUndirGraph4.h"
// #include"MulAdjUndirGraph5.h"

int main()
{
	try									// 用try封装可能出现异常的代码
	{
		MulAdjUndirGraph<char, int> g(vexs, n, 7);

		for (int v = 0; v < n; v++)
			for (int u = 0; u < n; u++)
				if (m[v][u] != 0) {g.InsertArc(v, u, m[v][u]);}

		while (c != '#') {
			cout << endl << "1. 显示图.";
			cout << endl << "2. 插入端点序号为v1,v2的带权边.";
			cout << endl << "3. 插入端点数据为e的点.";
			cout << endl << "4. 删除端点序号为v1,v2的带权边.";
			cout << endl << "5. 删除端点序号为v的点.";
			cout << endl << "6. 求序号为v的端点的第一个邻接点.";
			cout << endl << "7. 任意两点之间长度为len的简单路径数目.";
			cout << endl << "8. 删除端点数据为e1,e2的带权边.";
			cout << endl << "9. 删除端点数据为e的点.";
			cout << endl << "a. 顶点v1的相对于v2的下一个邻接点.";
			cout << endl << "#. 退出";
			cout << endl << "选择功能(1~9,a):";
			cin >> c;
			switch (c) {
			case '1':
				cout << "图：" << endl;
				g.Show();
				break;
			case '2':
				cout << "分别输入端点序号v1，v2(用空格键相隔):";
				cin >> v1 >> v2;
				cout << "输入边的权w：";
				cin >> w;
				g.InsertArcP(v1, v2, w);
				g.Show();
				break;
			case '3':
				cout << "输入点的数据：";
				cin >> e;
				g.InsertVex(e);
				break;
			case '7':
				cout << "输入任意两点之间简单路径的长度：";
				cin >> len;
				cout << "任意两点之间长度为" << len << "的简单路径数目为"
					<< g.SimplePathNum(len) << "。" << endl;
				break;
			case '4':
				cout << "输入两点的序号：";
				cin >> v1 >> v2;
				g.DeleteArc(v1, v2);
				break;
			case '8':
				cout << "输入两点的数据：";
				cin >> e1 >> e2;
				g.DeleteArc(e1, e2);
				break;
			case '5':
				cout << "输入点的序号：";
				cin >> v1;
				g.DeleteVex(v1,m);
				break;
			case '9':
				cout << "输入点的数据：";
				cin >> e1;
				g.DeleteVex(e1,m);
				break;
			case '6': 
				{
				cout << "输入点的序号：";
				cin >> v1;
				int adjV = g.FirstAdjVex(v1);
				cout << vexs[v1] << "的第一个邻接点为";
				cout << vexs[adjV] << "。" << endl;
				break;}
			case 'a': 
				cout << "分别输入端点序号v1，v2(用空格键相隔): ";
				cin >> v1 >> v2;
				cout << "顶点" << vexs[v1] << "的相对于" << vexs[v2] << "的下一个邻接点是" << vexs[g.NextAdjVex(v1, v2)] << endl;
				break;
			}
		}
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}
	return 0;
}
