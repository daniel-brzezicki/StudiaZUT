#include "pch.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <crtdbg.h>
#include <sstream>

#define _CRTDBG_MAP_ALLOC

using namespace std;

template<typename T>
class dynamic_arr {
public:
	dynamic_arr() {
		this->max = 1;
		this->list = new T[max];
	}

	~dynamic_arr() {
		clear();
	}

	void add(T data) {
		if (n < max) {
			list[n] = data;
			n++;
		}
		else
		{
			this->max = this->max * 2;
			T * tmp;
			tmp = list;
			this->list = new T[this->max];
			for (int i = 0; i < n; i++) {
				list[i] = tmp[i];
			}


			list[n] = data;
			n++;

			delete[] tmp;
		}
	}

	T at(int index) {
		if (index < n && index >= 0)
			return list[index];
		else
			throw out_of_range{ "Nie ma takiego elementu na liscie" };
	}

	void change(int index, T data) {
		if (index < n && index >= 0)
			list[index] = data;
		else
			throw out_of_range{ "Nie ma takiego elementu na liscie" };
	}

	void clear() {
		delete[] list;
		n = 0;
		max = 0;
	}

	int elements() {
		return n;
	}

	void boubleSort() {
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < n; j++) {

				if (list[j] < list[j - 1]) {
					T temp;
					temp = list[j];
					list[j] = list[j - 1];
					list[j - 1] = temp;
				}
			}
		}
	}

	char toString() {
		return n ;
	}

	string display() const{
		ostringstream oss;

		for (int i = 0; i < n; i++) {
			oss<<list[i];

		}
		return oss.str();
	}

	//friend ostream& operator<<(ostream& strumien_wy, someobject& o);

private:

	T * list;
	size_t n = 0, max;

};

/*std::ostream& operator<< (std::ostream& out, const someobject &obj)
{
	out << obj.i;
	return out;
}*/


struct someobject{
	char a;
	int i;

	bool operator<(const someobject &other) const
	{
		return (i < other.i);
	}

	bool operator>(const someobject &other) const
	{
		return (i > other.i);
	}


};



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

//template<typename T>
void DisplayList(dynamic_arr<someobject> * list) {
	someobject so;
	for (int i = 0; i < list->elements(); i++) {
		so = list->at(i);
		cout << so.a << " " << so.i << endl;
	}
}


int main()
{
	dynamic_arr<int> datest;
	datest.add(1);
	datest.clear();

	datest.add(2);
	//DisplayList(&a);
	cout << datest.display() << endl;
	return 0;


	/*srand(time(NULL));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	dynamic_arr<someobject> *da = new dynamic_arr<someobject>();
	someobject so;
	so.a = 'a';*/

	/*for (int i = 0; i < 85; i++) {
		so.i = RandomInt();
		da->add(so);
	}

	DisplayList(da);

	cout << endl;
	da->boubleSort();

	DisplayList(da);*/

	//printf("%d", da->toString());
	//cout << da->toString() << endl;

	/*const int order = 7;
	const int n = pow(10, order); 


	clock_t t1 = clock();
	double max_time_per_element = 0.0;

	for (int i = 0; i < n; i++) {
		clock_t t1_element = clock();

		so.i = RandomInt();
		da->add(so);

		clock_t t2_element = clock();
		double time_per_element = (t2_element - t1_element) / (double)CLOCKS_PER_SEC;
		if (time_per_element > max_time_per_element)
		{
			max_time_per_element = time_per_element;
			cout << "Nowy najgorszy czas dodania elementu: " << time_per_element << endl;
		}
	}


	clock_t t2 = clock();


	double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Czas calej operacji: " << time << endl;

	da->clear();

	delete da;*/

}

