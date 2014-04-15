#ifndef EKSPERYMENT_HH
#define EKSPERYMENT_HH

#include <iostream>
#include <fstream> /* praca z plikiem */
#include <limits> /* limit ignorowania znakow */
#include <random> /* generatory */
#include <string> /* dla nazw plikow */


int uporzadkowanie_elementow(int rozmiar);


/******************************** NOWY EKSPERYMENT ****************************/
template <typename TYP>
bool nowy_eksperyment(TYP *tablica, TYP *rozklad, unsigned int rozmiar)
{
  char opcja;
  while(true)
    {
      std::cout<<std::endl;
      std::cout << "Tablica posiada "<<rozmiar<<" elementow."<<std::endl;
      std::cout << "Rozpoczac nowy eksperyment ? [t/n]: ";
	  
      std::cin >> opcja;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  
      std::cout<<std::endl;
	  
      switch(opcja)
	{
	case 'n': /* wyjscie z programu */
	  {
	    std::cout << "Koniec dzialania programu !"<<std::endl;
	    std::cout << "___________________________"<<std::endl;
	    delete [] tablica;
	    delete [] rozklad;
	  }	  
	  return false;
	  
	case 't':
	  { 
	    eksperyment(tablica,rozklad,rozmiar);
	    zapisz_do_pliku(rozklad,rozmiar);
	  }	  
	  break;
	      
	default: /* opcja nierozpoznana */
	  std::cerr << "--------------------------------"<<std::endl;
	  std::cerr << "Nie rozpoznano opcji :'"<<opcja<<"' "<<std::endl;
	  std::cerr << "Wprowadz 't' lub 'n'"<<std::endl;
	  std::cerr << "--------------------------------"<<std::endl;

	} /* end switch */
    } /* end while */

  return true;
}
/******************************************************************************/


/******************* MENU DO PRZEPROWADZENIA EKSPERYMENTU *********************/
template <typename TYP>
bool eksperyment(TYP *tablica, TYP *rozklad, int rozmiar)
{
  char wybor;

  while(true)
    {
      std::cout << "Wczytac dane z pliku ? [t/n]: ";
      std::cin >> wybor;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

      switch (wybor)
	{
	case 't':
	  {
	    if(wczytaj_z_pliku(rozklad,rozmiar))
	      {
		/* jezeli uzytkownik wczyta dane z pliku to pozostaje mu tylko
		   wybrac rodzaj sortowania danych */
		wybor_sortowania(tablica,rozklad,rozmiar);
		return false;
	      }
	    else
	      {
		std::cerr << "Prosze wygenerowac wlasny rozklad."<<std::endl;
	      }
	  }
	case 'n':
	  {
	    std::cout<<std::endl;
	    /* wybranie rozkladu liczb (jednostajny,normalny,Poissona) */
	    rozklad_liczb(tablica,rozklad,rozmiar);
	    
	    std::cout << std::endl;
	    /* wybranie sortowania (babelkowe, scalanie, introspektywne) */
	    wybor_sortowania(tablica,rozklad,rozmiar);
	    return false;	    
	  }
	default:
	  {
	    std::cerr << "---------------------------------"<<std::endl;
	    std::cerr << "Nie rozpoznano opcji '"<<wybor<<"'"<<std::endl;
	    std::cerr << "Wprowadz 't' lub 'n'"<<std::endl;
	    std::cerr << "---------------------------------"<<std::endl;
	  }
	} /* end switch */
    } /* end while */

  return true;
}
/******************************************************************************/


