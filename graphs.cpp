#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

class msasiedztwa
{
private:
    int **macierz, *visited, msize = 0, hasLoop = 0;
    stack<int> sorted;
    queue<int> list;
    void createMatrix(int size)
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
        int pos = positon;
        if (visited[positon] == -1)
        {
            hasLoop = 1;
        }
        else if (visited[positon] == 0)
        {
            visited[positon] = -1;
            for (int n = 0; n < msize; n++)
            {
                if (macierz[n][positon] == 1)
                {
                    if (visited[n] != 1)
                    {
                        pos = findFirstDEL(n);
                        break;
                    }
                }
            }
            visited[positon] = 0;
        }
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
    ~msasiedztwa()
    {
        for (int n = 0; n < msize; n++)
        {
            delete[] macierz[n];
        }
        delete[] macierz;
        delete[] visited;
    };
    void loadFromFile(string name = "input.txt")
    {
        ifstream file(name);
        if (file.is_open())
        {
            int a, b, validate;
            file >> a >> validate;
            createMatrix(a);
            while (file >> a >> b)
            {
                a--;
                b--;
                macierz[a][b] = 1;
                macierz[b][a] = -1;
                validate--;
            }
            if (validate != 0)
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
        createMatrix(size);
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
    void DFSmsasiedztwa(int print = 0)
    {
        stack<int> empty;
        swap(sorted, empty);
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
        if (print)
        {
            printDFS();
        }
    }
    void DELmsasiedztwa(int print = 0)
    {
        queue<int> empty;
        swap(list, empty);
        int n = 0;
        do
        {
            if (visited[n] == 0)
            {
                int pos = findFirstDEL(n);
                visited[pos] = 1;
                list.push(pos + 1);
            }
            else
            {
                n++;
            }
        } while (list.size() != msize && !hasLoop);
        if (print)
        {
            printDEL();
        }
    }
};

struct funnySorting
{
    bool operator()(int l, int r)
    {
        return l > r;
    }
} funnySorting;

class mgrafu
{
private:
    int **macierz, *visited, msize, hasLoop;
    vector<int> *ni, *pi, *bi;
    stack<int> sorted;
    queue<int> list;
    void createMatrix(int size)
    {
        msize = size;
        hasLoop = 0;
        macierz = new int *[size];
        visited = new int[size];
        ni = new vector<int>[size];
        pi = new vector<int>[size];
        bi = new vector<int>[size];
        for (int n = 0; n < size; n++)
        {
            macierz[n] = new int[size + 3];
            for (int m = 0; m < size; m++)
            {
                macierz[n][m] = 0;
                bi[n].push_back(m);
            }
            macierz[n][size] = 0;
            macierz[n][size + 1] = 0;
            macierz[n][size + 2] = 0;
            visited[n] = 0;
        }
    }
    void buildMatrix()
    {
        for (int n = 0; n < msize; n++)
        {
            sort(ni[n].begin(), ni[n].end(), funnySorting);
            sort(pi[n].begin(), pi[n].end(), funnySorting);
            sort(bi[n].begin(), bi[n].end(), funnySorting);
            int pos;
            while (!ni[n].empty())
            {
                if (macierz[n][msize] == 0)
                {
                    pos = ni[n].back();
                    macierz[n][msize] = pos + 1;
                }
                else
                {
                    macierz[n][pos] = ni[n].back() + 1;
                    pos = ni[n].back();
                }
                macierz[n][pos] = pos + 1;
                ni[n].pop_back();
            }
            while (!pi[n].empty())
            {
                if (macierz[n][msize + 1] == 0)
                {
                    pos = pi[n].back();
                    macierz[n][msize + 1] = pos + 1;
                }
                else
                {
                    macierz[n][pos] = pi[n].back() + 1 + msize;
                    pos = pi[n].back();
                }
                macierz[n][pos] = pos + 1 + msize;
                pi[n].pop_back();
            }
            while (!bi[n].empty())
            {
                if (macierz[n][msize + 2] == 0)
                {
                    pos = bi[n].back();
                    macierz[n][msize + 2] = pos + 1;
                }
                else
                {
                    macierz[n][pos] = -(bi[n].back() + 1);
                    pos = bi[n].back();
                }
                macierz[n][pos] = -(pos + 1);
                bi[n].pop_back();
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

            int pos = macierz[position][msize];
            if (pos != 0)
            {
                while (true)
                {
                    visitDFS(pos - 1);
                    if (macierz[position][pos - 1] == pos)
                    {
                        break;
                    }
                    pos = macierz[position][pos - 1];
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
    int findFirstDEL(int position)
    {
        int pos = position;
        if (visited[position] == -1)
        {
            hasLoop = 1;
        }
        else if (visited[position] == 0)
        {
            visited[position] = -1;
            int point = macierz[position][msize + 1];
            if (point != 0)
            {
                while (true)
                {
                    if (visited[point - 1] != 1)
                    {
                        pos = findFirstDEL(point - 1);
                        break;
                    }
                    if (macierz[position][point - 1] - msize == point)
                    {
                        break;
                    }
                    point = macierz[position][point - 1] - msize;
                }
            }
            visited[position] = 0;
        }
        return pos;
    }

public:
    mgrafu(){};
    ~mgrafu()
    {
        for (int n = 0; n < msize; n++)
        {
            delete[] macierz[n];
        }
        delete[] macierz;
        delete[] visited;
        delete[] ni;
        delete[] pi;
        delete[] bi;
    };
    void loadFromFile(string name = "input.txt")
    {
        ifstream file(name);

        if (file.is_open())
        {
            int a, b, validate;
            file >> a >> validate;
            createMatrix(a);
            while (file >> a >> b)
            {
                a--;
                b--;
                ni[a].push_back(b);
                pi[b].push_back(a);
                bi[a].erase(remove(bi[a].begin(), bi[a].end(), b), bi[a].end());
                bi[b].erase(remove(bi[b].begin(), bi[b].end(), a), bi[b].end());
                validate--;
            }
            buildMatrix();
            if (validate != 0)
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
        createMatrix(size);
        for (int n = 0; n < size; n++)
        {
            for (int m = n + 2; m <= size; m++)
            {
                ni[n].push_back(m - 1);
                pi[m - 1].push_back(n);
                bi[n].erase(remove(bi[n].begin(), bi[n].end(), m - 1), bi[n].end());
                bi[m - 1].erase(remove(bi[m - 1].begin(), bi[m - 1].end(), n), bi[m - 1].end());
            }
        }
        buildMatrix();
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
            cout << setw(5) << n;
        }
        cout << endl;
        for (int n = 0; n < msize; n++)
        {
            cout << setw(5) << n + 1;
            for (int m = 0; m < msize + 3; m++)
            {
                cout << setw(5) << macierz[n][m];
            }
            cout << endl;
        }
    }
    void DFSmgrafu(int print = 0)
    {
        stack<int> empty;
        swap(sorted, empty);
        int n = 0;
        do
        {
            if (print)
            {
                cout << "yay" << n << endl;
            }
            if (visited[n] == 0)
            {
                visitDFS(n);
            }
            else
            {
                n++;
            }
        } while (sorted.size() != msize && !hasLoop);
        // for (int n = 0; n < msize; n++)
        // {
        // }
        // if (!hasLoop)
        // {
        //     for (int n = 0; n < msize; n++)
        //     {
        //         if (visited[n] == 0)
        //         {
        //             hasLoop = 1;
        //             break;
        //         }
        //     }
        // }
        if (print)
        {
            printDFS();
        }
    }
    void DELmgrafu(int print = 0)
    {
        queue<int> empty;
        swap(list, empty);
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
        if (print)
        {
            printDEL();
        }
    }
};
void testSpeed()
{
    msasiedztwa m;
    cout << "macierz sasiedztwa" << endl
         << "DFS: ";
    for (int n = 100; n <= 1500; n += 100)
    {
        m.generateMatrix(n);
        auto start = chrono::high_resolution_clock::now();
        m.DFSmsasiedztwa();
        auto duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start);
        cout << "(" << n << "," << duration.count() << ")";
    }
    cout << endl
         << "DEL: ";
    for (int n = 100; n <= 1500; n += 100)
    {
        m.generateMatrix(n);
        auto start = chrono::high_resolution_clock::now();
        m.DELmsasiedztwa();
        auto duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start);
        cout << "(" << n << "," << duration.count() << ")";
    }

    mgrafu mg;
    cout << endl;
    cout << "macierz grafu" << endl
         << "DFS: ";
    for (int n = 100; n <= 1500; n += 100)
    {
        mg.generateMatrix(n);
        auto start = chrono::high_resolution_clock::now();
        mg.DFSmgrafu();
        auto duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start);
        cout << "(" << n << "," << duration.count() << ")";
    }
    cout << endl
         << "DEL: ";
    for (int n = 100; n <= 1500; n += 100)
    {
        mg.generateMatrix(n);
        auto start = chrono::high_resolution_clock::now();
        mg.DELmgrafu();
        auto duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start);
        cout << "(" << n << "," << duration.count() << ")";
    }
    cout << endl;
}
int main()
{
    // testSpeed();
    mgrafu m;
    m.loadFromFile("wyklad.txt");
    m.print();
    m.DELmgrafu(1);
    return 0;
}