<a name="docu-top"></a>
# Documentation of frankenshell
❗ README AND THE DOCUMENTATION IS CURRENTLY UNDER CONSTRUCTION ❗ 

**frankenshell** is a version of the 42 School project (**minishell**) that recreates in C a simplified version of the bash shell.

# Table of Contents
1. [Introduction](#introduction)
   1. [What is Bash?](#what-is-bash)
   2. [What is a shell?](#what-is-a-shell)
2. [Installation](#installation)
2. [Usage](#usage)

2. [Definitions](#definitions)
3. [Basic Shell Features](#basic-shell-features)
   1. [Shell Syntax](#shell-syntax)
      1. [Shell Operation PROGRAM FLOW](#shell-operation-program-flow)
      2. [Quoting](#quoting)
         1. [Single Quotes](#single-quotes)
         2. [Double Quotes](#double-quotes)
   2. [Shell Commands](#shell-commands)
      1. [Simple Commands](#simple-commands)
      2. [Pipelines](#pipelines)
   3. [Special Parameters (the fuckin $?)](#special-parameters-the-fuckin)
   4. [Shell Expansions](#shell-expansions)
      1. [Shell Parameter Expansion (DOLLAR EXPANSION I GUESS)](#shell-parameter-expansion-dollar-expansion-i-guess)
      2. [Quote Removal](#quote-removal)
   5. [Redirections](#redirections)
      1. [Redirecting Input](#redirecting-input)
      2. [Redirecting Output](#redirecting-output)
      3. [Appending Redirected Output](#appending-redirected-output)
      4. [Here Documents](#here-documents)
   6. [Executing Commands](#executing-commands)
      1. [Simple Command Expansion](#simple-command-expansion)
      2. [Command Search and Execution](#command-search-and-execution)
      3. [Command Execution Environment](#command-execution-environment)
      4. [Environment (VARIABLEN LINKED LIST AND STUFF) gibts unten nochmal, warum 2 kapitel?](#environment-variablen-linked-list-and-stuff-gibts-unten-nochmal-warum-2-kapitel)
      5. [Exit Status](#exit-status)
   7. [Signals](#signals)
4. [Builtin Commands](#builtin-commands)
   1. [echo](#echo)
   2. [cd](#cd)
   3. [pwd](#pwd)
   4. [export](#export)
   5. [unset](#unset)
   6. [env](#env)
   7. [42](#42)
   8. [history](#history)
   9. [exit](#exit)
5. [Shell Variables](#shell-variables)
6. [Using History Interactively](#using-history-interactively)
   1. [Bash History Facilities](#bash-history-facilities)
   2. [Bash History Builtins](#bash-history-builtins)
   3. [History Expansion](#history-expansion)
      1. [Event Designators](#event-designators)
      2. [Word Designators](#word-designators)
      3. [Modifiers](#modifiers)
6. [Known Bugs](#known-bugs)
6. [Acknowledgments](#acknowledgments)

## Introduction
### What is Bash?
### What is a shell?
## Installation
```
	# Clone this repository
	$ git clone https://github.com/AshParker19/42_minishell

	# Go into the repository
	$ cd 42_minishell

	# Compile the program
	$ make

	# Run the program
	$ ./frankenshell [OPTIONS]

	# OPTIONS:
	# 	--info, -i	prints details about the program flow during runtime

	# Use the program
	frankenshell--> echo "Let's goooooo!"

	# Exit the program
	$ exit
```
## Usage
**frankenshell** is designed to mimic the behavior of the traditional **bash** shell. So feel free to use it like bash.

![Example][example-gif]
## Definitions
These definitions are used throughout this manual as follows.

#### builtin
	A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system.
#### exit status
	The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255.
#### signal
	A mechanism by which a process may be notified by the kernel of an event occurring in the system.
#### token
	A sequence of characters considered a single unit by the shell. It is either a word or an operator.
#### POSIX
	A family of open system standards based on Unix. Bash is primarily concerned with the Shell and Utilities portion of the POSIX 1003.1 standard.

## Basic Shell Features
### Shell Syntax
#### Shell Operation PROGRAM FLOW
#### Quoting
- **Single Quotes**: Enclosing text in single quotes (`'`) prevents the shell from interpreting any metacharacters within the quoted sequence.
- **Double Quotes**: Using double quotes (`"`) also prevents interpretation of metacharacters, except for the dollar sign (`$`), which is used for variable expansion.

> ℹ️ &nbsp; Unclosed quotes (e.g. ```echo "Hello World```) will result in an error:\
> ⚠️ &nbsp; frankenshell: syntax error: unclosed quotes

##### Single Quotes
##### Double Quotes
### Shell Commands
#### Simple Commands
#### Pipelines
Pipes (`|`) allow the output of one command to be used as input for another, enabling command chaining.
### Special Parameters (the fuckin $?)
### Shell Expansions
The **Variable Expansion** works simmilar like in bash:
| Command            | Expand       | Output                        |
| ----------------- | :----------: | ----------------------------- |
| `echo $USER`       |      ✅        |      `current_user_value`      |
| `echo "$USER"`     |      ✅        |      `current_user_value`      |
| `echo '$USER'`     |      ❌        |      `$USER`                   |
| `<< $USER cat`     |      ❌        |  Won't expand, so the `EOF` of the heredoc will be `$USER` |

#### Shell Parameter Expansion (DOLLAR EXPANSION I GUESS)
#### Quote Removal
### Redirections

The table below describes the redirection features available in frankenshell:
| Feature| Mode            | Description                                                                                | Example                           |
|------|-------------|--------------------------------------------------------------------------------------------------|-----------------------------------|
| `<`  |Input Redirection         | Redirects input from a file to a command.                                           | `wc < file.txt`              |
| `<<` |Heredoc                   | Allows inputting multiple lines until a termination string is reached.              | `<< this_exits_the_hd wc`                  |
| `>`  |Output Redirection        | Redirects the output of a command to a file, overwriting it if it already exists.   | `echo "replace by foo" > file.txt`              |
| `>>` |Append Output Redirection | Appends command output to a file, creating it if it doesn't exist.                  | `echo "append foo" >> file.txt`

These redirections allow for flexible manipulation of command input and output, similar to standard bash functionality.

#### Redirecting Input
#### Redirecting Output
#### Appending Redirected Output
#### Here Documents
### Executing Commands
#### Simple Command Expansion
#### Command Search and Execution
#### Command Execution Environment
#### Environment (VARIABLEN LINKED LIST AND STUFF) gibts unten nochmal, warum 2 kapitel?
#### Exit Status
### Signals

	SIG_STATE_MAIN,
	SIG_STATE_PARENT,
	SIG_STATE_CHILD,
	SIG_STATE_CHILD_BUILTIN,
	SIG_STATE_HD_CHILD,
	SIG_STATE_IGNORE
 

## Builtin Commands
Each built-in command in frankenshell is detailed below with specific information and examples.

| Command                 | File(s)     	                                      												| Description									|
|-------------------------|-----------------------------------------------------------------------------------------------------|-----------------------------------------------|
| [`42`](#42)             | [`42.c`](../src/3_builtins/42.c)                    												| 42 it is ;)                                 	|
| [`cd`](#cd)             | [`cd.c`](../src/3_builtins/cd.c)                    												| Changes the current directory.              	|
| [`echo`](#echo)         | [`echo.c`](../src/3_builtins/echo.c)                												| Displays a line of text.                    	|
| [`env`](#env)           | [`env.c`](../src/3_builtins/env.c)                  												| Displays the environment variables.         	|
| [`exit`](#exit)         | [`exit.c`](../src/3_builtins/exit.c)                												| Exits the shell.                            	|
| [`export`](#export)     | [`export.c`](../src/3_builtins/export.c)<br>[`export_utils.c`](../src/3_builtins/export_utils.c)	| Sets or exports environment variables.      	|
| [`history`](#history)   | [`history.c`](../src/3_builtins/history.c)          												| Displays the command history.               	|
| [`pwd`](#pwd)           | [`pwd.c`](../src/3_builtins/pwd.c)                  												| Prints the working directory.               	|
| [`unset`](#unset)       | [`unset.c`](../src/3_builtins/unset.c)              												| Unsets environment variables.               	|



---

#### 42
<details>
  <summary>Displays a pretty 42 logo to STDOUT (or its redirection)</summary>

  ![42][builtin_42]  
</details>


| Information			|											|
|-----------------------|-------------------------------------------|
| Flags                 | `N/A`	                 					|
| Number of Arguments   | `0 to n` (all args will be ignored)   	|
| Exit Status           | `0`				           				|
| Affected Variables    | `[NONE]`			           				|

|Examples				|								|				  |								|							|
|-----------------------|-------------------------------|:---------------:|-----------------------------|---------------------------|
| **Cmd**            	| **STDOUT**    				| **Exit Status** | **Explanation**       		| **Affected Variables**	|
| `42`					| [the 42 logo] 				| `0`			  |								| 							|
| `42 foo bar`			| [the 42 logo] 				| `0`			  | all args will be ignored	| 							|

---

#### `cd`
Cd performs multiple tests if the given argument is correct. If so it changes the current working directory via `chdir` to the given path.
 
| Information			|								|
|-----------------------|-------------------------------|
| Flags                 | `N/A`	                 		|
| Number of Arguments   | `0` - `1`				   		|
| Argument Format	   	| absolute or relative path	   	|
| Exit Status           | `0` `1`			           	|
| Affected Variables    | `HOME` `OLDPWD` `PWD`        	|


**Examples**
|Examples				|						|				|														  |														|						
|-----------------------|---------------------------|:-------------:|-----------------------------------------------------|---------------------------------------------------------------|
| **Cmd**            	| **STDERR** 				|**Exit Status**| **Explanation**       								| **Affected Variables**<br>(bold variables will be updated)	|
| `cd`					| <br>`cd: HOME not set`	| `0`<br>`1`	  | if `HOME` set, wd updates to `HOME`<br>if `HOME` NOT set, wd doesn't update | `HOME` **`OLDPWD`** **`PWD`**<br>‎ |
| `cd ""`				| 							| `0`			  | empty argument, wd doesn't update					| 																|
| `cd valid_path`		| 							| `0` 			  | wd updates to `./valid_path`	 					| **`OLDPWD`** **`PWD`**										|
| `cd .`				| 							| `0` 			  | wd doesn't update; `OLDPWD` updated!				| **`OLDPWD`**													|
| `cd ..`				| 							| `0` 			  | wd updates to parent folder							| **`OLDPWD`** **`PWD`**										|
| `cd foo bar`			| `cd: too many arguments`								| `1`	|												|									 							|
| `cd noExist`			| `frankenshell: cd: noExist: No such file or directory`	| `1` 	|												|									 							|
| `cd noPermDir`		| `frankenshell: cd: noPermDir: Permission denied`		| `1` 	|												|									 							|
| `cd file`				| `frankenshell: cd: file: Not a directory`				| `1` 	|												|									 							|

> :warning:	 			&nbsp; If the external function `chdir` fails, an error message is printed and the exit status is set to `1`.\
> :white_check_mark: 	&nbsp; If `PWD` and/or `OLDPWD` are absent, the function operates normally and skips setting these variables.




---

#### echo
Displays a line of text.

| Information			|								|
|-----------------------|-------------------------------|
| Flags                 | `-n`		                 	|
| Number of Arguments   | `0` - `n`					  	|
| Argument Format	   	| all ASCII chars allowed		|
| Exit Status           | [Exit status info]           	|
| Affected Variables    | `[NONE]`			           				|

|Examples				|				|				|				  |						|							|
|-----------------------|---------------|---------------|:---------------:|-----------------------|---------------------------|
| **Cmd**            	| **STDOUT**    | **STDERR** 	| **Exit Status** | **Explanation**       | **Affected Variables**	|
| `echo "Hello"`     	| `Hello`       |            	| `0`      		  | Standard output       |							|
| `echo -n "World"`  	| `World`       |            	| `0`     		  | No newline at the end |							|
| `[Third Example]`  	| [STDOUT]      | [STDERR]   	| [Status]		  | [Explanation]         |							|
| `[Fourth Example]` 	| [STDOUT]      | [STDERR]   	| [Status]		  | [Explanation]         |							|

---

#### env

---

#### exit

---

#### export

---

#### history

---

#### pwd

---

#### unset

## Shell Variables
On programm start the enviromental variables will be loaded into frankenshell.\
With the following [builtin](#builtins) commands variables can be...
- **shown** using [env](#env)
- **sorted and shown**  using [export](#export) without arguments
- **created** using [export](#export)
- **changed** using [export](#export)
- **deleted** using [unset](#unset)

> ℹ️ &nbsp; Keep in mind that some [builtins](#builtins) (e.g. [cd](#cd)) change some variables during runtime!

## Using History Interactively
### Bash History Facilities
### Bash History Builtins
### History Expansion
#### Event Designators
#### Word Designators
#### Modifiers

## Known Bugs
	- export vs env
	- single cmds with redirs

## Acknowledgments
Thx to all those guys and gals for hints, tipps and feedback!

[@Gabriel](https://github.com/portugueseTorch)\
[@Martim](https://github.com/mm1212)\
[@Margarida](https://github.com/MariaAguiar)\
[@Manuel](https://github.com/manuel-aguiar)

:arrow_up:   <a href="#docu-top">back to top</a>   :arrow_up:




















































<!-- MARKDOWN LINKS & IMAGES -->
[example-gif]: /images/example.gif
[builtin_42]: /images/builtin_42.png