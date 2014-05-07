CPPFLAGS=-pedantic -Wall -Iinc -O2 -std=c++0x
PROG=program4

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/sortowanie.o obj/tester.o obj/eksperyment.o
	g++ -Wall -o ${PROG} obj/main.o obj/sortowanie.o obj/tester.o obj/eksperyment.o
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/sortowanie.hh inc/tester.hh inc/eksperyment.hh inc/typ.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 20%"
obj/sortowanie.o: src/sortowanie.cpp inc/sortowanie.hh
	g++ -c ${CPPFLAGS} -o obj/sortowanie.o src/sortowanie.cpp
	@echo "Kompilowanie ... 40%"
obj/tester.o: src/tester.cpp inc/tester.hh
	g++ -c ${CPPFLAGS} -o obj/tester.o src/tester.cpp
	@echo "Kompilowanie ... 60%" 
obj/eksperyment.o: src/eksperyment.cpp inc/eksperyment.hh
	g++ -c ${CPPFLAGS} -o obj/eksperyment.o src/eksperyment.cpp
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
	@echo "  char   - wymuszenie zmiany typu danych na typ char oraz"
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
	@echo "  make char " 
	@echo

double: __utworz_typ_double__ clean __start__

float: __utworz_typ_float__ clean __start__

int: __utworz_typ_int__ clean __start__

char: __utworz_typ_char__ clean __start__

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

__utworz_typ_char__:
	@echo \
"\r\n\
#ifndef TYP_HH\r\n\
#define TYP_HH\r\n\
#define TYP char\r\n\
#define NAZWA_TYPU  \"char\"\r\n\
#endif\r\n\
" > inc/typ.hh