<a name="docu-top"></a>
<br />
<div align="center">
	<a href="../art.sh">
    	<img src="../images/logo.png" alt="Logo" width="224" height="300">
  	</a>
  	<h1 align="center">Documentation of frankenshell</h1>
</div>
<br>

# Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
2. [Usage](#usage)
2. [Definitions](#definitions)
2. [Structs](#structs)
3. [**How frankenshell works**](#how-frankenshell-works)
    1. [Initialization](#initialization)
    2. [Input Management](#input-management)
        1. [Trim Input](#trim-input)
        2. [Mark Seperators](#mark-seperators)
        3. [Variable Expansion](#variable-expansion)
            1. [Variable Expansion](#variable-expansion)
            2. [Extract Limiter](#extract-limiter)
        4. [Tokenize](#tokenize)
        5. [Parse](#parse)
    3. [Execution](#execution)
        1. [Setup Execution](#setup-execution)
            1. [Setup Pipes](#setup-pipes)
            2. [Setup Redirections](#setup-redirections)
                1. [Heredoc](#heredoc)
        2. [Execute](#execute)
    4. [Termination](#termination)
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
      5. [Exit Status](#exit-status)
   7. [Signals](#signals)
4. [Builtin Commands](#builtin-commands)
5. [Environment Variables](#environment-variables)
6. [Known Bugs](#known-bugs)
7. [Acknowledgments](#acknowledgments)

## Introduction

As ChatGPT said in 2023:

> Minishell is a [42 school](https://42.fr/en/homepage/) project designed to create a simplified Unix shell. The idea behind Minishell is to develop a basic command-line interface (CLI) that can execute simple commands and handle input/output redirection. It's meant to serve as a learning exercise for students to gain a fundamental understanding of how shells work by implementing core features like parsing user input, managing processes, handling signals, creating builtins and executing system commands.

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
	A sequence of characters considered a single unit by frankenshell.
#### cycle
	The input is processed after the user hits the `return` key, which involves a series of steps: cleaning the input string, expanding variables, tokenizing, constructing an ast, setting up pipes, forking processes, and updating the exit status.
#### tree
	see ast
#### ast
	The parser in Frankenshell constructs an abstract syntax tree (AST). For more in-depth information on this subject, refer to the [Parser](#parser) chapter.

## Structs
### t_mbox
The struct `mbox` is the main structure of the program: it is being passed as an argument to most of the functions and contains all the info needed for the program to work.
> :page_facing_up:  &nbsp; The file ['manage_mbox.c'](../src/0_core/manage_mbox.c) contains the functions for initializing and destroying the mbox instance.
```
typedef struct s_mbox
{
    char                        *inp_orig;
    char                        *inp_trim;
    char                        *inp_shift;
    char                        *inp_expand;
    int                         consecutive_lt;
    bool                        error_status;
    t_env                       *env;
    t_list                      *history_lst;
    t_token                     *tokens;
    t_token                     *tmp_token;
    t_ast                       *root;
    t_ast                       *tmp_node;
    t_exec                      executor;
    int                         count_cycles;
    t_bool                      print_info;
} t_mbox;
```

---

### t_env
The struct `t_env` is used to build a liked list, storing all (enviromental) variables.
> :floppy_disk: &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :scroll:      &nbsp;  For further details see the section [Environment Variables](#environment-variables).
```
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;
```

---

### t_history
The struct `t_history` is used to build a liked list, storing all previous user input. Therefore it uses the generic linked list structure [`t_list`](#t_list). 
> :floppy_disk: &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :scroll:      &nbsp;  For further details about the history see the section [History](#history).
```
typedef struct s_history
{
    int         index;
    char        *inp;
    t_mbox      *mbox;
} t_history;
```  

---

### t_token
The struct `t_token` is used to build a liked list, storing all tokens.
> :floppy_disk: &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :scroll:      &nbsp;  For further details see the section [Tokenize](#tokenize).
```
typedef struct s_token
{
    int             type;
    char            *value;
    struct s_token  *next;
} t_token;
``````  

---

### t_ast
The struct `t_ast` is used to build a tree, storing all nodes.
> :floppy_disk: &nbsp;  The root of the ast is stored in the [`t_mbox`](#t_mbox) struct.\
> :scroll:      &nbsp;  For further details see the section [Parser](#parser).
```
typedef struct s_ast
{
    int             type;
    int             cmd_pos;
    char            *content;
    struct s_ast    *left;
    struct s_ast    *right;
} t_ast;
```

---

### t_list
The struct `t_list` is a generic linked list structure used for various purposes.
```
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

---

### t_exec
The struct `t_exec` is used to store all the information needed for the execution of a command.
> :floppy_disk: &nbsp;  An instance of this struct is stored in the [`t_mbox`](#t_mbox) struct.
```
typedef struct s_exec
{
    t_builtin_cmd   builtins[10];
    t_io            io;
    int             *pid;
    int             pid_index;
} t_exec;
```  

---

### t_io
The struct `t_io` is used to store all the information needed for the redirection of a command.
> :floppy_disk: &nbsp;  An instance of this struct is stored in the [`t_exec`](#t_exec) struct.\
> :scroll:      &nbsp;  For further details see the section [Redirections](#redirections).

```
typedef struct s_io
{
    t_bool  use_pipe[2];
    int     cmd_fd[2];
    int     dup_fd[2];
    int     prev_pipe[2];
} t_io;
```

---

### t_hd
The struct `t_hd` is used to store all the information needed for the heredoc redirection of a command.
> :scroll:      &nbsp;  For further details see the section [Here Documents](#here-documents).
```
typedef struct s_hd
{
    int     *fd;
    char    *lim;
    char    *cur_line;
} t_hd;
```

---

### t_builtin_cmd
The struct `t_builtin_cmd` is used to create a conection between a builtin command name and its corresponding function.
> :floppy_disk: &nbsp;  It is part of the [`t_exec`](#t_exec) struct.
```
typedef struct s_builtin_cmd
{
    char                *cmd_name;
    t_builtin_function  func_name;
} t_builtin_cmd;
```

---



# How frankenshell works
The main task of frankenshell can be grouped into steps:
- [Initialization](#initialization)
- Processing a Single Cycle
    - [Input Management](#input-management)
    - [Execution](#execution)
- [Termination](#termination)

Below you can find a detailed description of each step.
> :page_facing_up:  &nbsp; The file ['input_management.c'](../src/0_core/input_management.c) calls all the input management functions.

## Initialization
### Print Debug Info
If frankenshell is started with the flag `--info` or `-i`, it will print debug information during runtime.\
It will print the following information:
- Input States
    - the original input
    - the trimmed input
    - the shifted input
    - the expanded input
- Token List containing all tokens and their type
- AST Tree containing all nodes and their type

<details>
  <summary>Example <code>echo the home dir of $USER is storred in '$HOME'</code></summary>

  <pre><font color="#2AA1B3">frankenshell--&gt; </font>echo the home dir of $USER is storred in &apos;$HOME&apos;

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(echo the home dir of $USER is storred in &apos;$HOME&apos;)

input trimmed:			(echo the home dir of $USER is storred in &apos;$HOME&apos;)

input shifted:	shifted:	(echo�the�home�dir�of�$USER�is�storred�in��$HOME�)
		readable:	(echo_the_home_dir_of_$USER_is_storred_in_`$HOME`)
input expanded:	shifted:	(echo�the�home�dir�of�astein�is�storred�in��$HOME�)
		readable:	(echo_the_home_dir_of_astein_is_storred_in_`$HOME`)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(0) 	 token:(echo)
type:(0) 	 token:(the)
type:(0) 	 token:(home)
type:(0) 	 token:(dir)
type:(0) 	 token:(of)
type:(0) 	 token:(astein)
type:(0) 	 token:(is)
type:(0) 	 token:(storred)
type:(0) 	 token:(in)
type:(0) 	 token:($HOME)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

                                                               [arg] ($HOME)

                                                        [arg] (in)

                                                 [arg] (storred)

                                          [arg] (is)

                                   [arg] (astein)

                            [arg] (of)

                     [arg] (dir)

              [arg] (home)

       [arg] (the)

[cmd] (echo)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 1)             |</font>
 <font color="#26A269">----------------------------------------</font>
the home dir of astein is storred in $HOME
 <font color="#26A269">========================================</font>

<font color="#2AA1B3">frankenshell--&gt; </font>
</pre>

</details>

The ast tree is printed in a tree-like structure (left to right).The following example shows the ast tree of the input:\
`<< lol cat | wc -l | grep a > out | echo -n Hello World`
![Example][mindmap-ast-png]

## Input Management
All the following steps are executed for each cycle.


### Trim Input
First step is to trim the input. This means that all leading and trailing whitespaces are removed.
> :speech_balloon:  &nbsp; Start frankenshell with the flag `--info` to see the trimmed input during runtime.\

### Mark Separators

### Variable Expansion

#### Variable Expansion

#### Extract Limiter

### Tokenize

### Parse

## Execution

### Setup Execution

#### Setup Pipes

#### Setup Redirections

##### Heredoc

### Execute

## Termination





































































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

The builtin `42` displays a 42 logo to STDOUT (or its redirection)

<details>
  <summary>Attributes</summary>

| Attribute				| Details									|
|-----------------------|-------------------------------------------|
| Flags                 | `N/A`	                 					|
| Number of Arguments   | `0 to n` (all args will be ignored)   	|
| Exit Status           | `0`				           				|
| Affected Variables    | `[NONE]`			           				|
| File				    | [`42.c`](../src/3_builtins/42.c)			|

</details>

<details>
  <summary>Examples</summary>

| **CMD**            	| **STDOUT**    				| **Explanation**       	|
|-----------------------|-------------------------------|---------------------------|
| `42`					| [the 42 logo] 				|							|
| `42 foo bar`			| [the 42 logo] 				| all args will be ignored	|

</details>

<details>
  <summary>Screenshot</summary>

  ![42][builtin_42]  
</details>

---

#### cd

The builtin `cd` runs a few checks to ensure the provided path is valid. Once it's all good, it uses the external function `chdir` to change the current working directory (wd) to this new path. At the same time, it updates the `PWD` variable to the new directory and `OLDPWD` to the previous one.

<details>
  <summary>Attributes</summary>

| Attribute				| Details						|
|-----------------------|-------------------------------|
| Flags                 | `N/A`	                 		|
| Number of Arguments   | `0` - `1`				   		|
| Argument Format	   	| absolute or relative path	   	|
| Exit Status           | `0` `1`			           	|
| Affected Variables    | `HOME` `OLDPWD` `PWD`        	|
| File				    | [`cd.c`](../src/3_builtins/cd.c)|


</details>

<details>
  <summary>Examples</summary>

| **CMD**          	| **STDERR** 												|**Exit Status**| **Explanation**       			 		| **Affected Variables**<sup>1</sup>	|
|-------------------|-----------------------------------------------------------|:-------------:|-------------------------------------------|---------------------------------------|
| `cd`				| 															| `0`		 	| if `HOME` **is** set 						| `HOME` **`OLDPWD`** **`PWD`**			|
| `cd`				| `cd: HOME not set`										| `1`		 	| if `HOME` **is not** set					| 										|
| `cd ""`			| 															| `0`		 	| empty argument; <br> wd doesn't update	| 										|
| `cd valid_path`	| 															| `0` 		 	| wd updates to <br> `./valid_path`			| **`OLDPWD`** **`PWD`**				|
| `cd .`			| 															| `0` 		 	| wd doesn't update; <br> `OLDPWD` updated!	| **`OLDPWD`**							|
| `cd ..`			| 															| `0` 		 	| wd updates to <br> parent folder			| **`OLDPWD`** **`PWD`**				|
| `cd foo bar`		| `cd: too many arguments`									| `1`			|											|			 							|
| `cd noExist`		| `frankenshell: cd: noExist: No such file or directory`	| `1` 			|											|			 							|
| `cd noPermDir`	| `frankenshell: cd: noPermDir: Permission denied`			| `1` 			|											|			 							|
| `cd file`			| `frankenshell: cd: file: Not a directory`					| `1` 			|											|			 							|

<sup>1</sup> Bold variables will be updated.

</details>

:warning:	 		&nbsp; If the external function `chdir` fails, an error message is printed and the exit status is set to `1`.\
:white_check_mark: 	&nbsp; If `PWD` and/or `OLDPWD` are absent, the function operates normally and skips setting these variables.

---

#### echo

The builtin `echo` outputs the strings it is given as arguments, seperated by one space each, to the standard output (or its redirection).

<details>
  <summary>Attributes</summary>

| Attribute				| Details						|
|-----------------------|-------------------------------|
| Flags                 | `-n`		                 	|
| Number of Arguments   | `0` - `n`					  	|
| Argument Format	   	| all ASCII chars allowed		|
| Exit Status           | `0`				           	|
| Affected Variables    | `[NONE]`			       		|
| File				    | [`echo.c`](../src/3_builtins/echo.c)	|


</details>

<details>
  <summary>Examples</summary>

| **CMD**            	| **STDOUT**    | **LINEBREAK** 	|
|-----------------------|---------------|:-----------------:|
| `echo foo`	     	| `foo`			| :white_check_mark:|
| `echo "" '' foo`	    | `  foo`		| :white_check_mark:|
| `echo --n foo`  		| `--n foo`    	| :white_check_mark:|
| `echo -n foo`  		| `foo`       	| :x:       	  	|
| `echo -n -nn -nnn foo`| `foo`       	| :x:       	  	|
| `echo -n -nbar foo`  	| `-nbar foo`   | :x: 	    	 	|
| `echo -n foo -n`  	| `foo -n`      | :x:   			|

</details>

---

#### env

The builtin `env` outputs all variable key-value pairs of the linked list like `key=value\n`

<details>
  <summary>Attributes</summary>

| Attribute				| Details						|
|-----------------------|-------------------------------|
| Flags                 | `N/A`		                 	|
| Number of Arguments   | `0`						  	|
| Exit Status           | `0` `127`			           	|
| Affected Variables    | `[all]`			       		|
| File				    | [`env.c`](../src/3_builtins/env.c) |

</details>

<details>
  <summary>Examples</summary>

| **CMD**            	| **STDOUT** 	| **STDERR** 															| **Exit Status**	|
|-----------------------|---------------|-----------------------------------------------------------------------|:-----------------:|
| `env`			     	| `...` <br> `USER=astein` <br> `HOME=/home/astein` <br> `LANGUAGE=en` <br> `...`	   || `0`	 			|
| `env foo`		     	| 				| `env: ‘foo’: No such file or directory`								| `127`				|
| `env foo bar`	     	| 				| `env: ‘foo’: No such file or directory`								| `127`				|

</details>

:scroll: 		&nbsp; Refer to the section [Environment Variables](#environment-variables) for more details about the variables.
:warning: 		&nbsp; A [known bug](#known-bugs) exists with `env` and `export`.

---

#### exit

The builtin `exit` terminates the calling process, outputs `exit` to `STDERR` and if provided with a numeric argument, it sets the exit status to that argument's value.

<details>
  <summary>Attributes</summary>

| Attribute				| Details						|
|-----------------------|-------------------------------|
| Flags                 | `N/A`	                 		|
| Number of Arguments   | `0` - `1`				   		|
| Argument Format	   	| numeric [max long long]	   	|
| Exit Status           | `0` - `255`		           	|
| Affected Variables    | `[NONE]`			           	|
| File				    | [`exit.c`](../src/3_builtins/exit.c) |


</details>

<details>
  <summary>Examples</summary>

| **CMD**          	| **STDERR** 														|**Exit Status**    | **Terminates**		|
|-------------------|-------------------------------------------------------------------|:-----------------:|:---------------------:|
| `exit`			| `exit`															| `[doesn't update]`| :white_check_mark: 	|
| `exit 42`			| `exit`															| `42`				| :white_check_mark: 	|
| `exit -42`		| `exit`															| `214`			 	| :white_check_mark: 	|
| `exit 424242`		| `exit`															| `50`				| :white_check_mark: 	|
| `exit foo`		| `exit` <br> `frankenshell: exit: foo: numeric argument required`	| `2`				| :white_check_mark: 	|
| `exit foo 42`		| `exit` <br> `frankenshell: exit: foo: numeric argument required`	| `2`				| :white_check_mark: 	|
| `exit foo bar`	| `exit` <br> `frankenshell: exit: foo: numeric argument required`	| `2`				| :white_check_mark: 	|
| `exit 42 42`		| `exit` <br> `frankenshell: exit: too many arguments`				| `1`<sup>1</sup>	| :x:				 	|
| `exit 42 foo`		| `exit` <br> `frankenshell: exit: too many arguments`				| `1`<sup>1</sup>	| :x:				 	|

<sup>1</sup> The exit status will only be updated to `1` if the last exit status was `0`.

</details>

> :speech_balloon: &nbsp; If the argument exceeds 255, it will be subjected to modulo 256.

---

#### export

The builtin `export` updates (or creates) the enviromental variables inputed as key value pairs like `key1=value1 key2=value2`. If no argument is given, it will instead output all variables in alphabetical order.

<details>
  <summary>Attributes</summary>

| Attribute				| Details						|
|-----------------------|-------------------------------|
| Flags                 | `N/A`		                 	|
| Number of Arguments   | `0` - `n`					  	|
| Argument Format	   	| `key=value`					|
| Exit Status           | `0` `1`			           	|
| Affected Variables    | `[key]`			       		|
| Files				    | [`export.c`](../src/3_builtins/export.c) <br> [`export_utils.c`](../src/3_builtins/export_utils.c) |


</details>

<details>
  <summary>Examples</summary>

| **CMD**            		|**Equal Sign**		 |**Valid Key**<sup>1</sup>| **STDOUT**|**STDERR**|**Exit Status**    | **Affected Variables**<sup>2</sup>	|
|---------------------------|:------------------:|:-----------------------:|-----------|----------|:-----------------:|---------------------------------------|
| `export`		     		|			   		 |			 		  	   | `...` <br> `declare -x LANG="en_US.UTF-8"` <br> `declare -x LANGUAGE="en"` <br> `...` <sup>3</sup>|| `0` ||
| `export @`				| :x:		   		 | :x:				  	   |		   | ```frankenshell: export: `@': not a valid identifier``` 	| `1` ||
| `export @=foo`			| :white_check_mark: | :x:		 		  	   |		   | ```frankenshell: export: `@=foo': not a valid identifier```| `1` ||
| `export foo`				| :x:		   		 | :white_check_mark: 	   |		   |		  | `0` 			  |										|
| `export foo=bar`			| :white_check_mark: | :white_check_mark: 	   |		   |		  | `0` 			  |	**`foo`** 							|
| `export foo=bar school=42`| :white_check_mark: | :white_check_mark: 	   |		   |		  | `0` 			  |	**`foo`** **`school`**				|

<sup>1</sup> Refer to the section [Environment Variables](#environment-variables) for more details about the key syntax.\
<sup>2</sup> Bold variables will be updated.\
<sup>3</sup> In alphabetical order.

</details>

:scroll: 		&nbsp; Refer to the section [Environment Variables](#environment-variables) for more details about the variables.
:warning: 		&nbsp; A [known bug](#known-bugs) exists with `env` and `export`.

---

#### history

The builtin `history` outputs all previous user input in a numbered list.

<details>
  <summary>Attributes</summary>

| Attribute				| Details						|
|-----------------------|-------------------------------|
| Flags                 | `N/A`		                 	|
| Number of Arguments   | `0 to n` (all args will be ignored) |
| Exit Status           | `0`			           		|
| File				    | [`history.c`](../src/3_builtins/history.c) |

</details>

<details>
  <summary>Examples</summary>

| **CMD**            		| **STDOUT**					  |
|---------------------------|---------------------------------|
| `history`		     		| `  1  echo hi` <br> `  2  ls` <br> `...` <br> `  n  history`|
| `history foo bar`			| `  1  echo hi` <br> `  2  ls` <br> `...` <br> `  n  history`|

</details>

---

#### pwd

The builtin `pwd` outputs the current wd using the external function 'getcwd'. Like in bash all arguments will be ignored.

<details>
  <summary>Attributes</summary>

| Attribute				| Details									|
|-----------------------|-------------------------------------------|
| Flags                 | `N/A`	                 					|
| Number of Arguments   | `0 to n` (all args will be ignored)   	|
| Exit Status           | `0`				           				|
| Affected Variables    | `[NONE]`			           				|
| File				    | [`pwd.c`](../src/3_builtins/pwd.c)		|


</details>

<details>
  <summary>Examples</summary>

| **CMD**            	| **STDOUT**    				| **Explanation**       	|
|-----------------------|-------------------------------|---------------------------|
| `pwd`					| `/mnt/daten/GIT/frankenshell` |							|
| `pwd foo bar`			| `/mnt/daten/GIT/frankenshell` | all args will be ignored	|

</details>

---

#### unset

The builtin `unset` deletes the corresponding variables.

<details>
  <summary>Attributes</summary>

| Attribute				| Details									|
|-----------------------|-------------------------------------------|
| Flags                 | `N/A`	                 					|
| Number of Arguments   | `0 to n`									|
| Argument Format	   	| `key`										|
| Exit Status           | `0`				           				|
| Affected Variables    | `[key]`			           				|
| File				    | [`unset.c`](../src/3_builtins/unset.c)	|

</details>

<details>
  <summary>Examples</summary>

| **CMD**            	| **Explanation**       						|**Exit Status**|  **Affected Variables**	|
|-----------------------|-----------------------------------------------|---------------|---------------------------|
| `unset`				| nothing happens								| `0`			|							|
| `unset foo bar`		|the variables `foo` and `bar` will be deleted	| `0`			| `foo` `bar`				|

</details>

:scroll: 		&nbsp; Refer to the section [Environment Variables](#environment-variables) for more details about the variables.

---

## Environment Variables
On programm start the enviromental variables will be loaded into frankenshell.\
With the following [builtin](#builtins) commands variables can be...
- **shown** using [env](#env)
- **sorted and shown**  using [export](#export) without arguments
- **created** using [export](#export)
- **changed** using [export](#export)
- **deleted** using [unset](#unset)

> ℹ️ &nbsp; Keep in mind that some [builtins](#builtins) (e.g. [cd](#cd)) change some variables during runtime!

## Known Bugs

**export vs env**

If the built-in export is called with a valid key but no equal sign (like `export foo`) `foo` should be listed in the output of the `export`, but not in the output of the `env` function call. In frankenshell, `foo` is not added to the linked list of variables and therefore is not printed in either case. A simple boolean in the `s_env` structure could solve the problem.

---

**single cmds with redirs**

---

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
[mindmap-ast-png]: /images/mindmap-ast.png