// OSI_Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
using namespace std;
HANDLE workEvent, sumEvent;
struct arr {
    char* arr;
    int n;
};
DWORD WINAPI work(arr* a) {
    DWORD t;
    cout << "Input sleep time\n";
    cin >> t;
    int l = 0;
    for (size_t i = 0; i < a->n; i++)
    {
        if (33 <= (int)a->arr[i] <= 47 || 58 <= (int)a->arr[i] <= 64 || 91 <= (int)a->arr[i] <= 96 || 123 <= (int)a->arr[i] <= 127) {
            a->arr[l] = a->arr[i];
            l++;
            a->arr[i] = ' ';
        }
        else {
            a->arr[i] = ' ';
        }
        Sleep(t);
    }
    SetEvent(workEvent);
    return 0;
}
DWORD WINAPI SumElement(arr* a) {
    WaitForSingleObject(sumEvent, INFINITE);
    return 0;
}

int main()
{
    arr a;
    //cout << (int)' ';
    cout << "Input array size\n";
    cin >> a.n;
    a.arr = new char[a.n];
    cout << "Input elements";
    for (size_t i = 0; i < a.n; i++)
    {
        cin >> a.arr[i];
    }
    cout << "Array size: " << a.n << "\n";
    cout << "Array:\n";
    for (size_t i = 0; i < a.n; i++)
    {
        cout << a.arr[i];
    }
    cout << "\n";
    HANDLE work_h, SumElement_h;
    DWORD work_id, SumElement_id;
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
    for (size_t i = 0; i < a.n; i++)
    {
        cout << a.arr[i];
        if (i == k) {
            SetEvent(sumEvent);
        }
    }
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
