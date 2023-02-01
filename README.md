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
<h2>fork()</h2>
<p>If you call fork() once:</p>

_FYI:_

	|-----------|
	|  parent   |
	|___________|
		|
		|
	|-----------|
	|   child   |
	|___________|

<p>If you call fork() twice:</p>

_FYI:_

	|-----------|
	|  parent   |-------------->|
	|___________|               |
		|                   |
		|                   |
	|-----------|       |-----------|
	|   child   |       |   child   |
	|___________|       |___________|
		|
		|
	|-----------|
	|   child   |       
	|___________|

<p>If you call fork() 3 times:</p>

_FYI:_

	|-----------|       |-----------|
	|   child   |<------|  parent   |---------->|
	|___________|       |___________|           |
	                    	|                   |
	                    	|                   |
	|-----------|       |-----------|       |-----------|       |-----------|
	|   child   |<------|   child   |       |   child   |------>|   child   |
	|___________|       |___________|       |___________|       |___________|
	                    	|
	                    	|
	                    |-----------|
	                    |   child   |
	                    |___________|
	                    	|
	                    	|
	                    |-----------|
	                    |   child   |
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