// OsiLab3NewStandart.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<iomanip>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
using std::cout;
using std::cin;

std::mutex mutexCharNotNumberOrLetter;
std::condition_variable cvCharNotNumberOrLetter;

std::mutex mutexSumElements;
std::condition_variable cvSumElements;

void CharNotNumberOrLetter(std::vector<char>&vec) {
    std::unique_lock<std::mutex> locker(mutexCharNotNumberOrLetter);
    int sleepTime;
    cout << "Input sleep time\n";
    cin >> sleepTime;
    int l = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        
        if ((33 <= (int)vec[i] && (int)vec[i] <= 47) ||
            (58 <= (int)vec[i] && (int)vec[i] <= 64) ||
            (91 <= (int)vec[i] && (int)vec[i] <= 96) ||
            (123 <= (int)vec[i] && (int)vec[i] <= 127)) {
            if (l != i) {
                vec[l] = vec[i];
                l++;
                vec[i] = ' ';
            }
            else {
                l++;
            }
        }
        else {
            vec[i] = ' ';
        }
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
    }
    locker.unlock();
    cvCharNotNumberOrLetter.notify_one();

}
void SumElement(std::vector<char>& vec,int& sum) {
    std::unique_lock<std::mutex>locker(mutexSumElements);
    cvSumElements.wait(locker);
    int i = 0;
    while (vec[i]!= ' ') {
        sum += (int)vec[i];
        i++;
    }
    locker.unlock();
    cvSumElements.notify_one();
}

int main()
{
    int size;
    cout << "Input array size\n";
    cin >> size;
    cout << "Input elements";
    std::vector<char> vec(size);
    for (int i = 0;i < size;i++) {
        cin >> vec[i];
    }
    cout << "Array size: " << size << "\n";
    cout << "Array:\n";
    for (size_t i = 0; i < size; i++)
    {
        cout << vec[i];
    }
    cout << "\n";
    int k,sum=0;
    cout << "Input k<size\n";
    cin >> k; 
    std::thread work(CharNotNumberOrLetter, std::ref(vec));
    std::thread sumThread(SumElement, std::ref(vec),std::ref(sum));
    std::unique_lock<std::mutex> locker(mutexCharNotNumberOrLetter);
    cvCharNotNumberOrLetter.wait(locker);
    for (auto i : vec) {
        cout << i;
    }
    std::unique_lock<std::mutex>locker1(mutexSumElements);
    cvSumElements.notify_one();
    cvSumElements.wait(locker1);
    cout << "\nSum: " << sum;
    work.join();
    sumThread.join();
}

