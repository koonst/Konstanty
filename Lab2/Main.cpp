#include "Intro_Sort.h"
#include "Merge_Sort.h"
#include "Quick_Sort.h"
#include <chrono>
#include <iostream>

#define DataType int

#include <chrono> 

class Timer
{
private:

    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

template<typename T>
using SortFncPoint = void (*)(T*, T*, int, int, int);


template<typename T>
void print_table(T* tab, int n)
{
    for (int i = 0; i < n; i++) std::cout << tab[i] << " ";
}


template<typename T>
T* create_table(int n)
{
    return new T[n];
}


template<typename T>
void kill_table(T* table)
{
    delete[] table;
}

template<typename T>
void fill_random(T* tab, int n)
{
    for (int i = 0; i < n; i++) tab[i] = rand() % 100000 + 1;
}

template<typename T>
void sort_percent(T* tab, int n, double percent)
{
    if (percent == 100) //then sorts whole table in reverse order
    {
        std::sort(tab, tab + n, std::greater<T>());
        return;
    }
    std::sort(tab, tab + (int)((n * percent) / 100));
}


template<typename T>
void check_if_sorted(T* tab, int n)
{
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (tab[i] > tab[i + 1])
            {
                std::cout << "Table not sorted!";
                std::cin.get();
                exit(1);
            }
        }
    }
}

template<typename T>
void check_if_sorted_rewerse(T* tab, int n)
{
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (tab[i] < tab[i + 1])
            {
                std::cout << "Table not sorted!";
                std::cin.get();
                exit(1);
            }
        }
    }
}

int main()
{
    
    int ntab[5] = { 10000, 50000, 100000, 500000, 1000000 };
    double percenttab[7] = {25, 50, 75, 95, 99, 99.7, 100};

    SortFncPoint<DataType> mpoint = &mergeWrap, qpoint = &quickWrap, ipoint = &introWrap;
    SortFncPoint<DataType> ptable[3] = { qpoint, mpoint, ipoint };

    int iter = 0;
    std::string sorts[3] = { "QUCIK_SORT", "MERGE_SORT", "INTRO_SORT" };

    for (SortFncPoint<DataType> fp : ptable)
    {
        std::cout <<std::endl << sorts[iter++] << std::endl << std::endl;
        for (double percent : percenttab)
        {
            for (int n : ntab)
            {
                DataType* tab = create_table<DataType>(n);
                DataType* tmp = create_table<DataType>(n);

                {
                    fill_random<DataType>(tab, n);

                    Timer t;
                    sort_percent<DataType>(tab, n, percent);
                    std::cout << "time: " << t.elapsed() << std::endl;

                    if(percent!=100)
                    check_if_sorted<DataType>(tab, n*percent/100);
                    else
                    check_if_sorted_rewerse<DataType>(tab, n * percent / 100);
                }
                kill_table<DataType>(tab);
                kill_table<DataType>(tmp);

                std::cout << n << " table sorted!" << std::endl;
            }
            std::cout <<std::endl << percent << " % done!" << std::endl << std::endl;
        }
    }
    std::cout << "END OF SORTING!";
    std::cin.get();
    

    return 0;
}

