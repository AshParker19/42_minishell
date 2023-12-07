# FRANKENSHELL

FRANKENSHELL is a 42 School project that recreates a simplified version of the bash shell written in C.
## Authors
- [Anatolii](https://github.com/AshParker19)
- [Alex](https://github.com/0815-alex)


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

[Here, you'll provide an overview of the FRANKENSHELL project, its purpose, and its significance.]

## Installation

To install and run FRANKENSHELL, follow these simple steps:

- Clone the repository: https://github.com/AshParker19/42_minishell
- Compile the program using `make`:
- Start the program using: `./minishell [optional flag]`
- Optional flags include: `---info` or `-i`: prints details about the program flow.
- To exit the minishell, simply type: `exit`

## Usage

FRANKENSHELL is designed to mimic the behavior of the traditional bash shell. Below are the key features and functionalities included:

### Variable Expansions
- Variables from the environment (`env`) can be expanded, allowing dynamic command executions based on the current environment settings.

### Treating Contextual Quotes
- **Single Quotes**: Enclosing text in single quotes (`'`) prevents the shell from interpreting any metacharacters within the quoted sequence.
- **Double Quotes**: Using double quotes (`"`) also prevents interpretation of metacharacters, except for the dollar sign (`$`), which is used for variable expansion.

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

## Order of Execution (aka how the f*uck does it work)

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

[Information about the built-in commands in FRANKENSHELL.]

## Builtins Known Bugs
	- export vs env
	- single cmds with redirs