// Osi_Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
using namespace std;

int main()
{
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
    HANDLE hNamedPipe;
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = FALSE; 
    int n;
    cout << "Enter array size \n";

    cin >> n;
    char* arr = new char[n];
    cout << "\nEnter array elements \n";
    for (size_t i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << '\n';
    for (size_t i = 0; i < n; i++)
    {
        cout << arr[i];
    }
    cout << "\n";
    char h = 'h';
    //DWORD sz;
    
    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
    sa.lpSecurityDescriptor = &sd;
    hNamedPipe = CreateNamedPipe("\\\\.\\pipe\\demo_pipe", PIPE_ACCESS_DUPLEX, // читаем из канала и пишем в канал
        PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронная передача сообщений
        1, // максимальное количество экземпляров канала
        0, // размер выходного буфера по умолчанию
        0, // размер входного буфера по умолчанию
        INFINITE, // клиент ждет связь 500 мс
        &sa // доступ для всех пользователей
    );
    char c;
    if (hNamedPipe == INVALID_HANDLE_VALUE)
    {
        cerr << "Creation of the named pipe failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any char to finish server: ";
        cin >> c;
        return 0;
    }

    ConnectNamedPipe(hNamedPipe, (LPOVERLAPPED)NULL);
    char r;
    DWORD sz;
    WriteFile(hNamedPipe, &n, sizeof(n), &sz, (LPOVERLAPPED)NULL);
    WriteFile(hNamedPipe, arr, n, &sz, (LPOVERLAPPED)NULL);
    int m;
    //DWORD sz;
    ReadFile(hNamedPipe, &m, sizeof(m), &sz, (LPOVERLAPPED)NULL);
    char* res = new char[m];
    ReadFile(hNamedPipe, res, m, &sz, (LPOVERLAPPED)NULL);
    cout << '\n';
    for (size_t i = 0; i < m; i++)
    {
        cout << res[i];
    }
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
