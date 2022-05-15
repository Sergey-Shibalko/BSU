// Parent.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	HANDLE events_P[5];
	char p_P[2];
	for (size_t i = 0; i < 5; i++)
	{
		_itoa(i + 5, p_P, 10);
		events_P[i] = (HANDLE)CreateEvent(NULL, FALSE, FALSE, p_P);
		if (events_P[i] == NULL) {
			GetLastError();
		}

	}
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS,TRUE, "semaphore");
	if (sem == NULL) {
		GetLastError();
	}
	bool b;
	
	WaitForSingleObject(sem, INFINITE);
	
	
    HANDLE events[4];
	char p[2];
	for (size_t i = 0; i < 4; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = OpenEvent(SYNCHRONIZE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	DWORD ind;
	ind = WaitForMultipleObjects(4, events, FALSE, INFINITE);
	std::cout<<"Message "<<ind<<'\n'<<"From Boss to Parent";
	SetEvent(events_P[ind + 1]);
	//_getch();
	ReleaseSemaphore(sem, 1, NULL);
	WaitForSingleObject(exit_ev,INFINITE);
	

	

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
