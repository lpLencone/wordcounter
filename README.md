# wordcounter
word counter written in c

To compile the program, simply run make and run it as ./main

This program implements data structures to read a file and save the frequency each word appears in that.

## Options
Use option `-a` to pass a file; if not specified, program reads from standard input  
Use option `-h` to print out help menu (it's in portuguese)  
Use option `-i` to read the words case insensitively  
Use option `-o` to sort, pass in `p` to sort ASCIIbetically and `c` to sort by frequency  
Use option `-p` to search for a word or words; when searching for multiple words, pass them separated by a comma  
Use option `-s` to save, and pass in the path to the file where to save  
  
If options `-o` and `-p` are used, the order of the words specified takes precedence, meaning it won't matter if you passed -o as flag

## Note
For this program a word is any string of letters only. Numbers, underscore, etc. are not considered as part of words. If, then, there's the word 'e-mail' in a file, the program will consider 'e' to be a word as well as 'mail'.
