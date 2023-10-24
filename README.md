-> https://docs.google.com/spreadsheets/d/17linwSWODYO4O9Db0FohJYr_8shMTGvyo0MjToPrcAI/edit#gid=0

# FRANKENSHELL

some little bash copy....

## Setup

### minibox
blabla

### Store the Enviorment Variables
linkes list bla bla

## One Cycle
### Lexer
#### Trim String
input: some string from readline (not NULL)
output: no whitespaces at front or end

#### mark Seperators
input: trimmed string
marks all context qoutes through replacing them with random ascii values
output: qouted input

#### expand variables
replacing all ```$ABC``` with corresponing values (they can bee null)
only outside of single qouted block!

#### Tokenize
seting up a linked list. seperators are
- pipes (```|```)
- redirs (```>```, ```>>```, ```<```, ```<<```)
- spaces (outside of context qoute blocks)
- context qoutes

### Parser
- building a tree
- examples

### Executor

#### Main Procedure

#### Setup Pipes

#### Setup Redirections
##### Heredoc
Here the official readme
->https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Here-Documents

In the heredoc var expansion also works!
The heredoc doenst consider qoutes at all, so there are no contextual quotes
So in generall all variables no matter the qoute state will expand!

Anyhow, if the LIM is put in either single or double qoutes like ```<< "LIM" cat```
var expansion is somehow suppressed. This is atm a huge problem since our code removes
all contextual qoutes so the heredoc function doesnt receive any information about
qoutes! Not sure how to fix!
Because we can not leave contextual qoutes in a all cases inside the args node because
in all other cases they need to be removed before execution!

Functions of \ $ ` 
\   is a flag that the next one will be ignored if its $ or `
        e.g. "Hi \$LESS" -> "HI $LESS"
    if its something else we print both
        e.g. "Hello W\orld" -> "Hello W\orld"

$   is just doint normal var expansion (if the LIM isnt in qoutes)

`   the strange qouted string will be executed! (if the LIM isnt in qoutes)
        e.g. "Hi `ls` World" -> "Hi libft Makefile minishell World"
        e.g. "Hi `cmdnotexist` World" -> "cmdnotexist: command not found \n Hi  World"

maybe the remove conte

#### Executing System Commands

#### Executing Builtin Commands

