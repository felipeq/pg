all : app
app : main.o  klasy.o
	g++ -o app main.o  klasy.o -lSDL

main.o : main.cpp config.h klasy.hpp
	g++ -c -o main.o main.cpp -lSDL
	
klasy.o : klasy.cpp config.h klasy.hpp
	g++ -c -o klasy.o klasy.cpp -lSDL

clean : 
	rm *.o
