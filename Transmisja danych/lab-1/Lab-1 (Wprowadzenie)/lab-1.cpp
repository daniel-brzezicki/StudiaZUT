// ConsoleApplication18.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>
#include <math.h>

using namespace std;


double wartosc_funkcji(double x) { // f(x) = x^3
	return pow(x, 3);
}

int main()
{
	RGBABitmapImageReference * img = CreateRGBABitmapImageReference();

	vector<double> x;
	vector<double> y;

	double step=0.1f;
	double a=-100;
	double b=100;


	while (a < b) {
		x.push_back(a);
		y.push_back(wartosc_funkcji(a));
		a += step;
	}


	DrawScatterPlot(img, 600, 400, &x, &y);

	vector<double> *png = ConvertToPNG(img->image);
	WriteToFile(png, "plot.png");
	DeleteImage(img->image);
}