build : main.o airport.o plane.o runway.o
	g++ -std=c++11 -o "airport" main.o airport.o plane.o runway.o

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

airport.o : airport.cpp
	g++ -std=c++11 -c airport.cpp

plane.o : plane.cpp
	g++ -std=c++11 -c plane.cpp

runway.o : runway.cpp
	g++ -std=c++11 -c runway.cpp

clean :
	rm -f main.o airport.o plane.o runway.o

flush :
	rm -f main.o airport.o plane.o runway.o airport

cleanbuild : | flush build clean
