// lab-1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>
#include <math.h>

using namespace std;
# define M_PI           3.14159265358979323846

double wartosc_funkcji(double t, double f) { 
	return abs(pow(sin(2.0f* M_PI *f * pow(t, 2.0f)), 13.0f)) + cos(2.0f*M_PI*t);
}

double wartosc_funkcji_y(double t) {
	return (pow(t, 3.0) - 1) + cos(4 * pow(t, 2.0)*M_PI) * t;
}

double wartosc_funkcji_z(double t,double f) {
	return wartosc_funkcji(t,f) / (abs(wartosc_funkcji_y(t)*cos(5.0*t) - wartosc_funkcji(t,f) * wartosc_funkcji_y(t)) + 3.0);
}

double wartosc_funkcji_v(double t, double f) {
	return (wartosc_funkcji(t, f)*pow(t, 3.0)) / abs(wartosc_funkcji(t, f) - wartosc_funkcji_y(t)) + 0.5;
}

double wartosc_funkcji_u(double t) {
	if (0.1 > t&&t >= 0)
		return sin(6 * M_PI*t)*cos(5 * M_PI*t);
	else if (0.4 > t&& t >= 0.1)
		return -1.1*t*cos(41 * M_PI*pow(t, 2.0));
	else if (0.72 > t && t >= 0.4)
		return t * sin(20 * pow(t, 4.0));
	else if (1 > t && t >= 0.72)
		return 3.3*(t - 0.72)*cos(27 * t + 1.3);

}

void generatePNG(vector<double> x, vector<double>y, string fileName) {
	RGBABitmapImageReference * img = CreateRGBABitmapImageReference();
	DrawScatterPlot(img, 600, 400, &x, &y);

	vector<double> *png = ConvertToPNG(img->image);
	WriteToFile(png, fileName);
	DeleteImage(img->image);
}

int main()
{
	RGBABitmapImageReference * img = CreateRGBABitmapImageReference();
	vector<double> x;
	vector<double> y;

	double f = 4000;
	double fs = 8000;
	double tc = 1.0;
	double ts = 1 / fs;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji(x[i], f));
	}
	generatePNG(x, y, "zad1.png");


	//zad2
	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_y(x[i]));
	}
	generatePNG(x, y, "zad2y.png");

	//z
	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_z(x[i],f));
	}
	generatePNG(x, y, "zad2z.png");

	//v
	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_v(x[i], f));
	}
	generatePNG(x, y, "zad2v.png");



	//zad3
	y.clear();
	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji_u(x[i]));
	}
	generatePNG(x, y, "zad3u.png");



	x.clear();
	y.clear();
	//zad4
	f = 11025;
	fs = 22050;
	tc = 1.0;
	ts = 1 / fs;

	for (int i = 0; i < tc*fs; i++) {
		x.push_back(i / fs);
	}

	for (int i = 0; i < x.size(); i++) {
		y.push_back(wartosc_funkcji(x[i], f));
	}
	generatePNG(x, y, "zad4.png");
}