CXX = g++
CXXFLAGS = -O3 -I /usr/local/include  -I src/ -std=c++17 -pedantic

clean:
	rm -f *.o *.out

main: src/main.cpp
	$(CXX) $(CXXFLAGS) -L. src/main.cpp -o main.out

.PHONY: clean