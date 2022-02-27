
#include "pch.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <crtdbg.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <list>

using namespace std;







template<typename T>
class binaryHeap {
public:

	binaryHeap() {
	}

	~binaryHeap() {
		Clear();
	}

	void Add(T data, bool(*compare)(const T &, const T &)) {
		heap.push_back(data);
		restoreUp(heap.size() - 1, compare);
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

	string To_string(int num) {
		string s;

		if (num == 0) {
			for (int i = 0; i < heap.size(); i++) {
				cout << heap[i] << " ";
			}
		}
		else {
			for (int i = 0; i < num; i++) {
				cout << heap[i] << " ";
			}
		}



		return s;
	}

	const T & getRoot() const {
		return heap[0];
	}

	void sort(vector<T> & tab, bool(*compare)(const T &, const T &)) {
		heap = move(tab);
		//heap = tab;


		for (int i = heap.size() / 2 - 1; i >= 0; i--) {
			restore(i, heap.size(), compare);
		}


		for (int i = heap.size() - 1; i > 0; i--) {
			T data = heap[0];
			heap[0] = heap[i];
			heap[i] = data;
			restore(0, i, compare);
		}

		tab = move(heap);
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

		if (leftChildIndex >= 0 && rightChildIndex >= 0 && compare(heap[leftChildIndex], heap[rightChildIndex])) {
			leftChildIndex = rightChildIndex;
		}

		if (leftChildIndex > 0 && compare(heap[index], heap[leftChildIndex])) {
			T tmp = heap[index];
			heap[index] = heap[leftChildIndex];
			heap[leftChildIndex] = tmp;
			restoreDown(leftChildIndex, compare);
		}
	}



	void restore(int index, int size, bool(*compare)(const T &, const T &)) {
		int leftChildIndex = getLeftIndex(index);
		int rightChildIndex = getRightIndex(index);
		int root = index;

		if (leftChildIndex >= 0 && size > leftChildIndex && compare(heap[leftChildIndex], heap[root])) {
			root = leftChildIndex;
		}

		if (rightChildIndex >= 0 && size > rightChildIndex && compare(heap[rightChildIndex], heap[root])) {
			root = rightChildIndex;
		}

		if (root != index) {
			T tmp = heap[index];
			heap[index] = heap[root];
			heap[root] = tmp;
			restore(root, size, compare);
		}
	}

};

template<typename T>
class countingSort {
public:

	countingSort() {
	}

	~countingSort() {
		v.clear();
	}

	string To_string(int num) {
		string s;

		if (num == 0) {
			for (int i = 0; i < v.size(); i++) {
				cout << v[i] << " ";
			}
		}
		else {
			for (int i = 0; i < num; i++) {
				cout << v[i] << " ";
			}
		}


		return s;
	}

	void sort(vector<T> & tab) {
		v = tab;
		findMin(); findMax();

		int size = max - min + 1;


		vector<int> count;
		for (int i = 0; i < size; i++) {
			count.push_back(0);
		}

		for (int i = 0; i < v.size(); i++) {
			count[v[i] - min]++;
		}

		int index = 0;
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < count[i]; j++) {
				v[index++] = i + min;
			}
		}

		tab = v;
	}

private:
	vector<T> v;
	int min, max;

	void findMin() {
		min = v[0];
		for (int i = 0; i < v.size(); i++) {
			if (v[i] < min) {
				min = v[i];
			}
		}
	}

	void findMax() {
		max = v[0];
		for (int i = 0; i < v.size(); i++) {
			if (v[i] > max) {
				max = v[i];
			}
		}
	}


};

template<typename T>
class bucketSort {
public:

	bucketSort() {

	}

	~bucketSort() {
		v.clear();
	}

	string To_string(int num) {
		string s;

		if (num == 0) {
			for (int i = 0; i < v.size(); i++) {
				cout << v[i] << " ";
			}
		}
		else {
			for (int i = 0; i < num; i++) {
				cout << v[i] << " ";
			}
		}



		return s;
	}

	void sort(vector<T> & tab) {
		v = tab;
		findMax();
		findMin();


		vector<vector<int>> buckets;



		for (int i = 0; i < max - min + 1; i++) {
			vector<int> vec;
			buckets.push_back(vec);
		}

		int div = ceil((max) / v.size()) + 1;
		for (int i = 0; i < v.size(); i++) {
			int whichBucket = floor(v[i] / div);
			buckets[whichBucket].push_back(v[i]);
		}

		for (int i = 0; i < max - min + 1; i++) {
			std::sort(buckets[i].begin(), buckets[i].end(), greater<int>());
		}

		int index = 0;
		for (int i = max - min; i >= 0; i--) {
			for (int j = 0; j < buckets[i].size(); j++) {
				v[index++] = buckets[i][j];
			}
		}

		tab = v;
	}

