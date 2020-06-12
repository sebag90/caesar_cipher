Output_filename = main
Compiler = g++
Library = std=c++17
main_file = main.cpp
functions = ../../functions.cpp

all:clean
	$(Compiler) -$(Library) $(main_file) $(functions) -o $(Output_filename)
	

clean:
	rm -f $(Output_filename)