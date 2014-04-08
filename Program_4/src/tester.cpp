#include <iostream>
#include <limits>

#include "tester.hh"

using namespace std;

/* rozmiar tablicy */
bool rozmiar_tablicy(unsigned int &rozmiar)
{
  while(true)
    {
      cout << "Witaj ! Ile elementow ma miec tablica ?"<<endl;
      cin >> rozmiar;
      if(cin.fail()) 
	{
	  cerr << "Blad podczas wprowadzania rozmiaru tablicy. "<<endl;
	  cin.clear();
	  cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
      else
	{
	  return false;
	}
    }
  return true;
}
