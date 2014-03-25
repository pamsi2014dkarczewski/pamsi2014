#ifndef KOPIEC_HH
#define KOPIEC_HH

#include <limits>
#include <algorithm>

using namespace std;

/********************************* FUNKCJE *********************************/
/* generowanie liczb pseudolosowych */
template <typename TYP>
void generowanie_liczb(TYP *tablica, int roz)
{
  int min, max;
  cout << "Podaj parametry do generowania liczb."<<endl;	  
  cout << "Wartosc minimalna: ";
  cin >> min;
  cout << endl;
  
  cout << "Wartosc maksymalna: ";
  cin >> max;
  cout << endl;
  
  cout << "Wygenerowane liczby: "<<endl;
  for (int i = 0; i<roz; i++)
    {
      tablica[i]=(( min + rand() % (max-min + 1)));
      cout << tablica[i]<<" ";	    
    }
  cout<<endl;
}
/**************************************************************************/

/* wyswietlenie kopca */
template <typename TYP>
void wyswietl_kopiec(TYP *tablica, int roz)
{
  cout << "Kopiec w formie tablicy: "<<endl;
  for (int i = 0; i<roz; i++)
    {
      cout<<tablica[i]<<" ";
    }
  cout<<endl<<endl;
}
/***************************************************************************/


#endif
