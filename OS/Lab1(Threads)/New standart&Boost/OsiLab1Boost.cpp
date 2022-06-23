// OsiLab1Boost.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<boost/thread.hpp>
void ElementsFromAToB(std::vector<double>& arr, int a, int b) {
    int secondsToSleep = 1;
    for (int i = a;i <= b;i++) {
        std::cout << arr[i] << " ";
        boost::this_thread::sleep_for(boost::chrono::seconds(secondsToSleep));
    }
    std::cout << "\nWorker end work";
}
int main()
{
    int n;
    std::cin >> n;
    std::vector<double> arr(n);
    for (int i = 0;i < n;i++) {
        std::cin >> arr[i];
    }
    int a, b;
    std::cin >> a >> b;
    boost::thread worker(ElementsFromAToB, std::ref(arr), a, b);
    if (worker.joinable()) {
        worker.join();
    }
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
