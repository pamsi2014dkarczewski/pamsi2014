#ifndef LISTA_HH
#define LISTA_HH

/************************** KLASA ELEMENT_LISTY **************************/
/* Klasa zawiera wartosc elementu w liscie oraz wskaznik na element nastepny */

template <typename Typ>
class element_listy
{
public:
  Typ wartosc; /* wartosc elementu listy */
  element_listy *nastepny; /* wskaznik na nastepny element listy */
 
  element_listy(Typ wart, element_listy *wsk = NULL)  /* konstruktor */ 
  {
    wartosc = wart; /* do 'wartosc' przypisywana jest wartosc ktora 
		       zostanie dodana na stos */
    nastepny = wsk; /* ustawienie wskaznika na element nastepny*/
  } 

}; /* end class 'element_listy' */
/************************************************************************/



/**************************** KLASA STOS ********************************/
/* Klasa definiuje liste/stos oraz operacje jakie mozna na niej wykonac */
/* Zawiera takze wskaznik na pierwszy element, ostatni element i przechowuje 
   aktualny rozmiar stosu */

template <typename Typ>
class stos
{
private:
  element_listy<Typ> *poczatek; /* wskaznik na pierwszy element listy */
  element_listy<Typ> *koniec; /* wskaznik na ostatni element listy */
  int rozmiar_stosu; /* przechowuje rozmiar stosu */

public:
  stos() /* konstruktor */
  {
    poczatek = koniec = NULL; /* poczatek i koniec wskazuja na NULL */
    rozmiar_stosu = 0; /* stworzony stos nie ma rozmiaru */
  }

  /* Funkcja sprawdzajaca czy stos jest pusty.
     Zwraca 'true' jesli stos jest pusty przeciwnym wypadku zwroci 'false' */
  bool stos_pusty()
  {
    if (poczatek != NULL) return false;
    return true;  
  }

  /* funkcja zwracajaca aktualna ilosc elementow na stosie */
  int wielkosc_stosu()
  {
    return rozmiar_stosu; 
  }

  void dodaj_na_poczatek(Typ dana); /* dodanie elementu na poczatek listy */
  Typ * usun_z_poczatku(); /* usuniecie elementu z poczatku listy i zwrocenie 
			      zapisanej wartosci */
  void wyswietl_liste(); /* wyswietlanie zawartosci listy */

  ~stos(); /* destruktor */ 

}; /* end class 'stos' */
/*************************************************************************/



/****************************** DODANIE NA POCZATEK **************************/
template <typename Typ>
void stos<Typ>::dodaj_na_poczatek(Typ dana)
{
  /* stworzenie nowego elementu na poczatku listy z wartoscia 'dana' ktory 
     bedzie pokazywal na nastepny element */
  poczatek = new element_listy<Typ>(dana,poczatek);  
  if(koniec==NULL) koniec = poczatek; 
  rozmiar_stosu++; /* zwiekszenie zmiennej okreslajacej aktualny rozmiar stosu */
}
/*****************************************************************************/



/*************************** USUNIECIE Z PRZODU LISTY ************************/
template <typename Typ>
Typ *stos<Typ>::usun_z_poczatku()
{
  if(!stos_pusty()) /* jezeli stos nie jest pusty */
    {
      Typ *element = new Typ(poczatek -> wartosc); 
      element_listy<Typ> *temp = poczatek; /* pomocniczy wskaznik wskazujacy 
      					      na poczatek listy */
      if(poczatek == koniec) /* jezeli lista zawiera jeden element */
	{
	  poczatek = koniec = NULL; /* ustawienie wskaznikow na NULL */
	}      
      else /* jezeli lista zawiera kilka elementow */
	{
	  /* 'poczatek' wskazuje na element nastepny */
	  /*  dostaje sie do pola 'nastepny' w 'poczatek' i adres ten 
	      przypisuje do 'poczatek' */
	  poczatek = poczatek -> nastepny; 
	}      
      delete temp;  /* usuniecie pomocniczego wskaznika */
      rozmiar_stosu--; /* pomniejszenie rozmiaru stosu, poniewaz 
			  element zostal usuniety */
      return element;
    }
  else /* jezeli stos jest pusty */
    {
      std::cout << "Lista jest pusta ! Nie ma nic do usuniecia."<<std::endl;
      return NULL;
    }
}
/*****************************************************************************/


/****************************** WYSWIETLANIE LISTY ***************************/
template <typename Typ>
void stos<Typ>::wyswietl_liste()
{
  int i = 1; /* licznik elementu */
  std::cout << "Zawartosc listy: "<<std::endl;

  if(!stos_pusty()) /* jezeli stos nie jest pusty */
    {
      /* przejscie przez wszystkie elementy listy,  
	 stworzenie tymczasowej zmiennej 'temp' ktora wskazuje na 
	 poczatek listy:  element_listy<Typ> *temp = poczatek

	 (warunek) dopoki nie napotkam konca listy: temp != NULL

	 do 'temp' przypisywany jest wskaznik do 
	 nastepnego elementu: temp = temp -> nastepny         
      */
      for(element_listy<Typ> *temp = poczatek; temp != NULL; temp = temp -> nastepny)
	{    
	  /* wyswietlenie zawartosci */
	  std::cout<<" Element nr"<<i<<": "<<temp->wartosc<<std::endl;
	  i++;
	}
    }
  else /* jezeli stos jest pusty */
    {
      std::cout<<"Lista jest pusta !"<<std::endl;
    }
}
/****************************************************************************/


/******************************* DESTRUKTOR *********************************/
template <typename Typ>
stos<Typ>::~stos()
{
  /* usuniecie listy */
  /* dopoki stos nie jest pusty */
  for (element_listy<Typ> *element; !stos_pusty();)
    {
      /* do 'element' przypisywany jest adres elementu nastepnego 
	 dostaje sie do pola 'nastepny' w 'poczatek' go przypisuje do 'element' */
      element = poczatek -> nastepny;
      /* usuniecie elementu poczatkowego */
      delete poczatek;
      /* poczatek wskazuje teraz na pierwszy element ktory pozostal */
      poczatek = element;
    }
}
/****************************************************************************/

#endif