	void sortObjects(vector<T> & tab) {
		v = tab;
		findMaxObj();
		findMinObj();


		vector<vector<T>> buckets;



		for (int i = 0; i < max - min + 1; i++) {
			vector<T> vec;
			buckets.push_back(vec);
		}

		int div = ceil((max) / v.size()) + 1;
		for (int i = 0; i < v.size(); i++) {
			int whichBucket = floor(v[i].i / div);
			buckets[whichBucket].push_back(v[i]);
		}

		for (int i = 0; i < max - min + 1; i++) {
			std::sort(buckets[i].begin(), buckets[i].end(), greater<T>());
		}

		int index = 0;
		for (int i = max - min; i >= 0; i--) {
			for (int j = 0; j < buckets[i].size(); j++) {
				v[index++] = buckets[i][j];
			}
		}

		tab = v;
	}


private:
	vector<T> v;
	int min, max;



	void findMin() {
		min = v[0];
		for (int i = 0; i < v.size(); i++) {
			if (v[i] < min) {
				min = v[i];
			}
		}
	}

	void findMax() {
		max = v[0];
		for (int i = 0; i < v.size(); i++) {
			if (v[i] > max) {
				max = v[i];
			}
		}
	}

	void findMinObj() {
		min = v[0].i;
		for (int i = 0; i < v.size(); i++) {
			if (v[i] < min) {
				min = v[i].i;
			}
		}
	}
	void findMaxObj() {
		max = v[0].i;
		for (int i = 0; i < v.size(); i++) {
			if (v[i] > max) {
				max = v[i].i;
			}
		}
	}

};


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

	int operator/(const int &other) const {
		return i / other;
	}


	bool operator>(const int &other) const
	{
		return (i > other);
	}

	bool operator<(const int &other) const
	{
		return (i < other);
	}

	//int& operator=(int &other, someobject &so) {
	//	return other = so.i;
	//}
};

ostream& operator<<(ostream& strumien_wy, someobject& so)
{
	strumien_wy << so.a << " " << so.i;
	return strumien_wy;
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
	r = rand() % 1000000;

	return r;
}


bool c(const int &data1, const int &data2) {
	return data1 < data2;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));

	/*someobject s;

	int so;

	//vector<int> tab;
	vector<someobject> tab;
	s.i = 12;
	tab.push_back(s);
	s.i = 11;
	tab.push_back(s);
	s.i = 13;
	tab.push_back(s);
	s.i = 5;
	tab.push_back(s);
	s.i = 6;
	tab.push_back(s);
	s.i = 7;
	tab.push_back(s);
	s.i = 71;
	tab.push_back(s);
	s.i = 15;
	tab.push_back(s);
	s.i = 72;
	tab.push_back(s);


	bucketSort<someobject> *bs = new bucketSort<someobject>();
	bs->sortObjects(tab);

	delete bs;
	for (int i = 0; i < tab.size(); i++) {
		cout << tab[i] << " ";
	}


	return 0;*/

	const int MAX_ORDER = 7; // maksymalny rzad wielkosci sortowanych danych
	const int m = (int)pow(10, 7); // sortowane liczby ze zbioru {0 , ... , m - 1}
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = (int)pow(10, o); // rozmiar tablicy z danymi
		vector<int> array1;
		for (int i = 0; i < n; i++)
		{
			int rand_val = RandomInt(); // tu losowanie liczby calkowitej
			array1.push_back(rand_val);
		}

		cout << endl;

		for (int i = 0; i < 10; i++) {
			//cout << array1[i] << " ";
		}


		vector<int> array2 = array1; // pierwsza kopia
		vector<int> array3 = array1; // druga kopia


		countingSort<int> *cs = new countingSort<int>();


		clock_t t1 = clock();
		cs->sort(array1);
		clock_t t2 = clock();
		double time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "\nCzas sortowania przez zliczanie: " << time_per_element << " dla " << n << endl;
		//cout << "CountingSort" << cs->To_string(10);


		binaryHeap<int> *b = new binaryHeap<int>();
		t1 = clock();
		b->sort(array2, c);
		t2 = clock();
		time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "\nCzas sortowania przez kopcowanie: " << time_per_element << " dla " << n << endl;
		//cout << "HeapSort" << b->To_string(10);


		bucketSort<int> *bs = new bucketSort<int>();
		t1 = clock();
		bs->sort(array3);
		t2 = clock();
		time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "\nCzas sortowania kubelkowego: " << time_per_element << " dla " << n << endl;
		//cout << "BucketSort" << bs->To_string(10);

		cout << endl;

		if (array1 == array2 && array2 == array3 && array1 == array3)
			cout << "Tablice sa identyczne" << endl;
		else
			cout << "Tablice sa rozne" << endl;




		// wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		// sprawdzenie zgodnosci tablic array1 , array2 , array3 i wypis informacji o zgodnosci na ekran
		array1.clear();
		array2.clear();
		array3.clear();
		delete b;
		delete cs;
		delete bs;
	}
	return 0;
}