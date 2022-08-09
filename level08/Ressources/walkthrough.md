This time, the executable file is in ELF 64-bit format. There is also a /backups folder. At runtime, the program displays "Usage: ./level08 filename", then "ERROR: Failed to open (null)" because I passed no argument. 

Thanks to the source code analysis, we can see that the program creates a backup of the file passed in parameter. So we should be able to read the content of the `/home/users/level09/.pass` file this way.

Unfortunately, the program parameter is used to open the file with fopen(), then concatenated to "./backups/" to create the backup file. Passing the relative link `../level09/.pass`, we manage to open the file with fopen(), but the file `./backups/../level09/.pass` cannot be created because `backups/../level09` does not exist.

However, this problem can be easily overcome: by creating the tree in `/tmp`, then running the program from `/tmp` with an absolute path, we manage to:
- open the `/home/users/level09/.pass` file with fopen() because the absolute path is valid
- create the `backups/home/users/level09/.pass` file because the tree structure is good from where we are

```
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ ls
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09/
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

We can now reach the next level with the command `su level09` and fill in the flag found as a password.
