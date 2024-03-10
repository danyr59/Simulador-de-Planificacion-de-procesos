CCFLAGS = -Wall -g
CXX = g++ -std=c++17 -lpthread

main: utils.o process.o cpu.o fcfs.o
	$(CXX) main.cpp *.o -o main  
  
%.o: %.cpp
	$(CXX) -c $< -o $@


.PHONY: clean 
clean: 
	rm -f main *.o *~
