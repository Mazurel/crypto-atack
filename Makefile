CC=clang++
CXXFLAGS=-std=c++17 -O3 -fopenmp -fopenmp-simd -fconstexpr-steps=5000000

.PHONY: test

all: atack_2 atack_3 atack_3 atack_4 atack_5 atack_6

atack_2: atack.cpp *.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=2 -o atack/len_2
atack_3: atack.cpp *.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=3 -o atack/len_3
atack_4: atack.cpp *.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=4 -o atack/len_4
atack_5: atack.cpp *.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=5 -o atack/len_5
atack_6: atack.cpp *.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=6 -o atack/len_6

test:
	$(CC) test.cpp $(CXXFLAGS) -o test
	./test
	rm ./test
