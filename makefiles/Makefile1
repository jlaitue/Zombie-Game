CPP=g++ --std=c++11 -Wall
all : Test
Test : Test.o Element.o Monster.o Board.o
	$(CPP) -o Test Test.o Element.o Monster.o Board.o
	del	*.o *.hpp.gch

Test.o : Test.cpp
	$(CPP) -c Test.cpp
Element.o : Element.cpp
	$(CPP) -c Element.cpp
Monster.o : Monster.cpp
	$(CPP) -c Monster.cpp
Board.o : Board.cpp
	$(CPP) -c Board.cpp
clean :
	del	*.o *.hpp.gch
