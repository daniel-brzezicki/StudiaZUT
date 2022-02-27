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
	std::vector <int> matrix;


	Matrix(int x, int y) {
		this->x = x;
		this->y = y;

		/*for (int i = 0; i < x*y; i++) {
			matrix.push_back(0);
		}*/
	}
	~Matrix() {}

	void Show() {
		for (int i = 0; i <= this->x; i++) {
			ShowRow(i);
			//std::cout << std::endl;
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
			if (M.matrix.size() > i)M.matrix.at(i) += value;
			else M.matrix.push_back(value);
		}

		return M;
	}

	void T() {
		std::vector <int> temp;
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

	Matrix add(Matrix *m) {
		if (x == m->x && y == m->y) {
			Matrix M = *new Matrix(x, y);

			for (int i = 0; i < x*y; i++) {
				M.matrix.push_back(matrix.at(i) + m->matrix.at(i));
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
				M.ToMatrix(matrix.at(i) - m->matrix.at(i));
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
					if (j%y == y-1) {
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
	}

};



int main()
{
	Matrix *A = new Matrix(4, 3);
	Matrix *B = new Matrix(3, 4);
	Matrix *C = new Matrix(4, 3);

	A->load("file.txt");
	B->load("file1.txt");

	*C = A->multiply(B);

	B->Show();
	C->Show();

	C->save(*C);

	C->multiply(A);//wyjatek

	Matrix *D = new Matrix(1, 1);
	Matrix *E = new Matrix(1, 1);
	Matrix *F = new Matrix(1, 1);
	Matrix *G = new Matrix(1, 1);

	*D = *C;

	D->AddValue(2);

	*E = C->add(D);

	*F = C->add(D);

	*G = E->subtract(F);

	C->Show();
	D->Show();
	E->Show();

	F->Show();
	G->Show();

	A->add(B);//wyjatek2
}