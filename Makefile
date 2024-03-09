CCFLAGS = -Wall -g
CXX = g++ -std=c++17 -lpthread

main: main.cpp process.o
	$(CXX) main.cpp process.o -o main  
  
process.o: process.cpp
	$(CXX) process.cpp -c $(CCFLAGS)

cpu.o: cpu.cpp process.o
	$(CXX) cpu.cpp -c $(CCFLAGS)

.PHONY: clean 
clean: 
	rm -f main *.o *~
