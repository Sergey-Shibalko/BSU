﻿// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

int main()
{
    //cout << "Hello World!\n";
    HANDLE write, read;
    HANDLE end = CreateEvent(NULL, FALSE, FALSE, "end");
    if (end == NULL) {
        GetLastError();
    }
    int n;
    cout << "Enter array size \n";

    cin >> n;
    char* arr=new char[n];
    cout << "\nEnter array elements \n";
    for (size_t i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << '\n';
    for (size_t i = 0; i < n; i++)
    {
        cout<< arr[i];
    }
    cout << "\n";
    HANDLE event = CreateEvent(NULL, FALSE, FALSE, "1");
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL; // защита по умолчанию
    sa.bInheritHandle = TRUE;
    CreatePipe(&read, &write, &sa, 0);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    char a[80];
    wsprintf(a, "Consume.exe %d %d %d", int(write), int(read),n);

    if (!CreateProcess(NULL, a, NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        GetLastError();
    }
   // WriteFile()
    /*CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread)*/;
    for (size_t i = 0; i < n; i++)
    {
        DWORD size;
        WriteFile(write, &arr[i], sizeof(arr[i]), &size, NULL);
    }
   SetEvent(event);
   //HANDLE end = OpenEvent(SYNCHRONIZE, FALSE, "end");
   
   //Sleep(500);
   WaitForSingleObject(end, INFINITE);
   int m;
   DWORD sz;
   ReadFile(read, &m, sizeof(m), &sz, NULL);
   char* h = new char[m];
   for (int i = 0;i < m;i++) {
       DWORD size;
       ReadFile(read, &h[i], sizeof(h[i]), &size, NULL);
   }
   for (int i = 0;i < m;i++) {
       cout << h[i];
   }
   
   
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
