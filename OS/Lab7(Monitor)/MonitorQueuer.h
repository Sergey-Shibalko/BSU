#pragma once
#include<Windows.h>
class MonitorQueuer {
public:
    MonitorQueuer(int sizeN) :size(sizeN), addPos(sizeN - 1), removePos(sizeN - 1) {
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
        WaitForSingleObject(ProduceSem, INFINITE);
        arr[addPos] = a;
        addPos--;
        if (addPos == -1) {
            addPos = size - 1;
        }
        ReleaseSemaphore(ConsumeSem, 1, NULL);
    }
    unsigned short RemoveTail() {
        WaitForSingleObject(ConsumeSem, INFINITE);
        removePos--;
        if (removePos == -2) {
            removePos = size - 2;
        }
        ReleaseSemaphore(ProduceSem, 1, NULL);
        return arr[removePos + 1];
    }


private:
    unsigned short* arr;
    int size, addPos, removePos;
    HANDLE ProduceSem, ConsumeSem;
};