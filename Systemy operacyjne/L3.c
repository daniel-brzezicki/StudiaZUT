//SO IS1 210B LAB09
//Daniel Brzezicki
//bd46477@zut.edu.pl

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<windows.h>
#include <process.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	if (argc < 2 || argc>2) {
		fprintf(stderr, "Poprawne uzycie lab8 argument");
		return 1;
	}

	int length = strlen(argv[1]);

	for (int i = 0; i < length; i++) {
		if (!isdigit(argv[1][i])) {
			return 2;
		}

	}

	int a = atoi(argv[1]);
	if (a < 1 || a>13) {
		fprintf(stderr, "Argument za duzy lub za maly");
		return 3;
	}

	if (a == 1 || a == 2) {
		return 1;
	}


	STARTUPINFO child1 = { sizeof(child1) };

	PROCESS_INFORMATION child1Info;
	PROCESS_INFORMATION child2Info;
	char b[30];

	memset(&child1, 0, sizeof(child1));
	memset(&child1Info, 0, sizeof(child1Info));
	memset(&child2Info, 0, sizeof(child2Info));
	child1.cb = sizeof(child1);

	sprintf(b, "%s %d", argv[0], a - 1);
	if(!CreateProcess(NULL, b, NULL, NULL, FALSE, 0, NULL, NULL, &child1, &child1Info)) {
		return -1;
	}

	sprintf(b, "%s %d",argv[0], a - 2);
	if (!CreateProcess(NULL, b, NULL, NULL, FALSE, 0, NULL, NULL, &child1, &child2Info)) {
		return -1;
	}

	HANDLE p1 = child1Info.hProcess;
	WaitForSingleObject(p1, INFINITE);
	DWORD nCode = 0;
	GetExitCodeProcess(p1, &nCode);

	HANDLE p2 = child2Info.hProcess;
	WaitForSingleObject(p2, INFINITE);
	DWORD nCode1 = 0;
	GetExitCodeProcess(p2, &nCode1);

	printf("\n%d\t%d\t%d\t%d\n", GetCurrentProcessId(), child1Info.dwProcessId, a - 1, nCode);
	printf("%d\t%d\t%d\t%d\n", GetCurrentProcessId(), child2Info.dwProcessId, a - 2, nCode1);
	printf("%d\t\t\t%d\n", GetCurrentProcessId(), nCode + nCode1);

	CloseHandle(child1Info.hProcess);
	CloseHandle(child1Info.hThread);
	CloseHandle(child2Info.hProcess);
	CloseHandle(child2Info.hThread);


	return nCode+nCode1;
}
