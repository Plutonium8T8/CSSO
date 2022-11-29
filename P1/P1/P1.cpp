#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
using namespace std;

char* intToChar(int number)
{
	int count = 0;
	int power = 1;
	int numberAux = number;

	while (numberAux > 0)
	{
		count++;
		numberAux = numberAux / 10;
	}

	char returnBuffer[16];

	for (int index = 0; index < count - 1; index++)
	{
		power *= 10;
	}

	int index = 0;

	while (number > 0)
	{
		returnBuffer[index] = char((number / power) + 48);
		number %= power;
		power /= 10;
		index++;
	}

	return returnBuffer;
}

int lengthOf(char* buffer)
{
	int index = 0;

	while (int(buffer[index]) > 0)
	{
		index++;
	}

	return index;
}

void main()
{
	if (!CreateDirectoryA("D:\\Facultate\\CSSO\\Laboratorare\\Week2", NULL))
	{
		printf("CreateDirectory failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		printf("CreateDirectory succeded: C:\\Facultate\\CSSO\\Laboratoare\\Week2\n");
	}


	// Processes


	HANDLE h;

	h = CreateFileA("D:\\Facultate\\CSSO\\Laboratorare\\Week2\\procese.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("CreateFileA failed.err = %d \n", GetLastError());
		return;
	}

	HANDLE processes = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (processes == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return;
	}

	PROCESSENTRY32 pe32;

	DWORD read;

	char myBuffer[400];

	pe32.dwSize = sizeof(PROCESSENTRY32);

	int procesCounter = 0;

	if (!Process32First(processes, &pe32))
	{
		printf("Process32First failed. err = %d \n", GetLastError());
		CloseHandle(processes);
		return;
	}
	do
	{
		if (procesCounter != 0)
		{
			if (!WriteFile(h, intToChar(pe32.th32ParentProcessID), lengthOf(intToChar(pe32.th32ParentProcessID)), &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, " ", 1, &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, intToChar(pe32.th32ProcessID), lengthOf(intToChar(pe32.th32ProcessID)), &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, " ", 1, &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}
		}

		if (!WriteFile(h, pe32.szExeFile, lengthOf(pe32.szExeFile), &read, NULL))
		{
			printf("Error la scriere in fisier: %d", GetLastError());
			CloseHandle(h);
			return;
		}

		if (!WriteFile(h, "\n", 1, &read, NULL))
		{
			printf("Error la scriere in fisier: %d", GetLastError());
			CloseHandle(h);
			return;
		}

		procesCounter++;

	} while (Process32Next(processes, &pe32));

	CloseHandle(processes);

	CloseHandle(h);


	// Threads


	h = CreateFileA("D:\\Facultate\\CSSO\\Laboratorare\\Week2\\fire.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("CreateFileA failed.err = %d \n", GetLastError());
		return;
	}

	HANDLE threads = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (threads == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return;
	}

	THREADENTRY32 te32;

	te32.dwSize = sizeof(THREADENTRY32);

	int threadCounter = 0;

	if (!Thread32First(threads, &te32))
	{
		printf("Thread32First failed. err = %d \n", GetLastError());
		CloseHandle(threads);
		return;
	}
	do
	{
		if (threadCounter != 0)
		{
			if (!WriteFile(h, intToChar(te32.th32ThreadID), lengthOf(intToChar(te32.th32ThreadID)), &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, " ", 1, &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}
		}

		if (!WriteFile(h, intToChar(te32.th32OwnerProcessID), lengthOf(intToChar(te32.th32OwnerProcessID)), &read, NULL))
		{
			printf("Error la scriere in fisier: %d", GetLastError());
			CloseHandle(h);
			return;
		}

		if (!WriteFile(h, "\n", 1, &read, NULL))
		{
			printf("Error la scriere in fisier: %d", GetLastError());
			CloseHandle(h);
			return;
		}

		threadCounter++;

	} while (Thread32Next(threads, &te32));

	CloseHandle(threads);

	CloseHandle(h);


	// Modules
	/*

	h = CreateFileA("D:\\Facultate\\CSSO\\Laboratorare\\Week2\\module.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("CreateFileA failed.err = %d \n", GetLastError());
		return;
	}

	HANDLE modules = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (modules == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return;
	}

	MODULEENTRY32 me32;

	me32.dwSize = sizeof(MODULEENTRY32);

	int moduleCounter = 0;

	if (!Module32First(modules, &me32))
	{
		printf("Module32First failed. err = %d \n", GetLastError());
		CloseHandle(modules);
		return;
	}
	do
	{
		if (moduleCounter != 0)
		{
			if (!WriteFile(h, intToChar(me32.th32ModuleID), lengthOf(intToChar(me32.th32ModuleID)), &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, " ", 1, &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, intToChar(me32.th32ProcessID), lengthOf(intToChar(me32.th32ProcessID)), &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, " ", 1, &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, me32.szModule, lengthOf(me32.szModule), &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}

			if (!WriteFile(h, " ", 1, &read, NULL))
			{
				printf("Error la scriere in fisier: %d", GetLastError());
				CloseHandle(h);
				return;
			}
		}

		if (!WriteFile(h, me32.szExePath, lengthOf(me32.szExePath), &read, NULL))
		{
			printf("Error la scriere in fisier: %d", GetLastError());
			CloseHandle(h);
			return;
		}

		if (!WriteFile(h, "\n", 1, &read, NULL))
		{
			printf("Error la scriere in fisier: %d", GetLastError());
			CloseHandle(h);
			return;
		}

		moduleCounter++;

	} while (Module32Next(modules, &me32));

	CloseHandle(modules);

	CloseHandle(h);

	*/

	h = CreateFileA("D:\\Facultate\\CSSO\\Laboratorare\\Week2\\FileMapping.txt", GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("CreateFileA failed.err = %d \n", GetLastError());
		return;
	}

	HANDLE MemoryMapping = CreateFileMappingA(h, NULL, PAGE_EXECUTE_READWRITE, 256, 128, "cssow2basicsync");

	if (MemoryMapping == INVALID_HANDLE_VALUE)
	{
		printf("CreateFileA failed.err = %d \n", GetLastError());
		return;
	}

	if (!WriteFile(h, "Module: ", 8, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	/*if (!WriteFile(h, intToChar(moduleCounter), 1, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}*/

	if (!WriteFile(h, " Fire: ", 7, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	if (!WriteFile(h, intToChar(threadCounter), lengthOf(intToChar(threadCounter)), &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	if (!WriteFile(h, " Procese: ", 10, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	if (!WriteFile(h, intToChar(procesCounter), lengthOf(intToChar(procesCounter)), &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	if (!WriteFile(h, "\n", 1, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}
}