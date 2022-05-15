// Osi_lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
class MonitorQueuer {
public:
    MonitorQueuer(int sizeN) :size(sizeN),addPos(sizeN-1),removePos(sizeN-1) {
        ProduceSem = CreateSemaphore(NULL, size, size, "produce");
        ConsumeSem = CreateSemaphore(NULL, 0, size, "consume");
        arr = new unsigned short[size];
    }
    ~MonitorQueuer() {
        CloseHandle(ProduceSem);
        CloseHandle(ConsumeSem);
        delete[] arr;
    }
    void AddHead(unsigned short a) {
        WaitForSingleObject(ProduceSem,INFINITE);
        arr[addPos] = a;
        addPos--;
        if (addPos == -1) {
            addPos = size - 1;
        }
        ReleaseSemaphore(ConsumeSem,1,NULL);
    }
    unsigned short RemoveTail() {
        WaitForSingleObject(ConsumeSem, INFINITE);
        removePos--;
        if (removePos==-2) {
            removePos = size - 2;
        }
        ReleaseSemaphore(ProduceSem, 1, NULL);
        return arr[removePos + 1];
    }


private:
    unsigned short* arr;
    int size,addPos,removePos;
    HANDLE ProduceSem, ConsumeSem;
};
int main()
{
    std::cout << "Hello World!\n";
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
