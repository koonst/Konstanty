#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <map>

using namespace std;

void displayl(list<int> l) ////////dla listy
{
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n";
}

void displays(stack <int> s)////////dla stacku
{
    while (!s.empty())
    {
        cout << '\t' << s.top();
        s.pop();
    }
    cout << '\n';
}

void displaypq(priority_queue <int> pq)////////dla kolejki szpitalowej
{
    priority_queue <int> g = pq;
    while (!g.empty())
    {
        cout << '\t' << g.top();
        g.pop();
    }
    cout << '\n';
}

void displayHT(map <string, int> H)//////////////dla tablicy haszuj¹cej
{
    map <string, int> Sz = H;
    for (map <string, int>::iterator ii = H.begin(); ii != H.end(); ++ii)
    {
        cout << (*ii).first << ": " << ii->second << endl;
    }

}

//////////////////////MAIN//////////////////

int main()

{

    /////Dzia³anie STL listy////////////
    cout << "Dzialanie STL listy:" << endl << endl;

    list<int> lista = { 1, 5, 3, 4, 5 };
    displayl(lista);

    cout << "dzialanie push_back(13) i push_front(77):" << endl;
    lista.push_back(13);
    lista.push_front(77);

    displayl(lista);

    cout << "dzialanie insert('2',33) i remove(5):" << endl;

    list <int> ::iterator it = lista.begin();
    lista.insert(++it, 33);

    displayl(lista);

    lista.remove(5);

    displayl(lista);
    cout << endl;

    /////Dzia³anie STL stacku////////////

    cout << "Dzialanie STL stacku:" << endl << endl;
    cout << "push 5,1,9,10:" << endl;

    stack <int> stacka;

    stacka.push(5);
    displays(stacka);
    stacka.push(1);
    displays(stacka);
    stacka.push(9);
    displays(stacka);
    stacka.push(10);
    displays(stacka);

    cout << "pop (2 razy):" << endl;
    stacka.pop();
    stacka.pop();
    displays(stacka);
    cout << endl;

    /////Dzia³anie STL kolejki////////////

    cout << "Dzialanie STL kolejki:" << endl << endl;
    queue <int> q;

    cout << "Wprowadz 3 liczby: " << endl;

    for (int h = 0; h < 3; h++) {
        int a;

        cin >> a;

        q.push(a);
    }

    cout << endl;
    cout << "pierwszy element kolejki: " << q.front() << endl;

    q.pop();

    cout << "nowy pierwszy element po usunieciu: " << q.front() << endl << endl;

    /////Dzia³anie STL kolejki szpitalowej////////////

    priority_queue <int> prioq;
    prioq.push(10);
    prioq.push(30);
    prioq.push(20);
    prioq.push(5);
    prioq.push(1);

    cout << "kolejka priorytetowa: " << endl;
    displaypq(prioq);

    cout << "\nprioq.size() : " << prioq.size();//rozmiar
    cout << "\nprioq.top() : " << prioq.top();//pierwszy element


    cout << "\nprioq.pop() : ";
    prioq.pop();
    displaypq(prioq);
    cout << endl;
    system("pause");
    cin.get();

    /////Dzia³anie STL tabelki z haszowaniem////////////

    cout << "Dzialanie STL tablicy haszujacej:" << endl << endl;

    map <string, int> Htab;

    Htab["Konstanty"] = 5234;
    Htab["Jakub"] = 3374;

    cout << "tablica haszujaca:" << endl;
    displayHT(Htab);

    Htab.insert(std::pair<string, int>("Viktor", 1923));
    Htab.insert(std::pair<string, int>("Maria", 5328));

    cout << "tablica haszujaca po wrzuceniu Viktora z kluczem 1923 i Marii z kluczem 5328:" << endl;
    displayHT(Htab);

    cout << "klucz do zmiennej Viktor:" << endl;
    map<string, int>::iterator iter = Htab.find("Viktor");
    cout << iter->second << endl;

    cout << "usuniecie elementu Viktor:" << endl;
    Htab.erase(iter);
    displayHT(Htab);
    cout << "usuniecie elementu Konstanty:" << endl;
    map<string, int>::iterator niter = Htab.find("Konstanty");
    Htab.erase(niter);
    displayHT(Htab);

    return 0;
}