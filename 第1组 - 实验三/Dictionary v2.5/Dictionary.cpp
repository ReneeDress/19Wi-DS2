#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Assistance.h"
#include "Dictionary.h"
using namespace std;

int CountLines(char *filename)
{
	ifstream ReadFile;
	int n = 0;
	string temp;
	ReadFile.open(filename,ios::in);
	if(ReadFile.fail())
	{
	   return 0;
	} 
	else
	{
	   while(getline(ReadFile,temp))
	   {
	   	n++;
	   }
	   return n;
	}
	ReadFile.close();
}

int main(void)
{
	ifstream fin;
	ofstream fout;
	char filename[13] = "wordlist.txt";
	cout << "请输入'词书编号.txt'：";
	cin >> filename;
	
	string line[10000];
	string word, type, pron, chn;
	int cline = CountLines(filename);
	Dictionary dict;
	int num;

    char c = 'x';
    string x;
    WordNode *temp;

    while (c != '0')	{
        cout << endl << "1. 初始化词典.";
        cout << endl << "2. 添加词汇.";
        cout << endl << "3. 删除词汇.";
        cout << endl << "4. 查找词汇.";
        cout << endl << "5. 修改词汇.";
        cout << endl << "6. 查看词典.";
        cout << endl << "0. 退出系统.";
		cout << endl << "选择功能(0~6):";
		cin >> c;
		switch (c) 	{
			case '1': {
				fin.open(filename);
				if (!fin.is_open())
				{
					cout << "无法打开文件！" << endl;
					return 0;
				}

				for (int i = 0; i < cline; i++)
				{
					getline(fin, line[i]);
					stringstream sline(line[i]);
					sline >> word >> type >> pron >> chn;
					dict.Insert(word, type, pron, chn);
				}
				cout << "初始化词典成功。" << endl;
				num = dict.NodeCount();
				cout << "共有" << num << "条词条信息。" << endl;
				cout << endl;
				dict.Print();
				dict.Save(filename);
				break;}
		    case '2': {
            	cout << endl << "输入新单词:";
			    cin >> word;
			    cout << endl << "输入新单词的词性:";
			    cin >> type;
			    string ntype = type;
				if (type.length() < 5)
				{
					for (int i = 5; i > type.length(); i--)
					{
						string b = " ";
						ntype = b + type;
					}
				}
				string key = x + ntype;
				if (dict.FindInit(key) == NULL)
				{ cout << "单词已存在." << endl;}
				else
				{
					cout << endl << "输入新单词的拼读音标:";
				    cin >> pron;
				    cout << endl << "输入新单词的中文释义:";
				    cin >> chn;
				    dict.Insert(word, type, pron, chn);
				    cout << setfill(' ') << setw(20) << left << word;	
					cout << setfill(' ') << setw(5) << left << type << "  ";	
					cout << setfill(' ') << setw(30) << left << pron;	
					cout << setfill(' ') << setw(20) << left << chn << endl;
				}
			    break;}
           	case '4':
              	cout << endl << "输入查找的单词:";
			    cin >> x;
			    temp = dict.Find(x);
			    if (temp == NULL)
                   	cout << endl << "单词不存在." << endl;
              	else
              	{
                   	cout << endl << "单词存在." << endl;
                   	cout << setfill(' ') << setw(20) << left << temp->word;	
					cout << setfill(' ') << setw(5) << left << temp->type << "  ";	
					cout << setfill(' ') << setw(30) << left << temp->pron;	
					cout << setfill(' ') << setw(20) << left << temp->chn << endl;
					cout << endl;
              	}
                dict.Save(filename);
			    break;
		    case '3':
              	cout << endl << "输入删除的单词:";
			    cin >> x;
                dict.Delete(x);
                dict.Save(filename);
			    break;
			case '5': {
              	cout << endl << "输入需要修改的单词:";
			    cin >> x;
              	WordNode *target = dict.Find(x);
              	if (target != NULL) {
                cout << endl << "单词存在.";
                cout << endl << "输入需要修改的内容:";
				cout << endl << "1. 词性";
				cout << endl << "2. 拼读音标";
				cout << endl << "3. 中文释义";
				cout << endl;
				cin >> c;
				switch (c) {
				    case '1': {
				    	cout << endl << "输入新单词的词性:";
				    	cin >> type;
				    	string ntype = type;
				    	if (type.length() < 5)
						{
							for (int i = 5; i > type.length(); i--)
							{
								string b = " ";
								ntype = b + type;
							}
						}
						string key = x + ntype;
						WordNode f;
						if (dict.FindInit(key) == NULL)
						{
				    		dict.SetType(target, type);
						}
				    	else
				    	{
				    		cout << endl << "该单词已存在." << endl;
				    	}
				    	break;
				    }
				    case '2': {
				    	cout << endl << "输入新单词的拼读音标:";
				    	cin >> pron;
				    	dict.SetPron(target, pron);
				    	break;
				    }
				    case '3': {
				    	cout << endl << "输入新单词的中文释义:";
				    	cin >> chn;
				    	dict.SetChn(target, chn);
				    	break;
				    }
			    }
			    cout << setfill(' ') << setw(20) << left << target->word;	
				cout << setfill(' ') << setw(5) << left << target->type << "  ";	
				cout << setfill(' ') << setw(30) << left << target->pron;	
				cout << setfill(' ') << setw(20) << left << target->chn << endl;
				cout << endl;
			    dict.Save(filename);
				}
				else
					cout << endl << "单词不存在." << endl;
			    break;
			}
	        case '6':
				cout << endl;
				dict.Print();
				dict.Save(filename);
				break;
		}
	}

	system("PAUSE");				
	return 0;							
}

