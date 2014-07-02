#ifndef MACIERZ_GRAF_HH
#define MACIERZ_GRAF_HH

#include <chrono> /* pomiar czasu */

#define ILOSC_POWTORZEN 105 /* ilosc powtorzen algorytmu (>=5) */

/********************************* KLASA Macierz_graf *************************/
template <typename TYP>
class Macierz_graf
{
private:

  TYP **waga; /* macierz wag krawedzi */
  TYP **temp;

  TYP zrodlo;
  TYP *droga;
  TYP *poprzednik;
  
  int rozmiar; /* rozmiar macierzy, ilosc wierzcholkow */
  int ilosc_krawedzi;

public:

  /****************************** konstruktor *********************************/
  Macierz_graf();
  /****************************************************************************/

  /*************************** operacje na pliku/macierzy *********************/
  bool generuj_graf(double gestosc); 
  bool wczytaj_z_pliku(const std::string nazwa_odczytu);
  bool zapisz_do_pliku(const std::string nazwa_zapisu);
  bool zapisz_droge_do_pliku(const std::string nazwa_zapisu);
  /****************************************************************************/

  /********************************** dodatki *********************************/
  void wyswietl_macierz();
  bool graf_spojny();
  void odtworz_graf(TYP **waga, TYP **temp);
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
  ~Macierz_graf()
  {  
    for (int i = 0; i < rozmiar; i++)
      {
	delete [] waga[i];
	delete [] temp[i];
      }
    delete [] waga;
    delete [] temp;
    delete [] droga;
    delete [] poprzednik;  
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
  zrodlo = 0;

  /* stworzenie macierzy */
  waga = new TYP *[rozmiar];
  temp = new TYP *[rozmiar];
  droga = new TYP [rozmiar];
  poprzednik = new TYP [rozmiar];

  for (int i = 0; i < rozmiar; i++)
    {
      waga[i] = new TYP [rozmiar];
      temp[i] = new TYP [rozmiar];
    }

  /* wypelnienie macierzy wartoscia -20 */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i+1; j++)
	{
	  waga[i][j] = waga[j][i] = -20;
	  temp[i][j] = temp[j][i] = -20;
	}
    }
}
/******************************************************************************/


/******************************* GENEROWANIE GRAFU ****************************/
template <typename TYP>
bool Macierz_graf<TYP>::generuj_graf(double gestosc)
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

  /* wypelnienie macierzy losowymi wartosciami */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i; j++)
	{
	  /* zakres generowania liczb np. <1,500> */
	  wartosc = (rand() % waga_max) + waga_min; 
	  
	  if( wartosc  <= (gestosc*waga_max))
	    {
	      waga[i][j] = waga[j][i] = wartosc;
	      temp[i][j] = temp[j][i] = wartosc;
	      ilosc_krawedzi++;
	    }
	  waga[j][j] = -20; /* przekatna macierzy */
	  temp[j][j] = -20;
	}
    }

  return true;
}
/******************************************************************************/


/********************************** WCZYTYWANIE *******************************/
template <typename TYP>
bool Macierz_graf<TYP>::wczytaj_z_pliku(const std::string nazwa_odczytu)
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
	      waga[poczatek][koniec] = waga[koniec][poczatek] = wartosc;
	      temp[poczatek][koniec] = temp[koniec][poczatek] = wartosc; 
	    }
	  else
	    {
	      std::cerr << "Nieprawidlowa waga krawedzi !" << std::endl;
	      std::cerr << "Zostanie ona zastapiona wartoscia '-20' !" << std::endl;
	      waga[poczatek][koniec] = waga[koniec][poczatek] = -20;
	      temp[poczatek][koniec] = temp[koniec][poczatek] = -20;
	    }
	}	
    }

  plik.close();
  return true;
}
/******************************************************************************/


/************************** ZAPISYWANIE MACIERZY ******************************/
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
	      if ( waga[i][j] > -20)
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


/******************************* ZAPISYWANIE DROGI ****************************/
template <typename TYP>
bool Macierz_graf<TYP>::zapisz_droge_do_pliku(const std::string nazwa_zapisu)
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


