#include "Assistance.h"	
#include "Genealogy.h"
#include <string>
#include <iostream>
#include <iomanip>

Member *temp = NULL;
string clear;

void menu()
{
	cout << "=======		0	�˳�������		=======" << endl;
	cout << "=======		g	��ʾ��������		=======" << endl;
	cout << "=======		1	�������г�Ա		=======" << endl;
	cout << "=======		2	��ѯ���׵�n��		=======" << endl;
	cout << "=======		3	��ѯĳ����Ϣ		=======" << endl;
	cout << "=======		4	���ݳ������ڲ�ѯ	=======" << endl;
	cout << "=======		5	����������ѯ��ϵ	=======" << endl;
	cout << "=======		6	ָ������º���		=======" << endl;
	cout << "=======		7	�޸ĳ�Ա��Ϣ		=======" << endl;
	cout << "=======		8	ɾ��ָ����Ա		=======" << endl;
	return;
}

int main()
{
    try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		MemberData persons[100];
		int parents[100];
		int r, n, cur;
		InFile(persons, parents, r, n, "Genealogy.txt");
		cout << endl;
		Genealogy t(persons, parents, r, n);
		cout << "����:";
		DisplayTWithConcaveShape(t);
		t.ResetGeneration(t.root);

		menu();
		char input;
		while (cin >> input)
		{
			switch(input)
			{
				case '1' :
				cout << "�������г�Ա: ";
				t.LevelOrder(Write);
				cout << endl;
				break;
				case '2' :{
				cout << "�����ѯ���״���: ";
				char w;
				int n;
				cin >> clear;
				w = clear[0];
				n = (int)w - 48;
				getline(cin, clear);
				cout << "��ѯ����";
				int cnt = t.Generation(t.root, n, Write);
				cout << endl;
				if (n != 0 && n <= t.Height(t.root) && n > 0) cout << "��" << n << "����" << cnt << "�ˡ�" << endl;
				break;}
				case '3' :{
				cout << "�����ѯ���׳�Ա����: ";
				t.OutFile("Genealogy.txt");
				string index;
				getchar();
				getline(cin, index);
				temp = t.Search(index);
				if (temp == NULL) {cout << "���޴��ˡ�" << endl; break;}
				t.FindMember(t.root, index);
				t.FindFather(t.root, index);
				t.FindSon(t.root, index);
				cout << endl;
				break;}
				case '4' :{
				cout << "�����ѯ��������: (��ʽ -> yyyy/mm/dd) ";
				t.OutFile("Genealogy.txt");
				string bir;
				getchar();
				getline(cin, bir);
				if (t.FindBirth(t.root, bir) == 0) {cout << "�ޡ�";}
				cout << endl;
				break;}
				case '5' :{
				cout << "��������������ѯ��ϵ: (��ʽ�Կո�ָ� -> ĳĳĳ ĳĳĳ) ";
				t.OutFile("Genealogy.txt");
				string a, b;
				cin >> a >> b;
				getline(cin, clear);
				t.Relationship(t.root, a, b);
				break;}
				case '6' :{
				cout << "��������������Ϣ: " << endl;
				//cout << "��������������Ϣ(���� �������� ����״��(0 δ/1 ��) ���˵�ַ �Ƿ�����(0 ��/1 ��) ��������(0000/00/00)): " << endl;
				//cout << "(��ʽ -> ĳĳĳ yyyy/mm/dd 0 ��ַ 1 0000/00/00) ";
				t.OutFile("Genealogy.txt");
				string na, bi, ad, de;
				bool ma, al;
				cout << "����������: ";
			    cin >> na; getline(cin, clear);
			    cout << "�������������(��ʽ -> yyyy/mm/dd): ";
			    cin >> bi; getline(cin, clear);
			    cout << "���������״��(0:δ�� / 1:�ѻ�): ";
			    cin >> ma; getline(cin, clear);
			    cout << "��������˵�ַ: ";
			    cin >> ad; getline(cin, clear);
			    cout << "�������Ƿ�����(0:���� / 1:����): ";
			    cin >> al; getline(cin, clear);
			    if (al == 0)
			    {
				    cout << "��������������(��ʽ -> yyyy/mm/dd)��";
				    cin >> de; getline(cin, clear);
			    }
			    else {de = "0000/00/00";}
				//cin >> na >> bi >> ma >> ad >> al >> de;
				MemberData newperson = {na,bi,ma,ad,al,de,0};
				cout << "�����丸������: ";
				string dad;
				cin >> dad;
				temp = t.Search(dad);
				int child = t.NodeDegree(temp) + 1;
				t.InsertChild(temp, child, newperson);
				t.ResetGeneration(t.root);
				cout << endl;
				cout << "���¼���: ";
				DisplayTWithConcaveShape(t);
				t.FindMember(t.root, na);
				t.FindFather(t.root, na);
				t.FindSon(t.root, na);
				t.Relationship(t.root, dad, na);
				t.OutFile("Genealogy.txt");
				break;}
				case '7' :{
				cout << "�����޸ĳ�Ա����: ";
				t.OutFile("Genealogy.txt");
				string na;
				cin >> na;
				getline(cin, clear);
				temp = t.Search(na);
				if (temp == NULL) {cout << "���޴��ˡ�" << endl; break;}
				t.FindMember(t.root, na);
				MemberData edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
				char e;
				cout << "ѡ����Ҫ�޸ĵ���Ϣ: 1-����, 2-��������, 3-����״��, 4-���˵�ַ, 5-�Ƿ�����, 6-��������, 0-�˳��޸ġ�" << endl;
				cin >> e;{
				switch (e)
				{
					case '0': break;
					case '1': {
					string newname;
					cout << "�����޸ĺ��Ա������: ";
					cin >> newname;
					edit = { newname,temp->person.birth,temp->person.marriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "��Ϣ�޸ĺ�: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '2': {
					string newbirth;
					cout << "�����޸ĺ��Ա�ĳ�������(yyyy/mm/dd): ";
					cin >> newbirth;
					edit = { temp->person.name,newbirth,temp->person.marriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "��Ϣ�޸ĺ�: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '3': {
					bool newmarriage;
					cout << "�����޸ĺ��Ա�Ļ���״��(0:δ�� / 1:�ѻ�)): ";
					cin >> newmarriage;
					edit = { temp->person.name,temp->person.birth,newmarriage,temp->person.address,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "��Ϣ�޸ĺ�: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '4': {
					string newaddress;
					cout << "�����޸ĺ��Ա�ĸ��˵�ַ: ";
					cin >> newaddress;
					edit = { temp->person.name,temp->person.birth,temp->person.marriage,newaddress,temp->person.alive,temp->person.death,temp->person.generation};
					t.Modify(temp, edit);
					cout << "��Ϣ�޸ĺ�: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '5': {
					bool newalive;
					cout << "�����޸ĺ��Ա�Ƿ�����(0:���� / 1:����): ";
					cin >> newalive;
					if (newalive == 1) 
					{
						edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,newalive,"0000/00/00",temp->person.generation};
						t.Modify(temp, edit);
					}
					else
					{
						string newdeath;
						cout << "�����޸ĺ��Ա����������(yyyy/mm/dd): ";
						cin >> newdeath;
						edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,newalive,newdeath,temp->person.generation};
						t.Modify(temp, edit);
					}
					cout << "��Ϣ�޸ĺ�: " << endl;
					t.FindMember(t.root, temp->person.name);
					break;}
					case '6': {
					if (temp->person.alive == 1) { cout << "�ó�ԱĿǰ�����������޸ġ�5-�Ƿ���������" << endl; break;}
					else
					{
						string newdeath;
						cout << "�����޸ĺ��Ա����������(yyyy/mm/dd): ";
						cin >> newdeath;
						edit = { temp->person.name,temp->person.birth,temp->person.marriage,temp->person.address,temp->person.alive,newdeath,temp->person.generation};
						t.Modify(temp, edit);
						cout << "��Ϣ�޸ĺ�: " << endl;
						t.FindMember(t.root, temp->person.name);
					}
					break;}
					default: break;
				}
				}
				t.OutFile("Genealogy.txt");
				break;}
				case '8' :{
				cout << "����ɾ�����׳�Ա����: ";
				t.OutFile("Genealogy.txt");
				string index;
				getchar();
				getline(cin, index);
				temp = t.Search(index);
				if (temp == NULL) {cout << "���޴��ˡ�" << endl; break;}
				t.Delete(temp);
				cout << "ɾ���ɹ���" << endl;
				t.OutFile("Genealogy.txt");
				break;}
				case 'g' :
				cout << "����:";
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
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}
	return 0;							// ����ֵ0, ���ز���ϵͳ
}

