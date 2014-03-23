#ifndef STOS_HH
#define STOS_HH

#include <stack>
#include <limits>


/********************************* KLASA STOS *******************************/
template <typename TYP>
class stos
{
private:
  /* stworzenie stosu */
  std::stack <TYP> stos_glowny;

public:

  void dodaj_na_stos(); /* dodanie elementu na gore stosu */
  void wyswietlenie_stosu(); /* wyswietlenie zawartosci stosu */
  void wyszukaj_element(); /* wyszukiwanie elementu w stosie */
  bool usun_element(); /* usuniecie elementu z gory stosu */

}; /* end class stos */
/***************************************************************************/



/************************* DODANIE NA GORE STOSU ***************************/
template <typename TYP>
inline void stos<TYP>::dodaj_na_stos()
{
  TYP element; /* element ktory dodamy na stos */
  std::cout << "Podaj jaki element chcesz dodac na stos: ";
  std::cin >> element;
  if(std::cin.good()) /* jezeli uda sie wczytac element */
    {
      stos_glowny.push(element); /* wrzucimy element na gore stosu */
    }
  else /* wczytanie nieprawidlowego znaku */
    {
      std::cout << "Nieprawidlowy znak."<<std::endl;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}
/**************************************************************************/



/********************* WYSWIETLENIE ZAWARTOSCI STOSU **********************/
template <typename TYP>
void stos<TYP>::wyswietlenie_stosu()
{
  TYP element;
  std::stack<TYP> temp; /* stos pomocniczy */

  /* element na samym dole stosu jest elementem ktory 
     zostal dodany na stos jako pierwszy */
  std::cout << "Najnizej polozony element jest elementem najstarszym. "<<std::endl;
  std::cout << "Ilosc elementow na stosie: "<<stos_glowny.size()<<std::endl;
  if(!stos_glowny.empty()) /* stos nie jest pusty */
    {
      /* wyswietlenie stosu i skopiowanie go do stosu tymczasowego */
      while(!stos_glowny.empty())
	{
	  element = stos_glowny.top();
	  stos_glowny.pop(); /* zabranie elementu ze stosu */
	  temp.push(element); /* dodanie zdjetego elementu na stos tymczasowy */
	  std::cout << "Element na stosie: "<<element<<std::endl;	
	}

      /* przypisanie stosu tymczasowego do stosu glownego
	 dzieki temu stos glowny nie zmieni kolejnosci elementow */
      while(!temp.empty())
	{
	  element = temp.top();
	  temp.pop();
	  stos_glowny.push(element);
	}
    }
  else /* stos pusty */
    {
      std::cout << "Nie ma nic do wyswietlenia."<<std::endl;
    }
}
/***************************************************************************/



/**************************** WYSZUKIWANIE ELEMENTU ************************/
template <typename TYP>
void stos<TYP>::wyszukaj_element()
{
  int rozmiar = stos_glowny.size(); /* rozmiar potrzebny jest do okreslenia 
				       na ktorym miejscu znajduje sie element */
  int miejsce = 0; 
  int ile_razy = 0; /* licznik wystapien znalezionego elementu w stosie */
  TYP znajdz, element; /* 'znajdz' <-- jaki element w stosie bedzie szukany
			  'element' <-- pobrany element ze stosu */

  std::stack<TYP> temp; /* stos pomocniczy */

  if(!stos_glowny.empty()) /* stos nie jest pusty */
    {
      std::cout << "Podaj jaki element nalezy wyszukac: ";
      std::cin >> znajdz;

      if(std::cin.good()) 
	{
	  /* wyszukiwanie elementu w stosie i okreslenie jego pozycji */
	  while(rozmiar > 0)
	    {
	      miejsce = 0; 
	      element = stos_glowny.top(); /* pobranie elementu z gory */
	      stos_glowny.pop();
	      temp.push(element);

	      if(element == znajdz) /* gdy znaleziono szukany element */
		{
		  miejsce = rozmiar - miejsce; /* wyznaczenie jego pozycji */
		  std::cout << "Znaleziono element '"<<element<<"' na : "<<miejsce;
		  std::cout << " miejscu od spodu stosu."<<std::endl;
		  ile_razy++; /* licznik wystapien elementu w stosie */
		}
	      rozmiar--;
	    }

	  std::cout << "Twoj element wystepuje w stosie: ";
	  std::cout << ile_razy<<" raz(y)."<<std::endl;
	  
	  /* przypisanie stosu tymczasowego do stosu glownego
	     dzieki temu stos glowny nie zmieni kolejnosci elementow */
	  while(!temp.empty())
	    {
	      element = temp.top();
	      temp.pop();
	      stos_glowny.push(element);
	    }
	}
      else /* gdy wprowadzono nieprawidlowy znak */
	{
	  std::cout << "Nieprawidlowy znak."<<std::endl;
	  std::cin.clear(); 
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}
    }
  else /* stos pusty */
    {
      std::cout << "Nic nie znajde, bo stos jest pusty."<<std::endl;
    }
}
/***************************************************************************/



/*************************** USUNIECIE ELEMENTU ****************************/
template <typename TYP>
inline bool stos<TYP>::usun_element()
{
  if(stos_glowny.empty()) return false; /* jezeli stos jest pusty */
  
  std::cout << "Usunieto element: '"<<stos_glowny.top()<<"'"<<std::endl;
  stos_glowny.pop(); /* usuwamy element z gory stosu */
  
  return true;
}
/***************************************************************************/

#endif
