#ifndef LISTA_GRAF_HH
#define LISTA_GRAF_HH

#include <chrono> /* pomiar czasu */
#include <vector>
#include <algorithm> /* sortowanie */

#define ILOSC_POWTORZEN 105 /* ilosc powtorzen algorytmu */

/********************************* KLASA Lista_graf ***************************/
template <typename TYP>
class Lista_graf
{
public:

  /* klasa reprezentujaca krawedz */
  class Krawedz
  {
  public:
    int poczatek;
    int koniec;
    TYP waga;

    /* przeciazenie operatora porownania dla sortowania STL */
    bool operator < (const Krawedz& nastepna) const  
    {
      return (waga < nastepna.waga);
    }

    /* konstruktory */
    Krawedz() : poczatek(0), koniec(0), waga(0) {}
    Krawedz(int p, int k, TYP w) : poczatek(p), koniec(k), waga(w) {}

    /* destruktor */
    ~Krawedz(){}
  }; /* end class Krawedz */

  /**************************** konstruktor listy *****************************/
  Lista_graf();
  /****************************************************************************/

  /*************************** operacje na pliku/liscie ***********************/
  bool generuj_graf(double gestosc);  
  bool wczytaj_z_pliku(const std::string nazwa_odczytu);
  bool zapisz_do_pliku(const std::string nazwa_zapisu);
  bool zapisz_droge_do_pliku(const std::string nazwa_zapisu);
  /****************************************************************************/

  /********************************** dodatki *********************************/
  void wyswietl_liste();
  bool graf_spojny();
  void zmien_rozmiar(int rozmiar);

  void wyjscie_na_plik(std::ofstream &plik);
  void sciezka(int wsp, std::ofstream &plik);
  /****************************************************************************/

  /********************************* algorytmy ********************************/
  void algorytm_Dijkstry();
  void algorytm_Bellmana_Forda();
  bool Bellman_Ford();
  /****************************************************************************/

  /* destruktor */
  ~Lista_graf() {}

private:

  std::vector<Krawedz> lista;
  int *droga;
  int *poprzednik;
  int rozmiar, ilosc_krawedzi, zrodlo;

}; /* end class Lista_graf */
/******************************************************************************/


/************************************ KONSTRUKTOR *****************************/
template <typename TYP>
Lista_graf<TYP>::Lista_graf()
{
  rozmiar = 0;
  ilosc_krawedzi = 0;
  zrodlo = 0;

  droga = new int [rozmiar];
  poprzednik = new int [rozmiar];
}
/******************************************************************************/


/******************************* GENEROWANIE GRAFU ****************************/
template <typename TYP>
bool Lista_graf<TYP>::generuj_graf(double gestosc)
{
  TYP wartosc;
  int waga_min, waga_max;

  ilosc_krawedzi = 0;

  std::cout << "Podaj przedzial z jakiego beda generowane wagi sciezek.";
  std::cout << std::endl;
  std::cout << "Wartosc minimalna: "; 
  std::cin >> waga_min;

  std::cout << "Wartosc maksymalna: "; 
  std::cin >> waga_max;
  std::cout << std::endl;

  /* wypelnienie listy losowymi wartosciami */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i; j++)
	{
	  wartosc = (rand() % waga_max) + waga_min;
	  
	  if( wartosc  <= (gestosc*waga_max))
	    {
	      lista.push_back(Krawedz(i,j,wartosc));
	      lista.push_back(Krawedz(j,i,wartosc));
	      ilosc_krawedzi++;	    
	    }
	}
    }
  return true;
}
/******************************************************************************/


/******************************* ZMIANA ROZMIARU ******************************/
template <typename TYP>
void Lista_graf<TYP>::zmien_rozmiar(int roz)
{
  if (roz > 1)
    {
      delete [] droga;
      delete [] poprzednik;

      lista.clear();

      rozmiar = roz;

      droga = new int [rozmiar];
      poprzednik = new int [rozmiar];
    }
  else
    {
      std::cerr << "Rozmiar listy musi byc wiekszy od 1 !" << std::endl;
    }
}
/******************************************************************************/


