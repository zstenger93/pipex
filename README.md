<h1 align="center">
	📖 PIPEX
</h1>
<p align="center">
	<b><i>This project will let you discover in detail a UNIX mechanism that you already know
by using it in your program.</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/zstenger93/pipex?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/zstenger93/pipex?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/zstenger93/pipex?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/zstenger93/pipex?color=green" />
</p>
<h2 align=center>Allowed functions</h2>
<p align=center>open, close, read, write, malloc, free, perror, strerror, access, dup,</p>
<p align=center>dup2, execve, exit, fork, pipe, unlink, wait, waitpid, ft_printf</p>
<h2 align=center>env</h2>
<p align=center>When used in a pipeline, env is used to pass specific environment variables to a command or process in the pipeline, allowing it to access those values and use them in its execution.</p>
<h2 align=center>pipe()</h2>
<p align=center>A pipe is a system call that creates a unidirectional communication link between two process</p>
<p align=center>system call creates a pair of file descriptors, a read-end and a write-end, that are connected to each other so that data written to the write-end of the pipe is read from the read-end of the pipe.</p>
<p align=center>First process output on the stdout becomes the second process input on stdin</p>
<p align=center>First process -> infile, second process -> outfile</p>

_Pipeline_

            |---------|
            | PIPE(); |
            |_________|
             /       \
            /         \
          fd0         fd1
            |---------|
            | FORK(); |
            |_________|
              /     \
             /       \
            /         \
    |--------|       |-------|
    | PARENT |       | CHILD |
    |________|       |_______|
      /    \           /    \
    fd0    fd1        fd0   fd1

<h2 align=center>fork()</h2>
<p align=center>It's creating a new process, which is called child process, which runs concurrently with the process that makes the fork() call (parent process).</p>
<p align=center>After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.</p>
<p align=center>Negative Value: creation of a child process was unsuccessful.<p>
<p align=center>Zero: Returned to the newly created child process.<p>
<p align=center>Positive value: Returned to parent or caller. The value contains process ID of newly created child process.<p>

_If you call fork() once:_

	|-----------|
	|  PARENT   |
	|___________|
		|
		|
	|-----------|
	|  Child_1  |
	|___________|

_If you call fork() twice:_

    |-----------|
    |  PARENT   |___________
    |___________|           |
        |                   |
        |                   |
	|-----------|       |-----------|
	|  Child_1  |       |  Child_2  |
	|___________|       |___________|
		|
		|
	|-----------|
	|  Child_3  |       
	|___________|

_If you call fork() 3 times:_

	|-----------|       |-----------|
	|  Child_4  |<------|  PARENT   |___________
	|___________|       |___________|           |
	                    	|                   |
	                    	|                   |
	|-----------|       |-----------|       |-----------|       |-----------|
	|  Child_5  |<------|  Child_1  |       |  Child_2  |------>|  Child_6  |
	|___________|       |___________|       |___________|       |___________|
	                    	|
	                    	|
	                    |-----------|
	                    |  Child_3  |
	                    |___________|
	                    	|
	                    	|
	                    |-----------|
	                    |  Child_7  |
	                    |___________|

_If you call fork() 4 times:_


                                            |-----------|
                                            |  Child_8  |
                                            |___________|
                                                   |
                                                   |
    |-----------|       |-----------|       |-----------|        |-----------|       |-----------|
    |  Child_12 |<------|  Child_4  |<------|  PARENT   |------->|  Child_2  |------>|  Child_6  |
    |___________|       |___________|       |___________|        |___________|       |___________|
                                                    |                      |                  |
                                                    |                      |                  |
    |-----------|       |-----------|       |-----------|          |-----------|       |-----------|
    |  Child_13 |<------|  Child_5  |<------|  Child_1  |_____     |  Child_10 |       |  Child_14 |
    |___________|       |___________|       |___________|     |    |___________|       |___________|
                                              |               |
                                              |          |-----------|
                |-----------|       |-----------|        |  Child_9  |
                |  Child_11 |<------|  Child_3  |        |___________|
                |___________|       |___________|
                                            |
                                            |
                                      |-----------|      |-----------|
                                      |  Child_7  |----->|  Child_15 |
                                      |___________|      |___________|

<div align=center>
	<h2>dup2()</h2>
	<p> is a system call in the C programming language that is used to duplicate a file descriptor. The call takes two arguments: an existing file descriptor (the original) and a new file descriptor number (the copy).</p>
	<p>The new file descriptor is a copy of the original file descriptor, and it shares the same properties and underlying file table entry. Any changes made to the new file descriptor are reflected in the original file descriptor, and vice versa.</p>
	<p>If it was open previously, it's closed before being reused and it is running automatically</p>
	<p>Trying to use dup() and close() instead, could cause problems like, reuse of the fd between 2 proces</p>
	<h2>access()</h2>
	<p>can check the path with X_OK to the command</p>
	<h2>sterror()</h2>
	<p>returns a specific error code the program exited with if an error occoured</p>
	<h2>execve</h2>
	<p>The call takes three arguments: the pathname of the program to be executed, an array of arguments for the program, and an array of environment variables for the program.</p>
	<p>The execve() function replaces the current process image with the new process image, so that the new program runs in the same process as the calling program.</p>
	<p>It is used when you want to run a program in place of the current process, without creating a new process. This is useful when you want to start a new program from a C program, or when you want to replace the current shell with a different shell.</p>
	<h2>wait() & waitpid()</h2>
	<p>Both can be used for waiting child processes and with waitpid you can wait for a specific one and can use -1 to wait untill all process finsh</p>
	<h2 align=center>Error handling</h2>
	<p>Wrong amount of args</p>
	<p>Empty arguments or with only spaces in the argument</p>
	<p>Invalid infile or outfile</p>
	<p>No cat if the first command invalid</p>
	<p>Invalid commands</p>
	<p>Accepting commands with path as well, while checking if it's in /bin or /usr/bin</p>
	<p>Wrong path check for the previous point</p>
	<p>Correct returns as permission denied or no such file/folder etc.</p>
	<p>Dircet path check</p>
	<p>check for exit command</p>
	<p>fork error</p>
	<p>if first arg invalid and second is cat</p>
	<p>checking for script files</p>
	<p>commands not depending on the prev command, after an invalid command should work in bonus</p>
</div>
<div align=center>
<h2>Bonus</h2>
<p>heredoc</p>
<p>handling multiple commands</p>
<h2>🛠️Usage🛠️</h2>

```shell
./pipex infile "cmd" "cmd1" outfile
```

```shell
./pipex_bonus infile "cmd" "cmd1" "cmd2" "cmd3" "cmd4" outfile
```

```shell
./pipex_bonus here_doc stop "cmd" "cmd1" outfile
```
</div>
