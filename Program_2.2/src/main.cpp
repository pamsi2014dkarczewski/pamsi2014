#include <iostream>
#include <limits>
#include "lista.hh"

#define Typ int  /* Definicja typu dla jakiego wykonywany bedzie program.
		    Po zmianie typu nalezy skompilowac program poleceniem make.
		    Program testowany byl na typach: int, float, double */

using namespace std;


int main()
{
  int opcja; /* zmienna wyboru opcji menu */

  Typ element; /* definicja pojedynczego elementu listy */
  stos<Typ> lista; /* definicja stosu */

  cout<<"Lista 2, Program 2.2 |zajecia PAMSI| lista dwukierunkowa."<<endl;
 
  do
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << "1.Dodawanie elementu na poczatek listy"<<endl;
      cout << "2.Dodawanie elementu na koniec listy"<<endl;
      cout << "3.Wyswietlenie zawartosci listy"<<endl;
      cout << "4.Usuniecie elementu z przodu listy"<<endl;
      cout << "5.Usuniecie elementu z konca listy"<<endl;
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

	case 1: /* dodawanie elementu na poczatek listy */
	  cout << "Podaj element jaki chcesz dodac na poczatek listy : ";
	  cin >> element;
	  if(cin.fail()) /* jezeli wprowadzono nieprawidlowy znak */
	    {
	      cout<<"Nieprawidlowy znak."<<endl;
	      cin.clear(); 
	      cin.ignore(numeric_limits<streamsize>::max(),'\n');
	    }
	  else
	    {
	      lista.add_front(element); /* dodanie elementu na poczatek listy */
	    }	  
	  break;

	case 2: /* dodawanie elementu na koniec listy */
	  cout << "Podaj element jaki chcesz dodac na koniec listy : ";
	  cin >> element;
	  if(cin.fail()) /* jezeli wprowadzono nieprawidlowy znak */
	    {
	      cout<<"Nieprawidlowy znak."<<endl;
	      cin.clear(); 
	      cin.ignore(numeric_limits<streamsize>::max(),'\n');
	    }
	  else /* dodanie elementu na koniec listy */
	    {
	      lista.add_back(element); 
	    }	  
	  break;

	case 3: /* wyswietlenie listy */
	  cout<<"Rozmiar listy: "<<lista.size()<<endl<<endl;
	  lista.wyswietl_liste(); 
	  break;

	case 4: /* usuniecie elementu z przodu listy */
	  if(lista.size() > 0) /* jezeli lista zawiera elementy */
	    {
	      lista.delete_front();
	    }
	  else /* lista pusta */
	    {
	      cout << "Lista jest pusta ! Nie ma nic do usuniecia."<<endl;
	    }
	  break;

	case 5: /* usuniecie elementu z konca listy */
	  if(lista.size() > 0) /* jezeli lista zawiera elementy */
	    {
	      lista.delete_back(); 
	    }
	  else /* lista pusta */
	    {
	      cout << "Lista jest pusta ! Nie ma nic do usuniecia."<<endl;
	    }	  
	  break;

	default: /* nierozpoznana opcja */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu 0-5"<<endl;
	  cout << "--------------------------------"<<endl;
	  break;
	} /* end switch (menu) */

    }while(opcja != 0);

}
