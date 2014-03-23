#include <iostream>
#include <queue>

#include "kolejka.hh"
#include "typ.hh"

/* Program 3.3 z trzeciej listy zadan.

   Kolejka zostala zaimplementowana za pomoca STL. Mozliwe operacje do wykonania:
   - dodawanie elementow na koniec kolejki
   - pobranie elementu z poczatku kolejki (wraz z usunieciem)
   - wyswietlenie dlugosci kolejki

   Program dziala na roznych typach danych. W celu ulatwienia testowania
   programu plik 'makefile' zawiera definicje typow dla jakich program byl
   testowany. Przed uruchomieniem programu warto zapoznac sie z 'helpem' tzn.
   wpisanie 'make help' a nastepnie 'make help2'. 

   (skrot)
   make int --> kompilacja dla int
   make char --> kompilacja dla char
   itd.

   Program kompiluje sie bez bledow i bez ostrzezen.
   Testowany byl na typach: int, float, double, char, string.
*/

using namespace std;

int main ()
{

  char opcja;  /* zmienna wyboru opcji w menu */

  kolejka <TYP>kolejka_elementow; /* kolejka jest typu FIFO */

  cout << "---------------------------------------------"<<endl;
  cout << "| PROGRAM SKOMPILOWANO DLA TYPU: "<<NAZWA_TYPU<<endl;
  cout << "---------------------------------------------"<<endl;

  cout << "Lista 3, Program 3.3 |zajecia PAMSI| kolejka (STL)."<<endl;

  while(true)
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << "1.Dodanie elementu na koniec kolejki"<<endl;
      cout << "2.Pobranie elementu z poczatku kolejki (usuwanie)"<<endl;
      cout << "3.Wyswietlanie dlugosci kolejki"<<endl;
      cout << "0.Zakonczenie dzialania programu"<<endl;
      cout << "Twoj wybor (0-3): ";

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

	case '1': /* dodanie elementu na koniec kolejki */
	  kolejka_elementow.dodaj_na_koniec();
	  break;

	case '2': /* pobranie elementu z poczatku kolejki */
	  if(!kolejka_elementow.pobierz_z_poczatku()) 
	    {
	      cout << "Kolejka jest pusta"<<endl;
	    }
	  break;

	case '3': /* wyswietlanie dlugosci kolejki */
	  cout << "Ilosc elementow w kolejce: "<<kolejka_elementow.dlugosc()<<endl;
	  break;

	default: /* opcja nierozpoznana */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu 0-3"<<endl;
	  cout << "--------------------------------"<<endl;
	} /* end switch */
    } /* end while */
} /* end main */
