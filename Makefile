CPP=g++ --std=c++11 -Wall
all : TestBox
TestBox : Boxint.o Test.o
	$(CPP) -o TestBox Boxint.o Test.o
Test.o : Test.cpp
	$(CPP) -c Test.cpp
Boxint.o : Boxint.cpp
	$(CPP) -c Boxint.cpp
clean :
	del	*.o
g++ --std=c++11 -Wall -c Test.cpp
