# Interlude: Process API

## Questions

1. Write a program that calls fork(). Before calling fork(), have the main
   process access a variable (e.g., x) and set its value to something (e.g.,
   100). What value is the variable in the child process? What happens to the
   variable when both the child and parent change the value of x?

2. Write a program that opens a file (with the open() system call) and then
   calls fork() to create a new process. Can both the child and parent access
   the file descriptor returned by open()? What happens when they are writing to
   the file concurrently, i.e., at the same time?

3. Write another program using fork(). The child process should print “hello”;
   the parent process should print “goodbye”. You should try to ensure that the
   child process always prints first; can you do this without calling wait() in
   the parent?

4. Write a program that calls fork() and then calls some form of exec() to run
   the program /bin/ls. See if you can try all of the variants of exec(),
   including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and
   execvpe(). Why do you think there are so many variants of the same basic
   call?

5. Now write a program that uses wait() to wait for the child process to finish
   in the parent. What does wait() return? What happens if you use wait() in the
   child?

## Answers

1. The program is specified [here](src/1.c). The value of `x` in the child
   process is `100`. Since `fork` creates separate address spaces, the parent
   and child process actions do not affect the address spaces of the other.

2. The program is specified [here](src/2.c). Both the child and parent process
   have access to the file descriptor. When the processes write to the same
   file, they write one of `Hello, from the {parent,child} process!` in the
   order that the child or parent process calls the `write` system call i.e. if
   the child process accesses the file first, then we would see:

   ```txt
   Hello, from the child process!\0Hello, from the parent process!\0
   ```
