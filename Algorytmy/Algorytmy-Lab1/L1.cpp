//Daniel Brzezicki,
//bd46477@zut.edu.pl,




#include "pch.h"
#include <iostream>
#include <time.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


using namespace std;

template<typename T>
class wezel {
public:
	wezel() {
		this->prev = nullptr;
		this->next = nullptr;
	}

	wezel(const T& data) {
		this->data = data;
		this->prev = nullptr;
		this->next = nullptr;
	}

	void setData(T data) {
		this->data = data;
	}

	T& getData() { //Pobranie elementu
		return data;
	}

	void setPrevious(wezel<T> *previous) { //Zapisanie wskaznika na poprzedni elemnt
		this->prev = previous;
	}

	void setNext(wezel<T> *next) { //Zapisanie wskaznika na nastepny elemnt
		this->next = next;
	}

	wezel<T> * getPrevious() { //Pobranie wskaznika na poprzedni element
		return prev;
	}

	wezel<T> * getNext() {//Pobranie wskaznika na nastepny element
		return next;
	}

private:
	wezel<T> *prev, *next;
	T data;
};


template<typename T>
class lista {
public:
	lista() {
		this->head = nullptr;
		this->tail = nullptr;
		n=0;
	}

	~lista() {
		clear();
	}
	
	//a)
	void add(const T& dane) {
		wezel<T> *tmp = new wezel<T>(dane);
		if (head == nullptr) {	//Stworzenie glowy
			this->head = tmp;
			this->tail = tmp;
			//cout << "dodano glowe" << endl;
		}
		else {										//Dorzucenie kazdego kolejnego elementu

			this->tail->setPrevious(tmp);
			tmp->setNext(this->tail);
			this->tail = tmp;
			//cout << "dodano ogon" << endl;
		}
		this->n++;

	
	}


	//b)
	void addAtTheBeginning(const T& dane) {
		wezel<T> *tmp = new wezel<T>(dane);

		tmp->setPrevious(this->head);
		tmp->setNext(nullptr);
		this->head->setNext(tmp);

		this->head = tmp;

		
		this->n++;
	}

	//c)
	void delLast() {
		wezel<T> *tmp = nullptr;

		if(getTail()!=nullptr && getTail()->getNext()!=nullptr)
			tmp = tail->getNext();

		delete tail;


		this->n--;


		if (n <= 0) {
			//if (tmp != nullptr)
				//delete tmp;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else {
			this->tail = tmp;

			if (this->tail != nullptr)
				this->tail->setPrevious(nullptr);
		}

	}

	//d)
	void delFirst() {
		//if (n > 0) {
			wezel<T> *tmp = nullptr;

			if (getHead()!=nullptr && getHead()->getPrevious() != nullptr)
				tmp = getHead()->getPrevious();

			delete head;



			this->n--;

			if (n == 0) {
				//if (tmp != nullptr)
					//delete tmp;
				this->head = nullptr;
				this->tail = nullptr;
			}
			else {
				this->head = tmp;

				if (this->head != nullptr)
					this->head->setNext(nullptr);
			}
		//}
	}

	//e)
	T show(int index) {
		wezel<T> *tmp = nullptr;

		for (int i = 0; i < index+1; i++) {
			if (i == 0) {
				if(this->head != nullptr)
					tmp = this->head;
				else {
					throw out_of_range{ "Nie ma takiego elementu na liscie" };
				}
			}
			else {
				if (tmp->getPrevious() != nullptr)
					tmp = tmp->getPrevious();
				else {
					throw out_of_range{ "Nie ma takiego elementu na liscie" };
				}

			}
		}

		return tmp->getData();
	}

	//f)
	void findElementAndChange(int index, T data) {
		wezel<T> *tmp = nullptr;

		int counter = 0;
		for (auto i = this->head; i != nullptr; i = i->getPrevious()) {
			if (counter == index) {
				tmp = i;
			}
			counter++;
		}

		tmp->setData(data);
	}

