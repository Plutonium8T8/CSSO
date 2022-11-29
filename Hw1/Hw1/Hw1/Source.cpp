#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <timezoneapi.h>
using namespace std;


reinterpret_cast<void *>(str.c_str())

void main()
{
	HANDLE h, h2;

	if (!CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week1", NULL))
	{
		printf("CreateDirectory failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		printf("CreateDirectory succeded: C:\\Facultate\\CSSO\\Laboratoare\\Week1\n");
	}

	if (!CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Extensii", NULL))
	{
		printf("CreateDirectory failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		printf("CreateDirectory succeded: C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Extensii\n");
	}

	if (!CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate", NULL))
	{
		printf("CreateDirectory failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		printf("CreateDirectory succeded: C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\n");
	}

	h = CreateFileA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\HKLM.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("Error at file opening (%d)\n", GetLastError());
		return;
	}

	LARGE_INTEGER file1;
	GetFileSizeEx(h, &file1);

	char myBuffer[300];
	memset(myBuffer, 0, 300);
	DWORD read;

	HKEY result;

	RegOpenKeyExA(HKEY_LOCAL_MACHINE, NULL, 0, KEY_READ, &result);

	DWORD    lpcSubKeys = 0;               // number of subkeys 
	DWORD    lpcMaxSubKeyLen;              // longest subkey size 
	FILETIME lpftLastWriteTime;            // last write time 

	char achKey[MAX_KEY_LENGTH];
	memset(achKey, 0, MAX_KEY_LENGTH);

	DWORD cbName = MAX_KEY_LENGTH, i;

	DWORD retCode = RegQueryInfoKey(
		result,                    // key handle 
		NULL,                // buffer for class name 
		NULL,           // size of class string 
		NULL,                    // reserved 
		&lpcSubKeys,               // number of subkeys 
		&lpcMaxSubKeyLen,            // longest subkey size 
		NULL,            // longest class string 
		NULL,                // number of values for this key 
		NULL,            // longest value name 
		NULL,         // longest value data 
		NULL,   // security descriptor 
		&lpftLastWriteTime);       // last write time 

	for (i = 0; i < lpcSubKeys; i++)
	{
		cbName = MAX_KEY_LENGTH;
		retCode = RegEnumKeyEx(result, i,
			achKey,
			&cbName,
			NULL,
			NULL,
			NULL,
			&lpftLastWriteTime);

		printf("%s\n", achKey);
	}

	printf("%d\n", i);

	
	if (!WriteFile(h, achKey, MAX_KEY_LENGTH, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	myBuffer[0] = '\n';
	myBuffer[1] = (char)i - 48;

	if (!WriteFile(h, myBuffer, 2, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	SYSTEMTIME st;

	FileTimeToSystemTime(&lpftLastWriteTime, &st);

	printf("The system time is: %02d:%02d:%02d:%02d:%02d\n", st.wMinute, st.wHour, st.wDay, st.wMonth, st.wYear);

	if (!WriteFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	CloseHandle(h);

	h = CreateFileA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\HKCC.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("Error at file opening (%d)\n", GetLastError());
		return;
	}
	
	LARGE_INTEGER file2;
	GetFileSizeEx(h, &file2);

	lpcSubKeys = 0;

	RegOpenKeyExA(HKEY_CURRENT_CONFIG, NULL, 0, KEY_READ, &result);

	retCode = RegQueryInfoKey(
		result,                    // key handle 
		NULL,                // buffer for class name 
		NULL,           // size of class string 
		NULL,                    // reserved 
		&lpcSubKeys,               // number of subkeys 
		&lpcMaxSubKeyLen,            // longest subkey size 
		NULL,            // longest class string 
		NULL,                // number of values for this key 
		NULL,            // longest value name 
		NULL,         // longest value data 
		NULL,   // security descriptor 
		&lpftLastWriteTime);       // last write time 

	for (i = 0; i < lpcSubKeys; i++)
	{
		cbName = MAX_KEY_LENGTH;
		retCode = RegEnumKeyEx(result, i,
			achKey,
			&cbName,
			NULL,
			NULL,
			NULL,
			&lpftLastWriteTime);

		printf("%s\n", achKey);
	}

	printf("%d\n", i);


	if (!WriteFile(h, myBuffer, MAX_KEY_LENGTH, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	myBuffer[0] = '\n';
	myBuffer[1] = (char)i - 48;

	if (!WriteFile(h, myBuffer, 2, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	st;

	FileTimeToSystemTime(&lpftLastWriteTime, &st);

	printf("The system time is: %02d:%02d:%02d:%02d:%02d\n", st.wMinute, st.wHour, st.wDay, st.wMonth, st.wYear);

	if (!WriteFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	CloseHandle(h);

	h = CreateFileA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\HKCU.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("Error at file opening (%d)\n", GetLastError());
		return;
	}

	LARGE_INTEGER file3;
	GetFileSizeEx(h, &file3);

	lpcSubKeys = 0;

	RegOpenKeyExA(HKEY_CURRENT_USER, NULL, 0, KEY_READ, &result);

	retCode = RegQueryInfoKey(
		result,                    // key handle 
		NULL,                // buffer for class name 
		NULL,           // size of class string 
		NULL,                    // reserved 
		&lpcSubKeys,               // number of subkeys 
		&lpcMaxSubKeyLen,            // longest subkey size 
		NULL,            // longest class string 
		NULL,                // number of values for this key 
		NULL,            // longest value name 
		NULL,         // longest value data 
		NULL,   // security descriptor 
		&lpftLastWriteTime);       // last write time 

	for (i = 0; i < lpcSubKeys; i++)
	{
		cbName = MAX_KEY_LENGTH;
		retCode = RegEnumKeyEx(result, i,
			achKey,
			&cbName,
			NULL,
			NULL,
			NULL,
			&lpftLastWriteTime);

		printf("%s\n", achKey);
	}

	printf("%d\n", i);


	if (!WriteFile(h, achKey, MAX_KEY_LENGTH, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	myBuffer[0] = '\n';
	myBuffer[1] = (char)i - 48;

	if (!WriteFile(h, myBuffer, 2, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	FileTimeToSystemTime(&lpftLastWriteTime, &st);

	printf("The system time is: %02d:%02d:%02d:%02d:%02d\n", st.wMinute, st.wHour, st.wDay, st.wMonth, st.wYear);

	if (!WriteFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	CloseHandle(h);

	h = CreateFileA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\summary.txt", GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("Error at file opening (%d)\n", GetLastError());
		return;
	}

	GetFullPathNameA("HKLM.txt", 300, myBuffer, NULL);

	printf("\n%s\n", myBuffer);

	printf("%d", file1.LowPart);

	if (!WriteFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}


	GetFullPathNameA("HKCC.txt", 300, myBuffer, NULL);

	printf("\n%s\n", myBuffer);

	printf("%d", file2.LowPart);

	if (!WriteFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}


	GetFullPathNameA("HKCU.txt", 300, myBuffer, NULL);

	printf("\n%s\n", myBuffer);

	printf("%d\n", file3.LowPart);

	if (!WriteFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la scriere in fisier: %d", GetLastError());
		CloseHandle(h);
		return;
	}

	LPCTSTR Directory = TEXT("C:\\Facultate\\CSSO\\Laboratoare\\Week1");
	LSTATUS ReturnValue;

	ReturnValue = RegCreateKeyExA(
		HKEY_LOCAL_MACHINE,
		NULL,
		NULL,
		NULL,
		REG_SZ,
		KEY_ALL_ACCESS,
		NULL,
		&result,
		NULL);
	
	if (ERROR_SUCCESS != ReturnValue)
	{
		printf("RegCreateKeyEx failed\n");
		printf("%d\n", GetLastError());
		return;
	}


	if (ERROR_SUCCESS != ReturnValue)
	{
		printf("RegOpenKeyEx failed\n");
		printf("%d\n", GetLastError());
		return;
	}

	LPCSTR Value = "C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\summary.txt";
	ReturnValue = RegSetValueA(HKEY_LOCAL_MACHINE, "C:\\Facultate\\CSSO\\Laboratoare\\Week1", REG_SZ, Value, sizeof(Value));
	if (ERROR_SUCCESS != ReturnValue)
	{
		printf("RegStatusValueA failed\n");
		printf("%d\n", GetLastError());
		return;
	}

	ReturnValue = RegCloseKey(result);
	if (ERROR_SUCCESS != ReturnValue)
	{
		printf("RegCloseKey failed\n");
		printf("%d\n", GetLastError());
		return;
	}
}