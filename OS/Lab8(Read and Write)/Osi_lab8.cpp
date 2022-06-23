
#include <iostream>
#include<Windows.h>
#include"Book.h"
#include"write.h"

DWORD Writer(write* wr) {
    wr->b->Write(wr->a);
    return 0;
}
DWORD Reader(Book* b) {
    b->Read();
    return 0;
}
void closeH(HANDLE* arr,int n) {
    for (size_t i = 0; i < n; i++)
    {
        CloseHandle(arr[i]);
    }

}
int main()
{
    write* wr=new write();
    std::cout << "Input number of reader & writer process\n";
    Book* b = new Book();
    int w, r;
    std::cin >> r >> w;
    wr->b = b;
    HANDLE* writerH = new HANDLE[w];
    HANDLE* readerH = new HANDLE[r];
    DWORD ID;
    for (int i = 0;i < w;i++) {
        wr->a = i+1
            ;
        writerH[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer, wr, 0, &ID);
       
    }
    for (int i = 0;i < r;i++) {
        readerH[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader, b, 0, &ID);
    }
    WaitForMultipleObjects(w, writerH, TRUE, INFINITE);
    WaitForMultipleObjects(r, readerH, TRUE, INFINITE);
    closeH(writerH,w);
    closeH(readerH, r);
    delete[]readerH;
    delete[]writerH;
    delete b;
    delete wr;

}
