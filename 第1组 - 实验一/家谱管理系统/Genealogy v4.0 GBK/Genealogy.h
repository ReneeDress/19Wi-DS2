#ifndef __GENEALOGY_H__
#define __GENEALOGY_H__

#include "LinkQueue.h"
#include "Member.h"
#include <string>

class Genealogy
{
public:
	Member *root;
	/* Part 1 */
	Member *CreateTreeGhelp(MemberData persons[], int parents[], int r, int n);
	Genealogy(MemberData persons[], int parents[], int r, int n);
	/* Part 2 */
	Genealogy();
	Genealogy(const MemberData pers);
	Genealogy(Member *r);
	void Destroy(Member * &r);
	virtual ~Genealogy();
	/* Part 3 */
	int Height(Member *r) const;
	int	Height() const;
	Member * GetRoot() const;
	bool IsEmpty() const;
	/* Part 4 */
	Member *CopyTree(Member *copy);
	Genealogy(const Genealogy &copy);
	Genealogy &operator=(const Genealogy& copy);	
	/* Part 5 */
	Member *FirstChild(Member *cur) const;	
	Member *NextSibling(Member *cur) const;
	Member *PrevSibling(Member *r) const;
	Member *Parent(Member *r, const Member *cur) const;
	Member *Parent(Member *cur) const;
	Member *FirstChildParent(Member* r) const;
	Member* SearchGHelp(string index, Member* rt);
	Member* Search(string index);
	/* Part 6 */
	int NodeDegree(Member *cur) const;
	int Generation(Member *r, int gen,  void (*Visit)(const string &));
	int CountGeneration(Member *index);
	void ResetGeneration(Member *r);
	void FindFather(Member *r, string n);
	bool FindMember(Member *r, string n, bool flag = 0);
	void FindSon(Member *r, string n);
	bool FindBirth(Member *r, string b, bool flag = 0);
	void Relationship(Member *r, string a, string b, bool flaga = 0, bool flagb = 0);
	/* Part 7 */
	Status InsertChild(Member *cur, int i, const MemberData &e);
	void Delete(Member *r);
	void Modify(Member *index, MemberData e);
	/* Part 8 */
	void LevelOrder(void (*Visit)(const string &)) const;
	void MemberInformation(Member *index) const;
	void ViewAllInformation(Member *index) const;
	/* Part 9 */
	void OutFile(string filename= "Genealogy.txt");
	void OutAll(ostream &os, Member *p, int &num, int (&parentnum)[100]);
};
 
void DisplayTWithConcaveShape(const Genealogy &t, Member *r, int level);
void DisplayTWithConcaveShape(const Genealogy &t);
template<int N> 
void InFile(MemberData (&persons)[N], int (&parents)[N], int &r, int &n, string filename = "Genealogy.txt");

/* Part 1 */
Member *Genealogy::CreateTreeGhelp(MemberData persons[], int parents[], int r, int n)
{
	if (r >= 0 && r < n)
	{
		Member *rt = new Member(persons[r]);
		Member *subTreeRoot, *cur;
		for (int i = 0; i < n; i++)	
		{
			if (parents[i] == r)	
			{
				subTreeRoot = CreateTreeGhelp(persons, parents, i, n);
				if (rt->firstChild == NULL)	
				{
					rt->firstChild = subTreeRoot;	
					cur = subTreeRoot;
				}
				else
				{
					cur->nextSibling = subTreeRoot;
					cur = subTreeRoot;
				}
			}
		}
		return rt;
	}
	else return NULL;
}

Genealogy::Genealogy(MemberData persons[], int parents[], int r, int n)
{
	root = CreateTreeGhelp(persons, parents, 0, n);
}

/* Part 2 */
Genealogy::Genealogy()
{
	root = NULL;
}

Genealogy::Genealogy(const MemberData pers)
{
	root = new Member(pers);
}

Genealogy::Genealogy(Member *r)
{
	root = r;
}

void Genealogy::Destroy(Member * &r)
{
    Member *p;
	if (r != NULL)	{
		for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
			Destroy(p);
		delete r;
		r = NULL;
	}
}

Genealogy::~Genealogy()
{
	Destroy(root);
}

