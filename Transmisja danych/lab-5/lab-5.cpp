// lab-5TD.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <string>
#include <vector>
#include <cmath>

# define M_PI           3.14159265358979323846

using namespace std;

double fs;

class bajt {
public:
	int bit[7];
};

vector<bajt> CSTB(string s) {
	vector<bajt> binaryString;

	for (int i = 0; i < s.length(); i++) {
		bajt b;
		for (int j = 0; j < 7; j++) {
			b.bit[j] = s[i] % 2;
			s[i] = s[i] / 2;
		}

		bajt helper = b;
		for (int j = 6; j >= 0; j--) {
			b.bit[6 - j] = helper.bit[j];
		}
		binaryString.push_back(b);
	}

	return binaryString;
}

void generatePNG(vector<double> x, vector<double> y, string fileName) {
	RGBABitmapImageReference * img = CreateRGBABitmapImageReference();
	DrawScatterPlot(img, 600, 400, &x, &y);

	vector<double> *png = ConvertToPNG(img->image);
	WriteToFile(png, fileName);
	DeleteImage(img->image);
}

vector<double> Modules(vector<double> Xre, vector<double> Xim) {

	int n = Xre.size();
	vector<double> mo;
	for (int i = 0; i < n; i++) {
		mo.push_back(0);
	}

	for (int i = 0; i < n; i++) {
		mo[i] = sqrt(pow(Xre[i], 2) + pow(Xim[i], 2));
	}

	return mo;
}

void WartosciModulow(vector<double> Xre, vector<double> Xim, string fileName) {
	int N = Xre.size();
	vector<double> wartosci = Modules(Xre, Xim);
	vector<double> newWart;
	vector<double> indeksy;


	for (int k = 0; k < N / 2; k++) {
		indeksy.push_back(k*(fs / N));

		newWart.push_back(10 * log10(wartosci[k]));
	}

	generatePNG(indeksy, newWart, fileName);
}

void DFT(vector<double> x, string fileName) {
	int N = x.size();

	int n, k;
	vector<double> Xre;
	vector<double> Xim;

	for (int i = 0; i < N; i++) {
		Xre.push_back(0);
		Xim.push_back(0);
	}


	for (k = 0; k < N; ++k)
	{
		Xre[k] = 0;
		for (n = 0; n < N; ++n) {
			Xre[k] += x[n] * cos(n * k * 2 * M_PI / N);
		}

		Xim[k] = 0;
		for (n = 0; n < N; ++n) {
			Xim[k] -= x[n] * sin(n * k * 2 * M_PI / N);
		}
	}

	WartosciModulow(Xre, Xim, fileName);
}

void expand(vector<bajt>binary, int N, float A1, float A2, float fn, float ts) {
	vector<double> tab;
	vector<double>x;
	vector<double>y;

	for (int i = 0; i < binary.size(); i++) {
		for (int j = 0; j < 8; j++) {
			tab.push_back(binary[i].bit[j]);
		}
	}



	for (int i = 0; i < N; i++) {
		x.push_back(i * ts);
		if (tab[floor(x[i])] == 0)
			y.push_back(0);
		else
			y.push_back(1);
	}

	generatePNG(x, y, "expand.png");
}


void SignalToBits(vector<double> c_t,int N, double tc) {
	vector<double> ciag;
	double ones = 0;
	double zeros = 0;

	int a = floor(N / tc);

	int counter = 0;
	for (int i = 0; i < c_t.size(); i++) {
		counter = i;
		counter++;
		if (counter % 1000 == 0) {
			if (zeros > ones) {
				ciag.push_back(0);
			}
			else {
				ciag.push_back(1);
			}
			counter = 0;
			zeros = 0;
			ones = 0;
		}
		else {
			if (c_t[i] == 0)
				zeros++;
			else if(c_t[i]==1)
				ones++;
		}
	}

	cout << "Bity odczytane:  ";
	for (int i = 0; i < ciag.size(); i++) {
		std::cout << ciag[i];
	}
	cout << endl;
}

void ask(vector<bajt>binary, int N, float A1, float A2, float fn, float ts) {
	vector<double> tab;
	vector<double> x;
	vector<double> y;
	

	for (int i = 0; i < binary.size(); i++) {
		for (int j = 0; j < 7; j++) {
			tab.push_back(binary[i].bit[j]);
		}
	}



	for (int i = 0; i < N; i++) {
		x.push_back(i * ts);

		if (tab[floor(x[i])] == 0)
			y.push_back(0);//y.push_back(A1*sin(2 * M_PI*fn*x[i]));
		else
			y.push_back(A2*sin(2 * M_PI*fn*x[i]));

	}


	//x_t
	vector<double> x_t(N);
	int A = 13;
	for (int i = 0; i < N; i++) {
		double t = i / fs;
		x_t[i] = (A * sin(2 * M_PI*fn*t)) * y[i];
	}

	
	//p_t
	vector<double> p_t;
	double a = 0;
	int p = 1;
	for (int i = 0; i < N; i++) {
		a += x_t[i];
		double t = i / fs;
		if (x[i] >= p) {
			a = 0;
			p++;
		}
		//p_t[i] = a;
		p_t.push_back(a);
	}

	//c_t
	int h=0;
	vector<double> c_t;
	for (int i = 0; i < N; i++) {
		if (p_t[i] > h)
			c_t.push_back(1);
		else
			c_t.push_back(0);
	}

	SignalToBits(c_t, N,ts);

	generatePNG(x, y, "ask.png");
	generatePNG(x, x_t, "askxt.png");
	generatePNG(x, p_t, "askpt.png");
	generatePNG(x, c_t, "askct.png");
	//DFT(y, "askDFT.png");
}


