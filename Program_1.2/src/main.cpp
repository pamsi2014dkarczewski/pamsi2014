#include <iostream>
#include <cstdlib>

#include "funkcje.hh"

#define STR(x) #x

using namespace std;

int main ()
{

  int opcja;  /* zmienna wyboru opcji w menu */
  int rozmiar_tab; /* rozmiar tablicy ktory podaje uzytkownik */

  srand( time( NULL ) ); /* generowanie liczb losowych */

  cout<<"Przed przystapieniem do pracy podaj rozmiar tablicy: ";
  cin>>rozmiar_tab;

  c_tablica<int> tablica(rozmiar_tab); /* Jezeli kompilacja przebiega dla typu double/float nalezy zmienic 'int' na typ kompilacji */
  c_tablica<int> kopia(rozmiar_tab);

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
	  tablica.wczytywanie();
	  break;
	case 2: 
	  tablica.wyswietlanie();
	  break;
	case 3: 
	  tablica.wczytywanie_z_pliku();
	  break;
	case 4: 
	  tablica.zapisywanie_do_pliku();
	  break;
	case 5: 
	  tablica.wczytywanie_z_pliku_binarnego();
	  break;
	case 6: 
	  tablica.zapisywanie_do_pliku_binarnego();
	  break;
	case 7: 
	  tablica.wypelnianie_liczbami_losowymi();
	  break;
	case 8: 
	  kopia=tablica;
	  kopia.wyswietlanie();
	  break;
	default:
	  cout << "Nie rozpoznano opcji '"<<opcja<<"' !!!"<<endl;
	  cout << "Wprowadz ponownie liczbe z zakresu 0-8 !"<<endl;
	}
    }while(opcja !=0);

} //end main
