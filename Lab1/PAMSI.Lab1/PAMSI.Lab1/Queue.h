#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

// define default capacity of the queue
#define SIZE 10

// Class for queue
class queue
{
	int* arr;		// array to store queue elements
	int capacity;	// max capacity
	int front;		// front element in the queue
	int rear;		// last element in the queue
	int count;		// size of the queue

public:
	queue(int size = SIZE); 	// constructor
	~queue();   				// destructor

	void dequeue();
	void enqueue(int x);
	int peek();
	int size();
	bool isEmpty();
	bool isFull();
};