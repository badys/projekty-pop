#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct symbol {
	char wartosc;
	int licznik = 0;
};

struct gracz {
	char nazwa[40];
	int punkty;
};

void wypisz(char plansza[12][12], int rozmiar, bool kafelki[12][12], gracz* aktywny_gracz);
void wypelnij(char plansza[12][12], int rozmiar, symbol znak[]);
void inicjalizuj(char plansza[12][12], int rozmiar, symbol znak[], bool kafelki[12][12]);
bool koniec(bool kafelki[12][12], int rozmiar);
void ruchAI(char plansza[12][12], int rozmiar, bool kafelki[12][12], gracz* aktywny_gracz);
void ruchgracza(char plansza[12][12], int rozmiar, bool kafelki[12][12], gracz* aktywny_gracz);

gracz gracz1, gracz2;

int main() {

	symbol znak[72];
	gracz* aktywny_gracz = &gracz1; //wskaünik na aktywnego gracza
	int rozmiar, wybor;
	char plansza[12][12];
	bool kafelki[12][12];
	bool kontraAI = false;

	cout << "(1)gracz kontra gracz\n(2)gracz kontra AI\n";
	cin >> wybor;

	if (wybor == 2) kontraAI = true;

	cout << "Podaj nazwe gracza: ";
	cin >> gracz1.nazwa;

	if (!kontraAI) {
		cout << "Podaj nazwe drugiego gracza: ";
		cin >> gracz2.nazwa;
	}
	else strcpy_s(gracz2.nazwa,"komputer");

	cout << "Rozmiar planszy: 8 lub 12: ";
	cin >> rozmiar;

	inicjalizuj(plansza, rozmiar, znak, kafelki);
	wypisz(plansza, rozmiar, kafelki, aktywny_gracz);
	wypelnij(plansza, rozmiar, znak);

	while (!koniec(kafelki, rozmiar)) {

		if(kontraAI && aktywny_gracz == &gracz2) ruchAI(plansza, rozmiar, kafelki, aktywny_gracz);
		else if(kontraAI && aktywny_gracz == &gracz1) ruchgracza(plansza, rozmiar, kafelki, aktywny_gracz);
		else ruchgracza(plansza, rozmiar, kafelki, aktywny_gracz);

		wypisz(plansza, rozmiar, kafelki, aktywny_gracz);

	}

	system("PAUSE");
	return 0;
}

void ruchAI(char plansza[12][12], int rozmiar, bool kafelki[12][12], gracz* aktywny_gracz) {
	
	int y1, y2, x1, x2;

	do {
		y1 = rand() % rozmiar;
		x1 = rand() % rozmiar;
	} while (kafelki[y1][x1]);

	kafelki[y1][x1] = true;

	do {
		y2 = rand() % rozmiar;
		x2 = rand() % rozmiar;
	} while (kafelki[y2][x2]);

	kafelki[y2][x2] = true;

	if (plansza[y1][x1] == plansza[y2][x2])	gracz2.punkty++;
	else {
		kafelki[y1][x1] = false;
		kafelki[y2][x2] = false;
		aktywny_gracz = &gracz1;
	}
}

void ruchgracza(char plansza[12][12], int rozmiar, bool kafelki[12][12], gracz* aktywny_gracz) {

	int x1, x2, y1, y2;

	do {
		cout << "x: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;
		x1--;
		y1--;
		if (kafelki[y1][x1]) {
			wypisz(plansza, rozmiar, kafelki, aktywny_gracz);
			cout << "kafelek juz odkryty\n";
		}
	} while (kafelki[y1][x1]);

	kafelki[y1][x1] = true;

	wypisz(plansza, rozmiar, kafelki, aktywny_gracz);

	do {
		cout << "x: ";
		cin >> x2;
		cout << "y: ";
		cin >> y2;
		x2--;
		y2--;
		if (kafelki[y2][x2]) {
			wypisz(plansza, rozmiar, kafelki, aktywny_gracz);
			cout << "kafelek juz odkryty\n";
		}
	} while (kafelki[y2][x2]);

	kafelki[y2][x2] = true;

	wypisz(plansza, rozmiar, kafelki, aktywny_gracz);

	if (plansza[y1][x1] == plansza[y2][x2]) {
		cout << "Znalazles pare!";
		aktywny_gracz->punkty++;
	}
	else {
		cout << "Nie trafiles!\n";
		kafelki[y1][x1] = false;
		kafelki[y2][x2] = false;
		if (aktywny_gracz == &gracz1) aktywny_gracz = &gracz2;
		else if (aktywny_gracz == &gracz2) aktywny_gracz = &gracz1;		
	}
	system("pause");
}

void wypisz(char plansza[12][12], int rozmiar, bool kafelki[12][12], gracz* aktywny_gracz) {
	system("cls");
	for (int i = 0; i < rozmiar; i++) {
		cout << i + 1 << "\t|";
		for (int j = 0; j < rozmiar; j++) {
			cout << " ";

			if (kafelki[i][j]) {
				cout << plansza[i][j];
			}
			else cout << " ";
			cout << " |";
		}
		cout << "\n";
		if (!(i == rozmiar - 1)) {
			cout << "\t---------------------------------";
			if (rozmiar == 8) cout << endl;
			else if (rozmiar == 12) cout << "----------------\n";
		}
	}
	cout << "\n\t";
	for (int j = 0; j < rozmiar; j++) {
		cout << "  " << j + 1 << " ";
	}
	cout << "\nAktywny gracz: " << aktywny_gracz->nazwa << endl;
	cout << gracz1.nazwa << " - " << gracz1.punkty << "pkt.\n";
	cout << gracz2.nazwa << " - " << gracz2.punkty << "pkt.\n";

}

void wypelnij(char plansza[12][12], int rozmiar, symbol znak[]) {
	int buf;
	srand(time(NULL));
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			while (true) {
				buf = rand() % (rozmiar*rozmiar / 2);
				if (znak[buf].licznik < 2) {
					plansza[i][j] = znak[buf].wartosc;
					znak[buf].licznik++;
					break;
				}
			}
		}
	}
}

void inicjalizuj(char plansza[12][12], int rozmiar, symbol znak[], bool kafelki[12][12]) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			plansza[i][j] = NULL;
		}
	}
	for (int i = 0; i < 72; i++) {
		znak[i].wartosc = 33 + i;
	}
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			kafelki[i][j] = false;
		}
	}
}

bool koniec(bool kafelki[12][12], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if(kafelki[i][j] == false) return false;
		}
	}
	return true;
}