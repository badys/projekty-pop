#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//sta³a przechowuj¹ca rozmiar planszy
const int ROZMIAR = 9;

//struktura na planszê
struct Plansza {
	int** pole = nullptr;
	bool** podstawowy = nullptr;
};

int wybierzPoziomTrudnosci();
Plansza wygenerujPlansze(int poziomTrudnosci);
void rysujPlansze(int** pole);
bool czyPoprawnyRuch(int wartosc, int x, int y, Plansza plansza);
void wstawCyfre(Plansza plansza);
bool czyWygrana(int** pole);

//g³ówna funkcja programu
int main() {

	//inicjalizowanie generatora liczb pseudolosowych
	srand(time(NULL));

	//poziom trudnoœci definiuj¹cy iloœæ pól startowych na planszy (wstêpnie uzupe³nionych)
	int poziomTrudnosci = wybierzPoziomTrudnosci();

	//obiekt planszy zawieraj¹cy informacje o wartoœciach pól oraz czy dane pole jest starowym
	Plansza plansza = wygenerujPlansze(poziomTrudnosci);

	//zmienna informuj¹ca czy gra zosta³a zakoñczona - wygrana
	bool wygrana = false;

	//dopóki nie zostan¹ spe³nione warunki wygranej
	while (!wygrana) {
		rysujPlansze(plansza.pole);			//rysuje plansze
		wstawCyfre(plansza);				//obs³uguje wprowadzanie znaku przez gracza
		wygrana = czyWygrana(plansza.pole);	//sprawdza warunek wygranej
	}
	
	cout << "GRATULACJE\n";
	system("PAUSE");
	
	return 0;
}


//funkcja do wybru poziomu trudnoœci przez u¿ytownika z klawiatury
//zwraca int z poziomem trudnoœci
int wybierzPoziomTrudnosci() {

	char poziom;

	do {
		system("cls");
		cout << "Wybierz poziom trudnosci:\n";
		cout << "\t1 - Latwy\n";
		cout << "\t2 - Sredni\n";
		cout << "\t3 - Trudny\n\n";
		cout << "Poziom: ";
		
		cin.get(poziom);	//pobiera 1 znak z klawiatury
		cin.ignore();		//ignoruje kolejny znak (znak nowej linii - zatwierdzanie enterem)

		//jeœli wprowadzono 1,2,3 to zwraca adekwatny poziom trudnoœci
		if (poziom == '1') {
			return 1;
		}
		else if (poziom == '2') {
			return 2;
		}
		else if (poziom == '3') {
			return 3;
		}
		else {
			cout << "\nWYBIERZ POPRAWNA OPCJE!\n";
			system("pause");
		}

	} while (true);

}