/****************** WYBOR ROZKLADU ORAZ GENEROWANIE LICZB *********************/
template <typename TYP>
int rozklad_liczb(TYP *tablica, TYP *rozklad, int rozmiar)
{
  /* 'a' i 'b' --> parametry rozkladow 
     'liczba' --> wygenerowana liczba */
  double a,b,liczba; 
  char opcja;

  while(true)
    {
      std::cout << "1 - Generowanie tablicy i sortowanie z rozkladu jednostajnego"<<std::endl;
      std::cout << "2 - Generowanie tablicy i sortowanie z rozkladu normalnego"<<std::endl;
      std::cout << "3 - Generowanie tablicy z sortowanie z rozkladu Poissona"<<std::endl;
      std::cout << "Twoj wybor (1-3): ";
      
      std::cin >> opcja;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

      std::cout << std::endl;

      /* generator liczb losowych */
      std::default_random_engine generator;

      switch(opcja)
	{
	case '1': /* rozklad jednostajny */
	  {
	    std::cout << "Rozklad jednostajny na przedziale [a,b]"<<std::endl;
	    std::cout << "Podaj poczatek przedzialu: ";
	    std::cin >> a;
	    std::cout << "Podaj koniec przedzialu: ";
	    std::cin >> b;

	    /* generowanie rozkladu jednostajnego na przedziale [a,b]*/
	    std::uniform_real_distribution<double> distribution(a,b);
	    
	    /* zwrocenie ile elementow w tablicy ma byc uporzadkowanych */
	    int ilosc_sort = uporzadkowanie_elementow(rozmiar);
	    	    
	    std::cout << "Trwa generowanie rozkladu. Prosze czekac..."<<std::endl;

	    /* od 'zera' do 'ilosc_sort' (10%, 50%, 90%, 99%)  tablica bedzie 
	       wypelniona liczbami losowymi nastepnie tablica jest sortowana 
	       tak aby poczatkowe elementy byly ulozone rosnaco. */
	    for (int i = 0; i<ilosc_sort; i++)
	      {
		liczba = distribution(generator);
		rozklad[i]=liczba;
	      } 

	    /* uporzadkowanie elementow za pomoca sortowania */
	    sortowanie_introspektywne(rozklad,ilosc_sort);	    

	    /* dalsza czesc tablicy generowana jest w sposob losowy */
	    for (int j = ilosc_sort; j<rozmiar; j++)
	      {
		liczba = distribution(generator);
		rozklad[j]=liczba;
	      }
	  }
	  return false;
	  
	case '2': /* rozklad normalny */
	  {
	    std::cout << "Rozklad normalny."<<std::endl;
	    std::cout << "Podaj wartosc srednia: ";
	    std::cin >> a;
	    std::cout << "Podaj wartosc odchylenia standardowego: ";
	    std::cin >> b;

	    /* generowanie rozkladu normalnego */
	    std::normal_distribution<double> distribution(a,b);
	    
	    int ilosc_sort = uporzadkowanie_elementow(rozmiar);
	    
	    std::cout << "Trwa generowanie rozkladu. Prosze czekac..."<<std::endl;
	    
	   /* od 'zera' do 'ilosc_sort' (10%, 50%, 90%, 99%) tablica bedzie 
	       wypelniona liczbami losowymi nastepnie tablica jest sortowana 
	       tak aby poczatkowe elementy byly ulozone rosnaco. */
	    for (int i = 0; i<ilosc_sort; i++)
	      {
		liczba = distribution(generator);
		rozklad[i]=liczba;
	      } 

	    /* zwrocenie ile elementow w tablicy ma byc uporzadkowanych */
	    sortowanie_introspektywne(rozklad,ilosc_sort);	    

	    /* dalsza czesc tablicy generowana jest w sposob losowy */
	    for (int j = ilosc_sort; j<rozmiar; j++)
	      {
		liczba = distribution(generator);
		rozklad[j]=liczba;
	      }
	  }
	  
	  return false;
	  
	case '3': /* rozklad Poissona */
	  {
	    std::cout << "Rozklad Poissona."<<std::endl;
	    std::cout << "Podaj wartosc parametru 'alfa' rozkladu Poissona: ";
	    std::cin >> a;

	    /* generowanie rozkladu Poissona */
	    std::poisson_distribution<int> distribution(a);

	    /* zwrocenie ile elementow w tablicy ma byc uporzadkowanych */
	    int ilosc_sort = uporzadkowanie_elementow(rozmiar);
	    	    
	    std::cout << "Trwa generowanie rozkladu. Prosze czekac..."<<std::endl;

	   /* od 'zera' do 'ilosc_sort' (10%, 50%, 90%, 99%) tablica bedzie 
	       wypelniona liczbami losowymi nastepnie tablica jest sortowana 
	       tak aby poczatkowe elementy byly ulozone rosnaco. */
	    for (int i = 0; i<ilosc_sort; i++)
	      {
		liczba = distribution(generator);
		rozklad[i]=liczba;
	      }

	    sortowanie_introspektywne(rozklad,ilosc_sort);	    

	    /* dalsza czesc tablicy generowana jest w sposob losowy */
	    for (int j = ilosc_sort; j<rozmiar; j++)
	      {
		liczba = distribution(generator);
		rozklad[j]=liczba;
	      }
	  }
	  return false;
	  
	default:
	  {
	    std::cerr << "---------------------------------"<<std::endl;
	    std::cerr << "Nie rozpoznano opcji '"<<opcja<<"'"<<std::endl;
	    std::cerr << "Wprowadz liczbe z zakresu 1-3."<<std::endl;
	    std::cerr << "---------------------------------"<<std::endl;
	  }
	} /* end switch */

    } /* end while */

  return 1;
}
/******************************************************************************/


