// Sprawdzanie_dnia.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

int day, month, x, date;


int wyliczenie_dnia(int a) {
	if (a % 7 == 0) {
		printf_s("Dzien: %d,%d,2019 to poniedzialek.\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	else if (a % 7 == 1) {
		printf_s("Dzien: %d, %d, 2019 to wtorek\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	else if (a % 7 == 2) {
		printf_s("Dzien: %d,%d,2019 to sroda\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	else if (a % 7 == 3) {
		printf_s("Dzien: %d,%d,2019 to czwartek\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	else if (a % 7 == 4) {
		printf_s("Dzien: %d,%d,2019 to piatek\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	else if (a % 7 == 5) {
		printf_s("Dzien: %d,%d,2019 to sobota\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	else if (a % 7 == 6) {
		printf_s("Dzien: %d,%d,2019 to niedziela\n", date, month);
		printf_s("Tygodni - %d.\n", x / 7);
	}
	return 0;
}

int main()
{
	printf_s("Podaj date (format:dd,mm) \n");

	scanf_s("%d,%d", &day,&month);

	date = day;

	if (month == 1) {
		wyliczenie_dnia(day);
	}
	else if (month == 2) {
		x = 31 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 3) {
		x = 59 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 4) {
		x = 90 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 5) {
		x = 120 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 6) {
		x = 151 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 7) {
		x = 181 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 8) {
		x = 212 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 9) {
		x = 243 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 10) {
		x = 273 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 11) {
		x = 304 + day;
		day = x;
		wyliczenie_dnia(day);
	}
	else if (month == 12) {
		x = 334 + day;
		day = x;
		wyliczenie_dnia(day);
	}


}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
