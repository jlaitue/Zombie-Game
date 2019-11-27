CPP=g++ --std=c++11 -Wall
all : Test
Test : Test.o
	$(CPP) -o Test Test.o
Test.o : Test.cpp
	$(CPP) -c Test.cpp
clean :
	del	*.o *.hpp.gch