/********************************** WCZYTYWANIE *******************************/
template <typename TYP>
bool Lista_graf<TYP>::wczytaj_z_pliku(const std::string nazwa_odczytu)
{
  std::ifstream plik; /* dane wczytane do pliku */
  int poczatek, koniec;
  
  TYP wartosc;
  
  plik.open (nazwa_odczytu.c_str(), std::ios::in);
  
  if(plik.is_open()) /* jezeli plik zostanie otworzony */
    {
      std::cout << "Wczytuje dane !"<<std::endl;
      
      /* wczytanie pierwszej linii, ktora informuje o ilosci krawedzi, ilosci
	 wierzcholkow oraz podany jest wierzcholek startowy (zrodlo) */
      plik >> ilosc_krawedzi >> rozmiar >> zrodlo;

      if(plik.bad())
	{
	  std::cerr << "Blad w pierwszej linii pliku !" << std::endl;
	  return false;
	}

      while (!plik.eof() && !plik.bad())
	{
	  plik >> poczatek;

	  if(!plik) break; /* zapobiega duplikowaniu ostatniego wiersza */

	  if(poczatek > rozmiar)
	    {
	      std::cerr << "Poza rozmiarami macierzy !" << std::endl;
	      std::cerr << "Wczytanie nie powiodlo sie !" << std::endl;
	      return false;
	    }
	  plik >> koniec; 
	  if(koniec > rozmiar) 
	    {
	      std::cerr << "Poza rozmiarami macierzy !" << std::endl;
	      std::cerr << "Wczytanie nie powiodlo sie !" << std::endl;
	      return false;
	    }
	  
	  plik >> wartosc;
	  if(wartosc >= -10)
	    {
	      lista.push_back(Krawedz(poczatek,koniec,wartosc));
	      lista.push_back(Krawedz(koniec,poczatek,wartosc));
	    }
	  else
	    {
	      std::cerr << "Nieprawidlowa waga krawedzi !" << std::endl;
	      std::cerr << "Zostanie ona pominieta !" << std::endl;
	    }
	}	
    }

  plik.close();
  return true;
}
/******************************************************************************/


/******************************* ZAPISYWANIE **********************************/
template <typename TYP>
bool Lista_graf<TYP>::zapisz_do_pliku(const std::string nazwa_zapisu)
{
  std::ofstream plik; 

  plik.open(nazwa_zapisu.c_str(), std::ios::out | std::ios::trunc);

  if(plik.good())
    {
      for(unsigned int i = 0; i < lista.size(); i++)
	{
	  plik << lista[i].poczatek << "\t";
	  plik << lista[i].koniec << "\t";
	  plik << lista[i].waga << "\r" << std::endl;
	}
    }
  else
    {
      std::cerr << "ZAPISANIE DO PLIKU '" << nazwa_zapisu;
      std::cerr << "' NIE POWIODLO SIE !!!" << std::endl;

      plik.close();
      return false;
    }

  std::cout << "Zapisywanie do pliku : '" << nazwa_zapisu;
  std::cout << "' zakonczone powodzeniem." << std::endl; 
  
  plik.close();
  return true;
}
/******************************************************************************/


/******************************* ZAPISYWANIE DROGI ****************************/
template <typename TYP>
bool Lista_graf<TYP>::zapisz_droge_do_pliku(const std::string nazwa_zapisu)
{
  std::ofstream plik; 

  plik.open(nazwa_zapisu.c_str(), std::ios::out | std::ios::trunc);

  if(plik.good())
    {
      wyjscie_na_plik(plik);
    }
  else
    {
      std::cerr << "ZAPISANIE DO PLIKU '" << nazwa_zapisu;
      std::cerr << "' NIE POWIODLO SIE !!!" << std::endl;

      plik.close();
      return false;
    }

  std::cout << "Zapisywanie do pliku : '" << nazwa_zapisu;
  std::cout << "' zakonczone powodzeniem." << std::endl; 
  
  plik.close();
  return true;
}
/******************************************************************************/


