// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
#include <set>
using namespace std;

int main()
{
    //cout << "Hello World!\n";
    HANDLE hNamedPipe;
    hNamedPipe = CreateFile(
        "\\\\.\\pipe\\demo_pipe", // имя канала
        GENERIC_READ | GENERIC_WRITE, // читаем и записываем в канал
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        (LPSECURITY_ATTRIBUTES)NULL, // защита по умолчанию
        OPEN_EXISTING, // открываем существующий канал
        0, // атрибуты по умолчанию
        (HANDLE)NULL // дополнительных атрибутов нет
    );
    int n;
    DWORD sz;
    ReadFile(hNamedPipe, &n, sizeof(n), &sz, (LPOVERLAPPED)NULL);
    char* arr = new char[n];
    ReadFile(hNamedPipe, arr, n, &sz, (LPOVERLAPPED)NULL);
    for (size_t i = 0; i < n; i++)
    {
        cout << arr[i];
    }
    cout << "\nEnter m<n\n";
    int b = 0;
    cin >> b;
    while (b >= n) {
        cin >> b;
    }
    //int* del = new int[b];
    cout << "Delete indexes\n";
    set<int> d;
    for (int i = 0;i < b;i++) {
        int tmp = rand() % n;
        d.insert(tmp);
        cout << tmp<<" ";
    }
    int m = n - d.size();
    char* res = new char[m];
    cout << "\n";
    int ind = 0;
    for (int i = 0;i < n;i++) {
        if (d.find(i) == d.end()) {
            res[ind] = arr[i];
            cout << res[ind];
            ind++;

        }
    }
    WriteFile(hNamedPipe, &m, sizeof(m), &sz, (LPOVERLAPPED)NULL);
    WriteFile(hNamedPipe, res, m, &sz, (LPOVERLAPPED)NULL);
    char r;
    cin >> r;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
