#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void o_ruch(char plansza[7][7]); //ruch kó³ka
bool x_ruch(char plansza[7][7]); //ruch iksa - gracza
void pokaz(char plansza[7][7], int licznik_zbitych); //wypisuje plansze w kosoli
void inicjalizuj(char plansza[7][7]); //ustawia pocz¹tkowe wartoœci
void aktualizuj(char plansza[7][7], int &licznik_zbitych); //aplikuje zmiany (ruch na planszy, zbicie pionka)
bool ruch_w_gore(char plansza[7][7], int k);
bool ruch_w_dol(char plansza[7][7], int k);
bool ruch_w_lewo(char plansza[7][7], int k);
bool ruch_w_prawo(char plansza[7][7], int k);
bool sprawdz_wygrana(int licznik_zbitych); //sprawdza czy s¹ spe³nione warunki wygranej

struct X {
	int x;
	int y;
	bool zbity = false;
};

struct O {
	int x;
	int y;
};

X x[13];
O o;
bool x_wygral = false;

int main() {

	bool koniec = false;
	char plansza[7][7];
	int licznik_zbitych = 0; //licznik zbitych pionków x

	inicjalizuj(plansza);

	aktualizuj(plansza, licznik_zbitych);

	pokaz(plansza, licznik_zbitych);

	while (!koniec) {	//g³ówna petla gry

		while (!x_ruch(plansza)) {	//pêtla przerwana jeœli ruch by³ POPRAWNY
			system("PAUSE");
			pokaz(plansza, licznik_zbitych);
		};

		aktualizuj(plansza, licznik_zbitych);

		pokaz(plansza, licznik_zbitych);

		system("PAUSE");		

		o_ruch(plansza);

		aktualizuj(plansza, licznik_zbitych);

		pokaz(plansza, licznik_zbitych);

		koniec = sprawdz_wygrana(licznik_zbitych);
	}

	system("PAUSE");
	return 0;
}

bool sprawdz_wygrana(int licznik_zbitych) {
	if (x_wygral) {
		cout << "\nGracz (x) wygral rozgrywke!\n";
		return true;
	}
	else {
		if (licznik_zbitych >= 8) {
			cout << "\nKomputer (o) wygral rozgrywke! ;c\n";
			return true;
		}		
	}
	return false;
}

