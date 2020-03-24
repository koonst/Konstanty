#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

#define sIZE 10 // capacity of the stack

class stack
{
	int* arr;
	int top;      // size
	int capacity; // max capacity

public:
	stack(int size = sIZE); 	// constructor
	~stack();   				// destructor

	void push(int);
	int pop();
	int peek();

	int size();
	bool isEmpty();
	bool isFull();
};
// Constructor
stack::stack(int size)
{
	arr = new int[size];
	capacity = size;
	top = -1;
}

// Destructor
stack::~stack()
{
	delete arr;
}
void stack::push(int x)
{
	if (isFull())
	{
		cout << "OverFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	cout << "Inserting " << x << endl;
	arr[++top] = x;
}

int stack::pop()
{

	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	cout << "Removing " << peek() << endl;


	return arr[top--];
}

// return top element in a stack
int stack::peek()
{
	if (!isEmpty())
		return arr[top];
	else
		exit(EXIT_FAILURE);
}

// size
int stack::size()
{
	return top + 1;
}

// check if the stack is empty or not
bool stack::isEmpty()
{
	return top == -1;	// size() == 0;?
}

// is full or not
bool stack::isFull()
{
	return top == capacity - 1;	// return size() == capacity;?
}