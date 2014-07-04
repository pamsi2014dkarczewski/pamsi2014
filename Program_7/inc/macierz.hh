#ifndef MACIERZ_GRAF_HH
#define MACIERZ_GRAF_HH

#include <chrono> /* pomiar czasu */
#include <queue>

#define ILOSC_POWTORZEN 15 /* ilosc powtorzen algorytmu (>=5) */

/********************************* KLASA Macierz_graf *************************/
template <typename TYP>
class Macierz_graf
{
private:

  TYP **waga; /* macierz wag krawedzi */
  TYP **temp;
  TYP **przeplyw; /* macierz przeplywow */

  TYP *poprzednik; /* tablica przechowujaca poprzednikow */
  TYP *pozostalo; /* tablica przechowuje wartosci przeplywu ktore pozostaly */

  std::queue <TYP> kolejka;

  /* numer wierzcholka ze zrodlem i z ujsciem */
  int zrodlo, ujscie;
  
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
  /****************************************************************************/

  /********************************** dodatki *********************************/
  void wyswietl_macierz();
  void odtworz_graf(TYP **waga, TYP **temp);
  void zmien_rozmiar(int rozmiar);
  /****************************************************************************/

  /********************************* algorytmy ********************************/
  void algorytm_Edmondsa_Karpa();
  /****************************************************************************/


