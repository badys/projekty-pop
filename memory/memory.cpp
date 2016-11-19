#include <iostream>
#include <string>
#include <time.h>

using namespace std;

const int ROZMIAR_X = 7;
const int ROZMIAR_Y = 5;
const int ileSymboli = 6;

typedef char symbol[5][7];

struct Karta {

	bool odkryta = false;
	symbol *symbol = nullptr;

};

void wyswietl(Karta **karta);
Karta** inicjalizuj(symbol *tablicaSymboli[ileSymboli]);
void wybierzKarte(Karta **karta);
bool czyWygrane(Karta **karta);

int n, m;

int main() {

	// TODO: wybranie rozmiaru planszy	(n * m) % 2 == 0 && (n * m) / 2 <= ileSymboli
	//chwilowo hardcodowany rozmiar 4x3
	n = 4, m = 3;

	symbol *tablicaSymboli[ileSymboli];

	symbol para1 = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', '\\', '/', ' ', '\\', '/', '|' },
		{ '|', ' ', '\\', ' ', '/', ' ', '|' },
		{ '|', ' ', ' ', '|', ' ', ' ', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };
	symbol para2 = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', 'x', ' ', 'X', ' ', 'x', '|' },
		{ '|', ' ', 'X', ' ', 'X', ' ', '|' },
		{ '|', 'x', ' ', 'X', ' ', 'x', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };
	symbol para3 = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', ' ', ' ', '|', ' ', ' ', '|' },
		{ '|', ' ', '/', ' ', '\\', ' ', '|' },
		{ '|', '/', '\\', ' ', '/', '\\', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };
	symbol para4 = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', ' ', '\\', ' ', '//', ' ', '|' },
		{ '|', ' ', ' ', 'X', ' ', ' ', '|' },
		{ '|', ' ', '//', ' ', '\\', ' ', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };
	symbol para5 = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', ' ', '/', '\\', ' ', '/', '|' },
		{ '|', '<', ' ', ' ', 'x', ' ', '|' },
		{ '|', ' ', '\\', '/', ' ', '\\', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };
	symbol para6 = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', 'o', ' ', 'O', ' ', 'o', '|' },
		{ '|', ' ', 'O', ' ', 'O', ' ', '|' },
		{ '|', 'o', ' ', 'O', ' ', 'o', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };

	tablicaSymboli[0] = &para1;
	tablicaSymboli[1] = &para2;
	tablicaSymboli[2] = &para3;
	tablicaSymboli[3] = &para4;
	tablicaSymboli[4] = &para5;
	tablicaSymboli[5] = &para6;

	Karta **karta = inicjalizuj(tablicaSymboli);

	bool wygrane = false;
	while (!wygrane) {
		wyswietl(karta);
		wybierzKarte(karta);
		wygrane = czyWygrane(karta);
	}
	

	system("PAUSE");
	return 0;
}

Karta** inicjalizuj(symbol *tablicaSymboli[ileSymboli]) {

	//dynamiczne tworzenie dwuwymiarowej tablicy kart 
	Karta **karta = new Karta*[m];
	for (int i = 0; i < m; i++) {
		karta[i] = new Karta[n];

	}
	
	//ustawia wszystkie karty jako zakryte
	for (int y = 0; y < m; y++) {
		for (int x = 0; x < n; x++) {
			karta[y][x].odkryta = false;
		}
	}

	//generator liczb pseudo-losowych
	srand(time(NULL));
	//dla ka�dej pary symboli losuje dwie karty, kt�re nie zosta�y jeszcze odkryte(nie ustawiono im symbolu) i ustawia dla nich symbol(par�)
	for (int p = 0; p < ileSymboli; p++) {
		int x1, y1;
		do{
			x1 = rand() % n;
			y1 = rand() % m;
		} while (karta[y1][x1].odkryta == true); //losuje tak d�ugo jak karta jest odkryta, je�li jest zakryta to ustawia symbol
		karta[y1][x1].symbol = tablicaSymboli[p]; //ustala aktualny symbol dla karty
		karta[y1][x1].odkryta = true; //odkrywa kart� - oznacza to, �e karta ju� ma symbol i nie mo�e onby� nadpisany

		//tak samo jak dla pierwszej karty
		int x2, y2;
		do {
			x2 = rand() % n;
			y2 = rand() % m;
		} while (karta[y2][x2].odkryta == true);
		karta[y2][x2].symbol = tablicaSymboli[p];
		karta[y2][x2].odkryta = true;
	}
	//po ustawieniu wszystkim kartom symbolu nale�y je zakry� ponownie aby mo�na bylo rozpocz�� rozgrywk�
	for (int y = 0; y < m; y++) {
		for (int x = 0; x < n; x++) {
			karta[y][x].odkryta = false;
		}
	}	

	//zwraca wska�nik na gotow� tablic� (plansz�) kart, zainicjalizowanych symbolami
	return karta;
}

void wyswietl(Karta **karta) {

	system("cls");

	symbol zakrytaKarta = {
		{ ' ', '-', '-', '-', '-', '-', ' ' },
		{ '|', ' ', ' ', ' ', ' ', ' ', '|' },
		{ '|', ' ', ' ', ' ', ' ', ' ', '|' },
		{ '|', ' ', ' ', ' ', ' ', ' ', '|' },
		{ ' ', '-', '-', '-', '-', '-', ' ' } };

	for (int y = 0; y < m; y++) {

		for (int i = 0; i < ROZMIAR_Y; i++) {

			for (int x = 0; x < n; x++) {

				for (int j = 0; j < ROZMIAR_X; j++) {
					if (karta[y][x].odkryta == false) {
						cout << zakrytaKarta[i][j];
					}
					else {
						cout << (*karta[y][x].symbol)[i][j];
					}
				}

			}
			cout << endl;
		}


	}

}

void wybierzKarte(Karta **karta) {
	cout << "wybierz pierwsza karte (x y): ";
	int x1, y1;
	cin >> x1;
	cin >> y1;

	if (karta[y1][x1].odkryta == true) {
		cout << "Bledny ruch - karta juz odkryta" << endl;
		system("PAUSE");
		return;
	}

	karta[y1][x1].odkryta = true;
	wyswietl(karta);

	cout << "wybierz druga karte: ";
	int x2, y2;
	cin >> x2;
	cin >> y2;

	if (karta[y2][x2].odkryta == true) {
		cout << "Bledny ruch - karta juz odkryta" << endl;
		karta[y1][x1].odkryta = false;	//TODO: zamieni� na powt�rne wpisanie drugiej karty zamiast przerywania ruchu
		system("PAUSE");
		return;
	}

	karta[y2][x2].odkryta = true;
	wyswietl(karta);

	if (karta[y1][x1].symbol == karta[y2][x2].symbol) {
		
	}
	else {
		cout << "NIEUDANY RUCH" << endl;
		system("PAUSE");
		karta[y1][x1].odkryta = false;
		karta[y2][x2].odkryta = false;

		//TODO: zmiana gracza

	}

}

bool czyWygrane(Karta **karta) {
	for (int y = 0; y < m; y++) {
		for (int x = 0; x < n; x++) {
			if (karta[y][x].odkryta == false)
				return false;
		}
	}
	return true;
}