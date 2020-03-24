#include"list.h"
Link::Link()
{
    list = NULL;
}

node* Link::find_before_node(node* p) 
{
    int count = 0;
    int count1 = 0;
    node* temp = new node;
    temp = list;
    while (temp != p) {
        count++;
        temp = temp->next;
    }
    temp = list;
    while (count1 < count - 1) {
        count1++;
        temp = temp->next;
    }
    return temp;
}

void Link::pushFront(int data) 
{
    node* p = new node;
    p->info = data;
    p->next = list;
    list = p;
}

void Link::pushBack(int data) 
{
    node* p = new node;
    node* r = new node;
    node* q = new node;
    r = list;
    p->info = data;
    p->next = NULL;
    if (list == NULL) {
        list = p;
    }
    else {
        while (r->next != NULL) {
            r = r->next;
        }
        r->next = p;
    }
}

void Link::insert_before_node() 
{
    node* p = new node;
    node* l = new node;
    node* r = new node;
    int data1, data2;
    bool isFound = false;
    cout << "Enter the node: ";
    cin >> data1;
    p = list;
    while (p != NULL) {
        if (p->info == data1) {
            isFound = true;
            break;
        }
        l = p;
        p = p->next;
    }
    if (isFound) {
        cout << "Enter the data to insert:";
        cin >> data2;
        r->info = data2;
        if (p == list) {
            pushFront(data2);
        }
        else {
            l->next = r;
            r->next = p;
        }
    }
    else {
        cout << "\nMember not found\n";
    }
}

void Link::remove() 
{
    node* p = new node;
    node* l = new node;
    int data1;
    bool isFound = false;
    p = list;
    cout << "Enter the node: ";
    cin >> data1;
    if (p == NULL) {
        cout << "\nList is Empty" << endl;
        exit(0);
    }
    while (p != NULL)
    {
        if (p->info == data1)
        {
            isFound = true;
            l = p;
            p = p->next;
            break;
        }
        l = p;
        p = p->next;
    }
    if (isFound)
    {
        if (p == list->next)
        {
            list = p;
            delete l;
        }
        else
        {
            find_before_node(l)->next = p;
            delete l;
        }
    }
}

void Link::display() 
{
    node* p = new node;
    p = list;
    if (list == NULL) {
        cout << "\nNothing to Display\n";
    }
    else {
        cout << "\nThe contents of list\n";
        while (p != NULL) {
            cout << p->info << endl;
            p = p->next;
        }
    }
}