/**************************** WYSWIETLENIE LISTY ******************************/
template <typename TYP>
void Lista_graf<TYP>::wyswietl_liste()
{
  if(lista.size() > 0)
    {
      std::cout << "Poczatek   ->   Koniec   |   Waga" <<std::endl;
      for (unsigned int i = 0; i < lista.size(); i++)
	{
	  std::cout << std::setw(8) << lista[i].poczatek <<"   ";
	  std::cout << std::setw(2) << "->" <<"   ";
	  std::cout << std::setw(6) << lista[i].koniec << "   |   ";
	  std::cout << std::setw(4) << lista[i].waga << std::endl;
	}
    }
  else
    {
      std::cerr << "Lista jest pusta." << std::endl;
    }
  std::cout << std::setw(0) << std::endl;
}
/******************************************************************************/


/*********************************** GRAF SPOJNY ******************************/
/* sprawdzenie czy graf jest spojny */
/* spojnosc zwraca true, niespojnosc zwraca false */
template <typename TYP>
bool Lista_graf<TYP>::graf_spojny()
{
  int n = rozmiar;
  int m = ilosc_krawedzi;

  return ( ((n-1) <= m) && (((n*(n-1))/2) >= m) ) ? true : false;
}
/******************************************************************************/


/******************************** WYJSCIE NA PLIK *****************************/
template <typename TYP>
void Lista_graf<TYP>::wyjscie_na_plik(std::ofstream &plik)
{ 
  for(int i = 0; i < rozmiar; i++)
    {
      plik<<i<<" "<<droga[i]<<" ";
      sciezka(i,plik);
      plik<<std::endl;
    } 
}
/******************************************************************************/


/*********************************** DROGA ************************************/
template <typename TYP>
void Lista_graf<TYP>::sciezka(int w, std::ofstream &plik)
{
  if(w == zrodlo)
    {
      plik<<w<<" ";
    }  
  else if(poprzednik[w] == -1) std::cerr<<"Brak polaczenia: "<<zrodlo<<"->"<<w<<std::endl;
  else 
    {
      sciezka(poprzednik[w],plik);
      plik<<w<<" ";
    }
}
/******************************************************************************/


/***************************** ALGORYTM DIJKSTRY ******************************/
template <typename TYP>
void Lista_graf<TYP>::algorytm_Dijkstry()
{
  /* wartosc maksymalna symbolizuje nieskonczonosc */
  TYP max = std::numeric_limits<TYP>::max();

  bool *odwiedzone = new bool [rozmiar];

  double suma = 0; /* czas wykonania wszystkich algorytmow */

  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      int licznik = 0;
      int minimum;
      int min_index = 0;
      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();

      /* inicjalizacja */
      for(int i = 0; i < rozmiar; i++)
	{
	  droga[i] = max;
	  poprzednik[i] = -1;
	  odwiedzone[i] = false;
	}

      droga[zrodlo] = 0;
      
      while(licznik < rozmiar)
	{
	  /* znajdowanie najmniejszej nieodwiedzonej wagi */
	  minimum = max;
	  for(int i = 0; i < rozmiar; i++)
	    {
	      if((!odwiedzone[i]) && (droga[i] <= minimum))
		{
		  minimum = droga[i];
		  min_index = i;
		}
	    }

	  /* odwiedzona zostaje waga z najmniejsza wartoscia */
	  odwiedzone[min_index] = true;
	  
	  for(unsigned int j = 0; j < lista.size(); j++)
	    {
	      /* znajdownie sasiadow wierzcholka ktory zostal odwiedzony */
	      if(odwiedzone[min_index]) 
		{
		  int p = lista[j].poczatek;
		  int k = lista[j].koniec;

		  /* kazdy wierzcholek jest zapisany dwa razy tzn.
		     0 1 --> pierwszy wierzcholek
		     1 0 --> drugi wierzcholek
		     ale ciagle to ta sama krawedz i dlatego sprawdzam dwie 
		     wspolrzedne */

		  /* przypadek np. 0 1 */
		  if(p == min_index && lista[j].waga >=1 && lista[j].waga <=500)
		    {      		    
		      if(droga[k] > minimum + lista[j].waga)
			{
			  droga[k] = minimum + lista[j].waga;
			  poprzednik[k] = min_index;
			}
		    }

		  /* przypadek np 1 0 */
		  if(k == min_index && lista[j].waga >=1 && lista[j].waga <=500)
		    {
		      if(droga[p] > minimum + lista[j].waga)
			{
			  droga[p] = minimum + lista[j].waga;
			  poprzednik[p] = min_index;
			}
		    }
		} /* end if(odwiedzone[min_index]) */
	    } /* end for */
	  licznik++;
	} /* end while */
  
      auto t2 = std::chrono::high_resolution_clock::now();
      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
      if(i > 5) suma += roznica.count();
      std::cout<<"Czas wykonania algorytmu Dijkstry dla listy: "<<roznica.count()<<" milisekund."<<std::endl;	

    }

  std::cout << std::endl;
  std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
  std::cout << "Sredni czas wykonania algorytmu Dijkstry : ";
  std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;

}
/******************************************************************************/


