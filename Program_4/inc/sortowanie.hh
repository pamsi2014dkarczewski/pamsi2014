#ifndef SORTOWANIE_HH
#define SORTOWANIE_HH

#include <random>

/************************* SORTOWANIE BABELKOWE *******************************/
template <typename TYP>
inline void sortowanie_babelkowe(TYP *tablica, int rozmiar)
{
  TYP temp; /* zmienna pomocnicza, do zamiany elementow miejscami */
  bool zamieniono; /* flaga informujaca czy zamieniono elementy ze soba */
  do 
    {
      zamieniono = false; /* zerowanie flagi */
      --rozmiar; /* zmniejszenie rozmiaru, aby nie przekroczyc tablicy */
      for(int i = 0; i<rozmiar; i++)	
	{
	  /* jezeli elementy nie sa w porzadku rosnacym */
	  if(tablica[i]>tablica[i+1])
	    { /* zamiana elementow miejscami */
	      temp = tablica[i];
	      tablica[i]=tablica[i+1];
	      tablica[i+1]=temp;
	      /* ustawienie flagi informujacej o dokonanej zamianie */
	      zamieniono = true; 
	      }
	}
    }while(zamieniono); /* dopoki nie zostanie wykonana zadana zamiana */
}
/******************************************************************************/


/************************* SORTOWANIE SCALANIE ********************************/
template <typename TYP>
void sortowanie_scalanie(TYP *tablica, TYP *temp, int pierwszy, int ostatni)
{
  /* jeden element jest elementem posortowanym */
  if(ostatni <= pierwszy) return;

  /* srodek tablicy */
  int srodek = (pierwszy+ostatni)/2;

  /* dzielenie tablicy na dwie (prawa i lewa) */
  sortowanie_scalanie(tablica, temp, pierwszy, srodek); 
  sortowanie_scalanie(tablica, temp, srodek+1, ostatni);

  /* scalanie tablicy */
  scal_tablice(tablica, temp, pierwszy, srodek, ostatni);
}


/* scalanie tablicy */
template <typename TYP>
void scal_tablice(TYP *tablica, TYP *temp, int lewa, int srodek, int prawa)
{
  int i,j;  
  /* zapisuje lewa czesc tablicy w tablicy pomocniczej */
  for(i = srodek + 1; i>lewa; i--) 
    {
      temp[i-1] = tablica[i-1]; 
    }

  /* zapisuje prawa czesc tablicy w tablicy pomocniczej */
  for(j = srodek; j<prawa; j++) 
    {
      temp[prawa+srodek-j] = tablica[j+1]; 
    }

  /* scalanie dwoch tablic pomocniczych i zapisanie ich we wlasciwej tablicy */
  for(int k = lewa; k<=prawa; k++) 
    {
       if(temp[j]<temp[i])
	tablica[k] = temp[j--];
      else
      tablica[k] = temp[i++];
    }
}
/******************************************************************************/


/************************* SORTOWANIE INTROSPEKTYWNE **************************/
/* sortowanie introspektywne sklada sie z trzech sortowan:
   sortowanie szybkie --> do glebokosci M
   sortowanie przez kopcowanie --> sortowanie pozostalej czesci
   sortowanie przez wstawianie --> zlaczenie tablic w jednosc */
template <typename TYP>
void sortowanie_introspektywne(TYP *tablica, int rozmiar)
{
  /* int floor zaokraglenie w dol, M_LN2 - stala, logarytm naturalny z 2 */
  sortuj(tablica,rozmiar,(int)floor(2*log(rozmiar)/M_LN2));
  sortowanie_wstawianie(tablica,rozmiar);
}
/******************************************************************************/


/********************************* sortowanie *********************************/
template <typename TYP>
void sortuj (TYP *tablica, int rozmiar, int M)
{
  /* M oznacza stala glebokosci wywolan rekurencyjnych, jezeli jest mniejsza
     lub rowna zero to wykonywane jest sortowanie przez kopcowanie (pomocnicze) */
  if (M<=0)
  {
    sortowanie_kopcowanie(tablica,rozmiar);
    return;
  }

  int i = podzial(tablica,0,rozmiar);
  
  if (i>50)
    sortuj(tablica,i,M-1);
  if (rozmiar-1-i>50)
    sortuj(tablica+i+1,rozmiar-1-i,M-1);
}
/******************************************************************************/



