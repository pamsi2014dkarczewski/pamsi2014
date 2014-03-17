#ifndef LISTA_HH
#define LISTA_HH

/************************** KLASA ELEMENT_LISTY **************************/
/* Klasa zawiera wartosc elementu w liscie oraz wskaznik na element nastepny i poprzedni */

template <typename Typ>
class element_listy
{
public:
  Typ wartosc; /* wartosc elementu listy */
  element_listy *nastepny, *poprzedni; /* wskaznik na nastepny i poprzedni element listy */

  element_listy() 
  {
    nastepny = poprzedni = NULL;
  } 

  element_listy(const Typ& wart, element_listy *wsk = NULL, element_listy *wsk2 = NULL)  /* konstruktor */ 
  {
    wartosc = wart; /* do 'wartosc' przypisywana jest wartosc ktora zostanie dodana do listy */
    nastepny = wsk; /* ustawienie wskaznika na element nastepny */
    poprzedni = wsk2; /* ustawienie wskaznika na element poprzedni */
  } 

}; /* end class 'element_listy' */
/************************************************************************/



/**************************** KLASA STOS ********************************/
/* Klasa definiuje liste oraz operacje jakie mozna na niej wykonac */
/* Zawiera takze wskaznik na pierwszy element, ostatni element i przechowuje aktualny rozmiar stosu */

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
     Zwraca 'true' jeżeli stos jest pusty przeciwnym wypadku zwroci 'false' */
  bool stos_pusty()
  {
    if (poczatek != NULL) return false;
    return true;  
  }

  /* funkcja zwracajaca aktualna ilosc elementow na stosie */
  Typ size()
  {
    return rozmiar_stosu; 
  }

  void add_front(const Typ &dana); /* dodanie elementu na poczatek listy */
  void add_back(const Typ &dana); /* dodanie elementu na koniec listy */
  Typ delete_front(); /* usuniecie elementu z poczatku listy */
  Typ delete_back(); /* usuniecie elementu z konca listy */
  void wyswietl_liste(); /* wyswietlanie zawartosci listy */

  ~stos(); /* destruktor */ 

}; /* end class 'stos' */
/*************************************************************************/



/****************************** DODANIE NA POCZATEK **************************/
template <typename Typ>
void stos<Typ>::add_front(const Typ &dana)
{
  if(poczatek != NULL) /* jezeli lista nie jest pusta */
    {
      /* stworzenie nowego elementu i inicjalizacja jego pol 
	 pole 'wartosc' otrzymuje wartosc przekazana przez 'dana'
	 pole 'nastepny' otrzymuje wartosc zmiennej 'poczatek', tak ze pole to wskazuje na pierwszy element listy
	 pole 'poprzedni' otrzymuje wartosc NULL */
      poczatek = new element_listy<Typ>(dana,poczatek,NULL);

      /* pole 'poczatek' jest ustawiane tak aby wskazywalo na nowy element
	 pole 'poprzedni' elementu nastepnego jest ustawiane tak aby wskazywalo na nowy element (czyli wskazuje 'do tylu', nie jest to NULL) */
      poczatek->nastepny->poprzedni=poczatek;
    }
  else /* jezeli lista jest pusta */
    {
      koniec = poczatek = new element_listy<Typ>(dana); /* dodanie nowego elementu na poczatek */
    }
  rozmiar_stosu++; /* zwiekszenie zmiennej okreslajacej aktualny rozmiar stosu */
}
/*****************************************************************************/



/************************* DODANIE NA KONIEC LISTY ***************************/
template <typename Typ>
void stos<Typ>::add_back(const Typ &dana)
{
  if(koniec != NULL) /* gdy lista nie jest pusta */
    {
      /* stworzenie nowego elementu i inicjalizacja jego pol 
	 pole 'wartosc' otrzymuje wartosc przekazana przez 'dana'
	 pole 'nastepny' otrzymuje wartosc NULL
	 pole 'poprzedni' otrzymuje wartosc zmiennej 'koniec', tak ze pole to wskazuje na ostatni element listy */
      koniec = new element_listy<Typ>(dana,NULL,koniec); 

      /* pole 'koniec' jest ustawiane tak aby wskazywalo na nowy element
	 pole 'nastepny' poprzednika jest ustawiane tak aby wskazywalo na nowy element */     
      koniec->poprzedni->nastepny=koniec;
    }
  else /* gdy lista jest pusta */
    {
      poczatek = koniec = new element_listy<Typ>(dana);
    }
  rozmiar_stosu++;
}
/*****************************************************************************/



