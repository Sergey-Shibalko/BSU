
#include <iostream>
#include<Windows.h>
#include <set>
using std::cout;
using std::cin;
void print(char* arr, int n) {
    for (size_t i = 0; i < n; i++)
    {
        cout << arr[i];
    }

    cout << "\n";
}
int main()
{
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
    print(arr, n);
    cout << "\nEnter m<n\n";
    int b = 0;
    cin >> b;
    while (b >= n) {
        cin >> b;
    }
    cout << "Delete indexes\n";
    std::set<int> d;
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
            ind++;

        }
    }
    print(res, n);
    WriteFile(hNamedPipe, &m, sizeof(m), &sz, (LPOVERLAPPED)NULL);
    WriteFile(hNamedPipe, res, m, &sz, (LPOVERLAPPED)NULL);
    char r;
    cin >> r;
    CloseHandle(hNamedPipe);
    delete[]res;
    delete[]arr;
}