void o_ruch(char plansza[7][7]) {

	//zbijanie w lewo
	if (plansza[o.y][o.x - 1] == 'x' && plansza[o.y][o.x - 2] == ' ' && ( ( (o.y < 2 || o.y > 4) && o.x == 4 ) || ( (o.y >= 2 && o.y <= 4) && o.x > 1 ) ) ) {
		for (int k = 0; k < 13; k++) {
			if (x[k].x == o.x - 1 && x[k].y == o.y && x[k].zbity == false) {
				x[k].zbity = true;
				break;
			}
		}
		o.x = o.x - 2;
	}
	//zbijanie w prawo
	else if (plansza[o.y][o.x + 1] == 'x' && plansza[o.y][o.x + 2] == ' ' && ( ( (o.y < 2 || o.y > 4) && o.x == 2) || ( (o.y >= 2 && o.y <= 4) && o.x < 5) ) ) {
		for (int k = 0; k < 13; k++) {
			if (x[k].x == o.x + 1 && x[k].y == o.y && x[k].zbity == false) {
				x[k].zbity = true;
				break;
			}
		}
		o.x = o.x + 2;
	}
	//zbijanie w góre
	else if (plansza[o.y - 1][o.x] == 'x' && plansza[o.y - 2][o.x] == ' ' && (((o.x < 2 || o.x > 4) && o.y == 4) || ((o.x >= 2 && o.x <= 4) && o.x > 1))) {
		for (int k = 0; k < 13; k++) {
			if (x[k].x == o.x && x[k].y == o.y - 1 && x[k].zbity == false) {
				x[k].zbity = true;
				break;
			}
		}
		o.y = o.y - 2;
	}
	//zbijanie w dó³
	else if (plansza[o.y + 1][o.x] == 'x' && plansza[o.y + 2][o.x] == ' ' && (((o.x < 2 || o.x > 4) && o.y == 2) || ((o.x >= 2 && o.x <= 4) && o.y < 5))) {
		for (int k = 0; k < 13; k++) {
			if (x[k].x == o.x && x[k].y == o.y + 1 && x[k].zbity == false) {
				x[k].zbity = true;
				break;
			}
		}
		o.y = o.y + 2;
	}
	//jeœli nie ma co zbiæ to niech siê ruszy chocia¿
	else {

		bool prawo = false, lewo = false, gora = false, dol = false; //czy mo¿na wykonaæ ruch w dan¹ stronê

		//sprawdzenie dostêpnych kierunków do ruchu o 1 pole
		if (plansza[o.y][o.x - 1] == ' ' && (((o.y < 2 || o.y > 4) && (o.x > 2 && o.x < 5)) || ((o.y >= 2 && o.y <= 4) && o.x > 0))) {
			lewo = true;
		}
		if (plansza[o.y][o.x + 1] == ' ' && (((o.y < 2 || o.y > 4) && (o.x > 1 && o.x < 4)) || ((o.y >= 2 && o.y <= 4) && o.x < 6))) {
			prawo = true;
			}
		if (plansza[o.y - 1][o.x] == ' ' && (((o.x < 2 || o.x > 4) && (o.y > 2 && o.y < 5)) || ((o.x >= 2 && o.x <= 4) && o.y > 0))) {
			gora = true;
		}
		if (plansza[o.y + 1][o.x] == ' ' && (((o.x < 2 || o.x > 4) && (o.y > 1 && o.y < 4)) || ((o.x >= 2 && o.x <= 4) && o.y < 6))) {
			dol = true;
		}

		//jeœli mo¿na siê ruszyæ przynajmniej w jednym kierunku
		if (lewo || prawo || gora || dol) {
			srand(time(NULL));
			int kierunek;
			bool poprawny = false; //poprawnoœæ kierunku ruchu

			while (!poprawny) {
				kierunek = rand() % 4; //losujemy 1 z 4 kierunków i sprawdzamy czy by³ on zgodny, jeœli nie to losujemy do skutku
				switch (kierunek) {
				case 0:
					if (lewo) {
						o.x--;
						poprawny = true;
						break;
					}
				case 1:
					if (prawo) {
						o.x++;
						poprawny = true;
						break;
					}
				case 2:
					if (gora) {
						o.y--;
						poprawny = true;
						break;
					}
				case 3:
					if (dol) {
						o.y++;
						poprawny = true;
						break;
					}
				default: {}
				}
			}
		}
		//w przypadku braku mo¿liwego zbicia oraz ruchu stwierdzamy wygran¹ dla X
		else {
			x_wygral = true;
		}	
	}
}

bool x_ruch(char plansza[7][7]) {
	int iks, igrek;
	char y;
	bool poprawny_pionek = false;
	int aktywny_pionek;
	char kierunek;

	cout << "Podaj wspolrzedne.\n\tx: ";
	cin >> iks;
	cout << "\ty: ";
	cin >> y;

	switch (y) {
	case 'G': {
		igrek = 0;
		break;
	}
	case 'F': {
		igrek = 1;
		break;
	}
	case 'E': {
		igrek = 2;
		break;
	}
	case 'D': {
		igrek = 3;
		break;
	}
	case 'C': {
		igrek = 4;
		break;
	}
	case 'B': {
		igrek = 5;
		break;
	}
	case 'A': {
		igrek = 6;
		break;
	}
	default: {
		return false;
	}
	}

	for (int k = 0; k < 13; k++) {	//znalezienie id dla iksa którego wybraliœmy
		if (x[k].x == iks && x[k].y == igrek && x[k].zbity == false) {
			poprawny_pionek = true;
			aktywny_pionek = k;
			break;
		}
	}

	if (poprawny_pionek) { //jeœli wybraliœmy dobrze
		cout << "W ktora strone chcesz przesunac pionek?\n( g - gora, d - dol, l - lewo, p - prawo)\n\truch: ";
		cin >> kierunek;

		switch (kierunek) { //wybór ruchu
		case 'g': {
			if (!ruch_w_gore(plansza, aktywny_pionek)) {
				cout << "\t***niepoprawny ruch***\n";
				return false;
			}
			return true;
		}
		case 'd': {
			if (!ruch_w_dol(plansza, aktywny_pionek)) {
				cout << "\t***niepoprawny ruch***\n";
				return false;
			}
			return true;
		}
		case 'l': {
			if (!ruch_w_lewo(plansza, aktywny_pionek)) {
				cout << "\t***niepoprawny ruch***\n";
				return false;
			}
			return true;
		}
		case 'p': {
			if (!ruch_w_prawo(plansza, aktywny_pionek)) {
				cout << "\t***niepoprawny ruch***\n";
				return false;
			}
			return true;
		}
		default: {
			cout << "\t***nie ma takiego ruchu***\n";
			return false;
		}
		}

	}
	else { //jeœli wybraliœmy Ÿle
		cout << "niepoprawny pionek!\n";
		system("PAUSE");
		return false;
	}

}

