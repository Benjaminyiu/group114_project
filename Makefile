FLAGS = -pedantic-errors -std=c++11

instruction.o: instruction.cpp instruction.h
	g++ $(FLAGS) -c $<

rank.o: rank.cpp rank.h
	g++ $(FLAGS) -c $<

game: instruction.o rank.o main_page.cpp
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f *.o

.PHONY: clean
