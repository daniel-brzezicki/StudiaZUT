#include "pch.h"
#include <iostream>
#include <stdio.h>
int count_days(int day, int month, int year){
	int sum = 0;
	int i = 1970;
	int j = 1; 

	int rok_przestepny = 366;
	int rok = 365;
	int days_in_month = 0;
	int february = 0;
	int all_days = 0;

	while (i <= year) {
		if (i != year) {
			if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
				sum += rok_przestepny;
			}
			else {
				sum += rok;
			}
		}
		else if (i == year) {
			while (j <= month) {
				if (j == 1) {
					all_days = day + sum;
				}
				else if (j == 2) {
					days_in_month = 31;
					all_days = day + days_in_month + sum;
				}
				else if (j == 3) {
					if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
						february = 29;
						days_in_month = february + 31;
					}
					else {
						february = 28;
						days_in_month = february + 31;
					}
					all_days = day + days_in_month + sum;
				}
				else if (j == 4) {
					days_in_month = february + (31 * 2);
					all_days = day + days_in_month + sum;
				}
				else if (j == 5) {
					days_in_month = february + (31 * 2) + 30;
					all_days = day + days_in_month + sum;
				}
				else if (j == 6) {
					days_in_month = february + (31 * 3) + 30;
					all_days = day + days_in_month + sum;
				}
				else if (j == 7) {
					days_in_month = february + (31 * 3) + (30 * 2);
					all_days = day + days_in_month + sum;
				}
				else if (j == 8) {
					days_in_month = february + (31 * 4) + (30 * 2);
					all_days = day + days_in_month + sum;
				}
				else if (j == 9) {
					days_in_month = february + (31 * 5) + (30 * 2);
					all_days = day + days_in_month + sum;
				}
				else if (j == 10) {
					days_in_month = february + (31 * 5) + (30 * 3);
					all_days = day + days_in_month + sum;
				}
				else if (j == 11) {
					days_in_month = february + (31 * 6) + (30 * 3);
					all_days = day + days_in_month + sum;
				}
				else if (j == 12) {
					days_in_month = february + (31 * 6) + (30 * 4);
					all_days = day + days_in_month + sum;
				}
				j++;

			}
		}
		i++;
	}
	return all_days;
}

int show_day(int all_days, int day, int month, int year) {
	if (all_days % 7 == 0) {
		printf_s("\nDzien: %d. %d. %d to sroda.\n", day, month, year);
	}
	else if (all_days % 7 == 1) {
		printf_s("\nDzien: %d. %d. %d to czwartek\n", day, month, year);
	}
	else if (all_days % 7 == 2) {
		printf_s("\nDzien: %d. %d. %d to piatek\n", day, month, year);
	}
	else if (all_days % 7 == 3) {
		printf_s("\nDzien: %d. %d. %d to sobota\n", day, month, year);
	}
	else if (all_days % 7 == 4) {
		printf_s("\nDzien: %d. %d. %d to niedziela\n", day, month, year);
	}
	else if (all_days % 7 == 5) {
		printf_s("\nDzien: %d. %d. %d to poniedzialek\n", day, month, year);
	}
	else if (all_days % 7 == 6) {
		printf_s("\nDzien: %d. %d. %d to wtorek\n", day, month, year);
	}
	return 0;
}

int show_calendar(int all_days,int day, int month, int year) {
	int sum_of_days = all_days - day + 1;
	int day_begin = (sum_of_days + 2) % 7;
	int day_of_month;
	int column = 0;
	int date = 0;

	printf_s("\n Pn Wt Sr Cz Pt Sb Nd\n");

	if (month == 2 && year % 4 == 0 && year % 100 != 0 || month == 2 && year % 400 == 0) {
		day_of_month = 29;
	}
	else if (month == 2 && year % 4 != 0) {
		day_of_month = 28;
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		day_of_month = 31;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		day_of_month = 30;
	}
	while (date < day_of_month) {
		if (column < day_begin) {
			printf_s("   ");
		}
		else if (column >= day_begin) {
			date++;
			if (date >= 10) {
				printf_s(" %d", date);
			}
			else {
				printf_s("  %d", date); 
			}
		}
		column++;
		if (column % 7 == 0) {
			printf_s("\n");
		}
	}
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		printf_s("\nRok jest przestepny.");
	}
	else {
		printf_s("\nRok nie jest przestepny.");
	}
	return 0;
}

int get_value(int value) {
	int variable;
	if (value == 1){
		printf_s("Podaj dzien: ");
	}
	else if (value == 2){
		printf_s("Podaj miesiac: ");
	}
	else if (value == 3) {
		printf_s("Podaj rok: ");
	}
	scanf_s("%d", &variable);
	return variable;
}

int main(){

	int all_days, day, month, year;

	day = get_value(1);
	month = get_value(2);
	year = get_value(3);

	all_days = count_days(day, month, year);
	show_day(all_days, day, month, year);
	show_calendar(all_days,day, month, year);
}
