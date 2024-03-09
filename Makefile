CCFLAGS = -Wall -g
CXX = g++ -std=c++17 -lpthread

main: main.o process.o 
	$(CXX) main.o process.o -o main  

main.o: main.cpp 
	$(CXX) main.cpp -c $(CCFLAGS)
               
process.o: process.cpp process.h
	$(CXX) process.cpp -c $(CCFLAGS)

.PHONY: clean 
clean: 
	rm -f main *.o *~
