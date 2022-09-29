CC = g++ -std=c++11

all: StoreCalculator.out assets.out province.out city.out store.out

StoreCalculator.out: main.o functions.o
	$(CC) main.o functions.o -o StoreCalculator.out

assets.out: assets.o functions.o
	$(CC) assets.o functions.o -o assets.out

province.out: province.o functions.o
	$(CC) province.o functions.o -o province.out

city.out: city.o functions.o
	$(CC) city.o functions.o -o city.out

store.out: store.o functions.o
	$(CC) store.o functions.o -o store.out

main.o: main.cpp header.hpp
	$(CC) -c main.cpp -o main.o

assets.o: assets.cpp header.hpp
	$(CC) -c assets.cpp -o assets.o

province.o: province.cpp header.hpp
	$(CC) -c province.cpp -o province.o

city.o: city.cpp header.hpp
	$(CC) -c city.cpp -o city.o

store.o: store.cpp header.hpp
	$(CC) -c store.cpp -o store.o

functions.o: functions.cpp header.hpp
	$(CC) -c functions.cpp -o functions.o

clean:
	rm *.o StoreCalculator.out assets.out province.out city.out store.out