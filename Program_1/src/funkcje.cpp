#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>

#include "funkcje.hh"

using namespace std;


/***********************************************************************/
/*                                                                     */
/* Plik zawiera definicje funkcji wykorzystanych w programie           */
/*                                                                     */
/***********************************************************************/


/*-------------------- Wczytywanie tablicy z konsoli ------------------*/

void wczytywanie(int *tablica)
{
  for (int i=0; i<ROZMIAR_TAB; i++)
    {
      cout<<"Podaj element nr "<<i+1<<": ";
      cin>>tablica[i];
    }
}

/*---------------------------------------------------------------------*/


/*----------------------- Wyswietlanie tablicy ------------------------*/

void wyswietlanie(int *tablica)
{
  for (int i=0; i<ROZMIAR_TAB; i++)
    {
      cout<<"Wartosc elementu "<<i<<": "<<tablica[i]<<endl;
    }
}

/*---------------------------------------------------------------------*/


/*--------------------- Wczytywanie danych z pliku --------------------*/

bool wczytywanie_z_pliku (int *tablica)
{
  ifstream plik;
  int i=0;
  
  string nazwa_odczytu;
  cout<<"Podaj nazwe pliku do wczytania (bez rozszerzenia): ";
  cin>>nazwa_odczytu;
  
  /* Otworzenie pliku o nazwie wskazanej przez uzytkownika. 
     Nazwe nalezy wprowadzic bez rozszerzenia np 'dane' zostanie wczytany plik 'dane.dat' 
  */
  nazwa_odczytu += ".dat";
  plik.open (nazwa_odczytu.c_str(), ios::in);

  if(plik.is_open())    /* Jezeli uda sie otworzyc plik */
    {
      cout<<"Wczytuje dane !"<<endl;
      while (!plik.eof() && !plik.bad())  /* Dopoki nie napotkam konca pliku, albo wczytanie sie nie powiedzie */
	{
	  if( (plik>>tablica[i]).good() )
	    {
	      cout<<"Wczytano : "<<tablica[i]<<endl;
	      
	    }
	  else
	    {
	      /* Jezeli nie uda sie czytac liczby, czyli np zostanie wykryta litera, znak interpunkcyjny itp. to flaga zostaje wyczyszczona i ignoruje wejscie.
		 Uzytkownik zostaje poinformowany o tym ze w miejsce blednego znaku wpisane zostanie '0' */
	      cout<<"Znak nieprawidlowy, zostanie zastapiony przez '0'"<<endl;
	      plik.clear(); /* Wyczyszczenie flag */
	      plik.ignore(numeric_limits<streamsize>::max(),'\n'); /* pominiecie z wejscia wszystkiego, az do napotkania nowej linii */
	    }
	  i++;
	}
    }
  else /* Gdy nie uda sie wczytac pliku */
    {
      cout<<"PLIK '"<<nazwa_odczytu<<"' NIE MOZLIWY DO ODCZYTANIE LUB NIE ISTNIEJE"<<endl;
      return false;
    }

  cout<<"Wczytywanie zakonczone powodzeniem."<<endl; /* :) */

  return true;
}

/*---------------------------------------------------------------------*/

/*---------------------- Zapisywanie danych do pliku ------------------*/

bool zapisywanie_do_pliku (int *tablica)
{
  ofstream plik;
  string nazwa_zapisu;

  cout<<"Podaj nazwe pod ktora chcesz zapisac dane (bez rozszerzenia): ";
  cin>>nazwa_zapisu;

  /* Dane mozna zapisac pod dowolna nazwa.
     Rozszerzenie pliku zostanie dopisane automatycznie
     Jezeli plik z nazwa podana przez uzytkownika nie bedzie mozliwy do otworzenia (nie istnieje) to zostanie on utworzony. 
     Dane zostana zapisane z rozszerzeniem xxx.dat
  */
  nazwa_zapisu += ".dat";
  plik.open(nazwa_zapisu.c_str(), ios::out | ios::trunc);

  if(plik.good())
    {
      for(int i=0; i<ROZMIAR_TAB; i++)
	{
	  cout << "Zapisywanie elementu nr "<<i<<endl;
	  plik<<tablica[i]<<endl;
        }
    }
  else
    {
      cout<<"ZAPISANIE DO PLIKU '"<<nazwa_zapisu<<"' NIE POWIODLO SIE !!!"<<endl;
      return false;
    }

  cout<<"Zapisywanie zakonczone powodzeniem."<<endl; /* :) */

  return true;
}

/*---------------------------------------------------------------------*/

/*------------------- Zapisywanie do pliku binarnego ------------------*/

