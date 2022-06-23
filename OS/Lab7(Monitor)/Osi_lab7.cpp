
#include <iostream>
#include<Windows.h>
#include"MonitorQueuer.h"
#include"QueuerStruct.h"
HANDLE ac = CreateSemaphore(NULL, 1, 1, "acsess");
DWORD Produce(QueuerStruct* st) {
    
    char s[80];
    for (int i = 0;i < st->a;i++) {
        WaitForSingleObject(ac, INFINITE);
        st->queue->AddHead(st->b);
        wsprintf(s, "Produce product %d\n", st->b);

        std::cout << s;
        ReleaseSemaphore(ac, 1, NULL);
   }
    
    return 0;
}
DWORD Consume(QueuerStruct* st) {
    unsigned short tmp;
    char s[80];
    for (int i = 0;i < st->a;i++) {
       tmp= st->queue->RemoveTail();
       wsprintf(s, "Comsume product %d\n", tmp);
       std::cout << s;
       ReleaseSemaphore(ac, 1, NULL);
    }
    return 0;
}
void CloseH(HANDLE* arrH, int n) {
    for (int i = 0;i < n; i++) {
        CloseHandle(arrH[i]);
    }
}
int main()
{
    int n;
    MonitorQueuer* que;
    std::cout << "Input size\n";
    std::cin >> n;
    que = new MonitorQueuer(n);
    std::cout << "Input number of consume & produce process\n";
    int a,b;
    std::cin >> a>>b;
    QueuerStruct* cons = new QueuerStruct[a];
    QueuerStruct* prod = new QueuerStruct[b];
    int tmp;
    for (int i = 0;i < b;i++) {
        prod[i].queue = que;
        std::cout << "Input number of produce products\n";
        std::cin >> prod[i].a;
        std::cout << "Input product\n";
        std::cin >> prod[i].b;

    }
    for (int i = 0;i < a;i++) {
        cons[i].queue = que;
        std::cout << "Input number of consume products\n";
        std::cin >> cons[i].a;
    }
    
    HANDLE* produce = new HANDLE[b];
    HANDLE* consume = new HANDLE[a];
    DWORD ID;
    for (int i = 0;i < b;i++) {
        produce[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Produce, &prod[i],0, &ID);
    }
    for (int i = 0;i < a;i++) {
        consume[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Consume, &cons[i], 0, &ID);
    }
    WaitForMultipleObjects(b, produce, TRUE, INFINITE);
    WaitForMultipleObjects(a, consume, TRUE, INFINITE);
    CloseH(produce, b);
    CloseH(consume, a);
    delete[]consume;
    delete[]produce;
    delete[]prod;
    delete[]cons;
    delete que;
}
