Back in the world of ELF 32-bit LSB executables. At runtime, the name of the program is displayed and you are asked to enter a password, after which there is a very good chance that the program will display "Invalid password" and exit. Reconstructing the [source code](source.c), we find a number of functions, three of which are actually called  during program execution: the main() function, a test() function and a decrypt() function.

* The main() function displays a few lines and then saves the user's input in an int variable using scanf() before calling the test() function, passing it two parameters: the value saved with scanf(), and 0x1337d00d (= 322424845).

* In the test() function, the result of subtracting the user's input from 0x1337d00d is recorded. Depending on the result, the decrpypt() function is called either with this result as parameter or with rand().

* 




```
(gdb) info functions
...
0x080485f4  clear_stdin
0x08048617  get_unum
0x0804864f  prog_timeout
0x08048660  decrypt
0x08048747  test
0x0804885a  main
...
```

[stack canaries](https://en.wikipedia.org/wiki/Buffer_overflow_protection#Canaries)

The program has been compiled with the -fstack-protector flag


We can now reach the next level with the command `su level03` and fill in the flag found as a password.