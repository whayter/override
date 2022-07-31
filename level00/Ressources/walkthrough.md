The goal of this project is to get the content, for each level, of the .pass file that is in the current directory of the upper level. We are currently at level00, so we want to get the content of the file /home/users/level01/.pass:

```
level0@RainFall:~$ cat /home/users/level01/.pass
cat: /home/users/level01/.pass: Permission denied
```
Of course, that whould be too easy.

Using gdb, we can reconstruct the [source code](../source.c) of the executable file we have. The program displays a prompt and then asks the user to enter a password. The password appears in clear text in the code: 5276. When we enter it, the program confirms the authentication and launches a shell. We can then retrieve the contents of the .pass file:

```
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
We can now reach the next level with the command `su level01` and fill in the flag found as a password.