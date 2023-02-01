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
<h2 align=center>fork()</h2>
<p align=center>It's creating a new process, which is called child process, which runs concurrently with the process that makes the fork() call (parent process).</p>
<p align=center>After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.</p>
<p align=center>Negative Value: creation of a child process was unsuccessful.<p>
<p align=center>Zero: Returned to the newly created child process.<p>
<p align=center>Positive value: Returned to parent or caller. The value contains process ID of newly created child process.<p>

_If you call fork() once:_

	|-----------|
	|  parent   |
	|___________|
		|
		|
	|-----------|
	|  child_1  |
	|___________|

_If you call fork() twice:_

	|-----------|
	|  parent   |-------------->|
	|___________|               |
		|                   |
		|                   |
	|-----------|       |-----------|
	|  child_1  |       |  child_2  |
	|___________|       |___________|
		|
		|
	|-----------|
	|  child_3  |       
	|___________|

_If you call fork() 3 times:_

	|-----------|       |-----------|
	|  child_4  |<------|  parent   |---------->|
	|___________|       |___________|           |
	                    	|                   |
	                    	|                   |
	|-----------|       |-----------|       |-----------|       |-----------|
	|  child_5  |<------|  child_1  |       |  child_2  |------>|  child_6  |
	|___________|       |___________|       |___________|       |___________|
	                    	|
	                    	|
	                    |-----------|
	                    |  child_3  |
	                    |___________|
	                    	|
	                    	|
	                    |-----------|
	                    |  child_7  |
	                    |___________|

<div align=center>

### 📋 How pipes work:
_FYI:_

	Dunno yet :]

### 📋 Mandatory:

### 📋 Bonus:

### 🛠️ Usage:

### 🛠️ Testing:
</div>