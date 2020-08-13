#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static HANDLE serialPort;

static void DisplayError() {
	LPTSTR errorMessage;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		0,
		(LPTSTR)&errorMessage,
		0,
		NULL);
	MessageBox(GetConsoleWindow(), errorMessage, NULL, MB_OK);
	LocalFree(errorMessage);
}

int _tmain(int argc, TCHAR *argv[]) {
	if (argc > 1) {
		serialPort = CreateFile(
			argv[1],
			GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		if (serialPort == INVALID_HANDLE_VALUE) {
			DisplayError();
		}
		while (1) {
			char data[10];
			double temperature = rand() % 4000;
			temperature /= 100;
			int size = sprintf_s(data, sizeof data, "%.2f\n", temperature);
			if (!WriteFile(serialPort, data, size, &size, NULL)) {
				DisplayError();
			}
			Sleep(1000);
		}
	}
}
