#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class msasiedztwa
{
private:
    int **macierz, *visited, msize = 0, hasLoop = 0;
    stack<int> sorted;
    queue<int> list;
    void createMatirx(int size)
    {
        msize = size;
        hasLoop = 0;
        macierz = new int *[size];
        visited = new int[size];
        for (int n = 0; n < size; n++)
        {
            macierz[n] = new int[size];
            visited[n] = 0;
            for (int m = 0; m < size; m++)
            {
                macierz[n][m] = 0;
            }
        }
    }
    void visitDFS(int position)
    {
        // 0 not visited, -1 visited but not noted, 1 visited and noted
        if (visited[position] == -1)
        {
            hasLoop = 1;
        }
        else if (visited[position] == 0)
        {
            visited[position] = -1;
            for (int n = 0; n < msize; n++)
            {
                if (macierz[position][n] == 1)
                {
                    visitDFS(n);
                }
            }
            sorted.push(position + 1);
            visited[position] = 1;
        }
    }
    void printDFS()
    {
        if (hasLoop)
        {
            cout << "Graf zawiera cykl. Sortowanie niemożliwe." << endl;
            return;
        }
        cout << "Sorted: ";
        while (!sorted.empty())
        {
            cout << setw(4) << sorted.top();
            sorted.pop();
        }
        cout << endl;
    }
    int findFirstDEL(int positon)
    {
        if (visited[positon] == -1)
        {
            hasLoop = 1;
            return -1;
        }
        int pos = positon;
        visited[positon] = -1;
        for (int n = 0; n < msize; n++)
        {
            if (macierz[n][positon] == 1)
            {
                if (!visited[n])
                {
                    pos = findFirstDEL(n);
                }
            }
        }
        visited[positon] = 0;
        return pos;
    }
    void printDEL()
    {
        if (hasLoop)
        {
            cout << "Graf zawiera cykl. Sortowanie niemożliwe." << endl;
            return;
        }
        cout << "Sorted: ";
        while (!list.empty())
        {
            cout << setw(4) << list.front();
            list.pop();
        }
        cout << endl;
    }

public:
    msasiedztwa(){};
    void loadFromFile(string name = "input.txt")
    {
        ifstream file(name);
        if (file.is_open())
        {
            int a, b, validate;
            file >> a >> validate;
            createMatirx(a);
            while (file >> a >> b)
            {
                macierz[--a][--b] = 1;
                validate--;
            }
            if (validate)
            {
                cout << "[WARN] Incorrect graph." << endl;
            }
        }
        else
        {
            cout << "[ERR] File not found." << endl;
        }
    }
    void generateMatrix(int size)
    {
        createMatirx(size);
        for (int n = 1; n < size; n++)
        {
            for (int m = n - 1; m >= 0; m--)
            {
                macierz[n][m] = 1;
            }
        }
    }
    void print()
    {
        if (!msize)
        {
            cout << "[WARN] Create matrix first, use generateMatrix(size) or loadFromFile(name)." << endl;
            return;
        }
        cout << setw(3) << "";
        for (int n = 1; n <= msize; n++)
        {
            cout << setw(3) << n;
        }
        cout << endl;
        for (int n = 0; n < msize; n++)
        {
            cout << setw(3) << n + 1;
            for (int m = 0; m < msize; m++)
            {
                cout << setw(3) << macierz[n][m];
            }
            cout << endl;
        }
    }
    void DFSmsasiedztwa()
    {
        int n = 0;
        do
        {
            if (visited[n] == 0)
            {
                visitDFS(n);
            }
            else
            {
                n++;
            }
        } while (sorted.size() != msize && !hasLoop);
        printDFS();
    }
    void DELmsasiedztwa()
    {
        int n = 0;
        do
        {
            if (visited[n] == 0)
            {
                int pos = findFirstDEL(n);
                list.push(pos + 1);
                visited[pos] = 1;
            }
            else
            {
                n++;
            }
        } while (list.size() != msize && !hasLoop);
        printDEL();
    }
};

class mgrafu
{
private:
    int **macierz, msize = 0;
    queue<int> *lists;
    void createMatirx(int size)
    {
        msize = size;
        macierz = new int *[size];
        lists = new queue<int>[size];
        for (int n = 0; n < size; n++)
        {
            macierz[n] = new int[size + 3];
            for (int m = 0; m < size; m++)
            {
                macierz[n][m] = 0;
            }
        }
    }

public:
    mgrafu(){};
    void loadFromFile(string name = "input.txt")
    {
        ifstream file(name);
        if (file.is_open())
        {
            int a, b, validate;
            file >> a >> validate;
            createMatirx(a);
            while (file >> a >> b)
            {
                // todo
                validate--;
            }
            if (validate)
            {
                cout << "[WARN] Incorrect graph." << endl;
            }
        }
        else
        {
            cout << "[ERR] File not found." << endl;
        }
    }
    void generateMatrix(int size)
    {
        createMatirx(size);
    }
    void print()
    {
        if (!msize)
        {
            cout << "[WARN] Create matrix first, use generateMatrix(size) or loadFromFile(name)." << endl;
            return;
        }
        cout << setw(3) << "";
        for (int n = 1; n <= msize + 3; n++)
        {
            cout << setw(3) << n;
        }
        cout << endl;
        for (int n = 0; n < msize; n++)
        {
            cout << setw(3) << n + 1;
            for (int m = 0; m < msize + 3; m++)
            {
                cout << setw(3) << macierz[n][m];
            }
            cout << endl;
        }
    }
};
int main()
{
    cout << "owo" << endl;
    mgrafu m;
    m.generateMatrix(4);
    cout << "owo" << endl;
    m.print();
    return 0;
}