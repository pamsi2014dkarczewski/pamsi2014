CPPFLAGS=-pedantic -Wall -Iinc -O2 -std=c++0x
PROG=gra

__start__: obj ${PROG}
	./${PROG}

${PROG}: obj/main.o obj/Interface.o obj/Game.o
	g++ -Wall -o ${PROG} obj/main.o obj/Interface.o obj/Game.o
	@echo "Kompilowanie ... 100%" 
	@echo
obj/main.o: src/main.cpp inc/Game.hh inc/Interface.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp
	@echo "Kompilowanie ... 25%" 
obj/Interface.o: src/Interface.cpp inc/Interface.hh
	g++ -c ${CPPFLAGS} -o obj/Interface.o src/Interface.cpp
	@echo "Kompilowanie ... 50%" 
obj/Game.o: src/Game.cpp inc/Game.hh
	g++ -c ${CPPFLAGS} -o obj/Game.o src/Game.cpp
	@echo "Kompilowanie ... 75%" 
obj:
	mkdir obj
clean:
	rm -f ${PROG} obj/*
help:
	@echo
	@echo " Lista opcji dla polecenia make: "
	@echo 
	@echo "  make   - kompilacja i konsolidacja programu" 
	@echo "  obj    - tworzy katalog 'obj' dla plikow .o "
	@echo "  clean  - usuwa produkty kompilacji oraz program"
	@echo "  help   - wyswietla niniejszy komunikat"
	@echo