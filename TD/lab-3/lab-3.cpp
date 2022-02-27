#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>
#include <math.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <complex>
#include <valarray>


# define M_PI           3.14159265358979323846

using namespace std;


void generatePNG(vector<double> x, vector<double>y, string fileName) {
	RGBABitmapImageReference * img = CreateRGBABitmapImageReference();
	DrawScatterPlot(img, 600, 400, &x, &y);

	vector<double> *png = ConvertToPNG(img->image);
	WriteToFile(png, fileName);
	DeleteImage(img->image);
}

double m(float fm, float t) {
	return(sin(2 * M_PI *fm*t));
}

double Za(float Ka,float fm, float t,float fn) {
	return (Ka*m(fm, t) + 1)*cos(2 * M_PI*fn*t);
}

double Zp(float Kp, float fm, float t, float fn) {
	return cos(2 * M_PI * fn * t + Kp * m(fm, t));
}

double Zf(float fm, float t, float fn, float kf) {
	return cos(2 * M_PI * fn * t + (kf/fm) *m(fm,t));
}


double fs = 5000;

void zad1() {
	vector<double> x;
	vector<double> y;

	double fm = 5;
	double fn = 25;
	fs = 5000;
	double tc = 1.0;

	double ka = 0.5;
	double kp = 4.0;
	double kf = 4.0;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(Za(ka,fm,x[i],fn));
	}

	generatePNG(x, y, "Za.png");

	y.clear();

	for (int i = 0; i < x.size(); i++) {
		y.push_back(Zp(kp, fm, x[i], fn));
	}

	generatePNG(x, y, "Zp.png");

	y.clear();

	for (int i = 0; i < x.size(); i++) {
		y.push_back(Zf(fm,x[i],fn,kf));
	}

	generatePNG(x, y, "Zf.png");
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

	//for (int i = 0; i < n; i++) {
	//	cout<<mo[i]<<endl;
	//}

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

void zad2() {
	
}

void zad3() {
	double fmin=500;
	double fmax=1000;

	vector<double> x;
	vector<double> y;

	double fm = 20;
	double fn = 1000;
	fs = 5000;
	double tc = 1.0;

	double ka = 0.5;
	double kp = 4.0;
	double kf = 4.0;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(Za(ka, fm, x[i], fn));
	}
	


	DFT(y, "ZaM.png");

	//WartosciModulow(x, y, "ZaM.png");

	/*double maxV=NULL;
	double minV=NULL;
	for (int i = fmin; i < fmax; i++) {
		if (maxV == NULL)
			maxV = y[i];
		if (minV == NULL)
			minV = y[i];
		if (y[i] < minV)
			minV = y[i];
		if (y[i] > maxV)
			maxV = y[i];
	}*/

	//cout << maxV << " " << minV << "   " << maxV - minV;


	y.clear();

	for (int i = 0; i < x.size(); i++) {
		y.push_back(Zp(kp, fm, x[i], fn));
	}

	DFT(y, "ZpM.png");

	y.clear();

	for (int i = 0; i < x.size(); i++) {
		y.push_back(Zf(fm, x[i], fn, kf));
	}

	DFT(y, "ZfM.png");
}

int main()
{
	//zad1();
	zad3();
}
