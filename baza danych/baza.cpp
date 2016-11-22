#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
	string imie, nazwisko, email;
	int indeks;
};

struct Projekt {
	int student;
	int nr;
	string data;
};

struct Uwaga {
	int student;
	int projekt;
	string data;
	string tresc;
};

void menu_glowne(fstream &osoby, fstream &projekty);
void menu_studenta(fstream &osoby, fstream &projekty);
void menu_projektu(fstream &projekty);
void menu_uwag(fstream &uwagi);
void dodajstudenta(fstream &osoby);
void usunstudenta(fstream &osoby);
void modyfikujstudenta(fstream &osoby);
void wyswietlstudentow(fstream &osoby);
void wyszukajstudenta(fstream &osoby);
void dodajprojekt(fstream &projekty);
void usunprojekt(fstream &projekty);
void modyfikujprojekt(fstream &projekty);
void wyswietlprojektystudenta(fstream &projekty);
void wyswietlprojekty(fstream &projekty);
void wyswietluwagi(fstream &uwagi);
void dodajuwage(fstream &uwagi);
void usunuwage(fstream &uwagi);
void modyfikujuwage(fstream &uwagi);

int main() {

	fstream osoby, projekty, uwagi;
	char wybor;
	do {
		system("CLS");
		cout << "Menu :\n";
		cout << "1. - Studenci\n\n";
		cout << "2. - Projekty\n\n";
		cout << "3. - Uwagi\n\n";
		cout << "4. - Wyjscie\n\n";
		cin >> wybor;
		switch (wybor) {
		case '1': {
			menu_studenta(osoby, projekty);
			break;
		}
		case '2': {
			menu_projektu(projekty);
			break;
		}
		case '3': {
			menu_uwag(uwagi);
			break;
		}
		case '4':
			return 0;
		}
	} while (true);
}

void menu_studenta(fstream &osoby, fstream &projekty) {
	bool done = false;
	do {
		char wybor;
		system("CLS");
		cout << "Menu:\n";
		cout << "1. - Dodaj studenta\n\n";
		cout << "2. - Usun studenta\n\n";
		cout << "3. - Modyfikuj studenta\n\n";
		cout << "4. - Wyswietl studentow\n\n";
		cout << "5. - Wyszukaj studenta\n\n";
		cout << "6. - Wyswietl projekty studenta\n\n";
		cout << "0. - Wyjdz\n\n";
		cin >> wybor;
		switch (wybor) {
		case '1': {
			dodajstudenta(osoby);
			system("PAUSE");
			break;
		}
		case '2': {
			usunstudenta(osoby);
			system("PAUSE");
			break;
		}
		case '3': {
			modyfikujstudenta(osoby);
			system("PAUSE");
			break;
		}
		case '4': {
			wyswietlstudentow(osoby);
			system("PAUSE");
			break;
		}
		case '5': {
			wyszukajstudenta(osoby);
			system("PAUSE");
			break;
		}
		case '6': {
			wyswietlprojektystudenta(projekty);
			system("PAUSE");
			break;
		}
		case '0': {
			done = true;
		}
		}
	} while (!done);
}

void menu_projektu(fstream &projekty) {
	bool done = false;
	do {
		char wybor;
		system("CLS");
		cout << "Menu:\n";
		cout << "1. - Dodaj projekt\n\n";
		cout << "2. - Usun projekt\n\n";
		cout << "3. - Modyfikuj projekt\n\n";
		cout << "4. - Wyswietl wszystkie nadeslane projekty\n\n";
		cout << "0. - Wyjdz\n\n";
		cin >> wybor;
		switch (wybor) {
		case '1': {
			dodajprojekt(projekty);
			system("PAUSE");
			break;
		}
		case '2': {
			usunprojekt(projekty);
			system("PAUSE");
			break;
		}
		case '3': {
			modyfikujprojekt(projekty);
			system("PAUSE");
			break;
		}
		case '4': {
			wyswietlprojekty(projekty);
			system("PAUSE");
			break;
		}
		case '0': {
			done = true;
		}
		}
	} while (!done);
}

void menu_uwag(fstream &uwagi) {
	bool done = false;

	do {
		char wybor;
		system("CLS");
		cout << "Menu:\n";
		cout << "1. - Dodaj uwage\n\n";
		cout << "2. - Usun uwage\n\n";
		cout << "3. - Modyfikuj uwage\n\n";
		cout << "4. - Wyswietl uwagi\n\n";
		cout << "0. - Wyjdz\n\n";
		cin >> wybor;
		switch (wybor)
		{
		case '1': {
			dodajuwage(uwagi);
			system("PAUSE");
			break;
		}
		case '2': {
			usunuwage(uwagi);
			system("PAUSE");
			break;
		}
		case '3': {
			modyfikujuwage(uwagi);
			system("PAUSE");
			break;
		}
		case '4': {
			wyswietluwagi(uwagi);
			system("PAUSE");
			break;
		}
		case '0': {
			done = true;
		}
		}

	} while (!done);
}