	//g
	wezel<T> * findElement(T data) {
		for (auto i = this->head; i != nullptr; i = i->getPrevious()) {
			if (i->getData() ==data) {
				//cout << "Znaleziono element" << endl;
				return i;
			}
		}
		//cout << "nie znaleziono elementu" << endl;
		return nullptr;


	}
	
	
	//h 
	void findAndDel(T data) {
		wezel<T> *tmp = nullptr;
		wezel<T> *prev = nullptr;
		wezel<T> *next = nullptr;

		tmp = findElement(data);

		if (tmp != nullptr) {

			if (tmp->getPrevious() != nullptr) {
				prev = tmp->getPrevious();
			}

			if (tmp->getNext() != nullptr) {
				next = tmp->getNext();
			}

			if (next != nullptr) {
				next->setPrevious(prev);

			}

			if (prev != nullptr)
				prev->setNext(next);



			if (tmp->getData() == head->getData()) {
				this->head = prev;
			}

			if (tmp == tail) {
				this->tail = next;
			}


			delete tmp;

			n--;
		}


	}
	
	//i
	void addElementAt(T data, int index) {
		if (index < this->n) {
			wezel<T> *toAdd = new wezel<T>(data);
			wezel<T> *tmp = nullptr;
			wezel<T> *tmpToPrevious = nullptr;


			int counter = 0;
			for (auto i = this->head; i != nullptr; i = i->getPrevious()) {
				if (counter == index) {
					tmp = i;
				}
				counter++;
			}

			if (tmp->getPrevious() != nullptr) {
				tmpToPrevious = tmp->getPrevious();

				tmp->setPrevious(toAdd);

				tmpToPrevious->setNext(toAdd);
				toAdd->setNext(tmp);
				toAdd->setPrevious(tmpToPrevious);
				toAdd->setData(data);
			}
			else {
				tmp->setPrevious(toAdd);
				toAdd->setNext(tmp);
				toAdd->setData(data);
				this->tail = toAdd;
			}
			n++;

		}
	}

	//j
	void clear() {
		int size = n;
		for (int i = 0; i < size ; i++) {
			delFirst();
		}

	}


	//k
	int toString() {

		return n;
	}


	wezel<T> * getHead() {
		return this->head;
	}

	wezel<T> * getTail() {
		return this->tail;
	}

private:
	wezel<T> *head, *tail;
	int n = 0;
};



struct some_object {
	int f1;
	char f2;

	bool operator==(const some_object &other) const
	{
		return (f1 == other.f1 && f2 == other.f2);
	}
};


void ShowList(lista<some_object> *l) {
	some_object so;
	cout <<"Lista: "<< endl;
	if (l->getHead() != nullptr) {
		for (auto i = l->getHead(); i != nullptr; i = i->getPrevious()) {
			so = i->getData();
			cout << "" << so.f1 << " " << so.f2 << endl;
		}
	}
	else 
		cout << "Lista jest pusta " << endl;
	cout << endl;
}

char RandomChar() {
	int r;
	char c;
	r = rand() % 26;
	c = 'a' + r;

	return c;
}

int RandomInt() {
	int r;
	r = rand() % 10000;

	return r;
}


