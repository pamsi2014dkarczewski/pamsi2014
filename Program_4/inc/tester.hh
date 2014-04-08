#ifndef TESTER_HH
#define TESTER_HH

#include <chrono>

#define ILOSC_POWT_ALG 100 /* ile razy dana tablica ma byc sortowana */

/* definiowanie rozmiaru tablicy */
bool rozmiar_tablicy(unsigned int &rozmiar);


/******************************* WYBOR SORTOWANIA *****************************/
/* wybor jaka metoda dane beda sortowane */
template <typename TYP>
int wybor_sortowania(TYP *tablica, TYP *rozklad, int rozmiar)
{
  char opcja; /* zmienna wyboru opcji sortowania */
  double suma = 0; /* suma czasow sortowania */

  while (true)
    {
      std::cout << "1 - Sortowanie babelkowe"<<std::endl;
      std::cout << "2 - Sortowanie przez scalanie"<<std::endl;
      std::cout << "3 - Sortowanie introspektywne"<<std::endl;
      std::cout << "Twoj wybor (1-3): ";
      
      std::cin >> opcja;
      std::cin.clear(); /* wczytanie tylko pierwszego znaku */
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

      std::cout << std::endl;      

      switch(opcja)
	{
	case '1': /* sortowanie babelkowe */
	  {
	    std::cout << "Dane beda sortowane: "<<ILOSC_POWT_ALG<<" razy."<<std::endl;
	    std::cout << "Prosze czekac..."<<std::endl;
	    for(int i = 0; i<ILOSC_POWT_ALG; i++)
	      {
		przypisz_rozklad(tablica,rozklad,rozmiar);
		
		auto t1 = std::chrono::high_resolution_clock::now();
		
		sortowanie_babelkowe(tablica,rozmiar);

		/* pomiar czasu */
		auto t2 = std::chrono::high_resolution_clock::now();
		auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
		suma += roznica.count();
		
		/* sprawdzenie czy tablica rzeczywiscie jest posortowana */
		sprawdzenie_sortowania(tablica,rozmiar); 
	      }

	    std::cout << "Sredni czas wykonania sortowania: ";
	    std::cout <<(suma/ILOSC_POWT_ALG)<<" milisekund."<<std::endl;

	  }
	  return false;
	  
	case '2': /* sortowanie przez scalanie */
	  {
	    /* tablica pomocnicza dla sortowania przez scalanie */
	    TYP *temp;
	    temp = new TYP[rozmiar];

	    std::cout << "Dane beda sortowane: "<<ILOSC_POWT_ALG<<" razy."<<std::endl;
	    std::cout << "Prosze czekac..."<<std::endl;

	    for(int i = 0; i<ILOSC_POWT_ALG; i++)
	      {
		przypisz_rozklad(tablica,rozklad,rozmiar);
		
		auto t1 = std::chrono::high_resolution_clock::now();
		
		sortowanie_scalanie(tablica,temp,0,rozmiar-1);
		
		/* pomiar czasu */
		auto t2 = std::chrono::high_resolution_clock::now();
		auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
		suma += roznica.count();

		/* sprawdzenie czy tablica rzeczywiscie jest posortowana */
		sprawdzenie_sortowania(tablica,rozmiar);
	      }
	    delete [] temp;

	    std::cout << "Sredni czas wykonania sortowania: ";
	    std::cout <<(suma/ILOSC_POWT_ALG)<<" milisekund."<<std::endl;

	  }	 
	  return false;
	  
	case '3': /* sortowanie introspektywne */
	  {
	    std::cout << "Dane beda sortowane: "<<ILOSC_POWT_ALG<<" razy."<<std::endl;
	    std::cout << "Prosze czekac..."<<std::endl;

	    for(int i = 0; i<ILOSC_POWT_ALG; i++)
	      {
		przypisz_rozklad(tablica,rozklad,rozmiar);
		
		auto t1 = std::chrono::high_resolution_clock::now();

		sortowanie_introspektywne(tablica,rozmiar);

		/* pomiar czasu */
		auto t2 = std::chrono::high_resolution_clock::now();
		auto roznica = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);

		suma += roznica.count();

		/* sprawdzenie czy tablica rzeczywiscie jest posortowana */
		sprawdzenie_sortowania(tablica,rozmiar);
	      }

	    std::cout << "Sredni czas wykonania sortowania: ";
	    std::cout <<(suma/ILOSC_POWT_ALG)<<" milisekund."<<std::endl;

	  }	    
	  return false;
	  
	default:
	  {
	    std::cout << "---------------------------------"<<std::endl;
	    std::cout << "Nie rozpoznano opcji '"<<opcja<<"'"<<std::endl;
	    std::cout << "Wprowadz liczbe z zakresu 1-3."<<std::endl;
	    std::cout << "---------------------------------"<<std::endl;
	  }
	} /* end switch */
    } /* end while */
  return 1;
} /* end menu_wybor_sortowania */
/******************************************************************************/

#endif