bool zapisywanie_do_pliku_binarnego (int *tablica)
{
  ofstream plik;
  string nazwa_zapisu;
  
  cout<<"Podaj nazwe pod ktora chcesz zapisac dane w postaci binarnej (bez rozszerzenia): ";
  cin>>nazwa_zapisu;

  /* Dane mozna zapisac pod dowolna nazwa.
     Rozszerzenie pliku zostanie dopisane automatycznie
     Jezeli plik z nazwa podana przez uzytkownika nie bedzie mozliwy do otworzenia (nie istnieje) to zostanie on utworzony. 
     Dane zostana zapisane z rozszerzeniem xxx.bin
  */

  nazwa_zapisu += ".bin";
  plik.open(nazwa_zapisu.c_str(), ios::out | ios::trunc | ios::binary);

  if(plik.good())
    {
      for(int i=0; i<ROZMIAR_TAB; i++)
	{
	  cout << "Zapisywanie elementu nr "<<i<<endl;
	  plik.write(reinterpret_cast<const char *>(&tablica[i]), sizeof(tablica[i]));
	}
    }
  else
    {
      cout<<"ZAPISANIE DO PLIKU '"<<nazwa_zapisu<<"' NIE POWIODLO SIE !!!"<<endl;
      return false;
    }

  cout<<"Zapisywanie zakonczone powodzeniem."<<endl; /* :) */
  
  return true;
}

/*---------------------------------------------------------------------*/


/*------------------ Wczytywanie z pliku binarnego --------------------*/

bool wczytywanie_z_pliku_binarnego (int *tablica)
{
  ifstream plik;

  string nazwa_odczytu;
  cout<<"Podaj nazwe pliku binarnego do wczytania (bez rozszerzenia): ";
  cin>>nazwa_odczytu;
  
  /* Otworzenie pliku o nazwie wskazanej przez uzytkownika. 
     Nazwe nalezy wprowadzic bez rozszerzenia np 'dane' zostanie wczytany plik 'dane.bin' 
  */
  nazwa_odczytu += ".bin";
  plik.open (nazwa_odczytu.c_str(), ios::in | ios::binary);
  
  if(plik.is_open())
    {
      cout<<"Wczytuje dane !"<<endl;
          
      for(int i = 0; i<ROZMIAR_TAB; i++)	
	{
	  plik.read(reinterpret_cast<char *>(&tablica[i]),sizeof(tablica[i]));
          cout<<"Wczytano : "<<tablica[i]<<endl;	      
	}
    }
  else /* Gdy otworzenie pliku sie nie powiedzie */
    {
      cout<<"PLIK '"<<nazwa_odczytu<<"' NIE MOZLIWY DO ODCZYTANIE LUB NIE ISTNIEJE"<<endl;
      return false;
    }

  cout<<"Wczytywanie zakonczone powodzeniem."<<endl; /* :) */

  return true;
}

/*---------------------------------------------------------------------*/


/*--------------- Wypelnienie tablicy liczbami losowymi ---------------*/

void wypelnianie_liczbami_losowymi (int *tablica)
{
  int min,max,ilosc_liczb,liczba; /* zmienne do przechowywania zakresu losowania */
  cout<<"Podaj zakres generowania liczb losowych i ilosc liczb do wygenerowania."<<endl;

  cout<<"Wartosc minimalna: ";
  cin>>min;
  cout<<endl;

  cout<<"Wartosc maksymalna: ";
  cin>>max;
  cout<<endl;

  cout<<"Ile liczb wygenerowac ? ";
  cin>>ilosc_liczb;
  cout<<endl;

  /* Ilosc liczb do wygenerowania musi byc mniejsza lub rowna liczbie elementow tablicy (oczywiscie dodatnia). 
  */
  if(ilosc_liczb>0 && ilosc_liczb<=ROZMIAR_TAB)
    {
      for(int i=0; i<ilosc_liczb; i++)
	{
	  liczba=(( rand() % (max-min) ) + min );
	  cout << "Wylosowano liczbe: " <<liczba<<endl;
	  tablica[i]=liczba;
	}
    }
  else
    {
      cout<<"Ilosc wygenerowanych liczb musi byc z przedzialu: 1-"<<ROZMIAR_TAB<<" !"<<endl;
    }
}

/*---------------------------------------------------------------------*/

/*---------------------- Tworzenie kopii tablicy ----------------------*/

int *dynamiczna_kopia (int *tablica)
{
  int *tablica_kopia = new int[ROZMIAR_TAB];
  
  cout<<"Tworze kopie tablicy"<<endl;
  
  for(int i=0; i<ROZMIAR_TAB; i++)
    {
      tablica_kopia[i]=tablica[i];
    }
  return tablica_kopia;
}

/*---------------------------------------------------------------------*/

/*---------------------- Wyswietlanie kopii tablicy -------------------*/

int wyswietlenie_kopii (int *tablica)
{
  int *tablica_kopia = dynamiczna_kopia(tablica);
  cout<<"Kopia tablicy: "<<endl;
  for (int i=0; i<ROZMIAR_TAB; i++)
    {
      cout<<"Kopia -> element "<<i<<" : "<<*(tablica_kopia + i)<<endl;
    }
  return 0;
}

/*---------------------------------------------------------------------*/
