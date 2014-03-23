#include <iostream>
#include <stack>
#include "typ.hh"

#include "stos.hh"

/* Program 3.1 z trzeciej listy zadan.

   Stos zostal zaimplementowany za pomoca STL. Mozliwe operacje do wykonania:
   - dodawanie elementow na stos
   - wyswietlenie zawartosci stosu
   - wyszukiwanie elementu na stosie
   - usuwanie elementow ze stosu

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

  stos <TYP>stos_elementow; /* stos */

  cout << "---------------------------------------------"<<endl;
  cout << "| PROGRAM SKOMPILOWANO DLA TYPU: "<<NAZWA_TYPU<<endl;
  cout << "---------------------------------------------"<<endl;

  cout<<"Lista 3, Program 3.1 |zajecia PAMSI| stos (STL)."<<endl;

  while(true)
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << "1.Dodanie elementu na stos"<<endl;
      cout << "2.Wyswietlenie zawartosci stosu"<<endl;
      cout << "3.Wyszukiwanie elementu w stosie"<<endl;
      cout << "4.Usuwanie elementow ze stosu"<<endl;
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

	case '1': /* dodanie elementu na stos */
	  stos_elementow.dodaj_na_stos();
	  break;

	case '2': /* wyswietlenie stosu */
	  stos_elementow.wyswietlenie_stosu();
	  break;

	case '3': /* wyszukiwanie elementu w stosie */
	  stos_elementow.wyszukaj_element();
	  break;
	  
	case '4': /* usuwanie elementu ze stosu */
	  if(!stos_elementow.usun_element())
	    {
	      cout << "Stos jest pusty, nie ma nic do usuniecia."<<endl;
	    }
	  break;
	      
	default: /* opcja nierozpoznana */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu 0-4"<<endl;
	  cout << "--------------------------------"<<endl;
	} /* end switch */
    } /* end while */
} /* end main */
