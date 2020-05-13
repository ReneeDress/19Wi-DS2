#include"Assistance.h"
// #include"MulAdjUndirGraph.h"
#include"MulAdjUndirGraph1.h"
// #include"MulAdjUndirGraph2.h"
// #include"MulAdjUndirGraph3.h"
// #include"MulAdjUndirGraph4.h"
// #include"MulAdjUndirGraph5.h"

int main()
{
	try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		MulAdjUndirGraph<char, int> g(vexs, n, 7);

		for (int v = 0; v < n; v++)
			for (int u = 0; u < n; u++)
				if (m[v][u] != 0) {g.InsertArc(v, u, m[v][u]);}

		while (c != '#') {
			cout << endl << "1. ��ʾͼ.";
			cout << endl << "2. ����˵����Ϊv1,v2�Ĵ�Ȩ��.";
			cout << endl << "3. ����˵�����Ϊe�ĵ�.";
			cout << endl << "4. ɾ���˵����Ϊv1,v2�Ĵ�Ȩ��.";
			cout << endl << "5. ɾ���˵����Ϊv�ĵ�.";
			cout << endl << "6. �����Ϊv�Ķ˵�ĵ�һ���ڽӵ�.";
			cout << endl << "7. ��������֮�䳤��Ϊlen�ļ�·����Ŀ.";
			cout << endl << "8. ɾ���˵�����Ϊe1,e2�Ĵ�Ȩ��.";
			cout << endl << "9. ɾ���˵�����Ϊe�ĵ�.";
			cout << endl << "a. ����v1�������v2����һ���ڽӵ�.";
			cout << endl << "#. �˳�";
			cout << endl << "ѡ����(1~9,a):";
			cin >> c;
			switch (c) {
			case '1':
				cout << "ͼ��" << endl;
				g.Show();
				break;
			case '2':
				cout << "�ֱ�����˵����v1��v2(�ÿո�����):";
				cin >> v1 >> v2;
				cout << "����ߵ�Ȩw��";
				cin >> w;
				g.InsertArcP(v1, v2, w);
				g.Show();
				break;
			case '3':
				cout << "���������ݣ�";
				cin >> e;
				g.InsertVex(e);
				break;
			case '7':
				cout << "������������֮���·���ĳ��ȣ�";
				cin >> len;
				cout << "��������֮�䳤��Ϊ" << len << "�ļ�·����ĿΪ"
					<< g.SimplePathNum(len) << "��" << endl;
				break;
			case '4':
				cout << "�����������ţ�";
				cin >> v1 >> v2;
				g.DeleteArc(v1, v2);
				break;
			case '8':
				cout << "������������ݣ�";
				cin >> e1 >> e2;
				g.DeleteArc(e1, e2);
				break;
			case '5':
				cout << "��������ţ�";
				cin >> v1;
				g.DeleteVex(v1,m);
				break;
			case '9':
				cout << "���������ݣ�";
				cin >> e1;
				g.DeleteVex(e1,m);
				break;
			case '6': 
				{
				cout << "��������ţ�";
				cin >> v1;
				int adjV = g.FirstAdjVex(v1);
				cout << vexs[v1] << "�ĵ�һ���ڽӵ�Ϊ";
				cout << vexs[adjV] << "��" << endl;
				break;}
			case 'a': 
				cout << "�ֱ�����˵����v1��v2(�ÿո�����): ";
				cin >> v1 >> v2;
				cout << "����" << vexs[v1] << "�������" << vexs[v2] << "����һ���ڽӵ���" << vexs[g.NextAdjVex(v1, v2)] << endl;
				break;
			}
		}
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}
	return 0;
}
