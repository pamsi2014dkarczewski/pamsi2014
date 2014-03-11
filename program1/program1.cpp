#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#define ROZMIAR 10
using namespace std;


void wczytajtablice(int *tabl, unsigned int roz)
{
	for (int i = 0; i < roz; i++)
		cin >> tabl[i];
}
/////////////////////////////////////////////////////////

void wyswietltablice(int *tabl, unsigned int roz)
{
	for (int i = 0; i < roz; i++)
		cout << tabl[i] << endl;
}
/////////////////////////////////////////////////////////

void wczytajzpliku(fstream & plik, int *tab, unsigned int roz)
{
	int i = 0;
	while (!plik.eof() && i<roz)
	{		
		plik >> tab[i];
		i++;
	}
	plik.close();
}
/////////////////////////////////////////////////////////

void zapiszdopliku(fstream & plik, int *tab, unsigned int roz)
{

	for (int i = 0; i < roz; i++)
	plik << tab[i] << " ";
	plik.close();
}
/////////////////////////////////////////////////////////

void WypelnianieTablicy(int *tab, unsigned int roz)
{
	srand(time(NULL));
	for (int i = 0; i < roz; i++)
		tab[i] = rand() % 100;
}
/////////////////////////////////////////////////////////

int *kopia(int *tab, int roz)
{
	int *wsk = new int[roz];
	for (int i = 0; i < roz; i++)
		wsk[i] = tab[i];
	for (int i = 0; i < roz; i++)
		cout << wsk[i] << " ";
	//delete[] wsk;
	return wsk;

}
/////////////////////////////////////////////////////////

void ZapisywanieDoPlikuBinarnego(fstream & plik, int *tab, unsigned int roz)
{
	char zap;
	for (int i = 0; i < roz; i++)
	{
		zap = tab[i];
		plik.write((char*)&zap, sizeof(zap));
	}
	plik.close();
}
/////////////////////////////////////////////////////////

void WczytywaniePlikuBinarnego(fstream & plik, int *tab, unsigned int roz)
{
	char temp;
	
	for (int i = 0; i < roz; i++)
	{
		plik.read((char*)&temp, sizeof(temp));
		tab[i] = (int)temp;
	}
	plik.close();
}
/////////////////////////////////////////////////////////

int main()
{
	int tab[ROZMIAR];
	
	unsigned int opcja;

	do {
		cout << "1.Wczytanie tablicy z konsoli" << endl;
		cout << "2.Wyswietlenie tablicy" << endl;
		cout << "3.Wczytywanie z pliku tekstowego" << endl;
		cout << "4.Zapisywanie do pliku tekstowego" << endl;
		cout << "5.Wczytywanie z pliku binarnego" << endl;
		cout << "6.Zapisywanie do pliku binarnego" << endl;
		cout << "7.Wypelnianie tablicy" << endl;
		cout << "8.Tworzenie dynamicznej kopii wyswietlenie kopii" << endl;
		cout << "0.Koniec" << endl;
		cout << "Wybierz opcje" << endl;

		cin >> opcja;
		switch (opcja)
		{
		case 0: break;
		case 1: {wczytajtablice(tab, ROZMIAR); break; }
		case 2: {wyswietltablice(tab, ROZMIAR); break; }
		case 3: {fstream plik("tablica.txt");  wczytajzpliku(plik, tab, ROZMIAR); break; }
		case 4: {fstream plik("tablica.txt");  zapiszdopliku(plik, tab, ROZMIAR); break; }
		case 5: {fstream plik("tablicab.dat",ios::in | ios::binary);  WczytywaniePlikuBinarnego(plik, tab, ROZMIAR); break; }
		case 6: {fstream plik("tablicab.dat",ios::out | ios::binary);  ZapisywanieDoPlikuBinarnego(plik, tab, ROZMIAR); break; }
		case 7: {WypelnianieTablicy(tab, ROZMIAR); break; }
		case 8: {kopia(tab, ROZMIAR); break; }
		}
	} while (opcja != 0);

	system("pause");
	return 0;
}