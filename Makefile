CCFLAGS = -Wall -g
CXX = g++ -std=c++17 -lpthread

main: main.cpp process.o
	$(CXX) main.cpp process.o -o main  
  
process.o: process.cpp process.h  utils.o
	$(CXX) process.cpp -c $(CCFLAGS)

cpu.o: cpu.cpp cpu.h process.o
	$(CXX) cpu.cpp -c $(CCFLAGS)

utils.o: utils.h 
	$(CXX) utils.h -c $(CCFLAGS)

.PHONY: clean 
clean: 
	rm -f main *.o *~
