#include <iostream>
#include <fstream> /* praca z plikiem */
#include <limits> /* limit ignorowania znakow */
#include <string> /* dla nazw plikow */

#include "plik.hh"

using namespace std;

int znajdz_rozmiar_w_pliku(const string nazwa_odczytu)
{
  int rozmiar = 0;
  ifstream plik;

  cout << "Sprawdzam poprawnosc danych zapisanych w pliku !"<<endl;

  plik.open (nazwa_odczytu.c_str(), std::ios::in);

  if(plik.is_open())
    {
      /* wczytanie pierwszej linii, ktora informuje o ilosci wierzcholkow oraz 
	 ilosci krawedzi. */
      plik >> rozmiar;	

      if(plik.bad())
	{
	  std::cerr << "Blad w pierwszej linii pliku !" << std::endl;
	  return 1;
 	}
    }

  else
    {
      cerr << "Nie mozna otworzyc pliku !"<<endl;
      return 1;
    }

  plik.close();

  return rozmiar;
}
