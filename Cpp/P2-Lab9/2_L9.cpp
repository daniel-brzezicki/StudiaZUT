// 2_L9.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "BaseClass.h"
#include "OffensiveClass.h"
#include "PassiveClass.h"

void CreateCharacters() {
	//BaseClass *player = new OffensiveClass(50, "eplayer", 5, "ggg!");
	std::unique_ptr<BaseClass> player = std::make_unique<OffensiveClass>(20, "player", 5, "rrrr!");

	std::vector<std::unique_ptr<BaseClass>> characters;


	characters.push_back(std::make_unique<OffensiveClass>(2, "enemy", 1, "ggg!"));
	characters.push_back(std::make_unique<OffensiveClass>(2, "enemy", 1, "lalal!"));
	characters.push_back(std::make_unique<OffensiveClass>(2, "enemy", 1, "siup!"));
	characters.push_back(std::make_unique<OffensiveClass>(2, "enemy", 1, "lolek!"));
	characters.push_back(std::make_unique<OffensiveClass>(2, "enemy", 1, "fikolek!"));



	for (int i = 0; i < characters.size(); i++) {
		player->dealDamage(characters[i]);
	}
}



int main()
{
	//CreateCharacters();
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