bool ruch_w_gore(char plansza[7][7], int k) {
	//warunek na poprawne wykonanie ruchu
	if (plansza[x[k].y - 1][x[k].x] == ' ' && ( ( (x[k].x >= 2 && x[k].x <= 4) && x[k].y - 1 >= 0) || ( (x[k].x < 2 || x[k].x > 4) && x[k].y - 1 >= 2) ) ) {
		x[k].y--; //przesuniêcie pionka
		return true;
	}
	else return false;
}

bool ruch_w_dol(char plansza[7][7], int k) {

	if (plansza[x[k].y + 1][x[k].x] == ' ' && (((x[k].x >= 2 && x[k].x <= 4) && x[k].y + 1 <= 6) || ((x[k].x < 2 || x[k].x > 4) && x[k].y + 1 <= 4))) {
		x[k].y++;
		return true;
	}
	else return false;
}

bool ruch_w_lewo(char plansza[7][7], int k) {

	if (plansza[x[k].y][x[k].x - 1] == ' ' && (((x[k].y >= 2 && x[k].y <= 4) && x[k].x - 1 >= 0) || ((x[k].y < 2 || x[k].y > 4) && x[k].x - 1 >= 2))) {
		x[k].x--;
		return true;
	}
	else return false;
}

bool ruch_w_prawo(char plansza[7][7], int k) {

	if (plansza[x[k].y][x[k].x + 1] == ' ' && (((x[k].y >= 2 && x[k].y <= 4) && x[k].x + 1 <= 6) || ((x[k].y < 2 || x[k].y > 4) && x[k].x + 1 <= 4))) {
		x[k].x++;
		return true;
	}
	else return false;
}

void pokaz(char plansza[7][7], int licznik_zbitych) {
	system("cls");
	char znak = 71; //w ASCII 71 to du¿e G
	cout << "liczba zbitych pionkow x: " << licznik_zbitych << endl << endl;
	for (int i = 0; i < 7; i++) {
		cout << znak-- << "  ";
		for (int j = 0; j < 7; j++) {
			if ((j == 2 && (i < 2 || i > 4)) || (j == 0 && (i >= 2 && i <= 4))) cout << "|";
			if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) cout << plansza[i][j] << "|";
			if ((i < 2 || i > 4) && (j < 2 || j >4)) cout << "  ";
		}
		cout << endl;
	}
	cout << endl << "   ";
	for (int j = 0; j < 7; j++) {
		cout << " " << j;
	}
	cout << endl;
}

void aktualizuj(char plansza[7][7], int &licznik_zbitych) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			plansza[i][j] = ' ';
			if ((i == o.y) && (j == o.x)) plansza[i][j] = 'o';
			for (int k = 0; k < 13; k++) { //sprawdza czy wspó³rzêdne któregoœ z X pokrywaj¹ siê z danym polem na planszy, pod warunkiem ¿e nie by³ on zbity
				if ((i == x[k].y) && (j == x[k].x) && x[k].zbity == false) plansza[i][j] = 'x';
			}
		}
	}
	licznik_zbitych = 0;
	for (int k = 0; k < 13; k++) {
		if (x[k].zbity) licznik_zbitych++;
	}

}

void inicjalizuj(char plansza[7][7]) {
	//pocz¹tkowe wspó³¿êdne wszystkich pionków
	o.x = 3;
	o.y = 3;
	x[0].x = 0;
	x[0].y = 4;
	x[1].x = 1;
	x[1].y = 4;
	x[2].x = 2;
	x[2].y = 4;
	x[3].x = 3;
	x[3].y = 4;
	x[4].x = 4;
	x[4].y = 4;
	x[5].x = 5;
	x[5].y = 4;
	x[6].x = 6;
	x[6].y = 4;
	x[7].x = 2;
	x[7].y = 5;
	x[8].x = 3;
	x[8].y = 5;
	x[9].x = 4;
	x[9].y = 5;
	x[10].x = 2;
	x[10].y = 6;
	x[11].x = 3;
	x[11].y = 6;
	x[12].x = 4;
	x[12].y = 6;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			plansza[i][j] = ' ';
		}
	}
}