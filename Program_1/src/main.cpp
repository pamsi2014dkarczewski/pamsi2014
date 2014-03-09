#include <iostream>
#include <cstdlib>

#include "funkcje.hh"

using namespace std;

int main ()
{

  int opcja;  /* zmienna wyboru opcji w menu */
  int tablica[ROZMIAR_TAB]={0}; /* tablica statyczna o zdefiniowanym rozmiarze, rozmiar mozna zmienic w pliku funkcje.hh */

  srand( time( NULL ) ); /* generowanie liczb losowych */

  do
    {
      cout << endl;
      cout << "Program do zajec nr 2" <<endl;
      cout << "1.Wczytanie tablicy z konsoli"<<endl;
      cout << "2.Wyswietlenie tablicy"<<endl;
      cout << "3.Wczytywanie z pliku tekstowego"<<endl;
      cout << "4.Zapisywanie do pliku tekstowego"<<endl;
      cout << "5.Wczytywanie z pliku binarnego"<<endl;
      cout << "6.Zapisywanie do pliku binarnego"<<endl;
      cout << "7.Wypelnianie tablicy liczbami pseudolosowymi"<<endl;
      cout << "8.Tworzenie dynamicznej kopii + wyswietlenie kopii"<<endl;
      cout << "0.KONIEC"<<endl;
      cout << "Podaj opcje: ";

      cin >> opcja;
      cout << endl;

      switch(opcja)
	{
	case 0: 
	  cout<<"Koniec dzialania programu"<<endl;
	  cout<<"_________________________"<<endl;
	  break;
	case 1:
	  wczytywanie(tablica);
	  break;
	case 2: 
	  wyswietlanie(tablica);
	  break;
	case 3: 
	  wczytywanie_z_pliku(tablica);
	  break;
	case 4: 
	  zapisywanie_do_pliku(tablica);
	  break;
	case 5: 
	  wczytywanie_z_pliku_binarnego(tablica);
	  break;
	case 6: 
	  zapisywanie_do_pliku_binarnego(tablica);
	  break;
	case 7: 
	  wypelnianie_liczbami_losowymi(tablica);
	  break;
	case 8: 
	  wyswietlenie_kopii(tablica);
	  break;
	default:
	  cout << "Nie rozpoznano opcji '"<<opcja<<"' !!!"<<endl;
	  cout << "Wprowadz ponownie liczbe z zakresu 0-8 !"<<endl;
	}
    }while(opcja !=0);

} //end main
