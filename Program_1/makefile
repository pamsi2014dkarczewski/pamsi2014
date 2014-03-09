CPPFLAGS=-pedantic -Wall -Iinc
PROG=zajecia2.1

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/funkcje.o 
	g++ -Wall -o ${PROG} obj/main.o obj/funkcje.o
	@echo	
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/funkcje.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 33%"
obj/funkcje.o: src/funkcje.cpp inc/funkcje.hh
	g++ -c ${CPPFLAGS} -o obj/funkcje.o src/funkcje.cpp
	@echo "Kompilowanie ... 66%"
obj:
	mkdir obj
clean:
	rm -f core* ${PROG} obj/*
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
	@echo
