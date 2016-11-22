#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void menu(ifstream &plik, int &kursor, bool &tryb_hex, bool &tryb_txt, bool &powrot, int koniec);

void menu_glowne(bool &tryb_hex, bool &tryb_txt, bool &done, int &kursor);

void wyswietl_szesnastkowo(ifstream &plik, int kursor);

void wyswietl_tekstowo(ifstream &plik, int kursor);

void wyswietl_naglowek();

int main() 
{

	ifstream plik;

	bool tryb_hex = false, tryb_txt = false, done = false, powrot = true;

	string nazwa;

	cout << "Podaj nazwe pliku, wraz z rozszerzeniem: ";
	cin >> nazwa;

	plik.open(nazwa.c_str(), ios::ate);

	if (!plik.good()) 
	{
		cout << "Blad przy otwieraniu pliku!\n\n";
		system("PAUSE");
		return 0;
	}

	int kursor = 0;
	int koniec = (int)plik.tellg();

	do 
	{

		if (powrot) menu_glowne(tryb_hex, tryb_txt, done, kursor);

		if (tryb_hex) wyswietl_szesnastkowo(plik, kursor);

		if (tryb_txt) wyswietl_tekstowo(plik, kursor);

		if (tryb_hex || tryb_txt) menu(plik, kursor, tryb_hex, tryb_txt, powrot, koniec);

	} 
	while (!done);

	plik.close();
	return 0;
}

void menu_glowne(bool &tryb_hex, bool &tryb_txt, bool &done, int &kursor)
{
	system("CLS");
	kursor = 0;
	cout << "\n\n1. - Tryb TXT" << endl;
	cout << "\n2. - Tryb HEX" << endl;
	cout << "\n3. - Wyjscie" << endl;

	char wybor;
	cin >> wybor;

	do 
	{
		switch (wybor) 
		{
		case '1': 
		{
			tryb_txt = true;
			tryb_hex = false;
			break;
		};
		case '2': 
		{
			tryb_txt = false;
			tryb_hex = true;
			break;
		};
		case '3':
		{
			tryb_txt = false;
			tryb_hex = false;
			done = true;
			break;
		}
		}
	} 
	while (wybor != '1' && wybor != '2' && wybor != '3');	

	system("CLS");
}

void menu(ifstream &plik, int &kursor, bool &tryb_hex, bool &tryb_txt, bool &powrot, int koniec) 
{
	powrot = false;
	cout << "\n\n";
	if (kursor) cout << "\t\t\tu - Page Up" << endl;
	if (!plik.eof()) cout << "\t\t\td - Page Down" << endl;
	cout << "\t\t\tp - Powrot" << endl;

	char wybor;
	cin >> wybor;

	system("cls");
	/* Warunki sluzace do przewijania tekstu*/
	if (wybor == 'u' && tryb_hex) 
	{
		if (kursor >= 128) kursor -= 128;
	}
	else if (!plik.eof() && wybor == 'd' && tryb_hex)
	{
		if (kursor <= koniec - 128) kursor += 128;
	}
	else if (wybor == 'u' && tryb_txt) 
	{
		if (kursor >= 512) kursor -= 512;
	}
	else if (!plik.eof() && wybor == 'd' && tryb_txt) 
	{
		if (kursor <= koniec - 512) kursor += 512;
	}
	else if (wybor == 'p') 
	{
		powrot = true;
	}
}

void wyswietl_szesnastkowo(ifstream &plik, int kursor)
{
	char buf[16]; //bufor - 16 znaków w wierszu
	plik.clear(); //czyści flagi strumienia
	plik.seekg(kursor); //ustawia odpowiednie miejsce w pliku na współrzędne kursora; kursor się przestawia poprzez page up, page down o określoną liczbe znaków

	wyswietl_naglowek(); 

	for (int i = 0; i < 8; i++) //wyświetla 8 wierszy zaczynając od miejsca wyznaczonego przez kursor
	{
		if (plik.eof()) break; //jezeli w trakcie trwania pętli napotka koniec pliku, pętla jest przerywana aby nie wyswietlac pustych wierszy
		plik.read(buf, 16); //wczytuje 16 znaków do bufora
		cout.width(8); //ustawia szerokość pola adresu na 8 miejsc
		cout.fill('0'); //niewykorzystane miejsca są wyswietlane jako 0
		cout << hex << kursor + i*16 << "  "; //wypisuje adres na podstawie kursora oraz aktualnego obiegu pętli
		for (int i = 0; i < plik.gcount(); i++) //pętla wykonuje się tyle razy ile wczytano znaków, zazwyczaj 16 ale w przypadku ostatniego wiersza może byc ich mniej
		{
			cout << hex << (int)buf[i] << " "; //wypisuje znak jako liczbę szesnastkową, po uprzednim rzutowaniu na liczbe całkowitą
		}

		for (int i = 0; i < 16 - plik.gcount(); i++) cout << "   "; //jeśli był niepełny wiersz (ostatni) to tyle ile zabrakło znaków do 16 wypisuje przerw, dla estetyki

		for (int i = 0; i < plik.gcount(); i++)
		{
			cout << buf[i]; //wypisuje te same znaki tylko że jako tekst
		}

		cout << endl;
	}
}

void wyswietl_tekstowo(ifstream &plik, int kursor)
{
	char buf[64];
	plik.clear(); // czyszczenie flag w przypadku natrafienia na koniec pliku
	plik.seekg(kursor); // ustawienie wskaznika w pozadanym miejscu
	cout << "Tekstowe wyswietlanie pliku : \n";

	for (int i = 0; i < 8; i++) 
	{
		if (plik.eof()) break;
		plik.read(buf, 64);
		cout << "\t";
		for (int i = 0; i < plik.gcount(); i++)
		{
			cout << buf[i];
		}
		cout << endl;
	}
}

void wyswietl_naglowek()
{
	cout.width(8);
	cout.fill(NULL);
	cout << "Adres";
	cout << "  ";
	for (int i = 0; i < 10; i++)
	{
		cout << i << "  ";
	}
	for (int i = 0; i < 6; i++) 
	{
		cout << (char)(65+i) << "  ";
	}
	cout << "Tekst" << endl << endl;
}