/* Part 3 */
int Genealogy::Height(Member *r) const
{
    Member *p;
	if (r == NULL)
		return 0;
	else	{
		int maxSubTreeHeight = 0, h;
		for (p = FirstChild(r); p != NULL;  p = NextSibling(p))	
		{	
			h = Height(p);
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
		}
		return maxSubTreeHeight + 1;
	}
}
 
int Genealogy::Height() const
{
	return Height(root);
}

Member *Genealogy::GetRoot() const
{
	return root;
}
 
bool Genealogy::IsEmpty() const
{
	return root == NULL;
}

/* Part 4 */ 
Member *Genealogy::CopyTree(Member *troot)
{
	if (troot == NULL)
		return NULL;
	else	
	{
		Member *r = new Member(troot->person);
		Member *subTreeRoot, *cur, *p;
		for (p = FirstChild(troot); p != NULL;	p = NextSibling(p))
		{
			subTreeRoot = CopyTree(p);
			if (r->firstChild == NULL)		
			{
				r->firstChild = subTreeRoot;
				cur = subTreeRoot;
			}
			else	
			{
				cur->nextSibling = subTreeRoot;
				cur = subTreeRoot;
			}
		}
		return r;
	}
}
 
Genealogy::Genealogy(const Genealogy &copy)
{
	root = CopyTree(copy.GetRoot());
}
 
Genealogy &Genealogy::operator=(const Genealogy &copy)
{
	if (&copy != this)	
	{
		Destroy(root);
		root = CopyTree(copy.GetRoot());
	}
	return *this;
}

/* Part 5 */ 
Member *Genealogy::FirstChild(Member *cur) const
{
	if (cur == NULL)
		return NULL;	
	else
		return cur->firstChild;
}
 
Member *Genealogy::NextSibling(Member *cur) const
{
	if (cur == NULL)
		return NULL;
	else
		return cur->nextSibling;
}

Member* Genealogy::PrevSibling(Member* r) const
{
	LinkQueue<Member*> q;
	Member* cur, * p, * val;
	if (root != NULL) q.EnQueue(root);
	while (!q.IsEmpty())
	{
		q.DelQueue(cur);
		val = cur->nextSibling;
		if (val == r) return cur;
		for (p = FirstChild(cur); p != NULL; p = NextSibling(p))
		q.EnQueue(p);
	}
	return NULL;
}
 
Member *Genealogy::Parent(Member *r, const Member *cur) const
{
	if (r == NULL) return NULL;
	Member *p;
	for (p = FirstChild(r); p != NULL;	p = NextSibling(p))
		if (p == cur) return r;	
	for (p = FirstChild(r); p != NULL;	p = NextSibling(p))	
	{
		Member *q;
		q = Parent(p, cur);
		if (q != NULL) return q;
	}
	return NULL;
}
 
Member *Genealogy::Parent(Member *cur) const
{
	return Parent(root, cur);
}

Member* Genealogy::FirstChildParent(Member* r) const
{
	LinkQueue<Member*> q;
	Member* cur, * p, * val;
	if (root != NULL) q.EnQueue(root);
	while (!q.IsEmpty()) 
	{
		q.DelQueue(cur);
		val = cur->firstChild;
		if (val == r) return cur;        
		for (p = FirstChild(cur); p != NULL; p = NextSibling(p))
		q.EnQueue(p);
	}
	return NULL;
}

Member* Genealogy::SearchGHelp(string index,Member* rt)
{
	if (rt != NULL)
	{
		if (rt->person.name == index || rt->person.birth == index) return rt;
		Member* temp = NULL;
		for (rt = rt->firstChild; rt != NULL; rt = rt->nextSibling)
		{
			temp = SearchGHelp(index, rt);
			if (temp != NULL)
				return temp;
		}
	}
	return NULL;
}

Member* Genealogy::Search(string index)
{
	Member* temp = SearchGHelp(index, root);
	return temp;
}

/* Part 6 */ 
int Genealogy::NodeDegree(Member *cur) const
{
    Member *p;
	int count = 0;
	for (p = FirstChild(cur); p != NULL; p = NextSibling(p))
		count++;
	return count;
} 

