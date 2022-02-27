//Daniel Brzezicki,
//bd46477@zut.edu.pl,


#include "pch.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <cmath>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC


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
class Node
{
public:

	Node() {
		this->right = nullptr;
		this->left = nullptr;
	}

	void setData(T data) {
		this->data = data;
	}

	T& getData() {
		return data;
	}

	void setRight(Node<T> *right) { 
		this->right = right;
	}

	Node<T> * getRight() {
		return right;
	}

	void setLeft(Node<T> *left) {
		this->left = left;
	}

	Node<T> * getLeft() {
		return left;
	}

private:
	Node<T> * left;
	Node<T> * right;

	T data;

};

template<typename T>
class Binary_search_tree {
public:

	Binary_search_tree() {
		this->root = nullptr;
	}

	~Binary_search_tree() {
		Clear(root);
	}

	Node<T> * Add(Node<T> * node, T data) {

		if (node == nullptr) {
			Node<T> * tmp = new Node<T>();
			tmp->setData(data);
			n++;

			if (root == nullptr) {
				root = tmp;
			}
			return tmp;
		}

		if (node->getData() < data) {
			node->setRight(Add(node->getRight(), data));
		}
		else {
			node->setLeft(Add(node->getLeft(),  data));
		}

		return node;
	}

	void Clear(Node<T> * node) {
		if (node == nullptr) {
			return;
		}

		Clear(node->getLeft());
		Clear(node->getRight());


		delete node;
		if (root != nullptr) {
			root = nullptr;
			n = 0;
		}
	}

	Node<T> * FindElement(Node<T> * node,T data) {
		if (node == nullptr || node->getData() == data) {
			return node;
		}

		if (node->getData() > data) {
			return FindElement(node->getLeft(), data);
		}
		else {
			return FindElement(node->getRight(), data);
		}
	}


	Node<T> * FindMin(Node<T> * tmp) {
		T min = tmp->getData();

		while (tmp->getLeft() != nullptr) {
			tmp = tmp->getLeft();
		}

		return tmp;
	}




	Node<T> * Delete(Node<T> * node, T data) {
		if (node == nullptr) { 
			return node; 
		}

		if (node->getData() > data) {
			Node<T> * tmp = Delete(node->getLeft(), data);
			node->setLeft(tmp);
		}
		else if (node->getData() < data) {
			Node<T> * tmp = Delete(node->getRight(), data);
			node->setRight(tmp);
		}
		else {
			if (node->getLeft() == nullptr) {
				Node<T> * tmp = node->getRight();
				delete node;
				n--;
				return tmp;
			}
			else if (node->getRight() == nullptr) {
				Node<T> * tmp = node->getLeft();
				delete node;
				n--;
				return tmp;
			}
			Node<T> * tmp = FindMin(node->getRight());
			node->setData(tmp->getData());
			node->setRight(Delete(node->getRight(), tmp->getData()));
		}
		return node;
	}

	void Inorder(Node<T> * node)
	{
		if (node == nullptr) {
			return;
		}
		Inorder(node->getLeft());
		cout << node->getData() << endl;
		Inorder(node->getRight());
	}

	void Preorder(Node<T> * node)
	{
		if (node == nullptr) {
			return;
		}
		cout << node->getData() << endl;
		Preorder(node->getLeft());
		Preorder(node->getRight());
	}

	int CheckHeight() {
		Node<T> * tmp = nullptr;
		int heightMin = 1, heightMax = 1;

		if (root != nullptr) {
			tmp = root;
			while (tmp->getLeft() != nullptr) {
				tmp = tmp->getLeft();
				heightMin++;
			}

			tmp = root;
			while (tmp->getRight() != nullptr) {
				tmp = tmp->getRight();
				heightMax++;
			}

			if (heightMin < heightMax)
				height = heightMax;
			else
				height = heightMin;

			return height;
		}
		else
			return height = 0;

	}


	Node<T> * GetRoot() {
		return root;
	}


	string toString() const{
		ostringstream b;
		b << n << endl;
		return b.str();
	}

	int elements() {
		return n;
	}

private:
	int n;
	int height;

	Node<T> * root;
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



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*Binary_search_tree<int> tree;
	for (int i : {8, 4, 12, 2, 6, 10, 3, 5, 11}) {
		tree.Add(tree.GetRoot(), i);
	}

	tree.Delete(tree.GetRoot(), 5);

	tree.Inorder(tree.GetRoot());

	return 0;*/

	Binary_search_tree<someobject> * bst = new Binary_search_tree<someobject>();

	srand(time(NULL));



	someobject so;



	/*so.a = 'a';
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);

	cout << "Inorder" << endl;
	bst->Inorder(bst->GetRoot());

	cout << "Preorder" << endl;
	bst->Preorder(bst->GetRoot());

	cout << "Test" << endl;


	Node<someobject> * s = nullptr;
	s = bst->FindElement(so);
	cout << s->getData() << endl;


	cout << bst->toString() << endl;

	cout<<"Wysokosc: "<<bst->CheckHeight()<<endl;


	

	bst->Delete(bst->GetRoot(),so);

	bst->Inorder(bst->GetRoot());


	bst->Clear(bst->GetRoot());

	cout << "Wysokosc: " << bst->CheckHeight() << endl;

	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);
	so.i = RandomInt();
	bst->Add(bst->GetRoot(), so);


	cout << "Wysokosc: " << bst->CheckHeight() << endl;

	bst->Inorder(bst->GetRoot());

	bst->Clear(bst->GetRoot());*/

	const int MAX_ORDER = 6; // maksymalny rzad wielkosci dodawanych danych
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do drzewa
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			someobject so;
			so.a = RandomChar();
			so.i = RandomInt();
			bst->Add(bst->GetRoot(), so);
		}
		clock_t t2 = clock();

		//bst->Inorder(bst->GetRoot());
		double time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Wysokosc drzewa: " << bst->CheckHeight() << endl;
		cout << "Czas wykonania: " << time_per_element << endl;


		const int m = pow(10, 4);
		int hits = 0; // liczba trafien
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			someobject so;
			so.a = RandomChar();
			so.i = RandomInt();
			Node<someobject> * s = nullptr;
			s = bst->FindElement(bst->GetRoot(), so);
			if (s != nullptr)
				hits++;
		}
		t2 = clock();
		time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;

		cout << "Czas wykonania: " << time_per_element <<" z liczba trafien: "<< hits << endl;
		bst->Clear(bst->GetRoot());
	}
		
	delete bst;

}
