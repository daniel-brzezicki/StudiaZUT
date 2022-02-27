//Daniel Brzezicki,
//bd46477@zut.edu.pl,

#include "pch.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <crtdbg.h>
#include <time.h>
#include <cmath>


using namespace std;


struct someobject {
	char a;
	int i;

	bool operator<(const someobject &other) const
	{
		return (i < other.i);
	}

	bool operator<=(const someobject &other) const
	{
		return (i <= other.i);
	}

	bool operator>=(const someobject &other) const
	{
		return (i >= other.i);
	}

	bool operator>(const someobject &other) const
	{
		return (i > other.i);
	}

	bool operator==(const someobject &other) const
	{
		return (i == other.i && a == other.a);
	}

	bool operator!=(const someobject &other) const
	{
		return (i != other.i || a != other.a);
	}


};

ostream& operator<<(ostream& strumien_wy, someobject& so)
{
	strumien_wy << so.a << " " << so.i;
	return strumien_wy;
}





template<typename T>
class binaryHeap {
public:

	~binaryHeap() {
		Clear();
	}

	void Add(T data, bool (*compare)(const T &, const T &)) {
		heap.push_back(data);
		restoreUp(heap.size() - 1,compare);
	}


	void DeleteRoot(bool(*compare)(const T &, const T &)) {
		if (heap.size() > 0) {
			heap[0] = heap.at(heap.size() - 1);
			heap.pop_back();
			restoreDown(0, compare);
		}
	}

	void Clear() {
		heap.clear();
	}

	int Elements() {
		return heap.size();
	}

	string To_string() {
		string s;

		for (int i = 0; i < heap.size(); i++) {
			cout<<heap[i]<< " ";
		}


		return s;
	}

	const T & getRoot() const {
		return heap[0];
	}

private:
	vector<T> heap;



	int getParentIndex(int childIndex) {
		int parent = (childIndex - 1) / 2;
		if (childIndex != 0)
			return parent;
		else
			return -1;
	}

	int getRightIndex(int parentIndex) {
		int left = 2 * parentIndex + 1;
		if (left < heap.size())
			return left;
		else
			return -1;

	}


	int getLeftIndex(int parentIndex) {
		int right = 2 * parentIndex + 2;
		if (right < heap.size())
			return right;
		else
			return -1;
	}


	void restoreUp(int index, bool(*compare)(const T &, const T &)) {
		if (index >= 0 && getParentIndex(index) >= 0 && compare(heap[getParentIndex(index)], heap[index]))
		{
			T tmp = heap[index];
			heap[index] = heap[getParentIndex(index)];
			heap[getParentIndex(index)] = tmp;
			restoreUp(getParentIndex(index), compare);
		}
	}

	void restoreDown(int index, bool(*compare)(const T &, const T &)) {
		int leftChildIndex = getLeftIndex(index);
		int rightChildIndex = getRightIndex(index);

		if (leftChildIndex >= 0 && rightChildIndex >= 0 && compare(heap[leftChildIndex], heap[rightChildIndex])){
			leftChildIndex = rightChildIndex;
		}

		if (leftChildIndex > 0 && compare(heap[index], heap[leftChildIndex])){
				T tmp = heap[index];
				heap[index] = heap[leftChildIndex];
				heap[leftChildIndex] = tmp;
				restoreDown(leftChildIndex, compare);
		}
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
	r = rand() % 1000000;

	return r;
}


bool c(const someobject &data1, const someobject &data2) {
	return data1 < data2;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));
	someobject so;


	/*binaryHeap<someobject> b;

	for (int i = 0; i < 7; i++) {
		so.i = i;
		b.Add(so,c);
	}


	b.To_string();

	cout << endl;

	//b.DeleteRoot(c);
	while (b.Elements() > 0) {
		cout << b.getRoot().i << endl;
		b.DeleteRoot(c);
	}

	return 0;*/

	binaryHeap<someobject> * bh = new binaryHeap<someobject>();





	const int MAX_ORDER = 1; // maksymalny rzad wielkosci dodawanych danych
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do kopca
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			so.a = RandomChar();
			so.i = RandomInt();
			bh->Add(so,c);
		}
		clock_t t2 = clock();

		double time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Elementow w kopcu: " << bh->Elements() << ". Czas wykonania: " << time_per_element << endl;


		t1 = clock();
		for (int i = 0; i < n; i++) {
			
			cout<<bh->getRoot().i<<endl;
			bh->DeleteRoot(c);
		}
		t2 = clock();

		time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Elementow w kopcu: " << bh->Elements() << ". Czas wykonania: " << time_per_element << endl;

		bh->Clear();
	}

	delete bh;
	return 0;
}
