CC=clang++
CXXFLAGS=-std=c++17 -O3 -fopenmp -fopenmp-simd -fconstexpr-steps=5000000

.PHONY: test

main: main.cpp include/*.hpp
	$(CC) main.cpp $(CXXFLAGS) -o main

atack: atack_2 atack_3 atack_3 atack_4 atack_5 atack_6 atack_7

atack_2: atack.cpp include/*.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=2 -o atack/len_2
atack_3: atack.cpp include/*.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=3 -o atack/len_3
atack_4: atack.cpp include/*.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=4 -o atack/len_4
atack_5: atack.cpp include/*.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=5 -o atack/len_5
atack_6: atack.cpp include/*.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=6 -o atack/len_6
atack_7: atack.cpp include/*.hpp
	$(CC) atack.cpp $(CXXFLAGS) -DCODE_ID=7 -o atack/len_7

test:
	$(CC) test.cpp $(CXXFLAGS) -o test
	./test
	rm ./test