void psk(vector<bajt>binary, int N, float fn, float ts) {
	vector<double> tab;
	vector<double>x;
	vector<double>y;

	for (int i = 0; i < binary.size(); i++) {
		for (int j = 0; j < 7; j++) {
			tab.push_back(binary[i].bit[j]);
		}
	}



	for (int i = 0; i < N; i++) {
		x.push_back(i * ts);

		if (tab[floor(x[i])] == 0)
			y.push_back(sin(2 * M_PI*fn*x[i]));
		else
			y.push_back(sin(2 * M_PI*fn*x[i] + M_PI));

	}

	//x_t
	vector<double> x_t(N);
	int A = 13;
	for (int i = 0; i < N; i++) {
		double t = i / fs;
		x_t[i] = (A * sin(2 * M_PI*fn*t)) * y[i];
	}


	//p_t
	vector<double> p_t(N);
	double a = 0;
	int p = 1;
	for (int i = 0; i < N; i++) {
		a += x_t[i];
		double t = i / fs;
		if (x[i] >= p) {
			a = 0;
			p++;
		}
		p_t[i] = a;
	}

	//c_t
	vector<double> c_t;
	for (int i = 0; i < N; i++) {
		if (p_t[i] < 0)
			c_t.push_back(1);
		else
			c_t.push_back(0);
	}

	SignalToBits(c_t, N, ts);

	generatePNG(x,y, "psk.png");
	generatePNG(x, x_t, "pskxt.png");
	generatePNG(x, p_t, "pskpt.png");
	generatePNG(x, c_t, "pskct.png");
	//DFT(y, "pskDFT.png");
}

void fsk(vector<bajt>binary, double N, float fn1, float fn2, float ts) {
	vector<double> tab;
	vector<double>x;
	vector<double>y;

	for (int i = 0; i < binary.size(); i++) {
		for (int j = 0; j < 7; j++) {
			tab.push_back(binary[i].bit[j]);
		}
	}



	for (int i = 0; i < N; i++) {
		x.push_back(i * ts);

		if (tab[floor(x[i])] == 0)
			y.push_back(sin(2 * M_PI*fn1*x[i]));
		else
			y.push_back(sin(2 * M_PI*fn2*x[i]));
	}

	//x_t
	vector<double> x1_t(N);
	vector<double> x2_t(N);
	int A = 13;
	for (int i = 0; i < N; i++) {
		double t = i / fs;
		x1_t[i] = (A * sin(2 * M_PI*fn1*t)) * y[i];
		x2_t[i] = (A * sin(2 * M_PI*fn1*t)) * y[i];
	}


	//p_t
	vector<double> p1_t(N);
	vector<double> p2_t(N);
	double a = 0;
	double b = 0;
	int p = 1;
	for (int i = 0; i < N; i++) {
		a += x1_t[i];
		b += x2_t[i];
		//double t = i / fs;
		if (x[i] >= p) {
			a = 0;
			b = 0;

			p++;
		}
		p1_t[i] = a;
		p2_t[i] = b;

	}

	vector<double> p_t(N);
	for (int i = 0; i < N; i++) {
		p_t[i] = -p1_t[i] + p2_t[i];
	}

	//c_t
	vector<double> c_t;
	for (int i = 0; i < N; i++) {
		if (p_t[i] > 0)
			c_t.push_back(1);
		else
			c_t.push_back(0);
	}

	SignalToBits(c_t, N, ts);

	
	generatePNG(x, y, "fsk.png");
	generatePNG(x, x1_t, "fskx1t.png");
	generatePNG(x, x2_t, "fskx2t.png");
	generatePNG(x, p1_t, "fskp1t.png");
	generatePNG(x, p2_t, "fskp2t.png");
	generatePNG(x, p_t, "fskpt.png");
	generatePNG(x, c_t, "fskct.png");
	//DFT(y, "fskDFT.png");
}

vector<double> x_t(int A, vector<double> y,double fs,double fn, double fm, double tc) {
	double size = tc * fs;
	vector<double> w(size);
	double N = tc * fs;

	for (int i = 0; i < y.size(); i++) {
		double t = i / fs;
		w[i] = (A * sin(2 * M_PI*fn*t)) * y[i];

	}


	return w;
}


int main()
{
	vector<bajt> binaryString;
	binaryString = CSTB("test");
	cout << "Bity oryginalne: ";

	for (int i = 0; i < binaryString.size(); i++) {
		for (int j = 0; j < 7; j++) {
			cout << binaryString[i].bit[j];
		}
	}

	cout << endl;

	fs = 1000;
	float ts = (1 / fs);
	float A1 = 1;
	float A2 = 2;
	float W = 2;
	float fn = W * 7;
	float fn1 = (W + 1) * 7;
	float fn2 = (W + 2) * 7;
	float N = ceil(binaryString.size() * 1 / ts) *7;




	//expand(binaryString, N, A1, A2, fn, ts);
	ask(binaryString, N, A1, A2, fn, ts);
	psk(binaryString, N, fn, ts);
	fsk(binaryString, N, fn1, fn2, ts);
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
