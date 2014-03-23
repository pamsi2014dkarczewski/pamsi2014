#ifndef KOLEJKA_HH
#define KOLEJKA_HH

#include <queue>
#include <limits>


/********************************* KLASA KOLEJKA ****************************/
template <typename TYP>
class kolejka
{
private:
  /* stworzenie kolejki */
  std::queue <TYP> kolejka_glowna;

public:

  void dodaj_na_koniec(); /* dodawanie elementu na koniec kolejki */
  bool pobierz_z_poczatku(); /* pobranie elementu z poczatku kolejki */
  int dlugosc(); /* dlugosc kolejki */

}; /* end class kolejka */
/***************************************************************************/



/*********************** DODAWANIE NA KONIEC KOLEJKI ***********************/
template <typename TYP>
inline void kolejka<TYP>::dodaj_na_koniec()
{
  TYP element; /* element ktory dodamy na koniec kolejki */
  std::cout << "Podaj jaki element chcesz dodac na koniec kolejki: ";
  std::cin >> element;
  if(std::cin.good()) /* jezeli uda sie wczytac element */
    {
      kolejka_glowna.push(element); /* wrzucimy element na koniec */
    }
  else /* wczytanie nieprawidlowego znaku */
    {
      std::cout << "Nieprawidlowy znak."<<std::endl;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}
/**************************************************************************/



/************************** POBRANIE Z POCZATKU ***************************/
template <typename TYP>
bool kolejka<TYP>::pobierz_z_poczatku()
{
  /* jezeli kolejka jest pusta zwracam false */
  if(kolejka_glowna.empty()) return false; 
    
  /* element z poczatku kolejki zostaje pobrany, wysywietlony i usuniety */
  std::cout << "Pierwszy element kolejki to: "<< kolejka_glowna.front()<<std::endl;
  kolejka_glowna.pop();
  std::cout << "Element usunieto."<<std::endl;

  return true;
}
/***************************************************************************/



/**************************** DLUGOSC KOLEJKI ******************************/
template <typename Typ>
inline int kolejka<Typ>::dlugosc()
{
  /* zwrocona zostaje dlugosc kolejki */
  return kolejka_glowna.size();
}
/***************************************************************************/


#endif
