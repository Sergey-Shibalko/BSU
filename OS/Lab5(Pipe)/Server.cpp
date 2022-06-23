// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<conio.h>
#include<Windows.h>
using std::cout;
using std::cin;
void print(char* arr, int size) {
    for (int i = 0;i < size;i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
int main()
{
    HANDLE write, read;
    HANDLE end = CreateEvent(NULL, FALSE, FALSE, "end");
    if (end == NULL) {
        GetLastError();
    }
    int size;
    cout << "Enter array size \n";

    cin >> size;
    char* arr=new char[size];
    cout << "\nEnter array elements \n";
    for (size_t i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    cout << '\n';
    print(arr, size);
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
    wsprintf(a, "Consume.exe %d %d %d", int(write), int(read),size);

    if (!CreateProcess(NULL, a, NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        GetLastError();
    }
    for (size_t i = 0; i < size; i++)
    {
        DWORD sizeD;
        WriteFile(write, &arr[i], sizeof(arr[i]), &sizeD, NULL);
    }
   SetEvent(event);
   WaitForSingleObject(end, INFINITE);
   int answSize;
   DWORD sz;
   ReadFile(read, &answSize, sizeof(answSize), &sz, NULL);
   char* answStr = new char[answSize];
   for (int i = 0;i < answSize;i++) {
       DWORD sizeD;
       ReadFile(read, &answStr[i], sizeof(answStr[i]), &sizeD, NULL);
   }
   print(answStr, answSize);
   delete[]answStr;
   delete[]arr;
   CloseHandle(read);
   CloseHandle(write);
   CloseHandle(end);
   
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
