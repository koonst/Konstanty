#include"Stack.h"
#include"List.h"
#include"Queue.h"
#include"PriQueue.h"
#include"HashNode.h"
#include"HashKey.h"
#include"HashTab.h"
#include <iostream>
#include <cstdlib>
#include <assert.h>

struct MyKeyHash {
	unsigned long operator()(const int& k) const
	{
		return k % 10;
	}
};

int main()
{
	cout << "stack implementation" << endl << endl;
	stack pt(3);

	pt.push(1);
	pt.push(2);

	pt.pop();
	pt.pop();

	pt.push(3);

	cout << "Top element is: " << pt.peek() << endl;
	cout << "Stack size is " << pt.size() << endl;

	pt.pop();

	if (pt.isEmpty())
		cout << "Stack Is Empty\n";
	else
		cout << "Stack Is Not Empty\n";

	cout << endl;

	system("pause");
	cin.get();

	/////////////////////////////

	
	cout << "list implementation" << endl << endl;
	
	int choice;
	Link link;
	int data;
	do
	 {
		
		cout << "1. Insert at the begining" << endl;
		cout << "2. Insert at the end" << endl;
		cout << "3. Insert node" << endl;
		cout << "4. Delete node" << endl;
		cout << "5. Display" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter the option: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\nEnter data to Insert: ";
			cin >> data;
			link.pushFront(data);
			break;
		case 2:
			cout << "Enter data to Insert: ";
			cin >> data;
			link.pushBack(data);
			break;
		case 3:
			link.insert_before_node();
			break;
		case 4:
			link.remove();
			break;
		case 5:
			link.display();
			break;
		case 6:
			break;
		}
	} while (choice != 6);

	cout << endl;
	
	system("pause");
	cin.get();
	
		////////////////////////////

	cout << "queue implementation" << endl << endl;

	// create a queue of capacity 5
	queue q(5);

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);

	cout << "Front element is: " << q.peek() << endl;
	q.dequeue();

	q.enqueue(4);

	cout << "Queue size is " << q.size() << endl;

	q.dequeue();
	q.dequeue();
	q.dequeue();

	if (q.isEmpty())
		cout << "Queue Is Empty\n";
	else
		cout << "Queue Is Not Empty\n";

	cout << endl;

	system("pause");
	cin.get();

	///////////////////////////////////

	cout << "priority queue implementation" << endl << endl;

	int c, i, p;
	Priority_Queue pq;
	do
	{
	cout << "1.Insert\n";
	cout << "2.Delete\n";
	cout << "3.Display\n";
	cout << "4.Exit\n";
	cout << "Enter your choice : ";
	cin >> c;
	switch (c) {
	case 1:
		cout << "Input the item value to be added in the queue : ";
		cin >> i;
		cout << "Enter its priority : ";
		cin >> p;
		pq.insert(i, p);
		break;
	case 2:
		pq.del();
		break;
	case 3:
		pq.show();
		break;
	case 4:
		break;
	default:
		cout << "Wrong choice\n";
			   }
	}
	while (c != 4);

	cout << endl;

	system("pause");
	cin.get();

	/////////////////////////////////

	cout << "map implementation" << endl << endl;

	HashMap<int, string, 10, MyKeyHash> Tab;
	Tab.put(151, "Konstanty");
	Tab.put(742, "Jakub");
	Tab.put(333, "Veronika");

	string value;
	Tab.get(151, value);////wyszukiwanie elementu z kluczem 151
	cout << "element with key 151: ";
	cout << value << endl;
	bool res = Tab.get(333, value);
	if (res) 
	{
		cout << "element with key 333: ";
		cout << value << endl;
	}
	else
		cout << "no such element" << endl;

		cout << "trwa usuniecie elementu z kluczem 151, nie wylaczaj komputera" << endl;
		
	Tab.remove(151);
	system("pause");
	cin.get();

	res = Tab.get(151, value);
	cout << "surch for element with key 151:" << endl;
	if (res)
		cout << value << endl;
	else
		cout << "no such element" << endl;
	return 0;
}