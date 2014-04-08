#include <iostream>
#include <limits>

#include "tester.hh"
#include "eksperyment.hh"

/************************** UPORZADKOWANIE ELEMENTOW **************************/
/* wybor ile elementow w tablicy ma byc posortowane */
int uporzadkowanie_elementow(int rozmiar)
{
  char opcja;

  while(true)
    {
      int uporzadkowane; /* ilosc elementow ktore maja byc uporzadkowane */
      std::cout << "1 - Sortowanie nieuporzadkowanej tablicy "<<std::endl;
      std::cout << "2 - Sortowanie tablicy z 10% uporzadkowanymi elementami"<<std::endl;
      std::cout << "3 - Sortowanie tablicy z 50% uporzadkowanymi elementami"<<std::endl;
      std::cout << "4 - Sortowanie tablicy z 90% uporzadkowanymi elementami"<<std::endl;
      std::cout << "5 - Sortowanie tablicy z 99% uporzadkowanymi elementami"<<std::endl;
      std::cout << "Twoj wybor (1-5): ";
      
      std::cin >> opcja;
      std::cin.clear(); /* wczytanie tylko pierwszego znaku */
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

      switch(opcja)
	{
	case '1':
	  return 0;
	  
	case '2':
	  {
	    uporzadkowane = 0.1 * rozmiar;
	  }
	  return uporzadkowane;
	  
	case '3':
	  {
	    uporzadkowane = 0.5 * rozmiar;
	  }
	  return uporzadkowane;

	case '4':
	  {
	    uporzadkowane = 0.9 * rozmiar;
	  }
	  return uporzadkowane;
	  
	case '5':
	  {
	    uporzadkowane = 0.99 * rozmiar;
	  }
	  return uporzadkowane;

	default:
	  {
	    std::cout << "---------------------------------"<<std::endl;
	    std::cout << "Nie rozpoznano opcji '"<<opcja<<"'"<<std::endl;
	    std::cout << "Wprowadz liczbe z zakresu 1-5."<<std::endl;
	    std::cout << "---------------------------------"<<std::endl;
	  }
	} /* end switch */

    } /* end while */

  return 0;
}
/******************************************************************************/
