#include <windows.h>
#include <iostream>
#include <process.h>
using namespace std;

//volatile UINT count1;
struct arr {
	double* m;
	int n;
	int a;
	int b;
};

DWORD WINAPI Worker(arr* ar)
{

	for (size_t i = ar->a; i <= ar->b; i++)
	{
		cout << ar->m[i]<<'\n';
		Sleep(15);
	}
	return 0;
}
DWORD WINAPI Count() {
	int s1 = 0;
	int s2 = 1, sum;
	for (;;) {
		sum = s1 + s2;
		s1 = s2;
		s2 = sum;
		cout << sum<<'\n';
		Sleep(100);
	}
	return 0;
}
int main()
{
	HANDLE 	worker;
	DWORD	IDThread;
	arr ar;
	//int n,a,b;
	//double* m = new double[n];
	cout << "Input array size";
	cin >> ar.n;
	ar.m = new double[ar.n];
	for (int i = 0;i < ar.n;i++) {
		ar.m[i] = rand();
	}
	cout << "Input a";
	cin >> ar.a;
	cout << "Input b";
	cin >> ar.b;
	worker = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Worker,&ar,  0, &IDThread);
	if (worker == NULL)
		return GetLastError();
	Sleep(50);
	SuspendThread(worker);
	char in;
	cout << "Input 'r' to resume thread or 'b' to break thread";
	cin >> in;
	if (in == 'r') {
		ResumeThread(worker);
		//WaitForSingleObject(worker, INFINITE);
		//ExitThread(GetExitCodeThread(hThread,&IDThread));
		//TerminateThread(worker, 0);
	}
	else {
		//ExitThread(GetExitCodeThread(hThread, &IDThread));
		TerminateThread(worker, 0);
	}
	cout << "end" << '\n';
	
	unsigned  thrID;

	// закрываем дескриптор потока
	CloseHandle(worker);
	worker = (HANDLE)_beginthreadex(NULL,0, (_beginthreadex_proc_type)Worker,&ar,0, &thrID);
	if (worker == NULL)
		return GetLastError();
	WaitForSingleObjectEx(worker,INFINITE,0);
	TerminateThread(worker, 0);
	CloseHandle(worker);
	//Sleep(1000);
	worker= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count, NULL, CREATE_SUSPENDED, &IDThread);
	if (worker == NULL)
		return GetLastError();
	in = '0';
	cout << "Input 'r' to run thread" << '\n';
	cin >> in;
	if (in == 'r') {
		ResumeThread(worker);

	}
	cout << "Input 'b' to stop thread" << '\n';
	cin >> in;
	if (in == 'b') {
		TerminateThread(worker, 0);
		
	}
	CloseHandle(worker);
	return 0;
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