//funkcja generuje plansze do gry
//wybiera jeden z poœród kilku szablonów i wymazuje czêœæ pól
//reszta pól - pola podstawowe - nie mog¹ byæ nadpisane w czasie gry
Plansza wygenerujPlansze(int poziomTrudnosci) {

	//tworzy obiekt planszy, do którego wpisze wartoœci pól
	Plansza plansza;

	//gotowe, rozwi¹zane szablony sudoku
	int sudoku1[ROZMIAR][ROZMIAR] = { { 3, 8, 1, 7, 4, 9, 2, 6, 5 },
	{ 2, 5, 9, 6, 8, 3, 7, 4, 1 },
	{ 6, 7, 4, 2, 5, 1, 3, 8, 9 },
	{ 5, 3, 8, 4, 6, 2, 9, 1, 7 },
	{ 1, 4, 2, 8, 9, 7, 5, 3, 6 },
	{ 9, 6, 7, 1, 3, 5, 4, 2, 8 },
	{ 7, 1, 3, 5, 2, 8, 6, 9, 4 },
	{ 8, 9, 6, 3, 7, 4, 1, 5, 2 },
	{ 4, 2, 5, 9, 1, 6, 8, 7, 3 } };
	int sudoku2[ROZMIAR][ROZMIAR] = { { 3, 6, 5, 1, 4, 8, 9, 2, 7 },
	{ 2, 1, 7, 3, 5, 9, 8, 6, 4 },
	{ 9, 8, 4, 7, 2, 6, 5, 3, 1 },
	{ 4, 9, 6, 2, 1, 3, 7, 8, 5 },
	{ 8, 5, 2, 6, 9, 7, 4, 1, 3 },
	{ 7, 3, 1, 5, 8, 4, 2, 9, 6 },
	{ 5, 4, 9, 8, 3, 1, 6, 7, 2 },
	{ 1, 7, 8, 4, 6, 2, 3, 5, 9 },
	{ 6, 2, 3, 9, 7, 5, 1, 4, 8 } };
	int sudoku3[ROZMIAR][ROZMIAR] = { { 2, 5, 3, 7, 8, 4, 6, 9, 1 },
	{ 4, 8, 1, 6, 9, 2, 5, 3, 7 },
	{ 7, 6, 9, 3, 1, 5, 2, 8, 4 },
	{ 6, 4, 5, 9, 3, 1, 7, 2, 8 },
	{ 9, 1, 2, 5, 7, 8, 3, 4, 6 },
	{ 3, 7, 8, 4, 2, 6, 9, 1, 5 },
	{ 8, 2, 6, 1, 5, 3, 4, 7, 9 },
	{ 1, 9, 4, 2, 6, 7, 8, 5, 3 },
	{ 5, 3, 7, 8, 4, 9, 1, 6, 2 } };
	int sudoku4[ROZMIAR][ROZMIAR] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
	{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
	{ 7, 8, 9, 1, 2, 3, 4, 6, 5 },
	{ 2, 3, 4, 5, 9, 1, 6, 7, 8 },
	{ 5, 6, 7, 2, 4, 8, 3, 9, 1 },
	{ 8, 9, 1, 6, 3, 7, 2, 5, 4 },
	{ 6, 7, 8, 9, 1, 4, 5, 3, 2 },
	{ 9, 1, 2, 3, 7, 5, 8, 4, 6 },
	{ 3, 4, 5, 8, 6, 2, 9, 1, 7 } };
	int sudoku5[ROZMIAR][ROZMIAR] = { { 1, 7, 6, 2, 4, 5, 3, 8, 9 },
	{ 4, 5, 8, 3, 7, 9, 2, 1, 6 },
	{ 3, 2, 9, 1, 8, 6, 4, 5, 7 },
	{ 2, 8, 3, 5, 9, 4, 7, 6, 1 },
	{ 7, 6, 5, 8, 2, 1, 9, 4, 3 },
	{ 9, 4, 1, 7, 6, 3, 8, 2, 5 },
	{ 5, 9, 4, 6, 3, 8, 1, 7, 2 },
	{ 8, 1, 2, 9, 5, 7, 6, 3, 4 },
	{ 6, 3, 7, 4, 1, 2, 5, 9, 8 } };

	//tworzenie dynamiczne dwuwymiarowej tablicy - planszy
	//podwójny wskaŸnik jest traktowany prawie tak samo jak tablica dwuwymiarowa
	//dlatego tworz¹c int** = new int*[] tworzymy wska¿nik na tablicê wskaŸników
	//gdzie póŸniej w pêtli for ka¿dy wskaŸnik wskazuje na kolejn¹ tablicê
	//w ten sposób uzyskujemy tablicê dwuwymiarow¹
	int** pole = new int*[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++) {
		pole[i] = new int[ROZMIAR];
	}

	//losuje jedn¹ z gotowych plansz sudoku i przepisuje jej zawartoœæ
	//do stworzonej wczeœniej planszy u¿ytkowej
	int losowa_plansza = rand() % 5 + 1;
	switch (losowa_plansza) {
	case 1:
		for (int i = 0; i < ROZMIAR; i++) {
			for (int j = 0; j < ROZMIAR; j++) {
				pole[i][j] = sudoku1[i][j];
			}
		}
		break;
	case 2:
		for (int i = 0; i < ROZMIAR; i++) {
			for (int j = 0; j < ROZMIAR; j++) {
				pole[i][j] = sudoku2[i][j];
			}
		}
		break;
	case 3:
		for (int i = 0; i < ROZMIAR; i++) {
			for (int j = 0; j < ROZMIAR; j++) {
				pole[i][j] = sudoku3[i][j];
			}
		}
		break;
	case 4:
		for (int i = 0; i < ROZMIAR; i++) {
			for (int j = 0; j < ROZMIAR; j++) {
				pole[i][j] = sudoku4[i][j];
			}
		}
		break;
	case 5:
		for (int i = 0; i < ROZMIAR; i++) {
			for (int j = 0; j < ROZMIAR; j++) {
				pole[i][j] = sudoku5[i][j];
			}
		}
		break;
	default:
		break;
	}

	//ustala ile pól usun¹æ z planszy - adekwatnie do poziomu trudnoœci
	int polaDoUsuniecia = 0;
	if (poziomTrudnosci == 1) 
		polaDoUsuniecia = 30;
	else if (poziomTrudnosci == 2) 
		polaDoUsuniecia = 40;
	else if (poziomTrudnosci == 3) 
		polaDoUsuniecia = 70;

	//losowo usuwa pola z planszy
	while (polaDoUsuniecia > 0) {
		int x = rand() % 9;
		int y = rand() % 9;

		//je¿eli pole nie zosta³o wczeœniej oczyszczone to je oczyszcza (ustawia 0)
		if (pole[y][x] != 0) {
			pole[y][x] = 0;
			polaDoUsuniecia--;
		}
	}

	//tworzenie tablicy informuj¹cej czy dane pole jest podstawowym(startowym)
	//czyli takim, którego nie mo¿na nadpisaæ w czasie gry
	bool **podstawowy = new bool *[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++) {
		podstawowy[i] = new bool[ROZMIAR];
	}

	//ustalanie które pola s¹ podstawowe, a które nie
	//jeœli jest liczba nie równa 0 to pole jest podstawowe
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			if (pole[i][j] != 0) {
				podstawowy[i][j] = true;
			}
			else {
				podstawowy[i][j] = false;
			}
		}
	}

	//wpisanie wygenerowanych i ustalonych parametrów do obiektu plansza
	plansza.pole = pole;
	plansza.podstawowy = podstawowy;

	//zwraca plansze
	return plansza;
}


