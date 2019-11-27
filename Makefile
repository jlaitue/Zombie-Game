CPP=g++ --std=c++11 -Wall
all : Test
Test : Test.o Element.o Monster.o
	$(CPP) -o Test Test.o Element.o Monster.o
Test.o : Test.cpp
	$(CPP) -c Test.cpp
Element.o : Element.cpp
	$(CPP) -c Element.cpp
Monster.o : Monster.cpp
	$(CPP) -c Monster.cpp
clean :
	rm	*.o *.hpp.gch
