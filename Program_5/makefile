CPPFLAGS=-pedantic -Wall -Iinc -O2 -std=c++0x
PROG=program5

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/macierz.o obj/lista.o obj/plik.o
	g++ -Wall -o ${PROG} obj/main.o obj/macierz.o obj/lista.o obj/plik.o
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/macierz.hh inc/lista.hh inc/plik.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 20%" 
obj/macierz.o: src/macierz.cpp inc/macierz.hh
	g++ -c ${CPPFLAGS} -o obj/macierz.o src/macierz.cpp
	@echo "Kompilowanie ... 40%" 
obj/lista.o: src/lista.cpp inc/lista.hh
	g++ -c ${CPPFLAGS} -o obj/lista.o src/lista.cpp
	@echo "Kompilowanie ... 60%"
obj/plik.o: src/plik.cpp inc/plik.hh
	g++ -c ${CPPFLAGS} -o obj/plik.o src/plik.cpp
	@echo "Kompilowanie ... 80%" 
obj:
	mkdir obj
clean:
	rm -f ${PROG} obj/*
help:
	@echo
	@echo " Lista opcji dla polecenia make: "
	@echo 
	@echo "  obj    - tworzy katalog 'obj' dla plikow .o "
	@echo "  clean  - usuwa produkty kompilacji oraz program"
	@echo "  help   - wyswietla niniejszy komunikat"
	@echo "  int    - wymuszenie zmiany typu danych na typ int oraz"
	@echo "           kompilacja, konsolidacja i uruchomienie programu."
	@echo "  float  - wymuszenie zmiany typu danych na typ float oraz"
	@echo "           kompilacja, konsolidacja i uruchomienie programu"
	@echo "  double - wymuszenie zmiany typu danych na typ double oraz"
	@echo "           kompilacja, konsolidacja i uruchomienie programu."
	@echo
help2:	
	@echo 
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja, konsolidacja i uruchomienie"
	@echo "                   programu z aktualnym typem danych."
	@echo "  make obj       # tworzy katalog 'obj' "
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo "  make help      # wyswietla niniejszy komunikat"
	@echo
	@echo "  Typy wywolan programu:"
	@echo "  make int "     
	@echo "  make float " 
	@echo "  make double "  
	@echo

double: __utworz_typ_double__ clean __start__

float: __utworz_typ_float__ clean __start__

int: __utworz_typ_int__ clean __start__

__utworz_typ_double__:
	@echo \
"\r\n\
#ifndef TYP_HH\r\n\
#define TYP_HH\r\n\
#define TYP double\r\n\
#define NAZWA_TYPU  \"double\"\r\n\
#endif\r\n\
" > inc/typ.hh

__utworz_typ_float__:
	@echo \
"\r\n\
#ifndef TYP_HH\r\n\
#define TYP_HH\r\n\
#define TYP float\r\n\
#define NAZWA_TYPU  \"float\"\r\n\
#endif\r\n\
" > inc/typ.hh

__utworz_typ_int__:
	@echo \
"\r\n\
#ifndef TYP_HH\r\n\
#define TYP_HH\r\n\
#define TYP int\r\n\
#define NAZWA_TYPU  \"int\"\r\n\
#endif\r\n\
" > inc/typ.hh
