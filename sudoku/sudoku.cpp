#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//sta�a przechowuj�ca rozmiar planszy
const int ROZMIAR = 9;

//struktura na plansz�
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

//g��wna funkcja programu
int main() {

	//inicjalizowanie generatora liczb pseudolosowych
	srand(time(NULL));

	//poziom trudno�ci definiuj�cy ilo�� p�l startowych na planszy (wst�pnie uzupe�nionych)
	int poziomTrudnosci = wybierzPoziomTrudnosci();

	//obiekt planszy zawieraj�cy informacje o warto�ciach p�l oraz czy dane pole jest starowym
	Plansza plansza = wygenerujPlansze(poziomTrudnosci);

	//zmienna informuj�ca czy gra zosta�a zako�czona - wygrana
	bool wygrana = false;

	//dop�ki nie zostan� spe�nione warunki wygranej
	while (!wygrana) {
		rysujPlansze(plansza.pole);			//rysuje plansze
		wstawCyfre(plansza);				//obs�uguje wprowadzanie znaku przez gracza
		wygrana = czyWygrana(plansza.pole);	//sprawdza warunek wygranej
	}
	
	cout << "GRATULACJE\n";
	system("PAUSE");
	
	return 0;
}


//funkcja do wybru poziomu trudno�ci przez u�ytownika z klawiatury
//zwraca int z poziomem trudno�ci
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

		//je�li wprowadzono 1,2,3 to zwraca adekwatny poziom trudno�ci
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
//wybiera jeden z po�r�d kilku szablon�w i wymazuje cz�� p�l
//reszta p�l - pola podstawowe - nie mog� by� nadpisane w czasie gry
Plansza wygenerujPlansze(int poziomTrudnosci) {

	//tworzy obiekt planszy, do kt�rego wpisze warto�ci p�l
	Plansza plansza;

	//gotowe, rozwi�zane szablony sudoku
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
	//podw�jny wska�nik jest traktowany prawie tak samo jak tablica dwuwymiarowa
	//dlatego tworz�c int** = new int*[] tworzymy wska�nik na tablic� wska�nik�w
	//gdzie p�niej w p�tli for ka�dy wska�nik wskazuje na kolejn� tablic�
	//w ten spos�b uzyskujemy tablic� dwuwymiarow�
	int** pole = new int*[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++) {
		pole[i] = new int[ROZMIAR];
	}

	//losuje jedn� z gotowych plansz sudoku i przepisuje jej zawarto��
	//do stworzonej wcze�niej planszy u�ytkowej
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

	//ustala ile p�l usun�� z planszy - adekwatnie do poziomu trudno�ci
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

		//je�eli pole nie zosta�o wcze�niej oczyszczone to je oczyszcza (ustawia 0)
		if (pole[y][x] != 0) {
			pole[y][x] = 0;
			polaDoUsuniecia--;
		}
	}

	//tworzenie tablicy informuj�cej czy dane pole jest podstawowym(startowym)
	//czyli takim, kt�rego nie mo�na nadpisa� w czasie gry
	bool **podstawowy = new bool *[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++) {
		podstawowy[i] = new bool[ROZMIAR];
	}

	//ustalanie kt�re pola s� podstawowe, a kt�re nie
	//je�li jest liczba nie r�wna 0 to pole jest podstawowe
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

	//wpisanie wygenerowanych i ustalonych parametr�w do obiektu plansza
	plansza.pole = pole;
	plansza.podstawowy = podstawowy;

	//zwraca plansze
	return plansza;
}


//rysuje plansze w konsoli
void rysujPlansze(int** pole) {
	system("cls");	//czy�ci ekran
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
			//je�li kolumna jest podzielna przez 3 to wstawia dodatkowy separator
			if ((j + 1) % 3 == 0) {
				cout << "|";
			}
		}
		//je�li wiersz jest podzielna przez 3 to wstawia podw�jny separator
		//je�li nie to wstawia pojedynczy
		if ((i + 1) % 3 == 0) {
			cout << "\n\t===========================================\n";
		}
		else {
			cout << "\n\t-------------------------------------------\n";
		}
	}
	cout << "\t^\n\ty\n";	//strza�ka z "y"
}


//funkcja sprawdzaj�ca czy w danym polu mo�na wpisa� okre�lon� warto��
//zwraca true je�li ruch jest poprawny
bool czyPoprawnyRuch(int wartosc, int x, int y, Plansza plansza) {

	int kx, ky; //nr kwadratu na planszy w kt�ry chcemy wpisa� cyfr�
	kx = x / 3;
	ky = y / 3;

	//sprawdzanie w kwadracie czy wyst�pi�a taka cyfra
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

	//je�li pole jest polem podstawowym to ruch jest niepoprawny
	if (plansza.podstawowy[y][x] == true) {
		cout << "\tTo pole nie moze zostac zmienione!\n";
		return false;
	}

	//je�li nigdzie nie wyst�pi�a ta cyfra - ruch poprawny
	return true;
}


//funkcja realizuje wstawianie cyfry w danym polu - wybranym przez gracza
void wstawCyfre(Plansza plansza) {

	int x, y, wartosc;

	cout << "\tWybierz pole:\t xy wartosc \t np. a1 7  \n\t";

	char input[5];	//c-string na 4 znaki wprowadzone przez gracza

	//je�li byfor wej�ciowy jest gotowy
	if (cin.good()) {
		//wczytuje ci�g 4 znak�w (5 to null) do tablicy znak�w
		cin.getline(input, 5);
	}
	//je�li bufor niegotowy, z b��dami
	else if (cin.fail()) {
		cin.sync();		//usuwa niewczytane znaki z bufora
		cin.clear();	//czy�ci flagi o b��dach bufora
		return;			
	}

	//sprawdza czy wprowadzona komenda spe�nia za�o�ony wz�r (tabela ASCII)
	//	wz�r:	xy_w	gdzie 
	//		x - litera ma�a lub du�a a-i
	//		y - cyfra 1-9
	//		_ - spacja
	//		w - warto�c wpisana do pola 1-9
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
		//�le wpisana komenda
		cout << "\tZla skladnia.\n";
		system("PAUSE");
		return;
	}

	//sprawdza czy ruch jest poprawny
	if (czyPoprawnyRuch(wartosc, x, y, plansza)) {
		//je�li tak, wpisuje warto�� do danego pola
		plansza.pole[y][x] = wartosc;
		return;
	}
	else {
		cout << "\tNiepoprawny ruch!\n";
		system("PAUSE");
		return;
	}

}


//sprawdza czy wyst�pi�y warunki wygranej - wszystkie pola zape�nine
//(nie zajdzie sytuacja �eby wszystkie pola by�y zape�nione 
//je�li wcze�niej pojawi�a si� b��dnie wstawiona liczba)
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