int Genealogy::Generation(Member *r, int gen, void (*Visit)(const string &))
{
	int cnt = 0;
	if (gen == 0 || gen > Height(root) || gen < 0) {cout << "代数不合法。"; return cnt;}
	Member *p;
	if (r == root && gen != 0 && gen <= Height(root) && gen > 0) {cout << "第" << gen << "代: ";}
	if (gen == 1) {cnt = 1; (*Visit)(r->person.name); return cnt;}
	if (gen != 0 && gen != 1 && r == root) {cnt = 0;}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		if (p->person.generation == gen) {(*Visit)(p->person.name); cnt++;}
		else cnt = cnt + Generation(p, gen, Visit);
	}
	return cnt;
}
 
int Genealogy::CountGeneration(Member *index)
{
	if (index == root) return 1;
	Member *p = Parent(index);
	int n = 1;
	while (p != root)
	{
		p = Parent(p);
		n++;
	}
	return n+1;
}
 
void Genealogy::ResetGeneration(Member *r)
{
	Member *p;
	if (r == root) {r->person.generation = CountGeneration(r);}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		p->person.generation = CountGeneration(p);
		ResetGeneration(p);
	}
	return;
}
 
void Genealogy::FindFather(Member *r, string n)
{
	Member *p;
	if (n == root->person.name) {cout << n << "为家谱中最大的祖先，并无其父亲信息。" << endl; return;}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		if (p->person.name == n) {cout << n << "的父亲信息: " << endl; MemberInformation(r); return;}
		else {FindFather(p, n);}
	}
	//if (r -> firstChild == p && p == NULL) {cout << "查无此人。" << endl;}
	return;
}
 
bool Genealogy::FindMember(Member *r, string n, bool flag)
{
	Member *p;
	if (flag == 1) return flag;
	if (n == root->person.name) {cout << n << "的本人信息: " << endl; MemberInformation(root); flag = 1; return flag;}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		if (p->person.name == n) {cout << n << "的本人信息: " << endl; MemberInformation(p); flag = 1; return flag;}
		else {FindMember(p, n, flag);}
	}
	return flag;
}
 
void Genealogy::FindSon(Member *r, string n)
{
	Member *p;
	if (n == root->person.name) 
	{
		cout << n << "的孩子信息: " << endl; 
		Member *c;
		bool flag = 0;
		for (c = root -> firstChild; c != NULL; c = c -> nextSibling)
		{
			MemberInformation(c); flag = 1;
		}
		if (flag == 0) {cout << n << "没有孩子。" << endl;}
		return;
	}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		if (p->person.name == n) 
		{
			cout << n << "的孩子信息: " << endl; 
			Member *c;
			bool flag = 0;
			for (c = p -> firstChild; c != NULL; c = c -> nextSibling)
			{
				MemberInformation(c); flag = 1;
			}
			if (flag == 0) {cout << n << "没有孩子。" << endl;}
		}
		else {FindSon(p, n);}
	}
	//if (r -> firstChild == p && p == NULL) {cout << "查无此人。" << endl;}
	return;
}

bool Genealogy::FindBirth(Member *r, string b, bool flag)
{
	Member *p;
	if (r == root) {cout << "出生日期为" << b << "的成员: "; }
	if (b == root->person.birth && r == root) {flag = 1; cout << root->person.name << " ";}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		if (p->person.birth == b) {flag = 1; cout << p->person.name << " ";}
		flag = FindBirth(p, b, flag);
	}
	return flag;
}
 
