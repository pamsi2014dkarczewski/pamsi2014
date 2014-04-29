#ifndef KOPIEC_HH
#define KOPIEC_HH

#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip> /* setw() */
#include <cmath> /* pierwiastek */
#include <sstream>
#include <string>

/********************************* FUNKCJE *********************************/
/* generowanie liczb / znakow pseudolosowych */
template <typename TYP>
void generowanie_liczb(TYP *tablica, int roz)
{
  int min, max;
  std::cout << "Podaj parametry do generowania liczb / znakow"<<std::endl<<std::endl;
  std::cout << "Jezeli program skompilowano dla typu char to zaleca sie "<<std::endl;
  std::cout << "podanie wartosci z przedzialu <33,126> zgodnie z kodem ASCII"<<std::endl;
  std::cout << "Zeby wygenerowac liczby z przedzialu <0,9> jako parametry "<<std::endl;
  std::cout << "nalezy podac wartosc minimalna 48 oraz wartosc maksymalna 57 (zgodnie z kodem ASCII)."<<std::endl;
  std::cout << "Wartosc minimalna: ";
  std::cin >> min;
  std::cout << std::endl;
  
  std::cout << "Wartosc maksymalna: ";
  std::cin >> max;
  std::cout << std::endl;
  
  std::cout << "Wygenerowane liczby / znaki: "<<std::endl;
  for (int i = 1; i<=roz; i++)
    {
      tablica[i]=(( min + rand() % (max-min + 1)));
      std::cout << tablica[i]<<" ";	    
    }
  std::cout << std::endl;
}

/* wyswietlenie kopca */
template <typename TYP>
void wyswietl_kopiec(TYP *tablica, int roz)
{
  /* dlugosc 160 jest odpowiednia dla kopca do 31 elementow, dla wiekszej ilosci
     elementow reprezentacja graficzna staje sie nieczytelna. (testowalem na 
     terminalu o dlugosci 80 znakow) */
  short int dlugosc_terminala = 160;

  /* pierwszy element jest nieuzywany i jest zerem */
  std::cout << "Kopiec w formie tablicy: "<<std::endl;
  for (int i = 1; i<=roz; i++)
    {
      std::cout<<tablica[i]<<" ";
    }
  std::cout<<std::endl;


  std::cout << "Kopiec w formie 'graficznej': "<<std::endl;

  /* poziom drzewa, indeks pierwszego elementu na danym poziomie */
  for (int i = 1; i<=roz; i=i*2)
    {
      dlugosc_terminala = dlugosc_terminala/2;;
      
      /* nowa linia rozpoczyna sie od odsuniecia w sumie 'dlugosc_terminala/4' */
      std::cout << std::setw(dlugosc_terminala/2)<<std::endl;

      /* petla wyswietla liczby z tablicy dla danego poziomu drzewa */
      for (int j = i; j<=((i*2)-1) && j<=roz; j++)
	{
	  /* wyswietlona zostaje liczba, a kolejna liczba zostanie odsunieta */
	  std::cout << tablica[j]<<std::setw(dlugosc_terminala);
	}
    }
  /* wyzerowanie przesuniecia */
  std::cout << std::endl<<std::setw(0);
}
/***************************************************************************/

/* generowanie liczy PI */
template <typename TYP>
void generowanie_pi(TYP *tablica, int roz)
{
  double pi;
  int j = 1;

  /* generowanie liczby PI */
  for( double i = 1; i<=10000000; i++)
    {
      if( j%2 == 0)
	{
	  pi -= 12/(i*i);
	}
      else
	{
	  pi += 12/(i*i);
	}
      j++;
    }
  std::cout <<"Wygenerowana liczba Pi: "<<std::setprecision(roz+1)<<sqrt(pi)<<std::endl;

  /* konwersja wygenerowanej liczby PI do typu string */
  std::stringstream str;
  str << std::fixed << std::setprecision(roz+1) << sqrt(pi);
  std::string s = str.str();
   
  /* wypelnienie tablicy kolejnymi cyframi liczby PI */
  for (int i = 1; i<=roz; i++)
    {
      tablica[i] = s[i-1];
    }
}
/******************************************************************************/

#endif
