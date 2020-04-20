#include"List.h"
#include"Stack.h"
#include"Queue.h"
#include"PriQueue.h"
#include"HashMap.h"
int main()
{

	////////////////////////////////////////

	List<int> lst;
	lst.push_back(5);
	lst.push_back(10);
	lst.push_back(22);


	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << lst[i] << endl;
	}

	cout << endl;
	lst.pop_front();
	lst.push_front(0);
	lst.insert(99, 1);
	lst.remove(0);
	lst.pop_back();

	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << lst[i] << endl;
	}

	//lst.clear();

	cout << endl;
	cout << lst.GetSize() << endl;

	//////////////////////////////////////////////

	STACK <int> st1;

	st1.Print();
	st1.push(5);
	st1.push(9);
	st1.push(13);
	st1.push(7);

	st1.Print();

	cout << "Count: " << st1.Count() << endl;

	st1.pop(); // st1 = { }
	st1.pop();
	st1.Print();

	if (st1.IsEmpty())
		cout << "Stack is empty." << endl;
	else
		cout << "Stack is not empty" << endl;

	//////////////////////////////////////////////

	Queue<int> Q1;
	Q1.print("Q1");

	Q1.enqueue(5);
	Q1.print("Q1");

	Q1.enqueue(8);
	Q1.enqueue(11);
	Q1.enqueue(17);
	Q1.print("Q1");

	int d;
	d = Q1.GetItem();
	cout << "d = " << d << endl;

	Q1.print("Q1");

	Q1.dequeue();
	Q1.dequeue();

	Q1.print("Q1");

	//////////////////////////////////////////////

	QueueP<int> Qp1;

	Qp1.Enqueue(15, 7);
	Qp1.Enqueue(18, 9);
	Qp1.Enqueue(1, 3);
	Qp1.Enqueue(8, 6);
	Qp1.Enqueue(11, 6);
	Qp1.Enqueue(4, 6);
	Qp1.Print("Qp1");

	int dp;
	dp = Qp1.Dequeue();
	dp = Qp1.Dequeue();
	dp = Qp1.Dequeue();
	dp = Qp1.Dequeue();
	Qp1.Print("Qp1");
	cout << "dp = " << dp << endl << endl;

	//////////////////////////////////////////////

	HashMap<int, int>* h = new HashMap<int, int>;

	h->insertNode(1, 1);

	h->insertNode(2, 2);

	h->insertNode(2, 3);

	h->display();

	cout << h->sizeofMap() << endl;

	cout << h->deleteNode(2) << endl;

	cout << h->sizeofMap() << endl;

	cout << h->isEmpty() << endl;

	cout << h->get(2);
	

	return 0;
}