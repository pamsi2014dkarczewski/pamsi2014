#ifndef LISTA_HH
#define LISTA_HH

/************************** KLASA ELEMENT_LISTY **************************/
/* Klasa zawiera wartosc elementu w liscie oraz wskaznik na element 
   nastepny i poprzedni */

template <typename Typ>
class element_listy
{
public:
  Typ wartosc; /* wartosc elementu listy */

  /* wskaznik na nastepny i poprzedni element listy */
  element_listy *nastepny, *poprzedni; 

  element_listy() 
  {
    nastepny = poprzedni = NULL;
  } 

  /* konstruktor */
  element_listy(const Typ& wart, element_listy *wsk = NULL, element_listy *wsk2 = NULL) 
  {
    /* do 'wartosc' przypisywana jest wartosc ktora zostanie dodana do listy */
    wartosc = wart; 
    nastepny = wsk; /* ustawienie wskaznika na element nastepny */
    poprzedni = wsk2; /* ustawienie wskaznika na element poprzedni */
  } 

}; /* end class 'element_listy' */
/************************************************************************/



/**************************** KLASA STOS ********************************/
/* Klasa definiuje liste oraz operacje jakie mozna na niej wykonac */
/* Zawiera takze wskaznik na pierwszy element, ostatni element i przechowuje
   aktualny rozmiar listy */

template <typename Typ>
class lista
{
private:
  element_listy<Typ> *poczatek; /* wskaznik na pierwszy element listy */
  element_listy<Typ> *koniec; /* wskaznik na ostatni element listy */
  int rozmiar_listy; /* przechowuje rozmiar listy */

public:
  lista() /* konstruktor */
  {
    poczatek = koniec = NULL; /* poczatek i koniec wskazuja na NULL */
    rozmiar_listy = 0; /* stworzona lista na poczatku nie ma rozmiaru */
  }

  /* Funkcja sprawdzajaca czy lista jest pusta.
     Zwraca 'true' jeżeli lista jest pusty przeciwnym wypadku zwroci 'false' */
  bool lista_pusta()
  {
    if (poczatek != NULL) return false;
    return true;  
  }

  /* funkcja zwracajaca aktualna ilosc elementow w liscie */
  int wielkosc_listy()
  {
    return rozmiar_listy; 
  }

  void dodaj_na_poczatek(const Typ &dana);/*dodanie elementu na poczatek listy*/
  void dodaj_na_koniec(const Typ &dana); /* dodanie elementu na koniec listy */
  Typ usun_z_poczatku(); /* usuniecie elementu z poczatku listy */
  Typ usun_z_konca(); /* usuniecie elementu z konca listy */
  void wyswietl_liste(); /* wyswietlanie zawartosci listy */

  ~lista(); /* destruktor */ 

}; /* end class 'lista' */
/*****************************************************************************/



/****************************** DODANIE NA POCZATEK **************************/
template <typename Typ>
void lista<Typ>::dodaj_na_poczatek(const Typ &dana)
{
  if(poczatek != NULL) /* jezeli lista nie jest pusta */
    {
      /* stworzenie nowego elementu i inicjalizacja jego pol 
	 pole 'wartosc' otrzymuje wartosc przekazana przez 'dana'

	 pole 'nastepny' otrzymuje wartosc zmiennej 'poczatek', tak ze pole to 
	 wskazuje na pierwszy element listy

	 pole 'poprzedni' otrzymuje wartosc NULL */
      poczatek = new element_listy<Typ>(dana,poczatek,NULL);

      /* pole 'poczatek' jest ustawiane tak aby wskazywalo na nowy element

	 pole 'poprzedni' elementu nastepnego jest ustawiane tak aby wskazywalo 
	 na nowy element (czyli wskazuje 'do tylu', ale nie jest to NULL) */
      poczatek->nastepny->poprzedni=poczatek;
    }
  else /* jezeli lista jest pusta */
    {
      /* dodanie nowego elementu na poczatek */
      koniec = poczatek = new element_listy<Typ>(dana); 
    }

  /* zwiekszenie zmiennej okreslajacej aktualny rozmiar listy */
  rozmiar_listy++; 
}
/*****************************************************************************/



