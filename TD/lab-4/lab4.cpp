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

void generatePNG(vector<double> x, vector<double>y, string fileName) {
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

void ask(vector<bajt>binary,int N, float A1, float A2,float fn, float ts) {
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

		if (tab[floor(x[i]*7)] == 0)
			y.push_back(A1*sin(2 * M_PI*fn*x[i]));
		else
			y.push_back(A2*sin(2 * M_PI*fn*x[i]));

	}

	generatePNG(x, y, "ask.png");
	DFT(y,"askDFT.png");
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
			y.push_back(sin(2 * M_PI*fn*x[i]+M_PI));

	}

	generatePNG(x, y, "psk.png");
	DFT(y,"pskDFT.png");
}

void fsk(vector<bajt>binary, int N, float fn1, float fn2, float ts) {
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

	generatePNG(x, y, "fsk.png");
	DFT(y,"fskDFT.png");
}

int main()
{
	vector<bajt> binaryString;
	binaryString = CSTB("1011101");

	fs = 1000;
	float ts = 1 / fs;
	float A1 = 1;
	float A2 = 2;
	float W = 2;
	float fn = W * 7;
	float fn1 = (W + 1) * 7;
	float fn2 = (W + 2) * 7;

	float N = ceil(binaryString.size() * 1 / ts);

	expand(binaryString, N, A1, A2, fn, ts);
	ask(binaryString,N, A1, A2, fn, ts);
	psk(binaryString, N, fn, ts);
	fsk(binaryString, N, fn1,fn2, ts);
}

