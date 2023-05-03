#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
class msasiedztwa
{
private:
    int **macierz;
    int size = 0;

public:
    msasiedztwa(){};
    msasiedztwa(int rozmiar)
    {
        createMatirx(rozmiar);
    }
    void createMatirx(int rozmiar)
    {
        size = rozmiar;
        macierz = new int *[rozmiar];
        for (int n = 0; n < rozmiar; n++)
        {
            macierz[n] = new int[rozmiar];
            for (int m = 0; m < rozmiar; m++)
            {
                macierz[n][m] = 0;
            }
        }
    }
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
                cout << "[WARN] Data might be corrupted!" << endl;
            }
        }
        else
        {
            cout << "[ERR] File not found." << endl;
        }
    }
    void print()
    {
        if (!size)
        {
            cout << "[WARN] Create matrix first, use createMatrix(size) or loadFromFile(name)." << endl;
            return;
        }
        cout << setw(3) << "";
        for (int n = 1; n <= size; n++)
        {
            cout << setw(3) << n;
        }
        cout << endl;
        for (int n = 0; n < size; n++)
        {
            cout << setw(3) << n + 1;
            for (int m = 0; m < size; m++)
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
    msasiedztwa m;
    cout << "owo" << endl;
    m.loadFromFile();
    cout << "owo" << endl;
    m.print();

    return 0;
}