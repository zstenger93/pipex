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
<h2 align=center>fork()</h2>
<p align=center>


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