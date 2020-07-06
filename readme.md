Github: https://github.com/sebag90/caesar_cipher

# CAESAR CIPHER:
This program uses one of the easiest encryption technique to cipher and decipher a message.
Based on a key, each letter is shifted down the alphabet.

### Example:

Key = 4, Message = "Hello World" --> "Lipps Asvph"


This program also has an option (-bf) to crack a ciphered file without knowing the key by using 
brute force and letter frequency analysis given that the file is long enough.


## Dependencies:

- Boost for testing (sudo apt-get install libboost-all-dev)
- g++ or clang version 9
## Build:
g++ is the standard compiler, you can modify it in the makefile.
An executable named ccipher will be created. 

### commands: 

- make
- make raspi (for raspberry pi)

## Use:
	-h, --help	    	show this message and exit 
	-c, --cipher		cipher a message in interactive mode 
	-d, --decipher		decipher a message in interactive mode 
	-cf, --cipher -f	cipher files in input folder 
	-df, --decipher -f	decipher files in input folder 
	-bf, --bruteforce	crack ciphered files in input folder 



source input files (test1.txt, test2.txt, test3.txt, test4.txt): 

https://github.com/shekharkoirala/Game_of_Thrones