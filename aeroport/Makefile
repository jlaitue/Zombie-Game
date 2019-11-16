CPP=g++ --std=c++11 -Wall
all : TestAeroport

TestAeroport : Test.o Aeroport.o Avion.o Seat.o Person.o
	$(CPP) -o TestAeroport Test.o Aeroport.o Avion.o Seat.o Person.o

Test.o : Test.cpp
	$(CPP) -c Test.cpp

Aeroport.o : Aeroport.cpp
	$(CPP) -c Aeroport.cpp

Avion.o : Avion.cpp
	$(CPP) -c Avion.cpp

Seat.o : Seat.cpp
	$(CPP) -c Seat.cpp

Person.o : Person.cpp
	$(CPP) -c Person.cpp

clean :
	del	*.o *.hpp.gch
