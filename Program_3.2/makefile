CPPFLAGS=-pedantic -Wall -Iinc
PROG=program3.2

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/kopiec.o 
	g++ -Wall -o ${PROG} obj/main.o obj/kopiec.o
	@echo	
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/kopiec.hh inc/typ.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 33%"
obj/kopiec.o: src/kopiec.cpp inc/kopiec.hh
	g++ -c ${CPPFLAGS} -o obj/kopiec.o src/kopiec.cpp
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
	@echo "  help2  - wyswietla druga czesc pomocy"
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
	@echo "  make help2     # wyswietla niniejszy komunikat"
	@echo
	@echo "  Typy wywolan programu:"
	@echo "  make char "     
	@echo

char: __utworz_typ_char__ clean __start__

__utworz_typ_char__:
	@echo \
"\n\
#ifndef TYP_HH\n\
#define TYP_HH\n\
#define TYP char\n\
#define NAZWA_TYPU  \"char\"\n\
#endif\n\
" > inc/typ.hh