/*************************** USUNIECIE Z PRZODU LISTY ************************/
template <typename Typ>
Typ stos<Typ>::delete_front()
{
  /* utworzenie zmiennej 'element'
     'element' otrzymuje 'wartosc' elementu, nastepnie 'poczatek' jest ustawiany na element nastepny */
  Typ element = poczatek -> wartosc;
  if(koniec == poczatek) /* gdy na liscie jest tylko jeden element */
    {
      delete koniec; 
      koniec = poczatek = NULL; /* lista pusta, oba wskazuja na NULL */
    }
  else /* gdy na liscie jest wiecej niz jeden element */
    {
      /* 'poczatek' wskazuje na element nastepny,
	 dostaje sie do pola 'nastepny' w 'poczatek' i adres ten przypisuje do 'poczatek' */
      poczatek = poczatek -> nastepny;
      delete poczatek -> poprzedni; /* usuniecie z poczatku wskaznika do poprzedniego elementu */
      poczatek -> poprzedni = NULL; /* nie ma nic przed poczatkiem listy, dlatego pokazuje na NULL */
    }
  rozmiar_stosu--; /* zmniejszenie zmiennej, ktora okresla aktualny rozmiar stosu */
  return element; /* zwrocenie elementu */
}
/*****************************************************************************/



/*************************** USUNIECIE Z KONCA LISTY *************************/
template <typename Typ>
Typ stos<Typ>::delete_back()
{
  /* utworzenie zmiennej 'element'
     'element' otrzymuje 'wartosc' elementu, nastepnie 'koniec' jest ustawiane na element poprzedzajacy */
  Typ element = koniec -> wartosc;
  if(poczatek == koniec) /* gdy na liscie jest tylko jeden element */
    {
      delete poczatek;
      poczatek = koniec = NULL; /* lista pusta, oba wskazuja na NULL */
    }
  else /* gdy na liscie jest wiecej niz jeden element */
    {
      /* 'koniec' wskazuje na element poprzedni,
	 dostaje sie do pola 'poprzedni' w 'koniec' i adres ten przypisuje do 'koniec' */
      koniec = koniec -> poprzedni;
      delete koniec -> nastepny; /* usuniecie z konca wskaznika do nastepnego elementu */
      koniec -> nastepny = NULL; /* nie ma nic za lista, dlatego pokazuje na NULL */
    }

  rozmiar_stosu--; /* zmniejszenie zmiennej, ktora okresla aktualny rozmiar stosu */
  return element; /* zwrocenie elementu */
}
/*****************************************************************************/



/****************************** WYSWIETLANIE LISTY ***************************/
template <typename Typ>
void stos<Typ>::wyswietl_liste()
{
  int i = 1; /* licznik elementu */
  std::cout<<"Zawartosc listy: "<<std::endl;

  if(!stos_pusty()) /* jezeli lista nie jest pusta */
    {
      /* przejscie przez wszystkie elementy listy 
	 element_listy<Typ> *temp = poczatek | stworzenie tymczasowej zmiennej 'temp' ktora wskazuje na poczatek listy.
	 temp != NULL                        | (warunek) dopoki nie znajdzie konca listy
	 temp = temp -> nastepny             | do 'temp' przypisywany jest wskaznik do nastepnego elementu 
      */
      for(element_listy<Typ> *temp = poczatek; temp != NULL; temp = temp->nastepny)
	{    
	  std::cout<<" Element nr "<<i<<": "<<temp->wartosc<<std::endl;
	  i++;
	}
    }
  else /* lista jest pusta */
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