void dodajstudenta(fstream &osoby) {
	system("CLS");
	osoby.open("student.txt", ios::app);
	if (osoby.good()) {
		Student nowy;
		cout << "Wprowadz dane nowego studenta:\n";
		cout << "\tImie: ";			cin >> nowy.imie;
		cout << "\tNazwisko: ";		cin >> nowy.nazwisko;
		cout << "\tNr indeksu: ";	cin >> nowy.indeks;
		cout << "\tE-mail: ";		cin >> nowy.email;
		osoby << nowy.imie << " " << nowy.nazwisko << " " << nowy.indeks << " " << nowy.email << endl;
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	osoby.close();
	cout << "Dodawanie studenta przebieglo pomyslnie!\n" << endl;
}

void usunstudenta(fstream &osoby) {
	wyswietlstudentow(osoby);
	ofstream temp;
	bool usunieto = false;
	osoby.open("student.txt");
	if (osoby.good()) {
		Student szukany, buf;
		cout << "\nWprowadz indeks studenta, ktorego chcesz usunac: ";
		cin >> szukany.indeks;
		temp.open("temp.txt");
		while (osoby >> buf.imie >> buf.nazwisko >> buf.indeks >> buf.email) {
			if (szukany.indeks != buf.indeks) temp << buf.imie << " " << buf.nazwisko << " " << buf.indeks << " " << buf.email << endl;
			else usunieto = true;
		}
		temp.close();
	}
	else{
		cout << "Brak pliku!\n";
		return;
	}
	osoby.close();
	if (usunieto) {
		remove("student.txt");
		rename("temp.txt", "student.txt");
		cout << "Student usuniety pomyslnie!\n";
	}
	else cout << "Nie ma studenta o takim numerze indeksu!\n";
}

void modyfikujstudenta(fstream &osoby){
	wyswietlstudentow(osoby);
	ofstream temp;
	bool zmieniono = false;
	osoby.open("student.txt");
	if (osoby.good()) {
		Student szukany, buf, nowy;
		cout << "\nWprowadz indeks studenta, ktorego chcesz zmienic: ";
		cin >> szukany.indeks;
		temp.open("temp.txt");
		while (osoby >> buf.imie >> buf.nazwisko >> buf.indeks >> buf.email){
			if (szukany.indeks != buf.indeks) temp << buf.imie << " " << buf.nazwisko << " " << buf.indeks << " " << buf.email << endl;
			else{
				cout << "Wprowadz nowe dane studenta:\n";
				cout << "\tImie: ";			cin >> nowy.imie;
				cout << "\tNazwisko: ";		cin >> nowy.nazwisko;
				cout << "\tNr indeksu: ";	cin >> nowy.indeks;
				cout << "\tE-mail: ";		cin >> nowy.email;
				temp << nowy.imie << " " << nowy.nazwisko << " " << nowy.indeks << " " << nowy.email << endl;
				zmieniono = true;
			}
		}
		temp.close();
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	osoby.close();
	if (zmieniono) {
		remove("student.txt");
		rename("temp.txt", "student.txt");
		cout << "Dane studenta zmienione pomyslnie!\n";
	}
	else cout << "Nie ma studenta o takim numerze indeksu!\n";
	
}

void wyswietlstudentow(fstream &osoby){
	system("CLS");
	osoby.open("student.txt");
	if (osoby.good()){
		Student buf;
		cout << "Imie  Nazwisko  Nr Indeksu  E-mail" << endl << endl;
		while (osoby >> buf.imie >> buf.nazwisko >> buf.indeks >> buf.email){
			cout << buf.imie << "  " << buf.nazwisko << "  " << buf.indeks << "  " << buf.email << endl;
		}
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	osoby.close();
}

void wyszukajstudenta(fstream &osoby){
	system("CLS");
	osoby.open("student.txt");
	if (osoby.good()){
		Student szukany, buf;
		char wybor;
		cout << "Wyszukac studenta po (1)indeksie, (2)nazwisku? ";
		cin >> wybor;

		if (wybor == '1'){
			cout << "Wprowadz indeks studenta, ktorego chcesz wyszukac: ";
			cin >> szukany.indeks;
			cout << "Imie  Nazwisko  Nr Indeksu  E-mail" << endl << endl;
			while (osoby >> buf.imie >> buf.nazwisko >> buf.indeks >> buf.email){
				if (szukany.indeks == buf.indeks){
					cout << buf.imie << "  " << buf.nazwisko << "  " << buf.indeks << "  " << buf.email << endl;
				}
			}
		}
		else if (wybor == '2'){
			cout << "Wprowadz nazwisko studenta, ktorego chcesz wyszukac: ";
			cin >> szukany.nazwisko;
			cout << "Imie  Nazwisko  Nr Indeksu  E-mail" << endl << endl;
			while (osoby >> buf.imie >> buf.nazwisko >> buf.indeks >> buf.email){
				if (szukany.nazwisko == buf.nazwisko){
					cout << buf.imie << "  " << buf.nazwisko << "  " << buf.indeks << "  " << buf.email << endl;
				}
			}
		}
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	osoby.close();
}

void dodajprojekt(fstream &projekty) {
	system("CLS");
	projekty.open("projekty.txt", ios::app);
	if (projekty.good()) {
		Projekt nowy;
		cout << "Wprowadz dane nowego projektu:\n";
		cout << "\tNr indeksu studenta: ";		cin >> nowy.student;
		cout << "\tNr projektu: ";				cin >> nowy.nr;
		cout << "\tData nadeslania projektu: ";	cin >> nowy.data;
		projekty << nowy.student << " " << nowy.nr << " " << nowy.data << endl;
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	projekty.close();
	cout << "Projekt dodany pomyslnie!\n";
}

void usunprojekt(fstream &projekty) {
	wyswietlprojekty(projekty);
	ofstream temp;
	bool usunieto = false;
	projekty.open("projekty.txt");
	if (projekty.good()) {
		Projekt szukany, buf;
		cout << "\nWprowadz nr projektu, ktory chcesz usunac: ";
		cin >> szukany.nr;
		temp.open("temp.txt");
		while (projekty >> buf.student >> buf.nr >> buf.data) {
			if (szukany.nr != buf.nr) temp << buf.student << " " << buf.nr << " " << buf.data << endl;
			else usunieto = true;
		}
		temp.close();
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	projekty.close();
	if (usunieto) {
		remove("projekty.txt");
		rename("temp.txt", "projekty.txt");
		cout << "Projekt usuniety pomyslnie!\n";
	}
	else cout << "Nie ma projektu o takim numerze!\n";
	
}

void modyfikujprojekt(fstream &projekty) {
	wyswietlprojekty(projekty);
	ofstream temp;
	bool zmieniono = false;
	projekty.open("projekty.txt");
	if (projekty.good()) {
		Projekt szukany, buf, nowy;
		cout << "\nWprowadz nr projektu, ktory chcesz zmienic: ";
		cin >> szukany.nr;
		temp.open("temp.txt");
		while (projekty >> buf.student >> buf.nr >> buf.data) {
			if (szukany.nr != buf.nr) temp << buf.student << " " << buf.nr << " " << buf.data << endl;
			else {
				cout << "Wprowadz nowe dane projektu:\n";
				cout << "\tNr indeksu studenta: ";		cin >> nowy.student;
				cout << "\tNr projektu: ";				cin >> nowy.nr;
				cout << "\tData nadeslania projektu: ";	cin >> nowy.data;
				temp << nowy.student << " " << nowy.nr << " " << nowy.data << endl;
				zmieniono = true;
			}
		}
		temp.close();
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	projekty.close();
	if (zmieniono) {
		remove("projekty.txt");
		rename("temp.txt", "projekty.txt");
		cout << "Projekt zamieniony pomyslnie!\n";
	}
	else cout << "Nie ma projektu o takim numerze!\n";
	
}

void wyswietlprojekty(fstream &projekty) {
	system("CLS");
	projekty.open("projekty.txt");
	if (projekty.good()) {
		Projekt buf;
		cout << "Student  Nr  Data" << endl << endl;
		while (projekty >> buf.student >> buf.nr >> buf.data ) {
			cout << buf.student << "  " << buf.nr << "  " << buf.data << endl;
		}
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	projekty.close();
}

void wyswietlprojektystudenta(fstream &projekty) {
	projekty.open("projekty.txt");
	if (projekty.good()) {
		Projekt buf;
		int indeks;
		cout << "Podaj nr indeksu studenta, ktorego projekty chcesz wyswietlic: ";
		cin >> indeks;

		while (projekty >> buf.student >> buf.nr >> buf.data) {
			if (buf.student == indeks) cout << "Nr indeksu studenta: " << buf.student << " Nr projketu: " << buf.nr << " Data nadeslania: " << buf.data << endl;
		}
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	projekty.close();
}

void wyswietluwagi(fstream &uwagi) {
	system("CLS");
	uwagi.open("uwagi.txt");
	if (uwagi.good()) {
		Uwaga buf;
		cout << "Student  Projket  Data  Tresc" << endl << endl;
		while (uwagi >> buf.student >> buf.projekt >> buf.data) {
			getline(uwagi, buf.tresc);
			cout << buf.student << "  " << buf.projekt << "  " << buf.data << "  " << buf.tresc << endl;
			cout << "***\n";
		}
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	uwagi.close();
}

void dodajuwage(fstream &uwagi) {
	system("CLS");
	uwagi.open("uwagi.txt", ios::app);
	if (uwagi.good()) {
		Uwaga nowy;
		cout << "Wprowadz dane nowej uwagi:\n";
		cout << "\tNr indeksu studenta, ktorego dotyczy uwaga: ";	cin >> nowy.student;
		cout << "\tNr projektu, ktorego dotyczy uwaga: ";			cin >> nowy.projekt;
		cout << "\tData wystawienia uwagi: ";						cin >> nowy.data;
		cout << "\tTresc uwagi (max 400 znakow): ";	cin.ignore();	getline(cin, nowy.tresc);

		uwagi << nowy.student << " " << nowy.projekt << " " << nowy.data << " " << nowy.tresc << endl;
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	uwagi.close();
	cout << "Uwaga dodany pomyslnie!\n";
}

void usunuwage(fstream &uwagi) {
	wyswietluwagi(uwagi);
	ofstream temp;
	bool usunieto = false;	
	uwagi.open("uwagi.txt");
	temp.open("temp.txt");
	if (uwagi.good()) {
		Uwaga szukany, buf;
		cout << "\nWprowadz dane uwagi do usuniecia:\n";
		cout << "\tNr indeksu studenta, ktorego dotyczy uwaga: ";	cin >> szukany.student;
		cout << "\tNr projektu, ktorego dotyczy uwaga: ";			cin >> szukany.projekt;
		cout << "\tData wystawienia uwagi: ";						cin >> szukany.data;
	
		while (uwagi >> buf.student >> buf.projekt >> buf.data) {
			getline(uwagi, buf.tresc);
			if (szukany.student == buf.student && szukany.projekt == buf.projekt && szukany.data == buf.data) usunieto = true;
			else temp << buf.student << " " << buf.projekt << " " << buf.data << " " << buf.tresc << endl;
		}
	}
	else {
		cout << "hau\n";
		cout << "Brak pliku!\n";
		return;
	}
	uwagi.close();
	temp.close();

	if (usunieto) {
		cout << "Uwaga usunieta pomyslnie!\n";
		remove("uwagi.txt");
		rename("temp.txt", "uwagi.txt");
	}
	else cout << "Nie znaleziono takiej uwagi!\n";
}

void modyfikujuwage(fstream &uwagi) {
	wyswietluwagi(uwagi);
	ofstream temp;
	bool zmieniono = false;
	uwagi.open("uwagi.txt");
	temp.open("temp.txt");
	if (uwagi.good()) {
		Uwaga szukany, buf, nowa;
		cout << "Wprowadz dane uwagi, ktora chcesz zmienic:\n";
		cout << "\tNr indeksu studenta, ktorego dotyczy uwaga: ";	cin >> szukany.student;
		cout << "\tNr projektu, ktorego dotyczy uwaga: ";			cin >> szukany.projekt;
		cout << "\tData wystawienia uwagi: ";						cin >> szukany.data;

		while (uwagi >> buf.student >> buf.projekt >> buf.data) {
			getline(uwagi, buf.tresc);

			if (szukany.student == buf.student && szukany.projekt == buf.projekt && szukany.data == buf.data) {
				cout << "Wprowadz studenta: "; cin >> nowa.student;
				cout << "Wprowadz projekt: "; cin >> nowa.projekt;
				cout << "Wprowadz date: "; cin >> nowa.data;
				cout << "Wprowadz nowa tresc uwagi:\n";
				cin.ignore();
				getline(cin, nowa.tresc);
				temp << nowa.student << " " << nowa.projekt << " " << nowa.data << " " << nowa.tresc << endl;
				zmieniono = true;
			}
			else temp << buf.student << " " << buf.projekt << " " << buf.data << " " << buf.tresc << endl;
		}
	}
	else {
		cout << "Brak pliku!\n";
		return;
	}
	uwagi.close();
	temp.close();

	

	if (zmieniono) {
		remove("uwagi.txt");
		rename("temp.txt", "uwagi.txt");
		cout << "Uwaga zmieniona pomyslnie!\n";
	}
	else cout << "Nie znaleziono uwagi.\n";
	
}