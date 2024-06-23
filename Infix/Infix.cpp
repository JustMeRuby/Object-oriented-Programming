#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

template<class T>
class Node
{
	T data;
	Node* next;
	Node* prev;
public:
	Node() { next = NULL, prev = NULL; }
	~Node() {}
	void setData(T d) { data = d; }
	T getData() { return data; }
	void linkNext(Node* n) { next = n; }
	void linkPrev(Node* n) { prev = n; }
	Node* getNext() { return next; }
	Node* getPrev() { return prev; }
};

template<class T>
class Stack
{
	int size;
	Node<T>* head;
	Node<T>* tail;
public:
	Stack() { size = 0, head = NULL, tail = NULL; }
	~Stack() { clear(); }
	void push(T d)
	{
		Node<T>* new_node = new Node<T>;
		new_node->setData(d);
		if (isEmpty())
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->linkNext(new_node);
			new_node->linkPrev(tail);
			tail = new_node;
		}
		size++;
	}
	void pop()
	{
		if (isEmpty()) { return; }
		else if (size == 1)
		{
			delete head;
			head = NULL;
			tail = NULL;
		}
		else
		{
			tail = tail->getPrev();
			delete tail->getNext();
			tail->linkNext(NULL);
		}
		size--;
	}
	T top()
	{
		if (isEmpty()) { return 0; }
		return tail->getData();
	}
	void clear()
	{
		while (!isEmpty()) { pop(); }
	}
	bool isEmpty() { return (size == 0); }
};

const int numOps = 6;
string Ops[numOps] = { "+", "-", "*", "/", "^", "%" };

const int numFuncs = 7;
string Funcs[numFuncs] = { "sin", "cos", "tan", "log", "ln", "sqrt", "exp" };

bool isOp(string Word)
{
	int i;
	for (i = 0; i < numOps; i++)
	{
		if (Word == Ops[i]) return true;	
	}
	return false;
}

bool isFunc(string Word)
{
	int i;
	for (i = 0; i < numFuncs; i++)
	{
		if (Word == Funcs[i]) return true;	
	}
	return false;
}

bool isNum(string Word)
{
	bool decimal = true;
	bool negative = true;
	int i;
	for (i = 0; i < Word.length(); i++)
	{
		if (!isdigit(Word[i]))
		{
			if (Word[i] == '.' && decimal == true) decimal = false;
			else if (Word[i] == '-' && negative == true) negative = false;
			else return false;
		}
	}
	return true;
}

bool isLeftAssociative(string Word)
{
	if (Word == "+" || Word == "-" || Word == "*" || Word == "/" || Word == "%") return true;
	return false;
}

double CalculateOp(double num1, double num2, string op)
{
	if (op == "+") return num1 + num2;
	if (op == "-") return num1 - num2;
	if (op == "*") return num1 * num2;
	if (op == "/") return num1 / num2;
	if (op == "^") return pow(num1, num2);
	if (op == "%") return (int)num1 % (int)num2;
	return 0;
}

double CalculateFunc(double num, string func)
{
	if (func == "sin") return sin(num);
	if (func == "cos") return cos(num);
	if (func == "tan") return tan(num);
	if (func == "log") return log10(num);
	if (func == "ln") return log(num);
	if (func == "exp") return exp(num);
	if (func == "sqrt") return sqrt(num);
	return 0;
}

int Priority(string op)
{
	if (op == "+" || op == "=") return 1;
	if (op == "*" || op == "/" || op == "%") return 2;
	if (op == "^") return 3;
	if (isFunc(op)) return 4;
	return 0;
}

double Calculate(string iE)
{
	Stack<string> opStack;
	Stack<double> numStack;
	int countOpen = 0, countClose = 0;
	string Word;
	stringstream ss(iE);
	while (ss >> Word)
	{
		if (Word == "(")
		{
			opStack.push(Word);
			countOpen++;
		}
		else if (isFunc(Word)) { opStack.push(Word); }
		else if (isNum(Word)) { numStack.push(stod(Word)); }
		else if (Word == ")")
		{
			countClose++;
			while (!opStack.isEmpty() && opStack.top() != "(")
			{
				double num2 = numStack.top();
				numStack.pop();
				double num1 = numStack.top();
				numStack.pop();
				numStack.push(CalculateOp(num1, num2, opStack.top()));
				opStack.pop();
			}
			opStack.pop();
			if (!opStack.isEmpty())
			{
				if (isFunc(opStack.top()))
				{
					double num = numStack.top();
					numStack.pop();
					numStack.push(CalculateFunc(num, opStack.top()));
					opStack.pop();
				}
			}
		}
		else if (isOp(Word))
		{
			while ((!opStack.isEmpty() && opStack.top() != "(") &&
				((Priority(opStack.top()) > Priority(Word)) ||
				(Priority(opStack.top()) == Priority(Word) && isLeftAssociative(Word))))
			{
				double num2 = numStack.top();
				numStack.pop();
				double num1 = numStack.top();
				numStack.pop();
				numStack.push(CalculateOp(num1, num2, opStack.top()));
				opStack.pop();
			}
			opStack.push(Word);
		}
	}
	if (numStack.isEmpty()) { cout << "Wrong input! No number found in Expression" << '\n'; }
	if (countOpen != countClose)
	{
		if (countOpen < countClose) { cout << "Wrong input! Missing (" << '\n'; }
		else { cout << "Wrong input! Missing )" << '\n'; }
	}
	while (!opStack.isEmpty())
	{
		if (isOp(opStack.top()))
		{
			double num2 = numStack.top();
			numStack.pop();
			double num1 = numStack.top();
			numStack.pop();
			numStack.push(CalculateOp(num1, num2, opStack.top()));
			opStack.pop();
		}
		else if (isFunc(opStack.top()))
		{
			double num = numStack.top();
			numStack.pop();
			numStack.push(CalculateFunc(num, opStack.top()));
			opStack.pop();
		}
		else if (opStack.top() == "(")
		{
			return 0;
		}
	}
	return numStack.top();
}

int main()
{
	string iE;
	cout << "Enter infix Expression: ";
	getline(cin, iE);
	cout << "The result is: " << Calculate(iE) << '\n';
	return 0;
}