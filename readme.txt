Dependencies:
    - Boost for testing (sudo apt-get install libboost-all-dev)
    - g++ or clang version 9

Build:
	g++ is the standard compiler, you can modify it in the makefile.
	An executable named ccipher will be created.

    - make
    - make raspi (for raspberry pi)

Use:
	-h, --help	    	show this message and exit
	-c, --cipher		cipher a message in interactive mode
	-d, --decipher		decipher a message in interactive mode
	-cf, --cipher -f	cipher files in input folder
	-df, --decipher -f	decipher files in input folder
	-bf, --bruteforce	crack ciphered files in input folder



source input files: https://github.com/shekharkoirala/Game_of_Thrones