void Genealogy::Relationship(Member *r, string a, string b, bool flaga, bool flagb)
{
	Member *pa = Search(a);
	Member *pb = Search(b);

	if (pa == pb) {cout << "请输入不同的家族成员。" << endl; return;}
	int gap = pa->person.generation - pb->person.generation;
	//cout << a << "与" << b << "之间的关系为: ";
	if (gap > 0)//a为后代
	{
		switch(gap)
		{
			case 1:
			if (Parent(pa) == pb) {cout << pb->person.name << "是" << pa->person.name << "的父亲，" << pa->person.name << "是" << pb->person.name << "的孩子。" << endl;}
			else {cout << pb->person.name << "是" << pa->person.name << "的叔伯，" << pa->person.name << "是" << pb->person.name << "的侄子。" << endl;}
			break;
			case 2:
			if (Parent(Parent(pa)) == pb) {cout << pb->person.name << "是" << pa->person.name << "的祖父，" << pa->person.name << "是" << pb->person.name << "的孙子。" << endl;}
			else {cout << pb->person.name << "是" << pa->person.name << "的祖叔伯，" << pa->person.name << "是" << pb->person.name << "的孙侄。" << endl;}		
			break;
			case 3:
			if (Parent(Parent(Parent(pa))) == pb) {cout << pb->person.name << "是" << pa->person.name << "的曾祖父，" << pa->person.name << "是" << pb->person.name << "的曾孙子。" << endl;}
			else {cout << pb->person.name << "是" << pa->person.name << "的曾祖叔伯，" << pa->person.name << "是" << pb->person.name << "的曾孙侄。" << endl;}
			break;				
			default:
			Member *temp = pa;
			while (temp != pb && temp != NULL)
			{
				temp = Parent(temp);
				if (temp == NULL) {cout << pb->person.name << "是" << pa->person.name << "的旁系祖先，" << pa->person.name << "是" << pb->person.name << "的旁系后代。" << endl;}
				else if (temp == pb) {cout << pb->person.name << "是" << pa->person.name << "的直系祖先，" << pa->person.name << "是" << pb->person.name << "的直系后代。" << endl;}
			}
			break;
		}
	}
	else if (gap < 0)//b为后代
	{
		switch(gap)
		{
			case -1:
			if (Parent(pb) == pa) {cout << pa->person.name << "是" << pb->person.name << "的父亲，" << pb->person.name << "是" << pa->person.name << "的孩子。" << endl;}
			else {cout << pa->person.name << "是" << pb->person.name << "的叔伯，" << pb->person.name << "是" << pa->person.name << "的侄子。" << endl;}
			break;
			case -2:
			if (Parent(Parent(pb)) == pa) {cout << pa->person.name << "是" << pb->person.name << "的祖父，" << pb->person.name << "是" << pa->person.name << "的孙子。" << endl;}
			else {cout << pa->person.name << "是" << pb->person.name << "的祖叔伯，" << pb->person.name << "是" << pa->person.name << "的孙侄。" << endl;}		
			break;
			case -3:
			if (Parent(Parent(Parent(pb))) == pa) {cout << pa->person.name << "是" << pb->person.name << "的曾祖父，" << pb->person.name << "是" << pa->person.name << "的曾孙子。" << endl;}
			else {cout << pa->person.name << "是" << pb->person.name << "的曾祖叔伯，" << pb->person.name << "是" << pa->person.name << "的曾孙侄。" << endl;}
			break;				
			default:
			Member *temp = pb;
			while (temp != pa && temp != NULL)
			{
				temp = Parent(temp);
				if (temp == NULL) {cout << pb->person.name << "是" << pa->person.name << "的旁系祖先，" << pa->person.name << "是" << pb->person.name << "的旁系后代。" << endl;}
				else if (temp == pa) {cout << pb->person.name << "是" << pa->person.name << "的直系祖先，" << pa->person.name << "是" << pb->person.name << "的直系后代。" << endl;}
			}
			break;
		}

	}
	else//ab同代
	{
		if (pa != pb && Parent(pa) == Parent(pb)) {cout << pa->person.name << "与" << pb->person.name << "是亲兄弟。" << endl;}
		else {cout << pa->person.name << "与" << pb->person.name << "是表兄弟。" << endl;}
	}
	return;
}

/* Part 7 */ 
Status Genealogy::InsertChild(Member* cur, int i, const MemberData& e)
{
	if (cur == NULL) return FAIL;
	if (i < 1 || i > NodeDegree(cur) + 1) return FAIL;

	Member* newNode = new Member(e);
	if (i == 1) {
		newNode->nextSibling = cur->firstChild;
		cur->firstChild = newNode;
	}
	else 
	{
		Member* p = FirstChild(cur);
		for (int k = 1; k < i - 1; k++)
			p = NextSibling(p);
		newNode->nextSibling = p->nextSibling;
		p->nextSibling = newNode;
	}
	return SUCCESS;
}

