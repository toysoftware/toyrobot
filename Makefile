main: main.cpp Grid.h Robot.h
	g++ -o main main.cpp

.PHONY: clean

clean:
	@rm -f main *.o
