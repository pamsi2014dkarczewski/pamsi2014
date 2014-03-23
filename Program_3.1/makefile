CPPFLAGS=-pedantic -Wall -Iinc
PROG=program3.1

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/stos.o 
	g++ -Wall -o ${PROG} obj/main.o obj/stos.o
	@echo	
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/stos.hh inc/typ.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 33%"
obj/stos.o: src/stos.cpp inc/stos.hh
	g++ -c ${CPPFLAGS} -o obj/stos.o src/stos.cpp
	@echo "Kompilowanie ... 66%"
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
	@echo "  string - wymuszenie zmiany typu danych na typ string oraz"
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
	@echo "  make string " 
	@echo

double: __utworz_typ_double__ clean __start__

float: __utworz_typ_float__ clean __start__

int: __utworz_typ_int__ clean __start__

char: __utworz_typ_char__ clean __start__

string: __utworz_typ_string__ clean __start__

__utworz_typ_double__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP double\n\
#define NAZWA_TYPU  \"double\"\n\
#endif\n\
" > inc/typ.hh

__utworz_typ_float__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP float\n\
#define NAZWA_TYPU  \"float\"\n\
#endif\n\
" > inc/typ.hh

__utworz_typ_int__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP int\n\
#define NAZWA_TYPU  \"int\"\n\
#endif\n\
" > inc/typ.hh

__utworz_typ_char__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP char\n\
#define NAZWA_TYPU  \"char\"\n\
#endif\n\
" > inc/typ.hh

__utworz_typ_string__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP string\n\
#define NAZWA_TYPU  \"string\"\n\
#endif\n\
" > inc/typ.hh