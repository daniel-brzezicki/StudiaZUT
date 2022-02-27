// TDLab-7.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <string>


# define M_PI           3.14159265358979323846

using namespace std;

double m(float fm, float t) {
	return(sin(2 * M_PI *fm*t));
}

double Za(float Ka, float fm, float t, float fn) {
	return (Ka*m(fm, t) + 1)*cos(2 * M_PI*fn*t);
}

double Zp(float Kp, float fm, float t, float fn) {
	return cos(2 * M_PI * fn * t + Kp * m(fm, t));
}

double Zf(float fm, float t, float fn, float kf) {
	return cos(2 * M_PI * fn * t + (kf / fm) *m(fm, t));
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
		y.push_back(Za(ka, fm, x[i], fn));
	}


	y.clear();
}



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

bajt hamming(string str, bool negate, int bitToNegate) {
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


	return bajt;
}

void dehamming(bajt bajt, bool negate) {
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
		cout << "\nFalse";
	}
	cout << "\nS = " << s << endl;
}

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


vector<double> SignalToBits(vector<double> c_t, int N, double tc) {
	vector<double> ciag;
	double ones = 0;
	double zeros = 0;

	int a = floor(N / tc);

	int counter = 0;
	for (int i = 0; i < c_t.size(); i++) {
		counter = i;
		counter++;
		if (counter % ((N / 7) + 1) == 0) {
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
			else if (c_t[i] == 1)
				ones++;
		}
	}

	cout << "\nBity odczytane:  ";
	for (int i = 0; i < ciag.size(); i++) {
		std::cout << ciag[i];
	}
	cout << endl;

	return ciag;
}

vector<double> ask(vector<bajt>binary, int N, float A1, float A2, float fn, float ts) {
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
	int h = 0;
	vector<double> c_t;
	for (int i = 0; i < N; i++) {
		if (p_t[i] > h)
			c_t.push_back(1);
		else
			c_t.push_back(0);
	}

	vector<double> wynik = SignalToBits(c_t, N, ts);
	return wynik;
}

vector<double> psk(vector<bajt>binary, int N, float fn, float ts) {
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

	vector<double> wynik = SignalToBits(c_t, N, ts);
	return wynik;
	//SignalToBits(c_t, N, ts);

	/*generatePNG(x, y, "psk.png");
	generatePNG(x, x_t, "pskxt.png");
	generatePNG(x, p_t, "pskpt.png");
	generatePNG(x, c_t, "pskct.png");*/
	//DFT(y, "pskDFT.png");
}

vector<double> fsk(vector<bajt>binary, double N, float fn1, float fn2, float ts) {
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

	vector<double> wynik = SignalToBits(c_t, N, ts);
	return wynik;


	/*generatePNG(x, y, "fsk.png");
	generatePNG(x, x1_t, "fskx1t.png");
	generatePNG(x, x2_t, "fskx2t.png");
	generatePNG(x, p1_t, "fskp1t.png");
	generatePNG(x, p2_t, "fskp2t.png");
	generatePNG(x, p_t, "fskpt.png");
	generatePNG(x, c_t, "fskct.png");*/
	//DFT(y, "fskDFT.png");
}

double ber(bajt b1, bajt b2, int size=7) {
	int b = 0;
	for (int i = 0; i < size; i++) {
		if (b1.bit[i] != b2.bit[i])
			b++;
	}
	
	return (b / 7.0);
}

int main()
{
	string napis = "1101000";
	bajt input = CreateBajt(napis);
	/*s.append(to_string(binaryString[i].bit[j]));

	for (int i = 0; i < napis.length(); i++) {
		for (int j = 0; j < 7; j++) {
			s.append(to_string(binaryString[i].bit[j]));
		}
	}
	cout << s;*/


	//Zad1
	bajt hammingCoded = hamming(napis, false, 7);
	vector<bajt> binaryString;
	binaryString.push_back(hammingCoded);

	dehamming(binaryString[0], false);



	fs = 1000;
	float ts = 1 / fs;
	float A1 = 1;
	float A2 = 2;
	float W = 2;
	float fn = W * 7;
	float fn1 = (W + 1) * 7;
	float fn2 = (W + 2) * 7;

	float N = ceil(binaryString.size() * 1 / ts);


	/*vector<double> x;
	for (int i = 0; i < binaryString.size(); i++) {
		for (int j = 0; j < 7; j++) {
			x.push_back(binaryString[i].bit[j]);
		}
	}*/

	vector<double> y;
	y = ask(binaryString, N, A1, A2, fn, ts);

	bajt b;
	for (int i = 0; i < y.size(); i++) {
		b.bit[i] = y[i];
	}
	dehamming(b, false);
	cout <<"Ber: "<< ber(b, input)<<endl;



	y = psk(binaryString, N,fn, ts);

	for (int i = 0; i < y.size(); i++) {
		b.bit[i] = y[i];
	}
	dehamming(b, false);
	cout << "Ber: " << ber(b, input) << endl;



	y = fsk(binaryString, N, A1, A2, ts);

	for (int i = 0; i < y.size(); i++) {
		b.bit[i] = y[i];
	}
	dehamming(b, false);
	cout << "Ber: " << ber(b, input) << endl;


}