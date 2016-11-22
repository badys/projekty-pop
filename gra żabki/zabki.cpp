#include <iostream>

using namespace std;

bool wygrana(int tab[]);	//sprawdza czy spe³niony jest warunek zwyciêstwa
void wyswietl(int tab[]);	//wyœwietla plansze
void akcja(int tab[], char ruch, int &zero);	//decyzja o przesuniêciu pionków

int main() 
{

	int tab[11] = { 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2 };	//tablica przechowywuj¹ca informacje, kto stoi na danym kamieniu

	int zero = 5; //pozycja wolnego miejsca

	char ruch;	//decyzja gracza

	bool koniec = false;	//flaga zakoñczenia gry

	while (!koniec) 
	{

		system("cls");

		wyswietl(tab);

		cin >> ruch;	//wprowadzenie ruchu

		akcja(tab, ruch, zero);	

		if (wygrana(tab)) 
		{
			system("cls");
			wyswietl(tab);
			cout << "\t\t\t\t-----------------" << endl;
			cout << "\t\t\t\t|               |" << endl;
			cout << "\t\t\t\t|  Wygrales/as! |" << endl;
			cout << "\t\t\t\t|               |" << endl;
			cout << "\t\t\t\t-----------------" << endl;
			koniec = true;
		}

	}

	system("PAUSE");
	return 0;
}

bool wygrana(int tab[]) 
{
	if (tab[0] == 2 && tab[1] == 2 && tab[2] == 2 && tab[3] == 2 && tab[4] == 2 && tab[6] == 1 && tab[7] == 1 && tab[8] == 1 && tab[9] == 1 && tab[10] == 1) return true;
	else return false;
}

void wyswietl(int tab[]) 
{
	cout << "MENU :\nL - ruch w lewo \tP - ruch w prawo\tR - reset\n\n";
	for (int j = 0; j < 6; j++) 
	{
		for (int i = 0; i < 11; i++) 
		{
			if (j == 0) 
			{
				if (tab[i] == 1) cout << " O>\t";
				else if (tab[i] == 0) cout << "   \t";
				else if (tab[i] == 2) cout << "<O \t";
			}
			else if (j == 1) 
			{
				if (tab[i] == 1) cout << " |\\\t";
				else if (tab[i] == 0) cout << "   \t";
				else if (tab[i] == 2) cout << "/| \t";
			}
			else if (j == 2) 
			{
				if (tab[i] == 1) cout << " | \t";
				else if (tab[i] == 0) cout << "   \t";
				else if (tab[i] == 2) cout << " | \t";
			}
			else if (j == 3) 
			{
				if (tab[i] == 1) cout << "/ \\\t";
				else if (tab[i] == 0) cout << "   \t";
				else if (tab[i] == 2) cout << "/ \\\t";
				
			}
			else if (j == 4) 
			{
				cout << "___\t";
			}
			else if (j == 5) 
			{
				cout << " " << i + 1 << " \t";
			}
			
		}
		cout << endl;
	}
	cout << endl;
}

void akcja(int tab[], char ruch, int &zero) 
{
	if (ruch == 'P' || ruch == 'p') 
	{
		if (tab[zero - 1] == 1) //jeœli na lewo od przerwy jest pionek 1, to przesuwa go w prawo
		{
			tab[zero] = 1;
			tab[zero - 1] = 0;
			zero--;
		}
		else if (tab[zero - 2] == 1 && tab[zero - 1] == 2) //jeœli na lewo od przerwy jest pionek 2 a za nim pionek 1, to ten drugi przeskakuje pierwszego w prawo
		{
			tab[zero] = 1;
			tab[zero - 2] = 0;
			zero = zero - 2;
		}
	}
	else if (ruch == 'L' || ruch == 'l') 
	{
		if (tab[zero + 1] == 2) //jeœli na prawo od przerwy jest pionek 2, to przesuwa go w lewo
		{
			tab[zero] = 2;
			tab[zero + 1] = 0;
			zero++;
		}
		else if (tab[zero + 2] == 2 && tab[zero + 1] == 1) //jeœli na prawo od przerwy jest pionek 1 a za nim pionek 2, to ten drugi przeskakuje pierwszego w lewo
		{
			tab[zero] = 2;
			tab[zero + 2] = 0;
			zero = zero + 2;
		}
	}
	else if (ruch == 'R' || ruch == 'r') //reset - przyrwaca stan pocz¹tkowy
	{
		for (int i = 0; i < 11; i++) 
		{
			if (i < 5) tab[i] = 1;
			else if (i == 5) tab[i] = 0;
			else tab[i] = 2;
		}
		zero = 5;
	}
}