/**************************** ALGORYTM BELLMANA-FORDA *************************/
template <typename TYP>
bool Lista_graf<TYP>::Bellman_Ford()
{
  TYP max = std::numeric_limits<TYP>::max() - 10000; 

  /* inicjalizacja */
  for(int i = 0; i < rozmiar; i++)
    {
      droga[i] = max;
      poprzednik[i] = -1;
    }
  droga[zrodlo] = 0;

  bool wyjscie;
  for(int i = 1; i < rozmiar; i++)
    {
      wyjscie = true;

      /* kazda krawedz jest dwa razy dodawana, raz normalnie, a drugi raz 
	 jest zapisana z odwrotnymi wspolrzednymi */
      for(unsigned int j = 0; j < lista.size(); j++)
	{
	  int p = lista[j].poczatek;
	  int k = lista[j].koniec;
	  int w = lista[j].waga;
	  if(w >= -10 && w <= 1000)
	    {
	      if(droga[k] > droga[p] + w)
		{
		  wyjscie = false;
		  droga[k] = droga[p] + w;
		  poprzednik[k] = p;
		}
	    }
	}
      if(wyjscie) return true;
    }

  /* sprawdzenie ujemnego cyklu */
  for(unsigned int i = 0; i < lista.size(); i++)
    {
      int p = lista[i].poczatek;
      int k = lista[i].koniec;
      int w = lista[i].waga;

      if(droga[k] > droga[p] + w)
	{
	  return false;
	}
    }
  
  return true;
}
/******************************************************************************/


/************************ ALGORYTM BELLMANA-FORDA *****************************/
template <typename TYP>
void Lista_graf<TYP>::algorytm_Bellmana_Forda()
{
  double suma = 0; /* czas wykonania wszystkich algorytmow */

  bool flaga = true;

  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      auto t1 = std::chrono::high_resolution_clock::now();
   
      if(!Bellman_Ford())
	{
	  std::cerr<<"Wykryto ujemny cykl, prosze wygenerowac graf ponownie !";
	  std::cerr<<std::endl;
	  flaga = false;
	}
      else
	{
	  auto t2 = std::chrono::high_resolution_clock::now();

	  auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
	  if(i > 5) suma += roznica.count(); /* pierwsze 5 czasow pomijam */

	  std::cout << "Czas wykonania algorytmu Bellmana-Forda dla listy: ";
	  std::cout << roznica.count() << " milisekund." << std::endl;
	}
    } /* end for */

  if(flaga) /* gdy algorytm wykryl ujemny cykl to podsumowanie jest zbedne */
    {
      std::cout << std::endl;
      std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
      std::cout << "Sredni czas wykonania algorytmu Bellmana-Forda : ";
      std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;
    }
}
/******************************************************************************/

#endif