/********************************* podzial ************************************/
template <typename TYP>
int podzial (TYP *tablica, int pierwszy, int ostatni)
{
  int piwot = tablica[(rand() % ostatni)]; /* losowe wybranie piwotu */
  
  int i = pierwszy-1;
  
  for(int j = pierwszy; j<ostatni; j++)
    {
      if(tablica[j]<=piwot)
	{
	  i++;
	  zamien(tablica,i,j);
	}
    }
  return i;
}
/******************************************************************************/
 

/****************************** zamiana ***************************************/
/* funkcja zamienia kolejnoscia dwa elementy w tablicy */
template <typename TYP>
inline void zamien (TYP *tablica, int i, int j)
{
  TYP temp;
  temp=tablica[i];
  tablica[i]=tablica[j];
  tablica[j]=temp;
}
/******************************************************************************/

/*********************** sortowanie przez kopcowanie **************************/
template <typename TYP>
void sortowanie_kopcowanie (TYP *tablica, int rozmiar)
{
  int i;
  for (i = (rozmiar/2) - 1; i >= 0; --i)
    {
    /* przywrocenie wlasnosci kopca / stworzenie kopca */
    przesun_w_dol(tablica,i,rozmiar-1);  
    }
  for (i = rozmiar-1; i >= 1; --i)
    {
      /* zamiana elementu na gorze kopca (najwieksza wartosc) z elementem 
	 na spodzie kopca */
      zamien(tablica,0,i);
      /* przywrocenie wlasnosci kopca / stworzenie kopca 
	 po zamianie ostatni element jest juz posortowany (wartosc najwieksza)
	 dlatego kopiec zostaje stworzony z tablicy mniejszej o jeden element */
      przesun_w_dol(tablica,0,i-1);  
    }
}
/******************************************************************************/


/********************************** stworzenie kopca **************************/
/* tworzy kopiec, ktory zawiera wszystkie elementy tablicy z wyjatkiem ostatniego */
template <typename TYP>
void przesun_w_dol (TYP *tablica, int pierwszy, int ostatni)
{
  int najwiekszy = (2*pierwszy)+1;
  while (najwiekszy <= ostatni)
    {
      /* element pierwszy ma dwoje dzieci oraz element po lewej jest mniejszy
	 od elementu po prawej */
      if (najwiekszy < ostatni && tablica[najwiekszy] < tablica[najwiekszy+1])
	{
	  najwiekszy++;
	}

      /* jezeli zaburza porzadek to zostaje zamienione dziecko z rodzicem 
	 i przesuwane jest w dol */
      if (tablica[pierwszy] < tablica[najwiekszy])
	{
	  zamien(tablica,pierwszy,najwiekszy);
	  pierwszy = najwiekszy;
	  najwiekszy = (2*pierwszy)+1;
	}

      /* wyjscie z petli, tablica[pierwszy] nie zaburza kopca */
      else
	{
	  najwiekszy = ostatni+1;
	}
    }
}
/******************************************************************************/



/********************** sortowanie przez wstawianie ***************************/
template <typename TYP>
void sortowanie_wstawianie (TYP *tablica, int rozmiar)
{
  TYP temp;
  int j;
  
  /* sortowanie rozpoczyna sie od drugiego elementu tablicy (indeks 1), 
     dla kazdego elementu wykonywane jest przypisanie temp = tablica[i],
     wszystkie elementy wieksze od temp sa kopiowane do kolejnej komorki tablicy
     wartosc przechowywana w zmiennej temp jest zapisywana w odpowiednim miejscu
  */
  for (int i = 1; i<rozmiar; i++)
    {
      temp = tablica[i];
      for (j = i; j>0 && temp < tablica[j-1]; j--)
	{
	  tablica[j] = tablica[j-1];
	}
      tablica[j] = temp;
    }
}
/******************************************************************************/

#endif
