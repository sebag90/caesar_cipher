Output_filename = main
Compiler = g++
Library = std=c++17 
main_file = main.cpp
functions = functions.cpp

all:clean
	$(Compiler) -$(Library) -pthread $(main_file) $(functions) -o $(Output_filename)

raspi:clean
	clang++-9 -$(Library) -pthread $(main_file) $(functions) -o $(Output_filename) -lstdc++fs
	

clean:
	rm -f $(Output_filename)
