#include <iostream>

#include "kopiec.hh"
#include "typ.hh"

#define ROZMIAR 31 /* ROZMIAR okresla ilosc elementow w tablicy */

/* Program 3.2 z trzeciej listy zadan.

   Dodano:
   - wyswietlenie kopca w formie graficznej.
   - generowanie kolejnych cyfr liczby PI

   Kopiec zostal zaimplementowany za pomoca STL. Mozliwe operacje do wykonania:
   - wygenerowanie liczb pseudolosowych z przedzialu <0,9>
   - stworzenie kopca
   - wyswietlenie kopca (w formie tablicy i formie 'graficznej')
   - usuniecie elementu z poczatku (wartosc najwieksza)
   - wygenerowanie kolejnych cyfr liczby PI

   Program kompiluje sie bez bledow i bez ostrzezen.
*/

using namespace std;

int main ()
{

  srand( time( NULL ) ); /* generowanie liczb losowych */
 
  char opcja;  /* zmienna wyboru opcji w menu */
  
  TYP tablica[ROZMIAR+1] = {0}; /* tablica wypelniona zerami */
 
  int roz = ROZMIAR; /* rozmiar tablicy */

  cout << "---------------------------------------------"<<endl;
  cout << "| PROGRAM SKOMPILOWANO DLA TYPU: "<<NAZWA_TYPU<<endl;
  cout << "---------------------------------------------"<<endl;

  cout << "Lista 3, Program 3.2 |zajecia PAMSI| kopiec (STL)."<<endl;

  while(true)
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << "  1.Generowanie liczb pseudolosowych"<<endl;
      cout << "  2.Stworzenie kopca / przywrocenie wlasnosci"<<endl;
      cout << "  3.Wyswietlenie kopca"<<endl;
      cout << "  4.Usuniecie elementu ze szczytu kopca"<<endl;
      cout << "  5.Generowanie tablicy wypelnionej kolejnymi cyframi liczby PI"<<endl;
      cout << "  0.Zakonczenie dzialania programu"<<endl;
      cout << "  Twoj wybor (0-5): ";

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
	  generowanie_liczb(tablica,roz);
	  break;

	case '2': /* stworzenie kopca */
	  /* kopiec zostaje stworzony od drugiego elementu w tablicy,
	     pierwszy element tablicy zawsze jest zerem. */
	  make_heap(tablica+1,tablica+roz);
	  break;

	case '3': /* wyswietlenie kopca */
	  wyswietl_kopiec(tablica,roz);
	  break;
	  
	case '4': /* usuniecie wartosci ze szczytu (wartosc najwieksza) */
	  if(roz > 0)
	    {	  
	      cout<<"Wartosc usunieta ze szczytu kopca: "<<tablica[1];
	      tablica[1]=tablica[roz];
	      roz--;
	    }
	  else
	    {
	      cout << "Nie ma nic do usuniecia. "<<endl;
	      cout << "Kopiec jest pusty !"<<endl;
	    }
	  break;

	case '5':
	  generowanie_pi(tablica,roz);
	  break;

	default: /* opcja nierozpoznana */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu 0-5"<<endl;
	  cout << "--------------------------------"<<endl;
	} /* end switch */
    } /* end while */
} /* end main */



