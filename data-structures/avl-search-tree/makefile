CFLAGS = -Wall -Wextra -pedantic-errors

out: main.o person.o gdate.o avl.o gtable.o
	g++ $(CFLAGS) main.o person.o gdate.o avl.o gtable.o -o out

main.o: main.cpp
	g++ -c $(CFLAGS) main.cpp

person.o: person.cpp person.hpp
	g++ -c $(CFLAGS) person.cpp

gdate.o: gdate.cpp gdate.hpp
	g++ -c $(CFLAGS) gdate.cpp

avl.o: avl.cpp avl.hpp node.hpp
	g++ -c $(CFLAGS) avl.cpp

gtable.o: gtable.cpp gtable.hpp
	g++ -c $(CFLAGS) gtable.cpp

run:
	@clear
	@echo
	@./out

clear:
	rm main.o person.o gdate.o avl.o gtable.o
