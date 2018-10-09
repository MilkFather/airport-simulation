build : main.o plane.o runway.o random.o exqueue.o
	g++ -std=c++11 -o "airport" main.o plane.o runway.o random.o exqueue.o

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

plane.o : plane.cpp
	g++ -std=c++11 -c plane.cpp

runway.o : runway.cpp
	g++ -std=c++11 -c runway.cpp

random.o : random.cpp
	g++ -std=c++11 -c random.cpp

exqueue.o : exqueue.cpp
	g++ -std=c++11 -c exqueue.cpp

clean : 
	rm -f main.o plane.o runway.o random.o exqueue.o

flush : 
	rm -f main.o plane.o runway.o random.o exqueue.o airport

cleanbuild : | flush build clean