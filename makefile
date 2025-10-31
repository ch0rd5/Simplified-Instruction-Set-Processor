driver: main.o helpers.o
	g++ -std=c++17 -Wall -o driver main.o helpers.o

main.o: main.cpp helpers.h
	g++ -std=c++17 -Wall -c main.cpp

helpers.o: helpers.cpp helpers.h
	g++ -std=c++17 -Wall -c helpers.cpp

clean:
	rm *.o driver
