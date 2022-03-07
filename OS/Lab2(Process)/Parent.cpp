// Parent.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<conio.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    _CrtSetDebugFillThreshold(0);
    char lpszAppName[] = "C:\\Users\\acer\\source\\repos\\Osi_lab2\\Debug\\Child.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    //si.dwFillAttribute = BACKGROUND_RED;
    si.dwFlags = STARTF_USESIZE| STARTF_USEFILLATTRIBUTE;
    si.lpTitle =(LPSTR) "Sergey Shibalko";
    si.dwYSize = 1000;
    si.dwFillAttribute = FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    string str="";
    int t;
    string tmp="";
    int n;
    cin >> n;
    for (int i = 0;i < n;i++) {
        cin >> tmp;
        //_itoa(t, &tmp,10);
        str +=tmp;
        str += " ";
    }
    cout << str;
    str.length();
    char* h=new char[str.length()];
    for (int i = 0;i < str.length()-1;i++) {
        h[i] = str[i];
    }

    if (!CreateProcess(lpszAppName, h, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        _cputs("Invalid process");
       // _getch();
        return 0;
    }
    
    _cputs("Process created");
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    //delete str;
    //_getch();
    //delete &str;
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
