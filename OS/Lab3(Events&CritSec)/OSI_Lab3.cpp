// OSI_Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
#include"Array.h"
using std::cout;
using std::cin;
HANDLE workEvent, sumEvent;
CRITICAL_SECTION cs;

DWORD WINAPI work(array* a) {
    DWORD timeForSleep;
    cout << "Input sleep time\n";
    cin >> timeForSleep;
    int l = 0;
    for (size_t i = 0; i < a->size; i++)
    {
        if ((33 <= (int)a->array[i] && (int)a->array[i] <= 47) || 
            (58 <= (int)a->array[i] && (int)a->array[i] <= 64) || 
            (91 <= (int)a->array[i] && (int)a->array[i] <= 96) || 
            (123 <= (int)a->array[i] && (int)a->array[i] <= 127)) {
            if (l != i) {
                a->array[l] = a->array[i];
                l++;
                a->array[i] = ' ';
            }
            else {
                l++;
            }
        }
        else {
            a->array[i] = ' ';
        }
        Sleep(timeForSleep);
    }
    SetEvent(workEvent);
    return 0;
}
int sum = 0;
DWORD WINAPI SumElement(array* a) {
    EnterCriticalSection(&cs);
    WaitForSingleObject(sumEvent, INFINITE);
    int i = 0;
   
        while (a->array[i] != ' ') {
            sum += (int)a->array[i];
            i++;
            Sleep(200);
        }
    LeaveCriticalSection(&cs);
    return 0;
}

int main()
{
    array a;

    cout << "Input array size\n";
    cin >> a.size;
    a.array = new char[a.size];
    cout << "Input elements";
    for (size_t i = 0; i < a.size; i++)
    {
        cin >> a.array[i];
    }
    cout << "Array size: " << a.size << "\n";
    cout << "Array:\n";
    for (size_t i = 0; i < a.size; i++)
    {
        cout << a.array[i];
    }
    cout << "\n";
    HANDLE work_h, SumElement_h;
    DWORD work_id, SumElement_id;
    InitializeCriticalSection(&cs);
    int k;
    cout << "Input k\n";
    cin >> k;
    workEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (workEvent == NULL) {
        GetLastError();
    }
    sumEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (sumEvent == NULL) {
        GetLastError();
    }
    work_h = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, &a, 0, &work_id);
    if (work_h == NULL) {
        GetLastError();
    }
    SumElement_h = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SumElement, &a, 0, &SumElement_id);
    if (SumElement_h == NULL) {
        GetLastError();
    }
    WaitForSingleObject(workEvent, INFINITE);
    for (size_t i = 0; i < a.size; i++)
    {
        cout << a.array[i];
        if (i == k) {
            SetEvent(sumEvent);
        }
    }
    cout << "\nSum result\n";
    EnterCriticalSection(&cs);
    cout <<'\n'<< sum;
    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);
    CloseHandle(work_h);
    CloseHandle(SumElement_h);
    cout << "\n";
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
