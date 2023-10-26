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

>>>>>>>>>>

PROJEKT: FIX THE VAR EXPANSION, HEREDOCS AND TOKENIZER IN ONE GO!

1. TRIM
2. MARK QUOTES AND SPACES
3.1 VAR EXPANSION
	- leave all as it is (care about qoute state for expansion...etc.)
	- add a function that detects somehow the presense of "<<"    keep in mind that it CANT be like "<        <" atm out tokenizer accepts this case
		if we find << we switsh to anotger var expension mode -> 3.2 extract_limiter
		
3.2 extract_limiter (var expansion for << case)
	- same as 3.1 with some small changes!
	- this function automaticlly switches back to 3.1 if the end of the limiter of << was found! (IT SHOULD RETURN HOW MANY CHARS BELONG TO THE LIM SO THAT 3.1 KNOWS WHERE TO CONTINUE)
		- its over if we are
			- outside of qoute state
			- find a non printable char
			- or input is over (e.g. << lol)
	- this function first doesnt do anything else but creating a new string with everything that belomgs to the Limiter (so no Var expansion, no qoute removing)
	- instead its just copying the read chars to a new string we could call "limiter"
		- important! here we need to remove_offest of all quotes!    ? -> "
	- when we found the end of the LIMITTER we need to somehow check all the qoutes
		- IMPORTANT: A delimiter does never expand its variables in bash: so $LESS as a limiter stays  fucking $LESS
			- only execption is if the $ is infront of an contextual qoute (like << $'USER' or << $"USER") then
				- remove dollar and continue
		- to deal with the qoutes inside the limiter those rules apply
			- remeove contextual qoutes
			- leave none contextual qoutes
			- if found any qoute at all! MARK IT and pass it over to the heredoc so the heredoc know to ignore var expension
				- IDEA: the contextual qoutes by now are real qoutes (no garbage)
					- maybe we can just leave them in the string and the tokenizer will not delete it
						-> so it might end up in the value of the redir node?
						-> herdoc can trimm them off and then doest do expansion
						
4. TOKENIZE
	- works atm okayish but
	- after the expansion maybe we need to merge nodes together (like A=s and l$A should return ls)
	- we need to check if there are spaces between cmd and arg (like ls"-l" -> should be (ls-l: command not found)
	- MARTIM SAYS:
		ONLY VALID TOKEN SEPERATORS ARE (they always need to be outside of quotes)
			- whitspaces
			- pipes 
			- redirs
5. PARSE
6. EXECUTION
>>>>>>>>>>

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

