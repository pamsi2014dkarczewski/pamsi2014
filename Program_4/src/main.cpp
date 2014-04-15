#include <iostream>
#include <cstdlib> /*rand*/
#include <random> /* biblioteka dla generowania rozkladow */
#include <chrono> /* biblioteka dla obliczania czasu */

#include "sortowanie.hh"
#include "tester.hh"
#include "eksperyment.hh"
#include "typ.hh"

/* Program 4 z czwartej listy zadan. 
   wersja: v.1.1 */

using namespace std;

int main ()
{
  srand( time( NULL ) );
  unsigned int rozmiar; /* rozmiar tablicy */

  cout << "---------------------------------------------"<<endl;
  cout << "| PROGRAM SKOMPILOWANO DLA TYPU: "<<NAZWA_TYPU<<endl;
  cout << "---------------------------------------------"<<endl;

  cout<<"Lista 4, Program 4 |zajecia PAMSI| sortowanie."<<endl<<endl;
 
  rozmiar_tablicy(rozmiar); /* tester.cpp */
  
  /* dynamiczna tablica */
  TYP *tablica; 
  tablica = new TYP[rozmiar]; 
      
  /* tablica przechowuje wygenerowany rozklad liczb */
  TYP *rozklad;
  rozklad = new TYP[rozmiar];

  nowy_eksperyment(tablica,rozklad,rozmiar); /* eksperyment.hh */
 
} /* end main */
