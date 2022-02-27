#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>

class Matrix
{
private:

	int CountPos(int x, int y) {
		for (int i = 0; i < this->x*this->y; i++) {
			if (i%this->x == 0) {
				x--;
				if (x == 0) {
					for (int j = 0; j < y; j++) {
						if (y - 1 == j) {
							return j + i;
						}
					}
				}
			}
		}
	}


public:
	int x; //wiersz
	int y; //kolumna
	std::vector <float> matrix;


	Matrix(int x, int y) {
		this->x = x;
		this->y = y;

		/*for (int i = 0; i < x*y; i++) {
			matrix.push_back(0);
		}*/
	}
	~Matrix() {}

	Matrix& operator=(Matrix source) {
		this->x = source.x;
		this->y = source.y;
		this->matrix = source.matrix;

		return source;
	}

	Matrix operator+(const Matrix & right) const;
	Matrix operator+=(const Matrix & right);
	Matrix operator-(const Matrix & right) const;
	Matrix operator-=(const Matrix & right);
	Matrix operator*(Matrix & right)const;
	Matrix operator*=(Matrix & right);
	Matrix operator~();


	void Show() {
		for (int i = 0; i <= this->x; i++) {
			ShowRow(i);
		}
	}

	void ChangeValue(int row, int column, int value) {
		std::cout << std::endl;
		matrix[CountPos(row, column)] = value;
	}

	int Cell(int row, int column) {
		return matrix[CountPos(row, column)];
	}

	void ShowRow(int row) {
		for (int i = 0; i < this->x*this->y; i++) {
			if (i%this->y == 0) {
				row--;
				if (row == 0) {
					for (int j = 0; j < this->y; j++) {
						std::cout << matrix.at(j + i);
					}
				}
			}
		}
		std::cout << std::endl;
	}

	void ShowColumn(int column) {
		std::cout << std::endl;
		for (int i = 0; i < this->x*this->y; i++) {
			if (i%this->x == column - 1) {
				std::cout << matrix.at(i) << std::endl;
			}
		}
	}

	Matrix AddValue(int value) {
		Matrix M = *new Matrix(x, y);
		for (int i = 0; i < this->x*this->y; i++) {
			if (M.matrix.size() > i)M.matrix[i] += value;
			else M.matrix.push_back(value);
		}

		return M;
	}

	void T() {
		std::vector <float> temp;
		temp = matrix;
		matrix.clear();

		int tempX = this->x;
		int tempY = this->y;

		x = tempY;
		y = tempX;


		for (int n = 0; n < tempY; n++) {
			for (int i = 0; i < this->x*this->y; i++) {
				if (i%tempY == n) {
					matrix.push_back(temp[i]);
				}
			}
		}
	}


	void load(std::string FileName) {
		std::fstream inputFile(FileName, std::ios::in | std::ios::out | std::ios::app);

		if (!inputFile.is_open()) {
			throw std::exception("Can't read file.txt");
		}

		int intFromFile;
		int num = 0;
		while (inputFile >> intFromFile) {
			ToMatrix(intFromFile);
		}
		inputFile.close();
	}

	void ToMatrix(int value) {
		matrix.push_back(value);
	}

	std::string ToString() {
		std::string s;
		for (int i = 0; i < this->x*this->y; i++) {
			s += " " + std::to_string(matrix[i]);
		}
		return s;
	}

	void save(Matrix m) {
		std::string n = getFileName();

		std::ofstream outputFile(getFileName());
		if (!outputFile.is_open()) throw std::exception("Can't write file");

		outputFile << m.ToString();

		outputFile.close();
	}

	std::string getFileName() {
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);

		std::string time = '_' + std::to_string(now.tm_year + 1900) + '-' + std::to_string(now.tm_mon + 1) + '-' + std::to_string(now.tm_mday) + '_' + std::to_string(now.tm_hour) + '_' + std::to_string(now.tm_min) + '_' + std::to_string(now.tm_sec) + ".txt";
		std::string fileName = "matrix";
		return fileName + time;
	}


	/*Matrix add(Matrix *m) {
		if (x == m->x && y == m->y) {
			Matrix M = *new Matrix(x, y);

			for (int i = 0; i < x*y; i++) {
				M.matrix.push_back(matrix[i] + m->matrix[i]);
			}


			return M;
		}
		else {
			throw std::exception("Nie prawidlowe wymiary");
		}
	}

	Matrix subtract(Matrix *m) {
		if (x == m->x && y == m->y) {
			Matrix M = *new Matrix(x, y);

			for (int i = 0; i < x*y; i++) {
				M.ToMatrix(matrix[i] - m->matrix[i]);
			}


			return M;
		}
		else {
			throw std::exception("Nie prawidlowe wymiary");
		}
	}



	Matrix multiply(Matrix *m) {
		int value = 0;
		if (this->y == m->x) {
			Matrix M = *new Matrix(this->x, m->y);
			m->T(); //Uzylem macierzy transponowanej, aby latwiej bylo pomnozyc w petli.
			int temp = 0;

			for (int i = 0; i < this->x; i++) {
				for (int j = 0; j < m->y*m->x; j++) {

					value = matrix[this->y * i + (j % y)] * m->matrix[j];

					temp += value;
					if (j%y == y - 1) {
						//std::cout << temp << std::endl;
						M.matrix.push_back(temp);
						temp = 0;
					}
				}
			}
			return M;
		}
		else {
			throw std::exception("Nie prawidlowe wymiary");
		}
	}*/


	float det() {
		if (x == 2 && y == 2) {
			float d = matrix[0] * matrix[3] + matrix[1] * matrix[2];
			return d;
		}
		else {
			throw std::exception("Ta funkcja liczy jedynie wyznacznik dla macierzy 2x2");
		}
	}
};

