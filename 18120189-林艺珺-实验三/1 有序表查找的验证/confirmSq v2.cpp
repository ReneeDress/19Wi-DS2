#include <iostream>
using namespace std;

int main()
{
	int a[1000], b[1000], c[1000];
	int aNum, bNum, cNum;
	int i = 0, j = 0, k = 0;
	int common;

	cout << endl;
	cout << "!!!Common smallest element!!!" << endl;
	cout << endl;
	cout << "Input aNum bNum cNum" << endl;
	cin >> aNum >> bNum >> cNum;
	if(aNum == i || bNum == j || cNum == k ||
		 aNum <= 0	|| bNum <= 0 || cNum <= 0)
	{
		cout << "Illegal Num." << endl;
		return 1;
	} 
	cout << "Input a" << endl;
	for (i = 0; i < aNum; i++)
	{
		cin >> a[i];
	}
	// for (i = 0; i < aNum; i++)
	// {
	// 	cout << a[i];
	// }
	cout << "Input b" << endl;
	for (j = 0; j < bNum; j++)
	{
		cin >> b[j];
	}
	// for (j = 0; j < bNum; j++)
	// {
	// 	cout << b[j];
	// }
	cout << "Input c" << endl;
	for (k = 0; k < cNum; k++)
	{
		cin >> c[k];
	}
	// for (k = 0; k < cNum; k++)
	// {
	// 	cout << c[k];
	// }
	i = 0, j = 0, k = 0;
		 
	while(i < aNum && j < bNum && k < cNum)
	{
		if(a[i] < b[j]) i++;
		else if(b[j] < c[k]) j++;
		else if(c[k] < a[i]) k++;
		else
		{
			common = a[i];
			cout << "The common element is " << common << ". " << endl;
			cout << "a at " << i+1 << ", ";
			cout << "b at " << j+1 << ", ";
			cout << "c at " << k+1 << "." << endl;
			return 0;
		}
	}

	if(aNum == i || bNum == j || cNum == k ||
		 aNum <= 0	|| bNum <= 0 || cNum <= 0)
	{
		cout << "No common Num." << endl;
		return 1;
	} 
}