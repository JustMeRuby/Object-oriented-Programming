#pragma once
typedef int Item;
class stack
{
	Item* st, * top;
	int size;
	void Init(int sz) { st = top= new Item[size = sz]; }
	void CleanUp() { if (st)delete[]st; }
public:
	stack(int sz = 20) { Init(20); }
	~stack() { CleanUp(); }
	bool isEmpty()const { return top <= st; }
	bool isFull()const { return top - st >= size; }
	bool Push(Item x);
	bool Pop(Item* px);
};
