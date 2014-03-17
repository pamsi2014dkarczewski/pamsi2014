#include <iostream>
#include <limits>
#include "lista.hh"

#define Typ int  /* Definicja typu dla jakiego wykonywany bedzie program.
		    Po zmianie typu nalezy skompilowac program poleceniem make.
		    Program testowany byl na typach: int, float, double */

using namespace std;


int main()
{
  int opcja; /* zmienna wyboru opcji w menu */

  Typ element; /* definicja pojedynczego elementu listy */
  stos<Typ> lista; /* definicja stosu */

  cout<<"Lista 2, Program 2.1 |zajecia PAMSI| lista jednokierunkowa."<<endl;

  do
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << "1.Dodawanie elementu na poczatek listy"<<endl;
      cout << "2.Wyswietlenie zawartosci listy"<<endl;
      cout << "3.Wyswietlenie rozmiaru listy"<<endl;
      cout << "4.Usuniecie elementu z przodu listy"<<endl;
      cout << "0.Zakonczenie dzialania programu"<<endl;
      cout << "Twoj wybor: ";

      cin >> opcja;
      cout<<endl;

      switch (opcja)
	{
	case 0: /* wyjscie z programu */
	  cout<<"Koniec dzialania programu"<<endl;
	  cout<<"_________________________"<<endl;
	  break;

	case 1: /* dodawanie elementu na poczatku stosu */
	  cout << "Podaj element jaki chcesz dodac na stos :";
	  cin >> element;
	  if(cin.fail()) /* jezeli wprowadzono nieprawodlowy znak */
	    {
	      cout<<"Nieprawidlowy znak."<<endl;
	      cin.clear(); 
	      cin.ignore(numeric_limits<streamsize>::max(),'\n');
	    }
	  else /* dodanie elementu na poczatek stosu */
	    {
	      lista.add_front(element);
	    }	  
	  break;

	case 2: /* wyswietlanie aktualnej zawartosci listy */
	  lista.wyswietl_liste();
	  break;

	case 3: /* wyswietlenie aktualnego rozmiaru listy */
	  cout<<"Rozmiar listy :"<<lista.size()<<endl;
	  break;

	case 4: /* usuniecie elementu z przodu listy */
	  lista.delete_front(); 
	  break;

	default: /* nierozpoznana opcja */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu 0-4"<<endl;
	  cout << "--------------------------------"<<endl;
	  break;
	} /* end switch (menu) */

    }while(opcja != 0);

}
