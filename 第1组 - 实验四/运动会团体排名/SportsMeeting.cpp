#include<iostream>
using namespace std;

const int MAX = 100;

struct college
{
	int score;                     //学院得分
	int athlete[MAX];              //运动员编号
	int No_1;                      //冠军人数
	int No_2;                      //亚军人数
	int No_3;                      //季军人数
	int number;                    //参赛人数
	int college;                   //学院编号
};

struct Sport
{
	int num;                      //破纪录人数
	int person[6];                //前六名编号
	int person_score[6];          //六名运动员的得分
};

int cmp(College a, College b)
{
	if (a.score < b.score)return -1;
	else if (a.score > b.score)return 1;
	else
	{
		if (a.No_1 < b.No_1)return -1;
		else if (a.No_1 > b.No_1)return 1;
		else
		{
			if (a.No_2 < b.No_2)return -1;
			else if (a.No_2 > b.No_2)return 1;
			else
			{
				if (a.No_3 < b.No_3)return -1;
				else if (a.No_3 > b.No_3)return 1;
				else
				{
					if (a.number < b.number)return -1;
					else if (a.number > b.number)return 1;
					else
						return 0;
				}
			}
		}
	}

}

int main()
{
	int n, m;               //比赛项目数和参赛学院数
	cin >> n >> m;
	College clg[MAX];
	Sport spt[MAX];
	
	//初始化
	for (int i = 1; i < MAX; i++)
	{
		clg[i].score = 0;
		clg[i].No_1 = 0;
		clg[i].No_2 = 0;
		clg[i].No_3 = 0;
	}
	for (int i = 1; i < MAX; i++)
	{
		spt[i].person_score[0] = 8;
		spt[i].person_score[1] = 6;
		spt[i].person_score[2] = 4;
		spt[i].person_score[3] = 3;
		spt[i].person_score[4] = 2;
		spt[i].person_score[5] = 1;
	}

	//输入数据
	for (int i = 1; i <= m; i++)
	{
		clg[i].college = i;
		cin >> clg[i].number;
		for (int j = 1; j <= clg[i].number; j++)
			cin >> clg[i].athlete[j];                //第i个学院的第j位运动员编号
	}

	for (int i = 1; i <= n; i++)
	{
		cin >> spt[i].num;
		for (int j = 0; j < 6; j++)
		{
			cin >> spt[i].person[j];               //第i个项目的第j+1名编号
		}
		int temp = 0;
		while (temp < spt[i].num)
		{
			spt[i].person_score[temp] = 2 * spt[i].person_score[temp];
			temp++;
		}
	}
	
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 6;j++)
			for (int p = 1; p <= m; p++)
				for (int q = 1; q <= clg[p].number; q++)
				{
					if (spt[i].person[j] == clg[p].athlete[q])
					{
						clg[p].score = clg[p].score + spt[i].person_score[j];
						if (j == 0)
							clg[p].No_1++;
						else if (j == 1)
							clg[p].No_2++;
						else if (j == 2)
							clg[p].No_3++;
					}
				
				}

	bool finish = false;
	int i = 1;
	while (i < m && !finish)
	{
		finish = true;
		for (int j = 1; j <= m; j++)
			if (cmp(clg[j],clg[j + 1]) == -1) 
			{
				College temp = clg[j];
				clg[j] = clg[j + 1];
				clg[j + 1] = temp;
				finish = false;
			}
		i++;
	}
	
	int p = 1;
	int same = 1;
	for(int k = 1; k <= m; k++)
	{
		cout << p << "  " << clg[k].college;
		while (k <= m)
		{
			while (cmp(clg[k], clg[k + 1]) == 0)
			{
				cout << endl << p << "  " << clg[k + 1].college;
				k++; same++;
			}
			if (cmp(clg[k], clg[k + 1]) != 0)
				break;
		}
		cout << endl;
		p += same;
	}
	
	system("pause");
	return 0;
}