/**************************** WYSWIETLENIE MACIERZY ***************************/
template <typename TYP>
void Macierz_graf<TYP>::wyswietl_macierz()
{
  std::cout << "Wartosc '-20' oznacza brak polaczenia miedzy wierzcholkami" << std::endl;
 
  for (int i = 0; i < rozmiar; i++)
    {
      std::cout << std::endl;
      for (int j = 0; j < rozmiar; j++)
	{
	  std::cout << std::setw(4) << waga[i][j] << " ";
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


/******************************* ODTWORZ GRAF *********************************/
template <typename TYP>
void Macierz_graf<TYP>::odtworz_graf(TYP **waga, TYP **temp)
{
  /* wypelnienie macierzy ciagle tymi samymi wartosciami */
  /* do macierzy waga[][] przypisywana jest wartosc */
  for(int i = 0; i < rozmiar; i++)
    {
      for(int j = 0; j < rozmiar; j++)
	{
	  waga[i][j] = temp[i][j];
	}
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
      delete [] droga;
      delete [] poprzednik;

      rozmiar = roz;
      
      /* stworzenie nowej macierzy z wymaganym rozmiarem */
      waga = new TYP *[rozmiar];
      temp = new TYP *[rozmiar];
      droga = new TYP [rozmiar];
      poprzednik = new TYP [rozmiar];

      for (int i = 0; i < rozmiar; i++)
	{
	  waga[i] = new TYP [rozmiar];
	  temp[i] = new TYP [rozmiar];
	}
      
      /* wypelnienie macierzy wartoscia -20 */
      for (int i = 0; i < rozmiar; i++)
	{
	  for (int j = 0; j < i+1; j++)
	    {
	      waga[i][j] = waga[j][i] = -20;
	      temp[i][j] = temp[j][i] = -20;
	    }
	}
    }
  else
    {
      std::cerr << "Rozmiar macierzy musi byc wiekszy od 1 !" << std::endl;
    }
}
/******************************************************************************/


/******************************** WYJSCIE NA PLIK *****************************/
template <typename TYP>
void Macierz_graf<TYP>::wyjscie_na_plik(std::ofstream &plik)
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
void Macierz_graf<TYP>::sciezka(int w, std::ofstream &plik)
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
void Macierz_graf<TYP>::algorytm_Dijkstry()
{
  /* wartosc maksymalna symbolizuje nieskonczonosc */
  TYP max = std::numeric_limits<TYP>::max();
  
  int licznik;
  int min_index;
  int minimum;
  
  bool *odwiedzone = new bool [rozmiar];

  double suma = 0; /* suma czasow */
  
  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      licznik = 0;
      min_index = 0;
      /* odtworzenie grafu, chodzi o to aby graf byl ciagle ten sam */
      odtworz_graf(waga,temp);

      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();

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

	  for(int i = 0; i < rozmiar; i++)
	    {
	      if((!odwiedzone[i]) && (waga[min_index][i] > -1))
		{
		  if(droga[i] > droga[min_index]+waga[min_index][i])
		    {
		      droga[i] = droga[min_index]+waga[min_index][i];
		      poprzednik[i] = min_index;
		    }
		}
	    }	  
	  licznik++;
	}

      auto t2 = std::chrono::high_resolution_clock::now();
  
      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
  
      if(i > 5) suma += roznica.count(); /* pierwsze 5 czasow pomijam */

      std::cout<<"Czas wykonania algorytmu Dijkstry dla macierzy: "<<roznica.count()<<" milisekund."<<std::endl;	
 
    }
 
  std::cout << std::endl;
  std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
  std::cout << "Sredni czas wykonania algorytmu Dijkstry: ";
  std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;

  delete [] odwiedzone;
}
/******************************************************************************/


/**************************** ALGORYTM BELLMANA-FORDA *************************/
template <typename TYP>
bool Macierz_graf<TYP>::Bellman_Ford()
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
  for(int k = 1; k < rozmiar; k++)
    {
      wyjscie = true;
      for(int i = 0; i < rozmiar; i++)
	{
	  for(int j = 0; j < rozmiar; j++)
	    {
	      if(i!=j && waga[i][j] >= -10 && waga[i][j] <= 1000)
		{
		  if(droga[j] > droga[i] + waga[i][j])
		    {
		      wyjscie = false;
		      droga[j] = droga[i] + waga[i][j];	  
		      poprzednik[j] = i;
		    }
		}
	    }
	}
      if(wyjscie) return true;
    }

  /* sprawdzenie ujemnego cyklu */
  for(int i = 0; i < rozmiar; i++)
    {
      for(int j = 0; j < rozmiar; j++)
	{
	  if((i!=j) && (waga[i][j] >= -10) && (waga[i][j] <= 1000))
	    {
	      if(droga[j] > droga[i] + waga[i][j])
		{
		  return false;
		}
	    }
	}
    }

  return true;
}
/******************************************************************************/


/************************** ALGORYTM BELLMANA-FORDA ***************************/
template <typename TYP>
void Macierz_graf<TYP>::algorytm_Bellmana_Forda()
{ 
  double suma = 0; /* suma czasow */

  bool flaga = true;

  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :)." << std::endl;
  
  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      odtworz_graf(waga,temp);

      /* rozpoczecie pomiaru czasu */      
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
	  
	  std::cout << "Czas wykonania algorytmu Bellmana-Forda dla macierzy: ";
	  std::cout << roznica.count() << " milisekund." << std::endl;
	}
    } /* end for */
  
  if(flaga) /* gdy algorytm wykryl ujemny cykl to podsumowanie jest zbedne */
    {
      std::cout << std::endl;
      std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
      std::cout << "Sredni czas wykonania algorytmu Bellmana-Forda: ";
      std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;
    }
}
/******************************************************************************/

#endif
