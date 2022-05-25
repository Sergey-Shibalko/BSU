// Osi_lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
class Book {
public:
    Book() :writePos(0) {
        accsess = CreateSemaphore(NULL, 1, 1, "accsess");
        readSem = CreateSemaphore(NULL, 1, 1, "write");
        
    }
    void Write() {
        WaitForSingleObject(accsess, INFINITE);
        std::cout << "write\n";
        ReleaseSemaphore(accsess, 1, NULL);
    }
    void Read() {
        WaitForSingleObject(readSem, INFINITE);
        readerCount++;
        if(readerCount){ WaitForSingleObject(accsess, INFINITE); }
        ReleaseSemaphore(readSem, 1, NULL);
        std::cout << "read\n";
        WaitForSingleObject(readSem, INFINITE);
        readerCount--;
        if (readerCount==0) { ReleaseSemaphore(accsess, 1, NULL); }
        ReleaseSemaphore(readSem, 1, NULL);
    }
private:
    HANDLE accsess;
    HANDLE readSem;
    int size, writePos, readerCount = 0;
};
DWORD Writer(Book* b) {
    b->Write();
    return 0;
}
DWORD Reader(Book* b) {
    b->Read();
    return 0;
}

int main()
{
    std::cout << "Input number of reader & writer process\n";
    Book* b = new Book();
    int w, r;
    std::cin >> r >> w;
    HANDLE* writerH = new HANDLE[w];
    HANDLE* readerH = new HANDLE[r];
    DWORD ID;
    for (int i = 0;i < w;i++) {
        writerH[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer, b, 0, &ID);
    }
    for (int i = 0;i < r;i++) {
        writerH[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader, b, 0, &ID);
    }
    WaitForMultipleObjects(w, writerH, TRUE, INFINITE);
    WaitForMultipleObjects(r, readerH, TRUE, INFINITE);
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
