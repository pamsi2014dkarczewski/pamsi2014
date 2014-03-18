#include <iostream>
#include <limits>
#include "lista.hh"

/* Definicja typu dla jakiego wykonywany bedzie program.
   Po zmianie typu nalezy skompilowac program poleceniem make.
   Program testowany byl dla typow: int, float, double, char, string  */
#define Typ int

using namespace std;


int main()
{
  int opcja; /* zmienna wyboru opcji menu */

  Typ element; /* definicja pojedynczego elementu listy */
  lista<Typ> lista; /* definicja listy dwukierunkowej */

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
	      /* dodanie elementu na poczatek listy */
	      lista.dodaj_na_poczatek(element); 
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
	      lista.dodaj_na_koniec(element); 
	    }	  
	  break;

	case 3: /* wyswietlenie listy */
	  cout<<"Rozmiar listy: "<<lista.wielkosc_listy()<<endl<<endl;
	  lista.wyswietl_liste(); 
	  break;

	case 4: /* usuniecie elementu z przodu listy */
	  if(lista.wielkosc_listy() > 0) /* jezeli lista zawiera elementy */
	    {
	      lista.usun_z_poczatku();
	    }
	  else /* lista pusta */
	    {
	      cout << "Lista jest pusta ! Nie ma nic do usuniecia."<<endl;
	    }
	  break;

	case 5: /* usuniecie elementu z konca listy */
	  if(lista.wielkosc_listy() > 0) /* jezeli lista zawiera elementy */
	    {
	      lista.usun_z_konca(); 
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
