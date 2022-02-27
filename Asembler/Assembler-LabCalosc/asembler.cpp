#include "pch.h"
#include <iostream>

using namespace std;

void zad1a() {
	short y = 0;
	char a = 0x0F;
	__asm {
		mov ax, 0
		mov bh, 0
		mov bl, a

		shl bx, 4
		add ax, bx

		shl bx, 2
		add ax, bx

		mov y, ax
	}
	printf("%d", y);
}

//zad 1 wersja b i c do domu

void zad1_b() {
	short y = 0;
	char a = 0x0F;
	__asm {
		mov ax, 0
		mov bh, 0
		mov bl, a

		shl bx, 4
		sub ax, bx

		shl bx, 2
		sub ax, bx

		mov y, ax
	}
	printf("%d", y*(-1));
}

void zad1_c() {
	short y = 0;
	char a = 0x0F;
	__asm {
		mov ax, 0
		mov bh, 0
		mov bl, a
		mov cl, 0


		_while:
		cmp cl, 80
		jz _koniec
			push bx
			add ax, bx
			add cl, 1
			jmp _while
		_koniec:



		mov y, ax
	}
	printf("%d", y);
}


void zad2() {
	unsigned char a = 0x32, y;
	__asm {
		mov al, a
		sub al, 0x32
		jnz normalnaflaga
		mov y, 0
		jmp trochepowagi
		normalnaflaga :
		mov y, 1
			trochepowagi :
	}

	printf("%d", y);
}

void zad3() {
	unsigned char a = 0x32;
	bool y;
	__asm {
		mov al, a
		sub al, 0x32
		jz normalnaflaga
		mov y, 0
		jmp trochepowagi
		normalnaflaga :
		mov y, 1
			trochepowagi :
	}

	cout << y << endl;
}

void zad3_2() {
	unsigned char a = 0x32;
	bool y;
	__asm {
		mov y, 1;
		mov al, a;
		sub al, 0x32;
		jnz etykieta;
		mov y, 0;
	etykieta:
	}
	printf(y ? "true" : "false");
}

void zad4a() {
	int i;
	int y;
	__asm {
		mov eax, 0;
		mov ebx, 0;
		mov ecx, 5;
	forr:
		sub ecx, eax
			jz koniec
			mov ecx, 5
			add ebx, eax
			add eax, 1
			jmp forr
			koniec :
		mov y, ebx;
	}

	printf("%d", y);
}

void zad4b() {
	int i;
	int y;
	__asm {
		mov eax, 0;
		mov ebx, 0;
		mov ecx, 5;
	forr:
		cmp ecx, eax
			jz koniec
			add ebx, eax
			add eax, 1
			jmp forr
			koniec :
		mov y, ebx;
	}
	printf("%d", y);
}

void zad5a() {
	int i, y = 0;
	__asm {
		mov ebx, y
		_while :
		mov eax, ebx
			sub eax, 5
			jz et
			add ebx, 1
			jmp _while
			et :
		mov y, ebx
	}
	printf("%d", y);
}

void zad5c() {
	int i, y = 0;
	__asm {
		mov ebx, y
		_doWhile :
		add ebx, 1
			mov eax, ebx
			sub eax, 5 //xor eax, 5
			jz et
			jmp _doWhile
			et :
		mov y, ebx
	}
	printf("%d", y);
}


void zad6a() {
	unsigned char a = 0x00, y = 8;
	__asm {
		mov al, a
		mov bl, y

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov cl, al
		and cl, 0x01
		sub bl, cl
		shr al, 1

		mov y, bl
	}

	printf("%d", y);
}

void zad6b() {
	unsigned char a = 0x13, y = 8;



	__asm {
		mov al, a
		mov cl, 0
		mov dl, y
		skok :
		cmp cl, 8
			jz petla_for

			mov bl, al
			and bl, 0x01
			sub dl, bl
			shr al, 1


			add cl, 1
			jmp skok
			petla_for :
		mov y, dl
	}
	printf("%d", y);
}

void zad6b_C() {
	int zera = 0;
	unsigned char a = 0x00;

	bool parzystosc;

	a = ~a;
	while (a != 0) {
		zera += (a & 1);
		a = a >> 1;
	}


	printf("%d", zera);
}


