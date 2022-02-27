// lab-2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

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

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;


double fs;

void generatePNG(vector<double> x, vector<double>y, string fileName) {
	RGBABitmapImageReference * img = CreateRGBABitmapImageReference();
	DrawScatterPlot(img, 600, 400, &x, &y);

	vector<double> *png = ConvertToPNG(img->image);
	WriteToFile(png, fileName);
	DeleteImage(img->image);
}

// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray& x)
{


	const size_t N = x.size();
	if (N <= 1) return;

	// divide
	CArray even = x[std::slice(0, N / 2, 2)];
	CArray  odd = x[std::slice(1, N / 2, 2)];

	// conquer
	fft(even);
	fft(odd);

	// combine
	for (size_t k = 0; k < N / 2; ++k)
	{
		Complex t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}


void DFTtest(int N) {
	int n, k;   
	vector<double> x;
	vector<double> Xre;
	vector<double> Xim;
	vector<double> P;

	for (int i = 0; i < N; i++) {
		x.push_back(0);
		Xre.push_back(0);
		Xim.push_back(0);
		P.push_back(0);
	}

	srand(time(NULL));
	for (n = 0; n < N; ++n) {
		x[n] = n;
	}

	for (k = 0; k < N; ++k)
	{
		Xre[k] = 0;
		//cout << k+1 << " ";
		for (n = 0; n < N; ++n) {
			Xre[k] += x[n] * cos(n * k * 2 * M_PI / N);
		}

		Xim[k] = 0;
		for (n = 0; n < N; ++n) {
			Xim[k] -= x[n] * sin(n * k * 2 * M_PI / N);
		}
		//cout << "Re: " << Xre[k] << "  ";
		//cout << "Im: " << Xim[k];
		//cout << endl;
	}

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
		//x.push_back(0);
		Xre.push_back(0);
		Xim.push_back(0);
		//P.push_back(0);
	}

	/*srand(time(NULL));
	for (n = 0; n < N; ++n) {
		x[n] = n;
	}*/

	for (k = 0; k < N; ++k)
	{
		Xre[k] = 0;
		//cout << k+1 << " ";
		for (n = 0; n < N; ++n) {
			Xre[k] += x[n] * cos(n * k * 2 * M_PI / N);
		}

		Xim[k] = 0;
		for (n = 0; n < N; ++n) {
			Xim[k] -= x[n] * sin(n * k * 2 * M_PI / N);
		}
		//cout << "Re: " << Xre[k] << "  ";
		//cout << "Im: " << Xim[k];
		//cout << endl;
	}

	WartosciModulow(Xre, Xim, fileName);
}

void FFTtest(int N) {
	Complex* test = new Complex[N];
	for (int i = 0; i < N; i++) {
		test[i] = i;
	}
	CArray data(test,N);

	// forward fft
	fft(data);

	//std::cout << "fft" << std::endl;
	/*for (int i = 0; i < N; ++i)
	{
		std::cout << data[i] << std::endl;
	}*/
}

void FFT(vector<double> x) {
	int N = x.size();
	Complex* test = new Complex[N];
	for (int i = 0; i < N; i++) {
		test[i] = x[i];
	}

	
	CArray data(test, N);

	// forward fft
	fft(data);

	//std::cout << "fft" << std::endl;
	/*for (int i = 0; i < N; ++i)
	{
		std::cout << data[i] << std::endl;
	}*/
}


void zad1() {
	clock_t t1, t2;
	double time_per_element;
	for (int i = 128; i < 10240; i=i*2) {
		cout << i << " elementow"<<endl;

		t1 = clock();
		DFTtest(i);
		t2 = clock();
		time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas DFT "<< time_per_element << endl;

		t1 = clock();
		FFTtest(i);
		t2 = clock();
		time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas FFT " <<time_per_element << endl;
		cout << endl;
	}
}


double wartosc_funkcji_zad2(double t, double f) {
	return sin(M_PI *f *t);
}

void zad2() {
	vector<double> x;
	vector<double> y;

	double f = 200;
	fs = 4000;
	double tc = 1.0;
	double ts = 1 / fs;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_zad2(x[i], f));
	}

	DFT(y, "zad2.png");

	y.clear();
}


double wartosc_funkcji_zad3(double t, double f) {
	return abs(pow(sin(2.0f* M_PI *f * pow(t, 2.0f)), 13.0f)) + cos(2.0f*M_PI*t);
}

void zad3() {
	vector<double> x;
	vector<double> y;

	double f = 4000;
	fs = 8000;
	double tc = 1.0;
	double ts = 1 / fs;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_zad3(x[i], f));
	}

	DFT(y, "zad3.png");

	y.clear();
}


double wartosc_funkcji_y(double t) {
	return (pow(t, 3.0) - 1) + cos(4 * pow(t, 2.0)*M_PI) * t;
}

double wartosc_funkcji_z(double t, double f) {
	return wartosc_funkcji_zad3(t, f) / (abs(wartosc_funkcji_y(t)*cos(5.0*t) - wartosc_funkcji_zad3(t, f) * wartosc_funkcji_y(t)) + 3.0);
}

double wartosc_funkcji_v(double t, double f) {
	return (wartosc_funkcji_zad3(t, f)*pow(t, 3.0)) / abs(wartosc_funkcji_zad3(t, f) - wartosc_funkcji_y(t)) + 0.5;
}

void zad4() {
	vector<double> x;
	vector<double> y;

	double f = 4000;
	fs = 8000;
	double tc = 1.0;
	double ts = 1 / fs;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_zad3(x[i], f));
	}

	clock_t t1, t2;
	double time_per_element;


	t1 = clock();
	FFT(y);
	t2 = clock();
	time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Czas dla sygnalow nr 1: " << time_per_element << endl;

	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_y(x[i]));
	}

	t1 = clock();
	FFT(y);
	t2 = clock();
	time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Czas dla sygnalow nr 2: " << time_per_element << endl;


	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_z(x[i], f));
	}



	t1 = clock();
	FFT(y);
	t2 = clock();
	time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Czas dla sygnalow nr 3: " << time_per_element << endl;
	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_v(x[i], f));
	}


	t1 = clock();
	FFT(y);
	t2 = clock();
	time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Czas dla sygnalow nr 4: " << time_per_element << endl;
}

int main()
{
	zad1();
	zad2();
	zad3();
	zad4();
}
