#ifndef FUNKCJE_HH
#define FUNKCJE_HH

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>

#include "typ.hh"

using namespace std;


/***************************** KLASA c_tablica ****************************/

template <typename Typ>
class c_tablica
{
private:
  Typ *tablica;
  int rozmiar;

public:

  /* stworzenie tablicy oraz wyzerowanie jej */
  c_tablica<Typ>(int rozmiar2) /* konstruktor */
  {
    rozmiar=rozmiar2;
    tablica = new Typ[rozmiar];
  }

  void wczytywanie ();
  void wyswietlanie ();
  bool wczytywanie_z_pliku();
  bool zapisywanie_do_pliku();
  bool wczytywanie_z_pliku_binarnego ();
  bool zapisywanie_do_pliku_binarnego ();
  void wypelnianie_liczbami_losowymi ();
  c_tablica& operator = (c_tablica &kopia);

  ~c_tablica() /* destruktor */
  {
    delete[] tablica;
  }

}; //end class


/******************************* Metody **************************************/

template<typename Typ>
void c_tablica<Typ>::wczytywanie()
{
  for (int i=0; i<rozmiar; i++)
    {
      cout<<"Podaj element nr "<<i+1<<": ";
      cin>>tablica[i];
    }
}

template<typename Typ>
void c_tablica<Typ>::wyswietlanie()
{
  for (int i=0; i<rozmiar; i++)
    {
      cout<<"Wartosc elementu "<<i<<": "<<tablica[i]<<endl;
    }
}

template<typename Typ>
bool c_tablica<Typ>::wczytywanie_z_pliku ()
{
  ifstream plik;
  int i=0;
  
  string nazwa_odczytu;
  cout<<"Podaj nazwe pliku do wczytania: ";
  cin>>nazwa_odczytu;
  
  nazwa_odczytu += ".dat";
  plik.open (nazwa_odczytu.c_str(), ios::in);

  if(plik.is_open())
    {
      cout<<"Wczytuje dane !"<<endl;
      while (!plik.eof() && !plik.bad() && (i<rozmiar))
	{
	  if( (plik>>tablica[i]).good() )
	    {
	      cout<<"Wczytano : "<<tablica[i]<<endl;
	      
	    }
	  else
	    {
	      cout<<"Znak nieprawidlowy, zostanie zastapiony przez '0'"<<endl;
	      plik.clear(); 
	      plik.ignore(numeric_limits<streamsize>::max(),'\n');	    }
	  i++;
	}
    }
  else 
    {
      cout<<"PLIK '"<<nazwa_odczytu<<"' NIE MOZLIWY DO ODCZYTANIE LUB NIE ISTNIEJE"<<endl;
      return false;
    }

  cout<<"Wczytywanie zakonczone powodzeniem."<<endl; 

  return true;
}

template<typename Typ>
bool c_tablica<Typ>::zapisywanie_do_pliku ()
{
  ofstream plik;
  string nazwa_zapisu;

  cout<<"Podaj nazwe pod ktora chcesz zapisac dane: ";
  cin>>nazwa_zapisu;

  nazwa_zapisu += ".dat";
  plik.open(nazwa_zapisu.c_str(), ios::out | ios::trunc);

  if(plik.good())
    {
      for(int i=0; i<rozmiar; i++)
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

  cout<<"Zapisywanie zakonczone powodzeniem."<<endl; 

  return true;
}

template<typename Typ>
bool c_tablica<Typ>::zapisywanie_do_pliku_binarnego ()
{
  ofstream plik;
  string nazwa_zapisu;
  
  cout<<"Podaj nazwe pod ktora chcesz zapisac dane w postaci binarnej: ";
  cin>>nazwa_zapisu;

  nazwa_zapisu += ".bin";
  plik.open(nazwa_zapisu.c_str(), ios::out | ios::trunc | ios::binary);

  if(plik.good())
    {
      for(int i=0; i<rozmiar; i++)
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

  cout<<"Zapisywanie zakonczone powodzeniem."<<endl;
  
  return true;
}

template<typename Typ>
bool c_tablica<Typ>::wczytywanie_z_pliku_binarnego ()
{
  ifstream plik;

  string nazwa_odczytu;
  cout<<"Podaj nazwe pliku binarnego do wczytania: ";
  cin>>nazwa_odczytu;
  
  nazwa_odczytu += ".bin";
  plik.open (nazwa_odczytu.c_str(), ios::in | ios::binary);
  
  if(plik.is_open())
    {
      cout<<"Wczytuje dane !"<<endl;
          
      for(int i = 0; i<rozmiar; i++)	
	{
	  plik.read(reinterpret_cast<char *>(&tablica[i]),sizeof(tablica[i]));
          cout<<"Wczytano : "<<tablica[i]<<endl;	      
	}
    }
  else
    {
      cout<<"PLIK '"<<nazwa_odczytu<<"' NIE MOZLIWY DO ODCZYTANIE LUB NIE ISTNIEJE"<<endl;
      return false;
    }

  cout<<"Wczytywanie zakonczone powodzeniem."<<endl; 

  return true;
}

template<typename Typ>
void c_tablica<Typ>::wypelnianie_liczbami_losowymi ()
{
  int min,max,ilosc_liczb,liczba; 
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

  if(ilosc_liczb>0 && ilosc_liczb<=rozmiar)
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
      cout<<"Ilosc wygenerowanych liczb musi byc z przedzialu: 1-"<<rozmiar<<" !"<<endl;
    }
}

template <typename Typ>
c_tablica<Typ>& c_tablica<Typ>::operator = (c_tablica<Typ> &kopia)
{
  for (int i = 0; i<rozmiar; i++)
    {
      tablica[i]=kopia.tablica[i];
    }
  return *this;
}

#endif
