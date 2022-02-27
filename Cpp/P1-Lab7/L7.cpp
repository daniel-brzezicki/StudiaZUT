#include "pch.h"
#include <iostream>

int get_values(int t[10], int elements) {
	int x;
	printf_s("Podaj 10 cyfr:\n");
	for (int i = 0; i < elements; i++) {
		scanf_s("%d", &x);
		t[i] = x;
	}

	return 0;
}

int show_values(int t[10], int elements) {
	for (int i = 0; i < elements; i++) {
		printf_s("%d. %d\n", i+1, t[i]);
	}

	return 0;
}

int add(int t[10], int elements) {
	int sum = 0;
	for (int i = 0; i < elements; i++) {
		sum += t[i];
	}

	return sum;
}


int average(int t[10], int elements) {
	return add(t, elements) /elements;
}

int min(int t[10], int elements) {
	int min = t[0];
	for (int i = 0; i < elements; i++) {
		if (min > t[i]) {
			min = t[i];
		}
	}

	return min;
}
int max(int t[10], int elements) {
	int max = t[0];
	for (int i = 0; i < elements; i++) {
		if (max < t[i]) {
			max = t[i];
		}
	}

	return max;
}

int add_tabs(int t1[10], int t2[10], int t3[10],int elements) {
	for (int i = 0; i < elements; i++) {
		t3[i] = t1[i] + t2[i];
	}

	return 0;
}

int main()
{
	int tab[10];
	int elements = 10;
	int tab2[10];
	for (int i = 0; i < elements; i++) {
		tab[i] = tab2[i] = 12-i;
	}

	int tab3[10];

	//get_values(tab, elements);
	show_values(tab, elements);
	printf_s("Dodawanie: %d\n", add(tab, elements));
	printf_s("Srednia: %d\n", average(tab, elements));
	printf_s("Min: %d\n", min(tab, elements));
	printf_s("Max: %d\n", max(tab, elements));

	add_tabs(tab, tab2, tab3, elements);
	show_values(tab3, elements);
}

