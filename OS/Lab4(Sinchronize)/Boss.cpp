// Boss.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>
using std::cout;
using std::cin;

int main()
{
    HANDLE exit_ev = CreateEvent(NULL, FALSE, FALSE, "Exit");
    int n,m;
    cout << "Input number of Parent processes\n";
    cin >> n;
    cout << "Input number of Child processes\n";
    cin >> m;
    HANDLE sem = CreateSemaphore(NULL, 2, 2, "semaphore");
    HANDLE* proc = new HANDLE[n+m];
    HANDLE events[4];
    HANDLE mut;
    DWORD* id = new DWORD[n+m];
    STARTUPINFO* st = new STARTUPINFO[n + m];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[n + m];
    char p[2];
    for (size_t i = 0; i < 4; i++)
    {
        _itoa(i + 1, p, 10);
        events[i] = (HANDLE)CreateEvent(NULL, FALSE, FALSE,p );
        if (events[i] == NULL) {
            GetLastError();
        }
        
    }
    mut = CreateMutex(NULL, FALSE, "mutex");
    if (mut == NULL) {
        GetLastError();
    }
    for (int i = 0;i < n;i++) {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, (LPSTR)("Parent.exe"), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    for (size_t i = n; i < n + m; i++)
    {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, (LPSTR)("Child.exe"), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    int ind;

    for (int i = 0;i < n;i++) {
        cout << "Input message from 1 to 4\n";
        cin >> ind;
        SetEvent(events[ind - 1]);
    }
    
    char f;
    cout << "Press some button to close all process" << '\n';
    _getch();
    for (int i = 0;i < n+m;i++) {
       
        
        SetEvent(exit_ev);
    }
    _getch();
    delete[]id;
    delete[]st;
    delete[]pi;
    delete[] proc;
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