void zad7b() {
	unsigned char a = 0x00, y = 0;

	__asm {
		mov al, a
		mov cl, 0
		mov dl, y
		skok :
		cmp cl, 8
			jz petla_for
			mov bl, al
			and bl, 0x01
			add dl, bl
			shr al, 1
			add cl, 1
			jmp skok
			petla_for :
		and dl, 0x01
			xor dl, 1
			mov y, dl
	}
	printf("%d", y);
}

void zad7b_C() {
	int jedynki = 0;
	unsigned char a = 0x12;

	bool parzystosc;

	while (a != 0) {
		jedynki += (a & 0x01);
		a = a >> 1;
	}

	if (jedynki % 2 == 0)
		parzystosc = true;
	else
		parzystosc = false;

	printf(parzystosc ? "true" : "false");
}

void zad8a() {
	unsigned char a = 0x12, r;
	__asm {
		mov al, a
		mov cl, 0

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		//and bl, 1
		or cl, bl
		shr al, 1
		shl cl, 1

		mov bl, al
		and bl, 1
		or cl, bl

		mov r, cl

	}
	printf("%#x", r);
}

void zad8a_2() {
	unsigned char y = 0xbd;

	__asm {
		mov ah, y
		mov dh, ah
		mov ch, 0

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh
		shr ah, 1
		mov dh, ah

		and dh, 1
		add ch, dh

		and ch, 1
		xor ch, 1


		mov y, ch

	}

	printf("y = %d\n", y);

}

/*void zad8c() {

	unsigned char a = 0x80, r;


	__asm {
		mov al, a
		mov bl, r

		mov cl, 0xFF
		_for:
			shl bl,1
			test al, 
			jz koniec
				or bl, 0x01
			koniec:
			shr al, 1
			shr cl, 1
		jnz _for

		mov r, bl
	}



	printf("%#x", r);
}*/

void zad8_C_2() {
	unsigned char a = 0x12,r,pom;
	
	for (int i = 0; i < 8; i++) {
		pom = a;
		pom &= 1;
		r |= pom;
		a >>= 1;
	}
	printf("%#x", r);
}

void zad8_C() {
	uint8_t a = 0x12;
	uint8_t result = 0;
	for (int i = 0; i < 8; i++) {
		//if (i == 8){
			result = (result << 1) | (a & 0x1);
		a = a >> 1;
		//}
	}

	//cout << std::bitset<8>{result} << endl;
}


void zad9c() {
	unsigned char b = 5, a = 7;
	short y;

	__asm {
		mov ax, 0
		mov al, a
		mov bl, b
		mov cx, 0
		skocz:
		test bl, 1
			jz skacz
			add cx, ax
		skacz :
			shl al, 1
			shr bl, 1
			jnz skocz
			mov y, cx
	}
	printf("%d", y);
}

void zad10() {
	short a = 1000, y = 0;

	__asm {
		mov ax, a
		mov bx, ax

		shr bx, 3

		add ax, bx
		mov y, ax
	}
	printf("%d", y);
}

void zad11a() {
	unsigned char a = 5, y;
	__asm {

		mov y, 1
		mov al, a
		add al, -0x05
		jc flag
		mov y, 0
		flag:
	}
	printf("%d", y);
}


void zad12a() {
	int y;
	__asm {
		mov ecx, 0
		mov ebx, 0
		skok:
		mov eax, ecx
			add eax, -5
			jc petla_for
			add ebx, ecx
			add ecx, 1
			jmp skok
			petla_for :
		mov y, ebx
	}
	printf("%d", y);
}


void zad13() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 2;
			unsigned char b : 3;
			unsigned char c : 3;
		}bits;
	}b;

	b x;
	x.bits.a = 0x03;

	__asm {
		mov al, x
		and al, 3
		mov bl, al
		mov cl, al

		shl bl, 2
		or al, bl

		shl cl, 5
		or al, cl
		mov x, al

	}
	printf("%#x", x);
}


void zad14() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 1;
			unsigned char b : 3;
			unsigned char c : 4;
		}bits;
	}b;

	b x;
	x.bits.a = 0x01;
	x.bits.b = 0x03;
	x.bits.c = 0x01;

	__asm {
		mov al, x.BYTE
		mov ah, al
		and ah, 0x0F
		and al, 0x1
		jz _skip
			mov bl, ah
			and bl, 0x0E
			shl bl, 3
			add ah, bl
			_skip:
		mov x.BYTE, ah

	}
	printf("%#x", x.bits.c);

}


