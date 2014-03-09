#ifndef FUNKCJE_HH
#define FUNKCJE_HH

#define ROZMIAR_TAB 10 // maksymalny rozmiar tablicy statycznej

/***********************************************************************/
/*                                                                     */
/* Plik zawiera deklaracje funkcji wykorzystanych w programie           */
/*                                                                     */
/***********************************************************************/

void wczytywanie (int *tablica);
void wyswietlanie (int *tablica);
bool wczytywanie_z_pliku (int *tablica);
bool zapisywanie_do_pliku (int *tablica);
bool wczytywanie_z_pliku_binarnego (int *tablica);
bool zapisywanie_do_pliku_binarnego (int *tablica);
void wypelnianie_liczbami_losowymi (int *tablica);
int *dynamiczna_kopia (int *tablica);
int wyswietlenie_kopii (int *tablica);


#endif
