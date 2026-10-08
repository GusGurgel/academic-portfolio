out : main.o Midia.o CD.o DVD.o Arquivos.o
	g++ -o out main.o Midia.o CD.o DVD.o Arquivos.o -lstdc++fs
main.o: main.cpp
	g++ -c main.cpp
Midia.o: Midia.cpp Midia.h
	g++ -c Midia.cpp
CD.o: CD.cpp CD.h
	g++ -c CD.cpp
DVD.o: DVD.cpp DVD.h
	g++ -c DVD.cpp
Arquivos.o: Arquivos.cpp Arquivos.h
	g++ -c Arquivos.cpp -lstdc++fs