void zad15() {
	unsigned char tab[5];
	__asm {
		lea eax, tab
		mov cl, 0
		wroc:
		cmp ecx, 5
			jz wyjdz
			mov[eax], cl
			add eax, 1
			add cl, 1
			jmp wroc
			wyjdz :
	}

	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", tab[i]);
	}
}

void zad16(){
	#pragma pack(1)
	typedef struct {
		unsigned char a ;
		int b;
		long c;
	}MTestStruct;
	MTestStruct testSturct;
	testSturct.a = 1;
	testSturct.b = 2;
	testSturct.c = 3;
	char* adr = (char*)(&testSturct);
	int size = sizeof(testSturct);
	for (int i = 0; i < size; i++) {
		printf("%x\n", (unsigned char)*(adr + i));
	}
}

void zad16_drugawersja() {
//#pragma pack(1)
	typedef struct {
		unsigned char a;
		int b;
		long c;
	}MTestStruct;
	MTestStruct testSturct;
	char* adr = (char*)(&testSturct);
	*adr = 1; //a
	*((int*)&adr[1]) = 2; //b
	*((long*)&adr[5]) = 3; //c
	__asm {
		lea ebx, testSturct
		mov [ebx], 1
		mov dword ptr[ebx+1], 2
		mov dword ptr[ebx+5], 3
	}
	int size = sizeof(testSturct);
	for (int i = 0; i < size; i++) {
		printf("%x\n", (unsigned char)*(adr + i));
	}
}

void zad17() {
//#pragma pack(2)
	class Base {
	public:
		unsigned char a;
	};

	class MTestStruct {
	public:
		int b;
		long c;
	};
	MTestStruct testSturct;
	char* adr = (char*)(&testSturct);
	__asm {
		lea ebx, testSturct
		mov [ebx], 1
		mov dword ptr[ebx + 2], 2
		mov dword ptr[ebx + 6], 3
	}
	int size = sizeof(testSturct);
	for (int i = 0; i < size; i++) {
		printf("%x\n", (unsigned char)*(adr + i));
	}
}

void zad18() {
#pragma pack(2)

	class Base {
	public:
		unsigned char a;
		virtual void aaa() {};
	};

	class MTestStruct {
	public:
		int b;
		long c;
		virtual void aaa() {};
	};


	MTestStruct testSturct;
	char* adr = (char*)(&testSturct);

	__asm {
		lea ebx, testSturct
		mov[ebx+4], 1
		mov dword ptr[ebx + 8], 2
		mov dword ptr[ebx + 12], 3
	}


	int size = sizeof(testSturct);
	for (int i = 0; i < size; i++) {
		printf("%x\n", (unsigned char)*(adr + i));
	}
}

void zadtest() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 1;
			unsigned char b : 3;
			unsigned char c : 4;
		}bits;
	}un_X;
	un_X x;

	x.bits.a = 1;
	x.bits.b = 2;
	x.bits.c = 8;

	__asm {
		mov al, x.BYTE
		mov bl, x.BYTE
		and al, 1
		jnz nonzero
		mov al, bl
		and al, 0xE
		jmp koniec
		nonzero :
		and bl, 0xE
			or al, bl
			shl bl, 3
			or al, bl
			koniec :
		mov x.BYTE, al
	}
	printf("%#x", x.bits.c);
}

int main()
{
	zad8a();
	//zadtest();
	//zad1a();
	//zad1_b();
	//zad1_c();
	//zad1a();
	//zad2();
	//zad3();
	//zad3_2();
	//zad4a();
	//zad4b();
	//zad5a();
	//zad5c();
	//zad6a();
	//zad6b();
	//zad7a();
	//zad8a();
	//zad8a_2();
	//zad8c();
	//zad9c();

	//zad9c();
	//zad10();
	//zad11a();
	//zad12a();
	//zad14();
	//zad15();
	//zad16();
	//zad16_drugawersja();
	//zad17();
	//zad18();


	
	//zad7b_C();
	//zad6b_C();
	//zad8_C_2();


}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
