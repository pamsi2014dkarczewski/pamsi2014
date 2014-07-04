#include <iostream>
#include <cstdlib> /* rand() */
#include <iomanip> /* setw() */
#include <list> /* lista */
#include <fstream>
#include <limits>

#include "macierz.hh"
#include "plik.hh"
#include "typ.hh"

using namespace std;

int main ()
{
  /* rand() */
  srand (time(NULL));

  /* pliki z danymi musza sie znajdowac w katalogu "dane" w folderze z programem */

  /* foldery: dane, inc, obj, src */

  char opcja;
  string nazwa_odczytu, nazwa_zapisu, sciezka;
  Macierz_graf<TYP> macierz;
  
  cout << "---------------------------------------------" << endl;
  cout << "| PROGRAM SKOMPILOWANO DLA TYPU: " << NAZWA_TYPU << endl;
  cout << "---------------------------------------------" << endl;

  cout << "Lista 7, Program 7 |zajecia PAMSI| graf." << endl;
  cout << "Algorytm Edmondsa-Karpa, maskymalny przeplyw";
   
  while(true)
    {
      cout << endl;
      cout << "MENU: " <<endl;
      cout << " Operacje na macierzy:"<<endl;
      cout << "  1.Generowanie grafu."<<endl;
      cout << "  2.Wczytanie grafu z pliku."<<endl;
      cout << "  3.Zapisanie grafu do pliku."<<endl;
      cout << "  4.Wyswietlenie macierzy."<<endl;
      cout << "  5.Algorytm Edmondsa-Karpa dla macierzy."<<endl;
      cout << " Twoj wybor (0-5): ";

      cin >> opcja;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
            
      switch(opcja)
	{
	case '0': 
	  {
	    cout<<"Koniec dzialania programu"<<endl;
	    cout<<"_________________________"<<endl;
	  }	  
	  return false;

	case '1': /* generowanie grafu */
	  {
	    int ilosc_wierzcholkow;
	    double gestosc;

	    cout << "Podaj ilosc wierzcholkow: ";
	    cin >> ilosc_wierzcholkow;

	    cout << "Podaj gestosc: ";
	    cin >> gestosc;

	    macierz.zmien_rozmiar(ilosc_wierzcholkow);
	    macierz.generuj_graf(gestosc);
	  }
	  break;

	case '2': /* wczytanie grafu z pliku */
	  {
	    cout << "Do nazwy pliku zostanie dopisane rozszerzenie '.txt'" << endl;
	    cout << "Podaj nazwe pliku do wczytania (bez rozszerzenia): ";
	    cin >> nazwa_odczytu;
	    nazwa_odczytu += ".txt"; /* dodanie rozszerzenie do nazwy */
	    sciezka = "dane/"; /* gdzie zapisane sa dane */
	    nazwa_odczytu = sciezka + nazwa_odczytu;

	    /* zmiana rozmiaru macierzy, 
	       funkcja znajdz_rozmiar_w_pliku (...) zwraca wartosc, okreslajaca 
	       minimalny niezbedny rozmiar macierzy, ktora nalezy stworzyc aby 
	       bezproblemowo wczytac dane z pliku 

	       zwrocenie wartosci 0 oznacza blad podczas otwierania pliku */
	    int rozmiar = znajdz_rozmiar_w_pliku(nazwa_odczytu);
	    
	    if(rozmiar > 0)
	      {	    
		macierz.zmien_rozmiar(rozmiar);
	    
		/* graf zostaje wypelniony danymi wczytanymi z pliku */
		macierz.wczytaj_z_pliku(nazwa_odczytu);
		
	      }
	  }
	  break;

	case '3': /* zapisanie grafu do pliku */
	  {
	    cout << "Do nazwy pliku zostanie dopisane rozszerzenie '.txt'" << endl;
	    cout << "Podaj nazwe pliku do ktorego dane beda zapisane (bez rozszerzenia): ";
	    cin >> nazwa_zapisu;
	    nazwa_zapisu += ".txt";

	    macierz.zapisz_do_pliku(nazwa_zapisu);
	  }
	  break;

	case '4': /* wyswietlenie macierzy */
	  {
	    macierz.wyswietl_macierz();
	  }
	  break;
	  
	case '5': /* Algorytm Edmondsa-Karpa */
	  {
	    macierz.algorytm_Edmondsa_Karpa();
	    cout << "***************************************************"<<endl;
	  }
	  break;
	  
	default: /* opcja nierozpoznana */
	  cout << "--------------------------------"<<endl;
	  cout << "Nie rozpoznano opcji :'"<<opcja<<"' "<<endl;
	  cout << "Podaj liczbe z zakresu (0-5)"<<endl;
	  cout << "--------------------------------"<<endl;
	} /* end switch */
    } /* end while */
} /* end main */
