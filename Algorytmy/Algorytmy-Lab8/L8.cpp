//Daniel Brzezicki,
//bd46477@zut.edu.pl,

#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
#include <algorithm> 


using namespace std;

class Point {
public:
	int id;
	float x, y;
};


float odleglosc(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int zakret(Point a, Point b, Point c) {
	float k = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (k > 0)
		return -1;
	else if (k < 0)
		return 1;
	return 0;
}

Point p;
bool c(Point a, Point b) {
	int z = zakret(p, a, b);
	if (z == 0) {
		if (odleglosc(p, a) < odleglosc(p, b))
			return true;
		else
			return false;
	}
	if (z == -1)
		return true;
	else
		return false;
}

void show(vector<Point> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].id<<"  ";
	}

	cout << "\n" << endl;
}

vector<Point> graham(vector<Point> &points) {
	vector<Point> otoczka;


	clock_t t1 = clock();

	for (int i = 1; i < points.size(); i++) {
		if (points[i].y < points[0].y) {
			swap(points[0], points[i]);
		}
		else if (points[i].y == points[0].y && points[i].x < points[0].x) {
			swap(points[0], points[i]);
		}
	}

	p = points[0];
	sort(points.begin()+1, points.end(), c);

	clock_t t2 = clock();
	double time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "\nCzas posortowania: " << time_per_element;
	cout << "\nIndex pierwszego elementu: " << p.id;

	t1 = clock();

	for (int i = 0; i < 3; i++) {
		otoczka.push_back(points[i]);
	}

	for (int i = 3; i < points.size(); i++) {
		Point temp = otoczka[otoczka.size() - 1];
		otoczka.pop_back();
		while (zakret(otoczka[otoczka.size() - 1], temp, points[i]) != -1) {
			temp = otoczka[otoczka.size() - 1];
			otoczka.pop_back();
		}
		otoczka.push_back(temp);
		otoczka.push_back(points[i]);
	}

	t2 = clock();
	time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "\nCzas dzialania algorytmu: " << time_per_element;

	return otoczka;
}

void program(string fileName) {
	vector<Point> points;
	ifstream inFile;
	float x, y;

	inFile.open(fileName);
	if (!inFile) {
		cout << "unable to open" << endl;
		exit(1);
	}
	inFile.ignore(numeric_limits<streamsize>::max(), '\n');

	Point p;
	int i = 0;
	while (!inFile.eof()) {
		inFile >> p.x >> p.y;
		p.id = i;
		i++;
		points.push_back(p);
	}

	cout << "Ilosc elementow: " << points.size();
	vector<Point> otoczka = graham(points);
	cout << "\nPunkty tworzace wypukla otoczke: "<< otoczka.size() << endl;
	show(otoczka);
	points.clear();
}

int main() {
	//program("points1.txt");
	//program("points2.txt");
	//program("points3.txt");
	//program("points4.txt");
	//program("points5.txt");
	program("points6.txt");
	return 0;
}