//rysuje plansze w konsoli
void rysujPlansze(int** pole) {
	system("cls");	//czyœci ekran
	cout << "\n\t  || A | B | C || D | E | F || G | H | I || <-x";
	cout << "\n\t===========================================\n";
	for (int i = 0; i < ROZMIAR; i++) {
		cout << "\t" << i + 1 << " ||";
		for (int j = 0; j < ROZMIAR; j++) {
			if (pole[i][j] == 0) {
				cout << "   |";
			}
			else {
				cout << " " << pole[i][j] << " |";
			}
			//jeœli kolumna jest podzielna przez 3 to wstawia dodatkowy separator
			if ((j + 1) % 3 == 0) {
				cout << "|";
			}
		}
		//jeœli wiersz jest podzielna przez 3 to wstawia podwójny separator
		//jeœli nie to wstawia pojedynczy
		if ((i + 1) % 3 == 0) {
			cout << "\n\t===========================================\n";
		}
		else {
			cout << "\n\t-------------------------------------------\n";
		}
	}
	cout << "\t^\n\ty\n";	//strza³ka z "y"
}


//funkcja sprawdzaj¹ca czy w danym polu mo¿na wpisaæ okreœlon¹ wartoœæ
//zwraca true jeœli ruch jest poprawny
bool czyPoprawnyRuch(int wartosc, int x, int y, Plansza plansza) {

	int kx, ky; //nr kwadratu na planszy w który chcemy wpisaæ cyfrê
	kx = x / 3;
	ky = y / 3;

	//sprawdzanie w kwadracie czy wyst¹pi³a taka cyfra
	for (int i = ky * 3; i < ky * 3 + 3; i++) {
		for (int j = kx * 3; j < kx * 3 + 3; j++) {
			if (plansza.pole[i][j] == wartosc) {
				cout << "\tW kwadracie jest juz taka cyfra!\n";
				return false;
			}
		}
	}

	//sprawdzanie w wierszu 
	for (int j = 0; j < ROZMIAR; j++) {
		if (plansza.pole[y][j] == wartosc) {
			cout << "\tW wierszu jest juz taka cyfra!\n";
			return false;
		}
	}

	//sprawdzanie w kolumnie
	for (int i = 0; i < ROZMIAR; i++) {
		if (plansza.pole[i][x] == wartosc) {
			cout << "\tW kolumnie jest juz taka cyfra!\n";
			return false;
		}
	}

	//jeœli pole jest polem podstawowym to ruch jest niepoprawny
	if (plansza.podstawowy[y][x] == true) {
		cout << "\tTo pole nie moze zostac zmienione!\n";
		return false;
	}

	//jeœli nigdzie nie wyst¹pi³a ta cyfra - ruch poprawny
	return true;
}


