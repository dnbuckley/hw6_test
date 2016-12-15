
all: scrabble

Bag.o: Bag.cpp
	g++ -c Bag.cpp

Board.o: Board.cpp
	g++ -c Board.cpp

Dictionary.o: Dictionary.cpp
	g++ -c Dictionary.cpp

ai.o: ai.cpp
	g++ -c ai.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Scrabble.o: Scrabble.cpp
	g++ -c Scrabble.cpp

scrabble: Bag.o Board.o Dictionary.o ai.o Player.o Scrabble.o
	g++ Bag.o Board.o Dictionary.o ai.o Player.o Scrabble.o -o scrabble

clean:
	rm *.o scrabble