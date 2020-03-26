Output_filename = main
Compiler = g++
Library = std=c++17

all:clean
	$(Compiler) -$(Library) main.cpp functions.cpp -o $(Output_filename)
	

clean:
	rm -f $(Output_filename)