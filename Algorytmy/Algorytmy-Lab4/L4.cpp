//Daniel Brzezicki,
//bd46477@zut.edu.pl,


#include "pch.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <crtdbg.h>
#include <time.h>

using namespace std;

template<typename K, typename V>
class HashElement {
public:
	K key;
	V value;
	HashElement(K key, V value) {
		this->key = key;
		this->value = value;
	}
};

template<typename K, typename V>
class HashTable {
private:
	vector<HashElement<K, V>> * table;
	int N = 4;
	int size = 0;
public:
	HashTable() {
		table = new vector <HashElement<string, int>>[N];
	}

	~HashTable() {
		Clear();
		delete[] table;
	}

	int Hash(K key) {
		int a = 31;

		int h = 0;
		for (int i = 0; i < key.length(); i++) {
			h = a * h + key[i];
		}
		h = abs(h);

		return h % N;
	}

	void Add(K key, V value) {
		int hashed = Hash(key);

		if ((float)size / N > 0.75f) {
			Rehash();
		}
		

		for (int i = 0; i < table[hashed].size(); i++) {
			if (table[hashed][i].key == key) {
				table[hashed][i].value = value;
				return;
			}
		}
		table[hashed].push_back(HashElement<K, V>(key, value));
		size++;

	}

	void Rehash() {
		int oldN = N;
		N = N * 2;

		vector<HashElement<K, V>> * newTab = new vector<HashElement<K, V>>[N];
		vector<HashElement<K, V>> * oldTab = new vector<HashElement<K, V>>[oldN];


		for (int i = 0; i < oldN; i++) {
			oldTab[i] = table[i];
		}

		delete[] table;
		table = newTab;
		size = 0;
		
		for (int i = 0; i < oldN; i++) {
			for (auto j = oldTab[i].begin(); j < oldTab[i].end(); j++) {
				Add(j->key, j->value);
			}
		}
		delete[] oldTab;
	}

	void FindElement(K key) {
		int hashed = Hash(key);

		if (table[hashed].size() != 0) {
			string toShow = "";
			for (auto i = table[hashed].begin(); i < table[hashed].end(); i++) {
				if (i->key == key) {
					if (i == table[hashed].begin()) {
						toShow += to_string(i->value);
					}
					else {
						toShow += ", " + to_string(i->value);
					}
				}
			}
			cout << toShow << endl;
		}

	}

	bool Exists(K key) {
		int hashed = Hash(key);

		if (table[hashed].size() != 0 && table[hashed].at(0).key == key) {
			return true;
		}
		else
			return false;
	}

	string ShowElements() {

		for(int j=0;j<N;j++){
			if (table[j].size() > 0) {

				string toShow = "";
				toShow += table[j].at(0).key;
				for (auto i = table[j].begin(); i < table[j].end(); i++) {
					if (i == table[j].begin()) 
						toShow +=" : "+ to_string(i->value);
					else
						toShow += " -> " + to_string(i->value);
				}
				cout << toShow << endl;
			}
		}

		return to_string(Elements());
	}

	int Elements() {
		return size;
	}


	void Stats() {
		int empty = 0;
		int max = 0;
		for (int i = 0; i < size; i++) {
			if (table[i].size() == 0)
				empty++;
			else if (table[i].size() > max)
				max = table[i].size();

		}

		cout << "Puste :" << empty << endl;
		cout << "Najdluzsze :" << max << endl;
	}

	bool Remove(K key) {
		int hashed = Hash(key);

		if (table[hashed].size() != 0 && table[hashed].at(0).key == key) {
			size -= table[hashed].size();

			table[hashed].clear();
			return true;
		}
		return false;

	}

	void Clear() {
		if (size > 0) {
			for (int i = 0; i < N; i++) {
				if (table[i].size() != 0) {
					table[i].clear();
				}
			}
			size = 0;
		}
	}

	
};

string RandomChar() {
	int r;
	string c;

	while (c.length() < 6) {
		r = rand() % 26;
		c += 'a' + r;
	}

	return c;
}

int RandomInt() {
	int r;
	r = rand() % 1000000;

	return r;
}



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));


	HashTable<string, int> * ht = new HashTable<string, int>();



	

	const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		int n = pow(10, o); // rozmiar danych
		// dodawanie do tablicy mieszajacej
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			ht->Add(RandomChar(), RandomInt());
		}


		clock_t t2 = clock();

		//ht->ShowElements();
		ht->Stats();

		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Dlugosc tablicy: " << ht->Elements() << endl;
		cout << "Czas wykonania: " << time << endl;

		const int m = pow(10, 4);
		int hits = 0;
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			if (ht->Exists(RandomChar())) // wyszukiwanie wg losowego klucza
				hits++;
		}
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Hits: " << hits << endl;
		cout << "Czas wykonania: " << time << endl;

		ht->Clear();//czyszczenie tablicy mieszajacej

		cout << endl;
	}

	delete ht;

}

