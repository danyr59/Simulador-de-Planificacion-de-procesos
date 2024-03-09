CCFLAGS = -Wall -g
CXX = clang++11 -std=c++17 -lpthread

main: main.o process.o 
	$(CC) main.o process.o -o main  

main.o: main.cpp 
	$(CC) main.cpp -c $(CCFLAGS)
               
process.o: process.cpp process.h
	$(CC) process.cpp -c $(CCFLAGS)

.PHONY: clean 
clean: 
	rm -f main *.o *~
