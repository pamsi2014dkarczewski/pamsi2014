#include <iostream>

#include "kopiec.hh"
#include "typ.hh"

#define ROZMIAR 10 /* ROZMIAR okresla wielkosc tablicy */

/* Program 3.2 z trzeciej listy zadan.

   Kopiec zostal zaimplementowany za pomoca STL. Mozliwe operacje do wykonania:
   - wygenerowanie liczb pseudolosowych z dowolnego przedzialu
   - stworzenie kopca
   - wyswietlenie kopca
   - usuniecie elementu z poczatku (wartosc najwieksza)

   Program dziala na roznych typach danych. W celu ulatwienia testowania
   programu plik 'makefile' zawiera definicje typow dla jakich program byl
   testowany. 

   (skrot)
   make int --> kompilacja dla int
   make char --> kompilacja dla char
   itd.

   Program kompiluje sie bez bledow i bez ostrzezen.
   Testowany byl na typach: int, float, double
*/

using namespace std;

int main ()
{

  srand( time( NULL ) ); /* generowanie liczb losowych */
 
  char opcja;  /* zmienna wyboru opcji w menu */
  
  TYP tablica[ROZMIAR] = {0}; /* tablica wypelniona zerami */

  int roz = ROZMIAR-1; /* rozmiar tablicy */

  cout << "---------------------------------------------"<<endl;
  cout << "| PROGRAM SKOMPILOWANO DLA TYPU: "<<NAZWA_TYPU<<endl;
  cout << "---------------------------------------------"<<endl;

  cout << "Lista 3, Program 3.2 |zajecia PAMSI| kopiec (STL)."<<endl;

  while(true)
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << "1.Generowanie liczb pseudolosowych"<<endl;
      cout << "2.Stworzenie kopca / przywrocenie wlasnosci"<<endl;
      cout << "3.Wyswietlenie kopca"<<endl;
      cout << "4.Usuniecie elementu ze szczytu kopca"<<endl;
      cout << "0.Zakonczenie dzialania programu"<<endl;
      cout << "Twoj wybor (0-4): ";

      cin >> opcja;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
            
      cout<<endl;
    
      switch(opcja)
	{
	case '0': 
	  cout<<"Koniec dzialania programu"<<endl;
	  cout<<"_________________________"<<endl;
	  return false;

	case '1': /* generowanie liczb pseudolosowych */
	  generowanie_liczb(tablica, roz);
	  break;

	case '2': /* stworzenie kopca */
	  make_heap(tablica,tablica+roz);
	  break;

	case '3': /* wyswietlenie kopca */
	  wyswietl_kopiec(tablica, roz);
	  break;
	  
	case '4': /* usuniecie wartosci ze szczytu (wartosc najwieksza) */
	  cout<<"Wartosc usunieta ze szczytu kopca: "<<tablica[0];
	  tablica[0]=tablica[roz-1];
	  roz--;
	  break;

	default: /* opcja nierozpoznana */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu 0-4"<<endl;
	  cout << "--------------------------------"<<endl;
	} /* end switch */
    } /* end while */
} /* end main */