<!DOCTYPE HTML>
<HTML lang="pl">
	<HEAD>
		<META charset="UTF-8">
		<style>
			HTML{
			  background-image: url("background.jpg");
			  background-repeat: no-repeat;
			  background-attachment: fixed; 
			  background-size: cover;
			  font-family: Arial;
			}
			BODY{
				width: 970px;
				padding: 25px;
				margin-top: 25px;
				margin-bottom: 25px;
				margin-left: auto;
				margin-right: auto;
				background: rgba(255,255,255,0.7);
				}
			div{
				background-image:url("baner1.jpg");
				width: 970px;
				height: 470px;
				background-size: cover;
				text-align: center;
				margin:auto;
			}
			p{
				font-size: 14pt;
				text-align: left;
				margin-bottom: 10px;
				margin-top: 0px;
				margin-left: 0px;
				margin-right: 0px;
			}
			h5{
				font-size:65px;
				padding-top:230px;
				margin:0 auto;
				color: white;
			}
			h1{
				font-size: 32pt;
				font-weight: bold;
				margin-top: 30px;
				margin-bottom: 30px;
			}
			#ustawienie{
				width: 640px;
				margin-top: 10px;
				margin-bottom: 20px;
				display: block;
				margin:0 auto;
			}
			h2{
				font-size: 22pt;
				font-weight: bold;
				margin-top: 20px;
				margin-bottom: 20px;
			}
			 
		</style>
		<title>Tytul strony</title>
	</HEAD>
	<BODY>
			<div><h5>BANER</h5></div>
			<H1>Czym jest Breakdance?</H1>
			<p>Breakdance (inne nazwy: break, breaking, bboying, breakdancing) – rodzaj specyficznego i unikatowego tańca z dużą liczbą elementów siłowo-sprawnościowych, oraz kroków wykonywanych „w parterze”, czyli rękami i nogami (a często całym ciałem) na ziemi. Osoba tańcząca breakdance to b-boy/biboj (mężczyzna) lub b-girl/bigerl (kobieta). Jest to skrót od słowa break-boy/breakdance-boy. Po raz pierwszy słowa "b-boy" użył DJ Kool Herc na jednej z międzyblokowych imprez (block party/street jam). Taniec ten narodził się w latach 70. w Bronksie, dzielnicy Nowego Jorku i jest on jednym z czterech podstawowych i nieodłącznych elementów kultury hip hop obok rapu, DJingu (turntablismu) oraz graffiti[1].</p>
			<H2>Muzyka</H2>
			<p>Pierwotnie muzyką, do której tańczyli b-boye, była muzyka funk oraz soul puszczana na imprezach jako muzyka rozrywkowa. Z czasem DJe zaczęli zapętlać momenty, w których leciała sama perkusja (beat), co stało się podwaliną i inspiracją dla gatunku breakbeat, będącego najbliżej „idealnej” muzyki do tańca. Z głośników przenośnych magnetofonów w latach 80. oraz 90. leciał także hip-hop oraz electro. Te właśnie gatunki (funk, soul, breakbeat, hip-hop, electro) uważane są za muzykę do tańczenia breakdance, co nie znaczy, że każdy utwór posiadający cechy danego gatunku jest muzyką do breakdance. Np. współczesnym odmianom tych gatunków (szczególnie hip-hopu) bardzo daleko do ich pierwowzorów, głównie dzięki nastawieniu na masowego odbiorcę. Artyści tworzący stricte b-boyowy breakbeat, to m.in. DJ Def Cut, DJ Zeb Roc Ski, DJ Kid Stretch, Esone, DJ Nas'D, DJ Woodoo, czy DJ M@R.</p>
			<img src="photo.jpg" alt="Smiley face" id="ustawienie" height="300" width="640">
			<H2>Początki</H2>
			<p>Breakdance miał swój początek w dzielnicy Bronx, w Nowym Jorku. Powstał on od tzw. Uprock Battles (bitwy uprockowe) uprawianych przez tamtejsze gangi. Uprock (rocking) polega pokazywaniu różnych gestów i póz pod adresem przeciwnika (np. markowaniu uderzeń, kopnięć itp., były one głównie improwizowane). Uprock następnie przekształcił się w toprock (dużą inspiracją był taniec i muzyka Jamesa Browna). Później powstały kroki w parterze (footwork/floorrock) i szybsze, skomplikowane figury (powermoves). Właściwa forma breaka to zasługa głównie grup Rock Steady Crew i New York City Breakers. W Europie dużą popularność przyniósł tańcu film „Beat Street” z 1984 r., na którym uwieczniona jest m.in. bitwa wspomnianych dwóch legendarnych ekip.</p>
			<H2>Początki w Polsce</H2>
			<p>Pierwszą pół profesjonalną grupą breakową była Szczecińska grupa Be-Bop, oraz pochodząca z Gniezna Flash Boys[2] założona około roku 1986 w dwa lata po wielkim sukcesie Beat Street. Pierwsze mistrzostwa Polski odbyły się już w roku 1985 w Piotrkowie Trybunalskim. Grupa Be-Bop wyrusza na drugą edycję turnieju gdzie dominuje i zdobywa pierwsze miejsce. Po rozpadzie grupy Be-bop w Szczecinie powstała nowa grupa na podbudowie starej: Broken Steps. Już po czasach „wielkiej mody na breakdance” w roku 1987 zostaje założona we Włocławku grupa Scrap Beat, której to liderem i założycielem jest Robert Nieznański. Grupa przez ponad dekadę wyznaczała standardy w technicznym opanowaniu breaka, głównie figur power-moves. W późniejszym okresie swojej działalności grupa wyłączyła się z aktywnego udziału w życiu „podziemnej” sceny breakdance i skupiła się na działalności komercyjnej</p>
			<H2>Rywalizacja</H2>
			<p>Nieodłącznym elementem kultury b-boyingu są specyficzne formy rywalizacji w tańcu. Klasyczne pokazy solowe lub grupowe oceniane przez sędziów, tak charakterystyczne dla wszystkich tańców nowoczesnych, w breakdance odchodzą powoli do lamusa.</p>
	</BODY>
</HTML>
