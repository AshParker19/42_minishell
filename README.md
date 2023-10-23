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

