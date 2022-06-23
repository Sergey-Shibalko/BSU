// Consume.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include<conio.h>
#include <set>
using std::cout;
using std::cin;

int main(int argc, char* argv[])
{
    HANDLE end = OpenEvent(EVENT_ALL_ACCESS, FALSE, "end");
    HANDLE write = (HANDLE)atoi(argv[1]);
    HANDLE read= (HANDLE)atoi(argv[2]);
    HANDLE event = OpenEvent(SYNCHRONIZE, FALSE, "1");
    if (event == NULL) {
        GetLastError();
    }
    WaitForSingleObject(event, INFINITE);
    cout << "Enter b<n\n";
    int b = 0;
    cin >> b;
    int n = atoi(argv[3]);
    while (b >= n) {
        cin >> b;
    }
    int* del = new int[b];
    for (int i = 0;i < b;i++) {
        del[i] = rand() % n;
        cout << del[i];
    }
    cout << "\n";
    
    char* a = new char[n];
    
    //ReadFile(read, a, sizeof(a), &s, 0);
    for (int i = 0;i < atoi(argv[3]);i++) {
        DWORD s;
        ReadFile(read, &a[i], sizeof(a[i]), &s, NULL);
    }
    for (int i = 0;i < atoi(argv[3]);i++) {
        cout << a[i];
    }
    cout << '\n';
    
    DWORD sz;
    int ind = n-b;
    WriteFile(write, &b, sizeof(b), &sz, NULL);
    
    for (size_t i = 0; i < b; i++)
    {
        DWORD r;
       
            WriteFile(write, &a[del[i]], sizeof(a[i]), &r, NULL);
        
    }
    SetEvent(end);
    char ex;
    cout << "Exit - press Q";
    cin>> ex;
    while (ex != 'Q') {
        cin >> ex;
    }
    delete[]a;
    //cin >> b;
    
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