/***************************** PRZYPISANIE ROZKLADU ***************************/
/* przypisywanie wygenerowanego rozkladu do tablicy, aby pracowac ciagle na 
   tym samym rozkladzie liczb. Po zakonczeniu programu rozklad moze byc 
   zapisany do pliku */

template <typename TYP>
void przypisz_rozklad(TYP *tablica, TYP *rozklad, int rozmiar)
{
  for(int i = 0; i<rozmiar; i++)
    {
      tablica[i]=rozklad[i];
    }
}
/******************************************************************************/


/*************************** SPRAWDZENIE SORTOWANIA ***************************/
/* sprawdzenie czy tablica zostala prawidlowo posortowana, jezeli nie to 
   uzytkownik zostanie o tym poinformowany */
template <typename TYP>
bool sprawdzenie_sortowania(TYP *tablica, int rozmiar)
{
  for (int i = 0; i<rozmiar-1; i++)
    {
      if(tablica[i]>tablica[i+1])
	{
	  std::cerr << "Tablica nie jest posortowana :-("<<std::endl;
	  return false;
	}
    }
  return true;
}
/******************************************************************************/


/************************ WCZYTYWANIE DANYCH Z PLIKU **************************/
template <typename TYP>
bool wczytaj_z_pliku(TYP *tablica, int rozmiar)
{
  std::ifstream plik; /* dane wczytane do pliku */
  int i=0;
  
  std::string nazwa_odczytu;
  std::cout << "Podaj nazwe pliku do wczytania (bez rozszerzenia): ";
  std::cin >> nazwa_odczytu;
  
  nazwa_odczytu += ".dat";
  plik.open (nazwa_odczytu.c_str(), std::ios::in);

  if(plik.is_open()) /* jezeli plik zostanie otworzony */
    {
      std::cout<<"Wczytuje dane !"<<std::endl;

      while (!plik.eof() && !plik.bad() && (i<rozmiar))
	{
	  if( (plik>>tablica[i]).fail() )
	    {
	      std::cerr<<"Znak nieprawidlowy, zostanie zastapiony przez '0'"<<std::endl;
	      plik.clear(); 
	      plik.ignore(std::numeric_limits<std::streamsize>::max(),'\n');	
	    }
	  i++;
	}
    }
  else 
    {
      std::cerr<<"NIE MOZNA ODCZYTAC PLIKU '"<<nazwa_odczytu<<"' LUB PLIK NIE ISTNIEJE "<<std::endl;
      return false;
    }

  std::cout<<"Wczytywanie zakonczone powodzeniem."<<std::endl<<std::endl; 

  return true;
}
/******************************************************************************/



/************************** ZAPISYWANIE DANYCH DO PLIKU ***********************/
template <typename TYP>
bool zapisz_do_pliku(TYP *tablica, int rozmiar)
{
  std::ofstream plik;
  std::string nazwa_zapisu;
  char wybor;  

  while(true)
    {  
      std::cout << "Zapisac wygenerowany rozklad do pliku ? [t/n]: ";
      std::cin >> wybor;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      
      switch(wybor)
	{
	case 't':
	  {
	    std::cout << "Podaj nazwe pod ktora chcesz zapisac dane (bez rozszerzenia): ";
	    std::cin >> nazwa_zapisu;
  
	    nazwa_zapisu += ".dat";
	    plik.open(nazwa_zapisu.c_str(), std::ios::out | std::ios::trunc);

	    if(plik.good())
	      {
		for(int i=0; i<rozmiar; i++)
		  {
		    plik<<tablica[i]<<std::endl;
		  }
	      }
	    else
	      {
		std::cerr<<"ZAPISANIE DO PLIKU '"<<nazwa_zapisu<<"' NIE POWIODLO SIE !!!"<<std::endl;
	      }
	    return false;
	  }
	case 'n':
	  {
	    return false;
	  }
	default:
	  {
	    std::cerr << "---------------------------------"<<std::endl;
	    std::cerr << "Nie rozpoznano opcji '"<<wybor<<"'"<<std::endl;
	    std::cerr << "Wprowadz 't' lub 'n'"<<std::endl;
	    std::cerr << "---------------------------------"<<std::endl;
	  }
	}
    }

  std::cout<<"Zapisywanie do pliku : '"<<nazwa_zapisu<<"' zakonczone powodzeniem."<<std::endl; 

  return true;
}
/******************************************************************************/

#endif
