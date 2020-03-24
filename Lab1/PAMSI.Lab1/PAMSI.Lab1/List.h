#pragma once
#include<cstdlib>
#include <iostream>
using namespace std;

struct node 
{
    int info;
    struct node* next;
};

class Link {
    node* list;
public:
    Link();
    void pushFront(int);
    void pushBack(int);
    void insert_before_node();
    void remove(); 
    node* find_before_node(node*);
    void display();
};