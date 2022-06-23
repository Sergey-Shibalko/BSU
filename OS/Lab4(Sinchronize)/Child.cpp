// Child.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>

int main()
{
	HANDLE exit_ev = OpenEvent(SYNCHRONIZE, FALSE, "Exit");
	if (exit_ev == NULL) {
		GetLastError();
	}
    HANDLE mut = OpenMutex(SYNCHRONIZE, FALSE, "mutex");
    WaitForSingleObject(mut, INFINITE);
	HANDLE events[5];
	//HANDLE exit_ev = OpenEvent(SYNCHRONIZE, FALSE, "Exit");
	char p[2];
	for (size_t i = 0; i < 5; i++)
	{
		_itoa(i + 5, p, 10);
		events[i] = OpenEvent(SYNCHRONIZE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	DWORD ind;
	ind = WaitForMultipleObjects(4, events, FALSE, INFINITE);
	std::cout << "Message " << ind << '\n' << "From Parent to Child";
	_getch();
    ReleaseMutex(mut);
	std::cout << "\nEnd";
	WaitForSingleObject(exit_ev, INFINITE);
    
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