//funkcja realizuje wstawianie cyfry w danym polu - wybranym przez gracza
void wstawCyfre(Plansza plansza) {

	int x, y, wartosc;

	cout << "\tWybierz pole:\t xy wartosc \t np. a1 7  \n\t";

	char input[5];	//c-string na 4 znaki wprowadzone przez gracza

	//jeœli byfor wejœciowy jest gotowy
	if (cin.good()) {
		//wczytuje ci¹g 4 znaków (5 to null) do tablicy znaków
		cin.getline(input, 5);
	}
	//jeœli bufor niegotowy, z b³êdami
	else if (cin.fail()) {
		cin.sync();		//usuwa niewczytane znaki z bufora
		cin.clear();	//czyœci flagi o b³êdach bufora
		return;			
	}

	//sprawdza czy wprowadzona komenda spe³nia za³o¿ony wzór (tabela ASCII)
	//	wzór:	xy_w	gdzie 
	//		x - litera ma³a lub du¿a a-i
	//		y - cyfra 1-9
	//		_ - spacja
	//		w - wartoœc wpisana do pola 1-9
	if (((input[0] >= 65 && input[0] <= 73) || (input[0] >= 97 && input[0] <= 105)) && (input[1] >= 49 && input[1] <= 57) && (input[2] == 32) && (input[3] >= 49 && input[3] <= 57)) {

		if (input[0] >= 65 && input[0] <= 73) {
			x = static_cast<int>(input[0] - 65);	//zamiana znaku ASCII na int
		}	
		else if (input[0] >= 97 && input[0] <= 105) {
			x = static_cast<int>(input[0] - 97);
		}
		y = static_cast<int>(input[1] - 49);
		wartosc = static_cast<int>(input[3] - 48);

	}
	else {
		//Ÿle wpisana komenda
		cout << "\tZla skladnia.\n";
		system("PAUSE");
		return;
	}

	//sprawdza czy ruch jest poprawny
	if (czyPoprawnyRuch(wartosc, x, y, plansza)) {
		//jeœli tak, wpisuje wartoœæ do danego pola
		plansza.pole[y][x] = wartosc;
		return;
	}
	else {
		cout << "\tNiepoprawny ruch!\n";
		system("PAUSE");
		return;
	}

}


//sprawdza czy wyst¹pi³y warunki wygranej - wszystkie pola zape³nine
//(nie zajdzie sytuacja ¿eby wszystkie pola by³y zape³nione 
//jeœli wczeœniej pojawi³a siê b³êdnie wstawiona liczba)
bool czyWygrana(int ** pole) {

	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			if (pole[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}
