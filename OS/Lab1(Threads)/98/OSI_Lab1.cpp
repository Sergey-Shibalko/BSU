#include <windows.h>
#include <iostream>
#include <process.h>
#include"Array.h"
using std::cout;
using std::cin;

DWORD WINAPI Worker(array* ar)
{

	for (size_t i = ar->a; i <= ar->b; i++)
	{
		cout << ar->array[i]<<'\n';
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
	array ar;
	cout << "Input array size";
	cin >> ar.size;
	ar.array = new double[ar.size];
	for (int i = 0;i < ar.size;i++) {
		ar.array[i] = rand();
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
	}
	else {
		TerminateThread(worker, 0);
	}
	cout << "end" << '\n';
	unsigned  thrID;
	CloseHandle(worker);
	worker = (HANDLE)_beginthreadex(NULL,0, (_beginthreadex_proc_type)Worker,&ar,0, &thrID);
	if (worker == NULL)
		return GetLastError();
	WaitForSingleObjectEx(worker,INFINITE,0);
	TerminateThread(worker, 0);
	CloseHandle(worker);
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
	delete[] ar.array;
	return 0;
}
