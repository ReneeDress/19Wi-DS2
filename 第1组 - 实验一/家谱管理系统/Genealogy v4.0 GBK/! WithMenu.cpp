#include "Assistance.h"	
#include "Genealogy.h"
#include <string>
#include <iostream>
#include <iomanip>

Member *temp = NULL;
string clear;

void menu()
{
	cout << "=======		0	退出本程序		=======" << endl;
	cout << "=======		g	显示完整家谱		=======" << endl;
	cout << "=======		1	家谱所有成员		=======" << endl;
	cout << "=======		2	查询家谱第n代		=======" << endl;
	cout << "=======		3	查询某人信息		=======" << endl;
	cout << "=======		4	根据出生日期查询	=======" << endl;
	cout << "=======		5	两人姓名查询关系	=======" << endl;
	cout << "=======		6	指定添加新孩子		=======" << endl;
	cout << "=======		7	修改成员信息		=======" << endl;
	cout << "=======		8	删除指定成员		=======" << endl;
	return;
}

int main()
{
    try									// 用try封装可能出现异常的代码
	{
		MemberData persons[100];
		int parents[100];
		int r, n, cur;
		InFile(persons, parents, r, n, "Genealogy.txt");
		cout << endl;
		Genealogy t(persons, parents, r, n);
		cout << "家谱:";
		DisplayTWithConcaveShape(t);
		t.ResetGeneration(t.root);

		menu();
		char input;
		while (cin >> input)
		{
			switch(input)
			{
				case '1' :
				cout << "家谱所有成员: ";
				t.LevelOrder(Write);
				cout << endl;
				break;
				case '2' :{
				cout << "输入查询家谱代数: ";
				char w;
				int n;
				cin >> clear;
				w = clear[0];
				n = (int)w - 48;
				getline(cin, clear);
				cout << "查询家谱";
				int cnt = t.Generation(t.root, n, Write);
				cout << endl;
				if (n != 0 && n <= t.Height(t.root) && n > 0) cout << "第" << n << "代共" << cnt << "人。" << endl;
				break;}
				case '3' :{
				cout << "输入查询家谱成员姓名: ";
				t.OutFile("Genealogy.txt");
				string index;
				getchar();
				getline(cin, index);
				temp = t.Search(index);
				if (temp == NULL) {cout << "查无此人。" << endl; break;}
				t.FindMember(t.root, index);
				t.FindFather(t.root, index);
				t.FindSon(t.root, index);
				cout << endl;
				break;}
				case '4' :{
				cout << "输入查询出生日期: (格式 -> yyyy/mm/dd) ";
				t.OutFile("Genealogy.txt");
				string bir;
				getchar();
				getline(cin, bir);
				if (t.FindBirth(t.root, bir) == 0) {cout << "无。";}
				cout << endl;
				break;}
				case '5' :{
				cout << "输入两人姓名查询关系: (格式以空格分隔 -> 某某某 某某某) ";
				t.OutFile("Genealogy.txt");
				string a, b;
				cin >> a >> b;
				getline(cin, clear);
				t.Relationship(t.root, a, b);
				break;}
				case '6' :{
				cout << "输入新增孩子信息: " << endl;
				//cout << "输入新增孩子信息(姓名 出生日期 婚姻状况(0 未/1 已) 个人地址 是否在世(0 过/1 在) 死亡日期(0000/00/00)): " << endl;
				//cout << "(格式 -> 某某某 yyyy/mm/dd 0 地址 1 0000/00/00) ";
				t.OutFile("Genealogy.txt");
				string na, bi, ad, de;
				bool ma, al;
				cout << "请输入姓名: ";
			    cin >> na; getline(cin, clear);
			    cout << "请输入出生日期(格式 -> yyyy/mm/dd): ";
			    cin >> bi; getline(cin, clear);
			    cout << "请输入婚姻状况(0:未婚 / 1:已婚): ";
			    cin >> ma; getline(cin, clear);
			    cout << "请输入个人地址: ";
			    cin >> ad; getline(cin, clear);
			    cout << "请输入是否在世(0:过世 / 1:在世): ";
			    cin >> al; getline(cin, clear);
			    if (al == 0)
			    {
				    cout << "请输入死亡日期(格式 -> yyyy/mm/dd)：";
				    cin >> de; getline(cin, clear);
			    }
			    else {de = "0000/00/00";}
				//cin >> na >> bi >> ma >> ad >> al >> de;
				MemberData newperson = {na,bi,ma,ad,al,de,0};
				cout << "输入其父亲姓名: ";
				string dad;
				cin >> dad;
				temp = t.Search(dad);
				int child = t.NodeDegree(temp) + 1;
				t.InsertChild(temp, child, newperson);
				t.ResetGeneration(t.root);
				cout << endl;
				cout << "更新家谱: ";
				DisplayTWithConcaveShape(t);
				t.FindMember(t.root, na);
				t.FindFather(t.root, na);
				t.FindSon(t.root, na);
				t.Relationship(t.root, dad, na);
				t.OutFile("Genealogy.txt");
				break;}
				case '7' :{
				cout << "输入修改成员姓名: ";
				t.OutFile("Genealogy.txt");
				string na;
				cin >> na;
				getline(cin, clear);
				temp = t.Search(na);
				if (temp == NULL) {cout << "查无此人。" << endl; break;}
				t.FindMember(t.root, na);
				MemberData edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
				char e;
				cout << "选择您要修改的信息: 1-姓名, 2-出生日期, 3-婚姻状况, 4-个人地址, 5-是否在世, 6-死亡日期, 0-退出修改。" << endl;
				cin >> e;{
				switch (e)
				{
					case '0': break;
					case '1': {
					string newname;
					cout << "输入修改后成员的姓名: ";
					cin >> newname;
					edit = { newname,temp->person.birth,temp->person.marriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "信息修改后: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '2': {
					string newbirth;
					cout << "输入修改后成员的出生日期(yyyy/mm/dd): ";
					cin >> newbirth;
					edit = { temp->person.name,newbirth,temp->person.marriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "信息修改后: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '3': {
					bool newmarriage;
					cout << "输入修改后成员的婚姻状况(0:未婚 / 1:已婚)): ";
					cin >> newmarriage;
					edit = { temp->person.name,temp->person.birth,newmarriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "信息修改后: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '4': {
					string newaddress;
					cout << "输入修改后成员的个人地址: ";
					cin >> newaddress;
					edit = { temp->person.name,temp->person.birth,temp->person.marriage,newaddress,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "信息修改后: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '5': {
					bool newalive;
					cout << "输入修改后成员是否在世(0:过世 / 1:在世): ";
					cin >> newalive;
					if (newalive == 1) 
					{
						edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,newalive,"0000/00/00",temp->person.generation};
						t.Modify(temp, edit);
					}
					else
					{
						string newdeath;
						cout << "输入修改后成员的死亡日期(yyyy/mm/dd): ";
						cin >> newdeath;
						edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,newalive,newdeath,temp->person.generation};
						t.Modify(temp, edit);
					}
					cout << "信息修改后: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '6': {
					if (temp->person.alive == 1) { cout << "该成员目前在世，请先修改‘5-是否在世’。" << endl; break;}
					else
					{
						string newdeath;
						cout << "输入修改后成员的死亡日期(yyyy/mm/dd): ";
						cin >> newdeath;
						edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,temp->person.alive,newdeath,temp->person.generation};
						t.Modify(temp, edit);
						cout << "信息修改后: " << endl;
						t.FindMember(t.root, temp->person.name);
					}
					break;}
					default: break;
				}
				}
				t.OutFile("Genealogy.txt");
				break;}
				case '8' :{
				cout << "输入删除家谱成员姓名: ";
				t.OutFile("Genealogy.txt");
				string index;
				getchar();
				getline(cin, index);
				temp = t.Search(index);
				if (temp == NULL) {cout << "查无此人。" << endl; break;}
				t.Delete(temp);
				cout << "删除成功。" << endl;
				t.OutFile("Genealogy.txt");
				break;}
				case 'g' :
				cout << "家谱:";
				DisplayTWithConcaveShape(t);
				t.OutFile("Genealogy.txt");
				break;
				case '0' :
				return 0;
				default : t.OutFile("Genealogy.txt");
			}
			menu();
		}
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}
	return 0;							// 返回值0, 返回操作系统
}