/************************* DODANIE NA KONIEC LISTY ***************************/
template <typename Typ>
void lista<Typ>::dodaj_na_koniec(const Typ &dana)
{
  if(koniec != NULL) /* gdy lista nie jest pusta */
    {
      /* stworzenie nowego elementu i inicjalizacja jego pol 
	 pole 'wartosc' otrzymuje wartosc przekazana przez 'dana'

	 pole 'nastepny' otrzymuje wartosc NULL

	 pole 'poprzedni' otrzymuje wartosc zmiennej 'koniec', tak ze pole to 
	 wskazuje na ostatni element listy */
      koniec = new element_listy<Typ>(dana,NULL,koniec); 

      /* pole 'koniec' jest ustawiane tak aby wskazywalo na nowy element

	 pole 'nastepny' poprzednika jest ustawiane tak aby wskazywalo na 
	 nowy element */     
      koniec->poprzedni->nastepny=koniec;
    }
  else /* gdy lista jest pusta */
    {
      poczatek = koniec = new element_listy<Typ>(dana);
    }

  /* zwiekszenie zmiennej okreslajacej aktualny rozmiar stosu */
  rozmiar_listy++; 
}
/*****************************************************************************/



/*************************** USUNIECIE Z PRZODU LISTY ************************/
template <typename Typ>
Typ lista<Typ>::usun_z_poczatku()
{
  /* utworzenie zmiennej 'element'
     'element' otrzymuje 'wartosc' elementu, nastepnie 'poczatek' jest 
     ustawiany na element nastepny */
  Typ element = poczatek -> wartosc;
  if(koniec == poczatek) /* gdy na liscie jest tylko jeden element */
    {
      delete koniec; 
      koniec = poczatek = NULL; /* lista pusta, oba wskazuja na NULL */
    }
  else /* gdy na liscie jest wiecej niz jeden element */
    {
      /* 'poczatek' wskazuje na element nastepny,
	 dostaje sie do pola 'nastepny' w 'poczatek' i adres ten 
	 przypisuje do 'poczatek' */
      poczatek = poczatek -> nastepny;

      /* usuniecie z poczatku wskaznika do poprzedniego elementu */
      delete poczatek -> poprzedni; 

      /* nie ma nic przed poczatkiem listy, dlatego pokazuje na NULL */      
      poczatek -> poprzedni = NULL; 
    }

  /* zmniejszenie zmiennej, ktora okresla aktualny rozmiar listy */
  rozmiar_listy--; 

  return element; /* zwrocenie elementu */
}
/*****************************************************************************/



/*************************** USUNIECIE Z KONCA LISTY *************************/
template <typename Typ>
Typ lista<Typ>::usun_z_konca()
{
  /* utworzenie zmiennej 'element'
     'element' otrzymuje 'wartosc' elementu, nastepnie 'koniec' ustawiane jest 
     na element poprzedzajacy */
  Typ element = koniec -> wartosc;

  if(poczatek == koniec) /* gdy na liscie jest tylko jeden element */
    {
      delete poczatek;
      poczatek = koniec = NULL; /* lista pusta, oba wskazuja na NULL */
    }
  else /* gdy na liscie jest wiecej niz jeden element */
    {
      /* 'koniec' wskazuje na element poprzedni,
	 dostaje sie do pola 'poprzedni' w 'koniec' i adres ten 
	 przypisuje do 'koniec' */
      koniec = koniec -> poprzedni;

      /* usuniecie z konca wskaznika do nastepnego elementu */
      delete koniec -> nastepny; 

      /* za lista nic nie ma, dlatego pokazuje na NULL */
      koniec -> nastepny = NULL; 
    }

  /* zmniejszenie zmiennej, ktora okresla aktualny rozmiar listy */
  rozmiar_listy--; 

  return element; /* zwrocenie elementu */
}
/*****************************************************************************/



/****************************** WYSWIETLANIE LISTY ***************************/
template <typename Typ>
void lista<Typ>::wyswietl_liste()
{
  int i = 1; /* licznik elementu */
  std::cout<<"Zawartosc listy: "<<std::endl;

  if(!lista_pusta()) /* jezeli lista nie jest pusta */
    {
      /* przejscie przez wszystkie elementy listy 
	 stworzenie tymczasowej zmiennej 'temp' ktora wskazuje na 
	 poczatek listy: element_listy<Typ> *temp = poczatek 

	 (warunek) dopoki nie znajdzie konca listy: temp != NULL

	 do 'temp' przypisywany jest wskaznik do 
	 nastepnego elementu: temp = temp -> nastepny  
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
lista<Typ>::~lista()
{
  /* usuniecie listy */
  /* dopoki stos nie jest pusty */
  for (element_listy<Typ> *element; !lista_pusta();)
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
