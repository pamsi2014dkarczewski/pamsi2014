#ifndef MACIERZ_GRAF_HH
#define MACIERZ_GRAF_HH

#include <chrono> /* pomiar czasu */

#define ILOSC_POWTORZEN 105 /* ilosc powtorzen algorytmu */

/********************************* KLASA Macierz_graf *************************/
template <typename TYP>
class Macierz_graf
{
private:

  TYP **waga; /* macierz wag krawedzi */
  TYP **temp;

  int rozmiar; /* rozmiar macierzy */
  int ilosc_krawedzi;

public:

  /****************************** konstruktor *********************************/
  Macierz_graf();
  /****************************************************************************/

  /*************************** operacje na pliku/macierzy *********************/
  bool generuj_graf(double gestosc); 
  bool wczytaj_z_pliku(const std::string nazwa_odczytu);
  bool zapisz_do_pliku(const std::string nazwa_zapisu);
  /****************************************************************************/

  /********************************** dodatki *********************************/
  void wyswietl_macierz();
  bool graf_spojny();
  TYP krawedz(int poczatek, int koniec);
  int zeruj_krawedz(int poczatek, int koniec);
  void zmien_rozmiar(int rozmiar);
  void unia(int poczatek, int koniec, TYP *MST);
  TYP znajdz(int wartosc, TYP *MST);
  /****************************************************************************/

  /********************************* algorytmy ********************************/
  TYP algorytm_Kruskala();
  TYP algorytm_Prima();
  /****************************************************************************/

  /* destruktor */
  ~Macierz_graf()
  {  
    for (int i = 0; i < rozmiar; i++)
      {
	delete [] waga[i];
	delete [] temp[i];
      }
    delete [] waga;
    delete [] temp;  
  }

}; /* end class */
/******************************************************************************/


/*********************************** KONSTRUKTOR ******************************/
/* stworzenie macierzy */
template <typename TYP>
Macierz_graf<TYP>::Macierz_graf()
{
  rozmiar = 1;
  ilosc_krawedzi = 0;
  /* stworzenie macierzy */
  waga = new TYP *[rozmiar];
  temp = new TYP *[rozmiar];

  for (int i = 0; i < rozmiar; i++)
    {
      waga[i] = new TYP [rozmiar];
      temp[i] = new TYP [rozmiar];
    }

  /* wypelnienie macierzy wartoscia -1 */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i+1; j++)
	{
	  waga[i][j] = waga[j][i] = -1;
	  temp[i][j] = temp[j][i] = -1;
	}
    }
}
/******************************************************************************/


/******************************* GENEROWANIE GRAFU ****************************/
template <typename TYP>
bool Macierz_graf<TYP>::generuj_graf(double gestosc)
{
  TYP wartosc;
  int il_krawedzi = 0;

  /* wypelnienie macierzy losowymi wartosciami */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i; j++)
	{
	  wartosc = rand() % 100000;
	  
	  if( wartosc  < (gestosc*100000))
	    {
	      waga[i][j] = waga[j][i] = wartosc;
	      temp[i][j] = temp[j][i] = wartosc;
	      il_krawedzi++;
	    }
	  waga[j][j] = -1; /* przekatna macierzy */
	  temp[j][j] = -1;
	}
    }

  ilosc_krawedzi = il_krawedzi;

  return true;
}
/******************************************************************************/

/********************************** WCZYTYWANIE *******************************/
template <typename TYP>
bool Macierz_graf<TYP>::wczytaj_z_pliku(const std::string nazwa_odczytu)
{
  std::ifstream plik; /* dane wczytane do pliku */
  int poczatek, koniec;
  int il_krawedzi = 0;
  TYP wartosc;
  
  plik.open (nazwa_odczytu.c_str(), std::ios::in);

  if(plik.is_open()) /* jezeli plik zostanie otworzony */
    {
      std::cout << "Wczytuje dane !"<<std::endl;
 	
      while (!plik.eof() && !plik.bad())
	{
	  plik >> poczatek;
	  if(poczatek > rozmiar) std::cerr << "Poza rozmiarami macierzy !" << std::endl;
	  
	  plik >> koniec; 
	  if(koniec > rozmiar) std::cerr << "Poza rozmiarami macierzy !" << std::endl;

	  plik >> wartosc;
	  if(wartosc >= 0)
	    {
	      waga[poczatek][koniec] = waga[koniec][poczatek] = wartosc;
	      temp[poczatek][koniec] = temp[koniec][poczatek] = wartosc;
	      il_krawedzi++;  
	    }
	  else
	    {
	      std::cerr << "Waga krawedzi jest ujemna !" << std::endl;
	      std::cerr << "Zostanie ona zastapiona wartoscia '-1' !" << std::endl;
	      waga[poczatek][koniec] = waga[koniec][poczatek] = -1;
	      temp[poczatek][koniec] = temp[koniec][poczatek] = -1;
	    }
	}	
    }

  ilosc_krawedzi = il_krawedzi;

  plik.close();
  return true;
}
/******************************************************************************/