int main()
{

	srand(time(NULL));    // initialize the random number generator

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	lista<some_object>*ll = new lista<some_object>();
	some_object so;


	//Test A - dodanie elementow
	cout << "TEST A" << endl;

	clock_t t1 = clock();

	so.f1 = 123;
	so.f2 = 'a';
	ll->add(so);


	so.f1 = 2115;
	so.f2 = 'b';
	ll->add(so);


	so.f1 = 2222;
	so.f2 = 'c';
	ll->add(so);


	so.f1 = 444;
	so.f2 = 'f';
	ll->add(so);

	clock_t t2 = clock();
	double time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania 4x add(): " << time << endl;


	//test B
	cout << "\nTEST B" << endl;

	t1 = clock();

	ShowList(ll);

	so.f1 = 123123;
	so.f2 = 'g';
	ll->addAtTheBeginning(so);


	ShowList(ll);

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania addAtTheBeginning() + sprawdzenie: " << time << endl;



	//Test C
	cout << "\nTEST C" << endl;


	ShowList(ll);

	t1 = clock();

	ll->delLast();

	ShowList(ll);



	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania delLast() + sprawdzenie: " << time << endl;

	//Test D
	cout << "\nTEST D" << endl;

	t1 = clock();

	ShowList(ll);

	ll->delFirst();

	ShowList(ll);

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania delFirst() + sprawdzenie: " << time << endl;

	//Test E
	cout << "\nTEST E" << endl;

	t1 = clock();

	so = ll->show(0);
	cout << "Element o indeksie 0: " << so.f1 << " " << so.f2 << endl;

	so = ll->show(1);
	cout << "Element o indeksie 1: " << so.f1 << " " << so.f2 << endl;

	//so = ll->show(2);
	//cout << "Element o indeksie 2: " << so.f1 << " " << so.f2 << endl;

	//so = ll->show(3);
	//cout << "Element o indeksie 3: " << so.f1 << " " << so.f2 << endl;

	//Blad outofrange
	//so = ll->show(5);
	//cout << "Element o indeksie 5: " << so.f1 << " " << so.f2 << endl;

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania 4x show() + sprawdzenie: " << time << endl;

	//Test F
	cout << "\nTEST F" << endl;

	t1 = clock();

	ShowList(ll);

	ll->findElementAndChange(0, so);

	ShowList(ll);

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania findElementAndChange() + sprawdzenie: " << time << endl;


	//Test G
	cout << "\nTEST G" << endl;

	t1 = clock();

	//so = ll->getHead()->getData();
	some_object so1;
	so1.f1 = 2222;
	so1.f2 = 'c';


	ll->findElement(so1);

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania findElement() + sprawdzenie: " << time << endl;


	//Test H
	cout << "\nTEST H" << endl;

	t1 = clock();
	ShowList(ll);

	cout << "Elementow na liscie: " << ll->toString() << endl;
	ll->delFirst();
	ll->delFirst();

	ll->findAndDel(so1);

	ShowList(ll);
	cout << "Elementow na liscie: " << ll->toString() << endl;

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania findAndDel() + sprawdzenie: " << time << endl;


	//Test I
	cout << "\nTEST I" << endl;

	//t1 = clock();

	ShowList(ll);


	//ll->addElementAt(so, 1);
	cout << "Dodanie elementu" << endl;

	ShowList(ll);

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania addElementAt() + sprawdzenie: " << time << endl;

	//Test J
	cout << "\nTEST J" << endl;
	t1 = clock();

	//ll->clear();

	t2 = clock();
	time = (t2 - t1) / (double)CLOCKS_PER_SEC;	cout << "Czas wykonania clear(): " << time << endl;	ShowList(ll);	//Test K
	cout << "\nTEST K" << endl;
	cout << ll->toString() << endl;
	
	so.f1 = 1;
	so.f2 = 'a';


	const int MAX_ORDER = 6; 
	for (int o = 1; o <= MAX_ORDER; o++) 
	{
		const int n = pow(10, o); 

		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			so.f1 = RandomInt();
			so.f2 = RandomChar();

			ll->add(so);
		}
		clock_t t2 = clock();

		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas wykonania: " << time << endl;

		cout << ll->toString() << endl;

		const int m = pow(10, 4); 


		t1 = clock();


		for (int i = 0; i < m; i++) {
			so.f1 = RandomInt();
			so.f2 = RandomChar();

			ll->findAndDel(so);
		}
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas wykonania: " << time << endl;


		cout << ll->toString() << endl;
		ll->clear();

	}

	
	delete ll;
}