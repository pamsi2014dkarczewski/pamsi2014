#include <iostream>
#include <fstream> /* praca z plikiem */
#include <limits> /* limit ignorowania znakow */
#include <string> /* dla nazw plikow */

#include "plik.hh"

using namespace std;

int znajdz_rozmiar_w_pliku(const string nazwa_odczytu)
{
  int rozmiar = 0;
  int il_krawedzi, zrodlo;
  ifstream plik;

  cout << "Sprawdzam poprawnosc danych zapisanych w pliku !"<<endl;

  plik.open (nazwa_odczytu.c_str(), std::ios::in);

  if(plik.is_open())
    {
      plik >> il_krawedzi >> rozmiar >> zrodlo;

      while (!plik.eof() && !plik.bad())
	{
	  plik.ignore(numeric_limits<streamsize>::max(),'\n');
	}	
    }

  else
    {
      cerr << "Nie mozna otworzyc pliku !"<<endl;
      return 0;
    }

  plik.close();

  return rozmiar;
}
