#include "pch.h"
#include <iostream>
#include <math.h>

float pi = 3.14159265359;

float add(float a, float b) {
	return a + b;
}

void test_add(void)
{
	printf_s(" Test 1: \n\t Oczekiwano : 4.1, \n\t a uzyskano : %g\n", add(2.1, 2.0));
	printf_s(" Test 2: \n\t Oczekiwano : 0.1, \n\t a uzyskano : %g\n", add(0.1, 0.0));
	printf_s(" Test 3: \n\t Oczekiwano : 2.14, \n\t a uzyskano : %g\n", add(2.09, 0.05));
	printf_s(" Test 4: \n\t Oczekiwano : 7.77, \n\t a uzyskano : %g\n", add(2.77, 5.0));
	printf_s(" Test 5: \n\t Oczekiwano : 42, \n\t a uzyskano : %g\n", add(42, 0));
	printf_s(" Test 6: \n\t Oczekiwano : 0.000000001, \n\t a uzyskano : %g\n", add(0.000000001, 0.0));
}

float sub(float a, float b) {
	return a - b;
}

void test_sub(void)
{
	printf_s(" Test 1: \n\t Oczekiwano : 0.1, \n\t a uzyskano : %g\n", sub(2.1, 2.0));
	printf_s(" Test 2: \n\t Oczekiwano : 0.1, \n\t a uzyskano : %g\n", sub(0.1, 0.0));
	printf_s(" Test 3: \n\t Oczekiwano : 2.04, \n\t a uzyskano : %g\n", sub(2.09, 0.05));
	printf_s(" Test 4: \n\t Oczekiwano : -3.77, \n\t a uzyskano : %g\n", sub(2.77, 5.0));
	printf_s(" Test 5: \n\t Oczekiwano : 42, \n\t a uzyskano : %g\n", sub(42, 0));
	printf_s(" Test 6: \n\t Oczekiwano : 1e-9, \n\t a uzyskano : %g\n", sub(0.000000001, 0.0));
}
float mul(float a, float b) {
	return a * b;
}

void test_mul(void)
{
	printf_s(" Test 1: \n\t Oczekiwano : 4.2, \n\t a uzyskano : %g\n", mul(2.1, 2.0));
	printf_s(" Test 2: \n\t Oczekiwano : 0, \n\t a uzyskano : %g\n", mul(0.1, 0.0));
	printf_s(" Test 3: \n\t Oczekiwano : 0.1045, \n\t a uzyskano : %g\n", mul(2.09, 0.05));
	printf_s(" Test 4: \n\t Oczekiwano : 13.85, \n\t a uzyskano : %g\n", mul(2.77, 5.0));
	printf_s(" Test 5: \n\t Oczekiwano : 0, \n\t a uzyskano : %g\n", mul(42, 0));
	printf_s(" Test 6: \n\t Oczekiwano : 0, \n\t a uzyskano : %g\n", mul(0.000000001, 0.0));
}

double div(double a, double b) {
	return a / b;
}

void test_div(void)
{
	printf_s(" Test 1: \n\t Oczekiwano : 1.05, \n\t a uzyskano : %g\n", div(2.1, 2.0));
	printf_s(" Test 2: \n\t Oczekiwano : 2.0, \n\t a uzyskano : %g\n", div(2.0, 1.0));
	printf_s(" Test 3: \n\t Oczekiwano : 41.8, \n\t a uzyskano : %g\n", div(2.09, 0.05));
	printf_s(" Test 4: \n\t Oczekiwano : 0.554, \n\t a uzyskano : %g\n", div(2.77, 5.0));
	printf_s(" Test 5: \n\t Oczekiwano : 21.0, \n\t a uzyskano : %g\n", div(42.0, 2.0));
	printf_s(" Test 6: \n\t Oczekiwano : 1, \n\t a uzyskano : %g\n", div(0.1, 0.1));
}

double m_sin(double a) {
	return sin(a * (pi / 180.0));
}

void test_sin(void)
{
	printf_s(" Test 1: \n\t Oczekiwano : 1, \n\t a uzyskano : %g\n", m_sin(90));
	printf_s(" Test 2: \n\t Oczekiwano : 0.70710678118, \n\t a uzyskano : %g\n", m_sin(45));
	printf_s(" Test 3: \n\t Oczekiwano : 0.96592582628, \n\t a uzyskano : %g\n", m_sin(75));
	printf_s(" Test 4: \n\t Oczekiwano : 0.76604444311, \n\t a uzyskano : %g\n", m_sin(50));
	printf_s(" Test 5: \n\t Oczekiwano : 0.86602540378, \n\t a uzyskano : %g\n", m_sin(60));
	printf_s(" Test 6: \n\t Oczekiwano : 0.42261826174, \n\t a uzyskano : %g\n", m_sin(25));
}

double m_cos(double a) {
	return cos(a * (pi / 180.0));
}

void test_cos(void)
{
	printf_s(" Test 1: \n\t Oczekiwano : 0.0, \n\t a uzyskano : %g\n", m_cos(90));
	printf_s(" Test 2: \n\t Oczekiwano : 0.70710678118, \n\t a uzyskano : %g\n", m_cos(45));
	printf_s(" Test 3: \n\t Oczekiwano : 0.2588190451, \n\t a uzyskano : %g\n", m_cos(75));
	printf_s(" Test 4: \n\t Oczekiwano : 0.64278760968, \n\t a uzyskano : %g\n", m_cos(50));
	printf_s(" Test 5: \n\t Oczekiwano : 0.5, \n\t a uzyskano : %g\n", m_cos(60));
	printf_s(" Test 6: \n\t Oczekiwano : 0.90630778703, \n\t a uzyskano : %g\n", m_cos(270));
}

int main()
{
	test_add();
	test_sub();
	test_mul();
	test_div();
	test_sin();
	test_cos();
}
