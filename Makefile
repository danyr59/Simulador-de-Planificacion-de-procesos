CCFLAGS = -Wall -g
CXX = g++ -std=c++17 -lpthread

main: utils.o process.o cpu.o fcfs.o SJF.o random_selection.o npps.o ps.o RR.o
	$(CXX) $(CCFLAGS) main.cpp *.o -o main.out
  
%.o: %.cpp
	$(CXX) $(CCFLAGS) -c $< -o $@


.PHONY: clean 
clean: 
	rm -f main *.o *~
