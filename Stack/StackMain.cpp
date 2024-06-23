#include <iostream>
using namespace std;
#include "Stack.h"
void Xuat(int cs, int sm, bool XuatSao)
{
	if (XuatSao)
	{
		cout << "*";
	}
	cout << cs;
	if (sm > 1)
	{
		cout << "*" << sm;
	}
}

void PhanTich(int n, int x)
{
	stack s(32);
	bool XuatSao = false;
	int a = 2;
	int x, sm, px;
	while (n / a >= a)
	{
		while (n % a == 0)
		{
			s.Push(a);
			n /= a;
			x = x / a;
		}
		a++;
	}
	if (n > 1)
		s.Push(n);
		s.Pop(&x);
	sm = 1;
	while (s.Pop(&x))
	{
		if (x == px)
			sm++;
		else
		{

			Xuat(px, sm, XuatSao);
			XuatSao = true;
			px = x;
			sm = 1;
		}
	}
	Xuat(px, sm, true);
}

void main() {
	int n, x;
	cout << "Nhap n:";
	cin >> n;
	cout << "Nhap x:";
	cin >> x;
	PhanTich(n,x);
}