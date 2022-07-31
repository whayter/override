This time, the program asks the user to fill in a login, then a serial number. Obviously, there is little chance that the right combination will be found on the first try, so nothing special happens. So let's look at the program's assembly code to understand what's going on. The program records in the main() function the user's login with fgets(), then the serial number with scanf(). An auth() function is then called with the login and the serial number as parameters, which contains a hash algorithm. We notice the use of a [stack canary](https://en.wikipedia.org/wiki/Buffer_overflow_protection#Canaries) that will prevent us from performing a buffer overflow attack. 

The use of ptrace() in the auth() function will prevent us from analyzing the execution of the program by placing breakpoints in gdb. Well, more or less. This method is not infallible since we can modify the register values in gdb. So by placing a breakpoint at auth+114, we can redefine eax so that the condition `ptrace(PTRACE_TRACEME, 1, NULL, NULL) == -1` is false and bypass the security measure. Thus, by placing a second breakpoint at auth+286, we can display the value contained in eax, which corresponds to the expected hash for the given login. This way, we don't even need to reconstruct in detail how the hash algorithm works. Pretty cool isn't it?

```
level06@OverRide:~$ gdb level06

...

(gdb) b *auth+114
Breakpoint 1 at 0x80487ba
(gdb) b *auth+286
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaaaaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 123

Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax=0

...

Breakpoint 2, 0x08048866 in auth ()
(gdb) x/x $ebp-0x10
0xffffd618:     0x005f253e
```

So for the login "aaaaaaaaaaaaa", the expected serial number is 0x005f253e, that is 6235454.

```
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaaaaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6235454
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

We can now reach the next level with the command `su level07` and fill in the flag found as a password.