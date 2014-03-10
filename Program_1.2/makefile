CPPFLAGS=-pedantic -Wall -Iinc
PROG=zajecia2.2

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/funkcje.o 
	g++ -Wall -o ${PROG} obj/main.o obj/funkcje.o
	@echo	
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/funkcje.hh inc/typ.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 33%"
obj/funkcje.o: src/funkcje.cpp inc/funkcje.hh
	g++ -c ${CPPFLAGS} -o obj/funkcje.o src/funkcje.cpp
	@echo "Kompilowanie ... 66%"
obj:
	mkdir obj
clean:
	rm -f ${PROG} obj/*
help:
	@echo
	@echo " Lista opcji dla polecenia make: "
	@echo 
	@echo "  obj   - tworzy katalog 'obj' dla plikow .o "
	@echo "  clean - usuwa produkty kompilacji oraz program"
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo 
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make obj       # tworzy katalog 'obj' "
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo "  make help      # wyswietla niniejszy komunikat"
	@echo "  make int       # kompilacja i uruchomienie dla typu int"
	@echo "  make double    # kompilacja i uruchomienie dla typu double"
	@echo "  make float     # kompilacja i uruchomienie dla typu float"
	@echo

double: __utworz_typ_double__ clean __start__

float: __utworz_typ_float__ clean __start__

int: __utworz_typ_int__ clean __start__

__utworz_typ_double__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP double\n\
#define NAZWA_TYPU  \"double\"\n\
#endif\n\
" > inc/typ.hh
	cp dane/dane_double.dat dane.dat

__utworz_typ_float__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP float\n\
#define NAZWA_TYPU  \"float\"\n\
#endif\n\
" > inc/typ.hh
	cp dane/dane_float.dat dane.dat

__utworz_typ_int__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP int\n\
#define NAZWA_TYPU  \"int\"\n\
#endif\n\
" > inc/typ.hh
	cp dane/dane_int.dat dane.dat