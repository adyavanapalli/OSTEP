# Interlude: Process API

## Questions

1. Write a program that calls `fork()`. Before calling `fork()`, have the main
   process access a variable (e.g., `x`) and set its value to something (e.g.,
   `100`). What value is the variable in the child process? What happens to the
   variable when both the child and parent change the value of `x`?

2. Write a program that opens a file (with the `open()` system call) and then
   calls `fork()` to create a new process. Can both the child and parent access
   the file descriptor returned by `open()`? What happens when they are writing
   to the file concurrently, i.e., at the same time?

3. Write another program using `fork()`. The child process should print “hello”;
   the parent process should print “goodbye”. You should try to ensure that the
   child process always prints first; can you do this _without_ calling `wait()`
   in the parent?

4. Write a program that calls `fork()` and then calls some form of `exec()` to
   run the program `/bin/ls`. See if you can try all of the variants of
   `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`,
   `execvp()`, and `execvpe()`. Why do you think there are so many variants of
   the same basic call?

5. Now write a program that uses `wait()` to wait for the child process to
   finish in the parent. What does `wait()` return? What happens if you use
   `wait()` in the child?

6. Write a slight modification of the previous program, this time using
   `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

7. Write a program that creates a child process, and then in the child closes
   standard output (`STDOUT FILENO`). What happens if the child calls `printf()`
   to print some output after closing the descriptor?

8. Write a program that creates two children, and connects the standard output
   of one to the standard input of the other, using the `pipe()` system call.

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

3. One can do this by letting the parent process listen for a signal packet from
   the child process, after which it may safely print the "Goodbye" message.
   This program is demonstrated [here](src/3.c).

4. I've written a program that calls `execl` [here](src/4.c), but I'm not sure
   what the other variants do that well, so I'm skipping that part of the
   question.

5. This program is demonstrated [here](src/5.c). When `wait` is called in the
   parent process, it returns the process id (PID) of the child. When `wait` is
   called in the child process, it returns `-1` as there is no child process to
   wait for.

6. This program is demonstrated [here](src/6.c). Calling `waitpid()` is useful
   when we need to wait for a specific child, or need to pass additional options
   like `WNOHANG` (return immediately if no child has exited), `WUNTRACED` (also
   return if a child has stopped (but not traced via `ptrace(2)`). Status for
   traced children which have stopped is provided even if this option is not
   specified), or `WCONTINUED` (also return if a stopped child has been resumed
   by delivery of `SIGCONT`).

7. When the child closes `STDOUT_FILENO` and uses `printf`, no output is
   observed. This program is demonstrated [here](src/7.c).

8. This program is demonstrated [here](src/8.c). One caveat though: I found it
   unnecessary to create _two_ children, hence the program is demonstrated with
   just the parent and child.
