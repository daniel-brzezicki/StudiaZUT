#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h> 

struct Contact {
	int id = {};
	char name[100] = {};
	char last_name[100] = {};
	int num = {};
};

void Create(Contact a_con[100], int i);
int Check(Contact a_con[100]);
void Display(Contact con);
void Update(Contact a_con[100]);
void Delete(Contact a_con[100]);

int Check(Contact a_con[100]) {
	int count = 1;
	while (a_con[count - 1].id != 0) {
		count++;
	}
	a_con[count - 1].id = count;
	return count - 1;
}

void Create(Contact a_con[100], int i) {
	char input_name[100];
	char input_last_name[100];
	int dane;

	printf("Podaj imie\n");
	fgets(input_name, sizeof(input_name), stdin);
	strcpy_s(a_con[i].name, input_name);

	printf("Podaj nazwisko\n");
	fgets(input_last_name, sizeof(input_last_name), stdin);
	strcpy_s(a_con[i].last_name, input_last_name);

	printf("Podaj numer tel.\n");
	scanf_s("%d", &dane);
	a_con[i].num = dane;
}

/*void DisplayAll(Contact con[100]) {
	int count = 1;
	printf("--------------------\n");
	while (con[count - 1].id != 0) {
		printf("Kontakt nr: %d\n", con[count - 1].id);
		printf("Imie: %s\n", con[count - 1].name);
		printf("Nazwisko: %s\n", con[count - 1].last_name);
		printf("Numer telefonu: %d\n", con[count - 1].num);
		printf("--------------------\n");
		count++;
	}
}*/

void Display(Contact con) {
	if (con.id != 0) {
		printf("--------------------\n");
		printf("Id: %d\n", con.id);
		printf("Imie: %s\n", con.name);
		printf("Nazwisko: %s\n", con.last_name);
		printf("Numer telefonu: %d\n", con.num);
		printf("--------------------\n");
	}
	else {
		printf("Nie ma takiego kontaktu\n");
	}
}

void Update(Contact a_con[100]) {
	int i;
	int choice;
	int dane;
	char empty[10];

	printf("Podaj id kontaktu, ktory chcesz edytowac\n");
	scanf_s("%d", &i);
	Display(a_con[i - 1]);
	fgets(empty, sizeof(empty), stdin);//Spacje z scanfa

	Create(a_con, i - 1);

	printf("\nPomyslnie edytowano");
}

void Delete(Contact a_con[100]) {
	int i;
	printf("Podaj id kontaktu, ktory chcesz usunac\n");
	scanf_s("%d", &i);

	printf("Czy napewno chcesz usunac ten kontakt? Wpisz 1 - TAK / 2 - NIE \n");
	int choice;
	scanf_s("%d", &choice);

	if (choice == 1) {
		a_con[i - 1].id = 0;
		strcpy_s(a_con[i - 1].name, "");
		strcpy_s(a_con[i - 1].last_name, "");
		a_con[i - 1].num = 0;
	}
}

void Clear() {
	//system("cls");
	printf("C- Tworzenie wpisu\nR- Przegladanie danych\nU- Aktualizowanie wpisow\nD- Kasowanie istniejacych wpisow\nS- Zapisz i wyjdz\n");
}

void ReadToArray(Contact a_con[100]) {
	struct Contact get_from_file;
	FILE *inputFile;

	fopen_s(&inputFile, "kontakty.txt", "r");
	if (inputFile == NULL)
	{
		FILE *outputFile;
		fopen_s(&outputFile, "kontakty.txt", "w");
		fclose(outputFile);
		exit(1);
	}

	int j = 0;
	while (fread(&get_from_file, sizeof(struct Contact), 1, inputFile)) {
		a_con[j].id = get_from_file.id;
		strcpy_s(a_con[j].name, get_from_file.name);
		strcpy_s(a_con[j].last_name, get_from_file.last_name);
		a_con[j].num = get_from_file.num;
		j++;
	}

	fclose(inputFile);
}

void StoreContacts(Contact a_con[100]) {
	FILE *outputFile;

	fopen_s(&outputFile, "kontakty.txt", "w");
	if (outputFile == NULL) {
		exit(1);
	}

	int contacts_max = Check(a_con);
	for (int i = 0; i < contacts_max; i++) {
		fwrite(&a_con[i], sizeof(struct Contact), 1, outputFile);
	}

	fclose(outputFile);
	exit(1);
}

int main()
{
	int input_id;
	int create_id;
	struct Contact contact[100];
	ReadToArray(contact);
	while (1) {
		printf("C- Tworzenie wpisu\nR- Przegladanie danych\nU- Aktualizowanie wpisow\nD- Kasowanie istniejacych wpisow\nS- Zapisz i wyjdz\n");
		char c[10];
		fgets(c, sizeof(c), stdin);
		
		switch (toupper(c[0])) {
		case 'C':
			system("cls");
			create_id = Check(contact);
			Create(contact, create_id);
			break;
		case 'R':
			system("cls");
			//DisplayAll(contact);
			printf("Podaj id kontaktu: ");
			scanf_s("%d", &input_id);
			Display(contact[input_id - 1]);
			break;
		case 'U':
			system("cls");
			Update(contact);
			break;
		case 'D':
			system("cls");
			Delete(contact);
			break;
		case 'S':
			system("cls");
			StoreContacts(contact);
			break;
		}
	}
	return 0;
}
