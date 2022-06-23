#pragma once
#include<Windows.h>
class Book {
public:
    Book() {
        accsess = CreateSemaphore(NULL, 1, 1, "accsess");
        readSem = CreateSemaphore(NULL, 1, 1, "write");
    }
    void Write(int n) {
        WaitForSingleObject(accsess, INFINITE);
        std::cout << n << "write\n";
        a = n;
        ReleaseSemaphore(accsess, 1, NULL);
    }
    void Read() {
        WaitForSingleObject(readSem, INFINITE);
        readerCount++;
        if (readerCount) { WaitForSingleObject(accsess, INFINITE); }
        std::cout << a << " read" << "\n";
        readerCount--;
        if (readerCount == 0) { ReleaseSemaphore(accsess, 1, NULL); }
        ReleaseSemaphore(readSem, 1, NULL);
    }
private:
    HANDLE accsess;
    HANDLE readSem;
    int a, size;
    int readerCount = 0;
};