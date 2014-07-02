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
  Lista_graf() : rozmiar(0) {}
  /****************************************************************************/

  /*************************** operacje na pliku/liscie ***********************/
  bool generuj_graf(double gestosc);  
  bool wczytaj_z_pliku(const std::string nazwa_odczytu);
  bool zapisz_do_pliku(const std::string nazwa_zapisu);
  /****************************************************************************/

  /********************************** dodatki *********************************/
  void wyswietl_liste();
  bool graf_spojny();
  void zmien_rozmiar(int rozmiar);
  void unia(int poczatek, int koniec, TYP *MST);
  TYP znajdz(int wartosc, TYP *MST);
  /****************************************************************************/

  /********************************* algorytmy ********************************/
  TYP algorytm_Kruskala();
  TYP algorytm_Prima();
  /****************************************************************************/

  /* destruktor */
  ~Lista_graf() {}

private:

  std::vector<Krawedz> lista;
  int rozmiar;

}; /* end class Lista_graf */
/******************************************************************************/


/******************************* GENEROWANIE GRAFU ****************************/
template <typename TYP>
bool Lista_graf<TYP>::generuj_graf(double gestosc)
{
  TYP wartosc;
  /* wypelnienie listy losowymi wartosciami */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i; j++)
	{
	  wartosc = rand() % 100000;
	  
	  if( wartosc  < (gestosc*100000))
	    {
	      lista.push_back(Krawedz(i,j,wartosc));
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
  if (roz > 0)
    {
      rozmiar = roz;
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
  int poczatek,koniec;
  TYP wartosc;
  
  plik.open (nazwa_odczytu.c_str(), std::ios::in);

  if(plik.is_open()) /* jezeli plik zostanie otworzony */
    {
      std::cout << "Wczytuje dane !"<<std::endl;
 	
      while (!plik.eof() && !plik.bad())
	{
	  plik >> poczatek;

	  if (!plik) break; /* zapobiega duplikowaniu ostatniego wiersza */

	  if(poczatek > rozmiar) std::cerr << "Poza rozmiarami macierzy !" << std::endl;
	  
	  plik >> koniec; 
	  if(koniec > rozmiar) std::cerr << "Poza rozmiarami macierzy !" << std::endl;

	  plik >> wartosc;
	  if(wartosc >= 0)
	    {
	      lista.push_back(Krawedz(poczatek,koniec,wartosc));
	    }
	  else
	    {
	      std::cerr << "Waga krawedzi jest ujemna !" << std::endl;
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
      std::cerr << "ZAPISANIE DO PLIKU '" << nazwa_zapisu << "' NIE POWIODLO SIE !!!" << std::endl;

      plik.close();
      return false;
    }

  std::cout << "Zapisywanie do pliku : '" << nazwa_zapisu << "' zakonczone powodzeniem." << std::endl; 
  
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
  int m = lista.size();

  return ( ((n-1) <= m) && (((n*(n-1))/2) >= m) ) ? true : false;
}
/******************************************************************************/


/*********************************** UNIA/ZLACZENIE ***************************/
template <typename TYP>
void Lista_graf<TYP>::unia(int poczatek, int koniec, TYP *MST)
{
  if(MST[poczatek] == MST[koniec]) return;

  int wartosc1 = znajdz(poczatek,MST);
  int wartosc2 = znajdz(koniec,MST);  

  if (wartosc1 < wartosc2)
    {
      for (int i = 0; i < rozmiar; i++)
	{
	  if (MST[i] == wartosc1 || MST[i] == wartosc2)
	    {
	      MST[i] = MST[wartosc1];
	    }
	}
    }
  else
    {
      for (int i = 0; i < rozmiar; i++)
	{
	  if (MST[i] == wartosc2 || MST[i] == wartosc1)
	    {
	      MST[i] = MST[wartosc2];
	    }
	}
    }
}
/******************************************************************************/


/**************************** ZNAJDOWANIE WARTOSCI ****************************/
template <typename TYP>
TYP Lista_graf<TYP>::znajdz(int wartosc, TYP *MST)
{
  int nastepny = MST[wartosc];

  while (MST[nastepny] != nastepny)
    {
      nastepny = MST[nastepny];
    }

  return nastepny;
}
/******************************************************************************/


/***************************** ALGORYTM KRUSKALA ******************************/
template <typename TYP>
TYP Lista_graf<TYP>::algorytm_Kruskala()
{
  TYP wartosc_MST; /* zwaracana wartosc minimalnego drzewa rozpinajacego */

  int element_w_liscie; /* aktualnie analizowany element w liscie */
  int ilosc_krawedzi;

  double suma = 0; /* czas wykonania wszystkich algorytmow */
  
  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      TYP *MST = new TYP [rozmiar];

      wartosc_MST = 0;
      element_w_liscie = 0;
      ilosc_krawedzi = 0;

      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();

      /* wstepne wypelnienie minimalnego drzewa rozpinajacego */
      for(int i = 0; i < rozmiar; i++)
	{
	  MST[i] = i;
	}
  
      /* sortowanie listy wzgledem wag */
      std::sort(lista.begin(), lista.end());
  
      while (ilosc_krawedzi < rozmiar -1)
	{
	  /* hmm strasznie nieczytelnie mi to wyszlo :( */
	  if(znajdz(lista[element_w_liscie].poczatek,MST) != znajdz(lista[element_w_liscie].koniec,MST))
	    {
	      unia(lista[element_w_liscie].poczatek, lista[element_w_liscie].koniec,MST);
	      wartosc_MST += lista[element_w_liscie].waga;
	      ilosc_krawedzi++;	
	    } /* end if(znajdz...) */

	  element_w_liscie++; /* czas na nastepny element z listy :) */
	}
  
      auto t2 = std::chrono::high_resolution_clock::now();
      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
      if(i > 5) suma += roznica.count();
      std::cout<<"Czas wykonania algorytmu Kruskala dla listy: "<<roznica.count()<<" milisekund."<<std::endl;	

      delete [] MST;  

    }

  std::cout << std::endl;
  std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
  std::cout << "Sredni czas wykonania algorytmu Kruskala : ";
  std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;

  return wartosc_MST;
}
/******************************************************************************/


/**************************** ALGORYTM PRIMA **********************************/
template <typename TYP>
TYP Lista_graf<TYP>::algorytm_Prima()
{
  int il_wierzcholkow; /* ilosc wierzcholkow */
  TYP wartosc_MST;  /* zwracana wartosc minimalnego drzewa rozpinajacego */

  int p,k; /* poczatek i koniec wierzcholka */
  TYP w; /* waga */

  double suma = 0; /* czas wykonania wszystkich algorytmow */

  std::vector<Krawedz> kolejka(lista.size());

  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      bool *odwiedzony = new bool [rozmiar]; /* wierzcholki odwiedzone */

      il_wierzcholkow = 0;
      wartosc_MST = 0; 

      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();


      /* na poczatku zaden wierzcholek nie jest odwiedzony */  
      for(int i = 0; i < rozmiar; i++) 
	{
	  odwiedzony[i] = false;
	}

      odwiedzony[lista[0].poczatek] = true; /* pierwszy zostal odwiedzony */
  
      while(il_wierzcholkow < rozmiar -1)
	{
	  for(int i = 0; i < rozmiar; i++)
	    {
	      if(odwiedzony[i] == true)
		{
		  for (unsigned int j = 0; j < lista.size(); j++)
		    {
		      if(((lista[j].poczatek == i) || (lista[j].koniec == i)) && (odwiedzony[lista[j].koniec] == false || odwiedzony[lista[j].poczatek] == false))
			{
			  p = lista[j].poczatek;
			  k = lista[j].koniec;
			  w = lista[j].waga;
			  kolejka.push_back(Krawedz(p,k,w));
			}
		    }
		}
	    }
	  std::sort(kolejka.begin(),kolejka.end());
      
	  p = kolejka[0].poczatek;      
	  k = kolejka[0].koniec;
	  wartosc_MST += kolejka[0].waga;

	  /* usuniecie kolejki, aby elementy nie duplikowac elementow */
	  kolejka.clear(); 

	  odwiedzony[k] = true;
	  odwiedzony[p] = true;      
	  il_wierzcholkow++;
	}
  
      auto t2 = std::chrono::high_resolution_clock::now();

      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
      if(i > 5) suma += roznica.count(); /* pierwsze 5 czasow pomijam */

      std::cout<<"Czas wykonania algorytmu Prima dla listy: "<<roznica.count()<<" milisekund."<<std::endl;
  
      delete [] odwiedzony;

    } /* end for */

  std::cout << std::endl;
  std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
  std::cout << "Sredni czas wykonania algorytmu Prima : ";
  std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;
  
  return wartosc_MST;
}
/******************************************************************************/

#endif