  /* destruktor */
  ~Macierz_graf()
  {  
    for (int i = 0; i < rozmiar; i++)
      {
	delete [] waga[i];
	delete [] temp[i];
	delete [] przeplyw[i];
      }
    delete [] waga;
    delete [] temp;
    delete [] przeplyw;
    delete [] pozostalo;
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
  przeplyw = new TYP *[rozmiar];

  pozostalo = new TYP [rozmiar];
  poprzednik = new TYP [rozmiar];

  for (int i = 0; i < rozmiar; i++)
    {
      waga[i] = new TYP [rozmiar];
      temp[i] = new TYP [rozmiar];
      przeplyw[i] = new TYP [rozmiar];
    }

  /* wypelnienie macierzy wartoscia -1, 0 */
  for (int i = 0; i < rozmiar; i++)
    {
      for (int j = 0; j < i+1; j++)
	{
	  waga[i][j] = waga[j][i] = -1;
	  temp[i][j] = temp[j][i] = -1;
	  przeplyw[i][j] = przeplyw[j][i] = 0;
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
      for (int j = 0; j < rozmiar; j++)
	{
	  /* zakres generowania liczb np. <1,500> */
	  wartosc = (rand() % waga_max) + waga_min; 
	  
	  if( wartosc  <= (gestosc*waga_max) && i != j)
	    {
	      waga[i][j] = wartosc;
	      temp[i][j] = wartosc;
	      ilosc_krawedzi++;
	    }
	  waga[j][j] = 0; /* przekatna macierzy */
	  temp[j][j] = 0;
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

      /* wczytanie pierwszej linii, ktora informuje o ilosci wierzcholkow oraz 
	 ilosci krawedzi. */
      plik >> rozmiar >> ilosc_krawedzi;

      if(plik.bad())
	{
	  std::cerr << "Blad w pierwszej linii pliku !" << std::endl;
	  return false;
 	}

      /* wczytanie drugiej linii, ktora zawiera 'zrodlo' i 'ujscie' */
      plik >> zrodlo >> ujscie;

      if(plik.bad())
	{
	  std::cerr << "Blad w drugiej linii pliku !" << std::endl;
	  return false;
 	}

      /* wczytywanie grafu */
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
	  if(wartosc >= 0)
	    {
	      waga[poczatek][koniec] = wartosc;
	      temp[poczatek][koniec] = wartosc; 
	    }
	  else
	    {
	      std::cerr << "Nieprawidlowa waga krawedzi !" << std::endl;
	      std::cerr << "Zostanie ona zastapiona wartoscia '0' !" << std::endl;
	      waga[poczatek][koniec] = 0;
	      temp[poczatek][koniec] = 0;
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

      plik << rozmiar << "\t" << ilosc_krawedzi << std::endl;
      plik << zrodlo << "\t" << ujscie << std::endl;

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
	  std::cout << std::setw(4) << waga[i][j] << " ";
	}
    }
  std::cout << std::setw(0) << std::endl;
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
	  delete [] przeplyw[i];
	}

      delete [] waga;
      delete [] temp;
      delete [] przeplyw;
      delete [] pozostalo;
      delete [] poprzednik;

      rozmiar = roz;
      
      /* stworzenie nowej macierzy z wymaganym rozmiarem */
      waga = new TYP *[rozmiar];
      temp = new TYP *[rozmiar];
      przeplyw = new TYP *[rozmiar];

      pozostalo = new TYP [rozmiar];
      poprzednik = new TYP [rozmiar];

      for (int i = 0; i < rozmiar; i++)
	{
	  waga[i] = new TYP [rozmiar];
	  temp[i] = new TYP [rozmiar];
	  przeplyw[i] = new TYP [rozmiar];
	}
      
      /* wypelnienie macierzy wartoscia 0 */
      for (int i = 0; i < rozmiar; i++)
	{
	  for (int j = 0; j < i+1; j++)
	    {
	      waga[i][j] = waga[j][i] = 0;
	      temp[i][j] = temp[j][i] = 0;
	      przeplyw[i][j] = przeplyw[j][i] = 0;
	    }
	}
    }
  else
    {
      std::cerr << "Rozmiar macierzy musi byc wiekszy od 1 !" << std::endl;
    }
}
/******************************************************************************/


/************************** ALGORYTM EDMONDSA-KARPA ***************************/
template <typename TYP>
void Macierz_graf<TYP>::algorytm_Edmondsa_Karpa()
{
  /* wartosc maksymalna symbolizuje nieskonczonosc */
  TYP max = std::numeric_limits<TYP>::max();

  TYP przeplyw_max; /* wartosc maksymalnego przeplywu w sieci */
  TYP przepustowosc_residualna;

  bool *odwiedzone = new bool [rozmiar];

  int wyjscie = 0; /* wyjscie z petli */

  double suma = 0; /* suma czasow */
  
  std::cout << "Algorytm zostanie wykonany " << ILOSC_POWTORZEN << " razy. ";
  std::cout << "Piec pierwszych wywolan to 'rozgrzewka' :).";
  std::cout << std::endl << std::endl;

  /* 105 pomiarow czasu */
  for(int i = 1; i <= ILOSC_POWTORZEN; i++)
    {
      /* odtworzenie grafu, chodzi o to aby graf byl ciagle ten sam */
      odtworz_graf(waga,temp);

      /* rozpoczecie pomiaru czasu */
      auto t1 = std::chrono::high_resolution_clock::now();

      /* wyzerowanie macierzy z wartoscia przeplywu */
      for(int i = 0; i < rozmiar; i++)
	{
	  for (int j = 0; j < i + 1; j++)
	    {
	      przeplyw[i][j] = przeplyw[j][i] = 0;
	    }
	}

      przeplyw_max = 0;

      while(true)
	{
	  /* inicjalizacja */
	  for(int i = 0; i < rozmiar; i++)
	    {
	      odwiedzone[i] = false; /* zadna krawedz nie jest odwiedzona */
	      poprzednik[i] = 0; /* brak poprzednikow */
	    }

	  poprzednik[zrodlo] = -1;
	  pozostalo[zrodlo] = max;

	  /* wyzerowanie kolejki */
	  while(kolejka.size()) kolejka.pop(); 

	  kolejka.push(zrodlo); /* dodanie zrodla na koniec kolejki */

	  wyjscie = 0;
	  int i, j;

	  while(kolejka.size()) /* dopoki kolejka zawiera elementy */
	    {
	      i = kolejka.front(); /* pobranie elementu */
	      odwiedzone[i] = true; /* 'odwiedzenie' tego elementu */
	      kolejka.pop();

	      for(j = 0; j < rozmiar; j++) /* rozpoczecie BFS */
		{
		  /* wyznaczenie przepustowosci residualnej */
		  przepustowosc_residualna = waga[i][j] - przeplyw[i][j];

		  if(przepustowosc_residualna && !poprzednik[j] && odwiedzone[j] == false)
		    {
		      poprzednik[j] = i; /* zapamietanie poprzednika */

		      /* obliczenie przepustowosci do wezla 'j' */
		      pozostalo[j] = min(pozostalo[i], przepustowosc_residualna);
		      odwiedzone[j] = true; /* wezel odwiedzony */

		      if(j == ujscie)
			{
			  przeplyw_max += pozostalo[ujscie];

			  while( j != zrodlo) /* cofanie od ujscia do zrodla */
			    {
			      i = poprzednik[j];

			      /* w kierunku zwiekszenie przeplywu */
			      przeplyw[i][j] += pozostalo[ujscie];

			      /* kierunek przeciwny, zmniejszenie przeplywu */
			      przeplyw[j][i] -= pozostalo[ujscie];

			      /* nastepna krawedz */
			      j = i;
			    }
			  wyjscie = 1; break;
			}
		      kolejka.push(j);
		    } /* end if(przepustowosc_residualna && ...) */
		} /* end for */
	      if(wyjscie) break;
	    }
	  if(!wyjscie) break;

	} /* end while(true) */

      auto t2 = std::chrono::high_resolution_clock::now();
  
      auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
        
      std::cout << "Wartosc maksymalnego przeplywu w sieci: " << przeplyw_max;
      std::cout << std::endl;
      
      if(i > 5) suma += roznica.count(); /* pierwsze 5 czasow pomijam */

      std::cout << "Czas wykonania algorytmu Edmondsa-Karpa dla macierzy: ";
      std::cout << roznica.count()<<" milisekund." << std::endl << std::endl;	
 
    }
 
  std::cout << "******************* PODSUMOWANIE ******************"<<std::endl;
  std::cout << "Sredni czas wykonania algorytmu Edmondsa-Karpa: ";
  std::cout << (suma/(ILOSC_POWTORZEN - 5)) << " milisekund" << std::endl;

  delete [] odwiedzone;
}
/******************************************************************************/

#endif
