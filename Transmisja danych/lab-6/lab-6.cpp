// TDLabb6.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>

# define M_PI           3.14159265358979323846

using namespace std;

class bajt {
public:
	int bit[7] = { 0,0,0,0,0,0,0 };
};


bajt CreateBajt(string s) { //0 1 2 3 4 5 6 7 
	bajt b;
	b.bit[2] = s[0] - '0';
	b.bit[4] = s[1] - '0';
	b.bit[5] = s[2] - '0';
	b.bit[6] = s[3] - '0';
	return b;
}

void ShowBajt(bajt b) {
	for (int i = 0; i < 7; i++) {
		cout << b.bit[i];
	}
}

bajt Negate(bajt b, int bitToNegate) {
	if (b.bit[bitToNegate - 1] == 0)
		b.bit[bitToNegate - 1] = 1;
	else
		b.bit[bitToNegate - 1] = 0;
	return b;
}

void zad1(string str, bool negate, int bitToNegate) {
	bajt bajt = CreateBajt(str);

	cout << "Sygnal pocz." << endl;
	ShowBajt(bajt);

	cout << "\nSygnal parzystosci" << endl;
	bajt.bit[0] = (((bajt.bit[2] + bajt.bit[4]) % 2) + bajt.bit[6]) % 2;
	bajt.bit[1] = (((bajt.bit[2] + bajt.bit[5]) % 2) + bajt.bit[6]) % 2;
	bajt.bit[3] = (((bajt.bit[4] + bajt.bit[5]) % 2) + bajt.bit[6]) % 2;
	ShowBajt(bajt);

	cout << "\nSygnal z bitami parzystosci" << endl;
	if (negate)
		bajt = Negate(bajt, bitToNegate);
	ShowBajt(bajt);

	cout << "\nPo uwzglednieniu zanegowanego bitu" << endl;
	int x1d = (((bajt.bit[2] + bajt.bit[4]) % 2) + bajt.bit[6]) % 2;
	int x2d = (((bajt.bit[2] + bajt.bit[5]) % 2) + bajt.bit[6]) % 2;
	int x4d = (((bajt.bit[4] + bajt.bit[5]) % 2) + bajt.bit[6]) % 2;

	int x1daszek = (bajt.bit[0] + x1d) % 2;
	int x2daszek = (bajt.bit[1] + x2d) % 2;
	int x4daszek = (bajt.bit[3] + x4d) % 2;

	int s = x1daszek * 1 + x2daszek * 2 + x4daszek * 4;

	if (negate) {
		if (bajt.bit[s - 1] == 0)
			bajt.bit[s - 1] = 1;
		else
			bajt.bit[s - 1] = 0;
	}
	ShowBajt(bajt);
	if (s == 0) {
		cout << "\nTrue";
	}
	else {
		cout << "False";
	}
	cout << "\nS = " << s << endl;

}


void Zad2(string input) {
	Eigen::MatrixXd inp(1, 11);
	for (int i = 0; i < 11; i++) {
		inp(0, i) = input[i] - '0';
	}


	Eigen::MatrixXd bity(15,4);
	(bity << 
		0, 0, 0, 1,
		0, 0, 1, 0,
		0, 0, 1, 1,
		0, 1, 0, 0,
		0, 1, 0, 1,
		0, 1, 1, 0,
		0, 1, 1, 1,
		1, 0, 0, 0,
		1, 0, 0, 1,
		1, 0, 1, 0,
		1, 0, 1, 1,
		1, 1, 0, 0,
		1, 1, 0, 1,
		1, 1, 1, 0,
		1, 1, 1, 1).finished();
	cout << bity;
	cout << endl;
	

	Eigen::MatrixXd x1(11,1);
	(x1 << bity(2, 3), bity(4, 3), bity(5, 3), bity(6, 3), bity(8, 3), bity(9, 3), bity(10, 3), bity(11, 3), bity(12, 3), bity(13, 3), bity(14, 3)).finished();

	Eigen::MatrixXd x2(11, 1);
	(x2 << bity(2, 2), bity(4, 2), bity(5, 2), bity(6, 2), bity(8, 2), bity(9, 2), bity(10, 2), bity(11, 2), bity(12, 2), bity(13, 2), bity(14, 2)).finished();

	Eigen::MatrixXd x4(11, 1);
	(x4 << bity(2, 1), bity(4, 1), bity(5, 1), bity(6, 1), bity(8, 1), bity(9, 1), bity(10, 1), bity(11, 1), bity(12, 1), bity(13, 1), bity(14, 1)).finished();

	Eigen::MatrixXd x8(11, 1);
	(x8 << bity(2, 0), bity(4, 0), bity(5, 0), bity(6, 0), bity(8, 0), bity(9, 0), bity(10, 0), bity(11, 0), bity(12, 0), bity(13, 0), bity(14, 0)).finished();


	Eigen::MatrixXd P(11,4);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 11; j++) {
			if (i == 0)
				P(j, i) = x1(j);
			else if (i == 1)
				P(j, i) = x2(j);
			else if (i == 2)
				P(j, i) = x4(j);
			else if (i == 3)
				P(j, i) = x8(j);
		}
	}
	cout << endl;
	cout << P;
	Eigen::MatrixXd identity = Eigen::MatrixXd::Identity(11, 11);
	Eigen::MatrixXd G(P.rows(), P.cols() + identity.cols());
	G << P,identity;

	cout << endl;
	cout << G;

	cout << "\n" << endl;
	Eigen::MatrixXd s = inp * P;

	for (int i = 0; i < 4; i++) {
		s(0, i) = (int)s(0, i) % 2;
	}

	bool f=true;

	int x1d = (int)(s(0, 0) * 1);
	int x2d = (int)(s(0, 1) * 2);
	int x4d = (int)(s(0, 2) * 4);
	int x8d = (int)(s(0, 3) * 8);

	int S = x1d + x2d + x4d + x8d;



	if (S == 0) {
		cout << "\nTrue";
	}
	else {
		cout << "False";
		if (inp(0, S - 1) == 0)
			inp(0, S - 1) = 1;
		else
			inp(0, S - 1) = 0;
	}
	cout << "\nS = " << S << endl;
	cout << "\n" << inp;

}

int main()
{
	string str = "1101";
	int bitToNegate = 7;

	cout << "Przypadek 1:" << endl;
	zad1(str, false, bitToNegate);
	//cout << "\nPrzypadek 2:" << endl;
	//zad1(str, true, bitToNegate);

	Zad2("11010010101");
	Zad2("11010110101");
}