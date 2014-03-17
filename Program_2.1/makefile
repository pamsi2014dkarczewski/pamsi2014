CPPFLAGS=-pedantic -Wall -Iinc
PROG=program2.1

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/lista.o
	g++ -Wall -o ${PROG} obj/main.o obj/lista.o
	@echo	
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: inc/lista.hh src/main.cpp
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 50%"
obj/lista.o: src/lista.cpp inc/lista.hh
	g++ -c ${CPPFLAGS} -o obj/lista.o src/lista.cpp
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
	@echo