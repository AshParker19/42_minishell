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
3. [Usage](#usage)
4. [Definitions](#definitions)
5. [Structs](#structs)
	[[t_mbox](#t_mbox), 
	[t_env](#t_env), 
	[t_history](#t_history), 
	[t_token](#t_token), 
	[t_ast](#t_ast), 
	[t_list](#t_list), 
	[t_exec](#t_exec), 
	[t_io](#t_io), 
	[t_hd](#t_hd), 
	[t_builtin_cmd](#t_builtin_cmd)]
6. [How frankenshell works](#how-frankenshell-works)
   1. [Initialization](#initialization)
       1. [Info Mode](#info-mode)
   2. [Processing a Single Cycle](#processing-a-single-cycle)
       1. [Input Management](#input-management)
           1. [Trim Input](#trim-input)
           2. [Mark Empty Quotes](#mark-empty-quotes)
           2. [Shift Separators](#shift-separators)
               1. [Quoting](#quoting)
           3. [Variable Expansion](#variable-expansion)
               1. [Variable Expansion](#variable-expansion-1)
               2. [Extract Limiter](#extract-limiter)
           4. [Tokenizing](#tokenizing)
           5. [Parsing](#parsing)
   3. [Execution](#execution)
       1. [Setup Execution](#setup-execution)
           1. [Setup Pipes](#setup-pipes)
           2. [Setup Redirections](#setup-redirections)
               1. [Heredoc](#heredoc)
       2. [Execute](#execute)
   4. [Termination](#termination)
       1. [Exit Status](#exit-status)
       2. [Signals](#signals)
7. [Builtin Commands](#builtin-commands)
	[[42](#42-builtin), 
	[cd](#cd-builtin), 
	[echo](#echo-builtin), 
	[env](#env-builtin), 
	[exit](#exit-builtin), 
	[export](#export-builtin), 
	[history](#history-builtin), 
	[pwd](#pwd-builtin), 
	[unset](#unset-builtin)]
8. [Environment Variables](#environment-variables)
9. [Known Bugs](#known-bugs)
10. [Acknowledgments](#acknowledgments)


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
        4. [Tokenize](#tokenizing)
        5. [Parsing](#parsing)
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
The following emoji are used in this file:
| Emoji             | Meaning   |
| :---:             | ---       |
| :arrow_right:     | link to another chapter  |
| :page_facing_up:  | link to a code file           |
| :bulb:          	| hint		                    |
| :jigsaw:          | part of                       |



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
see [ast](#ast)
#### ast
The parser in Frankenshell constructs an abstract syntax tree (AST). For more in-depth information on this subject, refer to the [Parser](#parser) chapter.

## Structs
### t_mbox
The struct `mbox` is the main structure of the program: it is being passed as an argument to most of the functions and contains all the info needed for the program to work.
> :page_facing_up:  &nbsp; The file ['manage_mbox.c'](../src/0_core/manage_mbox.c) contains the functions for initializing and destroying the mbox instance.
```
typedef struct s_mbox
{
	char						*inp_orig;
	char						*inp_trim;
	char						*inp_shift;
	char						*inp_expand;
	int							consecutive_lt;
	bool						error_status;
	t_env						*env;
	t_list						*history_lst;
	t_token						*tokens;
	t_token						*tmp_token;
	t_ast						*ast;
	t_ast						*tmp_node;
	t_exec						exec;
	int							count_cycles;
	t_bool						info_mode;
} t_mbox;
```
TODO STRUCT CHANGED! 
---

### t_env
The struct `t_env` is used to build a liked list, storing all (enviromental) variables.
> :jigsaw:      &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :arrow_right:      &nbsp;  For further details see the section [Environment Variables](#environment-variables).
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
> :jigsaw:      &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :arrow_right:      &nbsp;  For further details about the history see the section [History](#history-builtin).
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
> :jigsaw:      &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :arrow_right:      &nbsp;  For further details see the section [Tokenize](#tokenizing).
```
typedef struct s_token
{
    int             type;
    char            *value;
    struct s_token  *next;
} t_token;
```

---

### t_ast
The struct `t_ast` is used to build a tree, storing all nodes.
> :jigsaw:      &nbsp;  The root of the ast is stored in the [`t_mbox`](#t_mbox) struct.\
> :arrow_right:      &nbsp;  For further details see the section [Parser](#parser).
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
> :jigsaw:      &nbsp;  An instance of this struct is stored in the [`t_mbox`](#t_mbox) struct.
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
> :jigsaw:      &nbsp;  An instance of this struct is stored in the [`t_exec`](#t_exec) struct.\
> :arrow_right:      &nbsp;  For further details see the section [Redirections](#redirections).

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
> :arrow_right:      &nbsp;  For further details see the section [Here Documents](#here-documents).
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
> :jigsaw:  &nbsp;  It is part of the [`t_exec`](#t_exec) struct.
```
typedef struct s_builtin_cmd
{
    char                *cmd_name;
    t_builtin_function  func_name;
} t_builtin_cmd;
```

---



## How frankenshell works
The main task of frankenshell can be grouped into those steps:
- [Initialization](#initialization)
- Processing a Single Cycle
    - [Input Management](#input-management)
    - [Execution](#execution)
- [Termination](#termination)

Below you can find a detailed description of each step.
> :page_facing_up:  &nbsp; The file ['input_management.c'](../src/0_core/input_management.c) calls all the input management functions.

### Initialization

On startup the program will initialize the [`t_mbox`](#t_mbox) struct. This struct contains all the information needed for the program to work. It is passed as an argument to most of the functions.\
The following steps are executed during initialization:
- creating a [t_env](#t_env) linked list for the [environment variables](#environment-variables)
- creating a [t_builtin_cmd](#t_builtin_cmd) array for the [builtin commands](#builtin-commands)
- ini

> :page_facing_up:  &nbsp; The file ['manage_mbox.c'](../src/0_core/manage_mbox.c) contains the functions for initializing and destroying the mbox instance.

#### Info Mode
To activate the info mode you can
- start frankenshell with the flag `--info` or `-i`
- run the [builtin command](#builtin-commands) [`infomode`](#infomode-builtin)

If the info mode is activated frankenshell will print the following information during runtime.:
started with the flag `--info` or `-i`, it will

| Input String  | Example                                               |
|---------------|-------------------------------------------------------|
| original      | `echo "Hello" $USER "" '!' \| wc    -l     `          |
| trimmed       | `echo "Hello" $USER "" '!' \| wc -l`                  |
| empty quotes  | `echo "Hello" $USER E_ '!' \| wc    -l`               |
| shifted       | `echo_DHelloD_$USER_E__S!S_P_wc____-l`                |
| expanded      | `echo_DHelloD_astein_E__S!S_P_wc____-l`               |

- Token list containing all tokens and their type
- AST containing all nodes and their type

##### Readable Input String
To get a 'readable' Version of the input strings, their [shifted values](#shift-separators) will be displayed like:
- `S` for `'` (contextual single quote)
- `D` for `"` (contextual double quote)
- `P` for `|` (seperating pipe)
- `I` for `<` (redirection in)
- `O` for `>` (redirection out)
- `_` (space that can be removed)
- `E` ('empty token' flag to inform the tokenizer that it should generate an empty token)
> :page_facing_up:  &nbsp; check out the `shift_readable` function in [TODO.c](../src/0_core/TODO.c)\
> :jigsaw: &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\
> :jigsaw: &nbsp;  The linked list is stored in the [`t_mbox`](#t_mbox) struct.\

TODO: UPDATE THE EXAMPLES SINCE I CHANGED THE DEBUG INFO LAYOUT
<details>
  <summary>Example <code>echo "Hello" $USER "" '!' | wc    -l&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</code></summary>

</details>

<details>
  <summary>Example <code>ls -l -a</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>ls -l -a

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(ls -l -a)

input trimmed:			(ls -l -a)

input shifted:	shifted:	(ls�-l�-a)
		readable:	(ls_-l_-a)
input expanded:	shifted:	(ls�-l�-a)
		readable:	(ls_-l_-a)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(0) 	 token:(ls)
type:(0) 	 token:(-l)
type:(0) 	 token:(-a)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

              [arg] (-a)

       [arg] (-l)

[cmd] (ls)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 1)             |</font>
 <font color="#26A269">----------------------------------------</font>
total 288
drwxrwxr-x 10 astein astein   4096 Dez 16 23:04 .
drwxrwxr-x  3 astein astein   4096 Dez 15 14:03 ..
-rwxrwxr-x  1 astein astein   6323 Dez 15 20:15 art.sh
-rwxrwxr-x  1 astein astein   1498 Dez 15 20:03 count_stats.sh
drwxrwxr-x  3 astein astein   4096 Dez 15 20:03 docs
-rwxrwxr-x  1 astein astein 214360 Dez 16 23:04 frankenshell
drwxrwxr-x  8 astein astein   4096 Dez 17 01:58 .git
-rw-rw-r--  1 astein astein    215 Dez 15 20:03 .gitignore
drwxrwxr-x  2 astein astein   4096 Dez 17 01:44 images
drwxrwxr-x  2 astein astein   4096 Dez 15 20:03 includes
drwxrwxr-x  4 astein astein   4096 Dez 16 23:04 libft
-rw-rw-r--  1 astein astein   3841 Dez 15 20:30 Makefile
drwxrwxr-x  6 astein astein   4096 Dez 16 23:04 obj
-rw-rw-r--  1 astein astein   4768 Dez 16 23:14 README1.md
-rw-rw-r--  1 astein astein   2797 Dez 16 15:22 README.md
drwxrwxr-x  7 astein astein   4096 Dez 15 20:03 src
-rw-rw-r--  1 astein astein     46 Dez 16 18:08 todo.txt
drwxrwxr-x  2 astein astein   4096 Dez 15 20:22 .vscode
 <font color="#26A269">========================================</font>

<font color="#2AA1B3">frankenshell--&gt; </font>
</pre>

</details>

<details>
  <summary>Example <code>echo the home dir of $USER is storred in '$HOME'</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>echo the home dir of $USER is storred in &apos;$HOME&apos;

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

<details>
  <summary>Example <code><< $DONT_EXPAND cat | wc -l</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>&lt;&lt; $DONT_EXPAND cat | wc -l

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(&lt;&lt; $DONT_EXPAND cat | wc -l)

input trimmed:			(&lt;&lt; $DONT_EXPAND cat | wc -l)

input shifted:	shifted:	(���$DONT_EXPAND�cat���wc�-l)
		readable:	(II_$DONT_EXPAND_cat_P_wc_-l)
input expanded:	shifted:	(��$DONT_EXPAND�cat���wc�-l)
		readable:	(II$DONT_EXPAND_cat_P_wc_-l)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(2) 	 token:(&lt;)
type:(2) 	 token:(&lt;)
type:(0) 	 token:($DONT_EXPAND)
type:(0) 	 token:(cat)
type:(1) 	 token:(|)
type:(0) 	 token:(wc)
type:(0) 	 token:(-l)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

              [arg] (-l)

       [cmd] (wc)

[|] (|)

       [cmd] (cat)

              [&lt;&lt;] ($DONT_EXPAND)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 2)             |</font>
 <font color="#26A269">----------------------------------------</font>
<font color="#A2734C">frankendoc&gt; </font>
</pre>

</details>

<details>
  <summary>Example <code>echo hi"" "" "" ""there</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>echo hi&quot;&quot; &quot;&quot; &quot;&quot; &quot;&quot;there

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(echo hi&quot;&quot; &quot;&quot; &quot;&quot; &quot;&quot;there)

input trimmed:			(echo hi&quot;&quot; &quot;&quot; &quot;&quot; &quot;&quot;there)

input shifted:	shifted:	(echo�hi�����������there)
		readable:	(echo_hiDD_E__E__DDthere)
input expanded:	shifted:	(echo�hi�����������there)
		readable:	(echo_hiDD_E__E__DDthere)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(0) 	 token:(echo)
type:(0) 	 token:(hi)
type:(0) 	 token:()
type:(0) 	 token:()
type:(0) 	 token:(there)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

                            [arg] (there)

                     [arg] ()

              [arg] ()

       [arg] (hi)

[cmd] (echo)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 1)             |</font>
 <font color="#26A269">----------------------------------------</font>
hi   there
 <font color="#26A269">========================================</font>

<font color="#2AA1B3">frankenshell--&gt; </font>
</pre>

</details>

> :arrow_right: &nbsp; Refer to the section [Parsing](#parsing) for a better understanding of the ast.


### Input Management
All the following steps are executed for each cycle.


#### Trim Input
First step is to trim the input. This means that all leading and trailing whitespaces are removed.
> :bulb:  &nbsp; Start frankenshell with the flag `--info` to see the trimmed input string during runtime.\

#### Mark Empty Quotes
Bash generates an empty token for a pair of empty quotes if the two conditions are met:
- the empty quotes are not inside another pair of quotes\
(refer to `OUT_Q` as the [quote state](#quote-state))
- the empty quotes are surrounded by at least one whitespace character (or the beginning/end of the string) before and after 

Empty quotes will be marked as `EMPTY_TOKEN` and `NO_SPACE` characters.
> :arrow_right: &nbsp; Refer to the section [Shift Separators](#shift-separators) for a better understanding of the marked input string.

Examples
| inp_trim		        | inp_eq            | empty quotes      |    
| ----------------------|-------------------|:-----------------:|
| `echo ""`			    | `echo E_`         | :white_check_mark:|
| `echo ''`			    | `echo E_`         | :white_check_mark:|
| `echo """"`			| `echo E___`       | :white_check_mark:|
| `echo "" "" "'hi"`    | `echo E_ E_ "'hi"`| :white_check_mark:|
| `echo hi""`			| `echo hi""`       | :x:               |
| `echo hi''`			| `echo hi''`       | :x:               |
| `echo ""hi`			| `echo ""hi`       | :x:               |
| `echo ''hi`			| `echo ''hi`       | :x:               |
| `echo '""'`			| `echo '""'`       | :x:               |
| `echo "''"`			| `echo "''"`       | :x:               |

> :arrow_right: &nbsp; Refer to the section [Readble Input String](#readable-input-string) for a better understanding of the marked input string.\
> :bulb:        &nbsp; Start frankenshell with the flag `--info` to see the marked input string during runtime.

#### Shift Separators
This step is used to mark all seperators in the input string. This is needed for the [tokenization](#tokenizing) and [parsing](#parsing).
##### Quotes
- **Single Quotes**: Enclosing text in single quotes (`'`) prevents the shell from interpreting any metacharacters within the quoted sequence.
- **Double Quotes**: Using double quotes (`"`) also prevents interpretation of metacharacters, except for the dollar sign (`$`), which is used for variable expansion.

Specail Case:
...

> ℹ️ &nbsp; Unclosed quotes (e.g. ```echo "Hello World```) will result in an error:\
> ⚠️ &nbsp; frankenshell: syntax error: unclosed quotes

###### Quote State
While traversing the input string, the `quote state` will be updated for each character. So if a seperating character is found it will be only marked if the `quote state` is OUT__QUOTE.
Examples:
```
Trimmed String:	echo "Hello 'astein', how are you?"
Quote State: 	OOOOODDDDDDDDDDDDDDDDDDDDDDDDDDDDDO
Marked String:	echo DHello 'astein', how are you?D
Explanation:	The single quote is inside a double quote, so it will be ignored.
```

> :bulb:  &nbsp; Start frankenshell with the flag `--info` to see the marked input string during runtime.\

#### Variable Expansion

The **Variable Expansion** works simmilar like in bash:

| Command            | Expand       | Output                        |
| ----------------- | :----------: | ----------------------------- |
| `echo $USER`       |      ✅        |      `current_user_value`      |
| `echo "$USER"`     |      ✅        |      `current_user_value`      |
| `echo '$USER'`     |      ❌        |      `$USER`                   |
| `<< $USER cat`     |      ❌        |  Won't expand, so the `EOF` of the heredoc will be `$USER` |

Special Cases
Table with $?, $Space $"", Herdeoc refer to next section and so on, expansion in herdoc refer to heredoc

> :arrow_right: &nbsp; Refer to the section [Quotes](#quotes) for a better understanding of variable expansion inside quotes.

##### Extract Limiter

special case var expansion in heredoc limiter doesnt work

> :bulb:  &nbsp; Start frankenshell with the flag `--info` to see the expanded input string during runtime.\

#### Tokenizing

The expanded input string will be tokenized. This means that the input string will be split into tokens. Each token will be marked with a type. The following table shows all possible token types:
...
Examples
```
Expanded String:	TODO
Tokens:				`ls`(arg); `-l`(arg); `-a`(arg); `|`(pipe); `wc`(cmd); `-l`(arg)
```

> :bulb:  &nbsp; Start frankenshell with the flag `--info` to see the token list during runtime.\

#### Parsing
After tokienizing the input string, the tokens will be parsed into an ast. The ast tree is used for the execution of the commands.
Each node of the ast tree is an instance of the [t_ast](#t_ast) struct. It therefore has a type, a content and a two pointers to its left and right child node.
This table shows all possible node types and their possible node conections:
| Node Type | Left Child | Right Child |
| --------- | ---------- | ----------- |
| `PIPE`	| `CMD`		 | `PIPE` `CMD`|
| `CMD`     | `REDIR` `NULL`    | `ARG` `NULL`|
| `REDIR`	| `REDIR` `NULL`	| `NULL`      |
| `ARG`     | `NULL`     | `ARG` `NULL`|

To achive this we used a modified version of TODOs logic. Below u find the BNF Notion
TODO BNF

The ast tree is shown in a tree-like structure (left to right). The following example shows the ast tree of the input:\
`<< lol cat | wc -l | grep a > out | echo -n Hello World`

![Example][mindmap-ast-png]

> :bulb:  &nbsp; Start frankenshell with the flag `--info` to see the ast tree during runtime.\


### Execution
The executor traverses the ast tree always from **left to right**. This ensures that pipes and redirections will always be setup before any command is executed.
All commands are executed in a child process.
Exception: Single Builtin cmds (refer to bugs)

All childs will be spawn right after each other (so before the previous child is finished). The parent process waits (because of the open pipe fd) until the child process is finished.
Exception: Heredoc

The parent waits for all childs to finish before it continues with the next cycle. Each time a child process is finished, the parent process updates the exit status of the last child process. (TODO check if this is true and link to chapter exit status).

#### Setup Execution

##### Setup Pipes

Pipes (`|`) allow the output of one command to be used as input for another, enabling command chaining.

> :exlamation:  &nbsp; Note that the redirction into the pipe might be overwritten by the [redirection of the command itself](#setup-redirections).

##### Setup Redirections

The table below describes the redirection features available in frankenshell:
| Feature| Mode            | Description                                                                                | Example                           |
|------|-------------|--------------------------------------------------------------------------------------------------|-----------------------------------|
| `<`  |Input Redirection         | Redirects input from a file to a command.                                           | `wc < file.txt`              |
| `<<` |Heredoc                   | Allows inputting multiple lines until a termination string is reached.              | `<< this_exits_the_hd wc`                  |
| `>`  |Output Redirection        | Redirects the output of a command to a file, overwriting it if it already exists.   | `echo "replace by foo" > file.txt`              |
| `>>` |Append Output Redirection | Appends command output to a file, creating it if it doesn't exist.                  | `echo "append foo" >> file.txt`

These redirections allow for flexible manipulation of command input and output, similar to standard bash functionality.


###### Heredoc

The heredoc redirection allows inputting multiple lines until a termination string is reached or an EOF is sent via CTRL+D. The herdoc runs always in a child process and is connected to the command with a pipe. The herdoc uses `readline` to read the user input.

If the heredoc recives an EOF, it will output the following error message:
> ⚠️ &nbsp; frankenshell: TODO

Variable expansion inside the herdoc is supported. Therefore each line of the heredoc will be expanded before it is sent to the pipe. TODO check if true.
NOTE: the expansion, like in bash, is not supposed to work if the heredoc limmite is enclosed in single quotes. TODO CHECK IF ALSO DOUBLE QUOTES?
EXAMPLE TABLE
...

##### Run CMD


###### Run Builtin 

TODO check out all builtins in the section

###### Run Executable 

the env linked list is send to execv

### Termination

#### Exit Status
The current exit status of minishell is stored as an node with the key `?` in the variable linkes list. This simplyfies the variable expansion of `$?`. To update the value the noraml `TODO` function can be used. Since the value is an `char*` and the exit status is an integer there is a function `TODO` that allows an integer as a paramter to update the value of the node.
Anyhow if the linked list is used for `execve`, `env` or `export` the `?` node will be ignored.

### Signals

Each time a fork is happening all existing processes will be set to a specific 'signal status' via 'conf_sig_handler' in TODO File. This status will
be used to determine which signal handling should be used in the calling process.

The following Signals are being treaded in frankenshell:
Table
| Shortcut | Signal Name | Description 						|
|:--------:|:-----------:|-------------						|
| `CTRL+C` | SIGINT      | Interrupt signal					|
| `CTRL+\` | SIGQUIT     | Quit signal 						|
| `CTRL+D` | EOF	     | An EOF is send to the input fd 	|

The following table shows all possible signal states defined in TODO enum file:
| Signal State | Description 						| `CTRL+C` | `CTRL+\` | `CTRL+D` |
|--------------|-------------						|----------|----------|----------|
| `SIG_STATE_MAIN`    | showing basic promt				| |||

TODO

	SIG_STATE_MAIN     showing basic promt
	SIG_STATE_PARENT   ignore all signals
	SIGNAl_CHILD    basic setup for child
	SIG_STATE_HD_CHILD  for heredoc

	SIG_STATE_MAIN,
	SIG_STATE_PARENT,
	SIG_STATE_CHILD,
	SIG_STATE_CHILD_BUILTIN,
	SIG_STATE_HD_CHILD,
	SIG_STATE_IGNORE
 

## Builtin Commands
Each built-in command in frankenshell is detailed below with specific information and examples.

| Command                         | File(s)     	                                      												| Description									|
|---------------------------------|-----------------------------------------------------------------------------------------------------|-----------------------------------------------|
| [`42`](#42-builtin)             | [`42.c`](../src/3_builtins/42.c)                    												| 42 it is ;)                                 	|
| [`cd`](#cd-builtin)             | [`cd.c`](../src/3_builtins/cd.c)                    												| Changes the current directory.              	|
| [`echo`](#echo-builtin)         | [`echo.c`](../src/3_builtins/echo.c)                												| Displays a line of text.                    	|
| [`env`](#env-builtin)           | [`env.c`](../src/3_builtins/env.c)                  												| Displays the environment variables.         	|
| [`exit`](#exit-builtin)         | [`exit.c`](../src/3_builtins/exit.c)                												| Exits the shell.                            	|
| [`export`](#export-builtin)     | [`export.c`](../src/3_builtins/export.c)<br>[`export_utils.c`](../src/3_builtins/export_utils.c)	| Sets or exports environment variables.      	|
| [`help`](#help-builtin)         | [`help.c`](../src/3_builtins/help.c)                												| Displays this documentation page on github  	|
| [`history`](#history-builtin)   | [`history.c`](../src/3_builtins/history.c)          												| Displays the command history.               	|
| [`infomode`](#infomode-builtin) | [`infomode.c`](../src/3_builtins/infomode.c)        												| Toggles the info mode.                      	|
| [`pwd`](#pwd-builtin)           | [`pwd.c`](../src/3_builtins/pwd.c)                  												| Prints the working directory.               	|
| [`unset`](#unset-builtin)       | [`unset.c`](../src/3_builtins/unset.c)              												| Unsets environment variables.               	|



---

#### 42 (builtin)

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

#### cd (builtin)

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

#### echo (builtin)

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

#### env (builtin)

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

:arrow_right: 		&nbsp; Refer to the section [Environment Variables](#environment-variables) for more details about the variables.\
:warning: 		&nbsp; A [known bug](#known-bugs) exists with `env` and `export`.

---

#### exit (builtin)

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

#### export (builtin)

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

> :arrow_right: 	&nbsp; Refer to the section [Environment Variables](#environment-variables) for more details about the variables.\
> :warning: 		&nbsp; A [known bug](#known-bugs) exists with `env` and `export`.

#### help (builtin)

The builtin `help` displays the documentation page on github.

<details>
  <summary>Attributes</summary>

| Attribute				| Details						                |
|-----------------------|-----------------------------------------------|
| Flags                 | `N/A`		                 	                |
| Number of Arguments   | `0 to n` (all args will be ignored)           |
| Exit Status           | `N/A`			           		                |
| File				    | [`help.c`](../src/3_builtins/help.c)          |

</details>

<details>
  <summary>Examples</summary>

| **CMD**       | **Explanation**       	|
|---------------|---------------------------|
| `help`		| opens the documentation 	|

</details>

---

#### history (builtin)

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

#### infomode (builtin)

The builtin `infomode` toggles the info mode feature.

> :arrow_right: &nbsp; Refer to the section [Info mode](#info-mode) for more details about the info mode.

<details>
  <summary>Attributes</summary>

| Attribute				| Details						                |
|-----------------------|-----------------------------------------------|
| Flags                 | `N/A`		                 	                |
| Number of Arguments   | `0 to n` (all args will be ignored)           |
| Exit Status           | `0`			           		                |
| File				    | [`infomode.c`](../src/3_builtins/infomode.c)  |

</details>

<details>
  <summary>Examples</summary>

| **CMD**       | **STDERR**				|
|---------------|---------------------------|
| `infomode`	| `INFO MODE ACTIVATED!`    |
| `infomode`    | `INFO MODE DEACTIVATED!`  |

</details>

---

#### pwd (builtin)

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

#### unset (builtin)

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

> :arrow_right: 		&nbsp; Refer to the section [Environment Variables](#environment-variables) for more details about the variables.

---

## Environment Variables
On programm start a [t_env](#t_env) linked list will be created from the enviromental variables and stored in the [t_mbox](#t_mbox) struct.

> :page_facing_up: 	&nbsp; All related functions are in the [a_env_vars.c](../src/1_core/d_env_vars.c) file.

The following functions are implemented:
```
// MANAGEMENT
void initialize_vars(t_mbox *mbox, char **env);                         //creates the ll on startup
void free_vars(t_mbox *mbox);                                           //frees the ll
static void *free_var(t_env *temp);                                     //free the given node
static void var_add_back(t_mbox *mbox, t_env *new_var);                 //adds the node to the end of the ll
 
// READ FUNCTIONS
t_bool is_var(const t_mbox *mbox, const char *key);                     //checks if the argument 'key' is present in list
static t_env *get_var_node(const t_mbox *mbox, const char *key);        //returns a pointer to the node with the given key
char *get_var_value(const t_mbox *mbox, const char *key);               //returns a pointer to the value of the given key
static int get_vars_count(const t_env *env_var);                        //returns the amount of nodes in the ll
char **get_env_as_matrix(const t_mbox *mbox, const char *put_quotes)    //creates a matrix of strings from the ll

// WRITE FUNCTIONS
void set_var_value(t_mbox *mbox, const char *key, const char *value);   //updates/creates node with the given key and value
void set_var_value_int(t_mbox *mbox, const char *key, int int_value);   //updates/creates node with the given key and int value
void increment_shlvl(t_mbox *mbox);                                     //increases the value of the 'SHLVL' variable
void unset_var(t_mbox *mbox, const char *key);                          //removes the node with the given key from the ll
```

With the following [builtin](#builtins) commands variables can be...
- **shown** using [env](#env-builtin)
- **sorted and shown**  using [export](#export-builtin) without arguments
- **created** using [export](#export-builtin)
- **changed** using [export](#export-builtin)
- **deleted** using [unset](#unset-builtin)

> :bulb:    		&nbsp; The linked list will be used for the [execve](#execve) function call.\
> :bulb:			&nbsp; The linked list will be used for storing the [exit status](#exit-status).\
> :bulb:			&nbsp; Keep in mind that some [builtins](#builtins) (e.g. [cd](#cd-builtin)) change some variables during runtime!

## Known Bugs

**export vs env**

If the built-in export is called with a valid key but no equal sign (like `export foo`) `foo` should be listed in the output of the `export`, but not in the output of the `env` function call. In frankenshell, `foo` is not added to the linked list of variables and therefore is not printed in either case. A simple boolean in the `s_env` structure could solve the problem.

---

**single cmds with redirs**
Since frankenshell doesn't fork for a single builtin cmd like `echo foo > out` it changes the fds of the main process. This might affect the next cycle since the fds are not reseted.
---

## Acknowledgments
Thx to all those guys and gals for hints, tipps and feedback!

[@Gabriel](https://github.com/portugueseTorch)\
[@Martim](https://github.com/mm1212)\
[@Margarida](https://github.com/MariaAguiar)\
[@Manuel](https://github.com/manuel-aguiar)

> :arrow_up:   <a href="#docu-top">back to top</a>   :arrow_up:




















































<!-- MARKDOWN LINKS & IMAGES -->
[example-gif]: /images/example.gif
[builtin_42]: /images/builtin_42.png
[mindmap-ast-png]: /images/mindmap-ast.png