/******************************* ZAPISYWANIE **********************************/
template <typename TYP>
bool Macierz_graf<TYP>::zapisz_do_pliku(const std::string nazwa_zapisu)
{
  std::ofstream plik; 

  plik.open(nazwa_zapisu.c_str(), std::ios::out | std::ios::trunc);

  if(plik.good())
    {
      for(int i = 0; i < rozmiar; i++)
	{
	  for(int j = 0; j < i+1; j++)
	    {
	      if ( waga[i][j] > -1)
		{
		  plik << i << "\t";
		  plik << j << "\t";
		  plik << waga[i][j] << "\r" << std::endl;
		}
	    }
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


/**************************** WYSWIETLENIE MACIERZY ***************************/
template <typename TYP>
void Macierz_graf<TYP>::wyswietl_macierz()
{
  std::cout << "Wartosc '-1' oznacza brak polaczenia miedzy wierzcholkami" << std::endl;
 
  for (int i = 0; i < rozmiar; i++)
    {
      std::cout << std::endl;
      for (int j = 0; j < rozmiar; j++)
	{
	  std::cout << std::setw(4) << krawedz(i,j) << " ";
	}
    }
  std::cout << std::setw(0) << std::endl;
}
/******************************************************************************/


/*********************************** GRAF SPOJNY ******************************/
/* sprawdzenie czy graf jest spojny */
/* spojnosc zwraca true, niespojnosc zwraca false */
template <typename TYP>
bool Macierz_graf<TYP>::graf_spojny()
{
  int n = rozmiar;
  int m = ilosc_krawedzi;

  return ( ((n-1) <= m) && (((n*(n-1))/2) >= m) ) ? true : false;
}
/******************************************************************************/


/********************************** KRAWEDZ ***********************************/
template <typename TYP>
TYP Macierz_graf<TYP>::krawedz(int poczatek, int koniec)
{
  if (poczatek < rozmiar && koniec < rozmiar)
    return waga [poczatek][koniec];
  else
    return -1 ;
}
/******************************************************************************/


/**************************** ZEROWANIE KRAWEDZI ******************************/
/* zerowanie oznacza wspianie wartosci -1 do macierzy */
template <typename TYP>
int Macierz_graf<TYP>::zeruj_krawedz(int poczatek, int koniec)
{
  if (poczatek < rozmiar && koniec < rozmiar)
    {
      return waga [poczatek][koniec] = waga[koniec][poczatek] = -1;
    }  
  else
    {
      std::cerr << "Nie mozna wyzerowac krawedzi : ";
      std::cerr << "[" << poczatek << "][" << koniec << "]" << std::endl;
      return -2;
    }
}
/******************************************************************************/


/******************************* ZMIANA ROZMIARU ******************************/
template <typename TYP>
void Macierz_graf<TYP>::zmien_rozmiar(int roz)
{
  if (roz > 1)
    {
      /* usuniecie obecnej macierzy */
      for (int i = 0; i < rozmiar; i++)
	{
	  delete [] waga[i];
	  delete [] temp[i];
	}

      delete [] waga;
      delete [] temp;

      rozmiar = roz;
      
      /* stworzenie nowej macierzy z wymaganym rozmiarem */
      waga = new TYP *[rozmiar];
      temp = new TYP *[rozmiar];

      for (int i = 0; i < rozmiar; i++)
	{
	  waga[i] = new TYP [rozmiar];
	  temp[i] = new TYP [rozmiar];
	}
      
      /* wypelnienie macierzy wartoscia -1 */
      for (int i = 0; i < rozmiar; i++)
	{
	  for (int j = 0; j < i+1; j++)
	    {
	      waga[i][j] = waga[j][i] = -1;
	      temp[i][j] = temp[j][i] = -1;
	    }
	}
    }
  else
    {
      std::cerr << "Rozmiar macierzy musi byc wiekszy od 1 !" << std::endl;
    }
}
/******************************************************************************/


/************************************* UNIA ***********************************/
template <typename TYP>
void Macierz_graf<TYP>::unia(int poczatek, int koniec, TYP *MST)
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
TYP Macierz_graf<TYP>::znajdz(int wartosc, TYP *MST)
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
TYP Macierz_graf<TYP>::algorytm_Kruskala()
{
  TYP wartosc_MST;

  int poczatek;
  int koniec;
  int ilosc_krawedzi;
  
  double suma = 0; 
  
  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      TYP *MST = new TYP [rozmiar]; /* minimalne drzewo rozpinajace */

      wartosc_MST = 0;
 
      poczatek = 0;
      koniec = 0;
      ilosc_krawedzi = 0;
      
      /* wypelnienie macierzy ciagle tymi samymi wartosciami */
      for(int i = 0; i < rozmiar; i++)
	{
	  for(int j = 0; j < rozmiar; j++)
	    {
	      waga[i][j] = temp[i][j];
	    }
	}
      
      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();

      /* wstepne wypelnienie minimalnego drzewa rozpinajacego */
      for(int i = 0; i < rozmiar; i++)
	{
	  MST[i] = i;
	}
  
      while (ilosc_krawedzi < rozmiar - 1)
	{
	  /* minimum ma wartosc maksymalna, aby znalezc minimum :) */
	  TYP minimum = std::numeric_limits<TYP>::max();

	  /* znajdowanie minimum w macierzy */
	  for (int i = 0; i < rozmiar; i++)
	    {
	      for (int j = 0; j < i+1; j++)
		{
		  if ((waga[i][j] < minimum) && (waga[i][j] > (-1)) )
		    {
		      poczatek = j;
		      koniec = i;
		      minimum = waga[i][j];
		    } /* end if(waga...) */
		} /* end for */
	    } /* end for */
     
	  if(znajdz(poczatek,MST) != znajdz(koniec,MST))
	    {
	      unia(poczatek,koniec,MST);
	      wartosc_MST += minimum;
	      ilosc_krawedzi++;	
	    } /* end if(znajdz...) */

	  /* zerowanie pobranego minimum */
	  zeruj_krawedz(poczatek,koniec);
 
	} /* end while */

      auto t2 = std::chrono::high_resolution_clock::now();
  
      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
  
      if(i > 5) suma += roznica.count(); /* pierwsze 5 czasow pomijam */

      std::cout<<"Czas wykonania algorytmu Kruskala dla macierzy: "<<roznica.count()<<" milisekund."<<std::endl;	
 
      /* usuniecie tabicy MST */
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
TYP Macierz_graf<TYP>::algorytm_Prima()
{
  int il_wierzcholkow; /* ilosc wierzcholkow */
  TYP wartosc_MST; /* zwracana wartosc minimalnego drzewa rozpinajacego */ 
  TYP minimum; 

  /* int poczatek = 0; */
  int koniec = 0; 

  double suma = 0;

  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      bool *odwiedzony = new bool [rozmiar]; /* wierzcholki odwiedzone */

      il_wierzcholkow = 0;
      wartosc_MST = 0;

      /* wypelnienie macierzy ciagle tymi samymi wartosciami */
      for(int i = 0; i < rozmiar; i++)
	{
	  for(int j = 0; j < rozmiar; j++)
	    {
	      waga[i][j] = temp[i][j];
	    }
	}

      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();

      /* na poczatku zaden wierzcholek nie jest odwiedzony */  
      for(int i = 0; i < rozmiar; i++) 
	{
	  odwiedzony[i] = false;
	}

      odwiedzony[0] = true; /* pierwszy zostal odwiedzony */

      /* sprawdzamy wszystkie wierzcholki */
      while(il_wierzcholkow < rozmiar - 1)
	{
	  /* w minimum wpisywana jest prowizoryczna nieskonczonosc */
	  minimum = std::numeric_limits<TYP>::max();

	  /* sprawdzenie wszystkich dolaczonych wierzcholkow */
	  for(int i = 0; i < rozmiar; i++)
	    {
	      if (odwiedzony[i] == true)
		{
		  /* znajdowanie minimalnej krawedzi */
		  for(int j = 0; j < rozmiar; j++) 
		    {
		      if(waga[i][j] < minimum && waga[i][j] > -1 && odwiedzony[j] == false)
			{
			  minimum = waga[i][j];
			  /* poczatek = i; */
			  koniec = j;
			}
		    }
		}
	    }

	  wartosc_MST += minimum;
	  odwiedzony[koniec] = true;
	  
	  il_wierzcholkow++;
	} /* end while */

      auto t2 = std::chrono::high_resolution_clock::now();

      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);

      if(i > 5) suma += roznica.count(); /* pierwsze 5 czasow pomijam */

      std::cout<<"Czas wykonania algorytmu Prima dla macierzy: "<<roznica.count()<<" milisekund."<<std::endl;
  
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
