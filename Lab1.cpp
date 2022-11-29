#include <windows.h>
#include <stdio.h>
using namespace std;

int main()
{
	HANDLE h;
	h = CreateFile("C:\\ok", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		printf("Error la deschidere fisier: %d\n", GetLastError());
		return 0;
	}
	char myBuffer[300];
	memset(myBuffer, 0, 300);
	DWORD read;
	if (!ReadFile(h, myBuffer, 300, &read, NULL))
	{
		printf("Error la citire din fisier: %d", GetLastError());
		CloseHandle(h);
		return 0;
	}

	CloseHandle(h);

	printf("Am citit din fisier %d caractere: %s\n", read, myBuffer);

}