Matrix Matrix::operator+(const Matrix & right)const {
	if (x == right.x && y == right.y) {
		Matrix M = *new Matrix(x, y);

		for (int i = 0; i < x*y; i++) {
			M.matrix.push_back(matrix[i] + right.matrix[i]);
		}

		return M;
	}
	else {
		throw std::exception("Nie prawidlowe wymiary");
	}
}

Matrix Matrix::operator+=(const Matrix & right){ 
	if (x == right.x && y == right.y) {
		Matrix M = *new Matrix(x, y);

		for (int i = 0; i < x*y; i++) {
			M.matrix.push_back(matrix[i] + right.matrix[i]);
		}

		this->operator=(M);
		return M;
	}
	else {
		throw std::exception("Nie prawidlowe wymiary");
	}

}


Matrix Matrix::operator-(const Matrix & right)const {
	if (x == right.x && y == right.y) {
		Matrix M = *new Matrix(x, y);

		for (int i = 0; i < x*y; i++) {
			M.ToMatrix(matrix[i] - right.matrix[i]);
		}

		return M;
	}
	else {
		throw std::exception("Nie prawidlowe wymiary");
	}
}

Matrix Matrix::operator-=(const Matrix & right) {
	if (x == right.x && y == right.y) {
		Matrix M = *new Matrix(x, y);

		for (int i = 0; i < x*y; i++) {
			M.ToMatrix(matrix[i] - right.matrix[i]);
		}

		this->operator=(M);
		return M;
	}
	else {
		throw std::exception("Nie prawidlowe wymiary");
	}
}

Matrix Matrix::operator*(Matrix & right)const{
	int value = 0;
	if (this->y == right.x) {
		Matrix M = *new Matrix(this->x, right.y);
		right.T(); //Uzylem macierzy transponowanej, aby latwiej bylo pomnozyc w petli.
		int temp = 0;

		for (int i = 0; i < this->x; i++) {
			for (int j = 0; j < right.y*right.x; j++) {

				value = matrix[this->y * i + (j % y)] * right.matrix[j];

				temp += value;
				if (j%y == y - 1) {
					M.matrix.push_back(temp);
					temp = 0;
				}
			}
		}
		return M;
	}
	else {
		throw std::exception("Nie prawidlowe wymiary");
	}
}


Matrix Matrix::operator*=(Matrix & right){
	int value = 0;
	if (this->y == right.x) {
		Matrix M = *new Matrix(this->x, right.y);
		right.T(); 
		int temp = 0;

		for (int i = 0; i < this->x; i++) {
			for (int j = 0; j < right.y*right.x; j++) {

				value = matrix[this->y * i + (j % y)] * right.matrix[j];

				temp += value;
				if (j%y == y - 1) {
					M.matrix.push_back(temp);
					temp = 0;
				}
			}
		}
		right.T();
		this->operator=(M);
		return M;
	}
	else {
		throw std::exception("Nie prawidlowe wymiary");
	}
}

Matrix Matrix::operator~() {
	Matrix M(this->x, this->y);
	M.matrix = matrix;
	matrix.clear();

	x = M.y;
	y = M.x;


	for (int n = 0; n < M.y; n++) {
		for (int i = 0; i < this->x*this->y; i++) {
			if (i%M.y == n) {
				matrix.push_back(M.matrix[i]);
			}
		}
	}

	return M;
}


int main()
{
	Matrix A(3, 2);
	Matrix B(3, 2);
	Matrix C(3, 2);
	Matrix D(0, 0);


	C.load("file.txt");
	B.load("file1.txt");
	
	A = B;

	D = A + B + C;

	std::cout << "Macierz A: "; A.Show();
	std::cout << "Macierz B: "; B.Show();
	std::cout << "Macierz C: "; C.Show();
	std::cout << "Macierz D: "; D.Show();

	Matrix E(3, 2);
	Matrix F(2, 3);
	Matrix G(0, 0);

	E.load("file.txt");
	F.load("file1.txt");

	G = E * F;
	G += G * G;
	std::cout << "Macierz E: "; E.Show();
	std::cout << "Macierz F: "; F.Show();
	std::cout << "Macierz G: "; G.Show();
	&G;
	std::cout << "Macierz G: "; G.Show();

	A.det();
}