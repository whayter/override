Back in the world of ELF 32-bit LSB executables. At runtime, the name of the program is displayed and you are asked to enter a password, after which there is a very good chance that the program will display "Invalid password" and exit. Reconstructing the [source code](source.c), we find a number of functions, three of which are actually called  during program execution: the main() function, a test() function and a decrypt() function:

* The main() function displays a few lines and then saves the user's input in an int variable using scanf() before calling the test() function, passing it two parameters: the value saved with scanf(), and 0x1337d00d (= 322424845).

* In the test() function, the result of subtracting the user's input from 0x1337d00d is recorded. Depending on the result, the decrpypt() function is called either with this result as parameter or with rand().

* The decrypt() function contains the encrypted password ("Q}|u`sfg~sf{}|a3") and the decrypted password ("Congratulations!"). In order to decrypt the password, the program performs an exclusive OR (XOR) for each character of the encrypted password with the parameter passed to the function. If the result matches the decrypted password, then a shell is launched.

::: Interesting fact
We deduce from some elements of the decrypt() function the use of the `-fstack-protector` flag at compile time, which protects against buffer overflow. How does it work ? The prologue of a function stores a guard variable onto the stack frame. Before returning from the function, the function epilogue checks the guard variable to make sure that it has not been overwritten. A guard variable that is overwritten indicates a buffer overflow, and the checking code alerts the run-time environment. This guard is called a [stack canaries](https://en.wikipedia.org/wiki/Buffer_overflow_protection#Canaries).
:::

We have a way to approximate the correct password: from the test() function, we know that `salt - input` must be greater than 0 and less than 10, or greater than 15 and less than 22, which leaves us with 15 possible values. What a lousy security system!

Here are the ranges for the possible values of the password: `322424823 < input < 322424830` or `322424835 < input < 322424845`. We could write a small script to find the right value in these intervals, but honestly, we will go faster by testing the different possibilities by hand. The correct password is 322424827.

```
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
We can now reach the next level with the command `su level04` and fill in the flag found as a password.