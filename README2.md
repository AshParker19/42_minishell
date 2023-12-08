# FRANKENSHELL

**FRANKENSHELL** is a version of the 42 School project (**minishell**) that recreates in C a simplified version of the bash shell.
## Authors
[ @Anatolii](https://github.com/AshParker19)\
[@Alex](https://github.com/0815-alex)

[Documentation &](./docs/documentation.md)

Thx to all those guys and gals for hints, tipps and feedback!\
[@Gabriel](https://github.com/portugueseTorch)
[@Martim](https://github.com/mm1212),
[@Margarida](https://github.com/MariaAguiar),
[@Manuel](https://github.com/manuel-aguiar)

## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Order of Execution (aka how the f*uck does it work)](#order-of-execution)
   - [Prepare Input](#prepare-input)
	 - [Trim](#trim)
	 - [Mark Context Chars](#mark-context-chars)
	 - [Expand Variables](#expand-variables)
	 - [Tokenize](#tokenize)
	 - [Parse](#parse)
   - [Execution](#execution)
	 - [Check for 'exit'](#check-for-exit)
	 - [Execute Single Command](#execute-single-command)
	 - [Execute Piped Commands](#execute-piped-commands)
5. [Variable Storage](#variable-storage)
6. [Builtins](#builtins)
8. [Known Bugs](#bugs)

## Introduction

As ChatGPT said in 2023:
> Minishell is a [42 school](https://42.fr/en/homepage/) project designed to create a simplified Unix shell. The idea behind Minishell is to develop a basic command-line interface (CLI) that can execute simple commands and handle input/output redirection. It's meant to serve as a learning exercise for students to gain a fundamental understanding of how shells work by implementing core features like parsing user input, managing processes, handling signals, creating builtins and executing system commands.

## How To Use
To clone and run frankenshell, you'll need Git and TODO
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


```
Usage:
	./frankenshell [OPTIONS]

Options:
	--info, -i	prints details about the program flow during runtime
```
**frankenshell** is designed to mimic the behavior of the traditional **bash** shell. So feel free to use it like bash.\
Below are the key features and functionalities included:
### Contextual Quotes
- **Single Quotes**: Enclosing text in single quotes (`'`) prevents the shell from interpreting any metacharacters within the quoted sequence.
- **Double Quotes**: Using double quotes (`"`) also prevents interpretation of metacharacters, except for the dollar sign (`$`), which is used for variable expansion.

> ℹ️ &nbsp; Unclosed quotes (e.g. ```echo "Hello World```) will result in an error:\
> ⚠️ &nbsp; frankenshell: syntax error: unclosed quotes

### Variable Management
On programm start the enviromental variables will be loaded into frankenshell.\
With the following [builtin](#builtins) commands variables can be...
- **shown** using [env](#env)
- **sorted and shown**  using [export](#export) without arguments
- **created** using [export](#export)
- **changed** using [export](#export)
- **deleted** using [unset](#unset)

> ℹ️ &nbsp; Keep in mind that some [builtins](#builtins) (e.g. [cd](#cd)) change some variables during runtime!

#### The **Variable Expansion** works simmilar like in bash:
| Command            | Expand       | Output                        |
| ----------------- | :----------: | ----------------------------- |
| `echo $USER`       |      ✅        |      `current_user_value`      |
| `echo "$USER"`     |      ✅        |      `current_user_value`      |
| `echo '$USER'`     |      ❌        |      `$USER`                   |
| `<< $USER cat`     |      ❌        |  Won't expand, so the `EOF` of the heredoc will be `$USER` |


### Redirections
The table below describes the redirection features available in FRANKENSHELL:
| Feature| Mode            | Description                                                                                | Example                           |
|------|-------------|--------------------------------------------------------------------------------------------------|-----------------------------------|
| `<`  |Input Redirection         | Redirects input from a file to a command.                                           | `wc < file.txt`              |
| `<<` |Heredoc                   | Allows inputting multiple lines until a termination string is reached.              | `<< this_exits_the_hd wc`                  |
| `>`  |Output Redirection        | Redirects the output of a command to a file, overwriting it if it already exists.   | `echo "replace by foo" > file.txt`              |
| `>>` |Append Output Redirection | Appends command output to a file, creating it if it doesn't exist.                  | `echo "append foo" >> file.txt`

These redirections allow for flexible manipulation of command input and output, similar to standard bash functionality.

### Pipes
Pipes (`|`) allow the output of one command to be used as input for another, enabling command chaining.

### Built-in Commands
| Command   | Description                                           |
|-----------|-------------------------------------------------------|
| `echo`    | Displays a line of text.                              |
| `cd`      | Changes the current directory.                        |
| `pwd`     | Prints the working directory.                         |
| `export`  | Sets or exports environment variables.                |
| `unset`   | Unsets environment variables.                         |
| `env`     | Displays the environment variables.                   |
| `42`      | 42 it is ;)											|
| `history` | Displays the command history.                         |
| `exit`    | Exits the shell.                                      |

Use these features as you would in a typical bash environment ;)

## Order of Execution (aka how ~~the f*uck~~ does it work)

### Prepare Input

#### Trim

[Explanation of the Trim process.]

#### Mark Context Chars

[Details about how context characters are marked.]

#### Expand Variables

[Description of the variable expansion process.]

#### Tokenize

[Explanation of the tokenization process.]

#### Parse

[Details on how the input is parsed.]

### Execution

#### Check for 'exit'

[Explanation of how the 'exit' command is handled.]

#### Execute Single Command

[Details on executing a single command like `ls -l >out.txt`.]

#### Execute Piped Commands

[How to execute piped commands like `ls -l | grep Makefile.md`.]

## Variable Storage

[Details on how variables are stored in FRANKENSHELL.]

## Builtins

Each built-in command in FRANKENSHELL is detailed below with specific information and examples.

### `echo`
Displays a line of text.

#### Table: Infos
|-----------------------|------------------------------|
| Number of Arguments   | [Number of arguments info]   |
| Flags                 | [Flags info]                 |
| Exit Status           | [Exit status info]           |
| Errors                | [Errors info]                |

#### Table: Examples
| Cmd                | STDOUT        | STDERR     | Exit Status | Explanation           |CHANGE ENV VARS
|--------------------|---------------|------------|-------------|-----------------------|
| `echo "Hello"`     | Hello         |            | 0           | Standard output       |
| `echo -n "World"`  | World         |            | 0           | No newline at the end |
| `[Third Example]`  | [STDOUT]      | [STDERR]   | [Status]    | [Explanation]         |
| `[Fourth Example]` | [STDOUT]      | [STDERR]   | [Status]    | [Explanation]         |


## Known Bugs
	- export vs env
	- single cmds with redirs


https://htmlpreview.github.io/?https://github.com/AshParker19/42_minishell/blob/cleanItDone/test.html

