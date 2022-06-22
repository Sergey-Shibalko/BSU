// Osi_Lab7_NewStandart.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <vector>
#include<semaphore>
class MonitorQueuer {
public:
    MonitorQueuer(int sizeN) :size(sizeN), addPos(sizeN - 1), removePos(sizeN - 1) {
        ProduceSem = new std::counting_semaphore<100>(sizeN);
        ConsumeSem = new std::counting_semaphore<100>(0);
        arr = new unsigned short[size];
    }
    ~MonitorQueuer() {
        delete ProduceSem;
        delete ConsumeSem;
        delete[] arr;
    }
    void AddHead(unsigned short a) {
        ProduceSem->acquire();
        arr[addPos] = a;
        addPos--;
        if (addPos == -1) {
            addPos = size - 1;
        }
        ConsumeSem->release();
    }
    unsigned short RemoveTail() {
        ConsumeSem->acquire();
        ProduceSem->release();
        removePos--;
        if (removePos == -2) {
            removePos = size - 2;
        }
        
        return arr[removePos + 1];
    }


private:
    unsigned short* arr;
    int size, addPos, removePos;
    std::counting_semaphore<100>* ProduceSem,* ConsumeSem;
};
void Produce(MonitorQueuer* mq,unsigned short a) {
    mq->AddHead(a);

}
void Consume(MonitorQueuer* mq) {
    std::cout<<mq->RemoveTail()<<'\n';
}
int main()
{
    int n;
    
    std::cout << "Input size\n";
    std::cin >> n;
    std::unique_ptr<MonitorQueuer> monitor(new MonitorQueuer(n));
    std::cout << "Input number of consume & produce process\n";
    int a, b;
    std::cin >> a >> b;
    std::vector<std::thread>ConsumeTh;
    std::vector<std::thread>ProduceTh;
    for (int i = 0;i < b;i++) {
        ProduceTh.push_back(std::thread(Produce, monitor.get(),i+1));
        //ProduceTh[i].join();
    }
    for (int i = 0;i < a;i++) {
        ConsumeTh.push_back(std::thread(Consume,monitor.get()));
       // ConsumeTh[i].join();
    }
    for (int i = 0;i < b;i++) {
        ProduceTh[i].join();
    }
    for (int i = 0;i < a;i++) {
        ConsumeTh[i].join();
    }
}

