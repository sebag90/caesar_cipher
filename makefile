Output_filename = ccipher
Compiler = g++
Library = std=c++17 
main_file = src/main.cpp
functions = src/functions.cpp

all:clean
	$(Compiler) -$(Library) -pthread $(main_file) $(functions) -o $(Output_filename)

raspi:clean
	clang++-9 -$(Library) -pthread $(main_file) $(functions) -o $(Output_filename) -lstdc++fs
	

clean:
	rm -f $(Output_filename)