void Genealogy::Delete(Member* r)
{
	if (r == root) root = NULL;
	else
	{
		Member* p, * temp;
		p = FirstChildParent(r);
		if (p != NULL) p->firstChild = r->nextSibling;
		temp = PrevSibling(r);
		if (temp != NULL) temp->nextSibling = r->nextSibling;
	}
}

void Genealogy::Modify(Member *index, MemberData e)
{
	index->person = e;
}

/* Part 8 */ 
void Genealogy::LevelOrder(void (*Visit)(const string &)) const
{
	LinkQueue<Member *> q;
	Member *cur, *p;
	if (root != NULL) q.EnQueue(root);
	while (!q.IsEmpty())	
	{
		q.DelQueue(cur);
		(*Visit)(cur->person.name);
		for (p = FirstChild(cur); p != NULL;  p = NextSibling(p))
			q.EnQueue(p);
	}
}
 
void Genealogy::MemberInformation(Member *index) const
{
	cout << "姓    名: " << index->person.name << endl;
	cout << "出生日期: " << index->person.birth << endl;
	if (index->person.marriage) {cout << "婚姻状况: 已婚" << endl;}
	else {cout << "婚姻状况: 未婚" << endl;}
	cout << "个人地址: " << index->person.address << endl;
	if (index->person.alive) {cout << "是否在世: 在世" << endl;}
	else 
	{
		cout << "是否在世: 过世" << endl;
		cout << "死亡日期: " << index->person.death << endl;
	}
	cout << "家谱第" << index->person.generation << "代。" << endl;
}
 
void Genealogy::ViewAllInformation(Member *r) const
{
	Member *p;
	if (r == root) {MemberInformation(r);}
	for (p = r -> firstChild; p != NULL; p = p -> nextSibling)
	{
		MemberInformation(p);
		ViewAllInformation(p);
	}
	return;
}

/* Part 9 */ 
void Genealogy::OutFile(string filename)
{
	ofstream fout;
	fout.open(filename.c_str());
	if(root != NULL)
	{
		fout << 0 << "  " << root->person.name << "  " << root->person.birth << "  " << root->person.marriage
			 << "  " << root->person.address << "  " << root->person.alive << "  " 
			 << root->person.death << "  " << root->person.generation<< "  "  << -1;
		int num = 0;
		int parentnum[100];
		OutAll(fout, root, num, parentnum);
	}
	fout.close();
}

void Genealogy::OutAll(ostream &os, Member *p, int &num, int (&parentnum)[100])
{

	int tag1, tag2;
	for(p = p->firstChild, tag1 = 0, tag2 = num + 1; p != NULL && p -> person.name != ""; p = p->nextSibling)
	{
		num++;
		if(tag1 == 0)
			parentnum[num] = num - 1;
		else
			parentnum[num] = parentnum[tag2];
		os << endl;
		os << num << "  " << p->person.name << "  " << p->person.birth << "  " << p->person.marriage
		   << "  " << p->person.address << "  " << p->person.alive << "  " 
		   << p->person.death << "  " << p->person.generation << "  " << parentnum[num];
		OutAll(os, p, num, parentnum);
		tag1 = 1;
	}
}

void DisplayTWithConcaveShape(const Genealogy &t, Member *r, int level)
{
    Member *p;
	if (r != NULL)	
	{
		cout << endl;
		for(int i = 0; i < level - 1; i++)
			cout<<" ";
		string n;
		n = r->person.name;
		cout << n;
		for (p = t.FirstChild(r); p != NULL;	p = t.NextSibling(p))
			DisplayTWithConcaveShape(t, p, level + 1);
	}
}
 
void DisplayTWithConcaveShape(const Genealogy &t)
{
	DisplayTWithConcaveShape(t, t.GetRoot(), 1);
	cout << endl;
}

template<int N>
void InFile(MemberData (&persons)[N], int (&parents)[N], int &r, int &n, string filename)
{
	ifstream fin;
	fin.open(filename);
	int temp;
	for(n = 0; !fin.eof(); n++)
	{
		fin >> temp;
		fin >> persons[n].name >> persons[n].birth >> persons[n].marriage >> persons[n].address 
			>> persons[n].alive >> persons[n].death >> persons[n].generation >> parents[n];
		if(persons[n].generation == 1) {r = n;}
	}
	fin.close();
}
#endif
