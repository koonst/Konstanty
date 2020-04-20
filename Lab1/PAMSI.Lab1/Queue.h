#pragma once
#include <iostream>
#include <new>
using namespace std;


template <typename T>
class Queue
{
private:
    T* p;
    int count;

public:

    Queue()
    {
        count = 0;
    }

    Queue(const Queue& obj)
    {

        count = obj.count;

        try {

            p = new T[count];

            for (int i = 0; i < count; i++)
                p[i] = obj.p[i];
        }
        catch (bad_alloc e)
        {

            cout << e.what() << endl;
            count = 0;
        }
    }

    ~Queue()
    {
        if (count > 0)
            delete[] p;
    }

    Queue& operator=(const Queue& obj)
    {
        T* p2;

        try {
            p2 = new T[obj.count];
            if (count > 0)
                delete[] p;

            p = p2;
            count = obj.count;

            for (int i = 0; i < count; i++)
                p[i] = obj.p[i];
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
        }
        return *this;
    }

    void enqueue(T item)
    {
        T* p2;
        p2 = p;

        try {
            
            p = new T[count + 1];

            for (int i = 0; i < count; i++)
                p[i] = p2[i];

            p[count] = item;

            count++;

            if (count > 1)
                delete[] p2;
        }
        catch (bad_alloc e)
        {

            cout << e.what() << endl;

            p = p2;
        }
    }

    T dequeue()
    {
        if (count == 0)
            return 0;

        T item;

        item = p[0];

        try {
            T* p2;

            p2 = new T[count - 1];

            count--;

            for (int i = 0; i < count; i++)
                p2[i] = p[i + 1];

            if (count > 0)
                delete[] p;

            p = p2;

            return item;
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
            return 0;
        }
    }

    T GetItem()
    {
        if (count > 0)
            return p[0];
        else
            return 0;
    }

    void clear()
    {
        if (count > 0)
        {
            delete[] p;
            count = 0;
        }
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    int GetN()
    {
        return count;
    }

    void print(const char* objName)
    {
        cout << "Object: " << objName << endl;
        for (int i = 0; i < count; i++)
            cout << p[i] << "\t";
        cout << endl;
        cout << "---------------------" << endl;
    }
};