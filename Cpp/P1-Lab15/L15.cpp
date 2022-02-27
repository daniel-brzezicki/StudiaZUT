#include <iostream>
#include <string>

void count() {

}

void input_num(int counter) {
	std::string liczba = "4.5M";
	//std::cin >> liczba;
	//std::cout << liczba << std::endl;

	counter = 0;
	int zeros;
	switch (liczba.at(liczba.length() - 1)) {
	case 'M':
		zeros = 6;
		liczba.pop_back();
		for (int i = liczba.length() - 1; i >= 0; i--) {
			if (liczba.at(i) != '.') {
				counter++;
			}
			else {
				break;
			}
			counter = 0;
		}

		for (int i = 0; i < zeros - counter; i++) {
			liczba.push_back('0');
		}

		break;
	case 'B':

		break;
	case 'T':

		break;
	case 'Q':
		if (liczba.at(liczba.length() - 2) == 'a') {

		}
		else if (liczba.at(liczba.length() - 2) == 'i') {

		}
		break;
	case 'S':
		if (liczba.at(liczba.length() - 2) == 'x') {

		}
		else if (liczba.at(liczba.length() - 2) == 'p') {

		}
		break;
	case 'O':

		break;
	}


	std::cout << liczba << std::endl;


}

void Convert() {

}


int main()
{
	int counter = 0;
	std::string num;

	input_num(counter);
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
