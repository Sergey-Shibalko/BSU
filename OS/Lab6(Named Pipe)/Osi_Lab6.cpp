
#include <iostream>
#include<Windows.h>
using std::cout;
using std::cin;
void print(char* arr,int size) {
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i];
    }

    cout << "\n";
}
int main()
{
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
    HANDLE hNamedPipe;
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = FALSE; 
    int size;
    cout << "Enter array size \n";
    cin >> size;
    char* arr = new char[size];
    cout << "\nEnter array elements \n";
    for (size_t i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    cout << '\n';
    print(arr, size);
    char h = 'h';
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
        std::cerr << "Creation of the named pipe failed." << std::endl
            << "The last error code: " << GetLastError() << std::endl;
        cout << "Press any char to finish server: ";
        cin >> c;
        return 0;
    }

    ConnectNamedPipe(hNamedPipe, (LPOVERLAPPED)NULL);
    char r;
    DWORD sz;
    WriteFile(hNamedPipe, &size, sizeof(size), &sz, (LPOVERLAPPED)NULL);
    WriteFile(hNamedPipe, arr, size, &sz, (LPOVERLAPPED)NULL);
    int m;
    //DWORD sz;
    ReadFile(hNamedPipe, &m, sizeof(m), &sz, (LPOVERLAPPED)NULL);
    char* res = new char[m];
    ReadFile(hNamedPipe, res, m, &sz, (LPOVERLAPPED)NULL);
    cout << '\n';
    print(res, m);
    cin >> r;
    delete[]res;
    delete[]arr;
    CloseHandle(hNamedPipe);
}
